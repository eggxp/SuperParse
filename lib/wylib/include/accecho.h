//---------------------------------------------------------------------------

#ifndef accechoH
#define accechoH
#include <vcl.h>
#include "blockclient.h"


typedef void __fastcall (__closure *TON_REFRESH_SUCCESS)(void);
class CAccPing
{
private:
  TStringList * ServerList;
  TStringList * ServerInfo;
  int			BestServerIndex;
  bool			bNotActiveServer;
protected:
  CBlockSocket BlockSocket; 
  static DWORD WINAPI RecvThreadFunc(LPVOID Parameter);
  String GetDelayString(DWORD DelayTime);
public:
  __fastcall CAccPing();
  __fastcall ~CAccPing();
  void SetServerList(TStrings * ServerIPList);
  String	GetServerInfo(int Index);
  int		Count(){return ServerList->Count;}
  void		RefreshServerInfo(); //ˢ�·�����״̬
  TON_REFRESH_SUCCESS  OnRefreshSuccess;
  int		GetBestServer(){return BestServerIndex;}   //��ȡ�ٶ���ѵķ�����
  bool		NotActiveServer(){return bNotActiveServer;}//���з��������޷�����
};


//---------------------------------------------------------------------------
#endif
