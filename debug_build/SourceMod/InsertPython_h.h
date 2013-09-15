<%FileComment%>
#ClassRep#NoNullClass#
////////////////////////////////////////////////////////////////
<%ClassComment%>
<%ClassName%>       *Get<%ClassName%>();
#MemberRep#
PyObject *          PySet<%MemberRealName%>(PyObject *self, PyObject *args);
#MemberRepEnd#
PyObject *          PyDoSend<%ClassName%>(PyObject *self, PyObject *args);
void                Reg<%ClassName%>Data();

#ClassRepEnd#