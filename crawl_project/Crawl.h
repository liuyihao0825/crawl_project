 
 
 
/**
 * @file Crawl.h
 * @author liuyihao
 * @date 2013/04/01 09:54:18
 * @brief ץȡ���࣬�Ӷ��л�ȡurl����������
 *  
 **/




#ifndef  __CRAWL_H_
#define  __CRAWL_H_

class Dispatcher;
class Epoller;

/* �̴߳����������ṹ�� */
typedef struct THRFUN_ARG_T
{
    Dispatcher *pdispatch;
    Epoller    *pepoll;
}thrfun_arg_t;

/* ץȡ���࣬�Ӷ��л�ȡurl���������� */
class Crawler
{
    private:
        pthread_t ptid;                                              //�߳�id

    public:
        int StartCrawlThr(Dispatcher *pdispatch, Epoller *pepoll);   //����ץȡ�߳�
};














#endif  //__CRAWL_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
