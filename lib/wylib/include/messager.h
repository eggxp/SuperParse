//---------------------------------------------------------------------------

#ifndef messagerH
#define messagerH
#include <windows.h>
#include <string>
using namespace std;
//����COPY_DATA��Ϣ�������ݵ���

class  CMessager
{
private:
   HWND      m_HostWindow; //Զ�̴��ھ��
protected:
public:
   string    m_HostWindowClassName; //Զ�̴�������
public:
  __fastcall CMessager();
  __fastcall ~CMessager();
  bool       Connect();   //���ӵ�Ŀ�괰��
  bool       Connected(){return (m_HostWindow!=0);}
  bool       Send(DWORD Flag,void *DataBuf,int DataLen);
};

//---------------------------------------------------------------------------
#endif
