/***************************************************************************
 *
 * Copyright (c) 2007 Baidu.com, Inc. All Rights Reserved
 * $Id: uln_http.h,v 1.11.4.5 2010/03/23 14:52:00 zhangyan04 Exp $ 
 * 
 **************************************************************************/

#ifndef ULN_HTTP_H
#define ULN_HTTP_H
#include <ul_net.h>
#include "uln_vector.h"

const int ULN_ERR_GENERAL_ERROR = -1;
const int ULN_ERR_MEMORY_NOT_ENOUGH = -2;
const int ULN_ERR_SOCKET_ERROR = -3;
const int ULN_ERR_CONNECT_TIMEOUT = -4;
const int ULN_ERR_READ_ERROR = -5;
const int ULN_ERR_CONNECT_ERROR = -6;
const int ULN_ERR_HOST_RESOLVE_FAILED = -7;
const int ULN_NOTICE_NONE = 0;
const int ULN_NOTICE_OK = 1;
const int ULN_NOTICE_TRUNC_BY_LIMIT = 2;
const int ULN_NOTICE_TRUNC_BY_SERVER = 3;

const unsigned int ULN_URL_LENGTH = 256;
const unsigned int ULN_URL_LENGTH_EX2 = 2048; //modified by zhangyan04@baidu.com
const unsigned int ULN_PAGE_LENGTH = 524288;
const unsigned int ULN_MAX_RPAIR_COUNT = 16;

const unsigned int ULN_DEFAULT_PAGESIZE = 32768;
const unsigned int ULN_MAX_LINE_SIZE = 2048;
const unsigned int ULN_MAX_LINE_SIZE_EX2 = 6144; //对于_ex2接口使用更长的行缓冲区.
const unsigned int ULN_MAX_HEAD_COUNT = 64; //http响应的(key,value)上限..
const unsigned int ULN_IP_LENGTH = 16;
const unsigned int ULN_REQ_SIZE = 4096;
const unsigned int ULN_REQ_SIZE_EX2 = 8192; //modified by zhangyan04@baidu.com
const int DEFAULT_NTIMEOUT = 300;
const int DEFAULT_NTIMEOUT_MS = 300;

const char* const BAIDU_USERAGENT =
"Baiduspider+(+http://www.baidu.com/search/spider.htm)";
const char* const COMMON_USERAGENT =
"Mozilla/4.0 (compatible; MSIE 5.0; Windows 98; DigExt)";

const char* const STR_METHOD_GET = "GET";
const char* const STR_METHOD_HEAD = "HEAD";
const char* const STR_METHOD_POST = "POST";
const char* const STR_METHOD_PUT = "PUT";
const char* const STR_METHOD_OPTIONS = "OPTIONS";
const char* const STR_METHOD_DELETE = "DELETE";
const char* const STR_METHOD_TRACE = "TRACE";

typedef struct ULN_RESPONSE_T {
    int            m_status_code;         ///< 状态码, 如200,404等
    char           m_version[16];         ///< HTTP版本, 如1.1
    char           m_status_phrase[128];  ///< 状态信息，如OK
    uln_vector_t*  m_reshead;             ///< 返回头信息
                           
    char*          m_buf;                 ///< 页面内容存储buffer
    unsigned int   m_size;                ///< buffer的大小
    unsigned int   m_len;                 ///< 页面长度

} uln_response_t;


typedef enum HTTP_METHOD_T {
    HTTP_GET,
    HTTP_HEAD,
    HTTP_POST,
    HTTP_PUT,
    HTTP_OPTIONS,
    HTTP_DELETE,
    HTTP_TRACE
} http_method_t;

typedef struct ULN_REQUEST_T {
    http_method_t   m_method;                 ///< 请求方法，如GET, POST等
    char            m_url[ULN_URL_LENGTH];    ///< 请求的URL,在crawl_page_ex及check_page_ex中，不起作用.
    char            m_ip[ULN_IP_LENGTH];      ///< 请求的IP, 在crawl_page_ex及check_page_ex中，不起作用.
    uln_vector_t*   m_req_head;               ///< 详细的请求头信息
} uln_request_t;

//////////////////////////////////////////////////////////////
//长度扩展后的结构..
//modified by zhangyan04@baidu.com
//just have extended url length:-)
typedef struct ULN_RESPONSE_EX2_T {
    int            m_status_code;         ///< 状态码, 如200,404等
    char           m_version[16];         ///< HTTP版本, 如1.1
    char           m_status_phrase[128];  ///< 状态信息，如OK
    uln_vector_ex2_t*  m_reshead;             ///< 返回头信息
                           
    char*          m_buf;                 ///< 页面内容存储buffer
    unsigned int   m_size;                ///< buffer的大小
    unsigned int   m_len;                 ///< 页面长度

} uln_response_ex2_t;

typedef struct ULN_REQUEST_EX2_T {
    http_method_t   m_method;                 ///< 请求方法，如GET, POST等
    char            m_url[ULN_URL_LENGTH_EX2];    ///< 请求的URL,在crawl_page_ex2及check_page_ex2中，不起作用.
    char            m_ip[ULN_IP_LENGTH];      ///< 请求的IP, 在crawl_page_ex2及check_page_ex2中，不起作用.
    uln_vector_ex2_t*   m_req_head;               ///< 详细的请求头信息
} uln_request_ex2_t;

/**
 * @brief 生成并初始化uln_response_t应答结构体. 
 *
 * @return  uln_response_t*, 应答结构体指针
 * @retval  非NULL，表示应答结构体指针, 若初始化成功
 * @retval  NULL, 若初始化成败
 * @see     uln_http_freeres()
 * @note    初始化时，会为m_buf字段开大小为ULN_DEFAULT_PAGESIZE大小的空间
 * @author wangjg
 * @date 2007/12/27 13:49:18
**/
uln_response_t* uln_http_initres(void);

