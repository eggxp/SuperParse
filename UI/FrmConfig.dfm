object ConfigFrm: TConfigFrm
  Left = 0
  Top = 0
  Caption = #37197#32622
  ClientHeight = 155
  ClientWidth = 225
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 193
    Height = 129
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 22
      Width = 24
      Height = 13
      Caption = #23383#20307
    end
    object Label2: TLabel
      Left = 16
      Top = 54
      Width = 24
      Height = 13
      Caption = #22823#23567
    end
    object edtCharset: TEdit
      Left = 56
      Top = 19
      Width = 129
      Height = 21
      TabOrder = 0
      Text = 'Tahoma'
    end
    object btOk: TButton
      Left = 16
      Top = 99
      Width = 75
      Height = 25
      Caption = #30830#23450
      ModalResult = 1
      TabOrder = 1
    end
    object btCancel: TButton
      Left = 110
      Top = 99
      Width = 75
      Height = 25
      Caption = #21462#28040
      ModalResult = 2
      TabOrder = 2
    end
    object edtCharsetSize: TCSpinEdit
      Left = 56
      Top = 51
      Width = 129
      Height = 22
      TabOrder = 3
      Value = 8
    end
    object cbUseDefSetup: TCheckBox
      Left = 3
      Top = -1
      Width = 113
      Height = 17
      Caption = #20351#29992#33258#23450#20041#37197#32622
      TabOrder = 4
    end
  end
end
