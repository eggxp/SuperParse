//---------------------------------------------------------------------------
//��ָ̬����������������
//����(���Ŀ��):
//����vector��װ,�ṩһ��������VCL��TList�Ľӿ�
//�����Զ��ͷ�Ԫ��,list����Ԫ��ָ���Խ�ʡ�ڴ�ռ�


//����ʱ��: 2004.08.24
//�޸ļ�¼: 2004.08.24
//�޸ļ�¼: 2005.01.19  ������Sort����,���ÿ�������
//�޸ļ�¼: 2005.03.12  �޸���Add����,����������ʱ��,�Զ���������
//�޸ļ�¼: 2006.06.06  ������alist.hģ����delete������move�������ܵ����ڴ�й©��bug(���Ƿ��ֵ�bug)
//����: Bluely

//---------------------------------------------------------------------------
#ifndef alistH
#define alistH
#include <vector>
using namespace std;
#define  AERR_ARRAY_FULL -1
#define  AERR_NOERR     0
//���庯������,��������Ƚ�
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T> class AList
{
  typedef int (*CListSortCompare)(T * Item1, T * Item2);
  /*�û��Զ��庯��,���ڱȽ�����Ԫ�صĴ�С,�����������õ�
  //����: Ҫ���մ�С��������

  int ComparASC(T *Item1, T *Item2)
  {
    if (Item1  < Item2)
    {
      return 1;
    }
    else if(Item1 == Item2)
    {
      return 0;
    }
    else if(Item1 > Item2)
    {
      return -1;
    }
    else
    {
      return 0;
    }
  }
  //���մӴ�С��˳������
  int ComparLow(T *Item1, T *Item2)
  {
    if (Item1  > Item2)
    {
      return 1;
    }
    else if(Item1 == Item2)
    {
      return 0;
    }
    else if(Item1 < Item2)
    {
      return -1;
    }
    else
    {
      return 0;
    }
  }*/
  private:
     bool    m_IsAutoFree;
  protected:
     vector<T *>  IndexTable;
     int          m_TrueSize;
     int          m_MaxSize;
     void         QuickSort(int L, int R,CListSortCompare SCompare);
  public:
     AList(bool IsAutoFree = true,int MaxSize = 10);  //����ָ���Ƴ�Ԫ�ص�ʱ���Ƿ��Զ�����delete�ͷ�ɾ��Ԫ��
     ~AList();
     __inline int    Count(){return m_TrueSize;}      //����Ԫ�ص�����
     __inline int    MaxSize(){return m_MaxSize;}     //���������ܴ�С
	 bool   Add(T *Data,bool AddToFirst=false);      //���һ��Ԫ��,��������򸲸�����ֵ,AddToFirst���Ϊ��,��ô������뵽��һ��Ԫ�� ,Ϊ������뵽���һ��Ԫ��
     T *    At(int Index);     //����Index���һ��Ԫ��
     T *   operator[](int Index){return At(Index);}
     void   Clear();           //���
     int    IndexOf(T *Data);  //����T���Ԫ�ص�Index
     void   Delete(int Index);  //ɾ��һ��Ԫ��
     T *    First();            //���ص�һ��Ԫ��
     T *    Last();             //�������һ��Ԫ��
     void   Pack();             //��������,�Ƴ�����ΪNULL��Ԫ��
     int    Remove(T *Data);    //�Ƴ�ĳ��Ԫ��
     void   Exchange(int Index1,int Index2);   //��������Ԫ�ص�ֵ
     void   Move(int DesIndex,int SrcIndex);   //��һ��Ԫ�ص�ֵ�ƶ�����һ��λ��
     int    LastError;
     void   SetNULL(int Index);
	 void   Insert(int Index,T *Data);
	 void   Replace(int Index,T*Data); //��һ����Ԫ���滻ĳλ���ϵľ�Ԫ��(�Զ��ͷž�Ԫ��)
     void   Sort(CListSortCompare SortCompareFunc);
     void   ReSize(int NewSize); //���·��������ܴ�С,��������е�����

};