/**
 * @brief 释放应答结构体内存, 同时释放结构体内buf的内存.
 *
 * @param [in] pres   : uln_response_t* 待释放的结构体指针.
 * @return  void 
 * @see  uln_http_initres()
 * @note 若传入指针为空，不做任何事情
 * @author wangjg
 * @date 2007/12/27 17:09:22
**/
void uln_http_freeres(uln_response_t *pres);


 /**
 * @brief 读取http头信息. 
 * http头的version、status_code、status_phrase存放在pres的相应字段，
 * 其它信息保存在pres->m_reshead中.
 *
 * @param [in]  sockfd   : int               socket句柄
 * @param [out] pres     : uln_response_t*   返回结构指针  
 * @param [in]  prl      : Rline*            缓冲区
 * @param [in]  ntimeout : int               超时时间
 * @return  int 操作结果
 * @retval   1  读取头部信息成功
 * @retval  -1  网络读取错误(超时或其他网络错误) 
 * @retval  -2  应答格式错误(返回头错误)
 * @retval  -3  传入参数不合法
 * @see   
 * @note  prl存储读到的数据,执行完此函数时,里面有可能还有未读的数据
 * @author wangjg
 * @date 2007/12/27 17:20:46
**/
int uln_http_readhead(int sockfd, uln_response_t* pres, Rline *prl, int ntimeout);

 /**
 * @brief 读取http头信息. 
 * http头的version、status_code、status_phrase存放在pres的相应字段，
 * 其它信息保存在pres->m_reshead中.
 * 与uln_http_readhead的不同是：此处超时时间精度为毫秒
 *
 * @param [in]  sockfd   : int               socket句柄
 * @param [out] pres     : uln_response_t*   返回结构指针  
 * @param [in]  prl      : Rline*            缓冲区
 * @param [in]  ntimeout : int               超时时间
 * @return  int 操作结果
 * @retval   1  读取头部信息成功
 * @retval  -1  网络读取错误(超时或其他网络错误) 
 * @retval  -2  应答格式错误(返回头错误)
 * @retval  -3  传入参数不合法
 * @see   
 * @note  prl存储读到的数据,执行完此函数时,里面有可能还有未读的数据
 * @author gonglei 
 * @date 2008/12/30
**/
int uln_http_readhead_ms(int sockfd, uln_response_t* pres, Rline *prl, int ntimeout);

/**
 * @brief 向已连接的socket句柄发送http请求.
 *
 * @param [in] sock       : const int         socket句柄
 * @param [in] preq       : uln_request_t*    请求结构体
 * @param [in] ntimeout   : int               超时时间(秒)
 * @return     int        操作结果
 * @retval     1          success
 * @retval     -1         failed
**/
int uln_http_sendreq(const int sock, uln_request_t* preq, int ntimeout);

/**
 * @brief 向已连接的socket句柄发送http请求.
 * 与uln_http_sendreq的不同是：此处超时时间单位为毫秒
 *
 * @param [in] sock       : const int         socket句柄
 * @param [in] preq       : uln_request_t*    请求结构体
 * @param [in] ntimeout   : int               超时时间(毫秒)
 * @return     int        操作结果
 * @retval     1          success
 * @retval     -1         failed
**/
int uln_http_sendreq_ms(const int sock, uln_request_t* preq, int ntimeout);

/**
 * @brief 读取http网页内容.
 *
 * @param [in]  sockfd   : int               socket句柄
 * @param [out] pres     : uln_response_t*   返回结构指针
 * @param [out] prl      : Rline*            缓冲区
 * @param [in]  maxlen   : int               从服务器一次读取的最大长度
 * @param [in]  ntimeout : int               超时时间(秒)
 * @return  int   操作结果
 * @retval  1     成功读取http内容
 * @retval  2     page被截断 (长度大于maxlen)
 * @retval  3     page没有全部读完
 * @retval -1     网络读取错误
 * @retval -3     数据格式错误
 * @retval -4     内存错误
 * @retval -7     trunk模式时,未接到末尾flag,对端服务器主动断开连接错误
 * @retval -8     读出page长度与头信息中的长度不一致
 * @retval -10    转入参数不合法
 * @see 
 * @note 
 * @author wangjg
 * @date 2008/01/02 10:07:42
**/
int uln_http_readcontent(int sockfd, uln_response_t* pres, Rline *prl, int maxlen, int ntimeout);

/**
 * @brief 读取http网页内容.
 * 与uln_http_readcontent的不同是：此处超时时间单位为毫秒
 *
 * @param [in]  sockfd   : int               socket句柄
 * @param [out] pres     : uln_response_t*   返回结构指针
 * @param [out] prl      : Rline*            缓冲区
 * @param [in]  maxlen   : int               从服务器一次读取的最大长度
 * @param [in]  ntimeout : int               超时时间(毫秒)
 * @return  int   操作结果
 * @retval  1     成功读取http内容
 * @retval  2     page被截断 (长度大于maxlen)
 * @retval  3     page没有全部读完
 * @retval -1     网络读取错误
 * @retval -3     数据格式错误
 * @retval -4     内存错误
 * @retval -7     trunk模式时,未接到末尾flag,对端服务器主动断开连接错误
 * @retval -8     读出page长度与头信息中的长度不一致
 * @retval -10    转入参数不合法
 * @see 
 * @note 
 * @author gonglei 
 * @date 2008/12/30
**/
int uln_http_readcontent_ms(int sockfd, uln_response_t* pres, Rline *prl, int maxlen, int ntimeout);

/**
 * @brief 初始化请求结构体. 
 *
 * 此函数初始化的请求头信息有, 
 * Connection:close, Accept-Language:zh-cn,zh-tw,百度的User-agent等.
 * 请求方法是HTTP_GET
 * 
 * 传入的ip只在请求结构体中起保存作用，对url的抓取或检查不起作用. 可设为NULL.
 *
 * @param [in] url  : const char*  需要抓取或检查的url
 * @param [in] ip   : const char*  url相应的ip
 * @return  uln_request_t*         请求结构体指针
 * @retval  非NULL                 成功
 * @retval  NULL                   初始化不成功
 * @see 
 * @note    传入的ip只在请求结构体中起保存作用，对url的抓取或检查不起作用. 可设为NULL.
 * @author wangjg
 * @date 2008/01/02 17:27:31
**/
uln_request_t* uln_http_initreq(const char* url, const char* ip);


/**
 * @brief 释放请求结构体.
 *
 * @param [in] preq   : uln_request_t* 待释放的请求结构体指针
 * @return  void 
 * @retval  无
 * @see 
 * @note 
 * @author wangjg
 * @date 2008/01/03 10:39:30
**/
void uln_http_freereq(uln_request_t *preq);


/**
 *  默认请求结构从网络抓取网页
 *  
 *  @param[in]  url      待抓取网页的url
 *  @param[in]  ip       待抓取网页服务器的ip地址
 *  @param[in]  maxlen   网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres     返回结构的指针
 *  @param[in]  ntimeout 超时时间,以秒为单位
 *  @param[in]  flag     当flag & 0x1 !=0 时，只接收文本格式.
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[out] pres     返回网页信息
 *  @return 操作结果
 *  - 1 表示成功,详细信息将记录在pres结构中.
 *  - 2 表示网页被截断
 *  - -1 命令错误，初始化过程导致失败
 *  - -2 非法url
 *  - -3 连接服务器失败或发送错误
 *  - -4 读数据其他错误,例如网络读写错误
 *  - -5 数据错误
 *  - -7 读取内容未结束时,对端服务器主动断开(发生在trunk模式下)
 *  - -8 在非chunk模式下，在长度有效情况下（长度len>0且len<maxlen）数据接收不完全
 *  - -10 参数不合法
 *
 *  @note pres只需初始化一次即可多次利用. 使用完毕后需调用uln_http_freeres释放资源.
**/
int uln_http_crawlpage(const char* url,const char* ip,int maxlen,
                       uln_response_t* pres, int ntimeout, int flag);

