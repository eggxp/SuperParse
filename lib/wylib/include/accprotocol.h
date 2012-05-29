//---------------------------------------------------------------------------
//ͨ��Э����,����ͻ��˺ͷ������˵�ͨ��Э��,���ݰ�����,���,У��ȹ���
//By LinYi 2004.02.16

#ifndef accprotocolH
#define accprotocolH
#include <Windows.hpp>
#include <dstring.h>
#include "md5.h"
#include "cryptclass.h"
enum TCmdType {acLOGIN=0,acCREATE_USER,acSAVEPOINT,acCMDBACK,acQUERYCARD};
#pragma pack(push, 1)
#define RSA_KEY_BUFFER_LEN      200
#define DATA_ENCRYPT_TYPE 1  //���ݼ����㷨 0=������,1=Des,2=Blowfish,3=BaseXorAdd,4=idea
#define MAX_USER_ID_LEN  31  //�û�id��󳤶�
#define LOGIN_SUCCEED    0   //��½�ɹ�
#define LOGIN_PASS_ERR   1  //�û������������
#define LOGIN_OVERTIME   3  //�û�ʹ�������ѹ�
#define LOGIN_QUERY_ERR  2 //��ѯ���ݿⷢ������
#define LOGIN_WAIT_UPDATE  5 //�ȴ��������


typedef struct tagMSGHEAD
{
  WORD DataSize;    //����ܴ�С
  WORD PackFlag;    //���У���־
  BYTE Cmd;         //������
  double RandKey;   //�����Կ
  char CmdMD5[36];  //��������MD5У��
}MSGHEAD,*PMSGHEAD;

typedef struct tagC_LOGIN_PACKET //�ӿͻ������ĵ�½��
{
   MSGHEAD PackHead;           //���ͷ
   BYTE    KeyLen;           //���ݽ���key����
   char    CryptKey[RSA_KEY_BUFFER_LEN];      //���ݽ���key����
   char    UserId[MAX_USER_ID_LEN];         //�û�Id
   char    UserPass[31];       //�û�����
   BYTE    ItemType;           //��Ϸ���
   DWORD   Reserve;            //����
}C_LOGIN_PACKET,*PC_LOGIN_PACKET;


typedef struct tagS_LOGIN_PACKET_HEAD //�ӷ������˷��صĵ�½��ͷ
{
   MSGHEAD PackHead;           //���ͷ
   BYTE    KeyLen;             //���ݽ���key����
   char    CryptKey[RSA_KEY_BUFFER_LEN];      //���ݽ���key����
   BYTE    ReturnCode;         //����ֵ
   char    UserId[MAX_USER_ID_LEN]; //�û�Id
   int     LogNum;             //��½����
   double  SP;                 //ʣ��洢��������ʱ��
   WORD    ExDataLen;          //��չ���ݳ���
   DWORD   Reserve1;           //����
   DWORD   Reserve2;           //����
}S_LOGIN_PACKET_HEAD,*PS_LOGIN_PACKET_HEAD;

typedef struct tagC_CREATE_USER_PACKET //�ӿͻ������Ľ����û����
{
   MSGHEAD PackHead;           //���ͷ
   char    UserId[MAX_USER_ID_LEN];         //�û�Id
   char    UserPass[31];       //�û�����
   char    EMail[61];          //�û�email
   BYTE    ItemType;           //���ͱ��
   DWORD   Reserve;            //����
}C_CREATE_USER_PACKET,*PC_CREATE_USER_PACKET;

typedef struct tagC_SAVE_POINT_PACKET //�ӿͻ������Ĵ�ֵ���
{
   MSGHEAD PackHead;           //���ͷ
   char    CardNo[31];         //����
   char    CardPass[31];       //����
   char    UserId[MAX_USER_ID_LEN];          //�û���
   char    UserPass[31];       //�û�����
   WORD    Cardtype;           //������
   BYTE    ItemType;           //���ͱ��
   DWORD   Reserve;            //����
   char    lgUserID[31];       //�����Ϳ���
}C_SAVE_POINT_PACKET,*PC_SAVE_POINT_PACKET;


typedef struct tagC_QUERY_CARD_PACKET    //�ӿͻ��˷��͵Ĳ�ѯ��ֵ���ķ��
{
   MSGHEAD PackHead;           //���ͷ
   char    CardNO[11];
   WORD    Cardtype;
   WORD    ItemType;
   DWORD   Reserve;
}C_QUERY_CARD_PACKET,*PC_QUERY_CARD_PACKET;

typedef struct tagS_QUERY_CARD_PACKET    //�ӷ������˷��͵Ĳ�ѯ��ֵ���ķ��
{
   MSGHEAD PackHead;           //���ͷ
   char    CardNO[11];
   BYTE    Remain;            //ʣ��ʹ�ô���
   double  SaveDate;        //ʹ��ʱ��
   BYTE    FullTimes; 		//��ʹ�ô���
   char    UserId[210];  //��ֵ��¼
}S_QUERY_CARD_PACKET,*PS_QUERY_CARD_PACKET;

typedef struct tagS_RETURN_PACKET //�ӷ������˷��ص�ͨ�ð�
{
   MSGHEAD PackHead;
   int     ReturnCode;
}S_RETURN_PACKET,*PS_RETURN_PACKET;

#pragma pack(pop)

