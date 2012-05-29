//---------------------------------------------------------------------------

#ifndef ColorAppendH
#define ColorAppendH
//---------------------------------------------------------------------------

#include "ParseTree.h"

struct	tagParseLenResult
{
	int	StartPos;
	int	Len;
	tagParseLenResult()
	{
		StartPos = 0;
		Len = 0;
	}
	bool	InArea(int pos)
	{
		if(pos >= StartPos && pos < StartPos+Len)
			return	true;
		return false;
	}
};

//��ɫ��չ�㷨

class	ColorAppender
{
private:
	ParseTree			*m_ParseTree;
	char				*m_lPData;
	int					m_Len;
	int					m_CurPos;
	int					m_AppendNum;
	AList<tagParseLenResult>	m_ParseLenResult;

	void				Append();

	bool				m_bEnableAppendColor;
public:
	ColorAppender();
	~ColorAppender();
	void		AppendColor(char *lpData, int Len, int curPos, ParseTree * parseTree, int appendNum);

	bool		GetEnableAppend(){return	m_bEnableAppendColor;}
	void		SetEnableAppend(bool enable){m_bEnableAppendColor = enable;}

	int			GetCurAppendColorODD(int pos);	//-1:û�� 1:���� 0:ż��
};

#endif
