#include "TH1.h"
#include "TH2.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TStyle.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

void make_flux_solo(){

/*Gera a Tela*/
    auto c9 = new TCanvas("c9","Fluxo");
    c9->SetGrid();
    c9->SetLogx();


/*Gera os graficos*/
    auto g = new TGraph("./Datas/ee/flux/Flux_BSM_LIV2.dat");

/*Estilo da linha*/
    g->SetLineStyle(9);
    
/*Cor e tamanho*/
    g->SetLineWidth(2);
    g->SetLineColor(kBlue);


    string gmax = "Max: " + to_string(TMath::MaxElement(g->GetN(),g->GetY()));
    

/*titulo e eixos*/
    g->SetTitle("Fluxos dos Neutrinos;Energia (GeV); Fluxos(Log)");
    

/*coloca limite do grafico*/
    g->GetXaxis()->SetLimits(0.25,10);
    g->GetXaxis()->CenterTitle(true);
    g->GetYaxis()->CenterTitle(true);
    g->GetXaxis()->SetRangeUser(0.25,10);
    g->GetYaxis()->SetRangeUser(-14.5,-10.05);

    //printf("MAX e: %f\n", gre->GetYaxis()->GetXmax());

/*Desenha*/ 
    g->Draw("Al");

/*Legendas*/
    auto legend = new TLegend(0.7,0.9,0.85,0.8);
    legend->SetHeader("","C"); // option "C" allows to center the header
    legend->AddEntry(g," 2e-23 ","l");
    legend->Draw();

    auto legend2 = new TLegend(0.1,0.1,0.37,0.2);
    legend2->SetHeader("Maximos ","C"); // option "C" allows to center the header
    legend2->AddEntry((TObject*)0,gmax.c_str(),"");
    legend2->Draw();

    legend->SetTextSize(0.025);
    legend2->SetTextSize(0.025);

    c9->SaveAs("./Graficos e Histogramas/ee/Flux/Fluxo_ee_LIV2.png");
}
