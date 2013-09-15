<%FileComment%>
#ClassRep#
<%ClassComment%>

////////////////////////////////////.h
#MemberRep#RepFrom1#
    DWORD                On<%MemberRealName%>(TStringList   * cmd);
#MemberRepEnd#

///////////////////////////////////.cpp
//RegisterCommand
#MemberRep#RepFrom1#
    GetEngine()->RegisterValue("<%MemberRealName%>", On<%MemberRealName%>);
#MemberRepEnd#

//func
#MemberRep#RepFrom1#
DWORD        Player::On<%MemberRealName%>(TStringList   * cmd)
{
    return  m_DBPlayer.<%MemberRealName%>;
}
#MemberRepEnd#

//switch
void    RefreshRolePropertyByType(tagCDBPlayer *player, int type, int Value)
{
    switch(type)
    {
        #MemberRep#RepFrom1#NoStr#
        case    <%SmallClassName%>Refresh_<%MemberRealName%>:
        {
            <%MemberComment%>
            player-><%MemberRealName%> = Value;
            break;
        }
        #MemberRepEnd#
    }
}


//Set
    curPlayer.GetSend().SendToDBPlayerCreate(
        #MemberRep#RepFrom1#
                        0<%,%>          #<%MemberRealName%>, <%MemberComment%>
        #MemberRepEnd#
    )
#ClassRepEnd#