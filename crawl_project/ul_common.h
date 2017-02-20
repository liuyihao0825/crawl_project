 
 
 
/**
 * @file ul_common.h
 * @author liuyihao
 * @date 2013/04/02 16:16:33
 * @brief ϵͳ�������ݽṹ�����ڱ��������url����Ӧ��Ϣ
 *  
 **/




#ifndef  __UL_COMMON_H_
#define  __UL_COMMON_H_

/* ��ҳ��󳤶� */
#define PAGE_MAX_LEN  524288

/* url��󳤶� */
#define URL_MAX_LEN   256

/* ������Ϣ��󳤶� */
#define REQ_MAX_LEN   356

/* ���ݽṹ�����������url����Ӧ��Ϣ */
typedef struct UL_CRAWL_T
{
    unsigned int   index;                  //����url�����к�
    int            sockfd;                 //socket fd
    char           url[URL_MAX_LEN];       //�����url
    char           request[REQ_MAX_LEN];   //������Ϣ
    char           *page_content;          //��ҳ����
}ul_crawl_t;











#endif  //__UL_COMMON_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
