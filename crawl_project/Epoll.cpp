 
 
 
/**
 * @file Epoll.cpp
 * @author liuyihao
 * @date 2013/04/09 16:36:43
 * @brief EPOLL�࣬�ṩEPOLL����
 *  
 **/

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include "ul_log.h"
#include "ul_common.h"
#include "Epoll.h"
using namespace std;

/* Epoll�������� */
#define EPOLL_FD_MAX_NUM 1024

/* ���ջ��������� */
#define REV_BUF_MAX_LEN  2048

/* �������ܣ�ƴ������ļ��� */
void CreateOutFile(int index, char *outFileStr)
{
    char FileName[8];

    sprintf(FileName, "%d", index);
    strcat(outFileStr, "../data/");
    strcat(outFileStr, FileName);
    strcat(outFileStr, ".html");
}

/* �������ܣ�����epoll fd */
int Epoller::EpollCreate()
{
    epfd = epoll_create(EPOLL_FD_MAX_NUM);

    if (0 > epfd)
    {
        ul_writelog(UL_LOG_NOTICE, "Failed to create epoll.\n");
        return -1;
    }

    return 0;
}

/* �������ܣ���sockfd ���� epoll */
int Epoller::EpollAdd(ul_crawl_t *pulcrawl)
{
    if (NULL == pulcrawl)
    {
        return -1;
    }

    int sockfd = pulcrawl->sockfd;
    struct epoll_event event;
    event.events = EPOLLIN | EPOLLOUT;     /* ����epoll in �� out �¼� */
    event.data.ptr = (void *)pulcrawl;

    if (0 != epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event))
    {
        close(sockfd);
        ul_writelog(UL_LOG_NOTICE, "Failed to add sockfd to epoll.\n");
        return -1;
    }

    return 0;
}

/* �������ܣ��߳��������� */
void *epoll_thr_fun(void *arg)
{
    ul_logstat_t l_stat = {UL_LOG_ALL, UL_LOG_ALL, 0};
    ul_openlog_r("epoll thread", &l_stat, NULL);

    int *epoll_fd = (int *)arg;
    int epfd = *epoll_fd;
    delete epoll_fd;

    int i;
    int nfds;
    int sockfd;
    int rec_len;                                 /* recv���� */
    char rec_buf[REV_BUF_MAX_LEN + 1];           /* recv������ */
    struct epoll_event ev[EPOLL_FD_MAX_NUM];
    struct epoll_event event;
    ul_crawl_t *pulcrawl;
    
    for (;;)
    {
        nfds = epoll_wait(epfd, ev, EPOLL_FD_MAX_NUM, 0);
        
        for (i = 0; i < nfds; i++)
        {
            if (ev[i].events & EPOLLOUT)           /* ����epollout�¼�������������Ϣ��������  */
            {
                pulcrawl = (ul_crawl_t *)ev[i].data.ptr;
                sockfd = pulcrawl->sockfd;
                
                send(sockfd, pulcrawl->request, strlen(pulcrawl->request), 0);

                event.data.ptr = (void *)pulcrawl;
                event.events = EPOLLIN;
                epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &event);
            }
            else if (ev[i].events & EPOLLIN)       /* ����epollin�¼���������Ӧ��Ϣ */
            {
                pulcrawl = (ul_crawl_t *)ev[i].data.ptr;
                sockfd = pulcrawl->sockfd;

                rec_len = recv(sockfd, rec_buf, REV_BUF_MAX_LEN, 0);
                if (0 < rec_len)
                {
                    strcat(pulcrawl->page_content, rec_buf);
                    memset(rec_buf, 0, sizeof(rec_buf));
                }
                else if (0 == rec_len)
                {
                    char outFileName[30];
                    outFileName[0] = '\0';
                    CreateOutFile(pulcrawl->index, outFileName);

                    ofstream outfile(outFileName);
                    outfile << pulcrawl->page_content;
                    outfile.close();
    
                    close(sockfd);

                    free(pulcrawl->page_content);
                    free(pulcrawl);
                }
            }
        }
    }

    ul_closelog_r(0);
    
    pthread_exit(NULL);

    return (void *)0;
}

/* �������ܣ�����epoll������� */
int Epoller::StartEpollWaitThr()
{
    int *epoll_fd = new int();
    *epoll_fd = epfd;

    if (0 != (pthread_create(&ptid, NULL, epoll_thr_fun, (void *)epoll_fd)))
    {
        ul_writelog(UL_LOG_NOTICE, "Failed to create epoll thread.\n");
        return -1;
    }

    return 0;
}

/* �������ܣ���ʼ��epfd */
Epoller::Epoller()
{
    epfd = 0;
}

/* �������ܣ��ر�epfd */
Epoller::~Epoller()
{
    if (0 != epfd)
    {
        close(epfd);
    }    
}















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
