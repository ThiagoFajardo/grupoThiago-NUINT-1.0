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

void make_prob_solo(){

    auto c2 = new TCanvas("c2","Probabilidade",700,500);
    c2->SetGrid();
    //c2->SetLogx();

    auto g  = new TGraph("./Datas/ee/prob/21/Prob_LIVN.dat");


    g->SetLineStyle(9);
    //grtau->SetLineStyle(7);
    //gre->SetLineStyle(7);
    
    g->SetLineColor(kRed);
    g->SetLineWidth(2);

    //gre->SetLineColor(kRed);
    //gre->SetLineWidth(2);
    //grtau->SetLineColor(kGreen);
    //grtau->SetLineWidth(2);

    //double mumax = TMath::MaxElement(grmu->GetN(),grmu->GetY());
    //double emax = TMath::MaxElement(gre->GetN(),gre->GetY());
    //double taumax = TMath::MaxElement(grtau->GetN(),grtau->GetY());
    //printf("MAX mu: %f\n", mumax);
    //printf("MAX e: %f\n", emax);
    //printf("MAX tau: %f\n", taumax);

    //auto *grmu = new TMultiGraph();

    //string mumax = "Max Muon: " + to_string(TMath::MaxElement(grmu->GetN(),grmu->GetY()));
    
    g->SetTitle("Probability Muon LIV5(Matter);Energy (GeV);Oscillation probability");
    g->GetXaxis()->SetLimits(0.25,10.0);
    g->GetXaxis()->SetRangeUser(0.25,10.0);
    g->GetYaxis()->SetRangeUser(0,1);
    //grmu->Add(grmu);
    //grmu->Add(grtau);
    //grmu->Add(gre);
    
    g->Draw("Al");

    auto legend = new TLegend(0.7,0.9,0.85,0.8);
    legend->SetHeader("Probability LIV5","C"); // option "C" allows to center the header
    legend->AddEntry(g,"Muon->Eletron","l");
    //legend->AddEntry(gre,"Muon->Eletron","l");
    //legend->AddEntry(grtau,"Muon->Tau","l");
    legend->Draw();

    //auto legend2 = new TLegend(0.1,0.1,0.37,0.2);
    //legend2->SetHeader("Maximos ","C"); // option "C" allows to center the header
    //legend2->AddEntry((TObject*)0,mumax.c_str(),"");
    //legend2->Draw();

    legend->SetTextSize(0.022);
    //legend2->SetTextSize(0.025);

    c2->SaveAs("./Graficos e Histogramas/ee/prob/21/Prob_ee_LIVN.png");
}
