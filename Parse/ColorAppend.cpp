//---------------------------------------------------------------------------


#pragma hdrstop

#include "ColorAppend.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

ColorAppender::ColorAppender()
{
	m_bEnableAppendColor = false;
}

ColorAppender::~ColorAppender()
{
}

void		ColorAppender::AppendColor(char *lpData, int Len, int curPos, ParseTree * parseTree, int appendNum)
{
	m_ParseTree = parseTree;
	m_lPData = lpData;
	m_Len = Len;
	m_CurPos = curPos;
	m_AppendNum = appendNum;

	m_ParseLenResult.Clear();
	Append();
}

void				ColorAppender::Append()
{
	int pos = m_CurPos;
	tagParseLenResult	*	curResult;
	int num = 0;
	while(pos < m_Len)
	{
		if(m_AppendNum != 0 && num >= m_AppendNum)
			break;
		m_ParseTree->UnPackData(pos);
		curResult = new tagParseLenResult;
		curResult->StartPos = pos;
		curResult->Len = m_ParseTree->GetSize();
		m_ParseLenResult.Add(curResult);
		pos += m_ParseTree->GetSize();

		num++;
	}

	m_ParseTree->UnPackData(m_CurPos);
}

int			ColorAppender::GetCurAppendColorODD(int pos)
{
	for(int i=0; i<m_ParseLenResult.Count(); i++)
	{
		if(m_ParseLenResult[i]->InArea(pos))
			return	i%2;
	}
	return -1;
}
