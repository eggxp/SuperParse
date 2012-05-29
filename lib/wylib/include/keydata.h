//---------------------------------------------------------------------------
/*
�ṩһ�����ݻ����һ������������
��ʵ��ͨ�õİ�Key�����Ͱ�Name������������,���е�����ֻ��Ҫ��AKeyData�̳�����,����ʵ�ֽӿ����⺯��,Ȼ�����ݼ���AIndexManage��,����ð�Key����,��Name���ң���Index����֮����
����: ��߮
����޸�����: 2004.12.04


*/
#ifndef keydataH
#define keydataH
#include <vcl.h>
#include "alist.h"
#include "amap.h"
//���ݽӿ���
//---------------------------------------------------------------------------
class AKeyData
{
  private:
  protected:
  public:
     __fastcall AKeyData(){;}
     virtual __fastcall ~AKeyData(){return;}
     virtual DWORD   GetKey()=0;
     virtual String  GetName()=0;
     virtual int     ReadData(char *buf)=0;  //�ӻ�������ȡ����,���ض�ȡ���ݵ�ֵ
	 virtual void    Reset()=0;
     virtual void    Assign(AKeyData *SrcData)=0; //������һ�����󿽱�
};

class AIndexManage
{
private:
   AIndexList<AKeyData> *DataList;
protected:

public:
  __fastcall AIndexManage(int MaxRecord=10000);
  virtual __fastcall ~AIndexManage();
  int      IndexOf(DWORD KeyID);
  int      IndexOfName(String Name);
  __inline int Count(){return DataList->Count();}
  AKeyData * Get(DWORD KeyID);
  AKeyData * GetByName(String Name);
  __inline AKeyData * At(int Index){return DataList->At(Index);}
  bool  Add(AKeyData * KeyData);
  void  Delete(int Index){DataList->Delete(Index);}
  void  DeleteByKey(DWORD Key){DataList->Delete(IndexOf(Key));}
  __inline void  Clear(){DataList->Clear();}
  String   GetName(DWORD ID);


};


#endif
