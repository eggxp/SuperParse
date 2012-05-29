//---------------------------------------------------------------------------
//bluely  2003.05.26
//������TList��,��һ�γ���ʹ��ģ����
//��Ҫ�Ľ� ֧������ ֧���Զ��ͷ�

/*���ģ���಻ͬ����,���뽫����ʵ�ְ����ڵ�������ÿ��Դ�ļ���,
  ʹ�������ܴӺ���ʵ�ֲ������롣ͨ���������ǽ�ģ����ĺ���ʵ��
  Ҳ���ڶ�������ͷ�ļ���,����ֻ���ڵ��õ�Դ�ļ��а�����ͷ��
  �����ɡ�*/

//�޸�����2003.08.22
// ע:  �������VCL ,�����Ѿ���������,���Բ���Alist�����


#ifndef mlistH
#define mlistH
#include <Classes.hpp>
namespace TypeList
{
template <class T> class TTypeList:public TList
{
  private:
     bool bAutoFree;
  protected:

  public:
     __fastcall TTypeList(bool bAutoFreeObj = false);
     __fastcall ~TTypeList();
     int  __fastcall Add(T *Item);
     void __fastcall Delete(int Index);
     void __fastcall Clear();
     T * __fastcall First();
     int __fastcall IndexOf(T *Item);
     void __fastcall Insert(int Index,T *Item);
     T * __fastcall Last();
     int __fastcall Remove(T *Item);
     T *__fastcall Get(int Index);
     void __fastcall Put(int Index,T *Item);
     bool __fastcall SaveToFile(String FileName,WORD FileFlag);
     bool __fastcall LoadFromFile(String FileName,WORD FileFlag);
     bool __fastcall SaveToStream(TMemoryStream *FileName,WORD FileFlag);
     bool __fastcall LoadFromStream(TStream *FileStream,WORD FileFlag);
     __property T * Items[int Index] = {read=Get, write=Put};
};

template <class T> __fastcall TTypeList<T>::TTypeList(bool bAutoFreeObj)
{
    bAutoFree =  bAutoFreeObj;
}

template <class T> __fastcall TTypeList<T>::~TTypeList()
{
   Clear();
}

template <class T> T *__fastcall TTypeList<T>::Get(int Index)
{
   if (Index<0 || Index>=Count)
    return NULL;
   return (T *) TList::Get(Index);
}

template <class T> void __fastcall TTypeList<T>::Put(int Index,T *Item)
{
   TList::Put(Index,Item);
}

template <class T> int __fastcall TTypeList<T>::Add(T *Item)
{
   return TList::Add(Item);
}

template <class T> void __fastcall TTypeList<T>::Delete(int Index)
{
   if (bAutoFree)
     delete Get(Index);
   TList::Delete(Index);
}

template <class T> void __fastcall TTypeList<T>::Clear()
{
   if (bAutoFree)
   {
     for (int j=0;j<Count;j++)
      delete Items[j];
   }
   TList::Clear();
}

template <class T> T * __fastcall TTypeList<T>::First()
{
   return (T*)TList::First();
}

template <class T> int __fastcall TTypeList<T>::IndexOf(T *Item)
{
   return TList::IndexOf(Item);
}

template <class T> void __fastcall TTypeList<T>::Insert(int Index,T *Item)
{
   TList::Insert(Index,Item);
}

template <class T> T * __fastcall TTypeList<T>::Last()
{
   return (T *)TList::Last();
}

template <class T> int __fastcall TTypeList<T>::Remove(T *Item)
{
   int nIndex = TList::Remove(Item);
   if (bAutoFree && (nIndex != -1))
      delete Item;
   return nIndex;
}
//���ļ���ȡ
template <class T> bool __fastcall TTypeList<T>::LoadFromFile(String FileName,WORD FileFlag)
{
   if (!FileExists(FileName))
     return false;
   WORD Flag;
   int  RecordCount=0;
   T *  Record;
   TMemoryStream *DatFile = new TMemoryStream;
   DatFile->LoadFromFile(FileName);
   Clear();
   DatFile->Read(&Flag,sizeof(WORD));
   if (Flag != FileFlag)
   {
      delete DatFile;
      return false;
   }
   RecordCount = (DatFile->Size-2)/sizeof(T);
   for (int i=0;i<RecordCount;i++)
   {
      Record = new T;
      DatFile->Read(Record,sizeof(T));
      Add(Record);
   }
   delete DatFile;
   return true;
}
//���浽�ļ�
template <class T> bool __fastcall TTypeList<T>::SaveToFile(String FileName,WORD FileFlag)
{
   WORD Flag;
   T *  Record;
   TMemoryStream *DatFile = new TMemoryStream;
   DatFile->Write(&FileFlag,sizeof(WORD));
   for (int i=0;i<Count;i++)
   {
      Record =  Get(i);
      DatFile->Write(Record,sizeof(T));
   }
   DatFile->SaveToFile(FileName);
   delete DatFile;
   return true;
}
//���浽�ļ�
template <class T> bool __fastcall TTypeList<T>::SaveToStream(TMemoryStream *FileName,WORD FileFlag)
{
   WORD Flag;
   T *  Record;
   FileName->Clear();
   FileName->Write(&FileFlag,sizeof(WORD));
   for (int i=0;i<Count;i++)
   {
      Record =  Get(i);
      FileName->Write(Record,sizeof(T));
   }
   FileName->Position = 0;
   return true;
}

//���ļ���ȡ
template <class T> bool __fastcall TTypeList<T>::LoadFromStream(TStream *FileStream,WORD FileFlag)
{
   WORD Flag;
   int  RecordCount=0;
   T *  Record;
   Clear();
   FileStream->Position = 0;
   FileStream->Read(&Flag,sizeof(WORD));
   if (Flag != FileFlag)
   {
      return false;
   }
   RecordCount = (FileStream->Size-2)/sizeof(T);
   for (int i=0;i<RecordCount;i++)
   {
      Record = new T;
      FileStream->Read(Record,sizeof(T));
      Add(Record);
   }
   return true;
}

}	/* namespace TypeList*/
using namespace TypeList;
//---------------------------------------------------------------------------
#endif
