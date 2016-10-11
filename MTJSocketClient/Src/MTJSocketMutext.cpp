//
//  MTJSocketMutext.cpp
//  MTJSocketClient
//
//  Created by Reddog on 16/10/10.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#include "MTJSocketMutext.h"

MTJSocketMutext::MTJSocketMutext(int nShared,int nType){

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, nShared);
    pthread_mutexattr_settype(&attr, nType);
    pthread_mutex_init(&m_sMutext, &attr);
    pthread_mutexattr_destroy(&attr);
}

MTJSocketMutext::~MTJSocketMutext(){

    pthread_mutex_destroy(&m_sMutext);
}