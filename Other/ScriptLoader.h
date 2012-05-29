//---------------------------------------------------------------------------

#ifndef ScriptLoaderH
#define ScriptLoaderH
//---------------------------------------------------------------------------
#include "PythonScript.h"
#include "WorkSpaceManager.h"

class       ScriptLoader
{
private:
    CPythonScript                   m_PythonScript;
    bool                            m_Inited;
public:
    ScriptLoader();
    ~ScriptLoader();
    void                            Init();
    bool                            GetInited(){return  m_Inited;}
    CPythonScript           *       GetPythonScript(){return    &m_PythonScript;}   
};

ScriptLoader        *       GetScriptLoader();
TStringList         *       GetWriteStr();
#endif
