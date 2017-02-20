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
const unsigned int ULN_MAX_LINE_SIZE_EX2 = 6144; //����_ex2�ӿ�ʹ�ø������л�����.
const unsigned int ULN_MAX_HEAD_COUNT = 64; //http��Ӧ��(key,value)����..
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
    int            m_status_code;         ///< ״̬��, ��200,404��
    char           m_version[16];         ///< HTTP�汾, ��1.1
    char           m_status_phrase[128];  ///< ״̬��Ϣ����OK
    uln_vector_t*  m_reshead;             ///< ����ͷ��Ϣ
                           
    char*          m_buf;                 ///< ҳ�����ݴ洢buffer
    unsigned int   m_size;                ///< buffer�Ĵ�С
    unsigned int   m_len;                 ///< ҳ�泤��

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
    http_method_t   m_method;                 ///< ���󷽷�����GET, POST��
    char            m_url[ULN_URL_LENGTH];    ///< �����URL,��crawl_page_ex��check_page_ex�У���������.
    char            m_ip[ULN_IP_LENGTH];      ///< �����IP, ��crawl_page_ex��check_page_ex�У���������.
    uln_vector_t*   m_req_head;               ///< ��ϸ������ͷ��Ϣ
} uln_request_t;

//////////////////////////////////////////////////////////////
//������չ��Ľṹ..
//modified by zhangyan04@baidu.com
//just have extended url length:-)
typedef struct ULN_RESPONSE_EX2_T {
    int            m_status_code;         ///< ״̬��, ��200,404��
    char           m_version[16];         ///< HTTP�汾, ��1.1
    char           m_status_phrase[128];  ///< ״̬��Ϣ����OK
    uln_vector_ex2_t*  m_reshead;             ///< ����ͷ��Ϣ
                           
    char*          m_buf;                 ///< ҳ�����ݴ洢buffer
    unsigned int   m_size;                ///< buffer�Ĵ�С
    unsigned int   m_len;                 ///< ҳ�泤��

} uln_response_ex2_t;

typedef struct ULN_REQUEST_EX2_T {
    http_method_t   m_method;                 ///< ���󷽷�����GET, POST��
    char            m_url[ULN_URL_LENGTH_EX2];    ///< �����URL,��crawl_page_ex2��check_page_ex2�У���������.
    char            m_ip[ULN_IP_LENGTH];      ///< �����IP, ��crawl_page_ex2��check_page_ex2�У���������.
    uln_vector_ex2_t*   m_req_head;               ///< ��ϸ������ͷ��Ϣ
} uln_request_ex2_t;

/**
 * @brief ���ɲ���ʼ��uln_response_tӦ��ṹ��. 
 *
 * @return  uln_response_t*, Ӧ��ṹ��ָ��
 * @retval  ��NULL����ʾӦ��ṹ��ָ��, ����ʼ���ɹ�
 * @retval  NULL, ����ʼ���ɰ�
 * @see     uln_http_freeres()
 * @note    ��ʼ��ʱ����Ϊm_buf�ֶο���СΪULN_DEFAULT_PAGESIZE��С�Ŀռ�
 * @author wangjg
 * @date 2007/12/27 13:49:18
**/
uln_response_t* uln_http_initres(void);

/**
 * @brief �ͷ�Ӧ��ṹ���ڴ�, ͬʱ�ͷŽṹ����buf���ڴ�.
 *
 * @param [in] pres   : uln_response_t* ���ͷŵĽṹ��ָ��.
 * @return  void 
 * @see  uln_http_initres()
 * @note ������ָ��Ϊ�գ������κ�����
 * @author wangjg
 * @date 2007/12/27 17:09:22
**/
void uln_http_freeres(uln_response_t *pres);


 /**
 * @brief ��ȡhttpͷ��Ϣ. 
 * httpͷ��version��status_code��status_phrase�����pres����Ӧ�ֶΣ�
 * ������Ϣ������pres->m_reshead��.
 *
 * @param [in]  sockfd   : int               socket���
 * @param [out] pres     : uln_response_t*   ���ؽṹָ��  
 * @param [in]  prl      : Rline*            ������
 * @param [in]  ntimeout : int               ��ʱʱ��
 * @return  int �������
 * @retval   1  ��ȡͷ����Ϣ�ɹ�
 * @retval  -1  �����ȡ����(��ʱ�������������) 
 * @retval  -2  Ӧ���ʽ����(����ͷ����)
 * @retval  -3  ����������Ϸ�
 * @see   
 * @note  prl�洢����������,ִ����˺���ʱ,�����п��ܻ���δ��������
 * @author wangjg
 * @date 2007/12/27 17:20:46
**/
int uln_http_readhead(int sockfd, uln_response_t* pres, Rline *prl, int ntimeout);

 /**
 * @brief ��ȡhttpͷ��Ϣ. 
 * httpͷ��version��status_code��status_phrase�����pres����Ӧ�ֶΣ�
 * ������Ϣ������pres->m_reshead��.
 * ��uln_http_readhead�Ĳ�ͬ�ǣ��˴���ʱʱ�侫��Ϊ����
 *
 * @param [in]  sockfd   : int               socket���
 * @param [out] pres     : uln_response_t*   ���ؽṹָ��  
 * @param [in]  prl      : Rline*            ������
 * @param [in]  ntimeout : int               ��ʱʱ��
 * @return  int �������
 * @retval   1  ��ȡͷ����Ϣ�ɹ�
 * @retval  -1  �����ȡ����(��ʱ�������������) 
 * @retval  -2  Ӧ���ʽ����(����ͷ����)
 * @retval  -3  ����������Ϸ�
 * @see   
 * @note  prl�洢����������,ִ����˺���ʱ,�����п��ܻ���δ��������
 * @author gonglei 
 * @date 2008/12/30
**/
int uln_http_readhead_ms(int sockfd, uln_response_t* pres, Rline *prl, int ntimeout);

/**
 * @brief �������ӵ�socket�������http����.
 *
 * @param [in] sock       : const int         socket���
 * @param [in] preq       : uln_request_t*    ����ṹ��
 * @param [in] ntimeout   : int               ��ʱʱ��(��)
 * @return     int        �������
 * @retval     1          success
 * @retval     -1         failed
**/
int uln_http_sendreq(const int sock, uln_request_t* preq, int ntimeout);

/**
 * @brief �������ӵ�socket�������http����.
 * ��uln_http_sendreq�Ĳ�ͬ�ǣ��˴���ʱʱ�䵥λΪ����
 *
 * @param [in] sock       : const int         socket���
 * @param [in] preq       : uln_request_t*    ����ṹ��
 * @param [in] ntimeout   : int               ��ʱʱ��(����)
 * @return     int        �������
 * @retval     1          success
 * @retval     -1         failed
**/
int uln_http_sendreq_ms(const int sock, uln_request_t* preq, int ntimeout);

