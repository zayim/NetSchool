//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ScktComp.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TFormClient : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *mm_glavniMeni;
        TMenuItem *mi_fullScreen;
        TClientSocket *cs_clientSocket;
        TMenuItem *mi_connect;
        TImage *im_slikaDesktopa;
        TMemo *me_log;
        void __fastcall mi_fullScreenClick(TObject *Sender);
        void __fastcall mi_connectClick(TObject *Sender);
        void __fastcall ClientSocketError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall ClientSocketDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocketConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocketRead(TObject *Sender,
          TCustomWinSocket *Socket);
private:	// User declarations
        bool fullScreen;
        AnsiString adresaServera;
        Graphics::TBitmap *slikaDesktopa;
        TJPEGImage *jpgDesktop;
        int sleepTime;
        TMemoryStream *podaci;
        int ukupnoPrimljeno;
        int zaPrimiti;
        bool slanjeUToku;
public:		// User declarations
        __fastcall TFormClient(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormClient *FormClient;
//---------------------------------------------------------------------------
#endif
