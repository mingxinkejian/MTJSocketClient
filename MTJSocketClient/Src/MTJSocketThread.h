//
//  MTJSocketThread.h
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#ifndef __MTJSocketClient__MTJSocketThread__
#define __MTJSocketClient__MTJSocketThread__

#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
//信号量
#include <semaphore.h>

typedef void* (*ThreadFunc)(void*);

class MTJSocketThread {

public:
    enum ThreadState{
        ERR_ALREADERY_INITIALIZED = -6,
        ERR_AT_CREATE_THREAD = -5,
        ERR_AT_CREATE_SEM = -4,
        ERR_NO_TASK = -3,
        ERR_NOT_IDLE = -2,
        UNINITIALIZED = -1,
        IDLE = 0,
        RUNNING = 1,
        QUITED = 9
    };
    
private:
    pthread_t m_threadId;
    /**
     *  @author mingtingjian, 16-10-11 15:10:10
     *
     *  创建线程
     *
     *  @param pFunc     回调函数
     *  @param pContext
     *  @param bDetached
     *  @param bScope
     *
     *  @return return value description
     */
    int Create(ThreadFunc pFunc,void* pContext,bool bDetached = false,bool bScope = false);
    /**
     *  @author mingtingjian, 16-10-11 15:10:36
     *
     *  结束线程
     */
    void End();
    int Init();
    static void* DoRun(void* pContext);
protected:
    int m_nStatus;
    sem_t* m_pSem;
public:
    MTJSocketThread();
    virtual ~MTJSocketThread();
    virtual void Run() = 0;
    inline sem_t* GetSem(){
    
        return m_pSem;
    }
    inline int Detach(){
    
        return pthread_detach(m_threadId);
    }
    inline int Join(void** retValue = NULL){
        
        return pthread_join(m_threadId, retValue);
    }
    inline void Exit(void* retValue = NULL){
    
        if (IsCurrent()) {
            pthread_exit(retValue);
        }
    }
    inline void Abalienate(){
    
        sched_yield();
    }
    inline bool IsCurrent(){
    
        if (pthread_equal(m_threadId, pthread_self()) != 0) {
            return true;
        }
        
        return false;
    }
    inline pthread_t GetThreadId(){
    
        return m_threadId;
    }
    inline int GetStatus(){
    
        return m_nStatus;
    }
    /**
     *  @author mingtingjian, 16-10-11 15:10:20
     *
     *  启动线程
     *
     *  @return
     */
    int Start();
};

#endif /* defined(__MTJSocketClient__MTJSocketThread__) */
