//
//  MTJSocketDataFrame.cpp
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#include "MTJSocketDataFrame.h"

MTJSocketDataFrame::MTJSocketDataFrame(int nLen):
m_pOriginData(NULL),
m_bIsEnd(false)
{
    Init(nLen);
}

MTJSocketDataFrame::~MTJSocketDataFrame(){

}

void MTJSocketDataFrame::Init(int nLen){

    m_pOriginData = new MTJSocketBuffer(nLen);
    m_pOriginData->WriteShort(0);
}

MTJSocketBuffer* MTJSocketDataFrame::GetData(){

    return m_pOriginData;
}

MTJSocketDataFrame* MTJSocketDataFrame::PutChar(char cValue){

    if (!m_bIsEnd) {
        m_pOriginData->WriteChar(cValue);
    }
    
    return this;
}

MTJSocketDataFrame* MTJSocketDataFrame::PutBytes(MTJSocketBuffer *pBytes){
    
    if (!m_bIsEnd) {
        m_pOriginData->WriteBytes(pBytes);
    }
    
    return this;
}

MTJSocketDataFrame* MTJSocketDataFrame::PutFloat(float fValue){
    
    if (!m_bIsEnd) {
        m_pOriginData->WriteFloat(fValue);
    }
    
    return this;
}

MTJSocketDataFrame* MTJSocketDataFrame::PutInt(int nValue){
    
    if (!m_bIsEnd) {
        m_pOriginData->WriteInt(nValue);
    }
    
    return this;
}

MTJSocketDataFrame* MTJSocketDataFrame::PutLong(long long llValue){
    
    if (!m_bIsEnd) {
        m_pOriginData->WriteLong(llValue);
    }
    
    return this;
}

MTJSocketDataFrame* MTJSocketDataFrame::PutShort(short sValue){
    
    if (!m_bIsEnd) {
        m_pOriginData->WriteShort(sValue);
    }
    
    return this;
}

MTJSocketDataFrame* MTJSocketDataFrame::PutString(char *pValue){
    
    if (!m_bIsEnd) {
        m_pOriginData->WriteUTF8(pValue);
    }
    
    return this;
}

MTJSocketDataFrame* MTJSocketDataFrame::Duplicate(){

    MTJSocketDataFrame* frame = new MTJSocketDataFrame(m_pOriginData->Capacity());
    m_pOriginData->MarkReaderIndex();
    frame->PutBytes(m_pOriginData);
    m_pOriginData->ResetReaderIndex();
    if (m_bIsEnd) {
        frame->End();
    }
    
    return frame;
}

void MTJSocketDataFrame::End(){

    MTJSocketBuffer* buffer = m_pOriginData;
    int reader = buffer->ReaderIndex();
    int writer = buffer->WriterIndex();
    const int len = writer - reader - 2;
    buffer->WriterIndex(reader);
    buffer->WriteShort(len);
    buffer->WriterIndex(writer);
    m_bIsEnd = true;
}

bool MTJSocketDataFrame::IsEnd(){

    return m_bIsEnd;
}

void MTJSocketDataFrame::SetEnd(bool bIsEnd){

    if (bIsEnd) {
        End();
    }else{
        m_bIsEnd = bIsEnd;
    }
}