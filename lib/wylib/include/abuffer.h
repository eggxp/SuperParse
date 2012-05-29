//---------------------------------------------------------------------------

#ifndef abufferH
#define abufferH
#include <vcl.h>
//TSmartBuffer��װ��һ����̬����������,���԰����Ͷ�ȡ��д������,�������ݿ�������
class TSmartBuffer
{
private:
   String m_Data;
   int    m_NewSize; //ÿ�λ�����������ʱ�����·���Ĵ�С
protected:
   int CurPos;
public:
  __fastcall TSmartBuffer(int DefauleBufSize=64);
  __fastcall ~TSmartBuffer();
   void SetPos(int NewPos);
   int  GetPos(){return CurPos;};
   void SetSize(int NewSize);  //���Ĵ�С�ᵼ��ԭ�������ݶ�ʧ
   void AppendSize(int NewSize);   //���Ӵ�С,���ᵼ�����ݶ�ʧ
   int  GetSize(){return m_Data.Length();};
   int  __fastcall Read(void * lpData,int Count);
   int  __fastcall Write(void * lpData,int Count);
   BYTE ReadBYTE();
   WORD ReadWORD();
   DWORD ReadDWORD();
   float  ReadFloat();
   double ReadDouble();
   String ReadCStr();  //��ȡc�����ַ���
   String ReadAnsiStr(); //��ȡpascal�����ַ���   DWORD Len,char *Str
   String ReadSmallAnsiStr(); //��ȡСpascal�����ַ���,BYTE Len,char *Str
   WideString  ReadWideCStr(); //��ȡc����˫�ֽ��ַ���
   WideString  ReadWideString(); //��ȡpascal����˫�ֽ��ַ���
   int  WriteBYTE(BYTE Value);
   int  WriteDWORD(DWORD Value);
   int  WriteWORD(WORD Value);
   int  WriteFloat(float Value);
   int  WriteDouble(double Value);
   int  WriteCStr(String &Str);  //��c�����ַ��� д��
   int  WriteAnsiStr(String &Str); //pascal�����ַ���д��
   int  WriteSmallAnsiStr(String &Str); //��Сpascal�����ַ���,BYTE Len,char *Str
   int  WriteWideCStr(WideString &Value); //c����˫�ֽ��ַ���д��
   int  WriteWideString(WideString &Value); //pascal����˫�ֽ��ַ���д��
   const void * Data(){return m_Data.data();}
   char * c_str(){return m_Data.c_str();}
   void Clear();
   void SaveToFile(String FileName);
   bool LoadFromFile(String FileName);
   bool LoadFromStream(TStream *Stream);
   void LoadFromString(const String &Data);
};

//---------------------------------------------------------------------------
#endif
