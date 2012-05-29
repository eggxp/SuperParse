//����Ч�ʺ����ó���
//
//�ٶ�˵��:
//����   ֱ�Ӵ�ȡ   �ǳ���
//����   ѭ������   Խ�����Ԫ��Խ��,Ԫ��Խ��Խ��
//����   log(n)     ��,��ֱ�Ӵ�ȡ��һ���log(10000) = 4 log(100000)=5  log(1000000)=6,Ԫ��������һλ��,����ʱ��ͱ�ֱ�Ӵ�ȡ����һ��
//
//
//	
//������			�����ȡ�ٶ�At(i)		��Key�����ٶ�  		�ڴ�ṹ  		�ڴ�����		 �����Ӻ�ɾ���ٶ�      �Ƽ����ó���
//AList			  ����(ֱ�Ӵ�ȡ)  	����           		 ˳����  		  С(�޶��⿪��)   ��       					Ԫ����������,���Ҳ���Ҫ����KeyƵ�����ҵĳ���
//AIndexMap       ����            	����           		 Btree     		  ��               ��    					Key=Value��ʽ��֯�����ݳ���,��Ҫ����KeyƵ������Value�ĳ���,�������Indexֱ�Ӵ�ȡ�ĳ���
//AIndexHashMap   ����                ~=����(ȡ����           ��ϣͰ    		�ϴ�			   ��    					Key=Value��ʽ��֯�����ݳ���,��Ҫ����KeyƵ������Value�ĳ���,�������Indexֱ�Ӵ�ȡ�ĳ���
//                                        Hash������ײ��)
//AIndexList      ����(ֱ�Ӵ�ȡ)      ����                  ˳����(������Ԫ��)    ��		 ��					����Ҫ��Key���ٲ���,����ҪIndexֱ�Ӵ�ȡ�ĳ���,����Ԫ���Զ�����,���Բ�������Ҫ��Ԫ�ر���ԭʼ˳��ĳ���ʹ��
//AIndexListPro   ����(ֱ�Ӵ�ȡ)      ����                  ˳����(������Ԫ��)    ��		 ����(Խǰ��Խ��)	����Ҫ��Key���ٲ���,����ҪIndexֱ�Ӵ�ȡ�ĳ���,����Ԫ���Զ�����,���Բ�������Ҫ��Ԫ�ر���ԭʼ˳��ĳ���ʹ��

//�󲿷ֳ���,�Ƽ�ʹ��AIndexList
//---------------------------------------------------------------------------
//amap.h
//---------------------------------------------------------------------------
//������������ά���Ľ��Ƕ����ָ��,�����Ƕ����ʵ��,���ԱȽ��ʺϴ����ͽṹ,���ʺϴ��ԭʼ�������ͱ���int,DWORD
//

//////////////////////////////////////////////////////////////////////////////////
//����:    AIndexMap                                                            //
//////////////////////////////////////////////////////////////////////////////////
//����:   ����STL Map��װ��Map��(ƽ�������)
//����:   �ṩ����ʱ��Ŀ��ٲ��ҹ���, ������ӽ����Ԫ�ؾ���Key�ؼ���������������,
//        Ԫ�ش����֯ΪBtree,���ٲ���ɾ��,���ٲ���
//        Key�ؼ��ֱ���Ψһ
//        ���ֺ�AListһ���ļ���ʹ�ýӿ�
//ȱ��:
//��ΪMap�ǹ���ʽ����,Ԫ�����ڴ��ʵ��λ�ò�����,��֧�������ȡ,����At(i)��������ʹ�ñ���,ʱ������Ϊ����
//BTree�����vector�ж�����ڴ�����(��Žڵ�ָ��)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////
//����:    AIndexHashMap                                                        //
//////////////////////////////////////////////////////////////////////////////////
//����:    ����STL Hash_Map��װ�Ĺ�������,
//����:    �ṩ�ӽ�����ʱ��Ŀ��ٲ��ҹ���,Ч��ȡ����Hash����,������ӽ����Ԫ�ؾ���
//         Key�ؼ���������������,Ԫ�ش����֯��ʽΪHashɢ��
//ȱ��:
//��ΪHash_Map�ǹ���ʽ����,,Ԫ�����ڴ��ʵ��λ�ò�����,��֧�������ȡ,����At(i)��������ʹ�ñ���,ʱ������Ϊ����
//Hash_Map�����vector�ж�����ڴ�����(Ͱ����,N�������Žڵ�ָ��)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////
//����:    AIndexList                                                           //
//////////////////////////////////////////////////////////////////////////////////
//����:    ����STL vector����������
//����:    ͨ���ڲ�����ʹvector��������״̬,find����ʹ�ö��ֲ����㷨�����Ի��log(n)���������ٶ�,
//         ͬʱ�ṩ����洢����,֧�ֿ���At(index)����,Find����֮ǰ,���������״̬�����Ƿ���Ҫ��������
//ȱ��:    �������Ԫ�غ�,��������. ���ʺ�����Ҫ��Ԫ�ر���ԭʼ˳��ĳ���

