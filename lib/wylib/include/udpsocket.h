//---------------------------------------------------------------------------

#ifndef udpsocketH
#define udpsocketH
#include <vcl.h>
#include <winsock.h>
#include "CommFunc.h"
//udp socket����,���ǿͻ������Ƿ�������
typedef void __fastcall (__closure *TOnUDPError)(int ErrorCode,const String &ErrorInfo);
typedef void __fastcall (__closure *TOnUDPRead)(char * SenderIP,char * Data,int Len);
class  CUDPSocket
{
private:
   WORD 		Port;
   WSADATA 		wsd;
   SOCKET  		ServerSocket;
   SOCKET		ClientSocket;
   SOCKADDR_IN  Sender;
   SOCKADDR_IN  Local;
   bool			CreateSocket();
   bool			InitClientSocket();
   bool			Active;
   int			SYSRecvBuffer; //ϵͳ���ջ�������λKB
protected:
   void ShowError(int ErrorCode,const String &Info);
   static DWORD WINAPI RecvThreadFunc(LPVOID Parameter); //���շ���̺߳���
public:
   CUDPSocket();
   ~CUDPSocket();
   void  Open();
   void	 Stop();
   bool  IsActive(){return Active;}
   void	 SetPort(WORD _Port){Port = _Port;}
   int __fastcall SendData(String DesIP,WORD DesPort,char * Data,int Len);
   void	 SetRecvBufSize(int KBSize){SYSRecvBuffer = KBSize*1024;} //ϵͳ���ջ�������λKB
   //�ص�֪ͨ�ӿ�
   TOnUDPError OnError;
   TOnUDPRead  OnRead;  //OnRead�����߳�������,��ע�������̰߳�ȫ����

};
//---------------------------------------------------------------------------
#endif
