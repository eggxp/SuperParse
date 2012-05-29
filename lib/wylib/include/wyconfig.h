//---------------------------------------------------------------------------

#ifndef wyconfigH
#define wyconfigH
#include <vcl.h>
#include "amap.h"
#include "cspin.h"
#include <IniFiles.hpp>
//���ڱ���Ͷ�ȡ�û�����
//����ģʽ Ĭ��ֵ,�ؼ���Tag
enum ValueSaveType{vsDefault,vsTag};
//---------------------------------------------------------------------------
struct tagValueRecord
{
    TComponent *GUIComponent;
	Variant    Value;
    bool       GUI2Value();    //��GUI�ؼ���ȡ��ֵ
    bool       Value2GUI();    //ˢ��GUI�ؼ�����ʾ����ֵ
    bool       WriteToINI(TCustomIniFile *lpIniFile,const String &SecName);
    bool       ReadFromINI(TCustomIniFile *lpIniFile,const String &SecName);
};
//---------------------------------------------------------------------------
class TConfig
{
private:
  AIndexList<tagValueRecord> * m_lpCommonConfig;     //ʹ��Hash���Լӿ������ٶ�
protected:
  String m_RecordName;
public:
  __fastcall TConfig();
  virtual __fastcall ~TConfig();
  void __fastcall SetRecordName(const String &RecordName);    //�����������¼��
  String __fastcall GetRecordName(){return m_RecordName;} //��ȡ�������¼��
  void __fastcall AddOptionRecord(TComponent * GUI_Component); //����һ��ѡ��
  void __fastcall GUI2Value();     //��GUI�ؼ���ȡ������ֵ
  void __fastcall Value2GUI();     //ˢ��GUI�ؼ���������ʾ����ֵ
  bool __fastcall Less(const String &OptionName,Variant Value);       //С�ڱȽ� <
  bool __fastcall Same(const String &OptionName,Variant Value);       //���ڱȽ� ==
  bool __fastcall Greater(const String &OptionName,Variant Value);    //���ڱȽ� >
  bool __fastcall LessAndSame(const String &OptionName,Variant Value);   //С�ڵ��ڱȽ�<=
  bool __fastcall GreaterAndSame(const String &OptionName,Variant Value);//���ڵ��ڱȽ�>=
  bool __fastcall AsBool(const String &OptionName);
  int  __fastcall AsInt(const String &OptionName);
  String __fastcall AsString(const String &OptionName);
  double __fastcall AsDouble(const String &OptionName);
  DWORD  __fastcall AsDWORD(const String &OptionName);
  virtual bool    LoadFromFile(const String &FileName,const String &SecName);
  virtual void    SaveToFile(const String &FileName);
  virtual bool    LoadFromIni(TMemIniFile * IniFile,const String &SecName);
  virtual void    SaveToIni(TMemIniFile * IniFile);
  void __fastcall SetValue(const String &OptionName,Variant Value);   //����ĳ�����ֵ
  Variant __fastcall GetValue(const String &OptionName);              //��ȡĳ�����ֵ
};

#endif