/**
 * @brief ��ȡhttp��ҳ����.
 *
 * @param [in]  sockfd   : int               socket���
 * @param [out] pres     : uln_response_t*   ���ؽṹָ��
 * @param [out] prl      : Rline*            ������
 * @param [in]  maxlen   : int               �ӷ�����һ�ζ�ȡ����󳤶�
 * @param [in]  ntimeout : int               ��ʱʱ��(��)
 * @return  int   �������
 * @retval  1     �ɹ���ȡhttp����
 * @retval  2     page���ض� (���ȴ���maxlen)
 * @retval  3     pageû��ȫ������
 * @retval -1     �����ȡ����
 * @retval -3     ���ݸ�ʽ����
 * @retval -4     �ڴ����
 * @retval -7     trunkģʽʱ,δ�ӵ�ĩβflag,�Զ˷����������Ͽ����Ӵ���
 * @retval -8     ����page������ͷ��Ϣ�еĳ��Ȳ�һ��
 * @retval -10    ת��������Ϸ�
 * @see 
 * @note 
 * @author wangjg
 * @date 2008/01/02 10:07:42
**/
int uln_http_readcontent(int sockfd, uln_response_t* pres, Rline *prl, int maxlen, int ntimeout);

/**
 * @brief ��ȡhttp��ҳ����.
 * ��uln_http_readcontent�Ĳ�ͬ�ǣ��˴���ʱʱ�䵥λΪ����
 *
 * @param [in]  sockfd   : int               socket���
 * @param [out] pres     : uln_response_t*   ���ؽṹָ��
 * @param [out] prl      : Rline*            ������
 * @param [in]  maxlen   : int               �ӷ�����һ�ζ�ȡ����󳤶�
 * @param [in]  ntimeout : int               ��ʱʱ��(����)
 * @return  int   �������
 * @retval  1     �ɹ���ȡhttp����
 * @retval  2     page���ض� (���ȴ���maxlen)
 * @retval  3     pageû��ȫ������
 * @retval -1     �����ȡ����
 * @retval -3     ���ݸ�ʽ����
 * @retval -4     �ڴ����
 * @retval -7     trunkģʽʱ,δ�ӵ�ĩβflag,�Զ˷����������Ͽ����Ӵ���
 * @retval -8     ����page������ͷ��Ϣ�еĳ��Ȳ�һ��
 * @retval -10    ת��������Ϸ�
 * @see 
 * @note 
 * @author gonglei 
 * @date 2008/12/30
**/
int uln_http_readcontent_ms(int sockfd, uln_response_t* pres, Rline *prl, int maxlen, int ntimeout);

/**
 * @brief ��ʼ������ṹ��. 
 *
 * �˺�����ʼ��������ͷ��Ϣ��, 
 * Connection:close, Accept-Language:zh-cn,zh-tw,�ٶȵ�User-agent��.
 * ���󷽷���HTTP_GET
 * 
 * �����ipֻ������ṹ�����𱣴����ã���url��ץȡ���鲻������. ����ΪNULL.
 *
 * @param [in] url  : const char*  ��Ҫץȡ�����url
 * @param [in] ip   : const char*  url��Ӧ��ip
 * @return  uln_request_t*         ����ṹ��ָ��
 * @retval  ��NULL                 �ɹ�
 * @retval  NULL                   ��ʼ�����ɹ�
 * @see 
 * @note    �����ipֻ������ṹ�����𱣴����ã���url��ץȡ���鲻������. ����ΪNULL.
 * @author wangjg
 * @date 2008/01/02 17:27:31
**/
uln_request_t* uln_http_initreq(const char* url, const char* ip);


/**
 * @brief �ͷ�����ṹ��.
 *
 * @param [in] preq   : uln_request_t* ���ͷŵ�����ṹ��ָ��
 * @return  void 
 * @retval  ��
 * @see 
 * @note 
 * @author wangjg
 * @date 2008/01/03 10:39:30
**/
void uln_http_freereq(uln_request_t *preq);


/**
 *  Ĭ������ṹ������ץȡ��ҳ
 *  
 *  @param[in]  url      ��ץȡ��ҳ��url
 *  @param[in]  ip       ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen   ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres     ���ؽṹ��ָ��
 *  @param[in]  ntimeout ��ʱʱ��,����Ϊ��λ
 *  @param[in]  flag     ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ.
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[out] pres     ������ҳ��Ϣ
 *  @return �������
 *  - 1 ��ʾ�ɹ�,��ϸ��Ϣ����¼��pres�ṹ��.
 *  - 2 ��ʾ��ҳ���ض�
 *  - -1 ������󣬳�ʼ�����̵���ʧ��
 *  - -2 �Ƿ�url
 *  - -3 ���ӷ�����ʧ�ܻ��ʹ���
 *  - -4 ��������������,���������д����
 *  - -5 ���ݴ���
 *  - -7 ��ȡ����δ����ʱ,�Զ˷����������Ͽ�(������trunkģʽ��)
 *  - -8 �ڷ�chunkģʽ�£��ڳ�����Ч����£�����len>0��len<maxlen�����ݽ��ղ���ȫ
 *  - -10 �������Ϸ�
 *
 *  @note presֻ���ʼ��һ�μ��ɶ������. ʹ����Ϻ������uln_http_freeres�ͷ���Դ.
**/
int uln_http_crawlpage(const char* url,const char* ip,int maxlen,
                       uln_response_t* pres, int ntimeout, int flag);

/**
 *  Ĭ������ṹ������ץȡ��ҳ
 *  ��ʱʱ�䵥λΪ����
 * 
 *  @param[in]  url      ��ץȡ��ҳ��url
 *  @param[in]  ip       ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen   ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres     ���ؽṹ��ָ��
 *  @param[in]  ntimeout ��ʱʱ��,�Ժ���Ϊ��λ
 *  @param[in]  flag     ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ.
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[out] pres     ������ҳ��Ϣ
 *  @return �������
 *  - 1 ��ʾ�ɹ�,��ϸ��Ϣ����¼��pres�ṹ��.
 *  - 2 ��ʾ��ҳ���ض�
 *  - -1 ������󣬳�ʼ�����̵���ʧ��
 *  - -2 �Ƿ�url
 *  - -3 ���ӷ�����ʧ�ܻ��ʹ���
 *  - -4 ��������������,���������д����
 *  - -5 ���ݴ���
 *  - -7 ��ȡ����δ����ʱ,�Զ˷����������Ͽ�(������trunkģʽ��)
 *  - -8 �ڷ�chunkģʽ�£��ڳ�����Ч����£�����len>0��len<maxlen�����ݽ��ղ���ȫ
 *  - -10 �������Ϸ�
 *
 *  @note presֻ���ʼ��һ�μ��ɶ������. ʹ����Ϻ������uln_http_freeres�ͷ���Դ.
**/
int uln_http_crawlpage_ms(const char* url,const char* ip,int maxlen,
                       uln_response_t* pres, int ntimeout, int flag);

/**
 *  �Զ�������ṹ������ץȡ��ҳ.
 *  ע: 
 *  uln_request_t�ṹ���е�m_url��m_ip���������ã���Ҫ���ú�������url��ip.  
 *
 *  @param[in]  url      ��ץȡ��ҳ��url
 *  @param[in]  ip       ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen   ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres     ���ؽṹ��ָ��
 *  @param[in]  ntimeout ��ʱʱ��
 *  @param[in]  flag     ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[in]  ereq     ����ṹ
 *  @param[out] pres     ������ҳ��Ϣ
 *  @return �������
 *
 *  - 1 ��ʾ�ɹ�,��ϸ��Ϣ����¼��pres�ṹ��.
 *  - 2 ��ʾ��ҳ���ض�
 *  - -1 ������������
 *  - -2 �Ƿ�url
 *  - -3 ���ӷ�����ʧ��
 *  - -4 ������ʧ��
 *  - -5 ���ݴ���
 *  - -7 ��ȡ������δ����,�Զ˷����������Ͽ�(������trunkģʽ��)
 *  - -8 �ڷ�chunkģʽʱ,�ڳ�����Ч�����(����len>0��len<maxlen)���ݽ��ղ���ȫ
 *  - -10 ����������Ϸ�.
 *
 *  @note presֻ���ʼ��һ�μ��ɶ������. ʹ����Ϻ������uln_http_freeres�ͷ���Դ.
 *  @note uln_request_t�ṹ���е�m_url��m_ip���������ã���Ҫ���ú�������url��ip
 */ 
