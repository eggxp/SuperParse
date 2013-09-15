<%FileComment%>
#ClassRep#NoNullClass#
////////////////////////////////////////////////////////////////
<%ClassComment%>
PyObject            *PyPackSend_<%ClassName%>(PyObject *self, PyObject *args)
{
    int     index;
    <%ClassName%> sendData;
    PyArg_ParseTuple(args, "<%MemberPyTuple%>", &index, 
                                    #MemberRep#RepFrom1#
                                    &sendData.<%MemberRealName%><%,%>
                                    #MemberRepEnd#
                                    );

    Player * curPlayer = GetGameWorldManager()->GetPlayerManager()->PlayerAt(index);

    if(curPlayer == NULL)
    {
        GetLog()->Error("PyPackSend_<%ClassName%>, script error : playerIndex = %d", index);
        return  NULL;
    }

    curPlayer->PushSend(sendData.GetBuffer(), IPacket::atNormal);
    return          Py_BuildValue("i", 1);
}
#ClassRepEnd#