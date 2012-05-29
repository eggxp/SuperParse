//---------------------------------------------------------------------------

#ifndef ScriptParamH
#define ScriptParamH
#include <Classes.hpp>
#include "alist.h"
//�ű����û���չ��������
struct WYParam
{
	Variant  Value;     //������ֵ
	String   Name;      //��������
	String   Info;	  //����˵��
	int      Type;   //0=��ֵ  1=�ַ���
};
//��������
class WY_Params
{
private:
   AList<WYParam> * m_ParamList; //�����б�
protected:
   int				m_RunTimeCount; //�����ڼ���ʵ��������
public:
   WY_Params();
   ~WY_Params();
   int 		Count(){return m_ParamList->Count();}  //Ԥ�����������
   int		RunTimeCount(){return m_RunTimeCount;}   	 //�����ڼ���ʵ��������
   WYParam * Add(const String &ParamName,const String &Info,Variant  Value,int Type);  //�½�һ������
   WYParam * Get(const String &ParamName);      //ĳ�����Ƿ����
   WYParam * At(int Index){return m_ParamList->At(Index);}
   Variant  ValueByName(const String &ParamName); //�������ֻ�ȡ�˲�����ֵ
   Variant  ValueByIndex(int Index); //����Index��ȡ�˲�����ֵ
   bool ReadFromStrings(TStrings * ParamStr);    //��һ��TStrings�ж�ȡ��ֵ
   void Assign(WY_Params * OtherParams);
   void Clear(){m_ParamList->Clear();}
};


//---------------------------------------------------------------------------
#endif
