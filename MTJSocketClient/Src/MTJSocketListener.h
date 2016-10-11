//
//  MTJSocketListener.h
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#ifndef __MTJSocketClient__MTJSocketListener__
#define __MTJSocketClient__MTJSocketListener__

#include "MTJSocket.h"
#include "MTJSocketBuffer.h"
#include "MTJSocketThread.h"

#define SOCKET_SIZE 1024 * 2

class MTJSocket;
class MTJSocketListener : public MTJSocketThread{

private:
    MTJSocket* m_pContext;
public:
    MTJSocketListener();
    virtual ~MTJSocketListener();
    virtual void OnMessage(MTJSocket* pSock,MTJSocketBuffer* pFrame) = 0;
    virtual void OnClose(MTJSocket* pSock,bool bFromRemote) = 0;
    virtual void OnIdle(MTJSocket* pSock) = 0;
    virtual void OnOpen(MTJSocket* pSock) = 0;
    virtual void OnError(MTJSocket* pSock,const char* error) = 0;
    void SetContext(MTJSocket* pSock);
    /**
     *  @author mingtingjian, 16-10-11 17:10:35
     *
     *  用于处理接收服务器发送的消息
     */
    virtual void Run();
};

#endif /* defined(__MTJSocketClient__MTJSocketListener__) */
