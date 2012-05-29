//---------------------------------------------------------------------------


#pragma hdrstop

#include "PythonScript.h"
#include <traceback.h>
#include <VCL.h>
#include <frameobject.h>
#include <StrUtils.hpp>
#include <Classes.hpp>
#include "Log4Me.h"
#include "CommFunc.h"
#include "CommPlus.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

#define     MAX_PYTHONSCRIPT_LOG_COUNT      10000
#define     LOG_MSG_COUNT                   200

size_t	GetStrCRC32(const char * StrKey)
{
	return	GetCrc32(0, (char *)StrKey, strlen(StrKey));
}

static          CPythonScript        *glpPythonScript = NULL;

CPythonScript       *       GetPythonScript()
{
    if(!glpPythonScript)
    {
        glpPythonScript = new  CPythonScript();
    }
    return          glpPythonScript;
}

//================================================================================
String      GetWhatMeaning(int what)
{
    switch(what)
    {
        case    PyTrace_CALL:
            return  "PyTrace_CALL";
        case    PyTrace_EXCEPTION:
            return  "PyTrace_EXCEPTION";
        case    PyTrace_LINE:
            return  "PyTrace_LINE";
        case    PyTrace_RETURN:
            return  "PyTrace_RETURN";
        case    PyTrace_C_CALL:
            return  "PyTrace_C_CALL";
        case    PyTrace_C_EXCEPTION:
            return  "PyTrace_C_EXCEPTION";
        case    PyTrace_C_RETURN:
            return  "PyTrace_C_RETURN";
    }
    return  "Unknown";
}

String      GetTraceMsg(PyObject *obj, PyFrameObject *frame, int what, PyObject *arg)
{
    String FileName = PyString_AsString(frame->f_code->co_filename);
    FileName = ExtractFileName(FileName);

    if(GetPythonScript()->GetFilterFileName() &&
                    GetPythonScript()->GetFilterFileName()->IndexOf(FileName.LowerCase()) >= 0)
    {
        //���ļ��ڹ����ļ���, ������
        return  "";
    }

    String compareName = FileName;

    String Name = PyString_AsString(frame->f_code->co_name);
    String Message = FormatStr("[%s, #%d](%s) %s ", FileName, frame->f_lineno, Name, GetWhatMeaning(what));

    String Detail;
    if(what == PyTrace_C_CALL)
    {
        Detail = FormatStr("Name : %s", PyString_AsString(arg));
    }
    else if(what == PyTrace_RETURN)
    {
        if(arg && PyString_Check(arg))
            Detail = PyString_AsString(arg);
        else if(arg && PyInt_Check(arg))
            Detail = PyInt_AsLong(arg);

        if(Detail != "")
            Detail = FormatStr("Value = %s", Detail);
    }
    if(Detail != "")
    {
        Message = FormatStr("%s->%s", Message, Detail);
    }
    return  Message;
}

int         Py_Tracefunc(PyObject *obj, PyFrameObject *frame, int what, PyObject *arg)
{
//    if(what == PyTrace_LINE)
//    {
//        //ȡ���кż�¼
//        return 0;
//    }

    String  msg;
    if(GetPythonScript()->GetEnableRecordStackOnRun())
    {
        msg = GetTraceMsg(obj, frame, what, arg);
        if(msg == "")
            return 0;
        //��¼����ʱ��Ϣ
        GetPythonScript()->AddRunMsg(msg);
    }

    if(obj == NULL)
    {
        //Ĭ�ϼ�¼����
        return 0;
    }
    if(obj != GetPythonScript()->GetCurRunFunc())
    {
        //ѡ��Ҫ��¼�ĺ���
        return  0;
    }

    msg = GetTraceMsg(obj, frame, what, arg);
    if(msg == "")
        return 0;

    GetPythonScript()->AddStackMessage(msg);
    return 0;
}

////////////////////////////////////////////////////////////////////

CPythonScript::CPythonScript()
{
    m_EnableRecordStackOnRun = false;
    m_CurRunFunc = NULL;
    m_CurTracingFunc = NULL;
    m_iCount = 0;
    m_Dicts.pfStrToSize_T = GetStrCRC32;
    m_Thunk.InitThunk((thisThunk::TMFP)&CPythonScript::Python_Alert, this);

    m_ErrorInfo = new TStringList();
    m_StackMessage = new TStringList();
    m_FilterFileName = new TStringList();
    m_RunStack = new TStringList();
    fpPythonError = NULL;

    Py_SetProgramName(Application->ExeName.c_str());
    m_UserOutputLog = new TStringList();
    m_bUserOutput = false;

    //��ʼ������
    m_FuncMethods.Clear();
    m_Dicts.Clear();
    m_CurFuncMethod = new TMethodDefList;
    m_FuncMethods.Add(m_CurFuncMethod);
    
    Py_Initialize();
    if(!Py_IsInitialized())
    {
        LogError("Sys", "python init fail!");
        return;
    }    

    AddMethod("Msg", (PYTHONFUNC)(m_Thunk.GetThunk()), "Message Handle");
    AddNameSpace("LogUI");

}


