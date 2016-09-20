//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ScktComp.hpp>
#include "../includes/protocol.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormServer : public TForm
{
__published:	// IDE-managed Components
        TButton *bt_aktiviraj;
        TServerSocket *ss_serverSocket;
        TMemo *me_log;
        TButton *Button1;
        TImage *im_desktopScreen;
        TTimer *tm_timer;
        void __fastcall bt_aktivirajClick(TObject *Sender);
        void __fastcall ServerSocketClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ServerSocketClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall tm_timerOnTimer(TObject *Sender);
private:	// User declarations
        HDC dc;
        Graphics::TCanvas *scrCanvas;
        TRect rt;
public:		// User declarations
        __fastcall TFormServer(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormServer *FormServer;
//---------------------------------------------------------------------------
#endif
