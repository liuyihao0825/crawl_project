 
 
 
/**
 * @file ul_common.h
 * @author liuyihao
 * @date 2013/04/02 16:16:33
 * @brief 系统公共数据结构，用于保存请求的url和响应信息
 *  
 **/




#ifndef  __UL_COMMON_H_
#define  __UL_COMMON_H_

/* 网页最大长度 */
#define PAGE_MAX_LEN  524288

/* url最大长度 */
#define URL_MAX_LEN   256

/* 请求信息最大长度 */
#define REQ_MAX_LEN   356

/* 数据结构，保存请求的url和响应信息 */
typedef struct UL_CRAWL_T
{
    unsigned int   index;                  //请求url的序列号
    int            sockfd;                 //socket fd
    char           url[URL_MAX_LEN];       //请求的url
    char           request[REQ_MAX_LEN];   //请求信息
    char           *page_content;          //网页内容
}ul_crawl_t;











#endif  //__UL_COMMON_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
