//---------------------------------------------------------------------------
//���¼�¼

#ifndef srvthreadH
#define srvthreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <ScktComp.hpp>
//ע��
//�̳߳�ÿ���̵߳Ķ�ջ��Сֻ��32K
class CServerSocket;
enum ThreadState{tsWAIT,tsCLIENT_CONNECT,tsSERVERCONNECT,tsPROCESS_CLIENT,tsPROCESS_SERVER,tsCLOSE,tsCREATE_FAIL};
String GetThreadStateName(ThreadState StateFlag);
//---------------------------------------------------------------------------
class CServerThread
{
private:
	   int				m_Index;        //�̳߳ص��еı��
	   SOCKET 			m_ClientSocket;
	   CServerSocket  * m_ServerSocket;
       bool             m_ClientConnect; //�ͻ����Ƿ�������
	   String           m_ClientIP;
	   String           m_LastError;
	   bool				m_Terminated; //�Ƿ���Ҫ�����߳�
	   HANDLE 			m_Handle;  // �߳̾��
	   DWORD			m_ThreadID;      //�߳�ID
	   DWORD  			m_StackSize;
	   char			   * lpRecvBuffer;    //���ջ�����
	   char			   * lpSendBuffer;	  //���ͻ�����
	   DWORD			m_RecvBufSize; //ʵ�ʷ���Ľ��ջ�������С
	   DWORD			m_SendBufSize; //ʵ�ʷ���ķ��ͻ�������С
protected:
		void __fastcall Execute();
		static DWORD WINAPI ThreadProc(LPVOID lpParameter);
public:
	   void * 			lpUserData; //�û��Զ�������
	   ThreadState      State;

	   int    RecvLen();
       void   __fastcall Log();
	   void   __fastcall ErrLog();
public:
		__fastcall CServerThread(bool CreateSuspended,CServerSocket * ServerSocket,DWORD StackSize,int Index);
		__fastcall ~CServerThread();
        int Recv(char * lpBuffer,int Len);
        int Send(char * lpBuffer,int Len);
        void CloseSocket();
        void ShowLog(String LogStr);
        void ShowErrLog(String LogStr);
        String GetClientIP(){return m_ClientIP;}
		SOCKET GetSocket(){return m_ClientSocket;}
		void   Terminate(){m_Terminated=true;}//�����߳�����
		DWORD  GetThreadID(){return m_ThreadID;}
		HANDLE  GetThreadHandle(){return  m_Handle;}
		String  LastError(){return m_LastError;}
		char *  RecvBufPtr(){return lpRecvBuffer;} //��ȡ�������ݻ�����ָ��
		char *  SendBufPtr(){return lpSendBuffer;} //��ȡ�������ݻ�����ָ��
		DWORD   RecvBufSize(){return m_RecvBufSize;}  //��ȡʵ�ʷ���Ľ��ջ�������С
		DWORD   SendBufSize(){return m_SendBufSize;}//��ȡʵ�ʷ���ķ��ͻ�������С
		String  GetState();
		int		GetIndex(){return  m_Index;}  //��ȡ���̶߳������̳߳ص��еı��
};
//---------------------------------------------------------------------------
#endif
