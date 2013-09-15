<%FileComment%>
#ClassRep#
<%ClassComment%>
struct	<%ClassName%>
{
	#MemberRep#
	<%MemberReadDataType%>		<%MemberReadDataName%>;		<%MemberComment%>
	#MemberRepEnd#
	<%ClassName%>()
	{
		Clear();
		<%SetHeadStr%>
	}
	int				GetLength()
    {
    #DynamicClass#
        int length = 0;
    #MemberRep#
        <%MemberGetLengthFunc%>
    #MemberRepEnd#
        return	length;
    #DynamicClassElse#
        return sizeof(<%ClassName%>);
    #DynamicClassEnd#
    }
    char *				GetBuffer(int Key=0)
    {
        #DynamicClass#
        data.SetLength(GetLength());
        ZeroMemory(data.c_str(), data.Length());
        int pos = 0;
    #MemberRep#
        <%MemberWriteBufferFunc%>
    #MemberRepEnd#
        return data.c_str();
        #DynamicClassElse#
        return    (char *)this;
        #DynamicClassEnd#
    }
	void                            Clear()
	{
	#DynamicClass#
	#MemberRep#
		<%MemberClearFunc%>
	#MemberRepEnd#
	#DynamicClassElse#
		memset(this, 0, sizeof(*this));
	#DynamicClassEnd#
	}
};
#ClassRepEnd#