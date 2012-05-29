//---------------------------------------------------------------------------
//����fastscript�Ľű������װ
//�ɰ�΢�̷߳�ʽ����ͨ��ʽ����
//
#ifndef scriptengH
#define scriptengH
#include "microthread.h"
#include "fs_iinterpreter.hpp"
#include "fs_icpp.hpp"
typedef Variant __fastcall (__closure * TCallMethodEvent)(System::TObject* Instance, TMetaClass* ClassType, const AnsiString MethodName, Variant &Params);
typedef void    __fastcall (__closure * TOnRunLine)(String UnitName,TPoint * LinePos);
class CScriptEngine
{
private:
  TfsScript *fsScript;
  TfsCPP    *CPPLang;
  bool       m_ThreadMode;
  bool		 m_ThreadSuspend; //�߳��Ƿ��ڹ���״̬
  MicroThread::MicroThreadInfo * m_MicroThread;
protected:
  String     m_LastErrorInfo;
  static     void WorkerThread(void *  ScriptEngine);
  void __fastcall OnLine(TfsScript* Sender,const AnsiString UnitName, const AnsiString SourcePos);
public:
  __fastcall CScriptEngine(TComponent * AOwner);
  __fastcall ~CScriptEngine();
  bool       IsRunning();
  bool       IsThreadMode(){return m_ThreadMode;}  //��ǰ�Ƿ����̷߳�ʽִ��
  bool       Start(bool ThreadMode=false); //��ʼ���нű�,����ָ��: �Ƿ����̷߳�ʽִ��
  void       Stop(); //�����ű�
  void		 ResumeThread();//�ָ�����Ľű��߳�
  void		 SleepThread(); //�����ű���cpu����Ȩ
  bool	 	 ThreadIsSuspend(){return m_ThreadSuspend;} //�߳��Ƿ������
  //���һ���������ű�����
  //����: AddMethod("function  Walk(PosX:int;PosY:int):boolean",OnScriptWalk);
  // ����ԭ��, OnScriptWalkΪ����˺����Ĺ���,����Variant __fastcall  OnScriptWalk(System::TObject* Instance, TMetaClass* ClassType, const AnsiString MethodName, Variant &Params);
  void __fastcall AddMethod(const AnsiString Syntax, TCallMethodEvent CallEvent, const AnsiString Category = "", const AnsiString Description = "");
  //------------------------------------------------------------------------------
  String     GetLastErrorInfo(){return m_LastErrorInfo;}  //��ȡ������Ϣ
  void       LoadScript(TStrings * ScriptText); //��TStrings��ȡ�ű�
  bool       LoadFromFile(String FileName);
  void		 SaveToOPCode(String FileName); //���ֵ��м����
  void		 LoadOPCode(String FileName); //�����м����
  void       LoadOPCode(TStrings * OPCodes); //�����м����
  Variant __fastcall Evaluate(const AnsiString Expression); //���ʽ��ֵ
  //-----------------------------------------------------------------------------
  //����ִ��
  TOnRunLine  OnRunLine;
};

//---------------------------------------------------------------------------
#endif
