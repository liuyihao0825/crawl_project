/***************************************************************************
 *
 * Copyright (c) 2007 Baidu.com, Inc. All Rights Reserved
 * $Id: uln_vector.h,v 1.8.4.2 2010/03/23 14:52:00 zhangyan04 Exp $ 
 * 
 **************************************************************************/


#ifndef ULN_VECTOR_H
#define ULN_VECTOR_H

const unsigned int ULN_MAX_NAME_LENGTH  = 32;          ///< ������ֳ���
const unsigned int ULN_MAX_VALUE_LENGTH = 256;         ///< ���ֵ�ĳ���
const int ULN_DEFAULT_COUNT             = 16;          ///< Ĭ��(���)ʱvector������

typedef struct ULN_PAIR {
    char m_name[ULN_MAX_NAME_LENGTH];       ///< pair������
    char m_value[ULN_MAX_VALUE_LENGTH];     ///< pair��ֵ
} uln_pair_t;

typedef struct ULN_VEC {
    int         m_size;                     ///< m_list��Ŀռ��С
    int         m_curpos;                   ///< m_list���Ԫ�ظ���
    uln_pair_t* m_list;                     ///< m_list����uln_pair_t������
} uln_vector_t;

////////////////////////////////////////////////////////////
///��չ����֮��Ľṹ
const unsigned int ULN_MAX_NAME_LENGTH_EX2 = 64; 
const unsigned int ULN_MAX_VALUE_LENGTH_EX2 = 4096;

typedef struct ULN_PAIR_EX2 {
    char m_name[ULN_MAX_NAME_LENGTH_EX2];
    char m_value[ULN_MAX_VALUE_LENGTH_EX2];
} uln_pair_ex2_t;

typedef struct ULN_VEC_EX2 {
    int m_size;
    int m_curpos;
    uln_pair_ex2_t *m_list;
}uln_vector_ex2_t;

/**
 * @brief  ��ʼ������.
 *
 * @return  uln_vector_t*  ��ʼ���������ָ�룬��NULL
 * @retval  ��NULL  �ɹ������������ָ��
 * @retval  NULL    ʧ��
**/
uln_vector_t* uln_vec_init(void);


/**
 * @brief �ͷŸ�vector�ڴ�.
 *
 * @param [in] pvec   : uln_vector_t*  ���ͷŵ�vectorָ��.
 * @return  void 
**/
void uln_vec_free(uln_vector_t* pvec);


/**
 * @brief ��Ԫ��(pname, pvalue)����vector���.
 *
 * @param [in] pvec     : uln_vector_t*  vectorָ��
 * @param [in] pname    : const char*    Ԫ������
 * @param [in] pvalue   : const char*    Ԫ��ֵ
 * @return  int  �������
 * @retval  1    �ɹ�
 * @retval -1    ʧ��(�ڴ�ʧ��)
 * @retval -2    ʧ��, pname���Ϸ�(���ȹ������ָ��)
 * @retval -3    ʧ��, pvalue���Ϸ�(���ȹ������ָ��)
 * @retval -4    ʧ��, pvec���Ͻ�(vec size����ȷ��pvecΪ��ָ��)
**/
int uln_vec_pushback(uln_vector_t* pvec,
                     const char* pname, const char* pvalue);


/**
 * @brief  �������л��pname��ӦԪ�ص�Ԫ��ֵ.
 *
 * @param [in]  pvec     : const uln_vector_t*   vectorָ��
 * @param [in]  pname    : const char*           Ԫ������
 * @param [out] pvalue   : char*                 ����Ԫ��ֵ��bufferָ��
 * @param [in]  size     : const unsigned int    ����Ԫ��ֵ��buffer��С
 *
 * @return  int          �������
 * @retval  1            �ɹ�
 * @retval  0            �����ڸ�Ԫ��
 * @retval  -1           ʧ��
 *
 * @note ���vector�д��ڶ��Ԫ�ص�����Ϊpname, ��᷵��vector�����һ��.
 *
**/
int uln_vec_getvalue(const uln_vector_t* pvec, const char* pname,
                     char* pvalue, const unsigned int size);


/**
 * @brief ����vector��pname��Ӧ��Ԫ��ֵ�����vector�д��ڶ��pname, ���޸����һ��.
 * ���������pname�����(pname, pvalue)����vectorĩ, ��push_back.
 *
 * @param [in] pvec        : uln_vector_t* vectorָ��
 * @param [in] pname       : const char*   Ԫ������
 * @param [in] pvalue      : const char*   Ԫ��ֵ
 * @return  int            �������
 * @retval  1              ��pname, pvalue push_back��vector��󣬳ɹ�
 * @retval  2              vector�д���pname��Ԫ�أ�ֱ���޸ģ��ɹ�
 * @retval <0              ʧ��(�������Ϸ���)
**/
int uln_vec_setvalue(uln_vector_t* pvec,
                     const char* pname, const char* pvalue);

