<%FileComment%>
#ClassRep#NoNullClass#
////////////////////////////////////////////////////////////////
<%ClassComment%>

class       IPY_<%SmallClassName%>
{
private:
    <%SmallClassName%>      *           m_Instance;
public:
    //��ʼ��
    IPY_<%SmallClassName%>();
    ~IPY_<%SmallClassName%>();
    void                SetInstance(<%SmallClassName%>   * instance);
    
    //get�Զ�����
    #MemberRep#RepFrom1
    <%gMemberC_StyleType%>      Get<%MemberGetName%>();                <%MemberComment%>
    #MemberRepEnd#

    //set�Զ�����
    #MemberRep#RepFrom1
    void                Set<%MemberGetName%>(<%gMemberC_StyleType%> data);         <%MemberComment%>
    #MemberRepEnd#
};

///////////////////////////////////////
    IPY_<%SmallClassName%>   *  Get<%SmallClassName%>ByKey(int key);
#ClassRepEnd#