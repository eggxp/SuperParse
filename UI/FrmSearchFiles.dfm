object SearchFilesFrm: TSearchFilesFrm
  Left = 0
  Top = 0
  Caption = #36229#32423#26597#25214#22120
  ClientHeight = 373
  ClientWidth = 306
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
  object cgProcess: TCGauge
    Left = 0
    Top = 211
    Width = 306
    Height = 19
    Align = alTop
    ForeColor = clYellow
    ExplicitLeft = 11
    ExplicitTop = 217
    ExplicitWidth = 221
  end
  object lvResult: TListView
    Left = 0
    Top = 230
    Width = 306
    Height = 143
    Align = alClient
    Columns = <
      item
        Width = 800
      end>
    GridLines = True
    HideSelection = False
    OwnerData = True
    ReadOnly = True
    RowSelect = True
    PopupMenu = PopupMenu1
    TabOrder = 0
    ViewStyle = vsReport
    OnData = lvResultData
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 306
    Height = 211
    Align = alTop
    TabOrder = 1
    object Label1: TLabel
      Left = 11
      Top = 16
      Width = 100
      Height = 13
      Caption = #36755#20837#35201#26597#25214#30340#20869#23481':'
    end
    object Label2: TLabel
      Left = 11
      Top = 85
      Width = 115
      Height = 13
      Caption = #36755#20837#35201#26597#25214#30340#25991#20214#22841' :'
    end
    object Label3: TLabel
      Left = 11
      Top = 161
      Width = 84
      Height = 13
      Caption = #36755#20837#25991#20214#25193#23637#21517
    end
    object edtSearchContent: TEdit
      Left = 29
      Top = 35
      Width = 203
      Height = 21
      TabOrder = 0
    end
    object cbSearchMode: TComboBox
      Left = 29
      Top = 62
      Width = 206
      Height = 21
      Style = csDropDownList
      ItemIndex = 0
      TabOrder = 1
      Text = #25628#32034'16'#36827#21046#23383#31526#20018
      Items.Strings = (
        #25628#32034'16'#36827#21046#23383#31526#20018
        #25628#32034'bin'
        #25628#32034'DWORD'
        #25628#32034'WORD'
        #25628#32034'BYTE')
    end
    object edtSearchPath: TEdit
      Left = 29
      Top = 104
      Width = 165
      Height = 21
      TabOrder = 2
    end
    object btSelectSearchPath: TButton
      Left = 200
      Top = 105
      Width = 32
      Height = 20
      Caption = #36873#25321
      TabOrder = 3
      OnClick = btSelectSearchPathClick
    end
    object cbInclude: TCheckBox
      Left = 29
      Top = 135
      Width = 113
      Height = 17
      Caption = #21253#21547#23376#25991#20214#22841
      TabOrder = 4
    end
    object btBeginSearch: TButton
      Left = 29
      Top = 184
      Width = 75
      Height = 25
      Caption = #24320#22987#25628#32034
      TabOrder = 5
      OnClick = btBeginSearchClick
    end
    object edtFileExt: TEdit
      Left = 117
      Top = 158
      Width = 77
      Height = 21
      TabOrder = 6
      Text = '*.*'
    end
    object btResearch: TButton
      Left = 152
      Top = 184
      Width = 80
      Height = 25
      Caption = #22312#32467#26524#20013#25628#32034
      TabOrder = 7
      OnClick = btResearchClick
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 240
    Top = 152
    object nLoadFile: TMenuItem
      Caption = #24403#21069#31383#21475#23548#20837#25991#20214'('#20250#20002#22833#24403#21069#31383#21475#25968#25454')'
      OnClick = nLoadFileClick
    end
  end
end
