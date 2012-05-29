//---------------------------------------------------------------------------
//�����������͵�2ά����ģ����  by bluely 2003.05
//�÷�����:
//typedef Array2D<int> IntArray;
//IntArray ia(640,480);  ����һ��640,480��int��ά����
//ע��,�����ڲ������˻����ڴ��memcpy���������Բ�֧�ָ�������ΪT,ֻ��֧��֧��memcpy�������������ͺ�struct

#ifndef array_2dH
#define array_2dH
template <class T>
class Array2D
{
  private:
   T **  m_lppBufMap;           //���ʵ�����ݵ�����ָ��
   int m_Width;               //����Ŀ��(����)
   int m_Height;              //����ĸ߶�(����)
   int m_Size;                  //����Ĵ�С
  public:
   __fastcall Array2D();
   __fastcall ~Array2D();
   __fastcall Array2D(int Width,int Heigth);
   __fastcall Array2D(int Width,int Heigth,void *Data);
   void Create(int Width,int Height);            //���ݿ�͸ߴ�������������
   void Create(int Width,int Height,void *Data); //�������ݻ�����������ά����
   void Free();                                 //��ղ����ͷ��ڴ�
   __inline int  Width(){return m_Width;}
   __inline int  Height(){return m_Height;}
   __inline int  Size(){return m_Size;}
   __inline int  BufferSize(){return   m_Size * sizeof(T);}   //�������е�����ʵ��ռ���ڴ��С
   void *        Data(); //��ȡ����ʵ�ʻ�����,���BufferSize()����ʹ��,���Եõ��������ͻ���������,ֱ�ӶԻ��������в���
   T * operator[](int i) {return m_lppBufMap[i];}
};
//---------------------------------------------------------------------------
template <class T>
__fastcall Array2D<T>::Array2D()
{
   m_lppBufMap = NULL;
   m_Width  = 0;
   m_Height = 0;
   m_Size = 0;
}
//---------------------------------------------------------------------------
template <class T>
__fastcall Array2D<T>::Array2D(int Width,int Heigth)
{
  m_lppBufMap = NULL;
  Create(Width,Heigth);
}
//---------------------------------------------------------------------------
template <class T>
__fastcall Array2D<T>::Array2D(int Width,int Heigth,void *Data)
{
  m_lppBufMap = NULL;
  Create(Width,Heigth,Data);
}
//---------------------------------------------------------------------------
template <class T>
__fastcall Array2D<T>::~Array2D()
{
  Free();
}
//---------------------------------------------------------------------------
template <class T>
void Array2D<T>::Create(int Width,int Height)
{
    Free();
    m_Width  = Width;
    m_Height = Height;
    m_Size   = m_Width * m_Height;
    m_lppBufMap = new T *[m_Width];    //�����һά
    m_lppBufMap[0] = new T[m_Size];  //����ڶ�ά
    ZeroMemory(m_lppBufMap[0], m_Size * sizeof(T));
    for(int i = 1; i < m_Width; i++)
    {
        m_lppBufMap[i] = m_lppBufMap[i - 1] + m_Height;
    }
}
//---------------------------------------------------------------------------
template <class T>
void Array2D<T>::Create(int Width,int Height,void *Data)
{
    Create(Width,Height);
    memcpy(m_lppBufMap[0],Data,m_Size * sizeof(T));
}


//---------------------------------------------------------------------------
template <class T>
void  Array2D<T>::Free()
{
   if (m_lppBufMap)
   {
     if (m_lppBufMap[0] != NULL)
     {
       delete [] m_lppBufMap[0];
     }
     delete []m_lppBufMap;
     m_lppBufMap = NULL;
   }
   m_Width  = 0;
   m_Height = 0;
   m_Size = 0;
}
//---------------------------------------------------------------------------
template <class T>
void *  Array2D<T>:: Data()
{
    if (m_Size <= 0)
    {
      return NULL;
    }
    return m_lppBufMap[0];
}
//---------------------------------------------------------------------------
#endif
