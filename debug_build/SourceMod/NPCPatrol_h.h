<%FileComment%>
#ClassRep#NoNullClass#
////////////////////////////////////////////////////////////////
<%ClassComment%>
PyObject            *PyNPC_<%ClassName%>(PyObject *self, PyObject *args);
PyObject            *PyNPC_RefreshPos(PyObject *self, PyObject *args);
PyObject            *PyNPC_PatrolPos(PyObject *self, PyObject *args);

void                RegNPCRefreshData();

#ClassRepEnd#