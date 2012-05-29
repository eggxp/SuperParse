//---------------------------------------------------------------------------

#ifndef PythonScriptH
#define PythonScriptH
//---------------------------------------------------------------------------
#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

#include <vcl.h>
#include "CommFunc.h"
#include <vector>
#include "AList.h"
#include "AMap.h"
#include "Win32Thunk.h"

using namespace std;

//ע��:
//1.һ��Ҫ���� : NDEBUG, ���ܶ��� _DEBUG !  ������벻��
//2.[��Ҫ] Ŀ¼���Ʋ��ܺ��ļ�������ͬ, ����Python�������(���������±����ʱ������, ��֪��Ϊʲô)

//��������:
//  const char *msg, * tit;
//  PyArg_ParseTuple(Args, "ss", &tit,&msg);
typedef void    (__closure * TPythonError)(String   Error);

struct      tagModuleDict
{
    PyObject    *   pModule;
    PyObject    *   pDict;
    tagModuleDict()
    {
        pModule = NULL;
        pDict = NULL;
    }
    ~tagModuleDict()
    {
    }
};

size_t	GetStrCRC32(const char * StrKey);

class   CPythonScript
{
private:
    String                  m_ScriptText;
    String                  m_ScriptPath;
    TStringList         *   m_ErrorInfo;
    void                    LogError(String fileName, String err);
    int                     m_iCount;

    bool                    m_EnableRecordStackOnRun;

    typedef     vector<PyMethodDef> TMethodDefList;
    AList<TMethodDefList>           m_FuncMethods;
    TMethodDefList                  *m_CurFuncMethod;

    bool                            CanLoadFromFile(String fileName);

    //ע��msg����
    typedef CAuxCdeclThunk<CPythonScript>  thisThunk;
    thisThunk	m_Thunk;
    typedef PyObject* (* PYTHONFUNC)(PyObject *self, PyObject *args);
    PyObject* __cdecl Python_Alert(DWORD,PyObject *self, PyObject *args);

    AIndexList<tagModuleDict>            m_Dicts;

    //��־��¼                                                 
    TStringList         *   m_StackMessage;
    PyObject            *   m_CurTracingFunc;
    PyObject            *   m_CurRunFunc;
    TStringList         *   m_FilterFileName;       //��¼��־��ʱ��, ��Ҫ���˵��ļ�
    TStringList         *   m_RunStack;               //�ű�����ʱ��¼���5����Ϣ

    TStringList         *   m_UserOutputLog;        //�û������־��¼�ĵص�
    bool                    m_bUserOutput;           //�Ƿ�Ҫ������û��Զ�������ص�

    bool        LoadFromFile(String FileName);
    bool        ReloadFromFile(String FileName);
public:
    CPythonScript();
    ~CPythonScript();

    void                    AddStackMessage(String msg);
    TStringList         *   GetErrorStrings(){return    m_ErrorInfo;}
    TPythonError            fpPythonError;

    void        Init();
    void        SetScriptPath(String    path);
    void        ReloadAll();
    bool        HaveLoadedFile(String FileName);

    TStringList *GetUserOutputLog(){return  m_UserOutputLog;}

    bool        RunString(const String  &srcName, bool enableUserLog = false);

    //ע���Զ��庯��
    void __fastcall AddMethod(const char * lpName, PyCFunction CallEvent, const char * lpDescription = "");
    void        AddNameSpace(const  String &lpNameSpace);

    //���нű���һ������, funcName�ǽű��ĺ�����, args �Ǻ��������б�
    //��Ч, �Ƽ�ʹ��
    //�����÷�:
    //  PyObject *pArgs, *list;
    //  pArgs = Py_BuildValue("(iis)", 1, 2, "three");
    //  list = Py_BuildValue("[iis]", 1, 2, "three");
    //  Py_BuildValue("{s:i,s:i}", "abc", 123, "def", 456)   ------> {'abc': 123, 'def': 456}

    PyObject*   RunFunc(const String &fileName, const String &funcName, PyObject *pArgs = NULL);
    String      GetScriptError();

    //////////////////////////////////////////////////////
    //��¼��־
    void        SetTrace(const String &fileName, const String &funcName);
    void        DisableTrace();
    PyObject*   GetCurTraceFunc(){return    m_CurTracingFunc;}
    PyObject*   GetCurRunFunc(){return  m_CurRunFunc;}
    TStringList*GetStackMessage(){return    m_StackMessage;}
    void        AddFilterFileName(String    fileName);
    TStringList *GetFilterFileName(){return  m_FilterFileName;}
    void        AddRunMsg(String    msg);
    TStringList*GetRunStack();
    //Python ����ģʽ, �򿪺�, �ٶȺ���
    void        SetEnableRecordStackOnRun();
    bool        GetEnableRecordStackOnRun(){return      m_EnableRecordStackOnRun;}
    /////////////////////////////////////////////////////
};


CPythonScript       *       GetPythonScript();

#endif
