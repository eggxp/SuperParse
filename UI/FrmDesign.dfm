object DesignFrm: TDesignFrm
  Left = 0
  Top = 0
  Caption = #35774#35745#39029
  ClientHeight = 656
  ClientWidth = 669
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
  object Splitter1: TSplitter
    Left = 0
    Top = 265
    Width = 669
    Height = 3
    Cursor = crVSplit
    Align = alTop
    ExplicitWidth = 31
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 669
    Height = 265
    Align = alTop
    Caption = #23553#21253#22836#23450#20041
    TabOrder = 0
    object vleHeadDef: TValueListEditor
      Left = 2
      Top = 15
      Width = 665
      Height = 207
      Align = alClient
      TabOrder = 0
      OnMouseUp = vleHeadDefMouseUp
      ColWidths = (
        150
        509)
    end
    object Panel1: TPanel
      Left = 2
      Top = 222
      Width = 665
      Height = 41
      Align = alBottom
      TabOrder = 1
      object btAddHeadDef: TButton
        Left = 406
        Top = 6
        Width = 75
        Height = 25
        Caption = #28155#21152
        TabOrder = 0
        OnClick = btAddHeadDefClick
      end
      object btDefHeadDef: TButton
        Left = 491
        Top = 6
        Width = 75
        Height = 25
        Caption = #21024#38500
        TabOrder = 1
        OnClick = btDefHeadDefClick
      end
      object btClearHeadDef: TButton
        Left = 576
        Top = 6
        Width = 75
        Height = 25
        Caption = #28165#31354
        TabOrder = 2
        OnClick = btClearHeadDefClick
      end
      object btSaveRefresh: TButton
        Left = 285
        Top = 6
        Width = 75
        Height = 25
        Caption = #20445#23384#24182#21047#26032
        TabOrder = 3
        OnClick = btSaveRefreshClick
      end
      object btOutputSource: TButton
        Left = 12
        Top = 6
        Width = 75
        Height = 25
        Caption = #23548#20986#26694#26550
        TabOrder = 4
        OnClick = btOutputSourceClick
      end
    end
  end
  object gbSubPack: TGroupBox
    Left = 0
    Top = 268
    Width = 669
    Height = 388
    Align = alClient
    Caption = #23553#21253#23376#23450#20041
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    object vleSubHeadDef: TValueListEditor
      Left = 2
      Top = 15
      Width = 665
      Height = 253
      Align = alClient
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnKeyDown = vleSubHeadDefKeyDown
      ColWidths = (
        150
        509)
    end
    object Panel2: TPanel
      Left = 2
      Top = 268
      Width = 665
      Height = 118
      Align = alBottom
      TabOrder = 1
      object btAddSubHead: TButton
        Left = 406
        Top = 6
        Width = 75
        Height = 25
        Caption = #28155#21152
        TabOrder = 0
        OnClick = btAddSubHeadClick
      end
      object btDeleteSubHead: TButton
        Left = 491
        Top = 6
        Width = 75
        Height = 25
        Caption = #21024#38500
        TabOrder = 1
        OnClick = btDeleteSubHeadClick
      end
      object Memo1: TMemo
        Left = 1
        Top = 1
        Width = 384
        Height = 116
        Align = alLeft
        Color = clInfoBk
        Lines.Strings = (
          #27880#24847'!'
          '    '#23553#21253#33258#23450#20041#30340'key'#26159#25991#20214', value'#26159#27492#25991#20214#30340#27880#37322'. '#27880#37322#26684#24335':'
          '    '#22836' + '#31354#26684' + '#23376#22836' + '#27880#37322' + "#" + '#35835#21462#27492#23553#21253#30340#32467#26500#20307#21517#31216', '#20363#22914':'
          '    01 02 '#20154#29289#30331#24405' #tagRoleLogin            '#27880#24847#31354#26684
          '    tagRoleLogin '#26159#29992#26469#35835#21462#36825#20010#23553#21253#30340#32467#26500#20307#21517#31216
          ''
          '    '#27492#22788#23553#21253#33258#23450#20041#30340'value'#39033#19981#20250#26174#31034#20027#22836',  '#35201#26356#25913#20027#22836#30340#35805', '#24517#39035#22312#26641
          #24418#32467#26500#20013#25913)
        TabOrder = 2
      end
    end
  end
  object btStartNew: TButton
    Left = 267
    Top = 0
    Width = 176
    Height = 25
    Align = alCustom
    Caption = #28857#25105#24320#22987#20840#26032#30340#36335#31243'!'
    TabOrder = 2
    OnClick = btStartNewClick
  end
  object SaveDialog1: TSaveDialog
    Filter = '.h|*.h'
    FilterIndex = 0
    Left = 336
    Top = 88
  end
end
