<%FileComment%>
#ClassRep#
/////////////////////////////接口
<%ClassComment%>
class I<%SmallClassName%>Interface
{
public:
	#MemberRep#
	virtual		<%MemberGetFunc%> = 0;
	#MemberRepEnd#
	virtual 	~I<%SmallClassName%>Interface(){}
};

/////////////////////////////实现
class T<%SmallClassName%>Mgr;
class T<%SmallClassName%>: public I<%SmallClassName%>Interface
{
private:
	<%ClassName%>   *m_Detail;
	//其他私有成员
	friend  T<%SmallClassName%>Mgr;          //管理类友元声明
protected:
	void BindData(char *lpData){m_Detail = (<%ClassName%> *)lpData;}
public:
	T<%SmallClassName%>(){m_Detail = NULL;}
	#MemberRep#
	<%MemberGetFunc%>
	{
		<%MemberReturnGetFunc%>
	}
	#MemberRepEnd#
};

#ClassRepEnd#