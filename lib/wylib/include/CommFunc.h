/** @defgroup CommFunc ������չ����,����VCL,ֻ������BCB(CommFunc.h)
 *  @author  eggxp
 *  @version 1.0
 *  @date    2005.02.20
 *  @{
 */


//---------------------------------------------------------------------------
#ifndef CommFuncH
#define CommFuncH
#include <Classes.hpp>
#include <Windows.h>
#include <time.h>
#include <Graphics.hpp>

typedef __int64 int64;
typedef __int32 int32;
typedef short int16;
typedef char int8;
typedef unsigned __int64 uint64;
typedef unsigned __int32 uint32;
typedef WORD uint16;
typedef BYTE uint8;

typedef uint64 far           *LPUINT64;

/** ��ȫɾ���ͷ�һ��ָ������Ӧ���ڴ� */
#define  SAFE_DELETE(p)	 { if ( p ) { delete ( p );     ( p ) = NULL; } }
//---------------------------------------------------------------------------
typedef struct tagPosInfo
{
  DWORD X;
  DWORD Y;
  DWORD ReMapCode;
}
POSINFO,*PPOSINFO;
//---------------------------------------------------------------------------
typedef struct tagSearchWindowData
{
  DWORD  dwOwnerPID;
  LPCSTR strClassName;
  LPCSTR strWindowName;
  HWND   hWnd;
}SEARCHWINDOWDATA, *LPSEARCHWINDOWDATA;
/** @defgroup  String �ַ�������
 *  @{
 */
/** ��ʽ����� \n
 *  printf��ʽ�������AnsiString�汾
 *  @param[in] Info      ��ʽ���ַ���,����ɲμ�c��printf����
 *  @param[in] ...       �䳤����
 *  @return ���ظ�ʽ������ַ���,AnsiString����
  *  @note �����ʽ�����ͺ�ʵ�ʴ������Ͳ��������ܻ�����VCL�׳��쳣������ %s��ӦSmallString
 *  @par ʾ��:
 *  @code
    String Info = FormatStr("�������: %s,���EXP:%d",EName,Exp);
 *  @endcode
 
 *  @see ::FormatString
 *  @deprecated VCL AnsiString���е�sprintf��Ա���������ƹ���
 */

//#ifdef UNICODE
//#define	FormatStr	FormatStrW
//#else
//#define	FormatStr	FormatStrA
//#endif // !UNICODE
//
//String FormatStrW(wchar_t *Info, ...);
//String FormatStrA(char *Info, ...);

#define	FormatStr	FormatString

/** ��ʽ�����(String��) \n
 *  printf��ʽ�������AnsiString�汾
 *  @param[in] Info      ��ʽ���ַ���,����ɲμ�c��printf����
 *  @param[in] ...       �䳤����
 *  @return ���ظ�ʽ������ַ���,AnsiString����
  *  @note �����ʽ�����ͺ�ʵ�ʴ������Ͳ��������ܻ�����VCL�׳��쳣������ %s��ӦSmallString
 *  @par ʾ��:
 *  @code
	String FormatInfo = "�������: %s,���EXP:%d";
	String Info = FormatString(FormatInfo,EName,Exp);
 *  @endcode

 *  @see ::FormatStr
 *  @deprecated VCL AnsiString���е�sprintf��Ա���������ƹ���
 */
String FormatString(String Info, ...); //��ʽ�����

/** �ָ��ַ��� \n
 *  ��һ���ַ�������ĳ���Ӵ��ָ���ַ����б�
 *  @param[in] SrcStr    Դ�ַ���,���ָ���ַ���
 *  @param[in] SplitChar �ָ��,�����Ƕ���ַ�
 *  @param[in] Str       ����ַ����б�,����ָ��Ľ��
 *  @return �޷���ֵ
 *  @note �ָ�õ��ַ���������TStrings��
 *  @par ʾ��:
 *  @code
    TStringList * OutputString = new TStringList;
	String SrcString = "��,��,��";
    SplitStr(SrcString,",",OutputString);
	//OutputString���:
	//OutputString->String[0] == "��"
	//OutputString->String[1] == "��"
	//OutputString->String[2] == "��"
 *  @endcode
 *  @see ��
 *  @deprecated ��
 */