//---------------------------------------------------------------------------
template <class T>   AList<T>::AList(bool IsAutoFree,int MaxSize)
{
	   if (MaxSize <=0)
	   	 MaxSize = 1;
     m_IsAutoFree =   IsAutoFree;
     ReSize(MaxSize);
     LastError = AERR_NOERR;
}
//---------------------------------------------------------------------------
template <class T>   AList<T>::~AList()
{
     Clear();
}
//---------------------------------------------------------------------------
template <class T>  void AList<T>::ReSize(int NewSize)
{
     m_TrueSize = 0;
     Clear();
     m_MaxSize =   NewSize;
     IndexTable.reserve(m_MaxSize);
     for (int i=0;i<m_MaxSize;i++)
      IndexTable.push_back(NULL);
}
//---------------------------------------------------------------------------
template<class T>
bool AList<T>::Add(T *Data,bool AddToFirst)
{
    if(m_TrueSize >= m_MaxSize)                     //�Ѿ�����
    {
        int OldSize = m_MaxSize;
        m_MaxSize = m_MaxSize * 2;       //����������Ϊԭ����һ��
        for(int i = 0; i < OldSize;i++) //�����Ԫ��
        {
            IndexTable.push_back(NULL);
        }
    }
	if(AddToFirst)
	{
     	Insert(0,Data);
	}
	else
	{
		IndexTable[m_TrueSize] = Data;
		m_TrueSize++;
	}
    return true;
}
//---------------------------------------------------------------------------
template <class T>  void  AList<T>::Insert(int Index,T *Data)
{
    if (m_TrueSize>=m_MaxSize)   //Ԥ���ռ䲻����
    {
        int OldSize = m_MaxSize;
        m_MaxSize = m_MaxSize * 2;
        for(int i = 0; i < OldSize;i++) //�����Ԫ��
        {
			IndexTable.push_back(NULL);
        }
	}
	if (m_TrueSize ==0)      //��û��Ԫ��,ֱ�Ӳ���
	{
	   IndexTable[m_TrueSize] = Data;
	   m_TrueSize++;
	   return;
	}
	if (Index>=0 && Index<m_TrueSize)
	{
	   //��ǰindex��ʼ��Ԫ��ָ������Ų��
	   m_TrueSize++; //Ԫ�ظ�����1
	   memmove(&IndexTable[Index+1],&IndexTable[Index],(m_TrueSize-Index-1)*sizeof(T *));
	   IndexTable[Index] = Data;  //������Ԫ��
	}
}
//---------------------------------------------------------------------------
template <class T>  int  AList<T>::IndexOf(T *Data)
{
    if (Data == NULL)
      return -1;
    for (int i=0;i<m_TrueSize;i++)
    {
       if (IndexTable[i] == Data)
         return i;
    }
    return -1;
}
//----------------------------------------------------------------------------
template <class T>  T *   AList<T>::At(int Index)
{
    if (Index>=0 &&  Index<m_TrueSize)
    {
      return  IndexTable[Index];
    }
    else
     return NULL;
}
//----------------------------------------------------------------------------
template <class T>  void  AList<T>::Clear()
{
   for (int i=0;i<m_TrueSize;i++)
   {
     if (m_IsAutoFree && IndexTable[i] != NULL)
       delete IndexTable[i];
       IndexTable[i] = NULL;
   }
   m_TrueSize = 0;
}
//----------------------------------------------------------------------------
template <class T> void  AList<T>::Delete(int Index)
{
  if (Index>=0 && Index<m_TrueSize)
  {
    if (m_IsAutoFree && IndexTable[Index]!=NULL)
      delete  IndexTable[Index];
    IndexTable[Index] = NULL;
	if (Index < m_TrueSize-1)  //����������һ��Ԫ��,�ᶯ
	memcpy(&IndexTable[Index],&IndexTable[Index+1],(m_TrueSize-(Index+1))*sizeof(T *));
    m_TrueSize --;
  }
}
//----------------------------------------------------------------------------
template <class T> void  AList<T>::SetNULL(int Index)
{
  if (Index>=0 && Index<m_TrueSize)
  {
    if (m_IsAutoFree && IndexTable[Index]!=NULL)
      delete  IndexTable[Index];
    IndexTable[Index] = NULL;
  }
}
//----------------------------------------------------------------------------
template <class T> T *  AList<T>::First()
{
   if (m_TrueSize>0)
     return   IndexTable[0];
   else
     return NULL;
}
//----------------------------------------------------------------------------
template <class T> T *  AList<T>::Last()
{
   if (m_TrueSize>0)
     return   IndexTable[m_TrueSize-1];
   else
     return NULL;
}
//----------------------------------------------------------------------------
template <class T> void  AList<T>::Pack()
{
   for (int i=m_TrueSize-1;i>=0;i--)
   {
      if (IndexTable[i] == NULL)
      {
        Delete(i);
      }
   }
}
//----------------------------------------------------------------------------
template <class T> int  AList<T>::Remove(T *Data)
{
   int Index =   IndexOf(Data);
   if (Index>=0)
   {
     Delete(Index);
   }
   return Index;
}
//---------------------------------------------------------------------------
template <class T> void  AList<T>::Exchange(int Index1,int Index2)
{
   T * tempEm;
   if (Index1<0 || Index1>=m_TrueSize || Index2<0 || Index2>=m_TrueSize)
   {
      return;
   }
   tempEm = IndexTable[Index1];
   IndexTable[Index1] =   IndexTable[Index2];
   IndexTable[Index2] =   tempEm;
}
//---------------------------------------------------------------------------
template <class T> void  AList<T>::Move(int DesIndex,int SrcIndex)
{
   if (DesIndex == SrcIndex)
     return;
   if (DesIndex<0 || DesIndex>=m_TrueSize || SrcIndex<0 || SrcIndex>=m_TrueSize)
     return;
   if  (IndexTable[DesIndex]!=NULL && m_IsAutoFree)
   {
      delete  IndexTable[DesIndex];
   }
   IndexTable[DesIndex] = IndexTable[SrcIndex];
   if (SrcIndex < m_TrueSize-1)  //����������һ��Ԫ��,�ᶯ
    memcpy(&IndexTable[SrcIndex],&IndexTable[SrcIndex+1],(m_TrueSize-(SrcIndex+1))*sizeof(T *));
   m_TrueSize --;
}
//---------------------------------------------------------------------------
template <class T> void  AList<T>::Replace(int Index,T*Data)
{
   if (Index<0 || Index>=m_TrueSize)
     return;
   if  (IndexTable[Index]!=NULL && m_IsAutoFree)    //�Զ��ͷ�ԭ����Ԫ��
   {
      delete  IndexTable[Index];
   }
   IndexTable[Index] = Data; //����Ԫ�طŵ�ԭ����λ��
}
//---------------------------------------------------------------------------
template <class T> void  AList<T>::Sort(CListSortCompare SortCompareFunc)
{
  if (Count() > 1)
  {
    QuickSort(0,Count() - 1,SortCompareFunc);
  }
}
//---------------------------------------------------------------------------
template <class T> void  AList<T>::QuickSort(int L, int R,CListSortCompare SCompare)
{
  int I=0;
  int J=0;
  int Half;
  T *P=NULL;
  T* t=NULL;
  do
  {
    I = L;
    J = R;
    Half = (L + R) >> 1;
    P = IndexTable[Half];
    do
    {
      while (SCompare(IndexTable[I],P) < 0)
      {
        I++;
      }
      while (SCompare(IndexTable[J],P) > 0)
      {
        J--;
      }
      if (I <= J)
      {
        t = IndexTable[I];
        IndexTable[I] = IndexTable[J];
        IndexTable[J] = t;
        I++;
        J--;
      }
    }
    while (I <= J);
    if (L < J)
    {
      QuickSort(L,J,SCompare);
    }
    L = I;
  }
  while (I < R);
}
//---------------------------------------------------------------------------
#endif
