/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file Epoll.h
 * @author lichuang(lichuang@baidu.com)
 * @date 2013/04/09 16:27:33
 * @brief Epoll�࣬�ṩepoll����
 *  
 **/




#ifndef  __EPOLL_H_
#define  __EPOLL_H_

/* Epoll�࣬�ṩepoll���� */
class Epoller
{
    private:
        pthread_t ptid;                         //�߳�id

    public:
        int epfd;                               //epoll fd
        int EpollCreate();                      //���� EPOLL
        int EpollAdd(ul_crawl_t *pulcrawl);     //�� EPOLL
        int StartEpollWaitThr();                //���� EPOLL_WAIT
        Epoller();                              //��ʼ��epfd
        ~Epoller();                             //�ر�epfd
};














#endif  //__EPOLL_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
