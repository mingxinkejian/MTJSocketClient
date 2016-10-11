//
//  MTJSocket.cpp
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#include "MTJSocket.h"
#include "MTJSocketPlatformConfig.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#include "MTJSocketBuffer.h"
#include "MTJSocketListener.h"
#include "MTJSocketProtocal.h"
#include "MTJSocketDataFrame.h"

#if TARGET_PLATFORM == PLATFORM_WIN32
#pragma comment(lib, "wsock32")
#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#endif

MTJSocket::MTJSocket():
m_pIP(NULL),
m_pListener(NULL),
m_pProtocal(NULL)
{
}

MTJSocket::~MTJSocket(){

    delete m_pProtocal;
    delete m_pListener;
}

int MTJSocket::GetSocketId(){

    return m_nSsockId;
}

MTJSocketListener* MTJSocket::GetListener(){

    return m_pListener;
}

void MTJSocket::SetListener(MTJSocketListener *pListener){

    m_pListener = pListener;
    m_pListener->SetContext(this);
}

MTJSocketProtocal* MTJSocket::GetProtocal(){

    return this->m_pProtocal;
}

void MTJSocket::SetProtocal(MTJSocketProtocal *pProtocal){

    m_pProtocal = pProtocal;
}

void MTJSocket::Open(const char *ip, unsigned int port){

    m_pIP = ip;
    m_nPort = port;
    
    //创建socket连接
    if ((m_nSsockId = socket(AF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET) {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(m_nPort);
        addr.sin_addr.s_addr = inet_addr(ip);
        
        if (connect(m_nSsockId, (struct sockaddr*)&addr, sizeof(addr)) != SOCKET_ERROR) {
            m_pListener->OnOpen(this);
            m_pListener->Start();
        }else{
            m_pListener->OnClose(this, false);
        }
    }else{
        m_pListener->OnClose(this, false);
    }
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
    while (count < len) {
        bytes = (int)send(m_nSsockId, content + count, len - count, 0);
        if (bytes == -1 || bytes == 0) {
            return -1;
        }
        count += bytes;
        frame->ReaderIndex(frame->ReaderIndex() + bytes);
    }
    
    return count;
}

int MTJSocket::Send(MTJSocketDataFrame *frame){

    if (frame->IsEnd()) {
        return Send(frame->GetData());
    }
    
    return 0;
}