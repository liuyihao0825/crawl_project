/***************************************************************************
 *
 * Copyright (c) 2007 Baidu.com, Inc. All Rights Reserved
 * $Id: uln_vector.h,v 1.8.4.2 2010/03/23 14:52:00 zhangyan04 Exp $ 
 * 
 **************************************************************************/


#ifndef ULN_VECTOR_H
#define ULN_VECTOR_H

const unsigned int ULN_MAX_NAME_LENGTH  = 32;          ///< 最大名字长度
const unsigned int ULN_MAX_VALUE_LENGTH = 256;         ///< 最大值的长度
const int ULN_DEFAULT_COUNT             = 16;          ///< 默认(最初)时vector的容量

typedef struct ULN_PAIR {
    char m_name[ULN_MAX_NAME_LENGTH];       ///< pair的名字
    char m_value[ULN_MAX_VALUE_LENGTH];     ///< pair的值
} uln_pair_t;

typedef struct ULN_VEC {
    int         m_size;                     ///< m_list里的空间大小
    int         m_curpos;                   ///< m_list里的元素个数
    uln_pair_t* m_list;                     ///< m_list，存uln_pair_t的数组
} uln_vector_t;

////////////////////////////////////////////////////////////
///扩展长度之后的结构
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
 * @brief  初始化数组.
 *
 * @return  uln_vector_t*  初始化后的数组指针，或NULL
 * @retval  非NULL  成功，代表该数组指针
 * @retval  NULL    失败
**/
uln_vector_t* uln_vec_init(void);


/**
 * @brief 释放该vector内存.
 *
 * @param [in] pvec   : uln_vector_t*  需释放的vector指针.
 * @return  void 
**/
void uln_vec_free(uln_vector_t* pvec);


/**
 * @brief 把元素(pname, pvalue)放入vector最后.
 *
 * @param [in] pvec     : uln_vector_t*  vector指针
 * @param [in] pname    : const char*    元素名称
 * @param [in] pvalue   : const char*    元素值
 * @return  int  操作结果
 * @retval  1    成功
 * @retval -1    失败(内存失败)
 * @retval -2    失败, pname不合法(长度过长或空指针)
 * @retval -3    失败, pvalue不合法(长度过长或空指针)
 * @retval -4    失败, pvec不合洁(vec size不正确或pvec为空指针)
**/
int uln_vec_pushback(uln_vector_t* pvec,
                     const char* pname, const char* pvalue);


/**
 * @brief  在数组中获得pname对应元素的元素值.
 *
 * @param [in]  pvec     : const uln_vector_t*   vector指针
 * @param [in]  pname    : const char*           元素名称
 * @param [out] pvalue   : char*                 存入元素值的buffer指针
 * @param [in]  size     : const unsigned int    存入元素值的buffer大小
 *
 * @return  int          操作结果
 * @retval  1            成功
 * @retval  0            不存在该元素
 * @retval  -1           失败
 *
 * @note 如果vector中存在多个元素的名称为pname, 则会返回vector中最后一个.
 *
**/
int uln_vec_getvalue(const uln_vector_t* pvec, const char* pname,
                     char* pvalue, const unsigned int size);


/**
 * @brief 设置vector中pname对应的元素值，如果vector中存在多个pname, 则修改最后一个.
 * 如果不存在pname，则把(pname, pvalue)放在vector末, 即push_back.
 *
 * @param [in] pvec        : uln_vector_t* vector指针
 * @param [in] pname       : const char*   元素名称
 * @param [in] pvalue      : const char*   元素值
 * @return  int            操作结果
 * @retval  1              把pname, pvalue push_back在vector最后，成功
 * @retval  2              vector中存在pname的元素，直接修改，成功
 * @retval <0              失败(参数不合法等)
**/
int uln_vec_setvalue(uln_vector_t* pvec,
                     const char* pname, const char* pvalue);

/**
 * @brief 删除元素pname及其对应的值.
 * 若vector中存在多个pname, 全部都删除.
 *
 * @param [in] pvec    : uln_vector_t*   vector指针
 * @param [in] pname   : const char*     元素名.
 * @return  int        操作结果
 * @retval  -1         失败(参数不合法)
 * @retval  >=0        删除的元素个数
**/
int uln_vec_delentry(uln_vector_t* pvec, const char* pname);


////////////////////////////////////////////////////////////
////扩展长度之后的接口..
/**
 * @brief  初始化数组.
 *
 * @return  uln_vector_ex2_t*  初始化后的数组指针，或NULL
 * @retval  非NULL  成功，代表该数组指针
 * @retval  NULL    失败
**/
uln_vector_ex2_t* uln_vec_init_ex2(void);


/**
 * @brief 释放该vector内存.
 *
 * @param [in] pvec   : uln_vector_ex2_t*  需释放的vector指针.
 * @return  void 
**/
void uln_vec_free_ex2(uln_vector_ex2_t* pvec);


/**
 * @brief 把元素(pname, pvalue)放入vector最后.
 *
 * @param [in] pvec     : uln_vector_ex2_t*  vector指针
 * @param [in] pname    : const char*    元素名称
 * @param [in] pvalue   : const char*    元素值
 * @return  int  操作结果
 * @retval  1    成功
 * @retval -1    失败(内存失败)
 * @retval -2    失败, pname不合法(长度过长或空指针)
 * @retval -3    失败, pvalue不合法(长度过长或空指针)
 * @retval -4    失败, pvec不合洁(vec size不正确或pvec为空指针)
**/
int uln_vec_pushback_ex2(uln_vector_ex2_t* pvec,
                         const char* pname, const char* pvalue);


/**
 * @brief  在数组中获得pname对应元素的元素值.
 *
 * @param [in]  pvec     : const uln_vector_ex2_t*   vector指针
 * @param [in]  pname    : const char*           元素名称
 * @param [out] pvalue   : char*                 存入元素值的buffer指针
 * @param [in]  size     : const unsigned int    存入元素值的buffer大小
 *
 * @return  int          操作结果
 * @retval  1            成功
 * @retval  0            不存在该元素
 * @retval  -1           失败
 *
 * @note 如果vector中存在多个元素的名称为pname, 则会返回vector中最后一个.
 *
**/
int uln_vec_getvalue_ex2(const uln_vector_ex2_t* pvec, const char* pname,
                         char* pvalue, const unsigned int size);


/**
 * @brief 设置vector中pname对应的元素值，如果vector中存在多个pname, 则修改最后一个.
 * 如果不存在pname，则把(pname, pvalue)放在vector末, 即push_back.
 *
 * @param [in] pvec        : uln_vector_ex2_t* vector指针
 * @param [in] pname       : const char*   元素名称
 * @param [in] pvalue      : const char*   元素值
 * @return  int            操作结果
 * @retval  1              把pname, pvalue push_back在vector最后，成功
 * @retval  2              vector中存在pname的元素，直接修改，成功
 * @retval <0              失败(参数不合法等)
**/
int uln_vec_setvalue_ex2(uln_vector_ex2_t* pvec,
                         const char* pname, const char* pvalue);

/**
 * @brief 删除元素pname及其对应的值.
 * 若vector中存在多个pname, 全部都删除.
 *
 * @param [in] pvec    : uln_vector_ex2_t*   vector指针
 * @param [in] pname   : const char*     元素名.
 * @return  int        操作结果
 * @retval  -1         失败(参数不合法)
 * @retval  >=0        删除的元素个数
**/
int uln_vec_delentry_ex2(uln_vector_ex2_t* pvec, const char* pname);

#endif
