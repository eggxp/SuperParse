//////////////////////////////////////////////////////////////
<%FileComment%>
#ClassRep#NoNullClass#
static          <%ClassName%>       g_<%ClassName%>;

<%ClassName%>       *   Get<%ClassName%>()
{
    return  &g_<%ClassName%>;
}

#MemberRep#RepFrom1#
<%gMemberC_StyleType%>      IPY_<%SmallClassName%>::Get<%MemberRealName%>()
{
    return  Get<%ClassName%>()-><%MemberC_StyleName%>;
}
#MemberRepEnd#

#ClassRepEnd#