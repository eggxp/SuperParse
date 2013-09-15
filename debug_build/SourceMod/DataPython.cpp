<%FileComment%>
#ClassRep#NoNullClass#
////////////////////////////////////////////////////////////////
<%ClassComment%>

PyObject            *PyData_<%ClassName%>(PyObject *self, PyObject *args)
{
    int     Key;
    PyArg_ParseTuple(args, "i", &Key);
    <%ClassName%>   *   curData = GetGameData()->Get<%SmallClassName%>()->GetDataByKey(Key);
    if(curData == NULL)
    {
        GetLog()->Error("PyData_<%ClassName%>, can't find key by key = %d", Key);
        return  NULL;
    }
    return  Py_BuildValue("{<%MemberPyBuildValue%>}",
                        #MemberRep#RepFrom1#
                        "<%MemberRealName%>", curData-><%MemberRealName%><%,%>
                        #MemberRepEnd#
                        );
}
#ClassRepEnd#