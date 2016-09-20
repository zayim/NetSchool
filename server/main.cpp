//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include <jpeg.hpp>
#include <fstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormServer *FormServer;
//---------------------------------------------------------------------------
__fastcall TFormServer::TFormServer(TComponent* Owner)
        : TForm(Owner)
{
        im_desktopScreen->Width=Screen->Width;
        im_desktopScreen->Height=Screen->Height;

        std::fstream data("../includes/time.txt",std::ios::in);
        int timerInterval;
        data >> timerInterval;
        tm_timer->Interval = timerInterval;
        data.close();

        dc = GetDC(0);
        scrCanvas = new Graphics::TCanvas;
        scrCanvas->Handle = dc;
        rt = Rect(0,0,Screen->Width, Screen->Height);
}
//---------------------------------------------------------------------------
void __fastcall TFormServer::bt_aktivirajClick(TObject *Sender)
{
        if (!ss_serverSocket->Active)
        {
                ss_serverSocket->Active=true;
                bt_aktiviraj->Caption="Deaktiviraj";
        }
        else
        {
                for (int i=0; i<ss_serverSocket->Socket->ActiveConnections; i++)
                        ss_serverSocket->Socket->Connections[i]->Close();
                ss_serverSocket->Active=false;
                bt_aktiviraj->Caption="Aktiviraj";
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::ServerSocketClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        me_log->Lines->Add("Konektovan klijent: " + Socket->RemoteHost);
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::ServerSocketClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
       me_log->Lines->Add("Diskonektovan klijent: " + Socket->RemoteHost);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TFormServer::Button1Click(TObject *Sender)
{
        tm_timer->Enabled=true;

}
//---------------------------------------------------------------------------

void __fastcall TFormServer::tm_timerOnTimer(TObject *Sender)
{
        if (!ss_serverSocket->Socket->ActiveConnections) return;

        im_desktopScreen->Canvas->CopyRect(rt, scrCanvas, rt);

        TJPEGImage *desktop = new TJPEGImage;
        desktop->Assign(im_desktopScreen->Picture->Bitmap);

        TMemoryStream *podaci = new TMemoryStream();
        desktop->SaveToStream(podaci);
        //desktop->SaveToFile("prtscrn.jpg");

        int velicina = podaci->Size;

        ss_serverSocket->Socket->Connections[0]->SendBuf(&velicina,sizeof(int));
        podaci->Position = 0;
        ss_serverSocket->Socket->Connections[0]->SendStream(podaci);
        me_log->Lines->Add("Uspješno poslano: " + ss_serverSocket->Socket->Connections[0]->RemoteAddress);

        delete desktop;
        /*if (!ss_serverSocket->Socket->ActiveConnections) return;

        HDC dc = GetDC(0);
        Graphics::TCanvas *scrCanvas = new Graphics::TCanvas;
        scrCanvas->Handle = dc;

        TRect rt = Rect(0,0,Screen->Width, Screen->Height);
        im_desktopScreen->Canvas->CopyRect(rt, scrCanvas, rt);

        TJPEGImage *desktop = new TJPEGImage;
        desktop->Assign(im_desktopScreen->Picture->Bitmap);

        TMemoryStream *podaci = new TMemoryStream();
        desktop->SaveToStream(podaci);
        //desktop->SaveToFile("prtscrn.jpg");

        int velicina = podaci->Size;

        ss_serverSocket->Socket->Connections[0]->SendBuf(&velicina,sizeof(int));
        podaci->Position = 0;
        ss_serverSocket->Socket->Connections[0]->SendStream(podaci);
        me_log->Lines->Add("Uspješno poslano: " + ss_serverSocket->Socket->Connections[0]->RemoteAddress);

        delete scrCanvas;
        delete desktop;
        ReleaseDC(NULL,dc);*/
}
//---------------------------------------------------------------------------