#define  PACK_FLAG  0x6688
#define MSG_HEAD_SIZE                  sizeof(MSGHEAD)
#define C_LOGIN_PACKET_SIZE            sizeof(C_LOGIN_PACKET)
#define S_LOGIN_PACKET_HEAD_SIZE       sizeof(S_LOGIN_PACKET_HEAD)
#define C_CREATE_USER_PACKET_SIZE      sizeof(C_CREATE_USER_PACKET)
#define C_SAVE_POINT_PACKET_SIZE       sizeof(C_SAVE_POINT_PACKET)
#define S_RETURN_PACKET_SIZE           sizeof(S_RETURN_PACKET)

typedef struct tagS_LOGIN_PACKET //�ӷ������˷��صĵ�½��
{
   S_LOGIN_PACKET_HEAD Head;        //���ͷ
   String              ExData;
   String              ToString()  //����������
   {
       String DataBuffer;
       char * pBuf;
       int  DataPos=0;
       DataBuffer.SetLength(sizeof(Head)+ExData.Length());
       pBuf =  DataBuffer.c_str();
       CopyMemory(&pBuf[DataPos],(char *)&Head,sizeof(Head));
       DataPos+=sizeof(Head);
       if (ExData.Length()>0)
       {
         CopyMemory(&pBuf[DataPos],ExData.c_str(),ExData.Length());
         DataPos+=ExData.Length();
       }
       return DataBuffer;
   }
}S_LOGIN_PACKET,*PS_LOGIN_PACKET;

class CAccBase
{
  private:
	  double		   LastRandKey;

  protected:
    WY_RSA       m_Rsa; //rsa������ ,��������Key
    WY_CryptBase * m_lpCrypt; //���ݼ����� ,��������
    bool         m_IsEncryptPacket; //�Ƿ���ܷ������
    CMD5Checksum m_MD5;
    virtual double    GetRandKey();
    virtual bool IsValidityCmd(BYTE Cmd);      //У������Ϸ���
    virtual int DecryptPacket(char *buf,int len,double RandKey) ;
    virtual int EncryptPacket(char *buf,int len,double RandKey) ;
    virtual String   MakeKeyByID(String ID)=0; //���⺯��,�ͻ��˺ͷ������˸����û�id,���ɼ�������key
  public:
    __fastcall CAccBase();
    __fastcall ~CAccBase();
    virtual bool       ReadHead(char *buf,int len,MSGHEAD &Head);       //��ȡ���ͷ
    virtual bool       CheckPacket(char *buf,int len);   //У�����Ϸ���
    virtual void       SetPacketEncryptMode(bool Mode);   //���ü���ģʽ
    virtual bool       GetPacketEncryptMode();            //��ȡ����ģʽ
    virtual void       SetRSA_Key_EncryptKey(const String &Key){m_Rsa.SetKeyDataDecryptKey(Key);}
    virtual void       SetRSA_KeyData(const String &Key){m_Rsa.LoadEnKeyData(Key);}
	String     LastError;
	virtual double 			 GetLastRandKey(){return LastRandKey;}
};
#ifdef SERVER_CRYPT_SIDE
class CAccServerProtocol:public CAccBase //��������Э��
{
private:
   double LoginRandKey;
protected:
  virtual String   MakeKeyByID(String ID);
public:
  __fastcall CAccServerProtocol();
  virtual __fastcall ~CAccServerProtocol();
  bool       ReadLoginCmd(char *buf,int len,PC_LOGIN_PACKET LoginPacket);
  bool       ReadCreateUserCmd(char *buf,int len,PC_CREATE_USER_PACKET CreatePacket);
  bool       ReadSavePointCmd(char *buf,int len,PC_SAVE_POINT_PACKET SpPacket);
  bool       ReadQueryCardCmd(char *buf,int len,PC_QUERY_CARD_PACKET SpPacket);
  String     MakeLoginReturn(S_LOGIN_PACKET &ServerData);
  String     MakeLoginReturn_Old(S_LOGIN_PACKET &ServerData); //�ɰ�,���ñ���
  bool              MakeQueryReturn(S_QUERY_CARD_PACKET &ServerData);
  S_RETURN_PACKET    MakeCommBackCmd(int ReturnCode,BYTE CmdType);
  void       LoadPrivateKey(const String &PrivateKeyData){m_Rsa.LoadPrivateKey(PrivateKeyData);}
};
#endif
class CAccClientProtocol:public CAccBase //�ͻ�����Э��
{
private:

protected:
  virtual String   MakeKeyByID(String ID);
public:
  __fastcall CAccClientProtocol();
  virtual __fastcall ~CAccClientProtocol();
  virtual String  MakeLoginCmd(String UserId,String PassWord,BYTE ItemType,DWORD Reserve);
  virtual C_CREATE_USER_PACKET MakeCreateUserCmd(String UserId,String PassWord,String Email,BYTE GameType,DWORD Reserve);
  virtual C_SAVE_POINT_PACKET  MakeSavePointCmd(String CardNo,String CardPassWord,String UserId,String lgUserId,String PassWord,WORD CardType,BYTE GameType,int Reserve);
  virtual C_QUERY_CARD_PACKET  MakeQueryCardCmd(String CardNo,WORD CardType,BYTE GameType,int Reserve);
  virtual bool               ReadLoginBackCmd(char * buf,int len,PS_LOGIN_PACKET LoginCmd);
  virtual bool               ReadPackBackCmd(char *buf,int len,PS_RETURN_PACKET ReturnPack);
  virtual bool               ReadQueryCardCmd(char *buf,int len,PS_QUERY_CARD_PACKET ReturnPack);

};

DWORD DoubleValueCRC(double Crc);

//---------------------------------------------------------------------------
#endif
