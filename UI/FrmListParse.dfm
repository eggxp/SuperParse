object ListParseFrm: TListParseFrm
  Left = 0
  Top = 0
  Caption = #25968#25454#35299#26512
  ClientHeight = 561
  ClientWidth = 671
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  WindowState = wsMaximized
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 49
    Width = 671
    Height = 3
    Cursor = crVSplit
    Align = alTop
    ExplicitTop = 81
    ExplicitWidth = 175
  end
  object Splitter2: TSplitter
    Left = 0
    Top = 469
    Width = 671
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitTop = 353
    ExplicitWidth = 119
  end
  object DBGrid1: TDBGrid
    Left = 0
    Top = 472
    Width = 671
    Height = 89
    Align = alBottom
    DataSource = DataSource1
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 671
    Height = 49
    Align = alTop
    TabOrder = 1
    object Label1: TLabel
      Left = 8
      Top = 8
      Width = 122
      Height = 13
      Caption = #35299#26512#26465#25968'(0'#34920#31034#25152#26377')'#65306
    end
    object cgProcess: TCGauge
      Left = 1
      Top = 32
      Width = 669
      Height = 16
      Align = alBottom
      ExplicitTop = 224
    end
    object edtParseCount: TCSpinEdit
      Left = 136
      Top = 5
      Width = 121
      Height = 22
      TabOrder = 0
    end
    object btStart: TButton
      Left = 391
      Top = 3
      Width = 75
      Height = 25
      Caption = #24320#22987
      TabOrder = 1
      OnClick = btStartClick
    end
    object btOutputFile: TButton
      Left = 472
      Top = 3
      Width = 75
      Height = 25
      Caption = #29983#25104#25991#20214
      TabOrder = 2
      OnClick = btOutputFileClick
    end
    object btOutput: TButton
      Left = 553
      Top = 3
      Width = 75
      Height = 25
      Caption = #23548#20986
      TabOrder = 3
      OnClick = btOutputClick
    end
  end
  object lvParseData: TListView
    Left = 0
    Top = 52
    Width = 671
    Height = 417
    Align = alClient
    Columns = <>
    GridLines = True
    OwnerData = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 2
    ViewStyle = vsReport
    OnData = lvParseDataData
  end
  object cdsData: TClientDataSet
    Aggregates = <>
    Params = <>
    Left = 8
    Top = 336
  end
  object DataSource1: TDataSource
    DataSet = cdsData
    Left = 216
    Top = 344
  end
  object SaveDialog1: TSaveDialog
    Filter = 'xml|*.xml'
    Left = 520
    Top = 104
  end
end