void SplitStr(AnsiString SrcStr,AnsiString SplitChar,TStrings *Str);
void SplitStrOld(AnsiString SrcStr,AnsiString SplitChar,TStrings *Str);


//String 		HexStrToBYTE(String Data);      //Ч�ʵ���,����,����Ϊ���ݾɴ��������
int     	HexStrToBin(LPBYTE OutputBuf,String SrcData);//Ч�ʵ���,����,����Ϊ���ݾɴ��������
AnsiString      HexStrToBinStr(String SrcData);

/** 16�����ַ���ת���ɶ��������� \n
 *  Դ�ַ����м���ո� AB 90 DD -> AB90DD,����Ż���
 *  @param[in] SrcText     //Դ��������0��β�ַ���)
 *  @param[in] DesBuffer  Ŀ�껺����(����������)
 *  @param[in] DesBufSize        Ŀ�껺��������
 *  @param[in] HasSplitChar        �Ƿ���ָ��ַ�
 *  @return ����ת��������ݳ���
 *  @note
 *  @par ʾ��:
 *  @code
	  String SrcText = "AB 90 DD";
	  char   DesBuffer[1024];
	  int BufferLen =  WY_HexToBin(SrcText.c_str(),DesBuffer,sizeof(DesBuffer));
	  //���:
	  //BufferLen = 3
	  //DesBuffer[0] = 0xAB
	  //DesBuffer[1] = 0x90
	  //DesBuffer[2] = 0xDD
 *  @endcode
 *  @see WY_BinToHex
 *  @deprecated ��
 */
int __fastcall WY_HexToBin(char * SrcText, char * DesBuffer,int DesBufSize,bool HasSplitChar=true);

/** ����������ת����16�����ַ��� \n
 *  ����ַ����м�ָ��������趨 ,����Ż���
 *  @param[in] DesText    Ŀ�껺������0��β�ַ���)
 *  @param[in] SrcBuffer  Դ������(����������)
 *  @param[in] SrcBufSize        Դ����������
 *  @param[in] SplitChar         //�Զ���ָ��ַ���0Ϊ��ʹ�÷ָ���
 *  @return �޷���ֵ
 *  @note
 *  @par ʾ��:
 *  @code
	  char   DesText[100];
	  memset(DesText,0,sizeof(DesText));
	  char   SrcBuffer[3]={0xAA,0xBB,0x10};
	  WY_BinToHex(DesText,SrcBuffer,sizeof(SrcBuffer),',');
	  ShowMessge(DesText);
	  //���:
	   DesText = "AA,BB,10";
 *  @endcode
 *  @see WY_HexToBin
 *  @deprecated ��
 */
void __fastcall WY_BinToHex(char * DesText,const char * SrcBuffer,int SrcBufSize,const char SplitChar=' ');


/** ����������ת����16�����ַ��� \n
 *  ��װ,���� WY_BinToHex�������Ա��ڷ���String,����ʹ��
 *  @param[in] SrcBuffer    Դ������(����������)
 *  @param[in] SrcLen        Դ����������
 *  @return �޷���ֵ
 *  @note  Ĭ��ֵ����' '��Ϊ�ָ��
 *  @par ʾ��:
 *  @code
	  char   SrcBuffer[3]={0xAA,0xBB,0x10};
	  String  DesText = BinToStr(SrcBuffer,sizeof(SrcBuffer));
	  ShowMessge(DesText);
	  //���:
	   DesText = "AA,BB,10";
 *  @endcode
 *  @see WY_BinToHex
 *  @deprecated ��
 */
String  BinToStr(char* SrcBuffer, int SrcLen);

/** ��һ��String������ݱ��浽�ļ��� \n
 *  ��String������ݵ�����ָ���ļ�
 *  @param[in] Data       String����
 *  @param[in] FileName   �ļ���,�����������·��,����: c:\\test.dat
 *  @return �޷���ֵ
 *  @note
 *  @par ʾ��:
 *  @code
	  char    SrcBuffer[3]={0xAA,0xBB,0x10};
	  DumpString(String(SrcBuffer),"c:\\test.dat");
	  //���:
	   test.dat��������:  0xAA 0xBB 0x10
 *  @endcode
 *  @see WY_BinToHex
 *  @deprecated ��
 */
