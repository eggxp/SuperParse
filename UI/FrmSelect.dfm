object SelectFrm: TSelectFrm
  Left = 0
  Top = 0
  Caption = 'SelectFrm'
  ClientHeight = 193
  ClientWidth = 219
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
  object Label1: TLabel
    Left = 16
    Top = 61
    Width = 31
    Height = 13
    Caption = #22823#23567' :'
  end
  object Label2: TLabel
    Left = 16
    Top = 26
    Width = 52
    Height = 13
    Caption = #24403#21069#20301#32622':'
  end
  object Label3: TLabel
    Left = 74
    Top = 93
    Width = 108
    Height = 13
    Caption = #21069#38754#21152'0x'#34920#31034'16'#36827#21046
  end
  object edtJumpOffset: TEdit
    Left = 74
    Top = 61
    Width = 121
    Height = 21
    TabOrder = 0
  end
  object edtCurOffset: TEdit
    Left = 74
    Top = 23
    Width = 121
    Height = 21
    ReadOnly = True
    TabOrder = 1
  end
  object Panel1: TPanel
    Left = 16
    Top = 112
    Width = 179
    Height = 25
    TabOrder = 2
    object rbFrmCurPosition: TRadioButton
      Left = 8
      Top = 4
      Width = 81
      Height = 17
      Caption = #24403#21069#20301#32622
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object rbFromStart: TRadioButton
      Left = 101
      Top = 4
      Width = 76
      Height = 17
      Caption = #36215#22987#20301#32622
      TabOrder = 1
    end
  end
  object btOK: TButton
    Left = 16
    Top = 160
    Width = 75
    Height = 25
    Caption = #30830#23450
    ModalResult = 1
    TabOrder = 3
  end
  object btCancel: TButton
    Left = 118
    Top = 160
    Width = 75
    Height = 25
    Caption = #21462#28040
    ModalResult = 2
    TabOrder = 4
  end
end
