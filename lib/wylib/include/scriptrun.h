#ifndef scriptrunH
#define scriptrunH
#include <Classes.hpp>
#include "amap.h"
#include "scriptparam.h"
enum TScriptState { scrNotRun=0, scrRun, scrPause, scrRestart };

//����һ�нű����ʺ�֪ͨʹ����
//����һ�нű�֮ǰ֪ͨʹ����,������ʾ�Ƿ����������һ��
typedef int __fastcall (__closure *TScrBeforeRunLine) (bool &CanRunNextLine);

//��Ҫ��ȡ��ֵ��ʱ��֪ͨʹ����
typedef int __fastcall (__closure *TScrOnGetVarEvent) (const String &ValueStr);

//�û�ָ���Ľű�������Ӧ�Ĵ�����ָ��
typedef int __fastcall (__closure *TUserFunction) (const String &FuncName,WY_Params &Params);
//��������
struct WY_Function
{
	 WY_Params  	Params;  //�˺����Ĳ����б�
	 String   		Name;    //�˺���������
	 String   		Info;    //�˺�����˵��
	 TUserFunction  UserFunctionPtr;  //�û�ָ���Ĵ���˽ű�������ָ��
	 WY_Function()
	 {
		 UserFunctionPtr = NULL;
	 }
	 int Run()
	 {
		if (UserFunctionPtr)
		{
		   return UserFunctionPtr(Name,Params);
		}
		else
		{
			return -1;
        }
     }
};

class IPascalScript;
class ICppScript;
class IParse;
class CScriptStack;
class   WY_ScriptEngine
{

private:
	TTimer			*RunTimer;	//ִ��ʱ��
    TStringList     *User_OPStr;                                    //��ǰ�����н���
    CScriptStack    *ScrStack;                                      //�ű����ж�ջ������
    TMemoryStream   *ScriptSrc;                                     //�ű�Դ�����ļ���
	IPascalScript   *PascalScript;                                  //�ű��﷨�������ͽ�����
	ICppScript      *CppScript;
	IParse          *ActiveParser;                                  //��ǰ��������Խ�����
    TStringList     *User_ScriptCmd;                                //�ű�α��������б�
    bool            Flag_C, Flag_Z;                                 //�Ƚ��жϱ�־λ
    String          ScriptRootPath;                                 //�ű��ļ���Ŀ¼
	TScriptState    ScriptState;                                    //��ǰ�ű�����״̬
	int             ScriptEIP;                                      //�ű���ǰEIP
	AList<WY_Function>	*  UserFunction; //�û��Զ��庯���б�
	String          ScriptName;                                     //��ǰ�ű���
	String          ScriptInfo;                                     //��ǰ�ű���Ϣ
	String          ScriptFile;                                     //��ǰ�ű��ļ�
	TStringList    * ScriptPathDefs;									//Ĭ�Ͻű�·��
private:
    String __fastcall   GetScriptPath(int ScriptType);
    bool __fastcall     IsJumpOP(String OPCode);
    String __fastcall   GetOpCmd(String CmdLine);
    int __fastcall      GetParValue(const String &Value);           //���ݱ������õ�������ʵ����ֵ
    int __fastcall      FindLabel(const String &LabelName);
    bool __fastcall     GetScriptInfo(TMemoryStream *SrcCodeData, String &Name,
                                      String &Info, bool CanDelInfo);
	void __fastcall     Scr_CMP();
    void __fastcall     Scr_JMP(String JmpCmd);
	void __fastcall     Scr_Call();
	void __fastcall 	Scr_SubCall();
	int 		  GetUserFunctionIndex(const String &FuncName);
	WY_Function * GetUserFunctionByName(const String &FuncName)
	{
	   return      GetUserFunction(GetUserFunctionIndex(FuncName));
	}
	WY_Function * GetUserFunction(int Index);
	void __fastcall OnTimer(System::TObject* Sender);
	String __fastcall ParseFunctionStr(const String &FunctionDef,WY_Params * Params);
public:
	String          LastError;                                      //���ĳ�����Ϣ
public:
	__fastcall          WY_ScriptEngine(String RootPath);
	__fastcall          ~WY_ScriptEngine();
	//�ű�״̬��ȡ����
	String				Name(){return ScriptName;} //��ȡ��ǰ�ű���
	String              Info(){return ScriptInfo;} //��ȡ��ǰ�ű�˵��                                     //��ǰ�ű���Ϣ
	String          	File(){return ScriptFile;} //��ȡ��ǰ�ű��ļ�����·��
	int __fastcall      GetStackLv();                               //�ӳ����ջ����
	String __fastcall   GetCurCmdLine();                            //��ǰ������
	__inline            TScriptState GetState(){return ScriptState;}
	String				GetStataInfo();
	__inline            int          GetEIP(){return ScriptEIP;}
	int 				ErrorPos();
	void                GetSysFuncList(TStrings *SysFunc);          //��ȡϵͳ�����б�
	void                GetSysIdentWordList(TStrings *IdentWord);   //��ȡϵͳ�ؼ����б�
	void                GetUserFuncList(TStrings *SysFunc);         //��ȡ�û������б�
	void                GetUserIdentWordList(TStrings *IdentWord);  //��ȡ�û��ؼ����б�
	bool                GetCmdCodeList(TStrings *DesCmdList);       //��ȡ�ѱ����α������
	__inline            bool         IsRunning(){return (ScriptState == scrRun || ScriptState == scrPause);}
	//�ű����п��ƺ���
	bool __fastcall     RunScript(String ScriptFileName);           //���ļ����нű�
	bool __fastcall		RunScript(TMemoryStream * SrcStream);			//�������нű�
	bool __fastcall		RunScript(TStrings * SrcStrings);			//���ַ����б����нű�


	void __fastcall     StopScript();                               //ֹͣ�ű�
	__inline void __fastcall     Pause(){ScriptState = scrPause;}  //��ͣ�ű�
	__inline void __fastcall     Resume(){if (ScriptState == scrPause)ScriptState=scrRun;}  //�ָ��ű�����
	bool __fastcall     DisposeCmdLine();                           //����һ�нű�
	//�ű��������ú���
	void    SetRunInterval(int Interval){RunTimer->Interval = Interval;} //���ýű�ʱ�Ӽ��
	void    SetScriptDefPath(TStrings * PathList){ScriptPathDefs->Assign(PathList);} //���ýű�Ĭ��·����
	bool    AddUserFunc(String FuncName,String Info,WY_Params * Params,TUserFunction UserFuncPtr);     //����һ���û��Զ��庯��
	bool    AddUserFunc(String FuncDef,String Info,TUserFunction UserFuncPtr);     //����һ���û��Զ��庯��
	void    AddUserIdentWord(String IdentWord); //����һ���û��Զ���ؼ���
	void    SetParserType(int Type);            //0= pascal ,1 = c++
	//�¼�
	TScrBeforeRunLine     OnBeforeRunLine;  //ִ��һ�нű�����֮ǰ֪ͨ
	TScrOnGetVarEvent     OnGetParValue;                              //�������ʵ��ֵʱ��ӿ�
};

//---------------------------------------------------------------------------
#endif
