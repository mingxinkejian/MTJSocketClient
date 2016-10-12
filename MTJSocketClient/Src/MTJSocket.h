//
//  MTJSocket.h
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#ifndef __MTJSocketClient__MTJSocket__
#define __MTJSocketClient__MTJSocket__


#include "MTJSocketBuffer.h"
#include "MTJSocketDataFrame.h"
#include "MTJSocketListener.h"
#include "MTJSocketProtocal.h"
#include "MTJSocketPlatformConfig.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

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

struct SocketAddress {
    union{
        struct sockaddr_in inetv4;
        struct sockaddr_in6 inetv6;
    }addr;
    socklen_t len;
};

class MTJSocketListener;
class MTJSocket {
public:
    
    enum SocketType{
        SOCK_TCP    = 1,
        SOCK_UDP    = 2,
        SOCK_TCP6   = 3,
        SOCK_UDP6   = 4,
        SOCK_UNIX_DGRAM = 5, //unix sock dgram
        SOCK_UNIX_STREAM = 6, //unix sock stream
    };
    
    SocketAddress m_sSockAddr;
protected:
    int m_nDomain;
    int m_nType;
    SocketType m_eSockType;
private:
    const char* m_pIP;
    unsigned int m_nPort;
    unsigned int m_nSsockId;
    
    MTJSocketListener* m_pListener;
    MTJSocketProtocal* m_pProtocal;
    
public:

    
    MTJSocket();
    virtual ~MTJSocket();
    /**
     *  @author mingtingjian, 16-10-11 16:10:37
     *
     *  开启socket配置
     *  SOCK_UNIX_DGRAM = 5, //unix sock dgram
     *  SOCK_UNIX_STREAM = 6, //unix sock stream
     *  上面两个选项不建议使用，如果使用上述两个选项，在windows下默认为TCP连接
     *
     *  @param ip   IP地址
     *  @param port 端口
     */
    void Open(MTJSocketListener *pListener,SocketType eSockType);
    void Connect(const char* ip,unsigned int port,double dTimeout,int nFlag = 0);
    /**
     *  @author mingtingjian, 16-10-11 16:10:52
     *
     *  关闭连接
     *
     *  @return
     */
    int Close();
    int Send(MTJSocketBuffer* frame);
    int Send(MTJSocketDataFrame* frame);
    MTJSocketListener* GetListener();
    
    void SetProtocal(MTJSocketProtocal *pProtocal);
    MTJSocketProtocal* GetProtocal();
    int GetSocketId();
    
    inline SocketType GetSocketType(){
        return m_eSockType;
    }
private:
    int InitInetAddr();
};

#endif /* defined(__MTJSocketClient__MTJSocket__) */