int uln_http_crawlpage_ex(const char* url, const char* ip, int maxlen,
                       uln_response_t* pres, int ntimeout, int flag, uln_request_t *ereq);

/**
 *  �Զ�������ṹ������ץȡ��ҳ.
 *  ��ʱʱ�䵥λΪ����
 *  ע: 
 *  uln_request_t�ṹ���е�m_url��m_ip���������ã���Ҫ���ú�������url��ip.  
 *
 *  @param[in]  url      ��ץȡ��ҳ��url
 *  @param[in]  ip       ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen   ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres     ���ؽṹ��ָ��
 *  @param[in]  ntimeout ��ʱʱ�䣬��λΪ����
 *  @param[in]  flag     ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[in]  ereq     ����ṹ
 *  @param[out] pres     ������ҳ��Ϣ
 *  @return �������
 *
 *  - 1 ��ʾ�ɹ�,��ϸ��Ϣ����¼��pres�ṹ��.
 *  - 2 ��ʾ��ҳ���ض�
 *  - -1 ������������
 *  - -2 �Ƿ�url
 *  - -3 ���ӷ�����ʧ��
 *  - -4 ������ʧ��
 *  - -5 ���ݴ���
 *  - -7 ��ȡ������δ����,�Զ˷����������Ͽ�(������trunkģʽ��)
 *  - -8 �ڷ�chunkģʽʱ,�ڳ�����Ч�����(����len>0��len<maxlen)���ݽ��ղ���ȫ
 *  - -10 ����������Ϸ�.
 *
 *  @note presֻ���ʼ��һ�μ��ɶ������. ʹ����Ϻ������uln_http_freeres�ͷ���Դ.
 *  @note uln_request_t�ṹ���е�m_url��m_ip���������ã���Ҫ���ú�������url��ip
 */ 
int uln_http_crawlpage_ms_ex(const char* url, const char* ip, int maxlen,
                       uln_response_t* pres, int ntimeout, int flag, uln_request_t *ereq);



/**
 *  Ĭ�Ͻṹ�����ҳ���޸Ĺ�������޸Ĺ�����ץȡ����ҳ
 *  
 *  @param[in]  url      ��ץȡ��ҳ��url
 *  @param[in]  ip       ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen   ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres     ���ؽṹ��ָ��
 *  @param[in]  ntimeout ��ʱʱ��
 *  @param[in]  flag     ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[in]  lmt      �ϴ��޸Ĺ����ַ�����ʽ
 *  @param[in]  etag     etag
 *  @param[in]  orilen   ԭ���ĳ���    
 *  @param[out] pres     ������ҳ��Ϣ
 *  @return �������
 *  - 0 ��ʾ���޸�
 *  - 1 ��ʾ���޸�,ץȡ��ҳ��pres�У���ϸ��Ϣ����¼��pres�ṹ��.
 *  - 2 ��ʾҳ�汻�ض�
 *  - -1 ������������
 *  - -2 �Ƿ�url
 *  - -3 ���ӷ�����ʧ��
 *  - -4 ������ʧ��
 *  - -5 ���ݴ���
 *  - -7 ��ȡ������Ϣ��δ����,�Զ˷����������Ͽ�(trunkģʽʱ)
 *  - -8 �ڷ�chunkģʽʱ,�ڳ�����Ч�����(����len>0��len<maxlen)���ݽ��ղ���ȫ
 *  - -10 ����������Ϸ�
 *
 *  @note presָ����ʹ����Ϻ���Ҫ����::uln_http_freeres�ͷ���Դ
 */  
int uln_http_checkpage(const char* url ,const char* ip, int maxlen,
                       uln_response_t* pres, int ntimeout, const int flag,
                       const char* lmt, const char* etag, const int orilen);

/**
 *  Ĭ�Ͻṹ�����ҳ���޸Ĺ�������޸Ĺ�����ץȡ����ҳ
 *  ��ʱʱ�䵥λΪ����
 *  
 *  @param[in]  url      ��ץȡ��ҳ��url
 *  @param[in]  ip       ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen   ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres     ���ؽṹ��ָ��
 *  @param[in]  ntimeout ��ʱʱ��(��ʱʱ�䵥λΪ����)
 *  @param[in]  flag     ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[in]  lmt      �ϴ��޸Ĺ����ַ�����ʽ
 *  @param[in]  etag     etag
 *  @param[in]  orilen   ԭ���ĳ���    
 *  @param[out] pres     ������ҳ��Ϣ
 *  @return �������
 *  - 0 ��ʾ���޸�
 *  - 1 ��ʾ���޸�,ץȡ��ҳ��pres�У���ϸ��Ϣ����¼��pres�ṹ��.
 *  - -1 ������������
 *  - 2 ��ʾҳ�汻�ض�
 *  - -2 �Ƿ�url
 *  - -3 ���ӷ�����ʧ��
 *  - -4 ������ʧ��
 *  - -5 ���ݴ���
 *  - -7 ��ȡ������Ϣ��δ����,�Զ˷����������Ͽ�(trunkģʽʱ)
 *  - -8 �ڷ�chunkģʽʱ,�ڳ�����Ч�����(����len>0��len<maxlen)���ݽ��ղ���ȫ
 *  - -10 ����������Ϸ�
 *
 *  @note presָ����ʹ����Ϻ���Ҫ����::uln_http_freeres�ͷ���Դ
 */  
int uln_http_checkpage_ms(const char* url ,const char* ip, int maxlen,
                       uln_response_t* pres, int ntimeout, const int flag,
                       const char* lmt, const char* etag, const int orilen);

/**
 *  �Զ�������ṹ�����ҳ���޸Ĺ�������޸Ĺ�����ץȡ����ҳ
 *  
 *  @param[in]  url      ��ץȡ��ҳ��url
 *  @param[in]  ip       ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen   ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres     ���ؽṹ��ָ��
 *  @param[in]  ntimeout ��ʱʱ��
 *  @param[in]  flag     ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[in]  lmt      �ϴ��޸Ĺ����ַ�����ʽ
 *  @param[in]  etag     etag
 *  @param[in]  orilen   ԭ���ĳ���    
 *  @param[in]  ereq     ����ṹ   
 *  @param[out] pres     ������ҳ��Ϣ
 *  @return �������
 *
 *  - 0 ��ʾ���޸�
 *  - 1 ��ʾ���޸�,ץȡ��ҳ��pres�У���ϸ��Ϣ����¼��pres�ṹ��.
 *  - 2 ��ʾҳ�汻�ض�
 *  - -1 ������������
 *  - -2 �Ƿ�url
 *  - -3 ���ӷ�����ʧ��
 *  - -4 ������ʧ��
 *  - -5 ���ݴ���
 *  - -7 ��ȡ������δ�ɹ�,�Զ˷������ر�(trunk mode)
 *  - -8 �ڷ�chunkģʽʱ,�ڳ�����Ч�����(����len>0��len<maxlen)���ݽ��ղ���ȫ
 *  - -10 ����Ĳ������Ϸ�
 *
 *  @note presָ����ʹ����Ϻ���Ҫ����::uln_http_freeres�ͷ���Դ
 */  