/**
 *  默认请求结构从网络抓取网页
 *  超时时间单位为毫秒
 * 
 *  @param[in]  url      待抓取网页的url
 *  @param[in]  ip       待抓取网页服务器的ip地址
 *  @param[in]  maxlen   网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres     返回结构的指针
 *  @param[in]  ntimeout 超时时间,以毫秒为单位
 *  @param[in]  flag     当flag & 0x1 !=0 时，只接收文本格式.
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[out] pres     返回网页信息
 *  @return 操作结果
 *  - 1 表示成功,详细信息将记录在pres结构中.
 *  - 2 表示网页被截断
 *  - -1 命令错误，初始化过程导致失败
 *  - -2 非法url
 *  - -3 连接服务器失败或发送错误
 *  - -4 读数据其他错误,例如网络读写错误
 *  - -5 数据错误
 *  - -7 读取内容未结束时,对端服务器主动断开(发生在trunk模式下)
 *  - -8 在非chunk模式下，在长度有效情况下（长度len>0且len<maxlen）数据接收不完全
 *  - -10 参数不合法
 *
 *  @note pres只需初始化一次即可多次利用. 使用完毕后需调用uln_http_freeres释放资源.
**/
int uln_http_crawlpage_ms(const char* url,const char* ip,int maxlen,
                       uln_response_t* pres, int ntimeout, int flag);

/**
 *  自定义请求结构从网络抓取网页.
 *  注: 
 *  uln_request_t结构体中的m_url及m_ip并不起作用，需要利用函数参数url和ip.  
 *
 *  @param[in]  url      待抓取网页的url
 *  @param[in]  ip       待抓取网页服务器的ip地址
 *  @param[in]  maxlen   网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres     返回结构的指针
 *  @param[in]  ntimeout 超时时间
 *  @param[in]  flag     当flag & 0x1 !=0 时，只接收文本格式
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[in]  ereq     请求结构
 *  @param[out] pres     返回网页信息
 *  @return 操作结果
 *
 *  - 1 表示成功,详细信息将记录在pres结构中.
 *  - 2 表示网页被截断
 *  - -1 命令致命错误
 *  - -2 非法url
 *  - -3 连接服务器失败
 *  - -4 读数据失败
 *  - -5 数据错误
 *  - -7 读取内容尚未结束,对端服务器主动断开(发送在trunk模式下)
 *  - -8 在非chunk模式时,在长度有效情况下(长度len>0且len<maxlen)数据接收不完全
 *  - -10 输入参数不合法.
 *
 *  @note pres只需初始化一次即可多次利用. 使用完毕后需调用uln_http_freeres释放资源.
 *  @note uln_request_t结构体中的m_url及m_ip并不起作用，需要利用函数参数url和ip
 */ 
int uln_http_crawlpage_ex(const char* url, const char* ip, int maxlen,
                       uln_response_t* pres, int ntimeout, int flag, uln_request_t *ereq);

/**
 *  自定义请求结构从网络抓取网页.
 *  超时时间单位为毫秒
 *  注: 
 *  uln_request_t结构体中的m_url及m_ip并不起作用，需要利用函数参数url和ip.  
 *
 *  @param[in]  url      待抓取网页的url
 *  @param[in]  ip       待抓取网页服务器的ip地址
 *  @param[in]  maxlen   网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres     返回结构的指针
 *  @param[in]  ntimeout 超时时间，单位为毫秒
 *  @param[in]  flag     当flag & 0x1 !=0 时，只接收文本格式
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[in]  ereq     请求结构
 *  @param[out] pres     返回网页信息
 *  @return 操作结果
 *
 *  - 1 表示成功,详细信息将记录在pres结构中.
 *  - 2 表示网页被截断
 *  - -1 命令致命错误
 *  - -2 非法url
 *  - -3 连接服务器失败
 *  - -4 读数据失败
 *  - -5 数据错误
 *  - -7 读取内容尚未结束,对端服务器主动断开(发送在trunk模式下)
 *  - -8 在非chunk模式时,在长度有效情况下(长度len>0且len<maxlen)数据接收不完全
 *  - -10 输入参数不合法.
 *
 *  @note pres只需初始化一次即可多次利用. 使用完毕后需调用uln_http_freeres释放资源.
 *  @note uln_request_t结构体中的m_url及m_ip并不起作用，需要利用函数参数url和ip
 */ 
int uln_http_crawlpage_ms_ex(const char* url, const char* ip, int maxlen,
                       uln_response_t* pres, int ntimeout, int flag, uln_request_t *ereq);



/**
 *  默认结构检测网页是修改过，如果修改过，则抓取该网页
 *  
 *  @param[in]  url      待抓取网页的url
 *  @param[in]  ip       待抓取网页服务器的ip地址
 *  @param[in]  maxlen   网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres     返回结构的指针
 *  @param[in]  ntimeout 超时时间
 *  @param[in]  flag     当flag & 0x1 !=0 时，只接收文本格式
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[in]  lmt      上次修改过的字符串格式
 *  @param[in]  etag     etag
 *  @param[in]  orilen   原来的长度    
 *  @param[out] pres     返回网页信息
 *  @return 操作结果
 *  - 0 表示无修改
 *  - 1 表示有修改,抓取网页到pres中，详细信息将记录在pres结构中.
 *  - 2 表示页面被截断
 *  - -1 命令致命错误
 *  - -2 非法url
 *  - -3 连接服务器失败
 *  - -4 读数据失败
 *  - -5 数据错误
 *  - -7 读取内容信息尚未结束,对端服务器主动断开(trunk模式时)
 *  - -8 在非chunk模式时,在长度有效情况下(长度len>0且len<maxlen)数据接收不完全
 *  - -10 输入参数不合法
 *
 *  @note pres指针在使用完毕后需要调用::uln_http_freeres释放资源
 */  
int uln_http_checkpage(const char* url ,const char* ip, int maxlen,
                       uln_response_t* pres, int ntimeout, const int flag,
                       const char* lmt, const char* etag, const int orilen);

/**
 *  默认结构检测网页是修改过，如果修改过，则抓取该网页
 *  超时时间单位为毫秒
 *  
 *  @param[in]  url      待抓取网页的url
 *  @param[in]  ip       待抓取网页服务器的ip地址
 *  @param[in]  maxlen   网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres     返回结构的指针
 *  @param[in]  ntimeout 超时时间(超时时间单位为毫秒)
 *  @param[in]  flag     当flag & 0x1 !=0 时，只接收文本格式
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[in]  lmt      上次修改过的字符串格式
 *  @param[in]  etag     etag
 *  @param[in]  orilen   原来的长度    
 *  @param[out] pres     返回网页信息
 *  @return 操作结果
 *  - 0 表示无修改
 *  - 1 表示有修改,抓取网页到pres中，详细信息将记录在pres结构中.
 *  - -1 命令致命错误
 *  - 2 表示页面被截断
 *  - -2 非法url
 *  - -3 连接服务器失败
 *  - -4 读数据失败
 *  - -5 数据错误
 *  - -7 读取内容信息尚未结束,对端服务器主动断开(trunk模式时)
 *  - -8 在非chunk模式时,在长度有效情况下(长度len>0且len<maxlen)数据接收不完全
 *  - -10 输入参数不合法
 *
 *  @note pres指针在使用完毕后需要调用::uln_http_freeres释放资源
 */  
