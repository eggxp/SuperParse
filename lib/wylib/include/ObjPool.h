//---------------------------------------------------------------------------

#ifndef ObjPoolH
#define ObjPoolH
#include "alist.h"
#include <deque>
//---------------------------------------------------------------------------
//ָ����� �����, ֧��������ٴ�ȡ,֧�ֿ��ٲ��ҿ��ж�����ͷſ��ж���

//����(���Ŀ��):
//����AListʵ��ָ��������,����ʹ��һ��deque�������ѷ����δ�������
//�����Զ��ͷ�Ԫ��,list����Ԫ��ָ���Խ�ʡ�ڴ�ռ�

//	�ڴ��������㷨
//	                          ---------
//      Free(T *)             | FREE   |	<----Get()
//          |                 |--------           |
//          |                 | FREE   |          |
//          |                 |--------           |
//          |                 | FREE   |          |
//          |                 |--------           |
//          |                 | FREE   |          |
//      SetUsed(T *,false)	  |--------           | T * Data = At(0);	//�ӵ�һ��Ԫ��ȡ��
//          |push_back()      | FREE   |          | pop_front();        //�Ƴ�
//          |                 |--------           | SetUsed(T *,true)   //��Ϊ�Ѿ�ʹ��
//      	|      			  | FREE   |
//          |--------------->  --------
//

//����ʱ��: 2007.09.21
//����: Bluely



template <class T> class AObjPool
{
typedef bool (*TCLASS_OPFUNC_IS_USED)(T * Item1);
typedef void (*TCLASS_OPFUNC_SET_USED)(T * Item1,bool Used);
  private:
  protected:
	 AList<T> 	  * TTable;  //Ԫ������
	 deque<T *>  	IndexTable; //Ԫ�������� ,
	 int			m_PoolSize;   //������С
  public:
	 int    LastError;
  public:
	 AObjPool(int PoolSize);  //����ָ���Ƴ�Ԫ�ص�ʱ���Ƿ��Զ�����delete�ͷ�ɾ��Ԫ��
	 ~AObjPool();
	 __inline int    Count(){return TTable->Count();}      //����Ԫ�ص�����
	 __inline int    FreeCount(){return IndexTable.size();}   //����δʹ��Ԫ�ص�����
	 bool   Add(T *Data);     //���һ��Ԫ��,��������򸲸�����ֵ,AddToFirst���Ϊ��,��ô������뵽��һ��Ԫ�� ,Ϊ������뵽���һ��Ԫ��
	 T *    At(int Index){return TTable->At(Index);}     //����Index���һ��Ԫ��
	 T *    AtFreeQueue(int Index){return IndexTable.at(Index);}  //���������ӿ��ж��л��һ��Ԫ��
	 T *   operator[](int Index){return At(Index);}
	 int    IndexOf(T *Data){return TTable->IndexOf(Data);}  //����T���Ԫ�ص�Index
	 void   Clear();           //���
	 T	*	Get();			  //�ӻ����������ȡһ�����еĶ���
	 void   Free(T * Data);  //ɾ��һ��Ԫ��
	 bool	IsUsed(T * Data)
	 {
		 if (CB_IsUsedFunc)
		 {
			 return CB_IsUsedFunc(Data);
		 }
		 return false;
	 }
	 void   SetUsed(T * Data, bool Used)
	 {
		if(CB_SetUsedFunc)
		{
		   CB_SetUsedFunc(Data,Used);
		}
	 }
	 TCLASS_OPFUNC_IS_USED	 		 CB_IsUsedFunc;		//����һ��Ԫ���Ƿ�ʹ����,��Ҫʹ���߸���ʵ�����ָ��
	 TCLASS_OPFUNC_SET_USED	 		 CB_SetUsedFunc;       //����һ��Ԫ�ص�ʹ�ñ�־ ,��Ҫʹ���߸���ʵ�����ʵ��

};


//---------------------------------------------------------------------------
template <class T>   AObjPool<T>::AObjPool(int PoolSize)
{
	  m_PoolSize  = PoolSize;
	   if (m_PoolSize <=0)
		 m_PoolSize = 1;
	 TTable = new AList<T>(true,m_PoolSize);
	 LastError = AERR_NOERR;
	 CB_IsUsedFunc=NULL;
	 CB_SetUsedFunc=NULL;
}
//---------------------------------------------------------------------------
template <class T>   AObjPool<T>::~AObjPool()
{
	 delete TTable;
}
//---------------------------------------------------------------------------
template <class T>  bool AObjPool<T>::Add(T *Data)
{
	 TTable->Add(Data);
	 IndexTable.push_back(Data);   //��һ�μ����Ԫ��Ĭ��Ϊ�����ڴ�,
	 SetUsed(Data,false); //����Ϊ����δʹ��
	 return true;
}
//---------------------------------------------------------------------------
template <class T>  void AObjPool<T>::Clear()
{
	 IndexTable.clear();
	 TTable->Clear();
}
//---------------------------------------------------------------------------
template <class T>    T	*	AObjPool<T>::Get()
{
		if (FreeCount()<=0)
		{
			return NULL; 		//û�п��л�������
		}
		T * Data = IndexTable.at(0);   //ȡ����һ��Ԫ��
		while(IsUsed(Data))
		{
			//��Ԫ���Ѿ����ù�,����������������ܷ��ڿ��ж�������,�û����ظ�Free�����������
			IndexTable.pop_front();        //ɾ����һ��Ԫ��
			Data = IndexTable.at(0); 	   //�ٴ�ȡһ��Ԫ��
		}
		IndexTable.pop_front();
		SetUsed(Data,true);   //����Ϊ�Ѿ�ʹ��
		return Data;
}
//---------------------------------------------------------------------------
template <class T> void   AObjPool<T>::Free(T * Data)
{
	   if(!IsUsed(Data))
	   {
		  //��־�Ѿ������óɿ��е�,Ϊ�˷�ֹ�ظ�����,���ŵ����ж���
		  return;
       }	
	   SetUsed(Data,false);
	   IndexTable.push_back(Data);  //��ӵ����ж���
}
#endif
