//------------------------------------------------------
<%FileComment%>
#ClassRep#
void    IPY_Send::<%SmallClassName%>(
                    #MemberRep#RepFrom1#
                    <%gMemberC_StyleType%>      input<%MemberRealName%><%,%>
                    #MemberRepEnd#
                                )
{
    if(!m_Player)
        return;
    
    <%ClassName%>   m_Data;
    #MemberRep#RepFrom1#
    <%ClassSetMemberFunc%>
    #MemberRepEnd#
        
    m_Player->PushSend(m_Data.GetBuffer(), IPacket::atNormal);
}
#ClassRepEnd#