int uln_http_checkpage_ms(const char* url ,const char* ip, int maxlen,
                       uln_response_t* pres, int ntimeout, const int flag,
                       const char* lmt, const char* etag, const int orilen);

/**
 *  自定义请求结构检测网页是修改过，如果修改过，则抓取该网页
 *  
 *  @param[in]  url      待抓取网页的url
 *  @param[in]  ip       待抓取网页服务器的ip地址
 *  @param[in]  maxlen   网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres     返回结构的指针
 *  @param[in]  ntimeout 超时时间
 *  @param[in]  flag     当flag & 0x1 !=0 时，只接收文本格式
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[in]  lmt      上次修改过的字符串格式
 *  @param[in]  etag     etag
 *  @param[in]  orilen   原来的长度    
 *  @param[in]  ereq     请求结构   
 *  @param[out] pres     返回网页信息
 *  @return 操作结果
 *
 *  - 0 表示无修改
 *  - 1 表示有修改,抓取网页到pres中，详细信息将记录在pres结构中.
 *  - 2 表示页面被截断
 *  - -1 命令致命错误
 *  - -2 非法url
 *  - -3 连接服务器失败
 *  - -4 读数据失败
 *  - -5 数据错误
 *  - -7 读取内容尚未成功,对端服务器关闭(trunk mode)
 *  - -8 在非chunk模式时,在长度有效情况下(长度len>0且len<maxlen)数据接收不完全
 *  - -10 输入的参数不合法
 *
 *  @note pres指针在使用完毕后需要调用::uln_http_freeres释放资源
 */  
int uln_http_checkpage_ex(const char* url,const char* ip,int maxlen,
                       uln_response_t* pres, int ntimeout, const int flag,
                       const char* lmt, const char* etag, const int orilen, uln_request_t* ereq);

/**
 *  自定义请求结构检测网页是修改过，如果修改过，则抓取该网页
 *  超时单位为毫秒
 *  
 *  @param[in]  url      待抓取网页的url
 *  @param[in]  ip       待抓取网页服务器的ip地址
 *  @param[in]  maxlen   网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres     返回结构的指针
 *  @param[in]  ntimeout 超时时间(毫秒)
 *  @param[in]  flag     当flag & 0x1 !=0 时，只接收文本格式
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[in]  lmt      上次修改过的字符串格式
 *  @param[in]  etag     etag
 *  @param[in]  orilen   原来的长度    
 *  @param[in]  ereq     请求结构   
 *  @param[out] pres     返回网页信息
 *  @return 操作结果
 *
 *  - 0 表示无修改
 *  - 1 表示有修改,抓取网页到pres中，详细信息将记录在pres结构中.
 *  - 2 表示页面被截断
 *  - -1 命令致命错误
 *  - -2 非法url
 *  - -3 连接服务器失败
 *  - -4 读数据失败
 *  - -5 数据错误
 *  - -7 读取内容尚未成功,对端服务器关闭(trunk mode)
 *  - -8 在非chunk模式时,在长度有效情况下(长度len>0且len<maxlen)数据接收不完全
 *  - -10 输入的参数不合法
 *
 *  @note pres指针在使用完毕后需要调用::uln_http_freeres释放资源
 */  
int uln_http_checkpage_ms_ex(const char* url,const char* ip,int maxlen,
                       uln_response_t* pres, int ntimeout, const int flag,
                       const char* lmt, const char* etag, const int orilen, uln_request_t* ereq);

/**
 *  通过proxy从网络抓取网页
 *  
 *  @param[in]  url        待抓取网页的url,url请以http://开头，否则可能引发
 *  					   pres->m_status_code = 500错误（内部服务器错误)
 *                         或pres->m_status_code = 400 (解析请求出错)
 *  @param[in]  ip         待抓取网页服务器的ip地址
 *  @param[in]  maxlen     网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres       返回结构的指针
 *  @param[in]  ntimeout   超时时间
 *  @param[in]  flag       当flag & 0x1 !=0 时，只接收文本格式
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[in]  ereq       请求结构
 *  @param[in]  proxy_host proxy的主机名
 *  @param[in]  proxy_port proxy的端口号
 *  @param[out] pres       返回网页信息
 *  @return 操作结果
 *  - 1 表示返回信息头成功,详细信息将记录在pres结构中
 *  - 2 表示网页被截断
 *  - -1 命令错误，初始化过程导致失败
 *  - -2 非法url
 *  - -3 连接错误或发送错误
 *  - -4 无此状态
 *  - -5 数据错误
 *  - -6 其他错误 (来源可能在读取头信息失败,或读取内容信息失败)
 *  - -7 读取内容信息未结束,对端服务器主动断开(trunk mode)
 *  - -8 在非chunk模式时,在长度有效情况下(长度len>0且len<maxlen)数据接收不完全
 *  - -10 输入的参数不合法
 *
 *  @note 返回值为1与pres->m_status_code == 200同时成立才能认为网页内容抓取成功，
 *         如果返回code==500并且确认url没有问题，有可能是网络问题，可重复尝试；
 *  @note pres指针在使用完毕后需要调用::uln_http_freeres释放资源
 */
int uln_http_crawlpage_through_proxy(const char* url, const char* ip, int maxlen,
                uln_response_t* pres, int ntimeout, int flag,
                uln_request_t* ereq,
                const char* proxy_host, const int proxy_port);

/**
 *  通过proxy从网络抓取网页
 *  超时时间单位为毫秒
 *  
 *  @param[in]  url        待抓取网页的url,url请以http://开头，否则可能引发
 *  					   pres->m_status_code = 500错误（内部服务器错误)
 *                         或pres->m_status_code = 400 (解析请求出错)
 *  @param[in]  ip         待抓取网页服务器的ip地址
 *  @param[in]  maxlen     网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres       返回结构的指针
 *  @param[in]  ntimeout   超时时间(毫秒)
 *  @param[in]  flag       当flag & 0x1 !=0 时，只接收文本格式
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[in]  ereq       请求结构
 *  @param[in]  proxy_host proxy的主机名
 *  @param[in]  proxy_port proxy的端口号
 *  @param[out] pres       返回网页信息
 *  @return 操作结果
 *  - 1 表示返回信息头成功,详细信息将记录在pres结构中
 *  - 2 表示页面被截断
 *  - -1 命令错误，初始化过程导致失败
 *  - -2 非法url
 *  - -3 连接错误或发送错误
 *  - -4 无此状态
 *  - -5 数据错误
 *  - -6 其他错误 (来源可能在读取头信息失败,或读取内容信息失败)
 *  - -7 读取内容信息未结束,对端服务器主动断开(trunk mode)
 *  - -8 在非chunk模式时,在长度有效情况下(长度len>0且len<maxlen)数据接收不完全
 *  - -10 输入的参数不合法
 *
 *  @note 返回值为1与pres->m_status_code == 200同时成立才能认为网页内容抓取成功，
 *         如果返回code==500并且确认url没有问题，有可能是网络问题，可重复尝试；
 *  @note pres指针在使用完毕后需要调用::uln_http_freeres释放资源
 */
