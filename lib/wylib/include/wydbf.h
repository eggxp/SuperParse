//---------------------------------------------------------------------------
//���ι�˾�Զ������ݸ�ʽ
//ʵ��һ���Զ����С�����ݿ�
//��ʼ�汾: 2005.10.25 by ��߮
//���ڴ��,�������ݶ�ȡ���ڴ浱��
//------------------------------------------------------------------------------
#ifndef wydbfH
#define wydbfH
#include <vcl.h>
#include "alist.h"
#define FLAG     0x5566  //�ļ�ͷ��־
#define VER_FLAG 0x1000  //�汾��Ϣ

#define MAX_FIELD_NAME_LEN 12           //�ֶ�����󳤶�
#define MAX_DBNAME_LEN 20 //��˵����󳤶�
#define FIELD_LEN    sizeof(WY_Field)   //�ֶνṹ����
enum FIELD_TYPE {ftBYTE = 0,ftWORD,ftDWORD,ftBUFFER,ftSTRING};
struct tagDB_Head
{
   WORD  Flag;
   WORD  VerFlag;
   char  DB_Name[MAX_DBNAME_LEN];
   DWORD FieldCount;
   DWORD RecordCount;
};

//�ֶ���
class WY_Field
{
   private:
   char   m_Name[MAX_FIELD_NAME_LEN];   //�ֶ���
   int    m_Type;    //�ֶ�����
   int    m_Length;   //�ֶγ���
   protected:

   public:
     WY_Field(){memset(m_Name,0,MAX_FIELD_NAME_LEN);m_Type=0;m_Length=0;}
     ~WY_Field(){;}
     void SetType(int Type);
     void SetName(String Name);
     void SetLength(int Length);   //�����ֶγ���,��ftBUFFER��ftSTRING���͵��ô˺�����Ч
     FIELD_TYPE  GetType(){return FIELD_TYPE(m_Type);}        //��ȡ�ֶ�����
     int         GetLength(){return m_Length;}      //��ȡ�ֶγ���
     String      GetName(){return String(m_Name);}        //��ȡ�ֶ�����
     int         WriteToBuffer(char * lpDesData); //�������ṹд�뻺����
     void        WriteToStream(TMemoryStream * Stream);
     int         ReadFromBuffer(char * lpDesData);
     int         GetSize(){return MAX_FIELD_NAME_LEN+sizeof(int)+sizeof(int);}  //��ȡField���͵�ʵ�ʴ�С
};



class WYDB_File
{
private:
   AList<WY_Field> * lpFieldList; //�ֶζ����б�
   TStringList *   lpDataRecord; //�����¼����
   TMemoryStream * lpDataStream; //�������ݵ�������
   int             IndexOfFieldName(String FieldName);
   int             GetFieldBufferStartPos(int FieldIndex);
protected:
   tagDB_Head Head;
   void  ReadDataToMem();     //�����ж�ȡ�ֶ���Ϣ��lpFieldList,lpDataRecord
   void  SaveMemToStream();     // ������д�ص�����
   int   GetRecordLength();     //
   bool  m_IsOpened; //����
   int   m_CurrentRecordNO;
public:
  String LastError;
public:
  __fastcall WYDB_File();
  __fastcall ~WYDB_File();
  bool __fastcall LoadFromFile(String FileName);
  bool __fastcall SaveToFile(String FileName);
  bool __fastcall LoadFromStream(TMemoryStream * DataStream);
  bool __fastcall SaveToStream(TMemoryStream * DataStream);
  int     GetFieldCount(){return lpFieldList->Count();}
  int     GetRecordCount(){return lpDataRecord->Count;}
  String  GetRecordAsString(String FieldName,int NO=-1);  //��ȡ��ǰ��¼ĳ���ֶε�����,��String��ʽ
  String  GetRecordAsString(int FieldIndex,int NO=-1);  //��ȡ��ǰ��¼ĳ���ֶε�����,��String��ʽ
  int     GetRecordAsInteger(String FieldName,int NO=-1); //��ȡ��ǰ��¼ĳ���ֶε�����,��int��ʽ
  int     GetRecordAsInteger(int FieldIndex,int NO=-1);
  int     GetRecordAsBuffer(String FieldName,char * lpOutBuffer,int NO=-1);  //����������ʽ��ȡ��ǰ��¼ĳ���ֶε�����
  int     GetRecordAsBuffer(int FieldIndex,char * lpOutBuffer,int NO=-1);
  bool    SetRecordAsString(String FieldName,String Data,int NO=-1);  //ˢ�µ�ǰ��¼ĳ���ֶε�����,��String��ʽ
  bool    SetRecordAsInteger(String FieldName,int Data,int NO=-1); //ˢ�µ�ǰ��¼ĳ���ֶε�����,��int��ʽ
  bool    SetRecordAsBuffer(String FieldName,char * lpInBuffer,int Len,int NO=-1);//ˢ��ĳ����¼�ֶΰ�buffer��ʽ
  void    SetRecordNO(int NO){m_CurrentRecordNO =NO;} //���õ�ǰ��¼��
  int     GetRecordNO(){return m_CurrentRecordNO;} // ��ȡ��ǰ��¼��
  bool    AddField(String Name,int Type,int Length); //���һ���ֶ�
  String  GetDBName(){return Head.DB_Name;}
  void    SetDBName(String DBName);
  WY_Field * GetField(int Index){return lpFieldList->At(Index);}
  void    Close(){lpDataStream->Clear();lpFieldList->Clear();lpDataRecord->Clear();memset(&Head,0,sizeof(Head));}
  bool    IsOpen(){return m_IsOpened;}
  void    Append();   //���һ���ռ�¼
  void    Last(); //�������һ����¼
  void    Next(); //������һ����¼
  void    Prev(); //������һ����¼
  void    First(); //������һ����¼
};

//---------------------------------------------------------------------------
#endif