int uln_http_checkpage_ex(const char* url,const char* ip,int maxlen,
                       uln_response_t* pres, int ntimeout, const int flag,
                       const char* lmt, const char* etag, const int orilen, uln_request_t* ereq);

/**
 *  �Զ�������ṹ�����ҳ���޸Ĺ�������޸Ĺ�����ץȡ����ҳ
 *  ��ʱ��λΪ����
 *  
 *  @param[in]  url      ��ץȡ��ҳ��url
 *  @param[in]  ip       ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen   ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres     ���ؽṹ��ָ��
 *  @param[in]  ntimeout ��ʱʱ��(����)
 *  @param[in]  flag     ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[in]  lmt      �ϴ��޸Ĺ����ַ�����ʽ
 *  @param[in]  etag     etag
 *  @param[in]  orilen   ԭ���ĳ���    
 *  @param[in]  ereq     ����ṹ   
 *  @param[out] pres     ������ҳ��Ϣ
 *  @return �������
 *
 *  - 0 ��ʾ���޸�
 *  - 1 ��ʾ���޸�,ץȡ��ҳ��pres�У���ϸ��Ϣ����¼��pres�ṹ��.
 *  - 2 ��ʾҳ�汻�ض�
 *  - -1 ������������
 *  - -2 �Ƿ�url
 *  - -3 ���ӷ�����ʧ��
 *  - -4 ������ʧ��
 *  - -5 ���ݴ���
 *  - -7 ��ȡ������δ�ɹ�,�Զ˷������ر�(trunk mode)
 *  - -8 �ڷ�chunkģʽʱ,�ڳ�����Ч�����(����len>0��len<maxlen)���ݽ��ղ���ȫ
 *  - -10 ����Ĳ������Ϸ�
 *
 *  @note presָ����ʹ����Ϻ���Ҫ����::uln_http_freeres�ͷ���Դ
 */  
int uln_http_checkpage_ms_ex(const char* url,const char* ip,int maxlen,
                       uln_response_t* pres, int ntimeout, const int flag,
                       const char* lmt, const char* etag, const int orilen, uln_request_t* ereq);

/**
 *  ͨ��proxy������ץȡ��ҳ
 *  
 *  @param[in]  url        ��ץȡ��ҳ��url,url����http://��ͷ�������������
 *  					   pres->m_status_code = 500�����ڲ�����������)
 *                         ��pres->m_status_code = 400 (�����������)
 *  @param[in]  ip         ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen     ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres       ���ؽṹ��ָ��
 *  @param[in]  ntimeout   ��ʱʱ��
 *  @param[in]  flag       ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[in]  ereq       ����ṹ
 *  @param[in]  proxy_host proxy��������
 *  @param[in]  proxy_port proxy�Ķ˿ں�
 *  @param[out] pres       ������ҳ��Ϣ
 *  @return �������
 *  - 1 ��ʾ������Ϣͷ�ɹ�,��ϸ��Ϣ����¼��pres�ṹ��
 *  - 2 ��ʾ��ҳ���ض�
 *  - -1 ������󣬳�ʼ�����̵���ʧ��
 *  - -2 �Ƿ�url
 *  - -3 ���Ӵ�����ʹ���
 *  - -4 �޴�״̬
 *  - -5 ���ݴ���
 *  - -6 �������� (��Դ�����ڶ�ȡͷ��Ϣʧ��,���ȡ������Ϣʧ��)
 *  - -7 ��ȡ������Ϣδ����,�Զ˷����������Ͽ�(trunk mode)
 *  - -8 �ڷ�chunkģʽʱ,�ڳ�����Ч�����(����len>0��len<maxlen)���ݽ��ղ���ȫ
 *  - -10 ����Ĳ������Ϸ�
 *
 *  @note ����ֵΪ1��pres->m_status_code == 200ͬʱ����������Ϊ��ҳ����ץȡ�ɹ���
 *         �������code==500����ȷ��urlû�����⣬�п������������⣬���ظ����ԣ�
 *  @note presָ����ʹ����Ϻ���Ҫ����::uln_http_freeres�ͷ���Դ
 */
int uln_http_crawlpage_through_proxy(const char* url, const char* ip, int maxlen,
                uln_response_t* pres, int ntimeout, int flag,
                uln_request_t* ereq,
                const char* proxy_host, const int proxy_port);

/**
 *  ͨ��proxy������ץȡ��ҳ
 *  ��ʱʱ�䵥λΪ����
 *  
 *  @param[in]  url        ��ץȡ��ҳ��url,url����http://��ͷ�������������
 *  					   pres->m_status_code = 500�����ڲ�����������)
 *                         ��pres->m_status_code = 400 (�����������)
 *  @param[in]  ip         ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen     ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres       ���ؽṹ��ָ��
 *  @param[in]  ntimeout   ��ʱʱ��(����)
 *  @param[in]  flag       ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[in]  ereq       ����ṹ
 *  @param[in]  proxy_host proxy��������
 *  @param[in]  proxy_port proxy�Ķ˿ں�
 *  @param[out] pres       ������ҳ��Ϣ
 *  @return �������
 *  - 1 ��ʾ������Ϣͷ�ɹ�,��ϸ��Ϣ����¼��pres�ṹ��
 *  - 2 ��ʾҳ�汻�ض�
 *  - -1 ������󣬳�ʼ�����̵���ʧ��
 *  - -2 �Ƿ�url
 *  - -3 ���Ӵ�����ʹ���
 *  - -4 �޴�״̬
 *  - -5 ���ݴ���
 *  - -6 �������� (��Դ�����ڶ�ȡͷ��Ϣʧ��,���ȡ������Ϣʧ��)
 *  - -7 ��ȡ������Ϣδ����,�Զ˷����������Ͽ�(trunk mode)
 *  - -8 �ڷ�chunkģʽʱ,�ڳ�����Ч�����(����len>0��len<maxlen)���ݽ��ղ���ȫ
 *  - -10 ����Ĳ������Ϸ�
 *
 *  @note ����ֵΪ1��pres->m_status_code == 200ͬʱ����������Ϊ��ҳ����ץȡ�ɹ���
 *         �������code==500����ȷ��urlû�����⣬�п������������⣬���ظ����ԣ�
 *  @note presָ����ʹ����Ϻ���Ҫ����::uln_http_freeres�ͷ���Դ
 */
int uln_http_crawlpage_through_proxy_ms(const char* url, const char* ip, int maxlen,
                uln_response_t* pres, int ntimeout, int flag,
                uln_request_t* ereq,
                const char* proxy_host, const int proxy_port);

