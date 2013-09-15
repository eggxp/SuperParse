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
                        "<%MemberRealName%>", curNPC->GetNPCProperty()-><%MemberRealName%><%,%>
                        #MemberRepEnd#
                        );
}

#MemberRep#
PyObject *          PySetNPC<%MemberRealName%>(PyObject *self, PyObject *args)
{
    int     index;
    <%PyMemberSetDef%>
    <%PyMemberSetParse%>

    GameNPC * curNPC = GetGameWorldManager()->GetNPCManager()->GetNPCByIndex(index);
    if(curNPC == NULL)
    {
        GetLog()->Error("%s, script error : NPCIndex = %d", SOURCE_INFO, index);
        return  NULL;
    }

    <%ClassName%>   * curClass = curNPC->GetNPCProperty();
    <%PyMemberSetCopy%>
    return          Py_BuildValue("i", 1);
}
#MemberRepEnd#

void                RegNPCPropertyData()
{
    GetPythonScript()->AddMethod("GetProperty", PyNPC_<%ClassName%>);
    #MemberRep#
    GetPythonScript()->AddMethod("Set<%MemberRealName%>", PySetNPC<%MemberRealName%>);
    #MemberRepEnd#
}
#ClassRepEnd#