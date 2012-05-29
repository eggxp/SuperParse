//---------------------------------------------------------------------------

#ifndef applangH
#define applangH
#include <ActnList.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <IniFiles.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Variants.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit
//���ฺ���Զ�ת����Ŀ����
//�Զ�ת�������е� VCL�ؼ���
//1. ����  TAppLang����
//2. ����TAppLang->BindApplication(Application); ����Ŀ����TApplication
//3.���пؼ������Զ�ת�����뽫�˿ؼ���tag�������ó�255,�����Դ˿ؼ�
//4.���д��ڲ����Զ�ת������,�뽫�˴��ڵ�tag�������ó�254
//4.����SaveToIni()������ὫApplication���еĴ��ڱ��浽 ��ĿĿ¼\lang.ini
//5.��lang.iniת���ɶ�Ӧ�������ַ�,���Ᵽ��,����̨��汾��ʹ��langtw.ini
//6.�����ʼ����ʱ��,ʹ��LoadFromIni(INI�ļ���)��ʼ������
//7.������Ҳ���Զ�̬���� LoadFromIni(INI�ļ���)�л����԰汾
//8.�ǵð�ini������ַ�����������ĳɶ�Ӧ������  CHARSET=136
//                 								 Font=�ө���
//�Զ�ת�������еľ�̬�ַ���
//1.�������Թ����
//2.����ַ� _DT("�����ַ���")
//3.������֮��ʹ��applang.exe��ȡ�����ַ�����������ɶ�Ӧ�İ汾 ,�����langtw.txt(̨��)

/*  if (Screen->Fonts->IndexOf("MingLu")>=0)
  {
	 ConvForm->Font->Name = "MingLu";
  }
  else
  {
     ConvForm->Font->Name = L"�ө���";    //ϸ����
  }
  ConvForm->Font->Size = 9;
  ConvForm->Font->Charset = CHINESEBIG5_CHARSET;   */

//GB2312_CHARSET		134	Simplified Chinese characters (mainland china).
//CHINESEBIG5_CHARSET	136	Traditional Chinese characters (Taiwanese).
//DEFAULT_CHARSET		1	Font is chosen based solely on Name and Size. If the described font is not available on the system, Windows will substitute another font.
#define MSG_CREATE_NEW_WINDOWS   WM_USER+5551


class TAppLang
{
private:
   TApplication  * OwnApplication;
   Inifiles::THashedStringList*  LocalStrIndex;
   String LastIniFile;
   bool				IsNullChar(String Text);
   TFontCharset		CharSet;
   String			FontName;
   bool				SaveFormCaption; //�Ƿ񱣴洰�ڱ���
	void __fastcall OnMessage(tagMSG &Msg, bool &Handled);
	TForm *         FindForm(HWND FormHWND);
protected:
   void __fastcall SaveTComboBox(TMemIniFile * IniFile,String SecName,TComboBox * tagObj);
   void __fastcall LoadTComboBox(TMemIniFile * IniFile,String SecName,TComboBox * tagObj);
   void __fastcall SaveTListBox(TMemIniFile * IniFile,String SecName,TListBox * tagObj);
   void __fastcall LoadTListBox(TMemIniFile * IniFile,String SecName,TListBox * tagObj);
   void __fastcall SaveTNotebook(TMemIniFile * IniFile,String SecName,TNotebook * tagObj);
   void __fastcall LoadTNotebook(TMemIniFile * IniFile,String SecName,TNotebook * tagObj);
   void __fastcall SaveTListView(TMemIniFile * IniFile,String SecName,TListView * tagObj);
   void __fastcall LoadTListView(TMemIniFile * IniFile,String SecName,TListView * tagObj);
   void __fastcall SaveTAction(TMemIniFile * IniFile,String SecName,TAction * tagObj);   //���⴦��TAction
   void __fastcall LoadTAction(TMemIniFile * IniFile,String SecName,TAction * tagObj);
   void __fastcall SaveTMenuItem(TMemIniFile * IniFile,String SecName,TMenuItem * tagObj);   //���⴦��TMenuItem
   void __fastcall LoadTMenuItem(TMemIniFile * IniFile,String SecName,TMenuItem * tagObj);
   void __fastcall SaveTControl(TMemIniFile * IniFile,String SecName,TControl * tagObj);   //����TControl
   void __fastcall LoadTControl(TMemIniFile * IniFile,String SecName,TControl * tagObj);
   void __fastcall SaveForm(TMemIniFile * IniFile,TForm * tagForm);
   void __fastcall LoadForm(TMemIniFile * IniFile,TForm * tagForm);
public:
	TAppLang();
	~TAppLang();
	void __fastcall SaveToIni();
	bool __fastcall LoadFromIni(String FileName);
	String _stdcall ShowText(DWORD Flag1, DWORD Flag2, char * Text);
	String _stdcall ShowTextArray(DWORD dwFlag1, DWORD dwFlag2, LPVOID *pStr, INT nSizeOfArray, INT nIndex);
	void			BindApplication(TApplication  * _OwnApplication);
};

//ʹ�ýӿ�
TAppLang * AppLangPtr();
#define DT_FLAG1   0x11223344
#define DT_FLAG2   0x55667788
#define DT_FLAG3  0x99AABBCC
#define _DT(s)    					  AppLangPtr()->ShowText(DT_FLAG1,DT_FLAG2,s)
#define _TEXT_DT_ARRAYD(s, i)         AppLangPtr()->ShowTextArray(DT_FLAG1, DT_FLAG3, (LPVOID *)s, sizeof(s) / sizeof(char*), i)
#define _TEXT_DT_ARRAYP(s, i)         AppLangPtr()->ShowTextArray(DT_FLAG1, DT_FLAG3, (LPVOID *)s, -1, i)
#define _TEXT_DT_ARRAYPU(s, l, i)     AppLangPtr()->ShowTextArray(DT_FLAG1, DT_FLAG3, (LPVOID *)s, l, i)

//---------------------------------------------------------------------------
#endif
