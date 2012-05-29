//---------------------------------------------------------------------------

#ifndef serversocketH
#define serversocketH
#include <vcl.h>
#include <winsock.h>
#include "CommFunc.h"
#define ID_SOCKSERVER_EVENT_MSG		WM_USER + 1010
//�첽AsyncSelect������
typedef void __fastcall (__closure *TOnServerError)(SOCKET   ClientSocket,int ErrorCode,String ErrorInfo);
typedef void __fastcall (__closure *TOnData)(SOCKET   ClientSocket,char * Buf,int Len);
typedef void __fastcall (__closure *TOnSocketEvent)(SOCKET ClientSocket);

enum CESocketEvent{seCONNECT=0,seDISCONNECT,seSEND,seRECV,seERROR};
class CAsyncServerSocket
{
private:
  HINSTANCE    m_hInstance;
  SOCKET       m_ListenSocket;
  WNDPROC      m_pfOrgWndProc;
protected:
  bool          m_InitSuccess;
  bool          m_Connected;
  WORD          m_ServerPort;
  HWND          m_HWnd;
  void          Init();
  String        LastError;
  void         ThrowError(SOCKET   ClientSocket,int ErrorCode,const String &ErrorInfo);
  void         HookWindowWndProc();
  void         UnHookWindowWndProc();
  void __fastcall OnNetWindowMessage(Messages::TMessage &Message);
  bool         CreateSocketWindow();
  virtual void  OnSocketEvent(CESocketEvent Event,SOCKET SocketID);
public:
  __fastcall CAsyncServerSocket(HINSTANCE Instance);
  virtual __fastcall ~CAsyncServerSocket();
  bool        Start(WORD ListenPort);
  virtual bool        Stop();
  bool        IsActive(){return m_Connected;}
  SOCKET      GetSocketID(){return m_ListenSocket;}
  TOnServerError    OnError;            //�����¼�
  TOnSocketEvent  OnRecv;               //FD_READ �����ݵ���,���Խ���ʱ
  TOnSocketEvent  OnSend;             //FD_WRITE�¼�,���������ͻ�����׼������ ,���Է���ʱ
  TOnSocketEvent  OnClientConnect;      //FD_ACCEPT��������ͬ���Ժ�
  TOnSocketEvent  OnClientDisconnect;   //FD_CLOSE  �ͻ��˹ر�����ʱ
  String      GetIP(SOCKET Socket);
  String      GetLastErrorStr(){return LastError;}
  WORD        ListenPort(){return m_ServerPort;}
};



//---------------------------------------------------------------------------
#endif
