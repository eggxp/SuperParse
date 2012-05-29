//---------------------------------------------------------------------------
//���¼�¼
//2006.06.06 BY bluely
//Ϊnethandle.h��TNetHandle�������sock5����Э��֧��,���л���nethandle������ͻ���ͨѶ������ֱ��֧��sock5������

#ifndef nethandleH
#define nethandleH
#include <Classes.hpp>
#include <ScktComp.hpp>
#include "clientsocket.h"
class TSockProxyClient;
typedef struct tagNetMSG
{   // msg
    int    MessageID;
    int    SubCmdID;
	WPARAM wParam;
    LPARAM lParam;
} NET_MSG,*lpNET_MSG;

enum NET_MSG_TYPE{nmCONNECT=0,nmDISCONNECT,nmError,nmRECV,nmSEND,nmCanSEND,nmDECRECV,nmDECSEND,nmSelfSEND,nmSock5Finish};
typedef void  __fastcall (__closure *NetOnOutputLog)(const String &ValueStr);
typedef void  __fastcall (__closure *NetOnNetMessage)(NET_MSG_TYPE Type,void *Data,int DataLen);
typedef void  __fastcall (__closure *ProxyServerMessage)(NET_MSG_TYPE Type,String &RecvData);
//������Ϣ�������,�ӿ���
class TNetHandle
{
private:
   CClientSocket   *  _Client; //�첽��ϢSocket����
   TSockProxyClient	 *  _Sock5Protocol; //Sock5Э�鴦�����
   String			 _Sock5ServerIP;   //Sock5 ������IP
   WORD				 _Sock5Port;      //Sock5�������˿�
   DWORD			 LastRecvTime;
protected:
  void __fastcall OnClientConnect(CClientSocket  *ClientSocket);
  void __fastcall OnClientDisconnect(CClientSocket  *ClientSocket,bool ServerDisconnect);
  void __fastcall OnClientError(CClientSocket  *ClientSocket,int ErrorCode,char *ErrorInfo);
  void __fastcall OnClientRead(CClientSocket  *ClientSocket,SOCKET SocketID);
  void __fastcall OnClientSend(CClientSocket  *ClientSocket,SOCKET SocketID);
  virtual int __fastcall DispatchSocketWindowMsg(String &RecvData)=0;   //����Զ����������Ϣ(���,���ܷ����������),���麯��,�̳���ʵ��
  virtual void __fastcall DispatchNetworkQueue()=0;                  //��������������,���麯��,�̳���ʵ��
  virtual void __fastcall DispatchNetworkMsg(NET_MSG &NetMsg)=0;    //������������Ϣ,���麯��,�̳���ʵ��
  virtual void __fastcall PackSend(String &OrgData)=0;              //������ܴ���������,���麯��,�̳���ʵ��
  virtual void __fastcall PackSend(char * Data,int Len)=0;          //������ܴ���������,���麯��,�̳���ʵ��
  virtual void __fastcall OnSocketEvent(NET_MSG_TYPE NetMsg)=0;    //����֪ͨ�̳��෢���˺�������socket�¼�
  void __fastcall PostSocketMessage(NET_MSG_TYPE Type,void *Data,int DataLen);
protected:
   String          LastErrInfo;  //������Ϣ
   String          RecvCacheData;  //Recvδ�������������
   static          __fastcall void OnSocketError(int ErrorCode);
   void 		   LoginToProxy();
   bool 		   Recv_ProxyReturn(const String &RecvData);
public:
	NetOnOutputLog  OutputLog;          //ʵʱ�������ʾ��Ϣ�Ļص�����
	NetOnNetMessage OnSocketMessage;   //֪ͨʹ����������Ϣ�Ļص�����
	int  SendByteTotal; //�ۼƽ��ܷ����
	int  RecvByteTotal; //�ۼƷ��ͷ����
	bool    UseSock5Proxy; //�Ƿ�ʹ��Sock5����

public:
  __fastcall TNetHandle(TForm * AOwner=NULL);
  virtual __fastcall ~TNetHandle();
  void SetRemoteAddr(const String &IP,WORD Port); //����Զ�̷�������IP�Ͷ˿�
  int  SendData(String Data);                     //�ṩ�������ݵĽӿ�
  int  SendBuf(char *buf,int len);
  __inline bool IsActive(){return _Client->IsConnected();}       //�Ƿ�������״̬
  void OutputInfo(const String &Info);            //�����ʾ��Ϣ
  bool Connect();                                 //��������
  void DisConnect();                              //�Ͽ�����
  String GetHostAddr();
  DWORD	 IdleTime();		//����RECV����ʱ��,��λ����
  void SetSock5(String  Sock5ServerIP,  //Sock5 ������IP
				WORD    Sock5ServerPort, //Sock5�������˿�
				bool    UseAuthentication, //�Ƿ���Ҫ��֤�û���
				String  UserName,       //Sock5�������û���
				String  PassWord);       //Sock5����������
  SOCKET  SocketID(){return _Client->SocketID();} //����socketid
};

//---------------------------------------------------------------------------
//�����������
class TProxyServer
{
private:
   TNetHandle       * m_lpClientNetHandle;
   TServerSocket    * ServerSocket;
   TCustomWinSocket * m_LocalActiveServerSocket;
   NetOnNetMessage    m_pfOrgClientMessage;
   TStringList      * m_lpClientWaitDataBuf;   //Client����δ�ɹ���ʱ���ݴ�����ݻ�����
protected:
  void __fastcall ServerSocketClientConnect(TObject *Sender, TCustomWinSocket *Socket);
  void __fastcall ServerSocketClientDisconnect(TObject *Sender, TCustomWinSocket *Socket);
  void __fastcall ServerSocketClientError(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent,int &ErrorCode);
  void __fastcall ServerSocketClientRead(TObject *Sender, TCustomWinSocket *Socket);
  void __fastcall OnClientSocketMsg(NET_MSG_TYPE Type,void *Data,int DataLen);
public:
  ProxyServerMessage OnServerSocketMessage;
public:
  __fastcall TProxyServer();
  __fastcall ~TProxyServer();
  void __fastcall SetClientNetHandle(TNetHandle *ClientNetHandle);
  __inline void __fastcall SetServerPort(WORD Port){ServerSocket->Port = Port;}
  __inline WORD __fastcall GetPort(){return ServerSocket->Port;}
  __inline void __fastcall SetActive(bool IsActive){ServerSocket->Active = IsActive;}
  __inline bool __fastcall IsActive(){return ServerSocket->Active;}
  int      SendData(char *Data,int Len);

};

#endif
