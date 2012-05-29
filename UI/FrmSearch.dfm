object SearchFrm: TSearchFrm
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #26597#25214
  ClientHeight = 123
  ClientWidth = 240
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
  object Label1: TLabel
    Left = 11
    Top = 12
    Width = 100
    Height = 13
    Caption = #36755#20837#35201#26597#25214#30340#20869#23481':'
  end
  object edtSearchContent: TEdit
    Left = 29
    Top = 31
    Width = 203
    Height = 21
    TabOrder = 0
  end
  object cbSearchMode: TComboBox
    Left = 29
    Top = 58
    Width = 203
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 1
    Text = #25628#32034'16'#36827#21046#23383#31526#20018
    Items.Strings = (
      #25628#32034'16'#36827#21046#23383#31526#20018
      #25628#32034'bin')
  end
  object btOk: TButton
    Left = 11
    Top = 89
    Width = 75
    Height = 25
    Caption = #30830#23450
    ModalResult = 1
    TabOrder = 2
  end
  object Button2: TButton
    Left = 157
    Top = 89
    Width = 75
    Height = 25
    Caption = #21462#28040
    ModalResult = 2
    TabOrder = 3
  end
end