/**
 *  ͨ��proxy�����ҳ���޸Ĺ�������޸Ĺ�����ץȡ����ҳ
 *  
 *  @param[in]  url      ��ץȡ��ҳ��url, url��Ҫ��http://��ͷ��������������´���
 *  					  pres->m_status_code = 500�����ڲ�����������)
 *                        pres->m_status_code = 400 (�����������)
 *  @param[in]  ip       ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen   ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres     ���ؽṹ��ָ��
 *  @param[in]  ntimeout ��ʱʱ��
 *  @param[in]  flag     ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[in]  lmt      �ϴ��޸Ĺ����ַ�����ʽ
 *  @param[in]  etag     etag
 *  @param[in]  orilen   ԭ���ĳ���    
 *  @param[in]  ereq     ����ṹ   
 *  @param[in]  proxy_host proxy��������
 *  @param[in]  proxy_port proxy�Ķ˿ں�
 *  @param[out] pres     ������ҳ��Ϣ
 *  @return �������
 *  - 0 ��ʾ���޸�
 *  - 1 ��ʾ���޸�,ץȡ��ҳ��pres�У���ϸ��Ϣ����¼��pres�ṹ��.
 *  - 2 ��ʾҳ�汻�ض�
 *  - -1 ������������
 *  - -2 �Ƿ�url
 *  - -3 ���ӷ�����ʧ��
 *  - -4 ������ʧ��
 *  - -5 ���ݴ���
 *  - -6 ��ȡ��ҳ����ʧ��
 *  - -7 ��ȡ����δ���,�Զ˷����������Ͽ�(trunk mode)
 *  - -8 �ڷ�chunkģʽʱ,�ڳ�����Ч�����(����len>0��len<maxlen)���ݽ��ղ���ȫ
 *  - -10 �������Ϸ�
 *
 * @note ����ֵΪ1��pres->m_status_code == 200ͬʱ����������Ϊץȡ�ɹ���
 * @note presָ����ʹ����Ϻ���Ҫ����::uln_http_freeres�ͷ���Դ
 */
int uln_http_checkpage_through_proxy(const char* url, const char* ip, int maxlen,
                uln_response_t* pres, int ntimeout, const int flag,
                const char* lmt, const char* etag, const int orilen,
                uln_request_t*ereq, const char* proxy_host, const int proxy_port);

/**
 *  ͨ��proxy�����ҳ���޸Ĺ�������޸Ĺ�����ץȡ����ҳ
 *  ��ʱʱ�䵥λΪ����
 *  
 *  @param[in]  url      ��ץȡ��ҳ��url, url��Ҫ��http://��ͷ��������������´���
 *  					  pres->m_status_code = 500�����ڲ�����������)
 *                        pres->m_status_code = 400 (�����������)
 *  @param[in]  ip       ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen   ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres     ���ؽṹ��ָ��
 *  @param[in]  ntimeout ��ʱʱ��(����)
 *  @param[in]  flag     ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[in]  lmt      �ϴ��޸Ĺ����ַ�����ʽ
 *  @param[in]  etag     etag
 *  @param[in]  orilen   ԭ���ĳ���    
 *  @param[in]  ereq     ����ṹ   
 *  @param[in]  proxy_host proxy��������
 *  @param[in]  proxy_port proxy�Ķ˿ں�
 *  @param[out] pres     ������ҳ��Ϣ
 *  @return �������
 *  - 0 ��ʾ���޸�
 *  - 1 ��ʾ���޸�,ץȡ��ҳ��pres�У���ϸ��Ϣ����¼��pres�ṹ��.
 *  - 2 ��ʾҳ�汻�ض�
 *  - -1 ������������
 *  - -2 �Ƿ�url
 *  - -3 ���ӷ�����ʧ��
 *  - -4 ������ʧ��
 *  - -5 ���ݴ���
 *  - -6 ��ȡ��ҳ����ʧ��
 *  - -7 ��ȡ����δ���,�Զ˷����������Ͽ�(trunk mode)
 *  - -8 �ڷ�chunkģʽʱ,�ڳ�����Ч�����(����len>0��len<maxlen)���ݽ��ղ���ȫ
 *  - -10 �������Ϸ�
 *
 * @note ����ֵΪ1��pres->m_status_code == 200ͬʱ����������Ϊץȡ�ɹ���
 * @note presָ����ʹ����Ϻ���Ҫ����::uln_http_freeres�ͷ���Դ
 */
int uln_http_checkpage_through_proxy_ms(const char* url, const char* ip, int maxlen,
                uln_response_t* pres, int ntimeout, const int flag,
                const char* lmt, const char* etag, const int orilen,
                uln_request_t*ereq, const char* proxy_host, const int proxy_port);

//////////////////////////////////////////////////////////////
//������չ��Ľӿ�..
//############################################################
//############################################################
//modified by zhangyan04@baidu.com
//�޸ĵ������ǽ�url���ȴ�256����2048,���󳤶ȴ�4096�����8192
//�����������ӵĽӿ�ʹ�õ�����ṹ�嶼��uln_request_ex2_t�����ؽṹ�嶼��uln_response_ex2_t


/**
 * @brief ���ɲ���ʼ��uln_response_ex2_tӦ��ṹ��. 
 *
 * @return  uln_response_ex2_t*, Ӧ��ṹ��ָ��
 * @retval  ��NULL����ʾӦ��ṹ��ָ��, ����ʼ���ɹ�
 * @retval  NULL, ����ʼ���ɰ�
 * @see     uln_http_freeres_ex2()
 * @note    ��ʼ��ʱ����Ϊm_buf�ֶο���СΪULN_DEFAULT_PAGESIZE��С�Ŀռ�
**/
uln_response_ex2_t* uln_http_initres_ex2(void);


/**
 * @brief �ͷ�Ӧ��ṹ���ڴ�, ͬʱ�ͷŽṹ����buf���ڴ�.
 *
 * @param [in] pres   : uln_response_ex2_t* ���ͷŵĽṹ��ָ��.
 * @return  void 
 * @see  uln_http_initres_ex2()
 * @note ������ָ��Ϊ�գ������κ�����
**/
void uln_http_freeres_ex2(uln_response_ex2_t *pres);


 /**
 * @brief ��ȡhttpͷ��Ϣ. 
 * httpͷ��version��status_code��status_phrase�����pres����Ӧ�ֶΣ�
 * ������Ϣ������pres->m_reshead��.
 *
 * @param [in]  sockfd   : int               socket���
 * @param [out] pres     : uln_response_ex2_t*   ���ؽṹָ��  
 * @param [in]  prl      : Rline*            ������
 * @param [in]  ntimeout : int               ��ʱʱ��
 * @return  int �������
 * @retval   1  ��ȡͷ����Ϣ�ɹ�
 * @retval  -1  �����ȡ����(��ʱ�������������) 
 * @retval  -2  Ӧ���ʽ����(����ͷ����)
 * @retval  -3  ����������Ϸ�
 * @see   
 * @note  prl�洢����������,ִ����˺���ʱ,�����п��ܻ���δ��������
**/
int uln_http_readhead_ex2(int sockfd, uln_response_ex2_t* pres, Rline *prl, int ntimeout);


 /**
 * @brief ��ȡhttpͷ��Ϣ. 
 * httpͷ��version��status_code��status_phrase�����pres����Ӧ�ֶΣ�
 * ������Ϣ������pres->m_reshead��.
 * ��uln_http_readhead_ex2�Ĳ�ͬ�ǣ��˴���ʱʱ�侫��Ϊ����
 *
 * @param [in]  sockfd   : int               socket���
 * @param [out] pres     : uln_response_ex2_t*   ���ؽṹָ��  
 * @param [in]  prl      : Rline*            ������
 * @param [in]  ntimeout : int               ��ʱʱ��
 * @return  int �������
 * @retval   1  ��ȡͷ����Ϣ�ɹ�
 * @retval  -1  �����ȡ����(��ʱ�������������) 
 * @retval  -2  Ӧ���ʽ����(����ͷ����)
 * @retval  -3  ����������Ϸ�
 * @see   
 * @note  prl�洢����������,ִ����˺���ʱ,�����п��ܻ���δ��������
**/
int uln_http_readhead_ms_ex2(int sockfd, uln_response_ex2_t* pres, Rline *prl, int ntimeout);


