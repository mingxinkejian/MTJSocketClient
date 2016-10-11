//
//  ThreadHelper.h
//  starProfessor
//
//  Created by Reddog on 14-5-5.
//
//

#ifndef __starProfessor__ThreadHelper__
#define __starProfessor__ThreadHelper__

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
void ThreadSleep(unsigned sec);
class Thread {
protected:
    std::string name;
    pthread_t mythread;
    pthread_mutex_t mymutex;
    pthread_cond_t mycond;
protected:
    virtual void* run() = 0;
public:
#define LOCK_BEGIN  pthread_mutex_lock(&mymutex)
#define LOCK_END    pthread_mutex_unlock(&mymutex)
#define WAIT        pthread_cond_wait(&mycond, &mymutex)
#define NOTIFY_ALL  pthread_cond_broadcast(&mycond);
    bool m_ThreadIsFinished;
    
    Thread() {
        pthread_mutex_init(&mymutex, NULL);
        pthread_cond_init(&mycond, NULL);
        char msg[50];
        sprintf(msg, "%ld", time(NULL));
        name = msg;
        m_ThreadIsFinished=false;
    }
    
    Thread(const char* _name) : name(_name) {
        pthread_mutex_init(&mymutex, NULL);
        pthread_cond_init(&mycond, NULL);
    }
    
    virtual ~Thread() {
        stopThread();
        pthread_mutex_destroy(&mymutex);
        pthread_cond_destroy(&mycond);
        
    }
    
    const char* getName() {
        return name.c_str();
    }
    
    void start() {
        if ( pthread_create( &mythread, NULL, _run, this) ) {
            printf("error creating thread.\n");
            abort();
        }
    }
    void stopThread()
    {
        m_ThreadIsFinished=true;
//        pthread_join(mythread,NULL);
    }
    pthread_t getThreadId()
    {
        return pthread_self();
    }
private:
    static void* _run(void* This) {
        return ((Thread*) This)->run();
    }
};

class Synchronizable {
protected:
    pthread_mutex_t mymutex;
    pthread_cond_t mycond;
    
public:
#define LOCK_BEGIN  pthread_mutex_lock(&mymutex)
#define LOCK_END    pthread_mutex_unlock(&mymutex)
#define WAIT        pthread_cond_wait(&mycond, &mymutex)
#define NOTIFY_ALL  pthread_cond_broadcast(&mycond);
    
public:
    Synchronizable() {
        pthread_mutex_init(&mymutex, NULL);
        pthread_cond_init(&mycond, NULL);
    }
    
    virtual ~Synchronizable() {
        pthread_mutex_destroy(&mymutex);
        pthread_cond_destroy(&mycond);
    }
    
};
/*
 
 #include "ThreadHelper.h"
 
 #include <pthread.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <stdio.h>
 #include <time.h>
 #include <string>
 #include <vector>
 #include <sstream>
 
 // 生产者必须将数据安全地交给消费者。虽然只是这样的问题，但当生产者与消费者
 // 在不同的线程上运行时，两者的处理速度差将是最大的问题。当消费者要取数据时
 // 生产者还没有建立出数据，或是生产者建立出数据时消费者的状态还没办法接受数据等。
 // Producer-Consumer Pattern是在生产者和消费者之间加入一个“桥梁参与者”。
 // 以这个桥梁参与者缓冲线程之间的处理速度差。
 
 
 class Table : Synchronizable {
 private:
 int tail, head, count;
 std::vector<std::string> buffer;
 
 
 public:
 Table(int _count) : tail(0), head(0), count(0) {
 buffer.resize(_count);
 }
 
 
 void put(const char* cake) {
 LOCK_BEGIN;
 while (count >= buffer.size()) {
 printf("!!!TABLE IS FULL!!!\n");
 fflush(stdout); // flush stdout for windows
 WAIT;
 }
 buffer[tail] = cake;
 tail = (tail+1) % buffer.size();
 count++;
 NOTIFY_ALL;
 printf("puts  %s -- size %d\n", cake, count);
 fflush(stdout);
 LOCK_END;
 }
 
 
 const char* take() {
 LOCK_BEGIN;
 while (count<=0) {
 printf("!!!NO MORE CAKES!!!\n");
 WAIT;
 }
 std::string cake = buffer[head];
 head = (head+1) % buffer.size();
 count--;
 NOTIFY_ALL;
 printf("takes %s -- size %d\n", cake.c_str(), count);
 fflush(stdout);
 LOCK_END;
 return cake.c_str();
 }
 };
 
 
 static int mid;
 
 
 class MakerThread: public Thread {
 private:
 Table* table;
 public:
 MakerThread(const char* _name, Table* _table) : Thread(_name) {
 this->table = _table;
 srand((unsigned)time(NULL));
 }
 void* run() {
 while (true) {
 msleep(rand()%1000);
 std::stringstream ss;
 ss << "[Cake No." << nextId() << " by " << getName()  << "]";
 table->put(ss.str().c_str());
 }
 return NULL;
 }
 
 
 static int nextId() {
 return mid++;
 }
 };
 
 
 class EaterThread: public Thread {
 private:
 Table* table;
 public:
 EaterThread(const char* _name, Table* _table) : Thread(_name) {
 this->table = _table;
 }
 
 
 void* run() {
 while (true) {
 const char* cake = table->take();
 //            printf("%s\n", cake);
 msleep(rand()%1000);
 }
 return NULL;
 }
 };
 
 
 void pcRun() {
 Table* table = new Table(3);  // 建立可以放置3个蛋糕的桌子
 (new MakerThread("MakerThread-1", table))->start();
 (new MakerThread("MakerThread-2", table))->start();
 (new MakerThread("MakerThread-3", table))->start();
 (new EaterThread("EaterThread-1", table))->start();
 (new EaterThread("EaterThread-2", table))->start();
 (new EaterThread("EaterThread-3", table))->start();
 msleep(90 * 1000);
 getchar();
 printf("hello producer consumer");
 }
 
 #endif
 */
#endif /* defined(__starProfessor__ThreadHelper__) */
