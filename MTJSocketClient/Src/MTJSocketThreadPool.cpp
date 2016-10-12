//
//  MTJSocketThreadPool.cpp
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#include "MTJSocketThreadPool.h"
#include "MTJSocketPlatformConfig.h"
MTJSocketThreadPool::MTJSocketThreadPool(int nPoolSize):
m_nPoolSize(nPoolSize),
m_pPool(NULL)
{
    m_pPool = new MTJSocketWorkThread*[nPoolSize];
    for (int i = 0; i < nPoolSize; ++i) {
        m_pPool[i] = new MTJSocketWorkThread();
    }
}

MTJSocketThreadPool::~MTJSocketThreadPool(){
    
    if (NULL == m_pPool) {
        
    }else{
        for (int i = 0; i < m_nPoolSize; ++i) {
            if (NULL == m_pPool[i]) {
                continue;
            }
            MTJ_SAFE_DELETE(m_pPool[i]);
        }
        MTJ_SAFE_DELETE_ARRAY(m_pPool);
    }
}

void MTJSocketThreadPool::Offer(MTJSocketThread* pTask){
    
//    bool result = false;
    MTJSocketWorkThread* work = NULL;
    for (int i = 0; i < m_nPoolSize; ++i) {
        if (m_pPool[i]->GetStatus() == MTJSocketThread::IDLE) {
            
            m_pPool[i]->AddTask(pTask);
            return;
        }else if (work == NULL){
            
            work = m_pPool[i];
        }else if (work->TaskCount() > m_pPool[i]->TaskCount()){
        
            work = m_pPool[i];
        }
    }
    
    work->AddTask(pTask);
}

void MTJSocketThreadPool::Shutdown(){
    
    if (NULL == m_pPool) {
        return;
    }
    
    for (int i = 0; i < m_nPoolSize; ++i) {
        if (NULL == m_pPool[i]) {
            continue;
        }
        m_pPool[i]->SetStatus(MTJSocketThread::QUITED);
        sem_post(m_pPool[i]->GetSem());
        m_pPool[i]->Join();
        MTJ_SAFE_DELETE(m_pPool[i]);
    }
    MTJ_SAFE_DELETE_ARRAY(m_pPool);
}