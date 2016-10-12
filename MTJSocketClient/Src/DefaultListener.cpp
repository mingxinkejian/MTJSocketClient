//
//  DefaultListener.cpp
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#include "DefaultListener.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

DefaultListener::DefaultListener(){
}
DefaultListener::~DefaultListener(){
}
/**
 *  @author mingtingjian, 16-10-11 17:10:09
 *
 *  有数据到来时，解析处理数据
 *
 *  @param pSock
 *  @param pFrame
 */
void DefaultListener::OnMessage(MTJSocket* pSock,MTJSocketBuffer* pFrame){
    pFrame->ReaderIndex(0);
    
    std::string str = pFrame->ReadUTF8();
    printf("接收到的数据:%s\n",str.c_str());

    MTJ_SAFE_DELETE(pFrame);
}
void DefaultListener::OnClose(MTJSocket* pSock,bool bFromRemote){
    printf("Socket closed\n");
}
void DefaultListener::OnIdle(MTJSocket* pSock){
    printf("Socket connection is idle\n");
}
void DefaultListener::OnOpen(MTJSocket* pSock){
    printf("socket connecting");
    
    MTJSocketDataFrame* frame = new MTJSocketDataFrame(SOCKET_SIZE);
    std::string buff = "测试Socket";
    frame->PutString((char*)buff.c_str());
    frame->End();
    pSock->Send(frame);
    
    MTJ_SAFE_DELETE(frame);
}
void DefaultListener::OnError(MTJSocket* pSock,const char* error){
    printf("Socket connection error :%s\n",error);
}