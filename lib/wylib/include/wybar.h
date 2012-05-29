//---------------------------------------------------------------------------

#ifndef wybarH
#define wybarH
#include <vcl.h>
enum TextShowStyle{tssVALUE,tssPERCENT,tssBOTH,tssNONE};
//�ı����,��ֵ,�ٷֱ�,����һ����ʾ,���߶�����ʾ
class WYDrawBar
{
private:
  TPaintBox * OwnPaintBox;
protected:
   int	Min;
   int  Max;
   int  Position;
   TColor  m_TextColor;//�ı���ɫ
   TColor  m_BarColor; //��������ɫ
   TColor  m_BGColor;  //����ɫ
   TColor  m_FrameLineColor;//������ɫ
   bool    m_ShowFrameLine; //�Ƿ���ʾ����
   TextShowStyle  m_TextStyle;
   String	CurTextHead;
   void Refresh();
   void __fastcall OnPaint(System::TObject* Sender);
   void SetMin(int Value);
   void Init();
public:
   WYDrawBar(TPaintBox * PaintBox);
   WYDrawBar();
   ~WYDrawBar();
   void Bind(TPaintBox * PaintBox);
   void SetMax(int Value);
   void SetPosition(int Value,String NewText=" ");
   void SetTextColor(TColor TextColor);//�ı���ɫ
   void SetBarColor(TColor  BarColor); //��������ɫ
   void SetFrameLineColor(TColor  FrameLineColor);//������ɫ
   void SetShowFrameLine(bool    ShowFrameLine); //�Ƿ���ʾ����
   void SetBGColor(TColor    BGColor);     //����������ɫ
   void SetTextStyle(TextShowStyle  TextStyle);  //�ı���ʾ��ʽ

};
//---------------------------------------------------------------------------
#endif