//---------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
//����: IndexListPro
//���� : AIndexList�ļ�ǿ�棬֧���Զ����KeyType,����ֵ�����Զ���
//�Զ����KeyType���ͱ���֧�� == , > ,<�Ƚϲ�����



//2005.04.04 ��߮
#ifndef amapH
#define amapH

#if __BORLANDC__ < 0x0580
#include <hash_map>
#endif
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <vcl.h>



using namespace std;
//------------------------------------------------------------------------------
//mapָ������      AIndexMap
//------------------------------------------------------------------------------
template <class T>  class AIndexMap
{
  typedef map<string,T *,less<string> >::iterator IT_POS;
private:
   map<string,T *,less<string> >  m_DataMap;
   bool    m_IsAutoFree;
protected:

public:
  __fastcall AIndexMap(bool IsAutoFree = TRUE){m_IsAutoFree = IsAutoFree;}
  __fastcall ~AIndexMap(){Clear();}
  void  Clear();
  void  Add(const char * Key,T * lpData);
  T *   Find(const char * Key);
  T *   At(int Index);
  void  Delete(const char * Key);
  __inline int    Count(){return m_DataMap.size();}

};
//----------------------------------------------------------------------------
template <class T>  void  AIndexMap<T>::Clear()
{
   IT_POS Pos;
   for (Pos = m_DataMap.begin();Pos!= m_DataMap.end();++Pos)
   {
     if (m_IsAutoFree && Pos->second != NULL)
     {
       delete  Pos->second;
     }
   }
    m_DataMap.clear();
}
//----------------------------------------------------------------------------
template <class T>  void  AIndexMap<T>::Add(const char * Key,T * lpData)
{
     if (m_IsAutoFree && m_DataMap[Key] != NULL)
     {
       delete  m_DataMap[Key];
     }
    m_DataMap[Key] = lpData; //�÷���Ԫ��
}
//----------------------------------------------------------------------------
template <class T>  T *  AIndexMap<T>::Find(const char * Key)
{
   IT_POS Pos = m_DataMap.find(Key);
   if (Pos!= m_DataMap.end()) //�Ѿ������Keyֵ��Ԫ����
   {
      return  Pos->second;    //�ͷž�Ԫ��
   }
   return NULL;
}
//----------------------------------------------------------------------------
template <class T>  T *  AIndexMap<T>::At(int Index)
{
   if (Index>=Count() || Index<0)   //��Ч����
    return NULL;
   IT_POS Pos = m_DataMap.begin();
   if (Index==0)
   {
     return  Pos->second;
   }
   advance(Pos,Index);      //����
   return  Pos->second;
}

//----------------------------------------------------------------------------
template <class T>  void  AIndexMap<T>::Delete(const char * Key)
{
   IT_POS Pos = m_DataMap.find(Key);
   if (Pos!= m_DataMap.end()) //�Ѿ������Keyֵ��Ԫ����
   {
       if (m_IsAutoFree && Pos->second != NULL)
       {
          delete  Pos->second;    //�ͷž�Ԫ��
       }
       m_DataMap.erase(Pos);  //�Ƴ���Ԫ��
   }
}

