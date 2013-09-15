<%FileComment%>
#ClassRep#NoNullClass#
////////////////////////////////////////////////////////////////
<%ClassComment%>
PyObject            *PyPlayer_<%ClassName%>(PyObject *self, PyObject *args);

#MemberRep#RepFrom1
PyObject *          PySetPlayer<%MemberRealName%>(PyObject *self, PyObject *args);
#MemberRepEnd#

void                RegPlayerData();

#ClassRepEnd#