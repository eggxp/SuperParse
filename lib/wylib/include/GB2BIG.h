/*
����<->����ת����
ʵ�ּ��己���ֵ��໥ת��
����:������
����������: 2005.01.01
*/
#ifndef __GB2BIG_H__
  #define __GB2BIG_H__

  #ifdef __cplusplus
extern "C"
{
  #endif //__cplusplus
void    InitConvertTable();             //��ʼ�����,��������Ŀ���ʼ���ּ���
String  Gb2Big(String lpString);       // ����->����
String  Big2GBK(String lpString);     //����->����

  #ifdef __cplusplus
}
  #endif //__cplusplus
#endif __GB2BIG_H__