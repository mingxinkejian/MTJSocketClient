//
//  MTJSocketWorkThread.cpp
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#include "MTJSocketWorkThread.h"
#include "MTJSocketBlockingQueue.h"
#include "MTJSocketThread.h"
#include <errno.h>

MTJSocketWorkThread::MTJSocketWorkThread(){
    
    m_pQueue = new MTJSocketBlockingQueue<MTJSocketThread>;
    Start();
}
MTJSocketWorkThread::~MTJSocketWorkThread(){
    
    MTJ_SAFE_DELETE(m_pQueue);
}

void MTJSocketWorkThread::Run(){

    while (m_nStatus != QUITED) {
        MTJSocketThread* task = (MTJSocketThread*)m_pQueue->Poll();
        if (task != NULL) {
            m_nStatus = RUNNING;
            task->Run();
            MTJ_SAFE_DELETE(task);
        }else{
            m_nStatus = IDLE;
            sem_wait(m_pSem); //等待添加新的task
        }
    }
}


int MTJSocketWorkThread::TaskCount(){

    return m_pQueue->Size();
}
