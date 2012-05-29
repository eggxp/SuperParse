//---------------------------------------------------------------------------


#pragma hdrstop

#include "ScriptLoader.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

static      auto_ptr<TStringList>       gWriteStr(new   TStringList);
static      ScriptLoader                gScriptLoader;

TStringList         *           GetWriteStr()
{
    return  gWriteStr.get();
}

ScriptLoader        *           GetScriptLoader()
{
    if(gScriptLoader.GetInited() == false)
        gScriptLoader.Init();
    return  &gScriptLoader;
}

//-----------------------------------------------
//ParseFile

PyObject *          WriteStr(PyObject *self, PyObject *args)
{
    char    *s;
    PyArg_ParseTuple(args, "s", &s);
    gWriteStr->Add(s);
    return          Py_BuildValue("i", 1);
}

PyObject *          SetStr(PyObject *self, PyObject *args)
{
    int     index;
    char    *setStr;
    PyArg_ParseTuple(args, "is", &index, &setStr);
    if(index < 0 && index >= gWriteStr->Count)
        return  NULL;

    gWriteStr->Strings[index] = setStr;
    return          Py_BuildValue("i", 1);    
}

PyObject *          GetStr(PyObject *self, PyObject *args)
{
    int     index;
    PyArg_ParseTuple(args, "i", &index);
    return          Py_BuildValue("s", gWriteStr->Strings[index].c_str());
}

PyObject *          GetStrLineCount(PyObject *self, PyObject *args)
{
    return  Py_BuildValue("i", gWriteStr->Count);
}

//-----------------------------------------------
//WorkSpaceManager

PyObject *          GetPackCount(PyObject *self, PyObject *args)
{
    int count = GetWorkSpaceManager()->GetWorkSpacePacks()->GetWorkPacks()->Count();
    return  Py_BuildValue("i", count);
}

PyObject *          GetWorkSpaceCount(PyObject *self, PyObject *args)
{
    int count = GetWorkSpaceManager()->GetWorkSpaceCount();
    return  Py_BuildValue("i", count);
}

PyObject *          GetPackDetail(PyObject *self, PyObject *args)
{
    int     index;
    PyArg_ParseTuple(args, "i", &index);

    WorkPackHead * curHead = GetWorkSpaceManager()->GetWorkSpacePacks()->GetWorkPacks()->At(index);
    return  Py_BuildValue("{s:s,s:s,s:i}",
                        "HeadName", curHead->m_Head.c_str(),
                        "HeadDescribe", curHead->m_Describe,
                        "Count", curHead->m_Files.Count());
}

String  GetCallBackFuncNameByName(String name)
{
    String  callBackFuncName;
    if(name.AnsiPos("tag") == 1)
    {
        callBackFuncName = name.SubString(4, name.Length()-3);
    }
    else
        callBackFuncName = "_" + name;
    callBackFuncName = "On" + callBackFuncName;
    return  callBackFuncName;
}


PyObject *          GetWorkSpaceDetail(PyObject *self, PyObject *args)
{
    int     index;
    PyArg_ParseTuple(args, "i", &index);
    String  name = GetWorkSpaceManager()->GetWorkSpace(index)->GetStructName();
    String  callBackFuncName = GetCallBackFuncNameByName(name);
    
    return  Py_BuildValue("{s:s,s:s}",
                        "CallBackFuncName", callBackFuncName.c_str(),
						"StructTypeName", name.c_str());
}

PyObject *          GetPackWorkSpaceDetail(PyObject *self, PyObject *args)
{
    int     index, subHeadIndex;
    PyArg_ParseTuple(args, "ii", &index, &subHeadIndex);
    WorkSpace * curWorkSpace = GetWorkSpaceManager()->GetWorkSpacePacks()->GetWorkPacks()->At(index)->m_Files[subHeadIndex];

    String  name = curWorkSpace->GetStructName();
    String  callBackFuncName = GetCallBackFuncNameByName(name);
    
    return  Py_BuildValue("{s:s,s:s,s:s,s:s}",
                        "CallBackFuncName", callBackFuncName.c_str(),
                        "StructTypeName", name.c_str(),
						"SubHead", curWorkSpace->GetSubHead(),
						"Comment", curWorkSpace->GetComment()
                        );
}

//////////////////////////////////////////////////////////////////////////////////////

ScriptLoader::ScriptLoader()
{
    m_Inited = false;
}

ScriptLoader::~ScriptLoader()
{
}

void                    ScriptLoader::Init()
{
    if(m_Inited)
        return;
    m_Inited    =  true;
    m_PythonScript.AddMethod("WriteStr", WriteStr);
    m_PythonScript.AddMethod("GetStr", GetStr);
    m_PythonScript.AddMethod("SetStr", SetStr);
    m_PythonScript.AddMethod("GetStrLineCount", GetStrLineCount);
    m_PythonScript.AddNameSpace("ParseFile");

    m_PythonScript.AddMethod("GetPackCount", GetPackCount);
    m_PythonScript.AddMethod("GetPackDetail",  GetPackDetail);
    m_PythonScript.AddMethod("GetWorkSpaceCount",  GetWorkSpaceCount);
    m_PythonScript.AddMethod("GetWorkSpaceDetail",  GetWorkSpaceDetail);
    m_PythonScript.AddMethod("GetPackWorkSpaceDetail",  GetPackWorkSpaceDetail);
    m_PythonScript.AddNameSpace("WorkSpaceManager");
}