PyObject * __cdecl CPythonScript::Python_Alert(DWORD,PyObject *self, PyObject *args)
{
    const char *msg;
    PyArg_ParseTuple(args, "s", &msg);
    LogError("Alert", FormatStr("Python Msg : %s", msg));
    return Py_BuildValue("s", "sts.c_str()" );
}

CPythonScript::~CPythonScript()
{
    SAFE_DELETE(m_ErrorInfo);
    SAFE_DELETE(m_StackMessage);
    SAFE_DELETE(m_FilterFileName);
    SAFE_DELETE(m_RunStack);
    SAFE_DELETE(m_UserOutputLog);

    m_Dicts.Clear();
    m_FuncMethods.Clear();
    Py_Finalize();
}

void       CPythonScript::Init()
{
}

bool       CPythonScript::CanLoadFromFile(String fileName)
{
    String path = ExtractFilePath(fileName) + "\\";
    String name = ExtractFileName(fileName);
    name = LeftString(name, ".");

    if(path.AnsiPos("\\" + name + "\\"))
        return  false;
    return  true;
}

void       CPythonScript::AddStackMessage(String msg)
{
    if(m_StackMessage->Count > MAX_PYTHONSCRIPT_LOG_COUNT)
    {
        m_StackMessage->Clear();
    }
    m_StackMessage->Add(msg);
}

void        CPythonScript::AddFilterFileName(String    fileName)
{
    m_FilterFileName->Add(ExtractFileName(fileName).LowerCase());
}

void       CPythonScript::LogError(String fileName, String err)
{
    if(m_ErrorInfo->Count > MAX_PYTHONSCRIPT_LOG_COUNT)
        m_ErrorInfo->Clear();

    err = FormatStr("[%s][#%d %s] : %s", fileName, m_iCount, Now().TimeString(), err);
    m_ErrorInfo->Add(err);

    if(fpPythonError)
        fpPythonError(err);

    GetLog()->MessageWarn(0, err);
    m_iCount++;


    if(m_bUserOutput)
    {
        //�û��Զ������Ŀ�ĵ�
        m_UserOutputLog->Add(err);
    }
}

bool        CPythonScript::ReloadFromFile(String FileName)
{
    tagModuleDict  * curModuleDict = m_Dicts.Find(FileName.c_str());
    if(curModuleDict == NULL)
    {
        //û������ֵ�, �����µ���
        return LoadFromFile(FileName);
    }

    if(curModuleDict->pModule == NULL)
    {
        //�ֵ���û���������, ���µ���
        return  LoadFromFile(FileName);
    }

    PyObject    *   reloadModule = PyImport_ReloadModule(curModuleDict->pModule);

    if ( reloadModule == NULL )
    {
        LogError(FileName, FormatStr("Reload file : %s fail. %s", FileName, GetScriptError()));
        return false;
    }

    //ִ��python�ű�����
    curModuleDict->pDict = PyModule_GetDict(curModuleDict->pModule);
    m_iCount = 0;
    return true;
}

void        CPythonScript::SetScriptPath(String    path)
{
    m_ScriptPath = ExcludeTrailingPathDelimiter(path);

    auto_ptr<TStringList>   resultList(new TStringList);
    GetFileDirList(m_ScriptPath, resultList.get(), true);

    String      importPath;
    String curPath = Py_GetPath();
    curPath += ";" + m_ScriptPath;
    for(int i=0; i<resultList->Count; i++)
    {
        importPath = resultList->Strings[i];
        curPath += ";" + importPath;
    }

    PySys_SetPath(curPath.c_str());



    //��ʼ����Ŀ¼
    resultList->Clear();
    GetFileList(m_ScriptPath, ".py", resultList.get(), true);

    //����ķ�ʽ����, ��ֹ���import
    for(int i=resultList->Count-1; i>=0; i--)
    {
        LoadFromFile(resultList->Strings[i]);
    }

}

