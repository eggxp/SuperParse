//---------------------------------------------------------------------------

#ifndef hookloaderH
#define hookloaderH
#include <vcl.h>
#include <ScktComp.hpp>
#define  LOAD_DLL_SUCCED WM_USER+0x9111
#define  LOAD_DLL_FAIL   WM_USER+0x9112
#define  INSTALL_HOOK_SUCCED  WM_USER+0x9121  //�Զ�����Ϣ,֪ͨ�������Ӽ��سɹ�
#define  UNINSTALL_HOOK_SUCCED  WM_USER+0x9122  //�Զ�����Ϣ,֪ͨ�������Ӽ��سɹ�
#define MSG_CONNECT      WM_USER+0x1129
#define MSG_DISCONNECT   WM_USER+0x1130
#define MSG_HINT         WM_USER+0x1131
#define MSG_SEND         WM_USER+0x1132
#define MSG_RECV         WM_USER+0x1133
#define MSG_KEY_UP       WM_USER+0x1134


struct tagSERVERINFO
{
  char      IP[20];
  WORD      Port;
  SOCKET    SocketId;
};
typedef BOOL WINAPI (*SET_MSG_HOOK) (DWORD, HWND, char *);
typedef BOOL WINAPI (*SET_CBT_HOOK)(bool IsActive,char *TagExeName,HWND HostWindow,char *AppDllName);
typedef void __fastcall (__closure *TOnHOOKMsg)(const String &Msg);
typedef void __fastcall (__closure *TOnTagConnect)(tagSERVERINFO *lpServerInfo);
typedef void __fastcall (__closure *TOnTagDisconnect)(SOCKET    SocketId);
typedef void __fastcall (__closure *TOnTagHotKey)(DWORD KeyValue);
typedef void __fastcall (__closure *TOnDataOP)(int OPType,char *Data,int DataLen);
enum{hsNOTACTIVE=0,hsDETECTOR_TAG,hsTAGRUNNING};

enum HOOKType{htMSGHOOK=0,htCBTHOOK};

enum NETOPType{noSEND=0,noRECV};
enum FIND_WINDOW_MODE{fwmCLASS,fwmNAME,fwmBOTH};
//��ģ����������HOOK dll
//---------------------------------------------------------------------------
class THookLoader
{

private:
  TForm      *  m_Parent;
  HINSTANCE     m_InjectDll;
  bool          m_AppDllRunning;
  TTimer        * timHookDetector;
  int           m_State; //��ǰ����״̬
  HOOKType      m_HookType; //�ҹ���ʽ
protected:
  SET_MSG_HOOK           m_fpMsgHookfunc;
  SET_CBT_HOOK           m_fpCBTHookfunc;
  Classes::TWndMethod  m_fpOrgWndProc;
  Classes::TWndMethod  m_fpParentDefWndProc;
  TOnHOOKMsg           m_fpOnHookMsg;
  FIND_WINDOW_MODE	   m_FindWindowMode;
  void __fastcall      ParentFormWndProc(Messages::TMessage &Message);
  void __fastcall      ProcMsgData(int Flag,void *lpData,int Len);
  void __fastcall      OnHookDetectorTimer(TObject *Sender);
  int __fastcall       LoadDLL(String AppDllPath);
  void                 LogMsg(const String &Msg);
  HWND				   FindTagWindow();

public:
  TOnTagConnect        pfOnTagConnect;          //Ŀ��������ӳɹ� �¼�
  TOnTagDisconnect     pfOnTagDisconnect;       //Ŀ�����Ͽ����� �¼�
  TOnTagHotKey         pfOnTagKeydown;          //Ŀ��������ȼ� �¼�
  TOnDataOP            pfOnNetDataOP;           //�������ݴ������
  String               TagFormClass;
  String			   TagFormName;		//Ŀ�괰����
  String               TagExeName;
public:
  __fastcall THookLoader(TForm * Parent,TOnHOOKMsg MsgOutputProc,Classes::TWndMethod ParentDefWndProc);
  __fastcall ~THookLoader();
  void SetActive(bool IsActive);
  __inline int  State(){return m_State;}
  __inline HOOKType GetHookType(){return m_HookType;}
  __inline void SetHookType(HOOKType HookType){m_HookType=HookType;}
  __inline void SetFindWindowMode(FIND_WINDOW_MODE Mode){m_FindWindowMode = Mode;}
};

#endif