int uln_http_crawlpage_through_proxy_ms(const char* url, const char* ip, int maxlen,
                uln_response_t* pres, int ntimeout, int flag,
                uln_request_t* ereq,
                const char* proxy_host, const int proxy_port);

/**
 *  通过proxy检测网页是修改过，如果修改过，则抓取该网页
 *  
 *  @param[in]  url      待抓取网页的url, url需要以http://开头，否则会引起以下错误
 *  					  pres->m_status_code = 500错误（内部服务器错误)
 *                        pres->m_status_code = 400 (解析请求出错)
 *  @param[in]  ip       待抓取网页服务器的ip地址
 *  @param[in]  maxlen   网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres     返回结构的指针
 *  @param[in]  ntimeout 超时时间
 *  @param[in]  flag     当flag & 0x1 !=0 时，只接收文本格式
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[in]  lmt      上次修改过的字符串格式
 *  @param[in]  etag     etag
 *  @param[in]  orilen   原来的长度    
 *  @param[in]  ereq     请求结构   
 *  @param[in]  proxy_host proxy的主机名
 *  @param[in]  proxy_port proxy的端口号
 *  @param[out] pres     返回网页信息
 *  @return 操作结果
 *  - 0 表示无修改
 *  - 1 表示有修改,抓取网页到pres中，详细信息将记录在pres结构中.
 *  - 2 表示页面被截断
 *  - -1 命令致命错误
 *  - -2 非法url
 *  - -3 连接服务器失败
 *  - -4 读数据失败
 *  - -5 数据错误
 *  - -6 读取网页内容失败
 *  - -7 读取内容未完成,对端服务器主动断开(trunk mode)
 *  - -8 在非chunk模式时,在长度有效情况下(长度len>0且len<maxlen)数据接收不完全
 *  - -10 参数不合法
 *
 * @note 返回值为1与pres->m_status_code == 200同时成立才能认为抓取成功；
 * @note pres指针在使用完毕后需要调用::uln_http_freeres释放资源
 */
int uln_http_checkpage_through_proxy(const char* url, const char* ip, int maxlen,
                uln_response_t* pres, int ntimeout, const int flag,
                const char* lmt, const char* etag, const int orilen,
                uln_request_t*ereq, const char* proxy_host, const int proxy_port);

/**
 *  通过proxy检测网页是修改过，如果修改过，则抓取该网页
 *  超时时间单位为毫秒
 *  
 *  @param[in]  url      待抓取网页的url, url需要以http://开头，否则会引起以下错误
 *  					  pres->m_status_code = 500错误（内部服务器错误)
 *                        pres->m_status_code = 400 (解析请求出错)
 *  @param[in]  ip       待抓取网页服务器的ip地址
 *  @param[in]  maxlen   网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres     返回结构的指针
 *  @param[in]  ntimeout 超时时间(毫秒)
 *  @param[in]  flag     当flag & 0x1 !=0 时，只接收文本格式
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[in]  lmt      上次修改过的字符串格式
 *  @param[in]  etag     etag
 *  @param[in]  orilen   原来的长度    
 *  @param[in]  ereq     请求结构   
 *  @param[in]  proxy_host proxy的主机名
 *  @param[in]  proxy_port proxy的端口号
 *  @param[out] pres     返回网页信息
 *  @return 操作结果
 *  - 0 表示无修改
 *  - 1 表示有修改,抓取网页到pres中，详细信息将记录在pres结构中.
 *  - 2 表示页面被截断
 *  - -1 命令致命错误
 *  - -2 非法url
 *  - -3 连接服务器失败
 *  - -4 读数据失败
 *  - -5 数据错误
 *  - -6 读取网页内容失败
 *  - -7 读取内容未完成,对端服务器主动断开(trunk mode)
 *  - -8 在非chunk模式时,在长度有效情况下(长度len>0且len<maxlen)数据接收不完全
 *  - -10 参数不合法
 *
 * @note 返回值为1与pres->m_status_code == 200同时成立才能认为抓取成功；
 * @note pres指针在使用完毕后需要调用::uln_http_freeres释放资源
 */
int uln_http_checkpage_through_proxy_ms(const char* url, const char* ip, int maxlen,
                uln_response_t* pres, int ntimeout, const int flag,
                const char* lmt, const char* etag, const int orilen,
                uln_request_t*ereq, const char* proxy_host, const int proxy_port);

//////////////////////////////////////////////////////////////
//长度扩展后的接口..
//############################################################
//############################################################
//modified by zhangyan04@baidu.com
//修改的内容是将url长度从256增大到2048,请求长度从4096增大道8192
//后面所有增加的接口使用的请求结构体都是uln_request_ex2_t，返回结构体都是uln_response_ex2_t


/**
 * @brief 生成并初始化uln_response_ex2_t应答结构体. 
 *
 * @return  uln_response_ex2_t*, 应答结构体指针
 * @retval  非NULL，表示应答结构体指针, 若初始化成功
 * @retval  NULL, 若初始化成败
 * @see     uln_http_freeres_ex2()
 * @note    初始化时，会为m_buf字段开大小为ULN_DEFAULT_PAGESIZE大小的空间
**/
uln_response_ex2_t* uln_http_initres_ex2(void);


