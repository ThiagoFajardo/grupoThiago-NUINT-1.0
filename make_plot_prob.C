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

void make_plot_prob(){

    auto c2 = new TCanvas("c2","Probabilidade",700,500);
    c2->SetGrid();
    //c2->SetLogx();

    auto gstd  = new TGraph("./Datas/ee/prob/21/Prob_STD.dat");
    auto gliv1 = new TGraph("./Datas/ee/prob/21/Prob_LIV1.dat");
    auto gliv2  = new TGraph("./Datas/ee/prob/21/Prob_LIV2.dat");
    auto glivN  = new TGraph("./Datas/ee/prob/21/Prob_LIVN.dat");


    //gstd->SetLineStyle(7);
    gliv1->SetLineStyle(7);
    gliv2->SetLineStyle(7);
    glivN->SetLineStyle(7);

    gstd->SetLineColor(kBlue);
    gstd->SetLineWidth(2);

    gliv1->SetLineColor(kRed);
    gliv1->SetLineWidth(2);

    gliv2->SetLineColor(kBlack);
    gliv2->SetLineWidth(2);

    glivN->SetLineColor(6);
    gstd->SetLineWidth(2);


    //double mumax = TMath::MaxElement(gstd->GetN(),gstd->GetY());
    //double emax = TMath::MaxElement(gliv1->GetN(),gliv1->GetY());
    //double taumax = TMath::MaxElement(gliv2->GetN(),gliv2->GetY());
    //printf("MAX mu: %f\n", mumax);
    //printf("MAX e: %f\n", emax);
    //printf("MAX tau: %f\n", taumax);

    auto *g = new TMultiGraph();

    //string mumax = "Max Muon: " + to_string(TMath::MaxElement(gstd->GetN(),gstd->GetY()));
    
    g->SetTitle("Probabilidade Muon (Matter);Energy (GeV);Oscillation probability");
    g->GetXaxis()->SetLimits(0.25,10.0);
    g->GetXaxis()->SetRangeUser(0.25,10.0);
    g->GetYaxis()->SetRangeUser(0,1);
    g->Add(gstd);
    g->Add(gliv1);
    g->Add(gliv2);
    g->Add(glivN);

    g->Draw("Al");

    auto legend = new TLegend(0.7,0.9,0.85,0.8);
    legend->SetHeader("Probability","C"); // option "C" allows to center the header
    legend->AddEntry(gstd,"STD->Eletron","l");
    legend->AddEntry(gliv1,"LIV1->Eletron","l");
    legend->AddEntry(gliv2,"LIV2->Eletron","l");
    legend->AddEntry(glivN,"LIV5->Eletron","l");
    legend->Draw();

    //auto legend2 = new TLegend(0.1,0.1,0.37,0.2);
    //legend2->SetHeader("Maximos ","C"); // option "C" allows to center the header
    //legend2->AddEntry((TObject*)0,mumax.c_str(),"");
    //legend2->Draw();

    legend->SetTextSize(0.022);
    //legend2->SetTextSize(0.025);

    c2->SaveAs("./Graficos e Histogramas/ee/prob/21/Prob_ee_ALL.png");
}
