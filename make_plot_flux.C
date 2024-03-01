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

void make_plot_flux(){

/*Gera a Tela*/
    auto c9 = new TCanvas("c9","Fluxo");
    c9->SetGrid();
    //c9->SetLogx();


/*Gera os graficos*/
    auto gstd  = new TGraph("./Datas/ee/flux/Flux_BSM_STD.dat");
    auto gliv1 = new TGraph("./Datas/ee/flux/Flux_BSM_LIV1.dat");
    auto gliv2  = new TGraph("./Datas/ee/flux/Flux_BSM_LIV2.dat");
    auto glivN  = new TGraph("./Datas/ee/flux/Flux_BSM_LIVN.dat");



/*Estilo da linha*/
    //gstd->SetLineStyle(8);
    gliv1->SetLineStyle(9);
    gliv2->SetLineStyle(9);
    glivN->SetLineStyle(9);
    
/*Cor e tamanho*/
    gstd->SetLineWidth(2);
    gstd->SetLineColor(kBlue);

    gliv1->SetLineColor(kRed);
    gliv1->SetLineWidth(2);

    gliv2->SetLineColor(kBlack);
    gliv2->SetLineWidth(2);

    glivN->SetLineColor(6);
    glivN->SetLineWidth(2);

    string stdmax = "Max STD: " + to_string(TMath::MaxElement(gstd->GetN(),gstd->GetY()));
    string liv1max = "Max 1e-23: " + to_string(TMath::MaxElement(gliv1->GetN(),gliv1->GetY()));
    string liv2max = "Max 2e-23: " + to_string(TMath::MaxElement(gliv2->GetN(),gliv2->GetY()));
    string livNmax = "Max 5e-23: " + to_string(TMath::MaxElement(glivN->GetN(),glivN->GetY()));

/*Gera o grafico multiplo*/
    auto *g = new TMultiGraph();

/*titulo e eixos*/
    g->SetTitle("Fluxos dos Neutrinos;Energia (GeV); Fluxos(Log)");
    

/*coloca limite do grafico*/
    g->GetXaxis()->SetLimits(0.25,10);
    g->GetXaxis()->CenterTitle(true);
    g->GetYaxis()->CenterTitle(true);
    g->GetXaxis()->SetRangeUser(0.25,10);
    g->GetYaxis()->SetRangeUser(-14.5,-10.05);
    
/*adiciona os graficos principais*/
    g->Add(gstd);
    g->Add(gliv1); 
    g->Add(gliv2);
    g->Add(glivN);
    //printf("MAX e: %f\n", gre->GetYaxis()->GetXmax());

/*Desenha*/ 
    g->Draw("Al");

/*Legendas*/
    auto legend = new TLegend(0.7,0.9,0.85,0.8);
    legend->SetHeader("","C"); // option "C" allows to center the header
    legend->AddEntry(gstd,"STD","l");
    legend->AddEntry(gliv1,"1e-23","l");
    legend->AddEntry(gliv2,"2e-23","l");
    legend->AddEntry(glivN,"5e-23","l");
    legend->Draw();

    auto legend2 = new TLegend(0.1,0.1,0.37,0.2);
    legend2->SetHeader("Maximos ","C"); // option "C" allows to center the header
    legend2->AddEntry((TObject*)0,stdmax.c_str(),"");
    legend2->AddEntry((TObject*)0,liv1max.c_str(),"");
    legend2->AddEntry((TObject*)0,liv2max.c_str(),"");
    legend2->AddEntry((TObject*)0,livNmax.c_str(),"");
    legend2->Draw();

    legend->SetTextSize(0.025);
    legend2->SetTextSize(0.025);

    c9->SaveAs("./Graficos e Histogramas/ee/Flux/Fluxo_ee_ALL2.png");
}