/**
 * @brief 释放应答结构体内存, 同时释放结构体内buf的内存.
 *
 * @param [in] pres   : uln_response_ex2_t* 待释放的结构体指针.
 * @return  void 
 * @see  uln_http_initres_ex2()
 * @note 若传入指针为空，不做任何事情
**/
void uln_http_freeres_ex2(uln_response_ex2_t *pres);


 /**
 * @brief 读取http头信息. 
 * http头的version、status_code、status_phrase存放在pres的相应字段，
 * 其它信息保存在pres->m_reshead中.
 *
 * @param [in]  sockfd   : int               socket句柄
 * @param [out] pres     : uln_response_ex2_t*   返回结构指针  
 * @param [in]  prl      : Rline*            缓冲区
 * @param [in]  ntimeout : int               超时时间
 * @return  int 操作结果
 * @retval   1  读取头部信息成功
 * @retval  -1  网络读取错误(超时或其他网络错误) 
 * @retval  -2  应答格式错误(返回头错误)
 * @retval  -3  传入参数不合法
 * @see   
 * @note  prl存储读到的数据,执行完此函数时,里面有可能还有未读的数据
**/
int uln_http_readhead_ex2(int sockfd, uln_response_ex2_t* pres, Rline *prl, int ntimeout);


 /**
 * @brief 读取http头信息. 
 * http头的version、status_code、status_phrase存放在pres的相应字段，
 * 其它信息保存在pres->m_reshead中.
 * 与uln_http_readhead_ex2的不同是：此处超时时间精度为毫秒
 *
 * @param [in]  sockfd   : int               socket句柄
 * @param [out] pres     : uln_response_ex2_t*   返回结构指针  
 * @param [in]  prl      : Rline*            缓冲区
 * @param [in]  ntimeout : int               超时时间
 * @return  int 操作结果
 * @retval   1  读取头部信息成功
 * @retval  -1  网络读取错误(超时或其他网络错误) 
 * @retval  -2  应答格式错误(返回头错误)
 * @retval  -3  传入参数不合法
 * @see   
 * @note  prl存储读到的数据,执行完此函数时,里面有可能还有未读的数据
**/
int uln_http_readhead_ms_ex2(int sockfd, uln_response_ex2_t* pres, Rline *prl, int ntimeout);


/**
 * @brief 读取http网页内容.
 *
 * @param [in]  sockfd   : int               socket句柄
 * @param [out] pres     : uln_response_ex2_t*   返回结构指针
 * @param [out] prl      : Rline*            缓冲区
 * @param [in]  maxlen   : int               从服务器一次读取的最大长度
 * @param [in]  ntimeout : int               超时时间(秒)
 * @return  int   操作结果
 * @retval  1     成功读取http内容
 * @retval  2     page被截断 (长度大于maxlen)
 * @retval  3     page没有全部读完
 * @retval -1     网络读取错误
 * @retval -3     数据格式错误
 * @retval -4     内存错误
 * @retval -7     trunk模式时,未接到末尾flag,对端服务器主动断开连接错误
 * @retval -8     读出page长度与头信息中的长度不一致
 * @retval -10    转入参数不合法
 * @see 
 * @note 
**/
int uln_http_readcontent_ex2(int sockfd, uln_response_ex2_t* pres, Rline *prl, int maxlen, int ntimeout);


/**
 * @brief 读取http网页内容.
 * 与uln_http_readcontent_ex2的不同是：此处超时时间单位为毫秒
 *
 * @param [in]  sockfd   : int               socket句柄
 * @param [out] pres     : uln_response_ex2_t*   返回结构指针
 * @param [out] prl      : Rline*            缓冲区
 * @param [in]  maxlen   : int               从服务器一次读取的最大长度
 * @param [in]  ntimeout : int               超时时间(毫秒)
 * @return  int   操作结果
 * @retval  1     成功读取http内容
 * @retval  2     page被截断 (长度大于maxlen)
 * @retval  3     page没有全部读完
 * @retval -1     网络读取错误
 * @retval -3     数据格式错误
 * @retval -4     内存错误
 * @retval -7     trunk模式时,未接到末尾flag,对端服务器主动断开连接错误
 * @retval -8     读出page长度与头信息中的长度不一致
 * @retval -10    转入参数不合法
 * @see 
 * @note 
**/
int uln_http_readcontent_ms_ex2(int sockfd, uln_response_ex2_t* pres, Rline *prl, int maxlen, int ntimeout);

/**
 * @brief 初始化请求结构体. 
 *
 * 此函数初始化的请求头信息有, 
 * Connection:close, Accept-Language:zh-cn,zh-tw,百度的User-agent等.
 * 请求方法是HTTP_GET
 * 
 * 传入的ip只在请求结构体中起保存作用，对url的抓取或检查不起作用. 可设为NULL.
 *
 * @param [in] url  : const char*  需要抓取或检查的url
 * @param [in] ip   : const char*  url相应的ip
 * @return  uln_request_ex2_t*         请求结构体指针
 * @retval  非NULL                 成功
 * @retval  NULL                   初始化不成功
 * @see 
 * @note    传入的ip只在请求结构体中起保存作用，对url的抓取或检查不起作用. 可设为NULL.
 **/
uln_request_ex2_t* uln_http_initreq_ex2(const char* url, const char* ip);

/**
 * @brief 释放请求结构体.
 *
 * @param [in] preq   : uln_request_ex2_t* 待释放的请求结构体指针
 * @return  void 
 * @retval  无
 * @see 
 * @note 
 **/
void uln_http_freereq_ex2(uln_request_ex2_t* preq);

/**
 * @brief 向已经连接的socket句柄发送HTTP请求 
 *
 * @param [in] sock       : const int         socket句柄
 * @param [in] preq       : uln_request_ex2_t*    请求结构体
 * @param [in] ntimeout   : int               超时时间(秒)
 * @return     int        操作结果 
 * @retval     1          success
 * @retval     -1         failed
 **/
int uln_http_sendreq_ex2(const int sock, uln_request_ex2_t* preq, int ntimeout);


/**
 * @brief 向已经连接的socket句柄发送HTTP请求 
 * 与uln_http_sendreq_ex2的不同在于：此处超时时间单位为毫秒
 *
 * @param [in] sock       : const int         socket句柄
 * @param [in] preq       : uln_request_ex2_t*    请求结构体
 * @param [in] ntimeout   : int               超时时间(毫秒)
 * @return     int        操作结果 
 * @retval     1          success
 * @retval     -1         failed
 **/
int uln_http_sendreq_ms_ex2(const int sock, uln_request_ex2_t* preq, int ntimeout);


/**
 *  自定义请求结构检测网页是修改过，如果修改过，则抓取该网页
 *  
 *  @param[in]  url      待抓取网页的url
 *  @param[in]  ip       待抓取网页服务器的ip地址
 *  @param[in]  maxlen   网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres     返回结构的指针
 *  @param[in]  ntimeout 超时时间
 *  @param[in]  flag     当flag & 0x1 !=0 时，只接收文本格式
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[in]  lmt      上次修改过的字符串格式
 *  @param[in]  etag     etag
 *  @param[in]  orilen   原来的长度    
 *  @param[in]  ereq     请求结构   
 *  @param[out] pres     返回网页信息
 *  @return 操作结果
 *
 *  - 0 表示无修改
 *  - 1 表示有修改,抓取网页到pres中，详细信息将记录在pres结构中.
 *  - 2 表示页面被截断
 *  - -1 命令致命错误
 *  - -2 非法url
 *  - -3 连接服务器失败
 *  - -4 读数据失败
 *  - -5 数据错误
 *  - -7 读取内容尚未成功,对端服务器关闭(trunk mode)
 *  - -8 在非chunk模式时,在长度有效情况下(长度len>0且len<maxlen)数据接收不完全
 *  - -10 输入的参数不合法
 *
 *  @note pres指针在使用完毕后需要调用::uln_http_freeres_ex2释放资源
 */  
