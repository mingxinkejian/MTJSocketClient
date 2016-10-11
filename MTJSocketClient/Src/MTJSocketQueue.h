//
//  MTJSocketQueue.h
//  MTJSocketClient
//
//  Created by Reddog on 16/10/10.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#ifndef MTJSocketClient_MTJSocketQueue_h
#define MTJSocketClient_MTJSocketQueue_h

template <class T>
class MTJSocketQueue {
    
public:
    MTJSocketQueue(){
    }
    
    virtual ~MTJSocketQueue(){
    }
    
    virtual bool Offer(T* pElement) = 0;
    virtual T* Poll() = 0;
    virtual T* Peek() = 0;
    virtual int Size() = 0;
};

#endif
