<%FileComment%>
#ClassRep#NoNullClass#
////////////////////////////////////////////////////////////////
<%ClassComment%>
PyObject            *PyNPC_<%ClassName%>(PyObject *self, PyObject *args);

#MemberRep#
PyObject *          PySetNPC<%MemberRealName%>(PyObject *self, PyObject *args);
#MemberRepEnd#

void                RegNPCPropertyData();

#ClassRepEnd#