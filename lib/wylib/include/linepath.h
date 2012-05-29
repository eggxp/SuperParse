//---------------------------------------------------------------------------

#ifndef linepathH
#define linepathH
#include <vcl.h>
#include "alist.h"
class  ALinePath
{
private:
  AList<TPoint> * WayPointList;
  int CurStepLong;
  int LineMoveStep;
protected:
  static VOID CALLBACK DirectProc(int X,int Y,LPARAM lpData);
public:
   ALinePath();
   ~ALinePath();
	//ֱ�ߴ���,StepLongΪÿ��֮��ļ������,����ֵΪ���ɵ�·������
   int Process(DWORD StartX,DWORD StartY,DWORD EndX,DWORD EndY,int StepLong=20);
   int Count(){return WayPointList->Count();} //�������ɵ�·������
   TPoint *  At(int Index){return WayPointList->At(Index);} //ȡһ��·��

};
//---------------------------------------------------------------------------
#endif
