#ifndef AccTokenH
#define AccTokenH

//---------------------------------------------------------------------------
#include <Classes.hpp>
class   IAccToken                                           // ��׼�ʷ�������(��ʽ)
{

public:
    int     Type;                                           //��������
    long    Value;                                          //ֵ,������ֵ��Ч
    int     ReadLen;
    String  Text;                                           //����

public:
    enum
    {
        ENDF    = 0,
        ENDL    = 1,
        KEYWORD = 2,
        IDENT   = 3,
        INTEGER = 4,
        FLOAT   = 5,
        OPERATOR= 6,
        STRING  = 7,
        IERROR  = 8,
        SYSFUNC = 9
    };
    virtual int Read() = 0;
};

class   IParse
{

protected:
    TStream *is;

public:
    TStrings    *OutPutList;                                //�����������
    String      BeginLabel, EndLabel;
    enum { scrPROGEND = 0, scrLINEEND = 1, scrMODEND = 2, scrERROR = 4 };
    String ErrorInfo;

public:
    IParse()
    {
        is = NULL;
        OutPutList = NULL;
    }

    virtual~IParse()
    { ;
    }

    virtual bool    IsSysFunc(String Opcode) = 0;
    virtual bool    IsIdentWord(String Opcode) = 0;
    virtual bool    IsDefaultSysFunc(String Opcode) = 0;    //�Ƿ���Ĭ�ϵ�ϵͳ����
    virtual bool    IsDefaultIdent(String Opcode) = 0;      //�Ƿ���Ĭ�ϵ�ϵͳ�ؼ���
    virtual void    GetSysFuncList(TStrings *SysFuncList) = 0;          //��ȡϵͳ�����б�
    virtual void    GetSysIdentWordList(TStrings *IndentWordList) = 0;  //��ȡϵͳ�ؼ����б�
    virtual void    GetUserFuncList(TStrings *SysFuncList) = 0;         //��ȡ�û������б�
    virtual void    GetUserIdentWordList(TStrings *IndentWordList) = 0; //��ȡ�û��ؼ����б�
    virtual void    SetSysFunc(TStrings *SysFuncList) = 0;              //����ϵͳ�����б�
    virtual void    SetIdentWord(TStrings *IdentWordList) = 0;          //����ϵͳ�ؼ���
    virtual int     GoScript(TStream *Input, TStrings *OutPut) = 0;     //��ʼ����
    virtual int     ErrorPos() = 0;
};
#endif
