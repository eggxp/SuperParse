<%FileComment%>
#ClassRep#NoNullClass#
////////////////////////////////////////////////////////////////
<%ClassComment%>

class       IPY_<%SmallClassName%>
{
private:
    <%SmallClassName%>      *           m_Instance;
public:
    //初始化
    IPY_<%SmallClassName%>();
    ~IPY_<%SmallClassName%>();
    void                SetInstance(<%SmallClassName%>   * instance);
    
    //get自动生成
    #MemberRep#RepFrom1
    <%gMemberC_StyleType%>      Get<%MemberGetName%>();                <%MemberComment%>
    #MemberRepEnd#

    //set自动生成
    #MemberRep#RepFrom1
    void                Set<%MemberGetName%>(<%gMemberC_StyleType%> data);         <%MemberComment%>
    #MemberRepEnd#
};

///////////////////////////////////////
    IPY_<%SmallClassName%>   *  Get<%SmallClassName%>ByKey(int key);
#ClassRepEnd#