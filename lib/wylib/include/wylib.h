#ifndef WYLIBH
#define WYLIBH

#define WYLIB_VERSION  "1.1.4"
//����ͨ�ù���������Ԫ
#include "CommFunc.h"
#pragma comment(lib, "wycommon.lib")

//����zlibѹ����
#ifdef  USE_WY_ZLIB    //����zlib����ļ���ʽ��Ԫ
#include "ZLIBEX.hpp"
//�����ļ�
#pragma comment(lib, "zlibex.lib")
#endif

#endif