//---------------------------------------------------------------------------
//���μ��ܿ��װ
//------------------------------------------------------------------------------
#ifndef cryptclassH
#define cryptclassH

#include <vcl.h>
#include "CryptoLib.h"
//------------------------------------------------------------------------------
//ע��!!!!!!!!!!!!!!!
//SERVER_CRYPT_SIDE    //�˺���Ч,��ʾ�������˱���,���κ��ʾ�ͻ���(����ȥ�����й���˽Կ�Ĵ���)
//�����趨��project��option,��Ŀ����ѡ��
//------------------------------------------------------------------------------
#define MAX_TEMP_OUTPUT_BUFFER_LEN 1024 * 32

struct tagPublicKeyData //KeyData����ṹ
{
   int EncryptType;
   R_RSA_PUBLIC_KEY  PublicKey;
   R_RANDOM_STRUCT   RandomStruct;
};

//���ּ��ܽ����㷨�Ļ���,RSA����
class WY_CryptBase
{
private:
  char DesBuf[MAX_TEMP_OUTPUT_BUFFER_LEN];
protected:

public:
  __fastcall WY_CryptBase();
  virtual __fastcall ~WY_CryptBase();
  virtual void Init(String Key)=0;
  virtual int  EncryptBuf(char *SrcBuf,int SrcLen,char *DesBuf)=0;  //����һ���ڴ�����,���⺯��
  virtual int  DecryptBuf(char *SrcBuf,int SrcLen,char *DesBuf)=0;  //����һ���ڴ�����,���⺯��
  virtual void EncryptStream(TMemoryStream *SrcStream,TMemoryStream *DesStream);
  virtual void DecryptStream(TMemoryStream *SrcStream,TMemoryStream *DesStream);
  virtual String EncryptStr(const String &Buf);
  virtual String DecryptStr(const String &Buf);
};

//��װRSA�㷨
//ʹ�ù���:
//һ. RSA Key����
//1.ʹ�� MakeKey ��Ա����, ���ɹ�Կ��˽Կ����,������m_KeyData
//2.ʹ�� SaveKeyData ��Ա����,���湫Կ����,���ü����㷨���ܣ���base16������ַ���,�ַ����ͻ���
//3.ʹ�� SavePrivateKey ��Ա����,����˽Կ����,��base16������ַ���,�ַ�����������
//��. �ͻ���ʹ�ù���
//1. ����SetKeyDataDecryptKey���� ����publickey�����㷨��Ҫ��Key(�Զ���)
//2.����LoadEnKeyData���� ���ܺ��publickey����
//3.����PublicEncrypt�������Խ��й�Կ����,�������ܷ��͸��������˵�����
//4.����PublicDecrypt�������Խ��й�Կ����,�������ܴӷ������˽��յ�����

//��.��������ʹ�ù���
//1. ���� LoadPrivateKey��ȡ˽��Key
//2. ���� PrivateEncrypt�������ݣ����͸��ͻ���
//3. ���� PrivateDecrypt,���ܿͻ��˷���������
class WY_RSA
{
private:
   tagPublicKeyData m_KeyData;
   #ifdef SERVER_CRYPT_SIDE
   R_RSA_PRIVATE_KEY m_PrivateKey;    //˽��Key���Ᵽ��
   #endif
   String        EnKeyDataStr; //����״̬��KeyData����
   String        KeyDataDecryptKey;
protected:
  virtual void GetTruePublicKey(R_RSA_PUBLIC_KEY  * PublicKey);
  virtual void GetTruePrivateKey(R_RSA_PRIVATE_KEY  * PrivateKey);
  virtual void GetTrueRandomStruct(R_RANDOM_STRUCT  * RandomStruct);
  virtual DWORD  GetDataBlockLen(R_RSA_PRIVATE_KEY  * PrivateKey);
  virtual DWORD  GetDataBlockLen(R_RSA_PUBLIC_KEY  * PubliceKey);
public:
  __fastcall WY_RSA();
  __fastcall ~WY_RSA();
  virtual void __fastcall MakeKey(int Bit,DWORD RandValue1,DWORD RandValue2);
  virtual String __fastcall PublicEncrypt(const String &Data); //��Կ����
  virtual String __fastcall PublicDecrypt(const String &Data); //��Կ����
  virtual String __fastcall PrivateEncrypt(const String &Data);  //˽Կ����
  virtual String __fastcall PrivateDecrypt(const String &Data);  //˽Կ����
  virtual void __fastcall   SetKeyDataDecryptKey(const String &Key){KeyDataDecryptKey = Key;} //�趨���ܻ�ԭRSA Key���ݵ���Կ
  virtual void __fastcall   LoadEnKeyData(const String &Data){EnKeyDataStr=Data;} //��ȡ����key����,�����ܺ�״̬����
  virtual void   __fastcall LoadPublicKeyData(const String &Data,const String &EncryptKey,tagPublicKeyData * lpOutKeyData); //�Ӽ���״̬��String��ȡKey����
  virtual String __fastcall SavePublicKeyData(int EncryptType,const String &EncryptKey); //����Key���ݵ�String 0=������,1=Des,2=Blowfish,3=BaseXorAdd,4=idea
  virtual String __fastcall SavePrivateKey(); //����˽��key
  virtual void   __fastcall LoadPrivateKey(const String &PrivateKeyData); //��ȡ˽��Key
};


//��װDes�㷨����
class WY_Des:public  WY_CryptBase
{
private:
   DES_CBC_CTX Context;
protected:
  String m_Key;
public:
  __fastcall WY_Des(){memset(&Context,0,sizeof(DES_CBC_CTX));}
  __fastcall ~WY_Des(){;}
  virtual void Init(String Key);
  virtual int  EncryptBuf(char *SrcBuf,int SrcLen,char *DesBuf);  //����һ���ڴ�����,���⺯��
  virtual int  DecryptBuf(char *SrcBuf,int SrcLen,char *DesBuf);
};
//��װBlowFish�㷨����
class WY_BlowFish:public  WY_CryptBase
{
private:
   BLOWFISH_CTX *ctx;

protected:

public:
  __fastcall WY_BlowFish();
  __fastcall ~WY_BlowFish();
  virtual void Init(String Key);
  virtual int  EncryptBuf(char *SrcBuf,int SrcLen,char *DesBuf);  //����һ���ڴ�����,���⺯��
  virtual int  DecryptBuf(char *SrcBuf,int SrcLen,char *DesBuf);
};

//��װIdea�㷨����
class WY_Idea:public  WY_CryptBase
{
private:
   String m_Key;
protected:

public:
  __fastcall WY_Idea(){;}
  __fastcall ~WY_Idea(){;}
  virtual void Init(String Key);
  virtual int  EncryptBuf(char *SrcBuf,int SrcLen,char *DesBuf);  //����һ���ڴ�����,���⺯��
  virtual int  DecryptBuf(char *SrcBuf,int SrcLen,char *DesBuf);

};
//��װxoradd�㷨����
class WY_Xor:public  WY_CryptBase
{
private:

protected:
  String m_Key;
public:
  __fastcall WY_Xor(){;}
  __fastcall ~WY_Xor(){;}
  virtual void Init(String Key);
  virtual int  EncryptBuf(char *SrcBuf,int SrcLen,char *DesBuf);  //����һ���ڴ�����,���⺯��
  virtual int  DecryptBuf(char *SrcBuf,int SrcLen,char *DesBuf);
};

WY_CryptBase * NewCryptClass(int Type);
//---------------------------------------------------------------------------
#endif
