//
//  MTJSocketBuffer.cpp
//  MTJSocketClient
//
//  Created by Reddog on 16/10/10.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#include "MTJSocketBuffer.h"
#include "MTJSocketPlatformConfig.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string.h>


MTJSocketBuffer::MTJSocketBuffer(int nLen){

    m_nLen = nLen;
    m_pData = (char*) malloc(nLen);
    m_nReaderIndex = 0;
    m_nWriterIndex = 0;
    m_nMarkReader = 0;
    m_nMarkWriter = 0;
}

MTJSocketBuffer::~MTJSocketBuffer(){

    MTJ_SAFE_FREE(m_pData);
}

int MTJSocketBuffer::Capacity(){

    return m_nLen;
}

MTJSocketBuffer* MTJSocketBuffer::Capacity(int nNewCapacity){

    if (nNewCapacity > m_nLen) {
        char* old = m_pData;
        m_pData = (char*) malloc(nNewCapacity);
        memcpy(m_pData, old, m_nLen);
        MTJ_SAFE_FREE(old);
        m_nLen = nNewCapacity;
    }
    
    return this;
}

const MTJSocketBuffer* MTJSocketBuffer::Clear(){

    m_nReaderIndex = 0;
    m_nWriterIndex = 0;
    m_nMarkReader = 0;
    m_nMarkWriter = 0;
    
    return this;
}

const MTJSocketBuffer* MTJSocketBuffer::Copy(){

    MTJSocketBuffer* copy = new MTJSocketBuffer(m_nLen);
    memcpy(copy->m_pData, m_pData, m_nLen);
    copy->m_nReaderIndex = m_nReaderIndex;
    copy->m_nWriterIndex = m_nWriterIndex;
    copy->m_nMarkReader = m_nMarkReader;
    copy->m_nMarkWriter = m_nMarkWriter;
    
    return copy;
}

bool MTJSocketBuffer::GetBoolean(int nIndex){

    if (nIndex < m_nLen) {
        return *(m_pData + nIndex);
    }
    
    return false;
}

char MTJSocketBuffer::GetChar(int nIndex){

    if (nIndex < m_nLen) {
        return *(m_pData + nIndex);
    }
    
    return '\0';
}

float MTJSocketBuffer::GetFloat(int nIndex){

    if (nIndex + 3 < m_nLen) {
        int ret = ((int) m_pData[nIndex]) << 24;
        ret |= ((int) m_pData[nIndex +1]) << 16;
        ret |= ((int) m_pData[nIndex +2]) << 8;
        ret |= ((int) m_pData[nIndex +3]);
        
        union{
            float f;
            int i;
        } u;
        u.i = ret;
        return u.f;
    }
    
    return 0.0f;
}

int MTJSocketBuffer::GetInt(int nIndex){
    if (nIndex + 3 < m_nLen) {
        int ret = ((int) m_pData[nIndex]) << 24;
        ret |= ((int) m_pData[nIndex +1]) << 16;
        ret |= ((int) m_pData[nIndex +2]) << 8;
        ret |= ((int) m_pData[nIndex +3]);
        
        return ret;
    }
    
    return 0;
}

long long MTJSocketBuffer::GetLong(int nIndex){

    if (nIndex + 7  < m_nLen) {
        long long ret = ((long long) m_pData[nIndex]) << 56;
        ret |= ((long long) m_pData[nIndex +1]) << 48;
        ret |= ((long long) m_pData[nIndex +2]) << 40;
        ret |= ((long long) m_pData[nIndex +3]) << 32;
        ret |= ((long long) m_pData[nIndex +4]) << 24;
        ret |= ((long long) m_pData[nIndex +5]) << 16;
        ret |= ((long long) m_pData[nIndex +6]) << 8;
        ret |= ((long) m_pData[nIndex +7]);
        return ret;
    }
    
    return 0;
}

short MTJSocketBuffer::GetShort(int nIndex){

    if (nIndex + 1 < m_nLen) {
        short r1 = m_pData[nIndex] << 8;
        short r2 = m_pData[nIndex + 1];
        short ret = r1 | r2;
        return ret;
    }
    
    return 0;
}

