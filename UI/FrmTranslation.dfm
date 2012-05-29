object TranslationFrm: TTranslationFrm
  Left = 0
  Top = 0
  Caption = 'TranslationFrm'
  ClientHeight = 97
  ClientWidth = 166
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 40
    Top = 64
    Width = 75
    Height = 25
    Caption = #30830#23450
    ModalResult = 1
    TabOrder = 0
  end
  object cbTanslation: TComboBox
    Left = 13
    Top = 24
    Width = 145
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 1
    Text = 'Windows'
    Items.Strings = (
      'Windows'
      'Dos 8 Bit'
      'AscII 7Bit'
      'MacIntoSh'
      'EBCDic CodePage 38')
  end
end
