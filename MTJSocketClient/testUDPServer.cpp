//
//  main.cpp
//  MTJSocketClient
//
//  Created by Reddog on 16/10/10.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define MAX_MSG_SIZE 1024


int main(int argc,char* argv[]){
    int skfd;
    socklen_t addrlen;
    int ret;
    struct sockaddr_in addr;
    struct sockaddr_in cltaddr;
    char *buf = (char*)malloc(MAX_MSG_SIZE);
    char *sndbuf = (char*)malloc(MAX_MSG_SIZE);
    
    //创建数据报式套接字skfd
    if(0 > (skfd = socket(AF_INET,SOCK_DGRAM,0))){
        perror("Create Error");
        exit(1);
    }
    
    bzero(&addr,sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    addr.sin_port=htons(9501);
    
    //将socket文件描述符skfd和本地端口和地址绑定起来
    if(0 > (bind(skfd,(struct sockaddr*)&addr,sizeof(struct sockaddr_in)))){
        perror("Bind Error");
        exit(1);
    }
    
    //开始收发数据
    while(true){
        ret = (int)recvfrom(skfd,buf,MAX_MSG_SIZE,0,(struct sockaddr*) &cltaddr,&addrlen);
        if(ret < 0){
            printf("recv data from %s:%d error!",inet_ntoa(cltaddr.sin_addr),ntohs(cltaddr.sin_port));
        }else if(ret == 0){
            perror("client has been closing socket!");
        }else{
            printf("From %s:%d,%s",inet_ntoa(cltaddr.sin_addr),ntohs(cltaddr.sin_port),buf);
            memset(sndbuf,0,MAX_MSG_SIZE);
            switch(buf[0]){
                case 'a':
                    strcpy(sndbuf,"After u ,lady...");
                    break;
                case 'b':
                    strcpy(sndbuf,"Before u ,sir...");
                    break;
                case 'c':
                    strcpy(sndbuf,"Can u?");
                    break;
                default:
                    strcpy(sndbuf,"I dont't know what u want!");
            }
            sendto(skfd,sndbuf,strlen(sndbuf),0,(struct sockaddr*)&cltaddr,addrlen);
        }
        memset(buf,0,MAX_MSG_SIZE);
    }
    return 0;
}


//#include <stdlib.h>
//#include <stdio.h>
//#include <errno.h>
//#include <string.h>
//#include <unistd.h>
//#include <netdb.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <sys/types.h>
//#include <arpa/inet.h>
//#define MAX_MSG_SIZE 1024
//
//int main(int argc,char** argv){
//    int skfd,ret,len;
//    struct sockaddr_in srvaddr;
//    char buf[MAX_MSG_SIZE]={0};
//    char sndbuf[MAX_MSG_SIZE]={0};
//    struct in_addr addr;
//    
//    //创建数据报式套接字skfd
//    if(0>(skfd=socket(AF_INET,SOCK_DGRAM,0))){
//        perror("Create Error");
//        exit(1);
//    }
//    
//    if(0 == inet_aton(argv[1],&addr)){
//        perror("server addr invalid!");
//        exit(1);
//    }
//    
//    bzero(&srvaddr,sizeof(struct sockaddr_in));
//    srvaddr.sin_family = AF_INET;
//    srvaddr.sin_addr=addr;
//    srvaddr.sin_port=htons(atoi(argv[2]));
//    
//    //我们的客户端只接收从服务器地址是srvaddr的主机发来的数据
//    if(0>(connect(skfd,(struct sockaddr*)&srvaddr,sizeof(struct sockaddr_in)))){
//        perror("Connect Error");
//        exit(1);
//    }
//    
//    //开始收发数据
//    while(1){
//        memset(sndbuf,0,MAX_MSG_SIZE);
//        len=read(0,sndbuf,MAX_MSG_SIZE);
//        ret=sendto(skfd,sndbuf,strlen(sndbuf),0,(struct sockaddr*)&srvaddr,sizeof(struct sockaddr));
//        if(ret == len){
//            memset(buf,0,MAX_MSG_SIZE);
//            //我们已经知道服务器地址信息了，所以最后两个参数为NULL
//            ret=recvfrom(skfd,buf,MAX_MSG_SIZE,0,NULL,NULL);
//            
//            if(ret < 0){
//                perror("read error from server!");
//            }else if(ret == 0){
//                perror("server has been closing socket!");
//            }else{
//                buf[ret]='\0';
//                printf("From Server:%s\n",buf);
//            }
//        }
//    }
//    return 0;
//}