int uln_http_checkpage_ex2(const char* url, const char* ip, int maxlen,
			      uln_response_ex2_t* pres, int ntimeout, const int flag,
			      const char* lmt, const char* etag, const int orilen, uln_request_ex2_t* ereq=NULL);


/**
 *  自定义请求结构检测网页是修改过，如果修改过，则抓取该网页
 *  超时单位为毫秒
 *  
 *  @param[in]  url      待抓取网页的url
 *  @param[in]  ip       待抓取网页服务器的ip地址
 *  @param[in]  maxlen   网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres     返回结构的指针
 *  @param[in]  ntimeout 超时时间(毫秒)
 *  @param[in]  flag     当flag & 0x1 !=0 时，只接收文本格式
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[in]  lmt      上次修改过的字符串格式
 *  @param[in]  etag     etag
 *  @param[in]  orilen   原来的长度    
 *  @param[in]  ereq     请求结构   
 *  @param[out] pres     返回网页信息
 *  @return 操作结果
 *
 *  - 0 表示无修改
 *  - 1 表示有修改,抓取网页到pres中，详细信息将记录在pres结构中.
 *  - 2 表示页面被截断
 *  - -1 命令致命错误
 *  - -2 非法url
 *  - -3 连接服务器失败
 *  - -4 读数据失败
 *  - -5 数据错误
 *  - -7 读取内容尚未成功,对端服务器关闭(trunk mode)
 *  - -8 在非chunk模式时,在长度有效情况下(长度len>0且len<maxlen)数据接收不完全
 *  - -10 输入的参数不合法
 *
 *  @note pres指针在使用完毕后需要调用::uln_http_freeres_ex2释放资源
 */  
int uln_http_checkpage_ms_ex2(const char* url, const char* ip, int maxlen,
				 uln_response_ex2_t* pres, int ntimeout, const int flag,
				 const char* lmt, const char* etag, const int orilen, uln_request_ex2_t* ereq=NULL);


/**
 *  自定义请求结构从网络抓取网页.
 *  注: 
 *  uln_request_ex2_t结构体中的m_url及m_ip并不起作用，需要利用函数参数url和ip.  
 *
 *  @param[in]  url      待抓取网页的url
 *  @param[in]  ip       待抓取网页服务器的ip地址
 *  @param[in]  maxlen   网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres     返回结构的指针
 *  @param[in]  ntimeout 超时时间
 *  @param[in]  flag     当flag & 0x1 !=0 时，只接收文本格式
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[in]  ereq     请求结构
 *  @param[out] pres     返回网页信息
 *  @return 操作结果
 *
 *  - 1 表示成功,详细信息将记录在pres结构中.
 *  - 2 表示页面被截断
 *  - -1 命令致命错误
 *  - -2 非法url
 *  - -3 连接服务器失败
 *  - -4 读数据失败
 *  - -5 数据错误
 *  - -7 读取内容尚未结束,对端服务器主动断开(发送在trunk模式下)
 *  - -8 在非chunk模式时,在长度有效情况下(长度len>0且len<maxlen)数据接收不完全
 *  - -10 输入参数不合法.
 *
 *  @note pres只需初始化一次即可多次利用. 使用完毕后需调用uln_http_freeres_ex2释放资源.
 *  @note uln_request_ex2_t结构体中的m_url及m_ip并不起作用，需要利用函数参数url和ip
 */ 

int uln_http_crawlpage_ex2(const char* url, const char* ip, int maxlen,
			      uln_response_ex2_t* pres, int ntimeout, int flag, uln_request_ex2_t* ereq=NULL);


/**
 *  自定义请求结构从网络抓取网页.
 *  超时时间单位为毫秒
 *  注: 
 *  uln_request_ex2_t结构体中的m_url及m_ip并不起作用，需要利用函数参数url和ip.  
 *
 *  @param[in]  url      待抓取网页的url
 *  @param[in]  ip       待抓取网页服务器的ip地址
 *  @param[in]  maxlen   网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres     返回结构的指针
 *  @param[in]  ntimeout 超时时间，单位为毫秒
 *  @param[in]  flag     当flag & 0x1 !=0 时，只接收文本格式
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[in]  ereq     请求结构
 *  @param[out] pres     返回网页信息
 *  @return 操作结果
 *
 *  - 1 表示成功,详细信息将记录在pres结构中.
 *  - 2 表示页面被截断
 *  - -1 命令致命错误
 *  - -2 非法url
 *  - -3 连接服务器失败
 *  - -4 读数据失败
 *  - -5 数据错误
 *  - -7 读取内容尚未结束,对端服务器主动断开(发送在trunk模式下)
 *  - -8 在非chunk模式时,在长度有效情况下(长度len>0且len<maxlen)数据接收不完全
 *  - -10 输入参数不合法.
 *
 *  @note pres只需初始化一次即可多次利用. 使用完毕后需调用uln_http_freeres_ex2释放资源.
 *  @note uln_request_ex2_t结构体中的m_url及m_ip并不起作用，需要利用函数参数url和ip
 */ 
int uln_http_crawlpage_ms_ex2(const char* url, const char* ip, int maxlen,
				 uln_response_ex2_t* pres, int ntimeout, int flag, uln_request_ex2_t* ereq=NULL);


/**
 *  通过proxy从网络抓取网页
 *  
 *  @param[in]  url        待抓取网页的url,url请以http://开头，否则可能引发
 *  					   pres->m_status_code = 500错误（内部服务器错误)
 *                         或pres->m_status_code = 400 (解析请求出错)
 *  @param[in]  ip         待抓取网页服务器的ip地址
 *  @param[in]  maxlen     网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres       返回结构的指针
 *  @param[in]  ntimeout   超时时间
 *  @param[in]  flag       当flag & 0x1 !=0 时，只接收文本格式
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[in]  ereq       请求结构
 *  @param[in]  proxy_host proxy的主机名
 *  @param[in]  proxy_port proxy的端口号
 *  @param[out] pres       返回网页信息
 *  @return 操作结果
 *  - 1 表示返回信息头成功,详细信息将记录在pres结构中
 *  - 2 表示页面被截断
 *  - -1 命令错误，初始化过程导致失败
 *  - -2 非法url
 *  - -3 连接错误或发送错误
 *  - -4 无此状态
 *  - -5 数据错误
 *  - -6 其他错误 (来源可能在读取头信息失败,或读取内容信息失败)
 *  - -7 读取内容信息未结束,对端服务器主动断开(trunk mode)
 *  - -8 在非chunk模式时,在长度有效情况下(长度len>0且len<maxlen)数据接收不完全
 *  - -10 输入的参数不合法
 *
 *  @note 返回值为1与pres->m_status_code == 200同时成立才能认为网页内容抓取成功，
 *         如果返回code==500并且确认url没有问题，有可能是网络问题，可重复尝试；
 *  @note pres指针在使用完毕后需要调用::uln_http_freeres_ex2释放资源
 */
