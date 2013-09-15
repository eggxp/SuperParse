<%FileComment%>
#ClassRep#NoNullClass#
////////////////////////////////////////////////////////////////
<%ClassComment%>

//≥ı ºªØ
IPY_<%SmallClassName%>::IPY_<%SmallClassName%>()
{
    m_Instance = NULL;
}

IPY_<%SmallClassName%>::~IPY_<%SmallClassName%>()
{
}

void                IPY_<%SmallClassName%>::SetInstance(<%SmallClassName%>   * instance)
{
    m_Instance = instance;
}


#MemberRep#RepFrom1
<%gMemberC_StyleType%>      IPY_<%SmallClassName%>::Get<%MemberGetName%>()
{
    WY_ASSERT(m_Instance)
    return      m_Instance->Get<%MemberGetName%>();
}
#MemberRepEnd#

#MemberRep#RepFrom1
void                IPY_<%SmallClassName%>::Set<%MemberGetName%>(<%gMemberC_StyleType%> data)
{
    WY_ASSERT(m_Instance)
    m_Instance->Set<%MemberGetName%>(data);
}
#MemberRepEnd#


///////////////////////////////////////////////
IPY_<%SmallClassName%>   *  Get<%SmallClassName%>ByKey(int key)
{
    <%SmallClassName%>Data * cur<%SmallClassName%>Data = GetGameData()->Get<%SmallClassName%>()->GetDataByKey(id);
    if(cur<%SmallClassName%>Data == NULL)
    {
        GetLog()->Error("IPY_<%SmallClassName%>::Get<%SmallClassName%>ByKey, key error = %d", key);
        return  NULL;
    }
}