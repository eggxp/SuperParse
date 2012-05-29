//---------------------------------------------------------------------------
//2006.06.06 by bluely  : ������Threadͬʱ������������޷������̵߳�����
#ifndef blockserverH
#define blockserverH
#include <vcl.h>
#include <SyncObjs.hpp>
#include <ScktComp.hpp>
#include "alist.h"

class CServerThread;
typedef void __fastcall (__closure * OnThreadMethods)(CServerThread * Thread);
typedef void __fastcall (__closure * OnLogMethods)(String Log);
struct ThreadInfo
{
  DWORD   ThreadID;
  int     State;
  SOCKET  ClientSocket;
  String  ClientIP;
  void *  UserData;
};

//�����̳߳ط�ʽ��Socket Server
class CServerSocket
{
private:
   AList<CServerThread> * m_ThreadPool; //�̳߳�
   TCriticalSection     * m_GlobalLock; //������
   TStringList          * m_LogList;
protected:
  SOCKET     m_ListenSocket;
  bool       m_IsActive;
  void       SetThreadPool(int ThreadNumber); //�����̳߳�
  void       FreeThreadPool();   //�ͷ��̳߳�������߳�
public:
  int       RecvTimeOut;    //���ճ�ʱ
  bool      CanShowLog;     //�Ƿ���ʾ��־��¼
  WORD      Port;
  OnLogMethods  OnOutputLog;
  OnLogMethods  OnOutputErrorLog;
  String     m_LastErrorStr;       //���Ĵ�����Ϣ
  OnThreadMethods  OnThreadBegin;     //�ڴ˺�����ʼ���̱߳���
  OnThreadMethods  OnThreadClientAccept;  //�ڴ˺��������û��Զ��崦��
  OnThreadMethods  OnThreadEnd;
public:
  __fastcall CServerSocket();
  __fastcall ~CServerSocket();
  bool       Start(int PoolSize);            //��ʼ����
  bool       Stop();             //��������
  SOCKET     SafeAccept(struct sockaddr FAR* addr,int FAR* addrlen);
  int        ThreadPoolSize(){return m_ThreadPool->Count();}
  bool       IsActive(){return m_IsActive;}
  bool       GetThreadInfo(int ThreadIndex,ThreadInfo * ThreadInfoOut);
  void       ShowLog(String Log);
  void       ShowErrorLog(String Log);
};

//---------------------------------------------------------------------------
#endif
