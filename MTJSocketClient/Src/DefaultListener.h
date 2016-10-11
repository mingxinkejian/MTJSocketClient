//
//  DefaultListener.h
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#ifndef __MTJSocketClient__DefaultListener__
#define __MTJSocketClient__DefaultListener__

#include "MTJSocketListener.h"
#include "MTJSocketBuffer.h"
#include "MTJSocket.h"

class DefaultListener : public MTJSocketListener {
    
    
public:
    DefaultListener();
    virtual ~DefaultListener();
    virtual void OnMessage(MTJSocket* pSock,MTJSocketBuffer* pFrame);
    virtual void OnClose(MTJSocket* pSock,bool bFromRemote);
    virtual void OnIdle(MTJSocket* pSock);
    virtual void OnOpen(MTJSocket* pSock);
    virtual void OnError(MTJSocket* pSock,const char* error);
};

#endif /* defined(__MTJSocketClient__DefaultListener__) */
