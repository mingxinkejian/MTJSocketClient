//
//  MTJSocketThread.cpp
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#include "MTJSocketThread.h"
#include "MTJSocketPlatformConfig.h"
#include <string>
#include <sstream>
#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

MTJSocketThread::MTJSocketThread():
m_nStatus(UNINITIALIZED),
m_pSem(NULL)
{
    
}

MTJSocketThread::~MTJSocketThread(){

    End();
}

int MTJSocketThread::Create(ThreadFunc pFunc, void *pContext,bool bDetached,bool bScope){

    pthread_attr_t threadAttr;
    int nStatus;
    nStatus = pthread_attr_init(&threadAttr);
    if (nStatus != 0) {
        return -1;
    }
    
    if (bDetached) {
        nStatus = pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);
        if (nStatus != 0) {
            pthread_attr_destroy(&threadAttr);
            return -1;
        }
    }
    
    if (bScope) {
        nStatus = pthread_attr_setscope(&threadAttr, PTHREAD_SCOPE_SYSTEM);
        if (nStatus != 0) {
            pthread_attr_destroy(&threadAttr);
            return -1;
        }
    }
    
    nStatus = pthread_create(&m_threadId, &threadAttr, pFunc, pContext);
    
    pthread_attr_destroy(&threadAttr);
    return nStatus;
}

int MTJSocketThread::Init(){

    //此处需要判断是否在IOS\OSX下，在IOS\OSX下不支持无名信号量，故需要调用sem_open创建
#if (TARGET_PLATFORM == PLATFORM_IOS || TARGET_PLATFORM == PLATFORM_MAC)
    static int semIndex = 0;
    std::stringstream ss;
    ss << "socket-";
    semIndex++;
    std::string name;
    ss >> name;
    m_pSem = sem_open(name.c_str(), O_CREAT,0644,0);
    if (m_pSem == SEM_FAILED) {
        return ERR_AT_CREATE_SEM;
    }
#else
    m_pSem = new sem_t;
    if (sem_init(m_pSem, 0, 0) < 0) {
        return ERR_AT_CREATE_SEM;
    }
#endif
    if (Create(&DoRun, (void*)this) < 0) {
        return ERR_AT_CREATE_THREAD;
    }
    
    m_nStatus = IDLE;
    return m_nStatus;
}

void* MTJSocketThread::DoRun(void *pContext){

    MTJSocketThread* thread = (MTJSocketThread*)pContext;
    sem_wait(thread->m_pSem);
    if (RUNNING == thread->m_nStatus) {
        thread->Run();
    }
    
    thread->m_nStatus = QUITED;
    return (void*)(0);
}

int MTJSocketThread::Start(){

    if (m_nStatus == UNINITIALIZED) {
        Init();
        m_nStatus = RUNNING;
        sem_post(m_pSem);
    }
    
    return m_nStatus;
}

void MTJSocketThread::End(){

    if (m_pSem != NULL) {
        sem_post(m_pSem);
        //此处需要判断是否在IOS\OSX下，在IOS\OSX下不支持无名信号量，故需要调用sem_open创建
#if (TARGET_PLATFORM == PLATFORM_IOS || TARGET_PLATFORM == PLATFORM_MAC)
        sem_close(m_pSem);
#else
        sem_destroy(m_pSem);
        delete m_pSem;
#endif
        m_pSem = NULL;
    }
}