void  DumpString(String Data,String FileName);

/** ͳ���ַ�����ĳ�Ӵ��ĸ���
 *
 *  @param[in] InStr     Դ�ַ���
 *  @param[in] SubStr    ��Ҫͳ�Ƶ��ַ���
 *  @return ��ͳ���Ӵ��ĸ���
 *  @note   ��ͳ���Ӵ��Ǵ�Сд���е�
 *  @par ʾ��:
 *  @code
	  String SrcStr = "play you game,play,play,play";
	  int Count = CountChar(SrcStr,"play");
	  //���:
	   Count = 4
 *  @endcode
 *  @see WY_BinToHex
 *  @deprecated ��
 */
int   CountChar(String InStr,String SubStr);

/** �ָ��ַ�����һ����ֵ \n
 *  ��","�ָ��ַ���Ϊ2��,��ת������ֵ
 *  @param[in] SrcStr        Դ�ַ���
 *  @param[in] LeftValue     �ָ�����ֵ
 *  @param[in] RightValue    �ָ�����ֵ
 *  @return  �Ƿ�ָ�ɹ�
 *  @note    �ָ����","
 *  @par ʾ��:
 *  @code
	  String SrcStr = "111,222";
	  int Value1;
	  int Value2;
	  if (GetPairWWByStr(SrcStr,Value1,Value2))
	  {
		 ShowMessage(IntToStr(Value1+Value2));
	  }
	  //���:
	   Value1 = 111;
	   VAlue2 = 222;
 *  @endcode
 *  @see GetPairWSByStr
 *  @deprecated ��
 */
bool GetPairWWByStr(String SrcStr,int &LeftValue,int &RightValue);

/** �ָ��ַ�����һ����ֵ,һ���ַ��� \n
 *  ��","�ָ��ַ���Ϊ2��,��ת����һ����ֵ,һ���ַ���
 *  @param[in] SrcStr        Դ�ַ���
 *  @param[in] LeftValue     �ָ�����ֵ(��ֵ)
 *  @param[in] RightValue    �ָ�����ֵ(�ַ���)
 *  @return  �Ƿ�ָ�ɹ�
 *  @note    �ָ����","
 *  @par ʾ��:
 *  @code
	  String SrcStr = "111,222";
	  int Value1;
	  String Value2;
	  if (GetPairWWByStr(SrcStr,Value1,Value2))
	  {
		 ShowMessage(IntToStr(Value1));
	  }
	  //���:
	   Value1 = 111;
	   VAlue2 = "222";
 *  @endcode
 *  @see GetPairWWByStr
 *  @deprecated ��
 */
bool GetPairWSByStr(String SrcStr,int &LeftValue,String &RightValue);

/** �ָ��ַ�����3����ֵ\n
 *  ��","�ָ��ַ���Ϊ3��,��ת����3����ֵ
 *  @param[in] SrcStr        Դ�ַ���
 *  @param[in] Index     �ָ���(��ֵ1)
 *  @param[in] Value1    �ָ���(��ֵ2)
 *  @param[in] Value2   �ָ���(��ֵ3)
 *  @return  �Ƿ�ָ�ɹ�
 *  @note    �ָ����","
 *  @par ʾ��:
 *  @code
	  String SrcStr = "111,222,333";
	  int Value1;
	  int Value2;
	  int Value3;
	  if (GetPairWWByStr(SrcStr,Value1,Value2,Value3))
	  {
		 ShowMessage(IntToStr(Value1));
	  }
	  //���:
	   Value1 = 111;
	   VAlue2 = 222;
	   Value3 = 333;
 *  @endcode
 *  @see GetPairWWByStr
 *  @deprecated ��
 */
bool Get3ValueByStr(String SrcStr,int &Index,int &Value1,int &Value2);

/** ȡ���ַ�����������ĸ\n
 *  �ڲ�����isalpha(c)ʵ��
 *  @param[in] InStr      Դ�ַ���
 *  @return  ����ĸ����ɵ��Ӵ�
 *  @note    ����ĸ�ַ�ȫ��ȥ��
 *  @par ʾ��:
 *  @code
	  String SrcStr = "22 King Of Fighter 99";
	  String SubStr =  GetAlpha(SrcStr);
	  //���:
	  //SubStr = "KingOfFighter";
 *  @endcode
 *  @see GetDigit
 *  @deprecated ��
 */
