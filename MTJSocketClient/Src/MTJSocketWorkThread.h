//
//  MTJSocketWorkThread.h
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#ifndef __MTJSocketClient__MTJSocketWorkThread__
#define __MTJSocketClient__MTJSocketWorkThread__

#include <semaphore.h>
#include "MTJSocketThread.h"
#include "MTJSocketQueue.h"

class MTJSocketWorkThread : public MTJSocketThread {
private:
    MTJSocketQueue<MTJSocketThread>* m_pQueue;
protected:
    virtual void Run();
    
public:
    MTJSocketWorkThread();
    ~MTJSocketWorkThread();
    inline void AddTask(MTJSocketThread* pThread){
        m_pQueue->Offer(pThread);
        sem_post(m_pSem);
    }
    inline void SetStatus(int nStatus){
        m_nStatus = nStatus;
    }
    int TaskCount();
};

#endif /* defined(__MTJSocketClient__MTJSocketWorkThread__) */