#if __BORLANDC__ < 0x0580
//----------------------------------------------------------------------------
//AIndexHashMap   ������ָ������
//------------------------------------------------------------------------------
template <class T>  class AIndexHashMap
{
  typedef hash_map<string,T *,hash<string> >::iterator IT_POS;
private:
   hash_map<string,T *,hash<string> >  m_DataMap;
   bool    m_IsAutoFree;
protected:

public:
  __fastcall AIndexHashMap(bool IsAutoFree = TRUE){m_IsAutoFree = IsAutoFree;}
  __fastcall ~AIndexHashMap(){Clear();}
  void  Clear();
  void  Add(const char * Key,T * lpData);
  T *   Find(const char * Key);
  T *   At(int Index);
  void  Delete(const char * Key);
  __inline int    Count(){return m_DataMap.size();}
  __inline int    BucketCount(){return m_DataMap.bucket_count();}
  __inline void   SetBucketCount(int Count){m_DataMap.resize(Count);}

};
//----------------------------------------------------------------------------
template <class T>  void  AIndexHashMap<T>::Clear()
{
   IT_POS Pos;
   for (Pos = m_DataMap.begin();Pos!= m_DataMap.end();++Pos)
   {
     if (m_IsAutoFree && Pos->second != NULL)
     {
       delete  Pos->second;
     }
   }
    m_DataMap.clear();
}
//----------------------------------------------------------------------------
template <class T>  void  AIndexHashMap<T>::Add(const char * Key,T * lpData)
{
     if (m_IsAutoFree && m_DataMap[Key] != NULL)
     {
       delete  m_DataMap[Key];
     }
    m_DataMap[Key] = lpData; //�÷���Ԫ��
}
//----------------------------------------------------------------------------
template <class T>  T *  AIndexHashMap<T>::Find(const char * Key)
{
   IT_POS Pos = m_DataMap.find(Key);
   if (Pos!= m_DataMap.end()) //�Ѿ������Keyֵ��Ԫ����
   {
      return  Pos->second;    //�ͷž�Ԫ��
   }
   return NULL;
}
//----------------------------------------------------------------------------
template <class T>  T *  AIndexHashMap<T>::At(int Index)
{
   if (Index>=Count() || Index<0)   //��Ч����
    return NULL;
   IT_POS Pos = m_DataMap.begin();
   if (Index==0)
   {
     return  Pos->second;
   }
   advance(Pos,Index);      //����
   return  Pos->second;
}

//----------------------------------------------------------------------------
template <class T>  void  AIndexHashMap<T>::Delete(const char * Key)
{
   IT_POS Pos = m_DataMap.find(Key);
   if (Pos!= m_DataMap.end()) //�Ѿ������Keyֵ��Ԫ����
   {
       if (m_IsAutoFree && Pos->second != NULL)
       {
          delete  Pos->second;    //�ͷž�Ԫ��
       }
       m_DataMap.erase(Pos);  //�Ƴ���Ԫ��
   }
}

#endif

//----------------------------------------------------------------------------
//AIndexList   �����vectorģ��map set����Ϊ,�ṩ����洢��log(n)�Ŀ��ٲ�������
//------------------------------------------------------------------------------
typedef size_t (*CSTR_TO_SIZE_T)(const char * StrKey); //�Զ���Keyת������
template <class T>  class AIndexList
{
  typedef pair<size_t,T *> T_DATA_TYPE;
  typedef vector<T_DATA_TYPE>::iterator IT_POS;
  class DataCompare    //function obj
  {      // ���ڱȽϵ���
  public:
   bool operator()(const T_DATA_TYPE& lhs,   // ��������ıȽϺ���
	 const T_DATA_TYPE& rhs) const
   {
		return keyLess(lhs.first, rhs.first); // keyLess������
   }
  bool operator()(const T_DATA_TYPE& Ihs,   // ���ڲ��ҵıȽϺ���
     const T_DATA_TYPE::first_type& k) const // ����ʽ1,����lower_bound��
   {
        return keyLess(Ihs.first,k);
   }
   bool operator()(const T_DATA_TYPE::first_type& k,  // ���ڲ��ҵıȽϺ���
     const T_DATA_TYPE& rhs) const  // ����ʽ2,����equal_range��
   {
    return keyLess(k, rhs.first);
   } 

  private:
   bool keyLess(const T_DATA_TYPE::first_type& k1,  // ����ġ�
     const T_DATA_TYPE::first_type& k2) const // �ȽϺ���
   {
		return (k1 < k2);
   }
  };
private:
   vector<T_DATA_TYPE> m_IndexTable;
   bool    m_IsAutoFree;
   T_DATA_TYPE   KeyValue;
   
protected:
   bool    m_NeedSort; //�Ƿ���Ҫ������ſ��Բ���
   size_t  KeyConv(const char * StrKey)
   {
       if (pfStrToSize_T)
       {
         return pfStrToSize_T(StrKey);
       }
       return atoi(StrKey);
   }
public:
  __fastcall AIndexList(bool IsAutoFree = TRUE){m_IsAutoFree = IsAutoFree;m_NeedSort=false;pfStrToSize_T=NULL;}
  __fastcall ~AIndexList(){Clear();}
  void  Clear();
  //Add����˵��
  //Add����ֱ�����Ԫ�ص����һ��λ��,�����Key�ظ�,��Ӻ�ĵ�һ��������Ҫ��������
  //Add�����ʺϳ�ʼ����ʱ��ʹ��
  void  Add(size_t Key,T * lpData);
  //AddEx�����Ȳ���Keyֵ��Ӧ��Ԫ���Ƿ����,���������滻,����KeyΩһ��
  //��������,�����Ԫ�ص����Key����ĵط�,ʡȥһ��������
  //AddEx::����ʱ���ʼ�����̬�������ʱʹ��
  bool  AddEx(size_t Key,T * lpData);
  T *   Find(size_t Key);
  int   IndexOf(size_t Key);
  T *   At(int Index);
  bool  Delete(size_t Key);
  bool  DeleteByIndex(int index);
  __inline int    Count(){return m_IndexTable.size();}
  void  Sort(){sort(m_IndexTable.begin(), m_IndexTable.end(), DataCompare());m_NeedSort=false;}
  CSTR_TO_SIZE_T  pfStrToSize_T;
};
//------------------------------------------------------------------------------
template <class T> T *   AIndexList<T>::At(int Index)
{
	if (Index>=0 && Index < Count())
	{
	   return  m_IndexTable[Index].second;
	}
	return NULL;
}
//----------------------------------------------------------------------------
template <class T>  void  AIndexList<T>::Clear()
{
   for(int i=0;i<Count() ;i++)
   {
        if (m_IsAutoFree && m_IndexTable[i].second != NULL)
        {
               delete m_IndexTable[i].second;
        }
   }
   m_IndexTable.clear();
}