String GetAlpha(String InStr);
/** ȡ���ַ�������������\n
 *  �ڲ�����isdigit(c)ʵ��
 *  @param[in] InStr      Դ�ַ���
 *  @return  ����ĸ����ɵ��Ӵ�
 *  @note    ����ֵ�ַ�ȫ��ȥ��
 *  @par ʾ��:
 *  @code
	  String SrcStr = "22 King Of Fighter 99";
	  String SubStr =  GetDigit(SrcStr);
	  //���:
	  //SubStr = "2299";
 *  @endcode
 *  @see GetAlpha
 *  @deprecated ��
 */
String GetDigit(String InStr);

/** ȡ���ַ�������������\n
 *  ����ȥ����Ч��0
 *  @param[in] InStr      Դ�ַ���
 *  @return  �ɺϷ���ֵ��ɵ��Ӵ�
 *  @note    ����ֵ�ַ�ȫ��ȥ��,��Ч0�ַ�ȫ��ȥ��
 *  @par ʾ��:
 *  @code
	  String SrcStr = "JY00088888";
	  String SubStr =  GetTrueNumber(SrcStr);
	  //���:
	  //SubStr = "88888";
 *  @endcode
 *  @see GetDigit
 *  @deprecated ��
 */
String GetTrueNumber(String InStr);

/** ��һ���ַ�����ʼ��ȡ��ĳ�ַ�������\n
 *  �����Ӵ�
 *  @param[in] SrcString      Դ�ַ���
 *  @param[in] TokenChar      ֹͣ�ַ���
 *  @return  ��Դ����һ���ַ���ʼ��ֹͣ�ַ���֮����Ӵ�
 *  @note
 *  @par ʾ��:
 *  @code
	  String SrcStr = "JJ Kill You";
	  String SubStr =  ReadToken(SrcStr," ");
	  //���:
	  //SubStr = "JJ ";
 *  @endcode
 *  @see GetDigit
 *  @deprecated ��
 */
String ReadToken(String &SrcString,String TokenChar);

/** ȡ��һ���ַ�����ĳ���ַ���ߵ��ַ���
 *  @param[in] SrcString      Դ�ַ���
 *  @param[in] TokenStr      �ָ��ַ���
 *  @return  �ָ����ߵ��ַ���
 *  @note    �ָ��Ϊ","
 *  @par ʾ��:
 *  @code
	  String SrcStr = "JJ,Kill";
	  String SubStr =  LeftString(SrcStr);
	  //���:
	  //SubStr = "JJ";
 *  @endcode
 *  @see RightString
 *  @deprecated ��
 */
String LeftString(const String &SrcString,String TokenStr);

/** ȡ��һ���ַ�����ĳ���ַ��ұߵ��ַ���
 *  @param[in] SrcString      Դ�ַ���
 *  @param[in] TokenStr       �ָ��ַ���
 *  @return  �ָ���ұߵ��ַ���
 *  @note    �ָ��Ϊ","
 *  @par ʾ��:
 *  @code
	  String SrcStr = "JJ,Kill";
	  String SubStr =  RightString(SrcStr);
	  //���:
	  //SubStr = "Kill";
 *  @endcode
 *  @see LeftString
 *  @deprecated ��
 */
String RightString(const String &SrcString,String TokenStr);

/** @}*/ // �ַ�������

/** @defgroup OSExpand Windows����ϵͳ���ܺ���
 *  @{
 */
/** ���OS�ַ����Ƿ��м����ֿ� \n
 *  
 *  @return ���û��,����False,��ʾ�Լ�������Ϊ��Ҫ���Եĳ����޷��ڴ�ϵͳ������ , ����м����ֿ�,����True
 *  @note   ���û�м����ַ����ֿ�,��ô��ʹʹ��ת�뺯����Ҳ�޷���֤�����������ڷ�������ȫ��������
 *  @par ʾ��:
 *  @code
    if (!CheckOS_Font())
    {
       ShowMessage("your windows can't run this application!!");
       
    }
 *  @endcode
 */
