object MainForm: TMainForm
  Left = 194
  Top = 111
  Caption = 'MDI Application'
  ClientHeight = 726
  ClientWidth = 798
  Color = clAppWorkSpace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clBlack
  Font.Height = -11
  Font.Name = 'Default'
  Font.Style = []
  FormStyle = fsMDIForm
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDefault
  WindowState = wsMaximized
  WindowMenu = Window1
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 169
    Top = 21
    Height = 686
    ExplicitLeft = 256
    ExplicitTop = 248
    ExplicitHeight = 100
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 707
    Width = 798
    Height = 19
    AutoHint = True
    Panels = <
      item
        Width = 500
      end>
  end
  object TabSet1: TTabSet
    Left = 0
    Top = 0
    Width = 798
    Height = 21
    Align = alTop
    BackgroundColor = clWhite
    DitherBackground = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentBackground = True
    SoftTop = True
    Style = tsSoftTabs
    Tabs.Strings = (
      'test'
      'test2')
    TabIndex = 0
    TabPosition = tpTop
    OnChange = TabSet1Change
    OnDrawTab = TabSet1DrawTab
  end
  object Panel1: TPanel
    Left = 0
    Top = 21
    Width = 169
    Height = 686
    Align = alLeft
    TabOrder = 2
    object edtFind: TEdit
      Left = 1
      Top = 664
      Width = 167
      Height = 21
      Align = alBottom
      TabOrder = 0
      OnChange = edtFindChange
    end
    object nbShowPages: TNotebook
      Left = 1
      Top = 1
      Width = 167
      Height = 663
      Align = alClient
      PageIndex = 1
      TabOrder = 1
      object TPage
        Left = 0
        Top = 0
        Caption = 'List'
        ExplicitWidth = 0
        ExplicitHeight = 0
        object Panel2: TPanel
          Left = 0
          Top = 0
          Width = 167
          Height = 663
          Align = alClient
          TabOrder = 0
          object lvWorkSpace: TListView
            Left = 1
            Top = 1
            Width = 165
            Height = 661
            Align = alClient
            Columns = <
              item
                Caption = #21517#23383
                Width = 150
              end>
            HideSelection = False
            OwnerData = True
            ReadOnly = True
            RowSelect = True
            PopupMenu = pmWorkSpace
            TabOrder = 0
            ViewStyle = vsReport
            OnDblClick = lvWorkSpaceDblClick
            OnKeyPress = lvWorkSpaceKeyPress
          end
        end
      end
      object TPage
        Left = 0
        Top = 0
        Caption = 'Tree'
        object Panel3: TPanel
          Left = 0
          Top = 0
          Width = 167
          Height = 663
          Align = alClient
          TabOrder = 0
          object tvWorkSpaceTree: TTreeView
            Tag = 1
            Left = 1
            Top = 1
            Width = 165
            Height = 661
            Align = alClient
            Indent = 19
            PopupMenu = pmWorkSpace
            ReadOnly = True
            RowSelect = True
            TabOrder = 0
            OnDblClick = tvWorkSpaceTreeDblClick
            OnKeyPress = lvWorkSpaceKeyPress
          end
        end
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 496
    Top = 8
    object File1: TMenuItem
      Caption = #24037#20316#21306
      Hint = 'File related commands'
      object FileNewItem: TMenuItem
        Action = FileNew1
      end
      object FileSaveItem: TMenuItem
        Action = FileSave1
      end
      object N9: TMenuItem
        Caption = '-'
      end
      object FileOpenItem: TMenuItem
        Action = FileOpen1
      end
      object miReOpen: TMenuItem
        Caption = #37325#26032#25171#24320
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object FileCloseItem: TMenuItem
        Action = FileClose1
      end
      object FileExitItem: TMenuItem
        Action = FileExit1
      end
    end
    object N2: TMenuItem
      Caption = #26597#30475
      object N3: TMenuItem
        Action = actWatchLog
      end
      object N4: TMenuItem
        Action = actWatchPlugin
      end
      object N14: TMenuItem
        Caption = '-'
      end
      object Key1: TMenuItem
        Action = actSetKey
      end
      object Key2: TMenuItem
        Action = actUseGlobalKey
        AutoCheck = True
      end
      object N15: TMenuItem
        Caption = '-'
      end
      object N161: TMenuItem
        Action = actParseAsHex
        AutoCheck = True
      end
    end
    object N10: TMenuItem
      Caption = #38468#21152#24037#20855
      object N11: TMenuItem
        Action = actSearchFiles
      end
      object N16: TMenuItem
        Caption = '-'
      end
      object N17: TMenuItem
        Action = actOpenDesign
      end
      object N21: TMenuItem
        Caption = '-'
      end
      object N23: TMenuItem
        Action = actSetup
      end
      object N22: TMenuItem
        Action = actOpenSetup
      end
    end
    object N20: TMenuItem
      Action = actDebug
    end
    object Window1: TMenuItem
      Caption = '&Window'
      Hint = 'Window related commands'
      object WindowCascadeItem: TMenuItem
        Action = WindowCascade1
      end
      object WindowTileItem: TMenuItem
        Action = WindowTileHorizontal1
      end
      object WindowTileItem2: TMenuItem
        Action = WindowTileVertical1
      end
      object WindowMinimizeItem: TMenuItem
        Action = WindowMinimizeAll1
      end
      object WindowArrangeItem: TMenuItem
        Action = WindowArrangeAll1
      end
    end
    object Help1: TMenuItem
      Caption = '&Help'
      Hint = 'Help topics'
      object HelpAboutItem: TMenuItem
        Action = HelpAbout1
      end
    end
  end
  object OpenDialog: TOpenDialog
    Filter = #24037#20316#21306#25991#20214' (*.egg)|*.egg'
    Left = 464
    Top = 8
  end
  object ActionList1: TActionList
    Left = 432
    Top = 8
    object FileNew1: TAction
      Category = 'File'
      Caption = #26032#24314#24037#20316#21306
      Hint = 'New|Create a new file'
      ImageIndex = 6
      ShortCut = 16462
      OnExecute = FileNew1Execute
    end
    object FileOpen1: TAction
      Category = 'File'
      Caption = #25171#24320#24037#20316#21306
      Hint = 'Open|Open a file'
      ImageIndex = 7
      ShortCut = 16463
      OnExecute = FileOpen1Execute
    end
    object FileClose1: TWindowClose
      Category = 'File'
      Caption = #20851#38381#24037#20316#21306
      Hint = 'Close|Close current file'
      OnExecute = FileClose1Execute
    end
    object FileSave1: TAction
      Category = 'File'
      Caption = #20445#23384#24037#20316#21306
      Hint = 'Save|Save current file'
      ImageIndex = 8
      ShortCut = 16467
      OnExecute = FileSave1Execute
    end
    object FileExit1: TAction
      Category = 'File'
      Caption = #36864#20986
      Hint = 'Exit|Exit application'
      OnExecute = FileExit1Execute
    end
    object EditCut1: TEditCut
      Category = 'Edit'
      Caption = 'Cu&t'
      Enabled = False
      Hint = 'Cut|Cuts the selection and puts it on the Clipboard'
      ImageIndex = 0
      ShortCut = 16472
    end
    object EditCopy1: TEditCopy
      Category = 'Edit'
      Caption = '&Copy'
      Enabled = False
      Hint = 'Copy|Copies the selection and puts it on the Clipboard'
      ImageIndex = 1
      ShortCut = 16451
    end
    object EditPaste1: TEditPaste
      Category = 'Edit'
      Caption = '&Paste'
      Hint = 'Paste|Inserts Clipboard contents'
      ImageIndex = 2
      ShortCut = 16470
    end
    object WindowCascade1: TWindowCascade
      Category = 'Window'
      Caption = '&Cascade'
      Hint = 'Cascade'
      ImageIndex = 17
    end
    object WindowTileHorizontal1: TWindowTileHorizontal
      Category = 'Window'
      Caption = 'Tile &Horizontally'
      Hint = 'Tile Horizontally'
      ImageIndex = 15
    end
    object WindowTileVertical1: TWindowTileVertical
      Category = 'Window'
      Caption = 'Tile &Vertically'
      Hint = 'Tile Vertically'
      ImageIndex = 16
    end
    object WindowMinimizeAll1: TWindowMinimizeAll
      Category = 'Window'
      Caption = '&Minimize All'
      Hint = 'Minimize All'
    end
    object WindowArrangeAll1: TWindowArrange
      Category = 'Window'
      Caption = '&Arrange All'
      Hint = 'Arrange All'
    end
    object HelpAbout1: TAction
      Category = 'Help'
      Caption = '&About...'
      Hint = 
        'About|Displays program information, version number, and copyrigh' +
        't'
      OnExecute = HelpAbout1Execute
    end
    object actWatchLog: TAction
      Caption = #26597#30475#38169#35823#26085#24535
      OnExecute = actWatchLogExecute
    end
    object actWatchPlugin: TAction
      Caption = #26597#30475#25554#20214
      OnExecute = actWatchPluginExecute
    end
    object actSetComment: TAction
      Caption = #28155#21152#27880#37322'...'
      OnExecute = actSetCommentExecute
    end
    object actDeleteWorkSpace: TAction
      Caption = #21024#38500
      OnExecute = actDeleteWorkSpaceExecute
    end
    object actNewWorkSpace: TAction
      Caption = #26032#24314#24037#20316#21306
      OnExecute = actNewWorkSpaceExecute
    end
    object actSearchFiles: TAction
      Caption = #36229#32423#26597#25214'..'
      OnExecute = actSearchFilesExecute
    end
    object actAddWorkSpace: TAction
      Caption = #28155#21152#25991#20214
      OnExecute = actAddWorkSpaceExecute
    end
    object actOutputAllRecv: TAction
      Caption = #23548#20986#25152#26377'Recv...'
      OnExecute = actOutputAllRecvExecute
    end
    object actOutputAllSend: TAction
      Caption = #23548#20986#25152#26377'WriteBuffer...'
      OnExecute = actOutputAllSendExecute
    end
    object actSetKey: TAction
      Caption = #35774#32622'Key'
      OnExecute = actSetKeyExecute
    end
    object actUseGlobalKey: TAction
      AutoCheck = True
      Caption = #20351#29992#20840#23616'Key'
      OnExecute = actUseGlobalKeyExecute
    end
    object actParseAsHex: TAction
      AutoCheck = True
      Caption = #25353#29031'16'#36827#21046#26041#24335#35299#26512'/'#26597#30475
      OnExecute = actParseAsHexExecute
    end
    object actOpenDesign: TAction
      Caption = #35774#35745#39029
      OnExecute = actOpenDesignExecute
    end
    object actChangeView: TAction
      Caption = #20999#25442#21040#26641#24418#35270#22270
      OnExecute = actChangeViewExecute
    end
    object actDebug: TAction
      Caption = #35843#35797
      OnExecute = actDebugExecute
    end
    object actOpenSetup: TAction
      Caption = #20840#23616#37197#32622
      OnExecute = actOpenSetupExecute
    end
    object actSetup: TAction
      Caption = #39033#30446#37197#32622
      OnExecute = actSetupExecute
    end
    object actOutputReadWriteAll: TAction
      Caption = #23548#20986#25152#26377'ReadWriteAll'
      OnExecute = actOutputReadWriteAllExecute
    end
  end
  object XPManifest1: TXPManifest
    Left = 584
    Top = 8
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'E:\'
    Filter = #24037#20316#21306#25991#20214' (*.egg)|*.egg'
    Left = 336
    Top = 8
  end
  object pmWorkSpace: TPopupMenu
    Left = 88
    Top = 72
    object N8: TMenuItem
      Action = actNewWorkSpace
    end
    object N7: TMenuItem
      Caption = '-'
    end
    object N5: TMenuItem
      Action = actSetComment
    end
    object N12: TMenuItem
      Action = actAddWorkSpace
    end
    object N6: TMenuItem
      Action = actDeleteWorkSpace
    end
    object N13: TMenuItem
      Caption = '-'
    end
    object Recv1: TMenuItem
      Action = actOutputAllRecv
    end
    object WriteBuffer1: TMenuItem
      Action = actOutputAllSend
    end
    object ReadWriteAll1: TMenuItem
      Action = actOutputReadWriteAll
    end
    object N18: TMenuItem
      Caption = '-'
    end
    object N19: TMenuItem
      Action = actChangeView
      Caption = #20999#25442#21040#32463#20856#35270#22270
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = #24037#20316#25991#20214' (*.eggxp)|*.eggxp'
    Options = [ofHideReadOnly, ofAllowMultiSelect, ofEnableSizing]
    Left = 264
    Top = 24
  end
end
