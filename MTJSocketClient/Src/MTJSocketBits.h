//
//  MTJSocketBits.h
//  MTJSocketClient
//
//  Created by Reddog on 16/10/10.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#ifndef __MTJSocketClient__MTJSocketBits__
#define __MTJSocketClient__MTJSocketBits__
/**
 *  @author mingtingjian, 16-10-10 17:10:30
 *
 *  int a0 : 1; //表示占用一个bit位 一个字节共8位
 */
struct MTJSocketByte {
    int bit0 : 1;
    int bit1 : 1;
    int bit2 : 1;
    int bit3 : 1;
    int bit4 : 1;
    int bit5 : 1;
    int bit6 : 1;
    int bit7 : 1;
};

class MTJSocketBits {
private:
    int m_nSize;
    char* m_pBits;
public:
    MTJSocketBits(int nSize);
    virtual ~MTJSocketBits();
    int getBit(int nIndex);
    void setBit(int nIndex,int nValue);
    

};

#endif /* defined(__MTJSocketClient__MTJSocketBits__) */
