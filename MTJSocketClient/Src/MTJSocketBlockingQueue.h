//
//  MTJSocketBlockingQueue.h
//  MTJSocketClient
//
//  Created by Reddog on 16/10/10.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#ifndef MTJSocketClient_MTJSocketBlockingQueue_h
#define MTJSocketClient_MTJSocketBlockingQueue_h

#include "MTJSocketMutext.h"
#include <stdlib.h>
#include "MTJSocketAutoLock.h"
#include "MTJSocketLinkedQueue.h"

template <class T>
class MTJSocketBlockingQueue : public MTJSocketLinkedQueue<T> {
private:
    MTJSocketMutext* m_pLock;
public:
    MTJSocketBlockingQueue(){
        m_pLock = new MTJSocketMutext();
    }
    
    virtual ~MTJSocketBlockingQueue(){
        delete m_pLock;
    }
    
    bool Offer(T* pElement){
        MTJSocketAutoLock lock(m_pLock);
        return MTJSocketLinkedQueue<T>::Offer(pElement);
    }
    
    T* Peek(){
        MTJSocketAutoLock lock(m_pLock);
        return MTJSocketLinkedQueue<T>::Peek();
    }
    
    T* Poll(){
        MTJSocketAutoLock lock(m_pLock);
        return MTJSocketLinkedQueue<T>::Poll();
    }
    
    int Size(){
        MTJSocketAutoLock lock(m_pLock);
        return m_nSize;
    }
};

#endif
