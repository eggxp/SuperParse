//---------------------------------------------------------------------------

#ifndef servermgrH
#define servermgrH
#include "serversocket.h"
#include "serverclient.h"
#include "amap.h"
//---------------------------------------------------------------------------
//���ӹ����ά���ͻ����б�� ServerSocket
typedef TServerClient*  __fastcall (__closure *TUSER_NEW_CLIENTOBJ)(SOCKET Socket);
class CASynServerMgr : public CAsyncServerSocket
{
private:
  AIndexList<TServerClient> * m_ClientList;
protected:
  virtual void  OnSocketEvent(CESocketEvent Event,SOCKET SocketID);
  void __fastcall OnClientClose(SOCKET  SocketID);
  TServerClient * AddClient(SOCKET SocketID);
  void			  DelClient(SOCKET SocketID);
public:
  __fastcall 		  CASynServerMgr(HINSTANCE Instance);
  virtual __fastcall ~CASynServerMgr();
  int				Count(){return m_ClientList->Count();}
  TServerClient * 	At(int Index){return  m_ClientList->At(Index);}
  TServerClient *   Find(SOCKET SocketID);
  virtual bool      Stop();
  TUSER_NEW_CLIENTOBJ   OnUserNewClient; //���û�����TServerClient�ļ̳����֪ͨ����
};
#endif
