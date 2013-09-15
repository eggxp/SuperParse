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
    
    return  Py_BuildValue("{<%MemberPyBuildValueFrom0%>,s:i,s:i}",
                        #MemberRep#
                        "<%MemberRealName%>", curNPC->GetNPCRefreshPoint()->GetOrgData()-><%MemberRealName%>,
                        #MemberRepEnd#
                        "RefreshCount", curNPC->GetNPCRefreshPoint()->GetChRefreshCount(),
                        "PatrolPosCount", curNPC->GetNPCRefreshPoint()->GetChPatrolPosCount()
                        );
}

PyObject            *PyNPC_RefreshPos(PyObject *self, PyObject *args)
{
    int     index, refreshIndex;
    PyArg_ParseTuple(args, "ii", &index, &refreshIndex);

    GameNPC * curNPC = GetGameWorldManager()->GetNPCManager()->GetNPCByIndex(index);
    if(curNPC == NULL)
    {
        GetLog()->Error("%s, script error : NPCIndex = %d", SOURCE_INFO, index);
        return  NULL;
    }
    
    tagChRefreshPos *   refreshPos = curNPC->GetNPCRefreshPoint()->GetChRefreshPos(refreshIndex);
    if(refreshPos == NULL)
    {
        GetLog()->Error("%s, script error : NPCRefreshIndex = %d", SOURCE_INFO, refreshIndex);
        return  NULL;
    }
    
    return  Py_BuildValue("{s:i,s:i,s:i}",
                        "PosX", refreshPos->PosX,
                        "PosY", refreshPos->PosY,
                        "Area", refreshPos->Area
                        );
}

PyObject            *PyNPC_PatrolPos(PyObject *self, PyObject *args)
{
    int     index, patrolIndex;
    PyArg_ParseTuple(args, "ii", &index, &patrolIndex);

    GameNPC * curNPC = GetGameWorldManager()->GetNPCManager()->GetNPCByIndex(index);
    if(curNPC == NULL)
    {
        GetLog()->Error("%s, script error : NPCIndex = %d", SOURCE_INFO, index);
        return  NULL;
    }
    
    tagChPatrolPos *   patrolPos = curNPC->GetNPCRefreshPoint()->GetChPatrolPos(patrolIndex);
    if(patrolPos == NULL)
    {
        GetLog()->Error("%s, script error : NPCPatrolIndex = %d", SOURCE_INFO, patrolIndex);
        return  NULL;
    }
    
     return  Py_BuildValue("{s:i,s:i,s:i,s:i}",
                        "PosX", patrolPos->PosX,
                        "PosY", patrolPos->PosY,
                        "MinStopTime", patrolPos->MinStopTime,
                        "MaxStopTime", patrolPos->MaxStopTime
                        );
}

void                RegNPCRefreshData()
{
    GetPythonScript()->AddMethod("GetRefreshInfo", PyNPC_<%ClassName%>);
    GetPythonScript()->AddMethod("GetRefreshPos", PyNPC_RefreshPos);
    GetPythonScript()->AddMethod("GetPatrolInfo", PyNPC_PatrolPos);
}
#ClassRepEnd#