void        CPythonScript::ReloadAll()
{
    SetScriptPath(m_ScriptPath);
}

bool        CPythonScript::HaveLoadedFile(String FileName)
{
    if(m_Dicts.Find(FileName.c_str()))
        return      true;
    return          false;
}

bool       CPythonScript::LoadFromFile(String FileName)
{
    m_iCount = 0;
    if(CanLoadFromFile(FileName) == false)
    {
        LogError(FileName, FormatStr("�ļ� %s ��ȡ�п���ʧ��, ����python�ű������Ƿ��Ŀ¼����ͬ(�����ͬ, ��ִ�в���)!", FileName));
    }
    String importName = LeftString(ExtractFileName(FileName), ".");


    //�������Dict
    tagModuleDict   *   curModuleDict = m_Dicts.Find(FileName.c_str());
    if(curModuleDict == NULL)
    {
        curModuleDict = new tagModuleDict;
        m_Dicts.Add(FileName.c_str(), curModuleDict);
    }
    else
    {
        if(curModuleDict->pModule)
        {
            //����ֵ���ֵ, Ӧ�������¶���
            return  ReloadFromFile(FileName);
        }
    }
    
//    PyObject * pathObject = PySys_GetObject("path");
//    int len = PyList_GET_SIZE(pathObject);
//    for(int i=0; i<len; i++)
//    {
//        String aa = PyString_AsString(PyList_GetItem(pathObject, i));
//        String bb = aa;
//    }

    PyObject *pModule = PyImport_ImportModule(importName.c_str());   //   import �ű�������pModule

    if ( !pModule )
    {
        LogError(FileName, GetScriptError());
        return false;
    }

    PyObject *pDict = PyModule_GetDict(pModule);   //   ͨ��pModule�õ�dictionary


    curModuleDict->pModule = pModule;
    curModuleDict->pDict = pDict;
    return true;
}

//���ö�����
void        CPythonScript::AddNameSpace(const  String &lpNameSpace)
{
    //��ʼ��ģ��
    AddMethod(NULL, NULL);
    PyObject *pModule = Py_InitModule(lpNameSpace.c_str(), &m_CurFuncMethod->at(0));
    m_CurFuncMethod = new TMethodDefList;
    m_FuncMethods.Add(m_CurFuncMethod);
    if(pModule == NULL)
    {
        LogError("SysNameSpace", "python init can't find module!");
    }
}

void        CPythonScript::SetEnableRecordStackOnRun()
{
    m_EnableRecordStackOnRun = true;
    m_RunStack->Clear();
    PyEval_SetTrace(Py_Tracefunc, NULL);
}

//ע���Զ��庯��
void __fastcall CPythonScript::AddMethod(const char * lpName, PyCFunction CallEvent, const char * lpDescription)
{
    PyMethodDef curDef;
    curDef.ml_name = lpName;
    curDef.ml_meth = CallEvent;
    curDef.ml_doc = lpDescription;
    curDef.ml_flags = METH_VARARGS;
    m_CurFuncMethod->push_back(curDef);
}

bool            CPythonScript::RunString(const String  &srcName, bool enableUserLog)
{
    m_bUserOutput = enableUserLog;
    if(enableUserLog)
    {
        m_UserOutputLog->Clear();
    }

//    if(!IsPrepared())
//    {
//        LogError("RunString", "Python Not Prepared, Please Use SetPrepared() Func");
//        return  false;
//    }
    String fileWarn = "Custom String";
    String runStr = ReplaceStr(srcName, "\r\n", "\n");
    PyObject * mainModule = PyImport_AddModule("__main__");
    if(!mainModule)
    {
        LogError(fileWarn, "RunString AddModule __main__ Fail!");
        return false;
    }
    PyObject * mainDict = PyModule_GetDict(mainModule);
    if(!mainDict)
    {
        LogError("Custom String", GetScriptError());
        return false;
    }

    PyObject* runObj = PyRun_String(runStr.c_str(), Py_file_input, mainDict, mainDict);
    if(!runObj)
    {
        LogError("Custom String", GetScriptError());
        return false;
    }

    return true;
}

