/****************************************************************
 * ͨ������ģ�壺
 * 1������ģ��(IDataArray)��
 *    ��ʱ�򳣳��������飬��array[index]��ģ��IDataArray�����ʹ
 *    ����������������������Ĵ�С����Delphi�����SetLength
 *    ģ���������·����ڴ沢�Ҹ���ԭ�������ݡ��������Զ�����
 *    ���ش򿪣�ģ����������ʵ�����Ԫ������ֵ�Զ������ڴ��С
 *    ��ʹ�㲻�����ڴ泬�޵Ĺ��ǡ����ͷ�ģ��ʱģ����Զ����ռ��
 *    ���ڴ棬ģ��֧��ͨ�����ݺ��Զ���ṹ������֧���࣬�÷�����
 *               IDataArray<int> myarray;   // ģ����int����
 *               myarray.SetAutoMode(1);    // ���Զ����俪��
 *               myarray[0]=1;              // ģ�嶼�Զ�������
 *               myarray[1]=myarray[0]+1;
 * 2�������б�ģ��(ILister)
 *
 * ����޸�ʱ�䣺2003-06-12 19:57
 * �޸ļ�¼��
 *    2003-06-12 19:57
 *            ����һ��Bug��SetLengthδ����0���������new��0�ֽ�
 *        ��������ڴ�й©��
 ***************************************************************/

#ifndef __I_TEMPLATE_H__
#define __I_TEMPLATE_H__

#ifndef __cplusplus
#error  This file can only be compiled with a C++ compiler !!
#endif

template <class ClassType>
class IDataArray			// ����ģ��
{
protected:
	ClassType *TypeData;
	ClassType Nil;
	int DataCount;
	int AutoMode;
public:
	int Error;				// ���������(�������,���������)
	virtual ~IDataArray();
	IDataArray();
	IDataArray(int InitSize);
	int SetLength(int l);
	int GetLength();
	int SetAutoAlloc(int flag);
        int Delete(int index);
        void Clear();
	ClassType& operator[](int index);
};


template <class ClassType>
class ILister
{
protected:
	struct TypeRow
	{
		ClassType **data;
		int ColCount;
	};
	TypeRow *TypeRows;
	ClassType Nil;
	int RowCount;
	int AddRow();
public:
	int Error;
	ILister();
	virtual ~ILister();
	int Alloc();
	int Release(int handle);
	void Clear();
	ClassType* operator[](int handle);
};


template <class ClassType> IDataArray<ClassType>::IDataArray()
{
  TypeData = 0;
  DataCount = 0;
  AutoMode = 0;
  Error = 0;
}

template <class ClassType> IDataArray<ClassType>::IDataArray(int InitSize)
{
  IDataArray::IDataArray();
  SetLength(InitSize);
}

template <class ClassType> IDataArray<ClassType>::~IDataArray()
{
  delete [] TypeData;
  TypeData = 0;
  DataCount = 0;
}
template <class ClassType> int IDataArray<ClassType>::SetLength(int NewLen)
{
  int block1 = (DataCount + 127) >> 7, block2 = (NewLen + 127) >> 7;

  if (block1 == block2)
  {
    DataCount = NewLen;
    return 0;
  }
  if(block2 == 0)         // Clear all data ...
  {
    if(TypeData)
    {
      delete []TypeData;
      DataCount = NewLen;
      TypeData = NULL;
      return 0;
    }
  }
  if (block1 == 0 || TypeData == 0)
  {
    TypeData = new ClassType[block2 << 7];
    if (!TypeData)
    {
      Error++;
      return -1;
    }
    DataCount = NewLen;
  }
  else
  {
    ClassType *NewData;
    NewData = new ClassType[block2 << 7];
    if (!NewData)
    {
      Error++;
      return -1;
    }
    int min = (DataCount <= NewLen)? DataCount : NewLen;
    for (int i=0;i<min;i++)
      NewData[i] = TypeData[i];
    delete [] TypeData;
    TypeData = NewData;
    DataCount = NewLen;
  }
  return 0;
}
template <class ClassType> int IDataArray<ClassType>::GetLength()
{
  return DataCount;
}
template <class ClassType> int IDataArray<ClassType>::SetAutoAlloc(int flag)
{
  AutoMode = flag;
  return 0;
}
template <class ClassType> int IDataArray<ClassType>::Delete(int index)
{
  int iResult = 0;
  int block2 = ((DataCount - 1) + 127) >> 7;
  if (index >= 0 && index < DataCount)
  {
    if(DataCount == 1)
    {
      delete []TypeData;
      TypeData = 0;
      DataCount = 0;
    }
    else
    {
      ClassType *NewData;
      NewData = new ClassType[block2 << 7];
      if(NewData)
      {
        for(int i=0,j=0;i<DataCount;i++)
        {
          if(i != index)
          {
            NewData[j] = TypeData[i];
            j++;
          }
        }
        DataCount--;
        delete [] TypeData;
        TypeData = NewData;
        iResult = 1;
      }
      else
        Error++;
    }
  }
  else
    Error++;
  return iResult;
}

