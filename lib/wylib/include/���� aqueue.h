//---------------------------------------------------------------------------

#ifndef aqueueH
#define aqueueH
#include <queue>
#include "alist.h"

// ����,���ȶ���,��ջ����������

//����ʱ��: 2005.01.19
//����: Bluely
//����AList�Ķ�����

//AQueue         ����,�Ƚ��ȳ�
//APriorityQueue ���ȼ�����,��������,���ڿ�������,ĿǰЧ�ʲ���,�ȴ��ö���������ʵ��
//AStack         ��ջ��,�Ƚ����
template <class T> class AQueue
{
  private:
     AList<T> *DataTable; //������ݵĵط�
  protected:
  public:
     AQueue(int MaxSize = 1000)
     {
        DataTable = new AList<T>(false,MaxSize);  //����ָ���Ƴ�Ԫ�ص�ʱ���Ƿ��Զ�����delete�ͷ�ɾ��Ԫ��
     }
     ~AQueue(){delete DataTable;}
     void Push(T *Data){DataTable->Add(Data);}
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
     __inline int Count(){return DataTable->Count();}
};

//����STL   PriorityQueue�����ȼ�����(������)    ,δ���
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
};     */

//����AList�� ���ȼ�����,���ܲ��ѣ��ȴ�����ʵ��
//CListSortCompare����
/*int ComparDistance(A *Item1, A *Item2)
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
template <class T> class APriorityQueue
{
  typedef int (*CListSortCompare)(T * Item1, T * Item2);
  private:
     AList<T> *DataTable; //������ݵĵط�
  protected:
    CListSortCompare _SortCompareFunc;
  public:
     APriorityQueue(CListSortCompare SortCompareFunc,int MaxSize = 1000)
     {
        DataTable = new AList<T>(false,MaxSize);  //����ָ���Ƴ�Ԫ�ص�ʱ���Ƿ��Զ�����delete�ͷ�ɾ��Ԫ��
        _SortCompareFunc =   SortCompareFunc;
     }
     ~APriorityQueue(){delete DataTable;}
     void Push(T *Data){DataTable->Add(Data);DataTable->Sort(_SortCompareFunc);}
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
     __inline int Count(){return DataTable->Count();}

};

//����AList�Ķ�ջ��
template <class T> class AStack
{
  private:
     AList<T> *DataTable; //������ݵĵط�
  protected:
  public:
     AStack(int MaxSize = 1000)
     {
        DataTable = new AList<T>(false,MaxSize);  //����ָ���Ƴ�Ԫ�ص�ʱ���Ƿ��Զ�����delete�ͷ�ɾ��Ԫ��
     }
     ~AStack(){delete DataTable;}
     void Push(T *Data){DataTable->Add(Data);}
     T *Pop()
     {
       if (Count()<=0)
       {
          return NULL;
       }
       T * Result = DataTable->At(Count()-1);
       DataTable->Delete(Count()-1);
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
     __inline int Count(){return DataTable->Count();}
};
//---------------------------------------------------------------------------
#endif
