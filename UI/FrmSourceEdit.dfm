object SourceEditFrm: TSourceEditFrm
  Left = 0
  Top = 0
  Caption = 'SourceEditFrm'
  ClientHeight = 622
  ClientWidth = 641
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object panControl: TPanel
    Left = 0
    Top = 568
    Width = 641
    Height = 54
    Align = alBottom
    TabOrder = 0
    object btOk: TButton
      Left = 1
      Top = 1
      Width = 184
      Height = 52
      Align = alLeft
      Caption = #30830#23450'('#24555#25463#38190':Ctrl+Enter)'
      ModalResult = 1
      TabOrder = 0
    end
    object btCancel: TButton
      Left = 565
      Top = 1
      Width = 75
      Height = 52
      Align = alRight
      Caption = #21462#28040
      ModalResult = 2
      TabOrder = 1
    end
    object Memo1: TMemo
      Left = 185
      Top = 1
      Width = 380
      Height = 52
      Align = alClient
      Lines.Strings = (
        'i_(I_)'#20026#21629#21517#34920#31034#26159#25968#25454#24211#23384#20648#36807#31243#30340#36755#20837
        '_KEY_  '#20026#21629#21517#34920#31034#36825#20010#25968#25454#26159#25968#25454#24211#30340'key')
      TabOrder = 2
    end
  end
  object memSrcFile: TMemo
    Left = 0
    Top = 41
    Width = 641
    Height = 527
    Align = alClient
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 1
    WantTabs = True
    OnKeyDown = memSrcFileKeyDown
  end
  object pcSourceMod: TTabControl
    Left = 0
    Top = 0
    Width = 641
    Height = 41
    Align = alTop
    MultiLine = True
    TabOrder = 2
    Tabs.Strings = (
      #20266#20195#30721
      'ReadData'
      'WriteBuffer'
      'DataInterface'
      'ReadWriteAll'
      'ADOStore'
      'gADOCreate'
      #23384#20648#36807#31243'Load'
      #23384#20648#36807#31243'Save'
      #23384#20648#36807#31243'Insert'
      #23384#20648#36807#31243'QueryAll')
    TabIndex = 0
    OnChange = pcSourceModChange
  end
end