/**
 * @brief ��ȡhttp��ҳ����.
 *
 * @param [in]  sockfd   : int               socket���
 * @param [out] pres     : uln_response_ex2_t*   ���ؽṹָ��
 * @param [out] prl      : Rline*            ������
 * @param [in]  maxlen   : int               �ӷ�����һ�ζ�ȡ����󳤶�
 * @param [in]  ntimeout : int               ��ʱʱ��(��)
 * @return  int   �������
 * @retval  1     �ɹ���ȡhttp����
 * @retval  2     page���ض� (���ȴ���maxlen)
 * @retval  3     pageû��ȫ������
 * @retval -1     �����ȡ����
 * @retval -3     ���ݸ�ʽ����
 * @retval -4     �ڴ����
 * @retval -7     trunkģʽʱ,δ�ӵ�ĩβflag,�Զ˷����������Ͽ����Ӵ���
 * @retval -8     ����page������ͷ��Ϣ�еĳ��Ȳ�һ��
 * @retval -10    ת��������Ϸ�
 * @see 
 * @note 
**/
int uln_http_readcontent_ex2(int sockfd, uln_response_ex2_t* pres, Rline *prl, int maxlen, int ntimeout);


/**
 * @brief ��ȡhttp��ҳ����.
 * ��uln_http_readcontent_ex2�Ĳ�ͬ�ǣ��˴���ʱʱ�䵥λΪ����
 *
 * @param [in]  sockfd   : int               socket���
 * @param [out] pres     : uln_response_ex2_t*   ���ؽṹָ��
 * @param [out] prl      : Rline*            ������
 * @param [in]  maxlen   : int               �ӷ�����һ�ζ�ȡ����󳤶�
 * @param [in]  ntimeout : int               ��ʱʱ��(����)
 * @return  int   �������
 * @retval  1     �ɹ���ȡhttp����
 * @retval  2     page���ض� (���ȴ���maxlen)
 * @retval  3     pageû��ȫ������
 * @retval -1     �����ȡ����
 * @retval -3     ���ݸ�ʽ����
 * @retval -4     �ڴ����
 * @retval -7     trunkģʽʱ,δ�ӵ�ĩβflag,�Զ˷����������Ͽ����Ӵ���
 * @retval -8     ����page������ͷ��Ϣ�еĳ��Ȳ�һ��
 * @retval -10    ת��������Ϸ�
 * @see 
 * @note 
**/
int uln_http_readcontent_ms_ex2(int sockfd, uln_response_ex2_t* pres, Rline *prl, int maxlen, int ntimeout);

/**
 * @brief ��ʼ������ṹ��. 
 *
 * �˺�����ʼ��������ͷ��Ϣ��, 
 * Connection:close, Accept-Language:zh-cn,zh-tw,�ٶȵ�User-agent��.
 * ���󷽷���HTTP_GET
 * 
 * �����ipֻ������ṹ�����𱣴����ã���url��ץȡ���鲻������. ����ΪNULL.
 *
 * @param [in] url  : const char*  ��Ҫץȡ�����url
 * @param [in] ip   : const char*  url��Ӧ��ip
 * @return  uln_request_ex2_t*         ����ṹ��ָ��
 * @retval  ��NULL                 �ɹ�
 * @retval  NULL                   ��ʼ�����ɹ�
 * @see 
 * @note    �����ipֻ������ṹ�����𱣴����ã���url��ץȡ���鲻������. ����ΪNULL.
 **/
uln_request_ex2_t* uln_http_initreq_ex2(const char* url, const char* ip);

/**
 * @brief �ͷ�����ṹ��.
 *
 * @param [in] preq   : uln_request_ex2_t* ���ͷŵ�����ṹ��ָ��
 * @return  void 
 * @retval  ��
 * @see 
 * @note 
 **/
void uln_http_freereq_ex2(uln_request_ex2_t* preq);

/**
 * @brief ���Ѿ����ӵ�socket�������HTTP���� 
 *
 * @param [in] sock       : const int         socket���
 * @param [in] preq       : uln_request_ex2_t*    ����ṹ��
 * @param [in] ntimeout   : int               ��ʱʱ��(��)
 * @return     int        ������� 
 * @retval     1          success
 * @retval     -1         failed
 **/
int uln_http_sendreq_ex2(const int sock, uln_request_ex2_t* preq, int ntimeout);


/**
 * @brief ���Ѿ����ӵ�socket�������HTTP���� 
 * ��uln_http_sendreq_ex2�Ĳ�ͬ���ڣ��˴���ʱʱ�䵥λΪ����
 *
 * @param [in] sock       : const int         socket���
 * @param [in] preq       : uln_request_ex2_t*    ����ṹ��
 * @param [in] ntimeout   : int               ��ʱʱ��(����)
 * @return     int        ������� 
 * @retval     1          success
 * @retval     -1         failed
 **/
int uln_http_sendreq_ms_ex2(const int sock, uln_request_ex2_t* preq, int ntimeout);


/**
 *  �Զ�������ṹ�����ҳ���޸Ĺ�������޸Ĺ�����ץȡ����ҳ
 *  
 *  @param[in]  url      ��ץȡ��ҳ��url
 *  @param[in]  ip       ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen   ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres     ���ؽṹ��ָ��
 *  @param[in]  ntimeout ��ʱʱ��
 *  @param[in]  flag     ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[in]  lmt      �ϴ��޸Ĺ����ַ�����ʽ
 *  @param[in]  etag     etag
 *  @param[in]  orilen   ԭ���ĳ���    
 *  @param[in]  ereq     ����ṹ   
 *  @param[out] pres     ������ҳ��Ϣ
 *  @return �������
 *
 *  - 0 ��ʾ���޸�
 *  - 1 ��ʾ���޸�,ץȡ��ҳ��pres�У���ϸ��Ϣ����¼��pres�ṹ��.
 *  - 2 ��ʾҳ�汻�ض�
 *  - -1 ������������
 *  - -2 �Ƿ�url
 *  - -3 ���ӷ�����ʧ��
 *  - -4 ������ʧ��
 *  - -5 ���ݴ���
 *  - -7 ��ȡ������δ�ɹ�,�Զ˷������ر�(trunk mode)
 *  - -8 �ڷ�chunkģʽʱ,�ڳ�����Ч�����(����len>0��len<maxlen)���ݽ��ղ���ȫ
 *  - -10 ����Ĳ������Ϸ�
 *
 *  @note presָ����ʹ����Ϻ���Ҫ����::uln_http_freeres_ex2�ͷ���Դ
 */  
int uln_http_checkpage_ex2(const char* url, const char* ip, int maxlen,
			      uln_response_ex2_t* pres, int ntimeout, const int flag,
			      const char* lmt, const char* etag, const int orilen, uln_request_ex2_t* ereq=NULL);


