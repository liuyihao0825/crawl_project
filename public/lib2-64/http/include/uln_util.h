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
 *  ����������������ַ������http��������(�ڲ�ʹ�ú���)
 *  
 *  @param[in]  host  ������ַ
 *  @param[in]  port  �˿ں�
 *  @param[in]  secs  ��ʱʱ��(��)
 *  @param[out] ��
 *  @return sock���
 *  - >=0 ��ʾ�ɹ�
 *  - <0 ��ʾʧ��
 */
int uln_http_tcpconnect(const char *host, int port, int secs);

/**
 *  ����������������ַ������http��������(�ڲ�ʹ�ú���)
 *  
 *  @param[in]  host  ������ַ
 *  @param[in]  port  �˿ں�
 *  @param[in]  secs  ��ʱʱ��(����)
 *  @param[out] ��
 *  @return sock���
 *  - >=0 ��ʾ�ɹ�
 *  - <0 ��ʾʧ��
 */
int uln_http_tcpconnect_ms(const char *host, int port, int msecs);

/**
 *  ����prl��Ϊ���壬�������ȡָ�����ȵ�buf
 *  
 *  @param[in]  sockfd   sock���
 *  @param[in]  buf      �洢��ȡ���ݵ�buf
 *  @param[in]  size     Ҫ��ȡ�ĳ���
 *  @param[in]  pcurlen  �洢��ȡʵ�ʳ��ȵ�ָ��
 *  @param[in]  prl      ����ṹ
 *  @param[in]  ntimeout ��ʱʱ��(��)
 *  @param[out] buf      �洢��������
 *  @param[out] pcurlen  ʵ�ʶ�ȡ�ĳ���
 *  @return �������
 *  - -1                 �������Ϸ�
 *  - ULN_NOTICE_OK      ��ʾ�ɹ�
 *  - ULN_ERR_READ_ERROR ��ʾʧ��
 */
int uln_readbuf_o(int sockfd, char * buf, unsigned int size, ssize_t* pcurlen,
                  Rline* prl, int ntimeout);

/**
 *  ����prl��Ϊ���壬�������ȡָ�����ȵ�buf
 *  ��ʱ��λΪ����
 *
 *  @param[in]  sockfd   sock���
 *  @param[in]  buf      �洢��ȡ���ݵ�buf
 *  @param[in]  size     Ҫ��ȡ�ĳ���
 *  @param[in]  pcurlen  �洢��ȡʵ�ʳ��ȵ�ָ��
 *  @param[in]  prl      ����ṹ
 *  @param[in]  ntimeout ��ʱʱ��(����)
 *  @param[out] buf      �洢��������
 *  @param[out] pcurlen  ʵ�ʶ�ȡ�ĳ���
 *  @return �������
 *  - -1                 �������Ϸ�
 *  - ULN_NOTICE_OK      ��ʾ�ɹ�
 *  - ULN_ERR_READ_ERROR ��ʾʧ��
 */
int uln_readbuf_o_ms(int sockfd, char * buf, unsigned int size, ssize_t* pcurlen,
                  Rline* prl, int ntimeout);
#endif
