//
//  MTJSocketThreadPool.h
//  MTJSocketClient
//
//  Created by Reddog on 16/10/11.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#ifndef __MTJSocketClient__MTJSocketThreadPool__
#define __MTJSocketClient__MTJSocketThreadPool__

#include <string.h>
#include "MTJSocketWorkThread.h"
#include "MTJSocketMutext.h"
/// 线程池
class MTJSocketThreadPool {
private:
    int m_nPoolSize;
    MTJSocketWorkThread** m_pPool;
    
public:
    MTJSocketThreadPool(int nPoolSize = 1);
    ~MTJSocketThreadPool();
    
    inline int GetPoolSize(){
    
        return m_nPoolSize;
    }
    
    void Offer(MTJSocketThread* pTask);
    /**
     *  @author mingtingjian, 16-10-11 18:10:46
     *
     *  停止线程池，调用之后不能再往线程池里放task，因为已经删除了线程池指针，会报错
     */
    void Shutdown();
};

#endif /* defined(__MTJSocketClient__MTJSocketThreadPool__) */
