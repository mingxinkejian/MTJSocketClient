//
//  MTJSocketListener.cpp
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#include "MTJSocketListener.h"
#include "MTJSocketPlatformConfig.h"
#include "MTJSocket.h"
#include "MTJSocketBuffer.h"
#include "MTJSocketProtocal.h"

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
#endif


MTJSocketListener::MTJSocketListener():
m_pContext(NULL)
{

}
MTJSocketListener::~MTJSocketListener(){

}

void MTJSocketListener::SetContext(MTJSocket *pSock){

    m_pContext = pSock;
}

void MTJSocketListener::Run(){

    MTJSocketBuffer* buffer = new MTJSocketBuffer(SOCKET_SIZE);
    int size = 0;
    int sockId = m_pContext->GetSocketId();
    while (true) {
        size = (int)recv(sockId, buffer->GetData(), SOCKET_SIZE, 0);
        if (size > 0) {
            buffer->ReaderIndex(0);
            buffer->WriterIndex(size);
            while (true) {
                MTJSocketBuffer* frame = m_pContext->GetProtocal()->TranslateFrame(buffer);
                if (frame != NULL) {
                    OnMessage(m_pContext, frame);
                }else{
                    break;
                }
            }
        }else{
            break;
        }
    }
    delete buffer;
    OnClose(m_pContext, true);
}