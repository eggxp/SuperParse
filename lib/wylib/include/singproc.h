//---------------------------------------------------------------------------

#ifndef singprocH
#define singprocH
#include <vcl.h>
//�������޶���
//---------------------------------------------------------------------------
class WYSingleProc
{
private:
   String Name;
protected:
	virtual bool MutexCheck(bool &IsExists);
	virtual bool FileCheck(bool &IsExists);
	virtual bool EventCheck(bool &IsExists);
public:
	WYSingleProc(String ObjName);
	~WYSingleProc();
	virtual bool Check(bool &IsExists);   //�������ʾ�Ѿ���ʵ������,
};
#endif