MTJSocketBuffer* MTJSocketBuffer::MarkReaderIndex(){

    m_nMarkReader = m_nReaderIndex;
    
    return this;
}

MTJSocketBuffer* MTJSocketBuffer::MarkWriterIndex(){

    m_nMarkWriter = m_nWriterIndex;
    return this;
}

int MTJSocketBuffer::MaxWritableBytes(){

    return m_nLen - m_nWriterIndex;
}

bool MTJSocketBuffer::ReadBool(){

    if (m_nReaderIndex < m_nWriterIndex) {
        bool ret = (bool)(m_pData[m_nReaderIndex++]);
        return ret;
    }
    
    return false;
}

char MTJSocketBuffer::ReadChar(){

    if (m_nReaderIndex < m_nWriterIndex) {
        char ret = m_pData[m_nReaderIndex++];
        return ret;
    }
    
    return '\0';
}

float MTJSocketBuffer::ReadFloat(){

    if (m_nReaderIndex < m_nWriterIndex) {
        int ret = ((m_pData[m_nReaderIndex++]) << 24) & 0xff000000;
        ret |= ((m_pData[m_nReaderIndex++]) << 16) & 0x00ff0000;
        ret |= ((m_pData[m_nReaderIndex++]) << 8) & 0x0000ff00;
        ret |= ((m_pData[m_nReaderIndex++])) & 0x000000ff;
        union{
            float f;
            int i;
        } u;
        u.i = ret;
        return u.f;
    }
    
    return 0.0f;
}

int MTJSocketBuffer::ReadInt(){

    if (m_nReaderIndex + 3 < m_nWriterIndex) {
        int ret = ((m_pData[m_nReaderIndex++]) << 24) & 0xff000000;
        ret |= ((m_pData[m_nReaderIndex++]) << 16) & 0x00ff0000;
        ret |= ((m_pData[m_nReaderIndex++]) << 8) & 0x0000ff00;
        ret |= ((m_pData[m_nReaderIndex++])) & 0x000000ff;
        return ret;
    }
    
    return 0;
}

long long MTJSocketBuffer::ReadLong(){

    if (m_nReaderIndex + 7 < m_nWriterIndex) {
        long long ret = (((long long)m_pData[m_nReaderIndex++]) << 56) & 0xff00000000000000;
        ret |= (((long long)m_pData[m_nReaderIndex++]) << 48) & 0x00ff000000000000;
        ret |= (((long long)m_pData[m_nReaderIndex++]) << 40) & 0x0000ff0000000000;
        ret |= (((long long)m_pData[m_nReaderIndex++]) << 32) & 0x000000ff00000000;
        ret |= ((m_pData[m_nReaderIndex++]) << 24) & 0xff000000;
        ret |= ((m_pData[m_nReaderIndex++]) << 16) & 0x00ff0000;
        ret |= ((m_pData[m_nReaderIndex++]) << 8) & 0x0000ff00;
        ret |= ((m_pData[m_nReaderIndex++])) & 0x000000ff;
        return ret;
    }
    
    return 0;
}

short MTJSocketBuffer::ReadShort(){

    if (m_nReaderIndex + 1 < m_nWriterIndex) {
        int h = m_pData[m_nReaderIndex++];
        int l = m_pData[m_nReaderIndex++] & 0x000000ff;
        int len = ((h << 8) & 0x0000ff00) | (l);
        return len;
    }
    
    return 0;
}

int MTJSocketBuffer::ReadableBytes(){

    return m_nWriterIndex - m_nReaderIndex;
}

int MTJSocketBuffer::ReaderIndex(){

    return m_nReaderIndex;
}

MTJSocketBuffer* MTJSocketBuffer::ReaderIndex(int nReaderIndex){

    if (nReaderIndex <= m_nWriterIndex) {
        m_nReaderIndex = nReaderIndex;
    }
    
    return this;
}

MTJSocketBuffer* MTJSocketBuffer::ResetReaderIndex(){

    if (m_nMarkReader <= m_nWriterIndex) {
        m_nReaderIndex = m_nMarkReader;
    }
    
    return this;
}

