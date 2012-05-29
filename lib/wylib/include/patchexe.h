//---------------------------------------------------------------------------

#ifndef patchexeH
#define patchexeH
#include <vcl.h>
#include "alist.h"
//��߮
//2005.06.03 ��һ���汾
#define MAX_PATCH_LEN  16
#define DATA_HEAD_FLAG 0xaadc //�������ݵ�����ͷ��־
//------------------------------------------------------------------------------
//ִ��ĳ������,�����ڽ���ִ��֮ǰ�޸Ľ��̴���,Ȼ��ָ���������
#pragma pack(push, 1)

struct tagPatchAddrInfo
{
  DWORD Address; //ԭʼ��ַ
  int   Len;     //����
  BYTE  OrgCodeData[MAX_PATCH_LEN]; //ԭʼ����
  BYTE  NewCodeData[MAX_PATCH_LEN]; //�޸ĺ������
};
#pragma pack(pop)
//------------------------------------------------------------------------------
class TPatchProcess
{
private:
  AList<tagPatchAddrInfo> * m_PatchInfoList;
protected:
  void PatchCode(HANDLE ProcessHandle,DWORD ProcessID);
  bool PatchRecord(HANDLE ProcessHandle,DWORD ProcessID,tagPatchAddrInfo * lpPatchRecord);
  tagPatchAddrInfo *  ExistsAddress(DWORD Address);
public:
  String LastError;
  int    FailCount; //�ڴ�patchʧ�ܼ���
public:
  __fastcall TPatchProcess();
  __fastcall ~TPatchProcess();
  DWORD RunExe(const String &Cmdline,String DirName,int Visibility = SW_SHOW);
//------------------------------------------------------------------------------
//���һ���޸ļ�¼
//����: Ŀ���ַ,Ŀ�����ݳ���,ԭʼ����,������
//����ֵ: �ɹ����� True,ʧ�ܷ���false
//------------------------------------------------------------------------------
  bool AddPatchInfo(DWORD Addrees,int Len,LPBYTE lpOrgData,LPBYTE lpPatchData);

  //�޸ĵ������
  bool  LoadFromMem(LPBYTE Data,int Len); //��һ���������ж�ȡ�޸�����
  int   SaveToMem(LPBYTE Data);           //д���޸����ݵ�һ����������
  __inline void Delete(int Index){m_PatchInfoList->Delete(Index);}
  __inline void Clear(){m_PatchInfoList->Clear();}
  __inline tagPatchAddrInfo * At(int Index){return m_PatchInfoList->At(Index);}
  __inline int Count(){return m_PatchInfoList->Count();}
};

//---------------------------------------------------------------------------
#endif
