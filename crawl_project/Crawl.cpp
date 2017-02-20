 
 
 
/**
 * @file Crawl.cpp
 * @author liuyihao01
 * @date 2013/04/01 09:56:40
 * @brief 抓取器类，从队列获取url并建立连接 
 *  
 **/

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "ul_common.h"
#include "ul_log.h"
#include "ul_url.h"
#include "Epoll.h"
#include "Dispatch.h"
#include "Crawl.h"
using namespace std;

/* 函数功能：连接请求服务器并将sockfd加epoll */
int ConnectServer(ul_crawl_t *pulcrawl, Epoller *pepoll)
{
    int site_port;
    struct hostent *host;
    char site[UL_MAX_SITE_LEN];
    char port[UL_MAX_PORT_LEN];
    char path[UL_MAX_PATH_LEN];

    /* 通过url获取site, port, path */
    if (1 != (ul_parse_url(pulcrawl->url, site, port, path)))
    {
        ul_writelog(UL_LOG_NOTICE, "Failed to get site, port, path.\n");
        return -1;
    }
  
    site_port = atoi(port);

    /* 获取 site ip */
    if (NULL == (host = gethostbyname(site)))
    {
        ul_writelog(UL_LOG_NOTICE, "Failed to get IP.\n");
        return -1;
    }

    int sockfd;
    struct sockaddr_in server_addr;

    if (0 > (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        ul_writelog(UL_LOG_NOTICE, "Failed to create socket.\n");
        return -1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(site_port);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);

    if (0 > (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))))
    {
        close(sockfd);
        ul_writelog(UL_LOG_NOTICE, "Failed to connect server.\n");
        return -1;
    }

    pulcrawl->sockfd = sockfd;
    sprintf(pulcrawl->request, "GET %s HTTP/1.1\r\nHost:%s\r\nConnection:Close\r\n\r\n", path, site);

    /* 将连接加入epoll */
    if (0 != (pepoll->EpollAdd(pulcrawl)))
    {
        close(pulcrawl->sockfd);
        pulcrawl->sockfd = 0;
        ul_writelog(UL_LOG_NOTICE, "Failed to add sockfd to epoll.\n");
        return -1;
    }

    return 0;
}

/* 函数功能：线程回调函数 */
void *crawl_thread_fun(void *arg)
{
    thrfun_arg_t *pfun_arg = (thrfun_arg_t *)arg;
    Dispatcher *pdispatch = pfun_arg->pdispatch;
    Epoller *pepoll = pfun_arg->pepoll;
    delete pfun_arg;

    ul_logstat_t l_stat = {UL_LOG_NOTICE, UL_LOG_NOTICE, 0};
    ul_openlog_r("crawl thread", &l_stat, NULL);

    ul_crawl_t *pulcrawl_temp;
    
    /* 循环读取队列，取队列头元素，建立连接加epoll */
    while (1)
    {
        pulcrawl_temp = pdispatch->PopQueue();
        if (NULL == pulcrawl_temp)
        {
            usleep(1000);
        }
        else
        {
            if (0 == ConnectServer(pulcrawl_temp, pepoll))
            {
                ul_writelog(UL_LOG_NOTICE, "Send index= %d,Request url=%s success.\n", pulcrawl_temp->index, pulcrawl_temp->url);
                cout << "log: Send index=" << pulcrawl_temp->index << " Request= " << pulcrawl_temp->url << " success." << endl;
            }
            else
            {
                ul_writelog(UL_LOG_NOTICE, "Send index= %d,Request url=%s failed.\n", pulcrawl_temp->index, pulcrawl_temp->url);
                cout << "log: Send index=" << pulcrawl_temp->index << " Request= " << pulcrawl_temp->url << " failed." << endl;
                if (0 != pulcrawl_temp->sockfd)
                {
                    close(pulcrawl_temp->sockfd);
                }

                free(pulcrawl_temp->page_content);
                free(pulcrawl_temp);
            }
        }
    }

    ul_closelog_r(0);

    pthread_exit(NULL);

    return ((void *)0);
}

/* 函数功能：启动抓取线程 */
int Crawler::StartCrawlThr(Dispatcher *pdispatch, Epoller *pepoll)
{
    int ErrCode;

    thrfun_arg_t *fun_arg = new thrfun_arg_t;
    fun_arg->pdispatch = pdispatch;
    fun_arg->pepoll = pepoll;

    ErrCode = pthread_create(&ptid, NULL, crawl_thread_fun, (void *)fun_arg);
    if (0 != ErrCode)
    {
        ul_writelog(UL_LOG_NOTICE, "Failed to create crawl thread.\n");
    }

    return ErrCode;
}


















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
