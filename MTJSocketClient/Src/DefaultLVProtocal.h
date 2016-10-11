//
//  DefaultLVProtocal.h
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#ifndef __MTJSocketClient__DefaultLVProtocal__
#define __MTJSocketClient__DefaultLVProtocal__

#include "MTJSocketProtocal.h"
#include "MTJSocketBuffer.h"
/// 默认分帧协议，可以自动将数据处理为一个完整的数据帧
class DefaultLVProtocal : public MTJSocketProtocal {
private:
    int m_nStatus;
    int m_nH;
    int m_nL;
    short m_sLen;
    MTJSocketBuffer* m_pFrame;
    
public:
    DefaultLVProtocal();
    virtual ~DefaultLVProtocal();
    MTJSocketBuffer* TranslateFrame(MTJSocketBuffer* pBytes);
};

#endif /* defined(__MTJSocketClient__DefaultLVProtocal__) */
