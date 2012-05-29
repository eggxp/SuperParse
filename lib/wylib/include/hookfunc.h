//---------------------------------------------------------------------------

#ifndef hookfuncH
#define hookfuncH
#include <windows.h>
#include <winsock.h>
#include <string>
#include "injlib.h"
#ifdef VCVERSION
#include "comm_stl.h"
#else
#include "CommFunc.h"
#endif
#include "alist.h"
using namespace std;
class CHookData
{
   public:
    string FuncName;        //������
    LPBYTE OrgFuncAddr;    //ԭ���ĺ���ָ���ַ
    LPBYTE NewFuncAddr;    //�滻��ĺ���ָ���ַ
   public:
  __fastcall CHookData();
  __fastcall ~CHookData();
};
//---------------------------------------------------------------------------
//����api�����Ĺ�����
class CHooker
{
private:
  HMODULE   m_Module;  //��̬���ӿ���
  string    m_DllName; //��̬���ӿ�����
  AList<CHookData> *HookFuncList;  //��Ҫhook�ĺ����б�
protected:
public:
public:
  __fastcall CHooker(char * DllName);
  __fastcall ~CHooker();
  void  BeginHookFunc();
  void  EndHookFunc();
  bool  RegisterFunc(char * FuncName,LPBYTE ReplaceFuncAddr); //ע���滻����,
  bool  IsHooked(){return  m_Module != NULL;}
  LPBYTE GetOrgFuncAddr(char * FuncName);
};

#endif
