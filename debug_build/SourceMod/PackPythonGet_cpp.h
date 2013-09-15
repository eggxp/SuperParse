<%FileComment%>
#ClassRep#NoNullClass#
////////////////////////////////////////////////////////////////
<%ClassComment%>
static          <%ClassName%>       g_<%ClassName%>;            
<%ClassName%>       *Get<%ClassName%>()
{
    return  &g_<%ClassName%>;
}

PyObject            *PyPack_<%ClassName%>(PyObject *self, PyObject *args)
{
    return  Py_BuildValue("{<%MemberPyBuildValue%>}",
                        #MemberRep#RepFrom1#
                        "<%MemberRealName%>", Get<%ClassName%>()-><%MemberRealName%><%,%>
                        #MemberRepEnd#
                        );
}
#ClassRepEnd#