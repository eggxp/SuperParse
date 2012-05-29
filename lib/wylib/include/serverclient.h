//---------------------------------------------------------------------------

#ifndef serverclientH
#define serverclientH
#include <vcl.h>
#include <winsock.h>
#include "CommFunc.h"
//�������Ŀͻ��˴������,��ÿ���û��Ĵ���,���ԴӴ˻�������
class TServerClient;
typedef void __fastcall (__closure *TON_CLIENT_CLOSE)(SOCKET  SocketID);
typedef void __fastcall (__closure *TON_FREE)(TServerClient* ObjHandle);
class TServerClient
{
private:
  SOCKET       m_Socket;
protected:
  String       m_LastError;

public:
  TServerClient(SOCKET   Socket);
  virtual ~TServerClient();
  virtual int 	  SendBuf(char * Buffer,int Len);
  int	  SendString(String Data); //����һ��String�е�����
  virtual int     RecvBuf(char * DesBuffer,int BufferLen);  //recv���ݵ���������
  String  RecvString(); //recv���ݵ�һ��String�в�����
  int	  RecvLength(); //�鿴recv���������е����ݳ���
  bool    Close(); //�رպʹ˿ͻ��˵�����
  String  LastError(){return m_LastError;} //���Ĵ�����Ϣ
  String  GetIP();
  SOCKET  SocketID(){return m_Socket;}
  void *  lpUserData; //�û��Զ�������
  bool    IsConnect(){return !(m_Socket == INVALID_SOCKET);}
//�¼�֪ͨ
  TON_CLIENT_CLOSE    OnClientClose;   //�ͻ��˹ر�
  TON_FREE            OnFree;          //�����ͷŵ�ʱ��
};


//---------------------------------------------------------------------------
#endif