/**
 *  �Զ�������ṹ�����ҳ���޸Ĺ�������޸Ĺ�����ץȡ����ҳ
 *  ��ʱ��λΪ����
 *  
 *  @param[in]  url      ��ץȡ��ҳ��url
 *  @param[in]  ip       ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen   ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres     ���ؽṹ��ָ��
 *  @param[in]  ntimeout ��ʱʱ��(����)
 *  @param[in]  flag     ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[in]  lmt      �ϴ��޸Ĺ����ַ�����ʽ
 *  @param[in]  etag     etag
 *  @param[in]  orilen   ԭ���ĳ���    
 *  @param[in]  ereq     ����ṹ   
 *  @param[out] pres     ������ҳ��Ϣ
 *  @return �������
 *
 *  - 0 ��ʾ���޸�
 *  - 1 ��ʾ���޸�,ץȡ��ҳ��pres�У���ϸ��Ϣ����¼��pres�ṹ��.
 *  - 2 ��ʾҳ�汻�ض�
 *  - -1 ������������
 *  - -2 �Ƿ�url
 *  - -3 ���ӷ�����ʧ��
 *  - -4 ������ʧ��
 *  - -5 ���ݴ���
 *  - -7 ��ȡ������δ�ɹ�,�Զ˷������ر�(trunk mode)
 *  - -8 �ڷ�chunkģʽʱ,�ڳ�����Ч�����(����len>0��len<maxlen)���ݽ��ղ���ȫ
 *  - -10 ����Ĳ������Ϸ�
 *
 *  @note presָ����ʹ����Ϻ���Ҫ����::uln_http_freeres_ex2�ͷ���Դ
 */  
int uln_http_checkpage_ms_ex2(const char* url, const char* ip, int maxlen,
				 uln_response_ex2_t* pres, int ntimeout, const int flag,
				 const char* lmt, const char* etag, const int orilen, uln_request_ex2_t* ereq=NULL);


/**
 *  �Զ�������ṹ������ץȡ��ҳ.
 *  ע: 
 *  uln_request_ex2_t�ṹ���е�m_url��m_ip���������ã���Ҫ���ú�������url��ip.  
 *
 *  @param[in]  url      ��ץȡ��ҳ��url
 *  @param[in]  ip       ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen   ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres     ���ؽṹ��ָ��
 *  @param[in]  ntimeout ��ʱʱ��
 *  @param[in]  flag     ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[in]  ereq     ����ṹ
 *  @param[out] pres     ������ҳ��Ϣ
 *  @return �������
 *
 *  - 1 ��ʾ�ɹ�,��ϸ��Ϣ����¼��pres�ṹ��.
 *  - 2 ��ʾҳ�汻�ض�
 *  - -1 ������������
 *  - -2 �Ƿ�url
 *  - -3 ���ӷ�����ʧ��
 *  - -4 ������ʧ��
 *  - -5 ���ݴ���
 *  - -7 ��ȡ������δ����,�Զ˷����������Ͽ�(������trunkģʽ��)
 *  - -8 �ڷ�chunkģʽʱ,�ڳ�����Ч�����(����len>0��len<maxlen)���ݽ��ղ���ȫ
 *  - -10 ����������Ϸ�.
 *
 *  @note presֻ���ʼ��һ�μ��ɶ������. ʹ����Ϻ������uln_http_freeres_ex2�ͷ���Դ.
 *  @note uln_request_ex2_t�ṹ���е�m_url��m_ip���������ã���Ҫ���ú�������url��ip
 */ 

int uln_http_crawlpage_ex2(const char* url, const char* ip, int maxlen,
			      uln_response_ex2_t* pres, int ntimeout, int flag, uln_request_ex2_t* ereq=NULL);


/**
 *  �Զ�������ṹ������ץȡ��ҳ.
 *  ��ʱʱ�䵥λΪ����
 *  ע: 
 *  uln_request_ex2_t�ṹ���е�m_url��m_ip���������ã���Ҫ���ú�������url��ip.  
 *
 *  @param[in]  url      ��ץȡ��ҳ��url
 *  @param[in]  ip       ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen   ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres     ���ؽṹ��ָ��
 *  @param[in]  ntimeout ��ʱʱ�䣬��λΪ����
 *  @param[in]  flag     ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[in]  ereq     ����ṹ
 *  @param[out] pres     ������ҳ��Ϣ
 *  @return �������
 *
 *  - 1 ��ʾ�ɹ�,��ϸ��Ϣ����¼��pres�ṹ��.
 *  - 2 ��ʾҳ�汻�ض�
 *  - -1 ������������
 *  - -2 �Ƿ�url
 *  - -3 ���ӷ�����ʧ��
 *  - -4 ������ʧ��
 *  - -5 ���ݴ���
 *  - -7 ��ȡ������δ����,�Զ˷����������Ͽ�(������trunkģʽ��)
 *  - -8 �ڷ�chunkģʽʱ,�ڳ�����Ч�����(����len>0��len<maxlen)���ݽ��ղ���ȫ
 *  - -10 ����������Ϸ�.
 *
 *  @note presֻ���ʼ��һ�μ��ɶ������. ʹ����Ϻ������uln_http_freeres_ex2�ͷ���Դ.
 *  @note uln_request_ex2_t�ṹ���е�m_url��m_ip���������ã���Ҫ���ú�������url��ip
 */ 
int uln_http_crawlpage_ms_ex2(const char* url, const char* ip, int maxlen,
				 uln_response_ex2_t* pres, int ntimeout, int flag, uln_request_ex2_t* ereq=NULL);


/**
 *  ͨ��proxy������ץȡ��ҳ
 *  
 *  @param[in]  url        ��ץȡ��ҳ��url,url����http://��ͷ�������������
 *  					   pres->m_status_code = 500�����ڲ�����������)
 *                         ��pres->m_status_code = 400 (�����������)
 *  @param[in]  ip         ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen     ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres       ���ؽṹ��ָ��
 *  @param[in]  ntimeout   ��ʱʱ��
 *  @param[in]  flag       ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[in]  ereq       ����ṹ
 *  @param[in]  proxy_host proxy��������
 *  @param[in]  proxy_port proxy�Ķ˿ں�
 *  @param[out] pres       ������ҳ��Ϣ
 *  @return �������
 *  - 1 ��ʾ������Ϣͷ�ɹ�,��ϸ��Ϣ����¼��pres�ṹ��
 *  - 2 ��ʾҳ�汻�ض�
 *  - -1 ������󣬳�ʼ�����̵���ʧ��
 *  - -2 �Ƿ�url
 *  - -3 ���Ӵ�����ʹ���
 *  - -4 �޴�״̬
 *  - -5 ���ݴ���
 *  - -6 �������� (��Դ�����ڶ�ȡͷ��Ϣʧ��,���ȡ������Ϣʧ��)
 *  - -7 ��ȡ������Ϣδ����,�Զ˷����������Ͽ�(trunk mode)
 *  - -8 �ڷ�chunkģʽʱ,�ڳ�����Ч�����(����len>0��len<maxlen)���ݽ��ղ���ȫ
 *  - -10 ����Ĳ������Ϸ�
 *
 *  @note ����ֵΪ1��pres->m_status_code == 200ͬʱ����������Ϊ��ҳ����ץȡ�ɹ���
 *         �������code==500����ȷ��urlû�����⣬�п������������⣬���ظ����ԣ�
 *  @note presָ����ʹ����Ϻ���Ҫ����::uln_http_freeres_ex2�ͷ���Դ
 */
int uln_http_crawlpage_through_proxy_ex2(const char* url, const char* ip, int maxlen,
					uln_response_ex2_t* pres, int ntimeout, int flag, uln_request_ex2_t* ereq,
					const char* proxy_host, const int proxy_port);

