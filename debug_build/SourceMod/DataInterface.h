<%FileComment%>
#ClassRep#
/////////////////////////////�ӿ�
<%ClassComment%>
class I<%SmallClassName%>Interface
{
public:
	#MemberRep#
	virtual		<%MemberGetFunc%> = 0;
	#MemberRepEnd#
	virtual 	~I<%SmallClassName%>Interface(){}
};

/////////////////////////////ʵ��
class T<%SmallClassName%>Mgr;
class T<%SmallClassName%>: public I<%SmallClassName%>Interface
{
private:
	<%ClassName%>   *m_Detail;
	//����˽�г�Ա
	friend  T<%SmallClassName%>Mgr;          //��������Ԫ����
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