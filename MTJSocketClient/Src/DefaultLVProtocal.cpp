//
//  DefaultLVProtocal.cpp
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#include "DefaultLVProtocal.h"
#include <stddef.h>
DefaultLVProtocal::DefaultLVProtocal():
m_pFrame(NULL)
{

    m_nStatus = 0;
}
DefaultLVProtocal::~DefaultLVProtocal(){

    delete m_pFrame;
}
MTJSocketBuffer* DefaultLVProtocal::TranslateFrame(MTJSocketBuffer* pBytes){

    while (pBytes->ReadableBytes() > 0) {
        switch (m_nStatus) {
            case 0:
                m_nH = pBytes->ReadChar();
                m_nStatus = 1;
                break;
            case 1:
                m_nL = pBytes->ReadChar();
                m_sLen = ((m_nH << 8) & 0x0000ff00) | (m_nL);
                m_pFrame = new MTJSocketBuffer(m_sLen +2);
                m_pFrame->WriteShort(m_sLen);
                m_nStatus = 2;
                break;
            case 2:
                m_pFrame->WriteBytes(pBytes);
                if (m_pFrame->WritableBytes() <= 0) {
                    m_nStatus = 0;
                    return m_pFrame;
                }
                break;
            default:
                break;
        }
    }
    
    return NULL;
}