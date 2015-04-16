/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file Main.cpp
 * @author liuyihao01(com@baidu.com)
 * @date 2013/03/29 20:23:27
 * @brief 系统Main函数，实现抓取功能
 *  
 **/

#include <iostream>
#include <fstream>
#include "ul_conf.h"
#include "ul_log.h"
#include "ul_common.h"
#include "Epoll.h"
#include "Dispatch.h"
#include "Receive.h"
#include "Crawl.h"
using namespace std;

/* 配置项个数 */
#define UL_CONF_NUM 1

/* 函数功能：从配置文件中获取抓取器个数 */
void GetCrawlNumByConf(int *CrawlNum)
{
    ul_confdata_t *pulConf;

    pulConf = ul_initconf(UL_CONF_NUM);

    if (1 == ul_readconf("../conf/", "crawl.conf", pulConf))
    {
        ul_getconfint(pulConf, "CrawlerNumber", CrawlNum);
    }

    ul_freeconf(pulConf);

    return;
}

/* 函数功能：系统main函数，实现抓取功能 */
int main()
{
    /* 加载配置 */
    ul_logstat_t l_stat = {UL_LOG_NOTICE, UL_LOG_NOTICE, 0};
    ul_openlog("../log/", "crawl", &l_stat, MAX_FILE_SIZE, NULL);

    int crawler_num = 0;
    GetCrawlNumByConf(&crawler_num);

    /* 实例化 */
    Epoller *pepoller = new Epoller();
    Dispatcher *pdispatcher = new Dispatcher();
    Crawler *pcrawler = new Crawler[crawler_num];
    Receiver *preceiver = new Receiver();

    /* 启动服务 */
    pepoller->EpollCreate();

    for (int i = 0; i < crawler_num; i++)
    {
        pcrawler[i].StartCrawlThr(pdispatcher, pepoller);
    }

    preceiver->StartReceiveThr(pdispatcher);

    pepoller->StartEpollWaitThr();

    sleep(20);

    /* 去实例化 */
    delete pdispatcher;
    delete pepoller;
    delete preceiver;
    delete[] pcrawler;

    /* 删除配置 */
    cout << "Process end normaly." << endl;
    ul_closelog(0);

    return 0;
}



















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