template <class ClassType> void IDataArray<ClassType>::Clear()
{
  SetLength(0);
}

template <class ClassType> ClassType& IDataArray<ClassType>::operator[](int index)
{
  if (index < 0)
  {
    Error++;
    return Nil;
  }
  if (index >= DataCount)
  {
    if (!AutoMode)
    {
      Error++;
      return Nil;
    }
    if (SetLength(index + 1))
    {
      Error++;
      return Nil;
    }
  }
  return TypeData[index];
}

template <class ClassType> ILister<ClassType>::ILister()
{
  RowCount = 0;
  TypeRows = 0;
  Error = 0;
}

template <class ClassType> int ILister<ClassType>::AddRow()
{
  int NewIndex = 0;
  if (!TypeRows)
  {
    TypeRows = new TypeRow;
    if (TypeRows == 0)
      return -1;
    NewIndex = 0;
  }
  else
  {
    TypeRow *NewRows = new TypeRow[RowCount + 1];
    if (!NewRows)
      return -1;
    for (int i=0;i<RowCount;i++)
      NewRows[i] = TypeRows[i];
    delete [] TypeRows;
    TypeRows = NewRows;
    NewIndex = RowCount;
  }
  TypeRows[NewIndex].ColCount = 0;
  TypeRows[NewIndex].data = new ClassType *[64];
  if (!TypeRows[NewIndex].data)
    return -2;
  for (int i=0;i<64;i++)
    TypeRows[NewIndex].data[i] = 0;
  RowCount++;
  return 0;
}

template <class ClassType> int ILister<ClassType>::Alloc()
{
  int line, i;
  for (line=0;line<RowCount;line++)
    if (TypeRows[line].ColCount < 64)
      break;
  if (line == RowCount)
    if (AddRow())
    {
      Error++;
      return 0;
    }
  for (i=0;i<64;i++)
    if (TypeRows[line].data[i] == 0)
      break;
  if (i == 64)
  {
    Error++;
    return 0;
  }
  TypeRows[line].data[i] = new ClassType;
  if (!TypeRows[line].data[i])
  {
    Error++;
    return 0;
  }
  TypeRows[line].ColCount++;
  return line * 64 + i;
}

template <class ClassType> int ILister<ClassType>::Release(int handle)
{
  int line = handle >> 6;
  int index = handle & 63;
  if (line < 0 || line >= RowCount)
    return -1;
  if (TypeRows[line].data[index] == 0)
    return -2;
  delete TypeRows[line].data[index];
  TypeRows[line].data[index] = 0;
  TypeRows[line].ColCount--;
  return 0;
}

template <class ClassType> ClassType* ILister<ClassType>::operator[](int handle)
{
  int line = handle >> 6;
  int index = handle & 63;
  if (line < 0 || line >= RowCount)
  {
    Error++;
    return &Nil;
  }
  if (index < 0 || TypeRows[line].data[index] == 0)
  {
    Error++;
    return &Nil;
  }
  return TypeRows[line].data[index];
}

template <class ClassType> ILister<ClassType>::~ILister()
{
  for (int line=0;line<RowCount;line++)
  {
    for (int i=0;i<64;i++)
      if (TypeRows[line].data[i])
        delete TypeRows[line].data[i];
    delete [] TypeRows[line].data;
  }
  if (TypeRows)
    delete [] TypeRows;
  TypeRows = 0;
  RowCount = 0;
}

template <class ClassType> void ILister<ClassType>::Clear()
{
  for (int line=0;line<RowCount;line++)
  {
    for (int i=0;i<64;i++)
      if (TypeRows[line].data[i])
      {
	delete TypeRows[line].data[i];
	TypeRows[line].data[i] = 0;
      }
    TypeRows[line].ColCount = 0;
  }
  Error = 0;
}

#endif

