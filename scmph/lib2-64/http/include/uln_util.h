/***************************************************************************
 *
 * Copyright (c) 2007 Baidu.com, Inc. All Rights Reserved
 * $Id: uln_util.h,v 1.8 2010/01/05 00:45:21 zhangyan04 Exp $ 
 * 
 **************************************************************************/

#ifndef ULN_UTIL_H
#define ULN_UTIL_H

#include <ul_net.h>
const int SP_BUFSIZE = 1024;

/**
 *  根据所给的主机地址，进行http网络连接(内部使用函数)
 *  
 *  @param[in]  host  主机地址
 *  @param[in]  port  端口号
 *  @param[in]  secs  超时时间(秒)
 *  @param[out] 无
 *  @return sock句柄
 *  - >=0 表示成功
 *  - <0 表示失败
 */
int uln_http_tcpconnect(const char *host, int port, int secs);

/**
 *  根据所给的主机地址，进行http网络连接(内部使用函数)
 *  
 *  @param[in]  host  主机地址
 *  @param[in]  port  端口号
 *  @param[in]  secs  超时时间(毫秒)
 *  @param[out] 无
 *  @return sock句柄
 *  - >=0 表示成功
 *  - <0 表示失败
 */
int uln_http_tcpconnect_ms(const char *host, int port, int msecs);

/**
 *  利用prl作为缓冲，从网络读取指定长度的buf
 *  
 *  @param[in]  sockfd   sock句柄
 *  @param[in]  buf      存储读取数据的buf
 *  @param[in]  size     要读取的长度
 *  @param[in]  pcurlen  存储读取实际长度的指针
 *  @param[in]  prl      缓冲结构
 *  @param[in]  ntimeout 超时时间(秒)
 *  @param[out] buf      存储读的数据
 *  @param[out] pcurlen  实际读取的长度
 *  @return 操作结果
 *  - -1                 参数不合法
 *  - ULN_NOTICE_OK      表示成功
 *  - ULN_ERR_READ_ERROR 表示失败
 */
int uln_readbuf_o(int sockfd, char * buf, unsigned int size, ssize_t* pcurlen,
                  Rline* prl, int ntimeout);

/**
 *  利用prl作为缓冲，从网络读取指定长度的buf
 *  超时单位为毫秒
 *
 *  @param[in]  sockfd   sock句柄
 *  @param[in]  buf      存储读取数据的buf
 *  @param[in]  size     要读取的长度
 *  @param[in]  pcurlen  存储读取实际长度的指针
 *  @param[in]  prl      缓冲结构
 *  @param[in]  ntimeout 超时时间(毫秒)
 *  @param[out] buf      存储读的数据
 *  @param[out] pcurlen  实际读取的长度
 *  @return 操作结果
 *  - -1                 参数不合法
 *  - ULN_NOTICE_OK      表示成功
 *  - ULN_ERR_READ_ERROR 表示失败
 */
int uln_readbuf_o_ms(int sockfd, char * buf, unsigned int size, ssize_t* pcurlen,
                  Rline* prl, int ntimeout);
#endif
