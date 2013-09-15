<%FileComment%>
#ClassRep#NoNullClass#
////////////////////////////////////////////////////////////////
<%ClassComment%>

PyObject            *PyNPC_<%ClassName%>(PyObject *self, PyObject *args)
{
    int     index;
    PyArg_ParseTuple(args, "i", &index);

    GameNPC * curNPC = GetGameWorldManager()->GetNPCManager()->GetNPCByIndex(index);
    if(curNPC == NULL)
    {
        GetLog()->Error("%s, script error : NPCIndex = %d", SOURCE_INFO, index);
        return  NULL;
    }
    
    return  Py_BuildValue("{<%MemberPyBuildValueFrom0%>}",
                        #MemberRep#
                        "<%MemberRealName%>", curNPC->GetNPCData()-><%MemberRealName%><%,%>
                        #MemberRepEnd#
                        );
}


void                RegNPCDataData()
{
    GetPythonScript()->AddMethod("GetDataInfo", PyNPC_<%ClassName%>);
}
#ClassRepEnd#