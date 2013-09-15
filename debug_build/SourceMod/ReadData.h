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
	int				ReadData(char *_lpData, int _Len = 0, int Key=0)
	{
	    Clear();
	    #DynamicClass#
	    #DynamicClassElse#
	    if(_Len != 0 && _Len != GetLength())
            return 0;
        #DynamicClassEnd#
		int pos = 0;
	#DynamicClass#
	#MemberRep#
		<%MemberReadDataFunc%>
	#MemberRepEnd#
	#DynamicClassElse#
		memcpy(this, _lpData, sizeof(*this));
		pos += sizeof(*this);
	#DynamicClassEnd#
	
	    <%StaticCharFix%>
		if(_Len != 0 && pos != _Len)
		{
			GetLog()->Warn(FormatStr("Error in <%ClassName%> : %s ", BinToStr(_lpData, _Len)));
			return 0;
        }
		return pos;
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