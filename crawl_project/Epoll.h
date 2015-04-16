/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file Epoll.h
 * @author lichuang(lichuang@baidu.com)
 * @date 2013/04/09 16:27:33
 * @brief Epoll类，提供epoll功能
 *  
 **/




#ifndef  __EPOLL_H_
#define  __EPOLL_H_

/* Epoll类，提供epoll功能 */
class Epoller
{
    private:
        pthread_t ptid;                         //线程id

    public:
        int epfd;                               //epoll fd
        int EpollCreate();                      //创建 EPOLL
        int EpollAdd(ul_crawl_t *pulcrawl);     //加 EPOLL
        int StartEpollWaitThr();                //启动 EPOLL_WAIT
        Epoller();                              //初始化epfd
        ~Epoller();                             //关闭epfd
};














#endif  //__EPOLL_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
