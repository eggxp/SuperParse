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
   volatile long	      m_ClientCount; //��ǰ���ӵĿͻ�������
protected:
  SOCKET     m_ListenSocket;
  int		 m_ThreadStackSize;
  bool       m_IsActive;
  int		 m_ActiveThreadNumber;//ʵ�ʼ�����߳�����
  void       SetThreadPool(int ThreadNumber); //�����̳߳�
  void       FreeThreadPool();   //�ͷ��̳߳�������߳�
public:
  int       RecvTimeOut;    //���ճ�ʱ
  bool      CanShowLog;     //�Ƿ���ʾ��־��¼
  int		RecvBufSize;    //�������ݻ�������С
  int		SendBufSize;	//�������ݻ�������С
  WORD      Port;
  OnLogMethods  OnOutputLog;
  OnLogMethods  OnOutputErrorLog;
  String     	m_LastErrorStr;       //���Ĵ�����Ϣ
  //**************ע��*****************************************
  //Ϊ�˽�Լ�̶߳�ջ�ռ�,�̳߳�ÿ���߳�Ĭ�ϵĶ�ջ��Сֻ��64K
  //���лص�����ͳͳ�������߳�������,���Ծ�����Ҫʹ�ö�ջ����,������������new��̬��������
  //����ᵼ���̶߳�ջ���
  //�����Ҫ�õ���ľֲ���ջ,��ָ��ThreadStackSize����,ThreadStackSize������̫��,�ɽ������߳��������ܵ�Ӱ��
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
  int		 ActiveThreadNumber(){return m_ActiveThreadNumber;}
  void		 SetThreadStackSize(int Value){m_ThreadStackSize=Value;}
  int		 ClientCount(){return m_ClientCount;}
  void		 DecClientCount();
  int		 SendData(int ThreadIndex,char * lpBuffer,int Len);
  void		 CloseSocket(int ThreadIndex);
};

//---------------------------------------------------------------------------
#endif
