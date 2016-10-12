//
//  MTJSocket.cpp
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#include "MTJSocket.h"
#include <errno.h>

MTJSocket::MTJSocket():
m_pIP(NULL),
m_pListener(NULL),
m_pProtocal(NULL)
{
}

MTJSocket::~MTJSocket(){

    MTJ_SAFE_DELETE(m_pProtocal);
    MTJ_SAFE_DELETE(m_pListener);
}

int MTJSocket::GetSocketId(){

    return m_nSsockId;
}

MTJSocketListener* MTJSocket::GetListener(){

    return m_pListener;
}

MTJSocketProtocal* MTJSocket::GetProtocal(){

    return this->m_pProtocal;
}

void MTJSocket::SetProtocal(MTJSocketProtocal *pProtocal){

    m_pProtocal = pProtocal;
}

void MTJSocket::Open(MTJSocketListener *pListener,SocketType eSockType){

    m_pListener = pListener;
    m_pListener->SetContext(this);

    int domain = -1;
    int type = -1;
    
    switch (eSockType) {
        case SOCK_TCP:
            domain = AF_INET;
            type = SOCK_STREAM;
            break;
        case SOCK_TCP6:
            domain = AF_INET6;
            type = SOCK_STREAM;
            break;
        case SOCK_UDP:
            domain = AF_INET;
            type = SOCK_DGRAM;
            break;
        case SOCK_UDP6:
            domain = AF_INET6;
            type = SOCK_DGRAM;
            break;
#if TARGET_PLATFORM != PLATFORM_WIN32
//windows下不支持此参数，在客户端不建议使用下面两个选项，仅作为支持
        case SOCK_UNIX_DGRAM:
            domain = AF_UNIX;
            type = SOCK_DGRAM;
            break;
        case SOCK_UNIX_STREAM:
            domain = AF_UNIX;
            type = SOCK_STREAM;
            break;
#endif
        default:
            domain = AF_INET;
            type = SOCK_STREAM;
            break;
    }
    m_nDomain = domain;
    m_nType = type;
    m_eSockType = eSockType;
    m_nSsockId = socket(AF_INET, SOCK_STREAM, 0);
}

void MTJSocket::Connect(const char* ip,unsigned int port,double dTimeout,int nFlag){
    
    m_pIP = ip;
    m_nPort = port;
    if (m_nSsockId != INVALID_SOCKET) {
        if (InitInetAddr() != 1) {
            //不等于1表示创建失败
            m_pListener->OnClose(this, false);
        }else{
            //特殊处理，UDP为无连接协议
            if (m_eSockType == SOCK_UDP || m_eSockType == SOCK_UDP6) {
//                goto UDP;
            }
            int connError;
            extern int errno;
            if ((connError = connect(m_nSsockId, (struct sockaddr*)&m_sSockAddr.addr, m_sSockAddr.len)) != SOCKET_ERROR) {
//            UDP:
                int bufSize = SOCKET_UDP_SIZE; //通常设置为32K
                if (m_eSockType == SOCK_UDP || m_eSockType == SOCK_UDP6) {
                    setsockopt(m_nSsockId, SOL_SOCKET, SO_SNDBUF, &bufSize, sizeof(bufSize));
                    setsockopt(m_nSsockId, SOL_SOCKET, SO_RCVBUF, &bufSize, sizeof(bufSize));
                }
                
                m_pListener->OnOpen(this);
                m_pListener->Start();
            }else{
                printf("connect error code: %d\n",errno);
                m_pListener->OnClose(this, false);
            }
        }
    }else{
        m_pListener->OnClose(this, false);
    }
}

int MTJSocket::InitInetAddr(){
    
    void* s_addr = NULL;
    if (m_eSockType == SOCK_TCP || m_eSockType == SOCK_UDP) {
        m_sSockAddr.addr.inetv4.sin_family = AF_INET;
        m_sSockAddr.addr.inetv4.sin_port = htons(m_nPort);
        s_addr = &m_sSockAddr.addr.inetv4.sin_addr.s_addr;
        m_sSockAddr.len = sizeof(m_sSockAddr.addr.inetv4);
        //inet_pton为新的函数，支持IPV6，inet_addr比较老
        if (inet_pton(AF_INET, m_pIP, s_addr)) {
            return 1;
        }
    }else if(m_eSockType == SOCK_TCP6 || m_eSockType == SOCK_UDP6){
        m_sSockAddr.addr.inetv6.sin6_family = AF_INET6;
        m_sSockAddr.addr.inetv6.sin6_port = htons(m_nPort);
        s_addr = &m_sSockAddr.addr.inetv6.sin6_addr.s6_addr;
        m_sSockAddr.len = sizeof(m_sSockAddr.addr.inetv6);
        if (inet_pton(AF_INET6, m_pIP, s_addr)) {
            return 1;
        }
    }else if(m_eSockType == SOCK_UNIX_STREAM || m_eSockType == SOCK_UNIX_DGRAM){
        printf("sorry unsupport SOCK_UNIX_STREAM or SOCK_UNIX_DGRAM\n");
    }
    
    return -1;
}

int MTJSocket::Close(){

    if (m_nSsockId == -1) {
        return -1;
    }
    
    int t = m_nSsockId;
    m_nSsockId = -1;
#if TARGET_PLATFORM == PLATFORM_WIN32
    shutdown(t, SD_SEND);
    return (closesocket(t));
#else
    shutdown(t, SHUT_RDWR);
    return close(t);
#endif
}

int MTJSocket::Send(MTJSocketBuffer *frame){
    
    char* content = frame->GetData();
    int bytes = 0;
    int count = 0;
    int len = frame->ReadableBytes();
    
    if (m_eSockType == SOCK_TCP || m_eSockType == SOCK_TCP6) {
        
        while (count < len) {
            bytes = (int)send(m_nSsockId, content + count, len - count, 0);
            if (bytes == -1 || bytes == 0) {
                return -1;
            }
            count += bytes;
            frame->ReaderIndex(frame->ReaderIndex() + bytes);
        }
    }else if (m_eSockType == SOCK_UDP || m_eSockType == SOCK_UDP6){
        extern int errno;
        count = (int)sendto(m_nSsockId, content, len, 0, (struct sockaddr*)&m_sSockAddr.addr, m_sSockAddr.len);
        printf("sendto error code: %d\n",errno);
    }


    
    return count;
}

int MTJSocket::Send(MTJSocketDataFrame *frame){

    if (frame->IsEnd()) {
        return Send(frame->GetData());
    }
    
    return 0;
}