<%FileComment%>
#ClassRep#NoNullClass#
////////////////////////////////////////////////////////////////
<%ClassComment%>

<%SmallClassName%>::<%SmallClassName%>()
{
    m_PythonInterface = NULL;
}

<%SmallClassName%>::~<%SmallClassName%>()
{
    SAFE_DELETE(m_PythonInterface);
}

int                         <%SmallClassName%>::ReadData(char *lpData)
{
    return  m_Data.ReadData(lpData);
}

IPY_<%SmallClassName%>      *<%SmallClassName%>::GetPythonInterface()
{
    if(!m_PythonInterface)
    {
        m_PythonInterface = new IPY_<%SmallClassName%>();
        m_PythonInterface->SetInstance(this);
    }
    return  m_PythonInterface;
}

////////////////////////////////////////////////////////////////
//get自动生成指针
#MemberRep#RepFrom1
<%MemberComment%>
<%gMemberC_StyleType%>      <%SmallClassName%>::Get<%MemberGetName%>()
{
    if(!m_Data)
        return <%MemberC_StyleReturn%>;
    return  m_Data->Get<%MemberGetName%>();
}
#MemberRepEnd#

////////////////////////////////////////////////////////////////
//get自动生成实体
#MemberRep#RepFrom1
<%MemberComment%>
<%gMemberC_StyleType%>      <%SmallClassName%>::Get<%MemberGetName%>()
{
    return  m_Data.<%MemberRealName%>;
}
#MemberRepEnd#
////////////////////////////////////////////////////////////////

//set自动生成
#MemberRep#RepFrom1
void                        <%SmallClassName%>::Set<%MemberGetName%>(<%gMemberC_StyleType%> input<%MemberGetName%>)
{
    <%ClassSetMemberFunc%>    
}
#MemberRepEnd#

#ClassRepEnd#


//SendRolePropertyRefresh(CDBPlayerRefresh_<%MemberGetName%>, input<%MemberGetName%>);