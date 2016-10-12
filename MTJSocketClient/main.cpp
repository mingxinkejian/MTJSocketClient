//
//  main.cpp
//  MTJSocketClient
//
//  Created by Reddog on 16/10/10.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "MTJSocketPlatformConfig.h"
#include "MTJSocket.h"
#include "MTJSocketThreadPool.h"
#include "MTJSocketListener.h"
#include "DefaultListener.h"
#include "DefaultLVProtocal.h"
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#ifdef WIN32
#pragma comment(lib, "wsock32")
#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#endif

//int main(int argc, const char * argv[]) {
//    // insert code here...
//    std::cout << "Hello, World!\n" ;
//    std::cout << sizeof(float) << std::endl;
////    setlocale(LC_ALL,"zh_CN.UTF-8");
//    setlocale(LC_ALL, "Chinese-simplified");
//#ifdef WIN32
//    WSADATA wsaData;
//    WORD version = MAKEWORD(2, 0);
//    WSAStartup(version, &wsaData);
//#endif
//    //连接TCP服务器
//    MTJSocket* socket = new MTJSocket();
//    MTJSocketListener* sockListener = new DefaultListener();
//    //调用顺序，设定一个接受socket的回调
//    socket->SetProtocal(new DefaultLVProtocal());
//    socket->Open(sockListener,MTJSocket::SOCK_UDP);
//    socket->Connect("127.0.0.1",9501, 60);
//    sockListener->Join(NULL);
//    socket->Close();
//    MTJ_SAFE_DELETE(socket);
//    return 0;
//}