//----------------------------------------------------------------------------
template <class T>  void  AIndexList<T>::Add(size_t Key,T * lpData)
{
   m_IndexTable.push_back(make_pair(Key,lpData));
   m_NeedSort = true;
}

//----------------------------------------------------------------------------
template <class T>  bool  AIndexList<T>::AddEx(size_t Key,T * lpData)
{
    if (m_NeedSort) //��Ҫ����
    {
       Sort();
    }
    if (Count()==0)
    {
        m_IndexTable.push_back(make_pair(Key,lpData));
        return true;
    }
    IT_POS Pos =  lower_bound(m_IndexTable.begin(),m_IndexTable.end(),Key,DataCompare());   // �ڴ�ͨ��lower_bound���ң�
    if (Pos != m_IndexTable.end() && (Pos->first == Key)/*lower_bound������ʹֵ������Ҳ�᷵��ĳ������ָ��,ָ����ӽ���λ��*/)
    {
        //�Ѿ������Ԫ����
        return false;
    }
    //m_IndexTable.insert(Pos,make_pair(Key,lpData));
    if (Pos ==NULL)
    {
        m_IndexTable.push_back(make_pair(Key,lpData));
        return true;
    }
    int Index = Pos - m_IndexTable.begin();
    if (Index<0)
    {
      return false;
    }
    m_IndexTable.push_back(make_pair(Key,lpData));
    memmove(&m_IndexTable[Index+1],&m_IndexTable[Index],(Count()-Index-1)*sizeof(T_DATA_TYPE));
    m_IndexTable[Index].first  = Key;
    m_IndexTable[Index].second = lpData;
    return true;
}

//------------------------------------------------------------------------------
template <class T>   T *   AIndexList<T>::Find(size_t Key)
{
	if (m_NeedSort) //��Ҫ����
	{
	   Sort();
	}
	IT_POS Pos =  lower_bound(m_IndexTable.begin(),m_IndexTable.end(),Key,DataCompare());   // �ڴ�ͨ��lower_bound���ң�
	if (Pos != m_IndexTable.end() && (Pos->first == Key)/*lower_bound������ʹֵ������Ҳ�᷵��ĳ������ָ��,ָ����ӽ���λ��*/)
	{
		return Pos->second;
	}
	return NULL;
}

