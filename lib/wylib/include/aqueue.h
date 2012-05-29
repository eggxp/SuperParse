// ---------------------------------------------------------------------------

#ifndef aqueueH
#define aqueueH
#include <vcl.h>
#include <boost/shared_ptr.hpp>
#include <queue>
#include "alist.h"
#include "AThreadLock.h"
using namespace std;
using boost::shared_ptr;

// ����,���ȶ���,��ջ����������



// �޸�ʱ��: 2007.7.28
// ����AList�Ķ�����  ��Ϊ ����stl �� queue  , Ч������10��
// �޸�ʱ��: 2010.3.20
// �����̰߳�ȫ����

// ����AList�Ķ�����  ��Ϊ ����stl �� queue  , Ч������10��

// AQueue         ����,�Ƚ��ȳ�
// APriorityQueue ���ȼ�����,��������,���ڿ�������,ĿǰЧ�ʲ���,�ȴ��ö���������ʵ��
// AStack         ��ջ��,�Ƚ����

template<class T>class AQueue
{
private:
	CRITICAL_SECTION m_csLock;
	queue<T*> *DataTable;

	// ������ݵĵط�
protected:
public:
	AQueue()
	{
		InitializeCriticalSection(&m_csLock);
		DataTable = new queue<T*>; // ����ָ���Ƴ�Ԫ�ص�ʱ���Ƿ��Զ�����delete�ͷ�ɾ��Ԫ��
	}

	~AQueue()
	{
		Clear();
		delete DataTable;
		DeleteCriticalSection(&m_csLock);
	}

	void Push(T *Data)
	{
		ThreadLock lock(&m_csLock);
		DataTable->push(Data);
	}

	T *Pop()
	{
		ThreadLock lock(&m_csLock);
		if (Count() <= 0)
		{
			return NULL;
		}
		T * Result = DataTable->front();
		DataTable->pop();
		return Result;
	};

	void Clear()
	{
		ThreadLock lock(&m_csLock);
		T * curT;
		for (int i = 0; i < Count(); i++)
		{
			curT = Pop();
		}
	}

	__inline int Count()
	{
		ThreadLock lock(&m_csLock);
		return DataTable->size();
	}

	__inline bool IsEmpty()
	{
		return DataTable->empty();
	}
};

template<class T>class ASharedPtrQueue
{
private:
	CRITICAL_SECTION m_csLock;
	queue<shared_ptr<T> >m_DataTable;

	// ������ݵĵط�
protected:
public:
	ASharedPtrQueue()
	{
		InitializeCriticalSection(&m_csLock);
	}

	~ASharedPtrQueue()
	{
		Clear();
		DeleteCriticalSection(&m_csLock);
	}

	void Push(shared_ptr<T>Data)
	{
		ThreadLock lock(&m_csLock);
		m_DataTable.push(Data);
	}

	bool Pop(shared_ptr<T> *output)
	{
		ThreadLock lock(&m_csLock);
		if (Count() <= 0)
		{
			return false;
		}
		shared_ptr<T> Result = m_DataTable.front();
		m_DataTable.pop();
		if(output)
		{
			*output = Result;
		}
		return true;
	};

	void Clear()
	{
		ThreadLock lock(&m_csLock);
		while (!m_DataTable.empty())
		{
			m_DataTable.pop();
		}
	}

	__inline int Count()
	{
		ThreadLock lock(&m_csLock);
		return m_DataTable.size();
	}

	__inline bool IsEmpty()
	{
		return m_DataTable.empty();
	}
};

template<class T>class AThreadNormalQueue
{
private:
	CRITICAL_SECTION m_csLock;
	queue<T> m_DataTable;

	// ������ݵĵط�
protected:
public:
	AThreadNormalQueue()
	{
		InitializeCriticalSection(&m_csLock);
	}

	~AThreadNormalQueue()
	{
		Clear();
		DeleteCriticalSection(&m_csLock);
	}

	void Push(T Data)
	{
		ThreadLock lock(&m_csLock);
		m_DataTable.push(Data);
	}

	bool Pop(T *output)
	{
		ThreadLock lock(&m_csLock);
		if (Count() <= 0)
		{
			return false;
		}
		T Result = m_DataTable.front();
		m_DataTable.pop();
		if(output)
		{
			*output = Result;
		}
		return true;
	};

	void Clear()
	{
		ThreadLock lock(&m_csLock);
		while (!m_DataTable.empty())
		{
			m_DataTable.pop();
		}
	}

	__inline int Count()
	{
		ThreadLock lock(&m_csLock);
		return m_DataTable.size();
	}

	__inline bool IsEmpty()
	{
		return m_DataTable.empty();
	}
};