/**
 * @brief ɾ��Ԫ��pname�����Ӧ��ֵ.
 * ��vector�д��ڶ��pname, ȫ����ɾ��.
 *
 * @param [in] pvec    : uln_vector_t*   vectorָ��
 * @param [in] pname   : const char*     Ԫ����.
 * @return  int        �������
 * @retval  -1         ʧ��(�������Ϸ�)
 * @retval  >=0        ɾ����Ԫ�ظ���
**/
int uln_vec_delentry(uln_vector_t* pvec, const char* pname);


////////////////////////////////////////////////////////////
////��չ����֮��Ľӿ�..
/**
 * @brief  ��ʼ������.
 *
 * @return  uln_vector_ex2_t*  ��ʼ���������ָ�룬��NULL
 * @retval  ��NULL  �ɹ������������ָ��
 * @retval  NULL    ʧ��
**/
uln_vector_ex2_t* uln_vec_init_ex2(void);


/**
 * @brief �ͷŸ�vector�ڴ�.
 *
 * @param [in] pvec   : uln_vector_ex2_t*  ���ͷŵ�vectorָ��.
 * @return  void 
**/
void uln_vec_free_ex2(uln_vector_ex2_t* pvec);


/**
 * @brief ��Ԫ��(pname, pvalue)����vector���.
 *
 * @param [in] pvec     : uln_vector_ex2_t*  vectorָ��
 * @param [in] pname    : const char*    Ԫ������
 * @param [in] pvalue   : const char*    Ԫ��ֵ
 * @return  int  �������
 * @retval  1    �ɹ�
 * @retval -1    ʧ��(�ڴ�ʧ��)
 * @retval -2    ʧ��, pname���Ϸ�(���ȹ������ָ��)
 * @retval -3    ʧ��, pvalue���Ϸ�(���ȹ������ָ��)
 * @retval -4    ʧ��, pvec���Ͻ�(vec size����ȷ��pvecΪ��ָ��)
**/
int uln_vec_pushback_ex2(uln_vector_ex2_t* pvec,
                         const char* pname, const char* pvalue);


/**
 * @brief  �������л��pname��ӦԪ�ص�Ԫ��ֵ.
 *
 * @param [in]  pvec     : const uln_vector_ex2_t*   vectorָ��
 * @param [in]  pname    : const char*           Ԫ������
 * @param [out] pvalue   : char*                 ����Ԫ��ֵ��bufferָ��
 * @param [in]  size     : const unsigned int    ����Ԫ��ֵ��buffer��С
 *
 * @return  int          �������
 * @retval  1            �ɹ�
 * @retval  0            �����ڸ�Ԫ��
 * @retval  -1           ʧ��
 *
 * @note ���vector�д��ڶ��Ԫ�ص�����Ϊpname, ��᷵��vector�����һ��.
 *
**/
int uln_vec_getvalue_ex2(const uln_vector_ex2_t* pvec, const char* pname,
                         char* pvalue, const unsigned int size);


/**
 * @brief ����vector��pname��Ӧ��Ԫ��ֵ�����vector�д��ڶ��pname, ���޸����һ��.
 * ���������pname�����(pname, pvalue)����vectorĩ, ��push_back.
 *
 * @param [in] pvec        : uln_vector_ex2_t* vectorָ��
 * @param [in] pname       : const char*   Ԫ������
 * @param [in] pvalue      : const char*   Ԫ��ֵ
 * @return  int            �������
 * @retval  1              ��pname, pvalue push_back��vector��󣬳ɹ�
 * @retval  2              vector�д���pname��Ԫ�أ�ֱ���޸ģ��ɹ�
 * @retval <0              ʧ��(�������Ϸ���)
**/
int uln_vec_setvalue_ex2(uln_vector_ex2_t* pvec,
                         const char* pname, const char* pvalue);

/**
 * @brief ɾ��Ԫ��pname�����Ӧ��ֵ.
 * ��vector�д��ڶ��pname, ȫ����ɾ��.
 *
 * @param [in] pvec    : uln_vector_ex2_t*   vectorָ��
 * @param [in] pname   : const char*     Ԫ����.
 * @return  int        �������
 * @retval  -1         ʧ��(�������Ϸ�)
 * @retval  >=0        ɾ����Ԫ�ظ���
**/
int uln_vec_delentry_ex2(uln_vector_ex2_t* pvec, const char* pname);

#endif