bool   CheckOS_Font();

/** @}*/ // Windows����ϵͳ���ܺ���


/** @defgroup Process ������Ϣ,�ڴ��д
 *  @{
 */
 /** ��ȡĳ�����ڽ��̵�ĳ���ڴ�����\n
 *
 *  @param[in] aClassName    Ŀ����̴�������,ֻҪ�Ǵ˽��������Ĵ��ڣ��Ϳ�����Ϊ����
*  @param[in] BaseAddr       Ҫ��ȡ�Ľ����ڴ��ַ
*  @param[in] Len            Ҫ��ȡ�ĳ���
*  @param[in] lpBuf          ��Ž���Ļ�����ָ��
 *  @return �����ȡʧ��,����False,�����ȡ�ɹ�,����True
 *  @note   ��ȡʧ�ܵ�ԭ�������:����δ�ҵ�,��������Ӧ�Ľ���idδ�ҵ�,ReadProcessMemory����ʧ��
 *  @par ʾ��:
 *  @code
	 BYTE lpBuffer[8192];
	if (ReadMemory("TForm1",0x4123ab9,100,lpBuffer))
	{
	   ShowMessage(FormatStr("���̵�0x4123ab9�ڴ��ַ��������Ϊ:%s",BinToStr((char *)lpBuffer,100)));
	}
	else
	{
	   ShowMessage("��ȡʧ��");
	}
 *  @endcode
 */
bool ReadMemory(String aClassName, DWORD BaseAddr, DWORD Len, LPBYTE lpBuf);
 /** д��ĳ�����ڽ��̵�ĳ���ڴ�����\n
 *  
 *  @param[in] ClassName    Ŀ����̴�������,ֻҪ�Ǵ˽��������Ĵ��ڣ��Ϳ�����Ϊ����
*  @param[in] BaseAddr       Ҫд��Ľ����ڴ��ַ
*  @param[in] Len            Ҫд��ĳ���
*  @param[in] Buf          ���д�����ݵĻ�����ָ��
 *  @return ���д��ʧ��,����False,�����ȡ�ɹ�,����True
 *  @note   ��ȡʧ�ܵ�ԭ�������:����ID���ַ��Ч,д��Ȩ�޲��߱�
 *  @par ʾ��:
 *  @code
	 BYTE lpBuffer[8192];
	if (D_WriteMemory("TForm1",0x4123ab9,100,lpBuffer))
	{
	   ShowMessage(FormatStr("���̵�0x4123ab9�ڴ��ַ��������Ϊ:%s",BinToStr((char *)lpBuffer,100)));
	}
	else
	{
	   ShowMessage("д���ڴ�ʧ��");
	}
 *  @endcode
 */
bool WriteMemory(String ClassName,DWORD BaseAddr, DWORD Len, LPBYTE Buf);

 /** ��ȡĳ�����̵�ĳ���ڴ�����\n
 *  
 *  @param[in] ProcessID    Ŀ�����ID
*  @param[in] BaseAddr       Ҫ��ȡ�Ľ����ڴ��ַ
*  @param[in] Len            Ҫ��ȡ�ĳ���
*  @param[in] lpBuf          ��Ž���Ļ�����ָ��
 *  @return �����ȡʧ��,����False,�����ȡ�ɹ�,����True
 *  @note   ��ȡʧ�ܵ�ԭ�������:����ID���ַ��Ч,ReadProcessMemory����ʧ��
 *  @par ʾ��:
 *  @code
	 BYTE lpBuffer[8192];
	if (ReadMemory(GetCurrentProcessID(),0x4123ab9,100,lpBuffer))
	{
	   ShowMessage(FormatStr("���̵�0x4123ab9�ڴ��ַ��������Ϊ:%s",BinToStr((char *)lpBuffer,100)));
	}
	else
	{
	   ShowMessage("��ȡʧ��");
	}
 *  @endcode
 */
