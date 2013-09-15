<%FileComment%>
#ClassRep#NoNullClass#
////////////////////////////////////////////////////////////////
<%ClassComment%>
static          <%ClassName%>       g_<%ClassName%>;            
<%ClassName%>       *Get<%ClassName%>()
{
    return  &g_<%ClassName%>;
}


#MemberRep#
PyObject *          PySet<%MemberRealName%>(PyObject *self, PyObject *args)
{
    int     index;
    <%PyMemberSetDef%>
    <%PyMemberSetParse%>
    <%ClassName%> * curClass = Get<%ClassName%>();
    <%PyMemberSetCopy%>
    return          Py_BuildValue("i", 1);
}
#MemberRepEnd#

PyObject *          PyDoSend<%ClassName%>(PyObject *self, PyObject *args)
{
    int index;
    PyArg_ParseTuple(args, "i", &index);
    PlayerArea * curPlayer = GetGameWorld()->GetPlayerManager()->FindPlayerByIndex(index);
    if(curPlayer == NULL)
    {
        GetLog()->Error("%s, can't find player by Index = %d", SOURCE_INFO, index);
        return NULL;
    }

    String  buffer = GettagDBPlayer()->GetBuffer();
    buffer = StrHeadInsertBYTE(buffer, **ÌîÀàÐÍ**);
    curPlayer->SendDataServerPack(buffer);
    return          Py_BuildValue("i", 1);
}

void                Reg<%ClassName%>Data()
{
    #MemberRep#
    GetPythonScript()->AddMethod("Set<%MemberRealName%>", PySet<%MemberRealName%>);
    #MemberRepEnd#   
    GetPythonScript()->AddMethod("Send", PyDoSend<%ClassName%>);
    GetPythonScript()->AddNameSpace("<%ClassName%>");
}
#ClassRepEnd#