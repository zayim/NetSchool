object FormClient: TFormClient
  Left = 559
  Top = 51
  Width = 628
  Height = 652
  Caption = 'Klijent'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = mm_glavniMeni
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object im_slikaDesktopa: TImage
    Left = 0
    Top = 0
    Width = 609
    Height = 593
  end
  object me_log: TMemo
    Left = 16
    Top = 0
    Width = 577
    Height = 153
    TabOrder = 0
    Visible = False
  end
  object mm_glavniMeni: TMainMenu
    object mi_fullScreen: TMenuItem
      Caption = 'Enter full screen'
      OnClick = mi_fullScreenClick
    end
    object mi_connect: TMenuItem
      Caption = 'Konektuj se'
      OnClick = mi_connectClick
    end
  end
  object cs_clientSocket: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 4000
    OnConnect = ClientSocketConnect
    OnDisconnect = ClientSocketDisconnect
    OnRead = ClientSocketRead
    OnError = ClientSocketError
    Left = 280
    Top = 8
  end
end
