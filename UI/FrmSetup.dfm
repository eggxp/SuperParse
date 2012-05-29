object SetupFrm: TSetupFrm
  Left = 0
  Top = 0
  Caption = #39033#30446#37197#32622
  ClientHeight = 95
  ClientWidth = 327
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 24
    Width = 24
    Height = 13
    Caption = #35821#35328
  end
  object cbLanguage: TComboBox
    Left = 80
    Top = 21
    Width = 145
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 0
    Text = #32321#20307
    OnChange = cbLanguageChange
    Items.Strings = (
      #32321#20307
      #31616#20307
      'UTF-8'
      'Unicode')
  end
end
