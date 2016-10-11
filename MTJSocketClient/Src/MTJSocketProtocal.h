//
//  MTJSocketProtocal.h
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#ifndef MTJSocketClient_MTJSocketProtocal_h
#define MTJSocketClient_MTJSocketProtocal_h

#include "MTJSocketBuffer.h"

class MTJSocketProtocal {
    
    
public:
    MTJSocketProtocal(){
    
    }
    
    virtual ~MTJSocketProtocal(){
    
    }
    
    virtual MTJSocketBuffer* TranslateFrame(MTJSocketBuffer* pBytes) = 0;
};

#endif
