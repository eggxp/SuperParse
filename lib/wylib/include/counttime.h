//---------------------------------------------------------------------------
//��ȷʱ����ͳ���࣬���ڳ������ܷ���
//By LinYi 2004.3.31
//�÷�:
//CTimeCount TimeCount;
//TimeCount.BeginCount();
// ���������....
//double Havetimes = TimeCount.EndCount();
//Havetimes���ǳ�������������ĵ�ʱ�䣬��λ����(ms)

#ifndef counttimeH
#define counttimeH
#include <windows.h>

class CTimeCount
{
private:
   LARGE_INTEGER StartCountValue,EndCountValue;
   double Freq,Minus;
protected:
   bool IsBegin;
public:
  __fastcall CTimeCount();
  __fastcall ~CTimeCount();
  void __fastcall BeginCount();
  double __fastcall EndCount();

};

//---------------------------------------------------------------------------
#endif
