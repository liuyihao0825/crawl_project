 
 
 
/**
 * @file Receive.h
 * @author liuyihao
 * @date 2013/03/29 20:08:23
 * @brief �������࣬����url
 *  
 **/




#ifndef  __RECEIVE_H_
#define  __RECEIVE_H_

/* �������࣬����url */
class Receiver
{
    public:
        int StartReceiveThr(Dispatcher *pdispatch);       //��������url����

    private:
        pthread_t ptid;                                   //�߳�id
};














#endif  //__RECEIVE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
