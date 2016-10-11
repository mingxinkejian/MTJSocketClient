//
//  MTJSocketLinkedQueue.h
//  MTJSocketClient
//
//  Created by Reddog on 16/10/10.
//  Copyright (c) 2016年 mingtingjian. All rights reserved.
//

#ifndef MTJSocketClient_MTJSocketLinkedQueue_h
#define MTJSocketClient_MTJSocketLinkedQueue_h

#include <stdlib.h>
#include "MTJSocketQueue.h"

struct MTJSocketLinkedNode {
    void* data;
    MTJSocketLinkedNode* next;
};

template <class T>
class MTJSocketLinkedQueue : public MTJSocketQueue<T> {
protected:
    MTJSocketLinkedNode* m_pHead;
    MTJSocketLinkedNode* m_pTail;
    int m_nSize;
public:
    MTJSocketLinkedQueue() : m_pHead(NULL),m_pTail(NULL),m_nSize(0){
    }
    
    virtual ~MTJSocketLinkedQueue(){
        MTJSocketLinkedNode* p = m_pHead;
        while (p != NULL) {
            delete ((T*) p->data);
            MTJSocketLinkedNode* t = p;
            p = p->next;
            free(t);
        }
    }
    
    virtual bool Offer(T* pElement){
        MTJSocketLinkedNode* p = (MTJSocketLinkedNode*) malloc(sizeof(MTJSocketLinkedNode));
        p->data = pElement;
        p->next = NULL;
        if (m_nSize <= 0) {
            m_pHead = p;
            m_pTail = p;
        }else{
            m_pTail->next = p;
            m_pTail = p;
        }
        
        m_nSize++;
        return true;
    }
    
    virtual T* Peek(){
        if (m_pHead != NULL) {
            return (T*) (m_pHead->data);
        }
        return NULL;
    }
    
    virtual T* Poll(){
        if (m_pHead != NULL) {
            T* t = (T*)(m_pHead->data);
            MTJSocketLinkedNode* hp = m_pHead;
            m_pHead = m_pHead->next;
            if (m_pHead == NULL) {
                m_pTail = NULL;
            }
            free(hp);
            m_nSize--;
            return t;
        }
        return (T*)(NULL);
    }
    
    virtual int Size(){
        return m_nSize;
    }
};

#endif