MTJSocketBuffer* MTJSocketBuffer::ResetWriterIndex(){

    if (m_nMarkWriter >= m_nReaderIndex) {
        m_nWriterIndex = m_nMarkWriter;
    }
    
    return this;
}

MTJSocketBuffer* MTJSocketBuffer::SetBoolean(int nIndex, bool bValue){

    if (nIndex < m_nLen) {
        m_pData[nIndex] = (char) bValue;
    }
    
    return this;
}

MTJSocketBuffer* MTJSocketBuffer::SetChar(int nIndex, char cValue){

    if (nIndex < m_nLen) {
        m_pData[nIndex] = cValue;
    }
    
    return this;
}

MTJSocketBuffer* MTJSocketBuffer::SetBytes(int nIndex, char *pSrc, int nLen){

    if (nIndex + nLen < m_nLen) {
        memcpy(m_pData + nIndex, pSrc, nLen);
    }
    
    return this;
}

MTJSocketBuffer* MTJSocketBuffer::SetFloat(int nIndex, float fValue){

    if (nIndex + 4 <= m_nLen) {
        union{
            float f;
            int i;
        } u;
        u.f = fValue;
        m_pData[nIndex] = (u.i >> 24) & 0xff;
        m_pData[nIndex + 1] = (u.i >> 16) & 0xff;
        m_pData[nIndex + 2] = (u.i >> 8) & 0xff;
        m_pData[nIndex + 3] = (u.i) & 0xff;
    }
    
    return this;
}

MTJSocketBuffer* MTJSocketBuffer::SetIndex(int nReaderIndex, int nWriterIndex){

    if (nReaderIndex >= 0 && nReaderIndex <= nWriterIndex && nWriterIndex <= m_nLen) {
        m_nReaderIndex = nReaderIndex;
        m_nWriterIndex = nWriterIndex;
    }
    
    return this;
}

MTJSocketBuffer* MTJSocketBuffer::SetInt(int nIndex, int nValue){

    if (nIndex + 4 < m_nLen) {
        m_pData[nIndex++] = (nValue >> 24) & 0xff;
        m_pData[nIndex++] = (nValue >> 16) & 0xff;
        m_pData[nIndex++] = (nValue >> 8) & 0xff;
        m_pData[nIndex++] = (nValue) & 0xff;
    }
    
    return this;
}

MTJSocketBuffer* MTJSocketBuffer::SetLong(int nIndex, long long llValue){

    if (nIndex + 8 < m_nLen) {
        m_pData[nIndex++] = (llValue >> 56) & 0xff;
        m_pData[nIndex++] = (llValue >> 48) & 0xff;
        m_pData[nIndex++] = (llValue >> 40) & 0xff;
        m_pData[nIndex++] = (llValue >> 32) & 0xff;
        m_pData[nIndex++] = (llValue >> 24) & 0xff;
        m_pData[nIndex++] = (llValue >> 16) & 0xff;
        m_pData[nIndex++] = (llValue >> 8) & 0xff;
        m_pData[nIndex++] = (llValue) & 0xff;
    }
    
    return this;
}

MTJSocketBuffer* MTJSocketBuffer::SetShort(int nIndex, short sValue){

    if (nIndex + 2 < m_nLen) {
        m_pData[nIndex++] = (sValue >> 8) & 0xff;
        m_pData[nIndex++] = (sValue) & 0xff;
    }
    
    return this;
}

MTJSocketBuffer* MTJSocketBuffer::SkipBytes(int nLenght){

    if (m_nReaderIndex + nLenght <= m_nWriterIndex) {
        m_nReaderIndex += nLenght;
    }
    
    return this;
}

int MTJSocketBuffer::WritableBytes(){

    return m_nLen - m_nWriterIndex;
}

MTJSocketBuffer* MTJSocketBuffer::WriteBoolean(bool bValue){

    Capacity(m_nWriterIndex + 1);
    m_pData[m_nWriterIndex++] = (char) bValue;
    
    return this;
}

