<%FileComment%>
#ClassRep#NoNullClass#
////////////////////////////////////////////////////////////////
<%ClassComment%>

PyObject            *PyPlayer_<%ClassName%>(PyObject *self, PyObject *args)
{
    int     index;
    PyArg_ParseTuple(args, "i", &index);

    Player * curPlayer = GetGameWorldManager()->GetPlayerManager()->PlayerAt(index);
    if(curPlayer == NULL)
    {
        GetLog()->Error("%s, script error : playerIndex = %d", SOURCE_INFO, index);
        return  NULL;
    }
    
    return  Py_BuildValue("{<%MemberPyBuildValue%>}",
                        #MemberRep#RepFrom1#
                        "<%MemberRealName%>", curPlayer->GetPlayerData()-><%MemberRealName%><%,%>
                        #MemberRepEnd#
                        );
}

#MemberRep#RepFrom1#
PyObject *          PySetPlayer<%MemberRealName%>(PyObject *self, PyObject *args)
{
    int     index;
    <%PyMemberSetDef%>
    <%PyMemberSetParse%>

    Player * curPlayer = GetGameWorldManager()->GetPlayerManager()->PlayerAt(index);
    if(curPlayer == NULL)
    {
        GetLog()->Error("%s, script error : playerIndex = %d", SOURCE_INFO, index);
        return  NULL;
    }

    <%ClassName%>   * curClass = curPlayer->GetPlayerData();
    <%PyMemberSetCopy%>
    return          Py_BuildValue("i", 1);
}
#MemberRepEnd#

void                RegPlayerData()
{
    GetPythonScript()->AddMethod("GetInfo", PyPlayer_<%ClassName%>);
    #MemberRep#RepFrom1#
    GetPythonScript()->AddMethod("Set<%MemberRealName%>", PySetPlayer<%MemberRealName%>);
    #MemberRepEnd#
    GetPythonScript()->AddNameSpace("Player");
}
#ClassRepEnd#