bool D_ReadMemory(DWORD ProcessID,DWORD BaseAddr,DWORD Len, LPBYTE lpBuf);
 /** д��ĳ�����̵�ĳ���ڴ�����\n
 *
 *  @param[in] ProcessID    Ŀ�����ID
*  @param[in] BaseAddr       Ҫд��Ľ����ڴ��ַ
*  @param[in] Len            Ҫд��ĳ���
*  @param[in] Buf          ���д�����ݵĻ�����ָ��
 *  @return ���д��ʧ��,����False,�����ȡ�ɹ�,����True
 *  @note   ��ȡʧ�ܵ�ԭ�������:����ID���ַ��Ч,д��Ȩ�޲��߱�
 *  @par ʾ��:
 *  @code
	 BYTE lpBuffer[8192];
	if (D_WriteMemory(GetCurrentProcessID(),0x4123ab9,100,lpBuffer))
	{
	   ShowMessage(FormatStr("���̵�0x4123ab9�ڴ��ַ��������Ϊ:%s",BinToStr((char *)lpBuffer,100)));
	}
	else
	{
	   ShowMessage("д���ڴ�ʧ��");
	}
 *  @endcode
 */
bool D_WriteMemory(DWORD ProcessID,DWORD BaseAddr, DWORD Len, LPBYTE Buf);


String GetProcessName();
DWORD MyWinExeC(const String &Cmdline,String DirName,int Visibility= SW_SHOW);
void  PopUpWindow(HWND WinHwnd);  //��������ʾ����ǰ��
/** @}*/ // ������Ϣ,�ڴ��д

/**  @defgroup Number ����ת��,��ֵ����
 *  @{
 */

 /** ��һ��62�����ַ���ת����10������ֵ
 *  @param[in] s          62�������ַ��� ��Χ ASC '0' - 'Z'
 *  @return ����62���Ʊ�ʾ�ַ�������Ӧ��10������ֵ
 *  @note   ĳЩ���Ͽ��ܻ���62���Ʊ�ʾ,����ħ��������ʯ��ʱ��ϵ�еķ��
 *  @par ʾ��:
 *  @see ::c_10To62
 *  @code
	 int Value =  c_62To10("azd");
	 ShowMessage(FormatStr("62������ azd ��10������ֵΪ:%d",Value));
 *  @endcode
 */
int c_62To10(String s);

 /** ��10������ֵת����һ��62�����ַ���
 *  @param[in] Value    10������ֵ
 *  @return ���� 10������ֵ����Ӧ��62�����ַ���
 *  @note   ĳЩ���Ͽ��ܻ���62���Ʊ�ʾ,����ħ��������ʯ��ʱ��ϵ�еķ��
 *  @par ʾ��:
 *  @see ::c_62To10
 *  @code
	 String Str_62 =  c_10To62(1000);
	 ShowMessage(FormatStr("10������ֵ1000��62������:%s",Str_62));
 *  @endcode
 */
String c_10To62(int Value);
float  NumberToPercent(int Number1,int Number2);
/** @}*/  // ����ת��,��ֵ����


//���鴦��

void ReadBuf(LPVOID Buf,int &DataPos,LPVOID DesBuf,int Len);
BYTE ReadBYTE(LPBYTE Buf,int &DataPos);
BYTE ReadBit(BYTE * data, int maxLength, int index);
WORD ReadWORD(LPBYTE Buf,int &DataPos);
DWORD ReadDWORD(LPBYTE Buf,int &DataPos);
uint64 ReadUINT64(LPBYTE Buf,int &DataPos);
double ReadDouble(LPBYTE Buf,int &DataPos);
float ReadFloat(LPBYTE Buf,int &DataPos);


void WriteBuf(LPVOID Buf,int &DataPos,LPVOID SrcBuf,int Len);
void WriteBYTE(LPBYTE Buf,int &DataPos,BYTE Value);
void WriteBit(BYTE * data, int maxLength, int index, int value);
void WriteWORD(LPBYTE Buf,int &DataPos,WORD Value);
void WriteDWORD(LPBYTE Buf,int &DataPos,DWORD Value);
void WriteUINT64(LPBYTE Buf,int &DataPos,uint64 Value);
void WriteFloat(LPBYTE Buf,int &DataPos,float Value);
void WriteDouble(LPBYTE Buf,int &DataPos,double Value);
void WriteWideString(char *buf,int &DataPos,String &Text);
// motolora
void MotoReadBuf(LPVOID Buf,int &DataPos,LPVOID DesBuf,int Len);
BYTE MotoReadBYTE(LPBYTE Buf,int &DataPos);
WORD MotoReadWORD(LPBYTE Buf,int &DataPos);
DWORD MotoReadDWORD(LPBYTE Buf,int &DataPos);
double MotoReadDouble(LPBYTE Buf,int &DataPos);
float MotoReadFloat(LPBYTE Buf,int &DataPos);

