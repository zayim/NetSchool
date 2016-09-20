object FormServer: TFormServer
  Left = 779
  Top = 101
  Width = 623
  Height = 536
  Caption = 'Server'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object im_desktopScreen: TImage
    Left = 312
    Top = 16
    Width = 17
    Height = 25
    Visible = False
  end
  object bt_aktiviraj: TButton
    Left = 240
    Top = 80
    Width = 121
    Height = 33
    Caption = 'Aktiviraj server'
    TabOrder = 0
    OnClick = bt_aktivirajClick
  end
  object me_log: TMemo
    Left = 72
    Top = 160
    Width = 465
    Height = 249
    TabOrder = 1
  end
  object Button1: TButton
    Left = 24
    Top = 32
    Width = 89
    Height = 33
    Caption = 'Po'#269'ni'
    TabOrder = 2
    OnClick = Button1Click
  end
  object ss_serverSocket: TServerSocket
    Active = False
    Port = 4000
    ServerType = stNonBlocking
    OnClientConnect = ServerSocketClientConnect
    OnClientDisconnect = ServerSocketClientDisconnect
    Left = 272
    Top = 16
  end
  object tm_timer: TTimer
    Enabled = False
    Interval = 750
    OnTimer = tm_timerOnTimer
    Left = 536
    Top = 16
  end
end
