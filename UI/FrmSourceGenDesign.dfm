object SourceGenDesignFrm: TSourceGenDesignFrm
  Left = 0
  Top = 0
  Caption = #39033#30446#37197#32622
  ClientHeight = 145
  ClientWidth = 367
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
    Top = 24
    Width = 176
    Height = 13
    Caption = #35831#36755#20837#23553#21253#22836#30340#26368#22823#25968#30446'(16'#36827#21046')'
  end
  object Label2: TLabel
    Left = 16
    Top = 56
    Width = 200
    Height = 13
    Caption = #35831#36755#20837#23553#21253#23376#21629#20196#30340#26368#22823#25968#30446'(16'#36827#21046')'
  end
  object Label3: TLabel
    Left = 16
    Top = 89
    Width = 282
    Height = 13
    Caption = #27880#24847': '#20250#25913#21464#25991#20214#31995#32479#32467#26500', '#21482#36866#29992#20110#25209#37327#21019#24314#26032#39033#30446'!'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object edtHeadPackCount: TEdit
    Left = 232
    Top = 21
    Width = 121
    Height = 21
    TabOrder = 0
    Text = '0x32'
  end
  object edtSubHeadCount: TEdit
    Left = 232
    Top = 53
    Width = 121
    Height = 21
    TabOrder = 1
    Text = '0xF'
  end
  object btOk: TButton
    Left = 16
    Top = 112
    Width = 75
    Height = 25
    Caption = #30830#23450
    TabOrder = 2
    OnClick = btOkClick
  end
  object btCancel: TButton
    Left = 284
    Top = 112
    Width = 75
    Height = 25
    Caption = #21462#28040
    TabOrder = 3
    OnClick = btCancelClick
  end
end
