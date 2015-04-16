/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file Receive.cpp
 * @author liuyihao01(com@baidu.com)
 * @date 2013/03/29 20:10:31
 * @brief 接收器类，接收url
 *  
 **/

#include <iostream>
#include <string>
#include <fstream>
#include "ul_log.h"
#include "ul_common.h"
#include "Dispatch.h"
#include "Receive.h"
using namespace std;

/* 函数功能：接收器线程主处理函数 */
void *rec_thr_fun(void *arg)
{
    Dispatcher *pdispatch = (Dispatcher *)arg;

    ul_logstat_t l_stat = {UL_LOG_NOTICE, UL_LOG_NOTICE, 0};
    ul_openlog_r("receive thread", &l_stat, NULL);

    /* 打开url存放文件 url.txt */
    ifstream infile("../../url.txt");
    if (NULL == infile)
    {
        ul_writelog(UL_LOG_NOTICE, "Failed to read url.txt.\n");
        ul_closelog_r(0);
        return ((void *)1);
    }

    int count = 0;
    char *page;
    ul_crawl_t *pulcrawl;
    string url_input;

    /* 从 url.txt 中读取每条 url */
    while (getline(infile, url_input))
    {
        ++count;

        page = (char *)malloc(sizeof(char) * PAGE_MAX_LEN);
        pulcrawl = (ul_crawl_t *)malloc(sizeof(ul_crawl_t));

        /* 初始化 pulcrawl 结构 */
        memset(pulcrawl, 0, sizeof(ul_crawl_t));
        pulcrawl->index = count;
        pulcrawl->page_content = page;
        strcpy(pulcrawl->url, url_input.c_str());

        /* 将 pulcrawl 加入队列 */
        pdispatch->PushQueue(pulcrawl);    
    }

    infile.close();
    ul_closelog_r(0);
    
    pthread_exit(NULL);

    return ((void *)0);
} 

/* 函数功能：启动接收器服务 */
int Receiver::StartReceiveThr(Dispatcher *pdispatch)
{
    if(0 != (pthread_create(&ptid, NULL, rec_thr_fun, (void *)pdispatch)))
    {
        ul_writelog(UL_LOG_NOTICE, "Failed to create Receive Thread.\n");
        return -1;
    }

    return 0;
}









/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
