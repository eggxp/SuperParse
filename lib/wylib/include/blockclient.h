//---------------------------------------------------------------------------
/* By:Scodec [2007-6-21 9:59:54] */
// ��.h�ļ��� ���� SetTimeOut GetTimeOut��Ա����
#ifndef blockclientH
#define blockclientH
#include <vcl.h>
#include <winsock.h>

//�����ͻ���Socket
class CBlockSocket
{
private:
	WSADATA  wsaData;
	bool		 m_Connected;
	SOCKET		 m_SocketID;
	int			 RecvTimeOut;
protected:
	 void Init();
public:
	String		 LastError;
public:
	CBlockSocket();
	~CBlockSocket();
	bool Connect(String HostIP,WORD Port);
	int	 SendBuf(void * lpData,int Len);
	int	 RecvBuf(void * lpData,int Len);
	bool  IsActive(){return m_Connected;}
	void   Close();
    

    void SetTimeOut(int iTimeOut) {
        RecvTimeOut=iTimeOut;
    }/* By:Scodec [2007-6-21 9:59:54] */
    int GetTimeOut() {
        return RecvTimeOut;
    }/* By:Scodec [2007-6-21 9:59:56] */

};
//---------------------------------------------------------------------------
#endif
