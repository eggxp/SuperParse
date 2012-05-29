//---------------------------------------------------------------------------

#ifndef clientsocketH
#define clientsocketH
#include <vcl.h>
#include <winsock.h>
#define ID_SOCKCLIENT_EVENT_MSG		WM_USER + 1000
/***************************************************************************
 *  �� �� ����clientsocket.cpp
 *  ��    ����1.00.0                                                  
 *  ��    �ߣ�Bluely
 *  ��Ԫ���ܣ� ����WSAAsyncSelectģʽ��Socket��װ�࣬�����ڿͻ���
 *  ʹ�þ�����������demo��Ԫ
 *
 *  ���¼�¼��
 *  2005-03-21    ��һ���汾
 *  2005-03-22    �ڴ�����Ϣ�ص��������ж�Message.WParam != m_ClientSocketID�ж�,��ֹͬһ�����ڲ�ͬ��Client Socket��Ϣ����
 *  2005-03-23    ����Disconnect����û���ж϶Ͽ�״̬���ܵ����û�����ݹ������
                  ������������������ʱ��û�жϿ��û�֪ͨ�ص�����,���ܵ��º���ָ�����ʧ��

    ����:
      ʹ�ø�����ģʽ���ܻᵼ��һЩ����,�滻�����ڵ���Ϣ������,������������(����CClientSocket�Լ�����һ��ʵ��)Ҳ����������
      ����,���ܻᵼ����Ϣ����������ʧЧ

 *
 ***************************************************************************/
// WSAAsyncSelectģʽͨ��������Ϣ֪ͨSocket�¼�
//���Դ���ӵ���������캯��
//  __fastcall CClientSocket(HINSTANCE Instance);   CClientSocket�Լ���������
//  __fastcall CClientSocket(TForm *ParentForm);    ʹ�����е�VCL����,�������Լ��Ĵ���
//---------------------------------------------------------------------------
class CClientSocket;
typedef void __fastcall (__closure *TOnConnect)(CClientSocket  *ClientSocket);
typedef void __fastcall (__closure *TOnDisconnect)(CClientSocket  *ClientSocket,bool ServerDisconnect=false);
typedef void __fastcall (__closure *TOnRecv)(CClientSocket  *ClientSocket,SOCKET SocketID);
typedef void __fastcall (__closure *TOnSend)(CClientSocket  *ClientSocket,SOCKET SocketID);
typedef void __fastcall (__closure *TOnError)(CClientSocket  *ClientSocket,int ErrorCode,char *ErrorInfo);
class CClientSocket
{
private:
   bool         m_Connected;
   SOCKET       m_ClientSocketID;
   HWND         m_HWnd;
   HINSTANCE    m_hInstance;
   bool         m_InitSuccess;
   WNDPROC      m_pfOrgWndProc;
   TWndMethod   m_pfFormUserWndProc;
   WSADATA      wsaData;
   TForm *      m_ParentForm;
   bool         m_ParentWindowMode; //��ʹ����������ģʽ
   void         Init();
   void         HookWindowWndProc();
   void         UnHookWindowWndProc();
   bool         CreateSocketWindow();
   void         ThrowError(int ErrorCode);
   void         CloseSocket();
protected:
   char          m_ServerIP[256];
   WORD          m_ServerPort;
   //BCB
   void __fastcall OnNetWindowMessage(Messages::TMessage &Message);
   //VC
   static LRESULT CALLBACK DefWindowMessageProc(HWND WinHwnd,UINT Msg, WPARAM wParam, LPARAM lParam);
public:
  CHAR          LastError[256];  //���Ĵ�����Ϣ
  //�¼��ص�����ָ��
  TOnConnect    OnConnect;
  TOnDisconnect OnDisconnect;
  TOnRecv       OnRecv;
  TOnSend       OnSend;         //���ݻ�����׼���ÿ��Է���
  TOnError      OnError;
  DWORD        UserData;  //�û��Զ�������
public:
  //���������
  __fastcall            CClientSocket(HINSTANCE Instance);
  __fastcall            CClientSocket(TForm *ParentForm);
  virtual __fastcall    ~CClientSocket();

  //�����������
  bool                  Connect();                                 //����
  bool                  Disconnect(bool ServerDisconnect=false);   //�Ͽ�����
  int                   ReceiveLength();                           //��ǰ���շ���ĳ���
  int                   RecvBuf(char * Buf,int Len);              //��������,��OnRecv�������
  int                   SendBuf(char * Buf,int Len);              //��������
  __inline bool         IsConnected(){return (m_Connected && m_ClientSocketID != INVALID_SOCKET);}        //�жϵ�ǰ�Ƿ�����
  __inline              SOCKET SocketID(){return m_ClientSocketID;} //��ȡ��ǰSocket
  //���ú����ö�ȡ����
  void                  SetServerIP(char * IP);
  void                  SetServerPort(WORD Port);
  char *                GetServerIP(){return m_ServerIP;}
  __inline WORD         GetServerPort(){return m_ServerPort;}

};

#endif
