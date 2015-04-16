/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file Dispatch.h
 * @author liuyihao01(com@baidu.com)
 * @date 2013/04/01 09:50:13
 * @brief �ַ����࣬�ṩ���ж�д����
 *  
 **/




#ifndef  __DISPATCH_H_
#define  __DISPATCH_H_

#include <queue>
#include "ul_common.h"
using namespace std;

/* �ַ����࣬�ṩ���ж�д���� */
class Dispatcher
{
    private:
        queue<ul_crawl_t *> crawl_queue;         //���У����ul_crawl_t�ṹָ��
        pthread_mutex_t mutex;                   //���������Զ��н��м�������

    public:
        void PushQueue(ul_crawl_t *pulcrawl);    //push����
        ul_crawl_t *PopQueue();                  //pop���У������ض�ͷԪ��
        Dispatcher();                            //���캯������ʼ��mutex
        ~Dispatcher();                           //��������������mutex
};














#endif  //__DISPATCH_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