int uln_http_crawlpage_through_proxy_ex2(const char* url, const char* ip, int maxlen,
					uln_response_ex2_t* pres, int ntimeout, int flag, uln_request_ex2_t* ereq,
					const char* proxy_host, const int proxy_port);

/**
 *  通过proxy从网络抓取网页
 *  超时时间单位为毫秒
 *  
 *  @param[in]  url        待抓取网页的url,url请以http://开头，否则可能引发
 *  					   pres->m_status_code = 500错误（内部服务器错误)
 *                         或pres->m_status_code = 400 (解析请求出错)
 *  @param[in]  ip         待抓取网页服务器的ip地址
 *  @param[in]  maxlen     网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres       返回结构的指针
 *  @param[in]  ntimeout   超时时间(毫秒)
 *  @param[in]  flag       当flag & 0x1 !=0 时，只接收文本格式
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[in]  ereq       请求结构
 *  @param[in]  proxy_host proxy的主机名
 *  @param[in]  proxy_port proxy的端口号
 *  @param[out] pres       返回网页信息
 *  @return 操作结果
 *  - 1 表示返回信息头成功,详细信息将记录在pres结构中
 *  - 2 表示页面被截断
 *  - -1 命令错误，初始化过程导致失败
 *  - -2 非法url
 *  - -3 连接错误或发送错误
 *  - -4 无此状态
 *  - -5 数据错误
 *  - -6 其他错误 (来源可能在读取头信息失败,或读取内容信息失败)
 *  - -7 读取内容信息未结束,对端服务器主动断开(trunk mode)
 *  - -8 在非chunk模式时,在长度有效情况下(长度len>0且len<maxlen)数据接收不完全
 *  - -10 输入的参数不合法
 *
 *  @note 返回值为1与pres->m_status_code == 200同时成立才能认为网页内容抓取成功，
 *         如果返回code==500并且确认url没有问题，有可能是网络问题，可重复尝试；
 *  @note pres指针在使用完毕后需要调用::uln_http_freeres_ex2释放资源
 */
int uln_http_crawlpage_through_proxy_ms_ex2(const char* url, const char* ip, int maxlen,
					   uln_response_ex2_t* pres, int ntimeout, int flag, uln_request_ex2_t* ereq,
					   const char* proxy_host, const int proxy_port);


/**
 *  通过proxy检测网页是修改过，如果修改过，则抓取该网页
 *  
 *  @param[in]  url      待抓取网页的url, url需要以http://开头，否则会引起以下错误
 *  					  pres->m_status_code = 500错误（内部服务器错误)
 *                        pres->m_status_code = 400 (解析请求出错)
 *  @param[in]  ip       待抓取网页服务器的ip地址
 *  @param[in]  maxlen   网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres     返回结构的指针
 *  @param[in]  ntimeout 超时时间
 *  @param[in]  flag     当flag & 0x1 !=0 时，只接收文本格式
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[in]  lmt      上次修改过的字符串格式
 *  @param[in]  etag     etag
 *  @param[in]  orilen   原来的长度    
 *  @param[in]  ereq     请求结构   
 *  @param[in]  proxy_host proxy的主机名
 *  @param[in]  proxy_port proxy的端口号
 *  @param[out] pres     返回网页信息
 *  @return 操作结果
 *  - 0 表示无修改
 *  - 1 表示有修改,抓取网页到pres中，详细信息将记录在pres结构中.
 *  - 2 表示页面被截断
 *  - -1 命令致命错误
 *  - -2 非法url
 *  - -3 连接服务器失败
 *  - -4 读数据失败
 *  - -5 数据错误
 *  - -6 读取网页内容失败
 *  - -7 读取内容未完成,对端服务器主动断开(trunk mode)
 *  - -8 在非chunk模式时,在长度有效情况下(长度len>0且len<maxlen)数据接收不完全
 *  - -10 参数不合法
 *
 * @note 返回值为1与pres->m_status_code == 200同时成立才能认为抓取成功；
 * @note pres指针在使用完毕后需要调用::uln_http_freeres_ex2释放资源
 */
int uln_http_checkpage_through_proxy_ex2(const char* url, const char* ip, int maxlen,
					uln_response_ex2_t* pres, int ntimeout, const int flag,
					const char* lmt, const char* etag, const int orilen, uln_request_ex2_t* ereq,
					const char* proxy_host, const int proxy_port);



/**
 *  通过proxy检测网页是修改过，如果修改过，则抓取该网页
 *  超时时间单位为毫秒
 *  
 *  @param[in]  url      待抓取网页的url, url需要以http://开头，否则会引起以下错误
 *  					  pres->m_status_code = 500错误（内部服务器错误)
 *                        pres->m_status_code = 400 (解析请求出错)
 *  @param[in]  ip       待抓取网页服务器的ip地址
 *  @param[in]  maxlen   网页的最大长度,如果网页大于这个长度,将被截断     
 *  @param[in]  pres     返回结构的指针
 *  @param[in]  ntimeout 超时时间(毫秒)
 *  @param[in]  flag     当flag & 0x1 !=0 时，只接收文本格式
 *                       (由于历史原因，flag & 0x1 != 0，还会接收其它格式内容)
 *  @param[in]  lmt      上次修改过的字符串格式
 *  @param[in]  etag     etag
 *  @param[in]  orilen   原来的长度    
 *  @param[in]  ereq     请求结构   
 *  @param[in]  proxy_host proxy的主机名
 *  @param[in]  proxy_port proxy的端口号
 *  @param[out] pres     返回网页信息
 *  @return 操作结果
 *  - 0 表示无修改
 *  - 1 表示有修改,抓取网页到pres中，详细信息将记录在pres结构中.
 *  - 2 表示页面被截断
 *  - -1 命令致命错误
 *  - -2 非法url
 *  - -3 连接服务器失败
 *  - -4 读数据失败
 *  - -5 数据错误
 *  - -6 读取网页内容失败
 *  - -7 读取内容未完成,对端服务器主动断开(trunk mode)
 *  - -8 在非chunk模式时,在长度有效情况下(长度len>0且len<maxlen)数据接收不完全
 *  - -10 参数不合法
 *
 * @note 返回值为1与pres->m_status_code == 200同时成立才能认为抓取成功；
 * @note pres指针在使用完毕后需要调用::uln_http_freeres_ex2释放资源
 */
int uln_http_checkpage_through_proxy_ms_ex2(const char* url, const char* ip, int maxlen,
					   uln_response_ex2_t* pres, int ntimeout, const int flag,
					   const char* lmt, const char* etag, const int orilen, uln_request_ex2_t* ereq,
					   const char* proxy_host, const int proxy_port);



#endif
