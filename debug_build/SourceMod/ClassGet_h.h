<%FileComment%>
#ClassRep#NoNullClass#
////////////////////////////////////////////////////////////////
<%ClassComment%>
class	    IPY_<%SmallClassName%>;
class       <%SmallClassName%>
{
private:
    IPY_<%SmallClassName%>      *m_PythonInterface;
    <%ClassName%>                m_Data;
public:
    <%SmallClassName%>();
    ~<%SmallClassName%>();
    IPY_<%SmallClassName%>      *GetPythonInterface();
    int                         ReadData(char *lpData);
    
    ////////////////////////////////////////////////////////////////
    //get�Զ�����ָ��
    #MemberRep#RepFrom1
    <%MemberComment%>
    <%gMemberC_StyleType%>      Get<%MemberGetName%>();
    #MemberRepEnd#

    ////////////////////////////////////////////////////////////////
    //set�Զ�����
    #MemberRep#RepFrom1
    <%MemberComment%>
    void                Set<%MemberGetName%>(<%gMemberC_StyleType%> input<%MemberGetName%>);
    #MemberRepEnd#
};

#ClassRepEnd#