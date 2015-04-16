/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file Dispatch.cpp
 * @author liuyihao01(com@baidu.com)
 * @date 2013/04/01 09:52:29
 * @brief 分发模块，提供队列读写功能
 *  
 **/

#include <iostream>
#include <pthread.h>
#include "Dispatch.h"
using namespace std;

/* 函数功能：push队列 */
void Dispatcher::PushQueue(ul_crawl_t *pulcrawl)
{
    pthread_mutex_lock(&mutex);
 
    crawl_queue.push(pulcrawl);

    pthread_mutex_unlock(&mutex);

    return;
}

/* 函数功能：pop队列，如果队列为空，返回NULL */
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

/* 函数功能：初始化mutex */
Dispatcher::Dispatcher()
{
    pthread_mutex_init(&mutex, NULL);
}

/* 函数功能：销毁mutex */
Dispatcher::~Dispatcher()
{
    pthread_mutex_destroy(&mutex);
}














/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
