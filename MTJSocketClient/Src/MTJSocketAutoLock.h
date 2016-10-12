//
//  MTJAutoLock.h
//  MTJSocketClient
//
//  Created by Reddog on 16/10/10.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#ifndef MTJSocketClient_MTJAutoLock_h
#define MTJSocketClient_MTJAutoLock_h

#include "MTJSocketMutext.h"

class MTJSocketAutoLock {
private:
    MTJSocketMutext* m_pLock;
    
public:
    MTJSocketAutoLock(MTJSocketMutext *pMutext){
        m_pLock = pMutext;
        m_pLock->Lock();
    }
    
    ~MTJSocketAutoLock(){
        m_pLock->Unlock();
    }
};

#endif
