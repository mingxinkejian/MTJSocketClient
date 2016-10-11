//
//  MTJSocketDataFrame.h
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#ifndef __MTJSocketClient__MTJSocketDataFrame__
#define __MTJSocketClient__MTJSocketDataFrame__

#include "MTJSocketBuffer.h"
/// 数据帧，用来封装到达的数据包
class MTJSocketDataFrame {
private:
    MTJSocketBuffer* m_pOriginData; //原始数据
    bool m_bIsEnd; //是否封包
public:
    MTJSocketDataFrame(int nLen);
    virtual ~MTJSocketDataFrame();
    
    MTJSocketBuffer* GetData();
    MTJSocketDataFrame* PutChar(char cValue);
    MTJSocketDataFrame* PutBytes(MTJSocketBuffer* pBytes);
    MTJSocketDataFrame* PutShort(short sValue);
    MTJSocketDataFrame* PutInt(int nValue);
    MTJSocketDataFrame* PutLong(long long llValue);
    MTJSocketDataFrame* PutFloat(float fValue);
    MTJSocketDataFrame* PutString(char* pValue);
    
    void End();
    bool IsEnd();
    void SetEnd(bool bIsEnd);
    /**
     *  @author mingtingjian, 16-10-11 16:10:44
     *
     *  注意释放内存
     *
     *  @return MTJSocketDataFrame
     */
    MTJSocketDataFrame* Duplicate();
private:
    void Init(int nLen);
};

#endif /* defined(__MTJSocketClient__MTJSocketDataFrame__) */
