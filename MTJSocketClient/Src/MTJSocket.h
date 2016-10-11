//
//  MTJSocket.h
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#ifndef __MTJSocketClient__MTJSocket__
#define __MTJSocketClient__MTJSocket__

#include <stdio.h>
#include "MTJSocketBuffer.h"
#include "MTJSocketDataFrame.h"
#include "MTJSocketListener.h"
#include "MTJSocketProtocal.h"

class MTJSocketListener;
class MTJSocket {
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
     *  连接服务器
     *
     *  @param ip   IP地址
     *  @param port 端口
     */
    void Open(const char* ip,unsigned int port);
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
    void SetListener(MTJSocketListener* pListener);
    MTJSocketListener* GetListener();
    
    void SetProtocal(MTJSocketProtocal *pProtocal);
    MTJSocketProtocal* GetProtocal();
    int GetSocketId();
    
};

#endif /* defined(__MTJSocketClient__MTJSocket__) */
