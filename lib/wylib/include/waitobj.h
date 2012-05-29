//---------------------------------------------------------------------------

#ifndef waitobjH
#define waitobjH
#include <vcl.h>
//------------------------------------------------------------------------------
class TWaitForObj
{
private:
    DWORD m_LastWaitTime;
    int   m_TimeOut;
protected:
    String m_WaitInfo;

public:
  __fastcall TWaitForObj();
  __fastcall ~TWaitForObj();
  DWORD      WaitFor(DWORD TimeOut,const String &WaitInfo);  //��ʼ�ȴ�
  __inline int        GetElapseTime(){return (GetTickCount()-m_LastWaitTime);} //��ȡ�Ѿ��ȴ���ʱ��
  __inline int        RemainTime(){return (m_TimeOut-GetElapseTime());} //ʣ��ȴ�ʱ��
  void       Reset(){m_LastWaitTime=0;}           //����,ֹͣ�ȴ�
  bool       IsWaiting(){return (m_LastWaitTime!=0 && GetElapseTime() < m_TimeOut);} //�����Ƿ񻹴��ڵȴ�״̬
};

//---------------------------------------------------------------------------
#endif
