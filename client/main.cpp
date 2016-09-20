//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "../includes/protocol.h"
#include <fstream>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormClient *FormClient;
//---------------------------------------------------------------------------
__fastcall TFormClient::TFormClient(TComponent* Owner)
        : TForm(Owner), fullScreen(false), ukupnoPrimljeno(0), zaPrimiti(0), slanjeUToku(false)
{
        std::fstream data("../includes/time.txt",std::ios::in);
        data >> sleepTime >> sleepTime;
        data.close();
}
//---------------------------------------------------------------------------
void __fastcall TFormClient::mi_fullScreenClick(TObject *Sender)
{
        if (!fullScreen)
        {
                FormClient->BorderStyle=bsNone;
                FormClient->Top=0;
                FormClient->Left=0;
                FormClient->Width=Screen->Width;
                FormClient->Height=Screen->Height;
                fullScreen=true;
                mi_fullScreen->Caption="Exit full screen";
        }
        else
        {
                FormClient->BorderStyle=bsSizeable;
                FormClient->Top=200;
                FormClient->Left=400;
                FormClient->Width=600;
                FormClient->Height=400;
                fullScreen=false;
                mi_fullScreen->Caption="Enter full screen";
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormClient::mi_connectClick(TObject *Sender)
{

        if (!cs_clientSocket->Active)
        {
                if (InputQuery("Konekcija","Adresa servera: ",adresaServera))
                {
                        try
                        {
                                cs_clientSocket->Host=adresaServera;
                                cs_clientSocket->Active=true;

                        }
                        catch(ESocketError &e)
                        {
                                ShowMessage("Neuspjela konekcija!");
                        }
                }
        }
        else
                cs_clientSocket->Active=false;
}
//---------------------------------------------------------------------------

void __fastcall TFormClient::ClientSocketError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
        cs_clientSocket->Active=false;
        cs_clientSocket->Host="";
        ErrorCode=0;
        mi_connect->Caption="Konektuj se";
        ShowMessage("Neuspjela konekcija!");
}
//---------------------------------------------------------------------------

void __fastcall TFormClient::ClientSocketDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        mi_connect->Caption="Konektuj se";
        ShowMessage("Diskonektovani ste sa servera!");        
}
//---------------------------------------------------------------------------

void __fastcall TFormClient::ClientSocketConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        mi_connect->Caption="Diskonektuj se";
        ShowMessage("Konektovani ste na server!");
}
//---------------------------------------------------------------------------

void __fastcall TFormClient::ClientSocketRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
        me_log->Lines->Add(AnsiString("Poziv funkcije"));
        if (Socket->ReceiveLength()==0) { return; }

        if (!slanjeUToku)
        {
                Socket->ReceiveBuf(&zaPrimiti,sizeof(int));
                ukupnoPrimljeno=0;
                slanjeUToku=true;
                podaci = new TMemoryStream();
        }

        int bits=Socket->ReceiveLength();
        if (!bits) return;
        BYTE *buf = new BYTE[bits];

        //Sleep(sleepTime);
        //me_log->Lines->Add(AnsiString("Velicina: ") + bits);

        Socket->ReceiveBuf(buf,bits);
        podaci->Write(buf,bits);
        delete[] buf;

        ukupnoPrimljeno+=bits;

        if (ukupnoPrimljeno==zaPrimiti)
        {
                try
                {
                        jpgDesktop = new TJPEGImage;
                        podaci->Position=0;
                        jpgDesktop->LoadFromStream(podaci);

                        int sirina;
                        int visina;

                        if (fullScreen)
                        {
                                sirina=Screen->Width;
                                visina=Screen->Height;
                        }
                        else
                        {
                                sirina=this->Width;
                                visina=(9*this->Width)/16 ;
                        }


                        im_slikaDesktopa->Width = sirina;
                        im_slikaDesktopa->Height = visina;

                        jpgDesktop->DIBNeeded();

                        im_slikaDesktopa->Picture->Bitmap->Width=sirina;
                        im_slikaDesktopa->Picture->Bitmap->Height=visina;
                        im_slikaDesktopa->Picture->Bitmap->Canvas->StretchDraw(TRect(0,0,sirina,visina),jpgDesktop);
                }
                catch(...)
                {
                        Sleep(100);
                }

                delete podaci;
                delete jpgDesktop;

                slanjeUToku=false;
                ukupnoPrimljeno=0;
                zaPrimiti=0;
        }
}
//---------------------------------------------------------------------------