void MotoWriteBuf(LPVOID Buf,int &DataPos,LPVOID SrcBuf,int Len);
void MotoWriteBYTE(LPBYTE Buf,int &DataPos,BYTE Value);
void MotoWriteWORD(LPBYTE Buf,int &DataPos,WORD Value);
void MotoWriteDWORD(LPBYTE Buf,int &DataPos,DWORD Value);
void MotoWriteFloat(LPBYTE Buf,int &DataPos,float Value);
void MotoWriteDouble(LPBYTE Buf,int &DataPos,double Value);



int  FindWORD(LPBYTE cData,int MaxLen,WORD Value);
int  FindDWORD(LPBYTE cData,int MaxLen,DWORD Value);
//���㷨
int  MakeLineStep(int CurX,int CurY,int DesX,int DesY,int Step,TList *WalkList);  //ʵ�ֵò���,�������ھɴ������,���Ƽ��´���ʹ��
int  CalcPosDis(int CurX,int CurY,int DesX,int DesY);
void RotatePosByDis(int SrcX, int SrcY,int Dis,TPoint *DesPos, float Angle);
void RotatePos(int ZeroX,int ZeroY,int SrcX, int SrcY, TPoint *DesPos, float Angle);
int  GetAngle( int x1 , int  y1 , int x2 , int y2 );
int  GetReverseAngle(int OrgAngle);

//ʱ�����ڴ���
TDateTime Unix_timeToPc_time(time_t t,bool UTC);

//�ļ�,Ŀ¼����
int GetFileList(const String &Path,const String &Ext,TStrings *ResultList);
int GetFileList(const String &DirName,const String &Ext,TStrings *ResultList,bool SubDir);
int GetFileList(const String &DirName,const String &Ext,const String &TrueExt,TStrings *ResultList,bool SubDir);
String GetSysDir();
String EnvironmentPath(String PathName);
String GetCurDir();
void  ZeroTextFile(String FileName);
int GetFileSize(String sFileName);
DWORD GetFileCRC(String FileName);
int   GetLogicalDrive(TStrings *Drivers);
//������Ϣ
void ShowDebugInfo(String Info);
HWND __fastcall SearchWindow(DWORD ProcessId, LPCSTR strClassName, LPCSTR strWindowName);

//����
int   GetLocalIP(TStrings * IPList);
bool  IsLocalIP(String IP);

//����
int  WINAPI fnEncode6BitBufA(unsigned char *pszSrc, char *pszDest, int nSrcLen, int nDestLen);
int  WINAPI fnDecode6BitBufA(char *pszSrc, char *pszDest, int nDestLen);
String EncodeStr(String Src);
String DecodeStr(String Src);
DWORD _stdcall GetCrc32(DWORD crc, LPBYTE buf, UINT len);

//ϵͳ����
void ShutDown();
void ReBoot();
bool IsWin2k();
bool ShutDown2K(UINT Flag);
String GetEXEVersion(const String &ExeNameStr);
//�ؼ�

//ͼ��
TColor RGB2Color(BYTE R,BYTE G,BYTE B);
void   DrawShadeBar(TCanvas * DrawCanvas,int ClientWidth,int ClientHeight,bool VerticalDraw=false);      //������ɫ��һ��TCanvas


bool	ProcessExists(DWORD processID);
TDateTime TTimeToDateTime(const time_t t);
//---------------------------------------------------------------------------

uint64 Uint64Pow(uint64 num, int val);
uint64 StrToUint64Def(String str, int def);
String ReplaceStr(String input, String from, String to);
bool ForceRemoveDir(String SourceDir);

double GetNowTick();
#endif


/** @}*/ // ������չ����

