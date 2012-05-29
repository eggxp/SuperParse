object EditFileDescribeFrm: TEditFileDescribeFrm
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #25991#20214#23646#24615
  ClientHeight = 314
  ClientWidth = 293
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
    Left = 8
    Top = 16
    Width = 52
    Height = 13
    Caption = #25991#20214#25551#36848':'
  end
  object Label2: TLabel
    Left = 8
    Top = 71
    Width = 52
    Height = 13
    Caption = #21019#24314#26085#26399':'
  end
  object Label3: TLabel
    Left = 8
    Top = 103
    Width = 52
    Height = 13
    Caption = #25991#20214#27880#37322':'
  end
  object Label4: TLabel
    Left = 8
    Top = 44
    Width = 22
    Height = 13
    Caption = 'Key:'
  end
  object Button1: TButton
    Left = 8
    Top = 270
    Width = 75
    Height = 25
    Caption = #30830#23450
    ModalResult = 1
    TabOrder = 0
  end
  object Button2: TButton
    Left = 206
    Top = 270
    Width = 75
    Height = 25
    Caption = #21462#28040
    ModalResult = 2
    TabOrder = 1
  end
  object edtFileDescribe: TEdit
    Left = 80
    Top = 13
    Width = 201
    Height = 21
    TabOrder = 2
  end
  object edtCreateDate: TEdit
    Left = 80
    Top = 68
    Width = 121
    Height = 21
    ReadOnly = True
    TabOrder = 3
  end
  object memRemark: TMemo
    Left = 8
    Top = 122
    Width = 273
    Height = 142
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 4
  end
  object btResetTime: TButton
    Left = 207
    Top = 66
    Width = 74
    Height = 25
    Caption = #37325#35774#26085#26399
    TabOrder = 5
    OnClick = btResetTimeClick
  end
  object edtKey: TEdit
    Left = 80
    Top = 41
    Width = 201
    Height = 21
    TabOrder = 6
  end
end
