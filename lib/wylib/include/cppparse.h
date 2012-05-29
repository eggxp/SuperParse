//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef cppparseH
#define cppparseH

//---------------------------------------------------------------------------
#include "AccToken.h"
class ICppToken :
    public IAccToken                                            // Pascalʽ�ʷ�������
{

protected:
    TStream     *is;                                            //�ű�Դ����������
    TStringList *KeyWord;                                       //�ؼ����б�
    char        OPWord[20];                                     //������,�������
    char        ch;
    int         getnc();                                        //��ȡһ���ֽڲ�����ָ������

public:
    int         Line;                                           //��ǰ�к�
    TStringList *SysIdent;                                      //ϵͳ������ʶ���б�
    TStringList *SysFunc;                                       //ϵͳ�����б�
    ICppToken();
    ~ICppToken();
    void    ReadBack();
    bool    IsOperator(char chr);                               //�Ƿ��ǲ�����,�����
    void Start(TStream *input)
    {
        is = input;
        ch = 0;
        Line = 1;
        Type = ENDL;
    }                                                           //��ʼ��

    int Read();                                                 //��ȡ������һ�����ʻ����
};

class ICppScript :
    public IParse                                               // ��Pascal�ű���������,��������������PascalԴ����
{

protected:
    ICppToken   Token;                                          //Pascalʽ�ʷ�������
    int         LABEL_ID;                                       //���ɵı��ID;
    int         ParseExpression(String ElseLabel, String EndIfLabel,
                                String MainIfLabel);            // ���ɷ������ʽ�Ĵ���
    int         ParseScript();                                  // ����ָ��
    int         ParseLine();                                    // ����ָ��
    int         ParseStatement();                               // һ��ָ��
    int         ParseProgram();                                 // һ���ű�����
    int         MakeGoto();                                     /* ������ת����	*/
    int         MakeIf();                                       /* �����жϲ��� */
    int         MakeWhile();                                    /* ѭ��ģ��ʵ�� */
    int         MakeValue();                                    //����ϵͳ��ʾ��
    int         MakeSysFunc();                                  //����ϵͳ����
    String      MakeExpress(String OperatorType);
    String      MakeNotExpress(String OperatorType);
    String      Express2KeyWord(String ExpStr);
    int         OptimizeCode();                                 //�Ż����ɵ�α����  δ���
    int         OptimizeLabel(String LabelStr);                 //δ���
    void        SplitStr(AnsiString SrcStr, AnsiString SplitChar,
                         TStringList *Str);
    String      GenLabelId();

public:
    ICppScript();
    ~ICppScript();
    TStrings    *OutPutList;                                    //�����������
    bool        IsSysFunc(String Opcode);
    bool        IsIdentWord(String Opcode);
    bool        IsDefaultSysFunc(String Opcode);                //�Ƿ���Ĭ�ϵ�ϵͳ����
    bool        IsDefaultIdent(String Opcode);                  //�Ƿ���Ĭ�ϵ�ϵͳ�ؼ���
    void        GetSysFuncList(TStrings *SysFuncList);          //��ȡϵͳ�����б�
    void        GetSysIdentWordList(TStrings *IndentWordList);  //��ȡϵͳ�ؼ����б�
    void        GetUserFuncList(TStrings *SysFuncList);         //��ȡ�û������б�
    void        GetUserIdentWordList(TStrings *IndentWordList); //��ȡ�û��ؼ����б�
    void        SetSysFunc(TStrings *SysFuncList);              //����ϵͳ�����б�
	void        SetIdentWord(TStrings *IdentWordList);          //����ϵͳ�ؼ���
	void        AddUserFunc(String FuncName);     //����һ���û��Զ��庯��
	void        AddUserIdentWord(String IdentWord); //����һ���û��Զ���ؼ���
    int         GoScript(TStream *Input, TStrings *OutPut);     //��ʼ����
    int ErrorPos()
    {
        return Token.ReadLen;
    }
};
#endif

