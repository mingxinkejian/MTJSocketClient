//
//  MTJSocketBits.cpp
//  MTJSocketClient
//
//  Created by Reddog on 16/10/10.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//
#include <stdlib.h>
#include <string.h>
#include "MTJSocketBits.h"
#include "MTJSocketPlatformConfig.h"

MTJSocketBits::MTJSocketBits(int nSize){

    int bs = (nSize / 8) + 1;
    m_nSize = bs * 8;
    m_pBits = (char*) malloc(bs);
    memset(m_pBits, 0, bs);
    
}

MTJSocketBits::~MTJSocketBits(){

    MTJ_SAFE_FREE(m_pBits);
}

int MTJSocketBits::getBit(int nIndex){

    if (nIndex >= 0 && nIndex < m_nSize) {
        int i = nIndex / 8;
        int j = nIndex % 8;
        struct MTJSocketByte* byte = (struct MTJSocketByte*) (m_pBits + i);
        int r = 0;
        switch (j) {
            case 0:
                r = byte->bit0;
                break;
            case 1:
                r = byte->bit1;
                break;
            case 2:
                r = byte->bit2;
                break;
            case 3:
                r = byte->bit3;
                break;
            case 4:
                r = byte->bit4;
                break;
            case 5:
                r = byte->bit5;
                break;
            case 6:
                r = byte->bit6;
                break;
            case 7:
                r = byte->bit7;
                break;
        }
        r = 0x00000001 & r;
        return r;
    }
    
    return 0;
}

void MTJSocketBits::setBit(int nIndex, int nValue){

    if (nIndex > m_nSize) {
        int bs = ((nIndex + 1) / 8) + 1;
        char* temp = (char*) malloc(bs);
        memset(temp, 0, bs);
        memcpy(temp, m_pBits, m_nSize / 8);
        MTJ_SAFE_FREE(m_pBits);
        m_pBits = temp;
        m_nSize = bs * 8;
    }
    
    if (nIndex > 0) {
        int i = nIndex / 8;
        int j = nIndex % 8;
        struct MTJSocketByte* byte = (struct MTJSocketByte*) (m_pBits + i);
        int r = 0;
        switch (j) {
            case 0:
                r = byte->bit0;
                break;
            case 1:
                r = byte->bit1;
                break;
            case 2:
                r = byte->bit2;
                break;
            case 3:
                r = byte->bit3;
                break;
            case 4:
                r = byte->bit4;
                break;
            case 5:
                r = byte->bit5;
                break;
            case 6:
                r = byte->bit6;
                break;
            case 7:
                r = byte->bit7;
                break;
        }
    }
    
}