MTJSocketBuffer* MTJSocketBuffer::WriteChar(char cValue){

    Capacity(m_nWriterIndex + 1);
    m_pData[m_nWriterIndex++] = cValue;
    
    return this;
}

MTJSocketBuffer* MTJSocketBuffer::WriteFloat(float fValue){
    Capacity(m_nWriterIndex + 4);
    union
    {
        float f;
        int i;
    } u;
    u.f = fValue;
    
    m_pData[m_nWriterIndex++] = (u.i >> 24) & 0xff;
    m_pData[m_nWriterIndex++] = (u.i >> 16) & 0xff;
    m_pData[m_nWriterIndex++] = (u.i >> 8) & 0xff;
    m_pData[m_nWriterIndex++] = u.i & 0xff;
    
    return this;
}

MTJSocketBuffer* MTJSocketBuffer::WriteInt(int nValue){

    Capacity(m_nWriterIndex + 4);
    m_pData[m_nWriterIndex++] = (nValue >> 24) & 0xff;
    m_pData[m_nWriterIndex++] = (nValue >> 16) & 0xff;
    m_pData[m_nWriterIndex++] = (nValue >> 8) & 0xff;
    m_pData[m_nWriterIndex++] = (nValue) & 0xff;
    
    return this;
}

MTJSocketBuffer* MTJSocketBuffer::WriteLong(long long llValue){

    Capacity(m_nWriterIndex + 4);
    m_pData[m_nWriterIndex++] = (llValue >> 56) & 0xff;
    m_pData[m_nWriterIndex++] = (llValue >> 48) & 0xff;
    m_pData[m_nWriterIndex++] = (llValue >> 40) & 0xff;
    m_pData[m_nWriterIndex++] = (llValue >> 32) & 0xff;
    m_pData[m_nWriterIndex++] = (llValue >> 24) & 0xff;
    m_pData[m_nWriterIndex++] = (llValue >> 16) & 0xff;
    m_pData[m_nWriterIndex++] = (llValue >> 8) & 0xff;
    m_pData[m_nWriterIndex++] = (llValue) & 0xff;
    
    return this;
}

MTJSocketBuffer* MTJSocketBuffer::WriteShort(short sValue){

    Capacity(m_nWriterIndex + 2);
    m_pData[m_nWriterIndex++] = (sValue >> 8) & 0xff;
    m_pData[m_nWriterIndex++] = (sValue) & 0xff;
    
    return this;
}

MTJSocketBuffer* MTJSocketBuffer::WriteBytes(MTJSocketBuffer *bytes){

    int remain = m_nLen - m_nWriterIndex;
    int sum = bytes->m_nWriterIndex - bytes->m_nReaderIndex;
    int val = remain < sum ? remain : sum;
    if (val > 0) {
        memcpy(m_pData + m_nWriterIndex, bytes->m_pData + bytes->m_nReaderIndex, val);
        m_nWriterIndex += val;
        bytes->m_nReaderIndex += val;
    }
    
    return this;
}

char * MTJSocketBuffer::ReadUTF8(){

    short len = ReadShort(); //字节数
    char* charBuff = new char[len + 1];
    memcpy(charBuff, m_pData + m_nReaderIndex, len);
    charBuff[len] = '\0';
    m_nReaderIndex += len;
    return charBuff;
}

MTJSocketBuffer* MTJSocketBuffer::WriteUTF8(char *value){

    int len = (int)strlen(value);
    Capacity(m_nWriterIndex + len +2);
    WriteShort((short)len);
    memcpy(m_pData + m_nWriterIndex, value, len);
    m_nWriterIndex += len;
    return this;
}

int MTJSocketBuffer::WriterIndex(){

    return m_nWriterIndex;
}

MTJSocketBuffer* MTJSocketBuffer::WriterIndex(int nWriterIndex){

    if (nWriterIndex >= m_nReaderIndex && nWriterIndex <= m_nLen) {
        m_nWriterIndex = nWriterIndex;
    }
    
    return this;
}

char * MTJSocketBuffer::GetData(){

    return m_pData;
}