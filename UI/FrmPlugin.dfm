object PluginFrm: TPluginFrm
  Left = 0
  Top = 0
  Caption = #25554#20214#31649#29702'(result'#26368#22823#38271#24230#20026'500)'
  ClientHeight = 388
  ClientWidth = 549
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 549
    Height = 342
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = #25554#20214
      object Splitter1: TSplitter
        Left = 0
        Top = 161
        Width = 541
        Height = 3
        Cursor = crVSplit
        Align = alTop
        ExplicitWidth = 153
      end
      object lvPlugins: TListView
        Left = 0
        Top = 0
        Width = 541
        Height = 161
        Align = alTop
        Columns = <
          item
            Caption = #21517#31216
            Width = 200
          end
          item
            Caption = #29256#26412
          end
          item
            Caption = #25551#36848
            Width = 250
          end>
        OwnerData = True
        ReadOnly = True
        RowSelect = True
        PopupMenu = PopupMenu1
        TabOrder = 0
        ViewStyle = vsReport
        OnClick = lvPluginsClick
        OnData = lvPluginsData
      end
      object memInfo: TMemo
        Left = 0
        Top = 164
        Width = 541
        Height = 150
        Align = alClient
        Color = clInfoBk
        Ctl3D = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGreen
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 1
      end
    end
    object TabSheet2: TTabSheet
      Caption = #31867
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 541
        Height = 314
        Align = alClient
        Lines.Strings = (
          
            '//--------------------------------------------------------------' +
            '-------------'
          '#ifndef PlugInterfaceH'
          '#define PlugInterfaceH'
          
            '//--------------------------------------------------------------' +
            '-------------'
          ''
          '#define'#9'MAX_RESULT_LEN'#9#9#9#9'500'
          ''
          '#ifdef EXPORT_API'
          #9'#define VCIN_API extern "C" __declspec(dllexport)'
          '#else'
          #9'#define VCIN_API __declspec(dllimport)'
          '#endif'
          
            '//--------------------------------------------------------------' +
            '-------------'
          '#include <windows.h>'
          
            '//--------------------------------------------------------------' +
            '-------------'
          'struct'#9'tagTypeInfo'
          '{'
          #9'int version;'#9#9#9#9'// module type (IN_VER)'
          
            #9'char description[MAX_RESULT_LEN];'#9#9#9'// description of module, w' +
            'ith version '
          'string'#10#13#10#10
          ''
          ''
          
            #9'bool'#9'(*OnParse)(char *lpData, int Len, int &pos, char * result)' +
            ';'#10
          #9'char '#9'*(*GetVarName)();'#10
          #9'int '#9'(*GetSize)();'
          #9'tagTypeInfo()'
          #9'{'
          #9#9'version = 0;'
          #9#9'memset(description, '#39'\0'#39', MAX_RESULT_LEN);'
          #9'}'
          '};'
          ''
          'VCIN_API VOID WINAPI exeGetTypeInfo(tagTypeInfo *typeInfo);'
          'typedef VOID WINAPI (*getTypeInfo)(tagTypeInfo *typeInfo);'
          ''
          ''
          '#endif')
        TabOrder = 0
      end
    end
  end
  object edtPluginPath: TEdit
    Left = 0
    Top = 342
    Width = 549
    Height = 21
    Align = alBottom
    TabOrder = 1
    Text = 'edtPluginPath'
  end
  object btOk: TButton
    Left = 0
    Top = 363
    Width = 549
    Height = 25
    Align = alBottom
    Caption = #30830#23450
    TabOrder = 2
    OnClick = btOkClick
  end
  object PopupMenu1: TPopupMenu
    Left = 352
    Top = 120
    object nWatchHead: TMenuItem
      Caption = #26597#30475#22836
    end
  end
end