void            CPythonScript::SetTrace(const String &fileName, const String &funcName)
{
    PyObject *pFunc, *pDict;
    // �ҳ�������ΪfuncName�ĺ���
    tagModuleDict   *   curModuleDict = m_Dicts.Find(fileName.c_str());
    if(!curModuleDict)
    {
        LogError(fileName, "SetTrace dict is NULL!");
        return;
    }
    pDict = curModuleDict->pDict;

    if(!pDict)
    {
        LogError(fileName, FormatStr("SetTrace Function : %s Fail,can't Find pDict : %s", funcName, GetScriptError()));
        return;
    }

    pFunc = PyDict_GetItemString(pDict, funcName.c_str());
    if ( !pFunc || !PyCallable_Check(pFunc) )
    {
        LogError(fileName, FormatStr("SetTrace Function : %s Fail : %s", funcName, GetScriptError()));
        return;
    }

    m_CurTracingFunc = pFunc;
//    Py_IncRef(m_CurTracingFunc);
    //��PyEval_SetTrace����¼�к�
    //PyEval_SetProfile���ܼ�¼��ǰ�к�, ��׼ȷ, ���һ�Ī������
    PyEval_SetTrace(Py_Tracefunc, pFunc);
}

void            CPythonScript::DisableTrace()
{
    PyEval_SetTrace(NULL, NULL);
    m_CurTracingFunc = NULL;
    m_EnableRecordStackOnRun = false;
}

PyObject*        CPythonScript::RunFunc(const String &fileName, const String &funcName, PyObject *pArgs)
{
    m_bUserOutput = false;
//    if(!IsPrepared())
//    {
//        LogError("RunString", "Python Not Prepared, Please Use SetPrepared() Func");
//        return  NULL;
//    }
    PyObject *pFunc, *pDict;
    // �ҳ�������ΪfuncName�ĺ���
    tagModuleDict   *   curModuleDict = m_Dicts.Find(fileName.c_str());
    if(!curModuleDict)
    {
        LogError(fileName, "dict is NULL!");
        return NULL;
    }

    if(!curModuleDict->pModule)
    {
        LogError(fileName, "Can Not Find File!");
        return NULL;
    }

    pDict = curModuleDict->pDict;

    if(!pDict)
    {
        pDict = PyModule_GetDict(curModuleDict->pModule);

        if(!pDict)
        {
            LogError(fileName, FormatStr("Function : %s Run Fail,can't Find pDict : %s", funcName, GetScriptError()));
            return NULL;
        }
    }

    pFunc = PyDict_GetItemString(pDict, funcName.c_str());
    if ( !pFunc || !PyCallable_Check(pFunc) )
    {
        LogError(fileName, FormatStr("Function : %s Run Fail : %s", funcName, GetScriptError()));
        return NULL;
    }

    //�ָ��¼��־����
    m_CurRunFunc = pFunc;
    if(m_CurTracingFunc && m_CurTracingFunc == m_CurRunFunc)
    {
        AddStackMessage("");
        AddStackMessage(FormatStr("//////////////////%s, %s begin", fileName, funcName));
        AddStackMessage("");
    }

    // ����Python����
    PyObject* result = PyObject_CallObject(m_CurRunFunc, pArgs);
    Py_XDECREF(pArgs);
    if(result == NULL)
    {
        LogError(fileName, GetScriptError());
        return NULL;
    }

    return result;
}

String   CPythonScript::GetScriptError()
{
    PyObject *type_obj, *value_obj, *traceback_obj;
    PyErr_Fetch(&type_obj, &value_obj, &traceback_obj);
    if (value_obj == NULL)
        return "NoError Or Unknown";
//    if (!PyString_Check(value_obj))
//        return "NoError Or Unknown";

    char *value = PyString_AsString(value_obj);
    PyCodeObject *codeobj;
    String result = FormatStr("Error Message:\r\n%s", value);

    if (traceback_obj != NULL)
    {
        result += "\r\nTraceback:\r\n";

        PyTracebackObject *traceback = (PyTracebackObject *)traceback_obj;
        while(traceback)
        {
            codeobj = traceback->tb_frame->f_code;
            result += FormatStr("%s: %s(# %d)\r\n", PyString_AsString(codeobj->co_name),
                                PyString_AsString(codeobj->co_filename),
                                traceback->tb_lineno);

            traceback = traceback->tb_next;
        }
    }

    Py_XDECREF(type_obj);
    Py_XDECREF(value_obj);
    Py_XDECREF(traceback_obj);
    return result;
}

void        CPythonScript::AddRunMsg(String    msg)
{
    if(m_RunStack == NULL)
        return;
    if(m_RunStack->Count > LOG_MSG_COUNT)
    {
        m_RunStack->Clear();
    }
    m_RunStack->Add(msg);
}

TStringList*        CPythonScript::GetRunStack()
{
    return  m_RunStack;
}

