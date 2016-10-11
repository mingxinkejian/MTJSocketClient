//
//  MTJSocketBuffer.h
//  MTJSocketClient
//
//  Created by Reddog on 16/10/10.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#ifndef __MTJSocketClient__MTJSocketBuffer__
#define __MTJSocketClient__MTJSocketBuffer__

#include <iostream>

class MTJSocketBuffer {
private:
    char* m_pData; //数据
    int m_nLen; //长度，可扩展长度
    int m_nReaderIndex; //读指针
    int m_nWriterIndex; //写指针
    int m_nMarkReader; //读指针标记
    int m_nMarkWriter; //写指针标记
public:
    MTJSocketBuffer(int nLen);
    virtual ~MTJSocketBuffer();
    int Capacity();
    /**
     *  @author mingtingjian, 16-10-10 18:10:33
     *
     *  扩展容量
     *
     *  @param nNewCapacity
     *
     *  @return MTJSocketBuffer
     */
    MTJSocketBuffer* Capacity(int nNewCapacity);
    int ReaderIndex();
    MTJSocketBuffer* ReaderIndex(int nReaderIndex);
    int WriterIndex();
    MTJSocketBuffer* WriterIndex(int nWriterIndex);
    MTJSocketBuffer* SetIndex(int nReaderIndex,int nWriterIndex);
    int ReadableBytes();
    int WritableBytes();
    int MaxWritableBytes();
    const MTJSocketBuffer* Clear();
    MTJSocketBuffer* MarkReaderIndex();
    MTJSocketBuffer* ResetReaderIndex();
    MTJSocketBuffer* MarkWriterIndex();
    MTJSocketBuffer* ResetWriterIndex();
    bool GetBoolean(int nIndex);
    char GetChar(int nIndex);
    short GetShort(int nIndex);
    int GetInt(int nIndex);
    long long GetLong(int nIndex);
    float GetFloat(int nIndex);
    
    MTJSocketBuffer* SetBoolean(int nIndex,bool bValue);
    MTJSocketBuffer* SetChar(int nIndex,char cValue);
    MTJSocketBuffer* SetShort(int nIndex,short sValue);
    MTJSocketBuffer* SetInt(int nIndex,int nValue);
    MTJSocketBuffer* SetLong(int nIndex,long long llValue);
    MTJSocketBuffer* SetFloat(int nIndex,float fValue);
    MTJSocketBuffer* SetBytes(int nIndex,char* pSrc,int nLen);
    
    bool ReadBool();
    char ReadChar();
    short ReadShort();
    int ReadInt();
    long long ReadLong();
    float ReadFloat();
    /**
     *  @author mingtingjian, 16-10-11 11:10:03
     *
     *  用于读取字符串，注意释放内存，内部使用new data[]
     *
     *  @return char*
     */
    char* ReadUTF8();
    
    MTJSocketBuffer* SkipBytes(int nLenght);
    MTJSocketBuffer* WriteBoolean(bool bValue);
    MTJSocketBuffer* WriteChar(char cValue);
    MTJSocketBuffer* WriteShort(short sValue);
    MTJSocketBuffer* WriteInt(int nValue);
    MTJSocketBuffer* WriteLong(long long llValue);
    MTJSocketBuffer* WriteFloat(float fValue);
    MTJSocketBuffer* WriteBytes(MTJSocketBuffer* bytes);
    /**
     *  @author mingtingjian, 16-10-11 11:10:58
     *
     *  长度为2个字节 short型
     *
     *  @param value
     *
     *  @return
     */
    MTJSocketBuffer* WriteUTF8(char* value);
    const MTJSocketBuffer* Copy();
    char* GetData();
    
};

#endif /* defined(__MTJSocketClient__MTJSocketBuffer__) */
