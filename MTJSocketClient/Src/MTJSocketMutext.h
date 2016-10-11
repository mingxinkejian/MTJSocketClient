//
//  MTJSocketMutext.h
//  MTJSocketClient
//
//  Created by Reddog on 16/10/10.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#ifndef __MTJSocketClient__MTJSocketMutext__
#define __MTJSocketClient__MTJSocketMutext__

#include <pthread.h>

class MTJSocketMutext {
private:
    pthread_mutex_t m_sMutext;
    
public:
    MTJSocketMutext(int sh = PTHREAD_PROCESS_PRIVATE,int type = PTHREAD_MUTEX_NORMAL);
    ~MTJSocketMutext();
private:
    MTJSocketMutext(const MTJSocketMutext& mutext){
    }
    
    MTJSocketMutext& operator =(const MTJSocketMutext& mutext){
        return *this;
    }
    
public:
    inline int Lock(){
        return pthread_mutex_lock(&m_sMutext);
    }
    inline int Unlock(){
        return pthread_mutex_unlock(&m_sMutext);
    }
    inline int TryLock(){
        return pthread_mutex_trylock(&m_sMutext);
    }
};

#endif /* defined(__MTJSocketClient__MTJSocketMutext__) */
