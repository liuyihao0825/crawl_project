 
 
 
/**
 * @file Crawl.h
 * @author liuyihao
 * @date 2013/04/01 09:54:18
 * @brief 抓取器类，从队列获取url并建立连接
 *  
 **/




#ifndef  __CRAWL_H_
#define  __CRAWL_H_

class Dispatcher;
class Epoller;

/* 线程处理函数参数结构体 */
typedef struct THRFUN_ARG_T
{
    Dispatcher *pdispatch;
    Epoller    *pepoll;
}thrfun_arg_t;

/* 抓取器类，从队列获取url并建立连接 */
class Crawler
{
    private:
        pthread_t ptid;                                              //线程id

    public:
        int StartCrawlThr(Dispatcher *pdispatch, Epoller *pepoll);   //启动抓取线程
};














#endif  //__CRAWL_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
