//---------------------------------------------------------------------------

#ifndef cpuinfoH
#define cpuinfoH
#include <Classes.hpp>
#include <Windows.h>
#include <time.h>
#include <ExtCtrls.hpp>
typedef void __fastcall (__closure *TOnRefresh)(DWORD CPUUsage);
class TCPUInfo
{
private:
   bool InitSuccess;
protected:
   TTimer * RefreshTimer;
   void __fastcall OnRefresh(System::TObject* Sender);
   int        RefreshUsage(); //��ȡ��ǰռ����
public:
  __fastcall TCPUInfo();
  __fastcall ~TCPUInfo();
  TOnRefresh pfOnRefreshCPUUsage;


};

//---------------------------------------------------------------------------
#endif
