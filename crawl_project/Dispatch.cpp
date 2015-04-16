/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file Dispatch.cpp
 * @author liuyihao01(com@baidu.com)
 * @date 2013/04/01 09:52:29
 * @brief �ַ�ģ�飬�ṩ���ж�д����
 *  
 **/

#include <iostream>
#include <pthread.h>
#include "Dispatch.h"
using namespace std;

/* �������ܣ�push���� */
void Dispatcher::PushQueue(ul_crawl_t *pulcrawl)
{
    pthread_mutex_lock(&mutex);
 
    crawl_queue.push(pulcrawl);

    pthread_mutex_unlock(&mutex);

    return;
}

/* �������ܣ�pop���У��������Ϊ�գ�����NULL */
ul_crawl_t* Dispatcher::PopQueue()
{
    ul_crawl_t *pcrawl_temp = NULL;

    pthread_mutex_lock(&mutex);

    if (false == crawl_queue.empty())
    {
        pcrawl_temp = crawl_queue.front();
        crawl_queue.pop();
    }

    pthread_mutex_unlock(&mutex);
    
    return pcrawl_temp;
}

/* �������ܣ���ʼ��mutex */
Dispatcher::Dispatcher()
{
    pthread_mutex_init(&mutex, NULL);
}

/* �������ܣ�����mutex */
Dispatcher::~Dispatcher()
{
    pthread_mutex_destroy(&mutex);
}














/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