//------------------------------------------------------------------------------
template <class T>   int  AIndexList<T>::IndexOf(size_t Key)
{
    if (m_NeedSort) //��Ҫ����
    {
       Sort();
    }
    IT_POS Pos =  lower_bound(m_IndexTable.begin(),m_IndexTable.end(),Key,DataCompare());   // �ڴ�ͨ��lower_bound���ң�
    if (Pos != m_IndexTable.end() && (Pos->first == Key)/*lower_bound������ʹֵ������Ҳ�᷵��ĳ������ָ��,ָ����ӽ���λ��*/)
    {
        return Pos - m_IndexTable.begin();
    }
    return -1;
}
//---------------------------------------------------------------------------
template <class T> bool  AIndexList<T>::Delete(size_t Key)
{
    int Index = IndexOf(Key);
    return DeleteByIndex(Index);
}
template <class T> bool  AIndexList<T>::DeleteByIndex(int Index)
{
	if (Index >=0 && Index < Count())
	{
		IT_POS Pos = m_IndexTable.begin() + Index;
		if (m_IsAutoFree && Pos->second != NULL)
		{
			delete Pos->second;
		}
		m_IndexTable.erase(Pos);
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------
//AIndexListPro   AIndexList��ͨ�û���, �����vectorģ��map set����Ϊ,�ṩ����洢��log(n)�Ŀ��ٲ�������
//------------------------------------------------------------------------------
template <class KEYTYPE,class T>  class AIndexListPro
{
  typedef pair<KEYTYPE,T *> T_DATA_TYPE;
  typedef vector<T_DATA_TYPE>::iterator IT_POS;
  class DataCompare    //function obj
  {      // ���ڱȽϵ���
  public:
   bool operator()(const T_DATA_TYPE& lhs,   // ��������ıȽϺ���
	 const T_DATA_TYPE& rhs) const
   {
		return keyLess(lhs.first, rhs.first); // keyLess������
   }
  bool operator()(const T_DATA_TYPE& Ihs,   // ���ڲ��ҵıȽϺ���
	 const T_DATA_TYPE::first_type& k) const // ����ʽ1,����lower_bound��
   {
		return keyLess(Ihs.first,k);
   }
   bool operator()(const T_DATA_TYPE::first_type& k,  // ���ڲ��ҵıȽϺ���
	 const T_DATA_TYPE& rhs) const  // ����ʽ2,����equal_range��
   {
	return keyLess(k, rhs.first);
   } 

  private:
   bool keyLess(const T_DATA_TYPE::first_type& k1,  // ����ġ�
	 const T_DATA_TYPE::first_type& k2) const // �ȽϺ���
   {
		return (k1 < k2);
   }
  };
private:
   vector<T_DATA_TYPE> m_IndexTable;
   bool    m_IsAutoFree;
   T_DATA_TYPE   KeyValue;

protected:
   bool    m_NeedSort; //�Ƿ���Ҫ������ſ��Բ���
public:
  __fastcall AIndexListPro(bool IsAutoFree = TRUE){m_IsAutoFree = IsAutoFree;m_NeedSort=false;}
  __fastcall ~AIndexListPro(){Clear();}
  void  Clear();
  //Add����˵��
  //Add����ֱ�����Ԫ�ص����һ��λ��,�����Key�ظ�,��Ӻ�ĵ�һ��������Ҫ��������
  //Add�����ʺϳ�ʼ����ʱ��ʹ��
  void  Add(KEYTYPE Key,T * lpData);
  //AddEx�����Ȳ���Keyֵ��Ӧ��Ԫ���Ƿ����,���������滻,����KeyΩһ��
  //��������,�����Ԫ�ص����Key����ĵط�,ʡȥһ��������
  //AddEx::����ʱ���ʼ�����̬�������ʱʹ��
  bool  AddEx(KEYTYPE Key,T * lpData);
  T *   Find(KEYTYPE Key);
  int   IndexOf(KEYTYPE Key);
  T *   At(int Index);
  void  Delete(KEYTYPE Key);
  void	Delete(int Index);
  __inline int    Count(){return m_IndexTable.size();}
  void  Sort(){sort(m_IndexTable.begin(), m_IndexTable.end(), DataCompare());m_NeedSort=false;}
};

//----------------------------------------------------------------------------
template <class KEYTYPE,class T>  void  AIndexListPro<KEYTYPE,T>::Clear()
{
   for(int i=0;i<Count() ;i++)
   {
		if (m_IsAutoFree && m_IndexTable[i].second != NULL)
		{
			   delete m_IndexTable[i].second;
		}
   }
   m_IndexTable.clear();
}

//----------------------------------------------------------------------------
template <class KEYTYPE,class T>  void  AIndexListPro<KEYTYPE,T>::Add(KEYTYPE Key,T * lpData)
{
   m_IndexTable.push_back(make_pair(Key,lpData));
   m_NeedSort = true;
}
//----------------------------------------------------------------------------
template <class KEYTYPE,class T>  bool  AIndexListPro<KEYTYPE,T>::AddEx(KEYTYPE Key,T * lpData)
{
    if (m_NeedSort) //��Ҫ����
    {
       Sort();
    }
    if (Count()==0)
    {
        m_IndexTable.push_back(make_pair(Key,lpData));
        return true;
    }
    IT_POS Pos =  lower_bound(m_IndexTable.begin(),m_IndexTable.end(),Key,DataCompare());   // �ڴ�ͨ��lower_bound���ң�
    if (Pos != m_IndexTable.end() && (Pos->first == Key)/*lower_bound������ʹֵ������Ҳ�᷵��ĳ������ָ��,ָ����ӽ���λ��*/)
    {
		//�Ѿ������Ԫ����
		if(m_IsAutoFree)
		{
			//�Զ��ͷ�ֱ��ɾ��
			delete lpData;
        }
        return false;
    }

	if (Pos ==NULL)
	{
		m_IndexTable.push_back(make_pair(Key,lpData));
		return true;
	}
	m_IndexTable.insert(Pos,make_pair(Key,lpData));
	return true;
//	int Index = Pos - m_IndexTable.begin();
//	if (Index<0)
//	{
//	  return false;
//	}
//	m_IndexTable.push_back(make_pair(Key,lpData));
//	memmove(&m_IndexTable[Index+1],&m_IndexTable[Index],(Count()-Index-1)*sizeof(T_DATA_TYPE));
//	m_IndexTable[Index].first  = Key;
//	m_IndexTable[Index].second = lpData;
//	return true;
}
//------------------------------------------------------------------------------
template <class KEYTYPE,class T> T *   AIndexListPro<KEYTYPE,T>::At(int Index)
{
	if (Index>=0 && Index < Count())
	{
	   return  m_IndexTable[Index].second;
	}
	return NULL;
}
//------------------------------------------------------------------------------
template <class KEYTYPE,class T>  T *   AIndexListPro<KEYTYPE,T>::Find(KEYTYPE Key)
{
	if (m_NeedSort) //��Ҫ����
	{
	   Sort();
	}
	IT_POS Pos =  lower_bound(m_IndexTable.begin(),m_IndexTable.end(),Key,DataCompare());   // �ڴ�ͨ��lower_bound���ң�
	if (Pos != m_IndexTable.end() && (Pos->first == Key)/*lower_bound������ʹֵ������Ҳ�᷵��ĳ������ָ��,ָ����ӽ���λ��*/)
	{
		return Pos->second;
	}
	return NULL;
}
//------------------------------------------------------------------------------
template <class KEYTYPE,class T>  int  AIndexListPro<KEYTYPE,T>::IndexOf(KEYTYPE Key)
{
    if (m_NeedSort) //��Ҫ����
	{
       Sort();
    }
    IT_POS Pos =  lower_bound(m_IndexTable.begin(),m_IndexTable.end(),Key,DataCompare());   // �ڴ�ͨ��lower_bound���ң�
    if (Pos != m_IndexTable.end() && (Pos->first == Key)/*lower_bound������ʹֵ������Ҳ�᷵��ĳ������ָ��,ָ����ӽ���λ��*/)
    {
        return Pos - m_IndexTable.begin();
    }
    return -1;
}
//---------------------------------------------------------------------------
template <class KEYTYPE,class T> void  AIndexListPro<KEYTYPE,T>::Delete(KEYTYPE Key)
{
    int Index = IndexOf(Key);
    Delete(Index);
}
//----------------------------------------------------------------------------
template <class KEYTYPE,class T>  void  AIndexListPro<KEYTYPE,T>::Delete(int Index)
{
    if (Index >=0 && Index < Count())
    {
		if (m_IndexTable[Index].second && m_IsAutoFree)
		{
		  delete m_IndexTable[Index].second;
		  m_IndexTable[Index].second = NULL;
        }
//		if (Index<Count()-1)
//		{
//		  memcpy(&m_IndexTable[Index],&m_IndexTable[Index+1],(Count()-(Index+1))*sizeof(T_DATA_TYPE));
//		}
//		m_IndexTable.erase(m_IndexTable.end()-1);
		m_IndexTable.erase(m_IndexTable.begin()+Index);
	}
}
//---------------------------------------------------------------------------

#endif