// ����STL   PriorityQueue�����ȼ�����(������)    ,δ���
/*
template <class T> class APriorityQueue
{
class CTypePtr   //�ڵ�ָ���࣬< �����������Ժ�����ָ��priority_queue���������Ǵ�С����
{
public:
T* ptr;

CTypePtr(T * node)
{
ptr = node;
}

operator CTypePtr *() const
{
return ptr;
}

bool operator < (const CTypePtr& other) const     //����<�Ƚϲ����������ڸ�������������
{
return ((*ptr) > (*other));
}

bool operator == (const CTypePtr& other) const
{
return ( (*ptr) == (*other));
}
};
typedef std:: priority_queue<CTypePtr> NodeQueue;
private:
NodeQueue    PQueue;
protected:
public:
void Push(T *Data);
T *Pop()
{
if (Count()<=0)
{
return NULL;
}
T * Result = DataTable->At(0);
DataTable->Delete(0);
return Result;
};
void Clear(){DataTable->Clear();} //��ն���,�����ͷŶ��������Ԫ��
void FreeAndClear()
{
T *CurData;      //�ͷŶ��������Ԫ�ز�����ն���
while (Count()>0)
{
CurData = Pop();
delete  CurData;
}
Clear();
}
__inline T *   At(int Index){return DataTable->At(Index);}
__inline int Count(){return PQueue.Count();}
}; */

// ����AList�� ���ȼ�����,���ܲ��ѣ��ȴ�����ʵ��
// CListSortCompare����
/* int ComparDistance(A *Item1, A *Item2)
{
if (Item1->Dis  < Item2->Dis)
{
return 1;
}
else if(Item1->Dis == Item2->Dis)
{
return 0;
}
else if(Item1->Dis > Item2->Dis)
{
return -1;
}
else
{
return 0;
}
} */
template<class T>class APriorityQueue
{
	typedef int(*CListSortCompare)(T * Item1, T * Item2);

private:
	AList<T> *DataTable;
	// ������ݵĵط�
protected:
	CListSortCompare _SortCompareFunc;

public:
	APriorityQueue(CListSortCompare SortCompareFunc, int MaxSize = 1000)
	{
		DataTable = new AList<T>(false, MaxSize); // ����ָ���Ƴ�Ԫ�ص�ʱ���Ƿ��Զ�����delete�ͷ�ɾ��Ԫ��
		_SortCompareFunc = SortCompareFunc;
	}

	~APriorityQueue()
	{
		delete DataTable;
	}

	void Push(T *Data)
	{
		DataTable->Add(Data);
		DataTable->Sort(_SortCompareFunc);
	}

	T *Pop()
	{
		if (Count() <= 0)
		{
			return NULL;
		}
		T * Result = DataTable->At(0);
		DataTable->Delete(0);
		return Result;
	};

	void Clear()
	{
		DataTable->Clear();
	}
	// ��ն���,�����ͷŶ��������Ԫ��
	void FreeAndClear()
	{
		T *CurData; // �ͷŶ��������Ԫ�ز�����ն���
		while (Count() > 0)
		{
			CurData = Pop();
			delete CurData;
		}
		Clear();
	}

	__inline T * At(int Index)
	{
		return DataTable->At(Index);
	}

	__inline int Count()
	{
		return DataTable->Count();
	}

};

// ����AList�Ķ�ջ��
template<class T>class AStack
{
private:
	AList<T> *DataTable;

	// ������ݵĵط�
protected:
public:
	AStack(int MaxSize = 1000)
	{
		DataTable = new AList<T>(false, MaxSize); // ����ָ���Ƴ�Ԫ�ص�ʱ���Ƿ��Զ�����delete�ͷ�ɾ��Ԫ��
	}

	~AStack()
	{
		delete DataTable;
	}

	void Push(T *Data)
	{
		DataTable->Add(Data);
	}

	T *Pop()
	{
		if (Count() <= 0)
		{
			return NULL;
		}
		T * Result = DataTable->At(Count() - 1);
		DataTable->Delete(Count() - 1);
		return Result;
	};

	void Clear()
	{
		DataTable->Clear();
	}
	// ��ն���,�����ͷŶ��������Ԫ��
	void FreeAndClear()
	{
		T *CurData; // �ͷŶ��������Ԫ�ز�����ն���
		while (Count() > 0)
		{
			CurData = Pop();
			delete CurData;
		}
		Clear();
	}

	__inline T * At(int Index)
	{
		return DataTable->At(Index);
	}

	__inline int Count()
	{
		return DataTable->Count();
	}
};
// ---------------------------------------------------------------------------
#endif