/**
 *  ͨ��proxy������ץȡ��ҳ
 *  ��ʱʱ�䵥λΪ����
 *  
 *  @param[in]  url        ��ץȡ��ҳ��url,url����http://��ͷ�������������
 *  					   pres->m_status_code = 500�����ڲ�����������)
 *                         ��pres->m_status_code = 400 (�����������)
 *  @param[in]  ip         ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen     ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres       ���ؽṹ��ָ��
 *  @param[in]  ntimeout   ��ʱʱ��(����)
 *  @param[in]  flag       ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[in]  ereq       ����ṹ
 *  @param[in]  proxy_host proxy��������
 *  @param[in]  proxy_port proxy�Ķ˿ں�
 *  @param[out] pres       ������ҳ��Ϣ
 *  @return �������
 *  - 1 ��ʾ������Ϣͷ�ɹ�,��ϸ��Ϣ����¼��pres�ṹ��
 *  - 2 ��ʾҳ�汻�ض�
 *  - -1 ������󣬳�ʼ�����̵���ʧ��
 *  - -2 �Ƿ�url
 *  - -3 ���Ӵ�����ʹ���
 *  - -4 �޴�״̬
 *  - -5 ���ݴ���
 *  - -6 �������� (��Դ�����ڶ�ȡͷ��Ϣʧ��,���ȡ������Ϣʧ��)
 *  - -7 ��ȡ������Ϣδ����,�Զ˷����������Ͽ�(trunk mode)
 *  - -8 �ڷ�chunkģʽʱ,�ڳ�����Ч�����(����len>0��len<maxlen)���ݽ��ղ���ȫ
 *  - -10 ����Ĳ������Ϸ�
 *
 *  @note ����ֵΪ1��pres->m_status_code == 200ͬʱ����������Ϊ��ҳ����ץȡ�ɹ���
 *         �������code==500����ȷ��urlû�����⣬�п������������⣬���ظ����ԣ�
 *  @note presָ����ʹ����Ϻ���Ҫ����::uln_http_freeres_ex2�ͷ���Դ
 */
int uln_http_crawlpage_through_proxy_ms_ex2(const char* url, const char* ip, int maxlen,
					   uln_response_ex2_t* pres, int ntimeout, int flag, uln_request_ex2_t* ereq,
					   const char* proxy_host, const int proxy_port);


/**
 *  ͨ��proxy�����ҳ���޸Ĺ�������޸Ĺ�����ץȡ����ҳ
 *  
 *  @param[in]  url      ��ץȡ��ҳ��url, url��Ҫ��http://��ͷ��������������´���
 *  					  pres->m_status_code = 500�����ڲ�����������)
 *                        pres->m_status_code = 400 (�����������)
 *  @param[in]  ip       ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen   ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres     ���ؽṹ��ָ��
 *  @param[in]  ntimeout ��ʱʱ��
 *  @param[in]  flag     ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[in]  lmt      �ϴ��޸Ĺ����ַ�����ʽ
 *  @param[in]  etag     etag
 *  @param[in]  orilen   ԭ���ĳ���    
 *  @param[in]  ereq     ����ṹ   
 *  @param[in]  proxy_host proxy��������
 *  @param[in]  proxy_port proxy�Ķ˿ں�
 *  @param[out] pres     ������ҳ��Ϣ
 *  @return �������
 *  - 0 ��ʾ���޸�
 *  - 1 ��ʾ���޸�,ץȡ��ҳ��pres�У���ϸ��Ϣ����¼��pres�ṹ��.
 *  - 2 ��ʾҳ�汻�ض�
 *  - -1 ������������
 *  - -2 �Ƿ�url
 *  - -3 ���ӷ�����ʧ��
 *  - -4 ������ʧ��
 *  - -5 ���ݴ���
 *  - -6 ��ȡ��ҳ����ʧ��
 *  - -7 ��ȡ����δ���,�Զ˷����������Ͽ�(trunk mode)
 *  - -8 �ڷ�chunkģʽʱ,�ڳ�����Ч�����(����len>0��len<maxlen)���ݽ��ղ���ȫ
 *  - -10 �������Ϸ�
 *
 * @note ����ֵΪ1��pres->m_status_code == 200ͬʱ����������Ϊץȡ�ɹ���
 * @note presָ����ʹ����Ϻ���Ҫ����::uln_http_freeres_ex2�ͷ���Դ
 */
int uln_http_checkpage_through_proxy_ex2(const char* url, const char* ip, int maxlen,
					uln_response_ex2_t* pres, int ntimeout, const int flag,
					const char* lmt, const char* etag, const int orilen, uln_request_ex2_t* ereq,
					const char* proxy_host, const int proxy_port);



/**
 *  ͨ��proxy�����ҳ���޸Ĺ�������޸Ĺ�����ץȡ����ҳ
 *  ��ʱʱ�䵥λΪ����
 *  
 *  @param[in]  url      ��ץȡ��ҳ��url, url��Ҫ��http://��ͷ��������������´���
 *  					  pres->m_status_code = 500�����ڲ�����������)
 *                        pres->m_status_code = 400 (�����������)
 *  @param[in]  ip       ��ץȡ��ҳ��������ip��ַ
 *  @param[in]  maxlen   ��ҳ����󳤶�,�����ҳ�����������,�����ض�     
 *  @param[in]  pres     ���ؽṹ��ָ��
 *  @param[in]  ntimeout ��ʱʱ��(����)
 *  @param[in]  flag     ��flag & 0x1 !=0 ʱ��ֻ�����ı���ʽ
 *                       (������ʷԭ��flag & 0x1 != 0���������������ʽ����)
 *  @param[in]  lmt      �ϴ��޸Ĺ����ַ�����ʽ
 *  @param[in]  etag     etag
 *  @param[in]  orilen   ԭ���ĳ���    
 *  @param[in]  ereq     ����ṹ   
 *  @param[in]  proxy_host proxy��������
 *  @param[in]  proxy_port proxy�Ķ˿ں�
 *  @param[out] pres     ������ҳ��Ϣ
 *  @return �������
 *  - 0 ��ʾ���޸�
 *  - 1 ��ʾ���޸�,ץȡ��ҳ��pres�У���ϸ��Ϣ����¼��pres�ṹ��.
 *  - 2 ��ʾҳ�汻�ض�
 *  - -1 ������������
 *  - -2 �Ƿ�url
 *  - -3 ���ӷ�����ʧ��
 *  - -4 ������ʧ��
 *  - -5 ���ݴ���
 *  - -6 ��ȡ��ҳ����ʧ��
 *  - -7 ��ȡ����δ���,�Զ˷����������Ͽ�(trunk mode)
 *  - -8 �ڷ�chunkģʽʱ,�ڳ�����Ч�����(����len>0��len<maxlen)���ݽ��ղ���ȫ
 *  - -10 �������Ϸ�
 *
 * @note ����ֵΪ1��pres->m_status_code == 200ͬʱ����������Ϊץȡ�ɹ���
 * @note presָ����ʹ����Ϻ���Ҫ����::uln_http_freeres_ex2�ͷ���Դ
 */
int uln_http_checkpage_through_proxy_ms_ex2(const char* url, const char* ip, int maxlen,
					   uln_response_ex2_t* pres, int ntimeout, const int flag,
					   const char* lmt, const char* etag, const int orilen, uln_request_ex2_t* ereq,
					   const char* proxy_host, const int proxy_port);



#endif
