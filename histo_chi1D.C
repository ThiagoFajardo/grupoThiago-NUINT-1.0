#include "TH1.h"
#include "TH2.h"
#include "TH2D.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TLatex.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>


void histo_chi1D(){


/*Cria a Tela*/
TCanvas *c10 = new TCanvas("Chi2","Chi2",600,500);

/*cria o grafico do chi2*/
TGraph *graph = new TGraph("./BSM/chi2_co.dat");

/*Cria o histograma com o grafico do chi2*/
auto hist = new TH1F("Hist","Histogram",50,0,10);


/*Puxa os dados*/
fstream infile;
infile.open("./BSM/chi2_co.dat",ios::in);

double x;
int res;

for(int i = 0; i < 400; i++)
  {
    infile >> x >> res;
    /*Filtra valores para o histograma*/
    hist->Fill(x,res);
    /*Força a parada*/
    if(infile.eof()) break;
  }
  
/*fecha o arquivo*/
infile.close();

/*divide em dois graficos* */
//c10->Divide(1,2);
//
///*inicio primeiro gráfico*/
//c10->cd(1);
////hist->SetLogx();
//
//hist->SetStats(true);
////int binWithMax = hist->GetMaximumBin();
////double xValueWithMax = hist->GetXaxis()->GetBinCenter(binWithMax);
////double yValueWithMax = hist->GetBinContent(binWithMax);
//  
///*Titulos*/
//hist->GetXaxis()->CenterTitle();
//hist->GetYaxis()->CenterTitle();
//hist->GetXaxis()->SetTitle("log sin^{2} (2#theta_{13})");
//hist->GetYaxis()->SetTitle("#Delta #chi^{2}");
////hist->GetYaxis()->SetTitle("#delta_{CP} (graus)");
////hist->GetXaxis()->SetTitle("log sin^{2} (2#theta_{13})");
////hist->GetZaxis()->CenterTitle();
////hist->GetZaxis()->SetTitle("#Delta #chi^{2}");
//
///*Contornos*/
//double contornos[3] = {2.30,6.18,14.16};
//hist->SetContour(3,contornos);
//
///*Define a paleta de cores para o histograma*/
//int colors[3] = {kRed,kOrange,kYellow};
//gStyle->SetPalette(3,colors);
//
//gStyle->SetOptStat(1);
//
////hist->GetXaxis()->SetRangeUser(-2,2);
////hist->GetYaxis()->SetRangeUser(0,300);
//
///*Plota o histograma*/
//hist->Draw("cont3");
//hist->DrawNormalized("");

/*inicio do segundo grafico*/
c10->cd(2);

graph->SetLineStyle(1);
graph->SetLineColor(2);

graph->GetXaxis()->CenterTitle();
graph->GetYaxis()->CenterTitle();
graph->GetXaxis()->SetTitle("abs_a_mue");
graph->GetYaxis()->SetTitle("#Delta #chi^{2}");


graph->GetXaxis()->SetRangeUser(0,5);
graph->GetYaxis()->SetRangeUser(0,10);
graph->Draw("");



}
    
