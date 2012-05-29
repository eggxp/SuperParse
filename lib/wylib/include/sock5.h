//---------------------------------------------------------------------------
/*���ʺϷ�ͬ�����ӵ�sock5������������ӷ�װ��
����: Bluely
����:2003.09.27
˵��: ��ѭ RFC 1982 ��׼,Ŀǰֻʵ��sock5Э�����,UDPģʽ��û�в��Թ�.
/*
����: smNEGOTIATION   Э�̰汾�ͷ���
�ͻ���������������Ȼ��ͷ���������Э�̰汾����֤������

VER        �汾: 0x5 (sock5)
NMETHODS   NMETHODS�ֶΰ�������METHODS�ֶ��г��ֵķ�����ʾ����Ŀ�����ֽ�Ϊ��λ����
METHODS    ����:	0x00		����Ҫ��֤
                  	0x01   		GSSAPI
                  	0x02   		�û���/����
                  	0x03 -- 0x7F  	��IANA����
                  	0x80 -- 0xFE 	Ϊ˽�˷�����������
                  	0xFF   	 	û�п��Խ��ܵķ���

����������:
����������Щ�����ķ�����ѡ��һ��������һ������ѡ�е���Ϣ�ؿͻ��ˣ�
VER       �汾: 0x5 (sock5)
METHOD    Ӧ����SEND ��METHODS,���Ϊ0xFF��ʾû�п��Խ��ܵķ���

����: emAUTHENTICATION  У���û�
VER           version of subnegotiation
USERNAME LEN  �û�������
USERNAME      �û���
PassWord Len  ���볤��
PASSWORD      ����

����������:

0x0��ʾ��֤�ɹ�,����Ϊʧ��

����:smCONNECTION         ���ʹ���������Ϣ
SockVER        // socks version
ConnectMethod  // connect method
Reserved       // reserved
AddrType        //address type:   IP V4 address: X'01',
                                  DOMAINNAME:    X'03'
                                  IP V6 address: X'04'
HOSTNAME_LEN   //Ŀ������������
HOSTNAME       //Ŀ��������
PORT           //Ŀ�������˿�



*/
#ifndef sock5H
#define sock5H
#include <Classes.hpp>
enum TSockStepMode {smNEGOTIATION=0,smAUTHENTICATION,smCONNECTION,smFINISH};
enum TAuthenticationMode {amNoAuthentication,amUsernamePassword};
class TSockProxyClient
{
private:
   String mUserName;
   String mPassWord;
   DWORD  mHostIP;
   WORD   mPort;
   TSockStepMode mCurrentStep;
   int    mLastError;
private:
   String DoNegotiation();    //����Э�̲���
   String DoAuthentication(); //������֤����
   String DoConnection();     //�������Ӳ���
   bool RecvNegotiation(LPBYTE buf,int Len);    //����Э�̲��践�ط��
   bool RecvAuthentication(LPBYTE buf,int Len); //������֤���践�ط��
   bool RecvConnection(LPBYTE buf,int Len);     //�������Ӳ��践�ط��

public:
   TAuthenticationMode AuthenticationMode;
public:
  __fastcall TSockProxyClient();
  __fastcall ~TSockProxyClient();
  void       SetHostInfo(const String &Host,WORD Port); //����Ŀ���������Ϣ(���Ǵ����������ַ)
  void       SetUserInfo(const String &UserName,const String &PassWord);   //�����û���������
  String     ProcessNext();         //������һ��
  bool       ProcessRecvData(LPBYTE buf,int Len); //���������������Ϣ
  int        GetCurrentStep();  //��ȡ��ǰ�ʹ����������ͨ����ɲ���
  String     GetCurrentStepInfo();   //��ȡ��ǰ�ʹ����������ͨ����ɲ�������
  bool       IsFinish(); //�Ƿ��Ѿ�ȫ����֤���
  int        GetLastError();
  String     GetLastErrorStr();
  void       Reset();

};

//---------------------------------------------------------------------------
#endif
