/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file Dispatch.h
 * @author liuyihao01(com@baidu.com)
 * @date 2013/04/01 09:50:13
 * @brief 分发器类，提供队列读写功能
 *  
 **/




#ifndef  __DISPATCH_H_
#define  __DISPATCH_H_

#include <queue>
#include "ul_common.h"
using namespace std;

/* 分发器类，提供队列读写功能 */
class Dispatcher
{
    private:
        queue<ul_crawl_t *> crawl_queue;         //队列，存放ul_crawl_t结构指针
        pthread_mutex_t mutex;                   //互斥锁，对队列进行加锁保护

    public:
        void PushQueue(ul_crawl_t *pulcrawl);    //push队列
        ul_crawl_t *PopQueue();                  //pop队列，并返回队头元素
        Dispatcher();                            //构造函数，初始化mutex
        ~Dispatcher();                           //析构函数，销毁mutex
};














#endif  //__DISPATCH_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
