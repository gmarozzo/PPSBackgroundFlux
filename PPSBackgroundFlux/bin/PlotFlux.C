#include<string>
void PlotFlux(int run=315557, int tracks=1, int rebin=1)
{
  gStyle->SetOptStat(0);
  gStyle->SetPadRightMargin(0.25);
  //  gStyle->SetPalette(105);
  //  gStyle->SetLogz();

  TFile *f,*f2;
 
  std::string filename = "pixelHistogramsRecHits"+std::to_string(run)+".root";
  

    f = TFile::Open(filename.c_str());
    f2 = TFile::Open("pixelHistogramsRecHits315790.root");
    /*
  if(run==1)
    f = TFile::Open("/eos/cms/store/user/jjhollar/PPSHLLHCTimingSimulation/PixelRun2data/pixelHistograms_Run319678_LS49to294.root");
  if(run==2)
    f = TFile::Open("/eos/cms/store/user/jjhollar/PPSHLLHCTimingSimulation/PixelRun2data/pixelHistograms_Run315764_LS69to309.root");
  if(run==3)
    f = TFile::Open("/eos/cms/store/user/jjhollar/PPSHLLHCTimingSimulation/PixelRun2data/pixelHistograms_Run315790_LS700to898.root");
  if(run==4)
    f = TFile::Open("/eos/cms/store/user/jjhollar/PPSHLLHCTimingSimulation/PixelRun2data/pixelHistograms_Run315557_LS1to279.root");
    //f = TFile::Open("pixelHistograms_Run315557_LS1to279.root");
    */

  TH2F *h45210tr;
  TH2F *h45220tr;
  TH2F *h56210tr;
  TH2F *h56220tr;

  TH2F *h45210tr2;
  TH2F *h45220tr2;
  TH2F *h56210tr2;
  TH2F *h56220tr2;

  if(tracks==1)
    {
      h45210tr = (TH2F *)f->Get("histograms/trxy45210");
      h45220tr = (TH2F *)f->Get("histograms/trxy45220");
      h56210tr = (TH2F *)f->Get("histograms/trxy56210");
      h56220tr = (TH2F *)f->Get("histograms/trxy56220");

      h45210tr2 = (TH2F *)f2->Get("histograms/trxy45210");
      h45220tr2 = (TH2F *)f2->Get("histograms/trxy45220");
      h56210tr2 = (TH2F *)f2->Get("histograms/trxy56210");
      h56220tr2 = (TH2F *)f2->Get("histograms/trxy56220");
    }

  if(tracks==0)
    {
      h45210tr = (TH2F *)f->Get("histograms/xy45210pl3");                                                                                                           
      h45220tr = (TH2F *)f->Get("histograms/xy45220pl3");                                                                                                           
      h56210tr = (TH2F *)f->Get("histograms/xy56210pl3");                                                                                                           
      h56220tr = (TH2F *)f->Get("histograms/xy56220pl3");

      h45210tr2 = (TH2F *)f2->Get("histograms/xy45210pl3");                                                                                                           
      h45220tr2 = (TH2F *)f2->Get("histograms/xy45220pl3");                                                                                                           
      h56210tr2 = (TH2F *)f2->Get("histograms/xy56210pl3");                                                                                                           
      h56220tr2 = (TH2F *)f2->Get("histograms/xy56220pl3");                                                                                                           
    }

  TH2F *hflux45210 = new TH2F("hflux45210","hflux45210",30,-5,25,30,-15,15);
  TH2F *hflux45220 = new TH2F("hflux45220","hflux45220",30,-5,25,30,-15,15);
  TH2F *hflux56210 = new TH2F("hflux56210","hflux56210",30,-5,25,30,-15,15);
  TH2F *hflux56220 = new TH2F("hflux56220","hflux56220",30,-5,25,30,-15,15);

  Float_t lumi=1.0;
  if(run==315557)
    lumi = 0.164895489; // nb-1
  if(run==315790)
    lumi = 0.083389021; // nb-1
  if(run==315764)
    lumi = 0.139944577; // nb-1
  if(run==319678)
    lumi = 0.097165727; // nb-1
  if(run==324785)
    lumi = 0.200268051; // nb-1
  if(run==318877)
    lumi = 0.174206803; // nb-1
  if(run==323423)
    lumi = 0.022688383; // nb-1
  if(run==320673)
    lumi = 0.2823881112; // nb-1
  if(run==319310)
    lumi = 0.000004671; // nb-1
  if(run==315257)
    lumi = 0.016579999; // nb-1
  if(run==321975)
    lumi = 0.157500565; // nb-1

  if(run==324897)
    lumi = 0.054610472; // nb-1
  if(run==319657)
    lumi = 0.055736101; // nb-1
  if(run==324997)
    lumi = 0.045257540; // nb-1
  if(run==316058)
    lumi = 0.263421273; // nb-1
  if(run==317661)
    lumi = 0.524110704; // nb-1

  if(run==6)
    lumi = 0.026984394; // nb-1
  if(run==7)
    lumi = 0.041171361; // nb-1
  if(run==8)
    lumi = 0.054241549; // nb-1
  if(run==9)
    lumi = 0.036881271; // nb-1
  if(run==10)
    lumi = 0.063921057; // nb-1
  if(run==11)
    lumi = 0.045406165; // nb-1
  if(run==12)
    lumi = 0.039223269; // nb-1
  if(run==13)
    lumi = 0.041159815; // nb-1
  if(run==14)
    lumi = 0.038562871; // nb-1
  if(run==15)
    lumi = 0.040431654; // nb-1
  if(run==16)
    lumi = 0.042061339; // nb-1
  if(run==17)
    lumi = 0.033874181; // nb-1
  if(run==18)
    lumi = 0.033638402; // nb-1
  if(run==19)
    lumi = 0.003714879; // nb-1

  if(run==212)
    lumi = 0.066966415; // nb-1
  if(run==213)
    lumi = 0.09045041; 
  if(run==214)
    lumi = 0.078636603;
  if(run==215)
    lumi = 0.082128723;
  if(run==216)
    lumi = 0.092108967;
  if(run==217)
    lumi = 0.059154964;
  if(run==218)
    lumi = 0.010232743;

  Float_t lumiscaled = 1000.0*1000.0/lumi; // 1 fb-1
  Float_t areascale = 27777.778; // 30mm/500 bins => cm2
  Float_t totalscale = lumiscaled*areascale/1E14; // p/cm2/fb-1 * 1E14

  Float_t lumiscaled2 = 1000.0*1000.0/0.083389021;
  Float_t totalscale2 = lumiscaled2*areascale/1E14; // p/cm2/fb-1 * 1E14

  for(Int_t x = -5; x < 25; x++)
    {
      for(Int_t y = -15; y < 15; y++)
	{
	  Float_t ntr = h45220tr->Integral(h45220tr->GetXaxis()->FindBin(x),
					   h45220tr->GetXaxis()->FindBin(x+1),
					   h45220tr->GetYaxis()->FindBin(y),
					   h45220tr->GetYaxis()->FindBin(y+1));
	  Float_t theflux = ntr*lumiscaled*100/1E15; 
	  hflux45220->SetBinContent(hflux45220->GetXaxis()->FindBin(x),hflux45220->GetYaxis()->FindBin(y),theflux);

	  // 45-210
	  ntr = h45210tr->Integral(h45210tr->GetXaxis()->FindBin(x),
				   h45210tr->GetXaxis()->FindBin(x+1),
				   h45210tr->GetYaxis()->FindBin(y),
				   h45210tr->GetYaxis()->FindBin(y+1));
          theflux = ntr*lumiscaled*100/1E15;
          hflux45210->SetBinContent(hflux45210->GetXaxis()->FindBin(x),hflux45210->GetYaxis()->FindBin(y),theflux);

          // 56-220                                                                                                                                                  
          ntr = h56220tr->Integral(h56220tr->GetXaxis()->FindBin(x),
                                   h56220tr->GetXaxis()->FindBin(x+1),
                                   h56220tr->GetYaxis()->FindBin(y),
                                   h56220tr->GetYaxis()->FindBin(y+1));
          theflux = ntr*lumiscaled*100/1E15;
          hflux56220->SetBinContent(hflux56220->GetXaxis()->FindBin(x),hflux56220->GetYaxis()->FindBin(y),theflux);

	  // 56-210                                                                                                                                                  
          ntr = h56210tr->Integral(h56210tr->GetXaxis()->FindBin(x),
                                   h56210tr->GetXaxis()->FindBin(x+1),
                                   h56210tr->GetYaxis()->FindBin(y),
                                   h56210tr->GetYaxis()->FindBin(y+1));
          theflux = ntr*lumiscaled*100/1E15;
          hflux56210->SetBinContent(hflux56210->GetXaxis()->FindBin(x),hflux56210->GetYaxis()->FindBin(y),theflux);

	}
    }

  Int_t rebinning = rebin;
  Float_t rebinscale = 1.0*rebinning*rebinning;

  TFile *output = new TFile("output3.root","RECREATE");

  float x1,x2,y1,y2;

  if(tracks==1){
    x1=5;
    x2=20;
    y1=-10;
    y2=-10;
  }
  if(tracks==0){
    x1=4;
    x2=4;
    y1=-11;
    y2=8;
  }


  TCanvas *c2 = new TCanvas("c2","c2",800,800);
  c2->SetLogz();
  c2->Divide(2,2);
  c2->cd(1);
  gPad->SetLogz();
  h45210tr->SetTitle("p/cm2/fb^{-1} *10^{14}, 45-210");
  h45210tr->Scale((Float_t)totalscale/rebinscale);
  h45210tr2->Scale((Float_t)totalscale2/rebinscale);
  //h45210tr->SetMaximum(2);
  h45210tr2->SetMaximum(2);
  h45210tr->SetMinimum(0.0001);
  //h45210tr->Add(h45210tr2,-1);
  h45210tr = (TH2F*) h45210tr->Rebin2D(rebinning,rebinning);
  h45210tr->SetXTitle("x [mm]");
  h45210tr->SetYTitle("y [mm]");
  h45210tr->DrawCopy("colz");
  //h45210tr->ProjectionY()->DrawCopy();
  
  TLine *line1 = new TLine(x1,y1,x1+3,y1);
  line1->SetLineColor(kRed);
  line1->SetLineWidth(6);
  line1->Draw("same");
  TLine *line2 = new TLine(x1,y1,x1,y1+3);
  line2->SetLineColor(kRed);
  line2->SetLineWidth(6);
  line2->Draw("same");
  TLine *line3 = new TLine(x1,y1+3,x1+3,y1+3);
  line3->SetLineColor(kRed);
  line3->SetLineWidth(6);
  line3->Draw("same");
  TLine *line4 = new TLine(x1+3,y1,x1+3,y1+3);
  line4->SetLineColor(kRed);
  line4->SetLineWidth(6);
  line4->Draw("same");
  
  
  c2->cd(2);
  gPad->SetLogz();
  h45220tr->SetTitle("p/cm2/fb^{-1} *10^{14}, 45-220");
  h45220tr->Scale(totalscale/rebinscale);
  h45220tr2->Scale(totalscale2/rebinscale);
  //h45220tr->SetMaximum(2);
  h45220tr2->SetMaximum(2);
  h45220tr->SetMinimum(0.0001);
  //h45220tr->Add(h45220tr2,-1);
  h45220tr->SetXTitle("x [mm]");
  h45220tr->SetYTitle("y [mm]");
  h45220tr->Rebin2D(rebinning,rebinning)->DrawCopy("colz");
  //h45220tr->Rebin2D(rebinning,rebinning)->ProjectionY()->DrawCopy();

  TLine *line5 = new TLine(x2,y2,x2+3,y2);
  line5->SetLineColor(kRed);
  line5->SetLineWidth(6);
  line5->Draw("same");
  TLine *line6 = new TLine(x2,y2,x2,y2+3);
  line6->SetLineColor(kRed);
  line6->SetLineWidth(6);
  line6->Draw("same");
  TLine *line7 = new TLine(x2,y2+3,x2+3,y2+3);
  line7->SetLineColor(kRed);
  line7->SetLineWidth(6);
  line7->Draw("same");
  TLine *line8 = new TLine(x2+3,y2,x2+3,y2+3);
  line8->SetLineColor(kRed);
  line8->SetLineWidth(6);
  line8->Draw("same");

  c2->cd(3);
  gPad->SetLogz();
  h56210tr->SetTitle("p/cm2/fb^{-1} *10^{14}, 56-210");
  h56210tr->Scale(totalscale/rebinscale);
  h56210tr2->Scale(totalscale2/rebinscale);
  //h56210tr->SetMaximum(2);
  h56210tr2->SetMaximum(2);
  h56210tr->SetMinimum(0.0001);
  //h56210tr->Add(h56210tr2,-1);
  h56210tr->SetXTitle("x [mm]");
  h56210tr->SetYTitle("y [mm]");
  h56210tr->Rebin2D(rebinning,rebinning)->DrawCopy("colz");

  line1->Draw("same");
  line2->Draw("same");
  line3->Draw("same");
  line4->Draw("same");

  c2->cd(4);
  gPad->SetLogz();
  h56220tr->SetTitle("p/cm2/fb^{-1} *10^{14}, 56-220");
  h56220tr->Scale(totalscale/rebinscale);
  h56220tr2->Scale(totalscale2/rebinscale);
  //h56220tr->SetMaximum(2);
  h56220tr2->SetMaximum(2);
  h56220tr->SetMinimum(0.0001);
  //h56220tr->Add(h56220tr2,-1);
  h56220tr->SetXTitle("x [mm]");
  h56220tr->SetYTitle("y [mm]");
  h56220tr->Rebin2D(rebinning,rebinning)->DrawCopy("colz");
  //h56220tr->Rebin2D(rebinning,rebinning)->ProjectionY()->DrawCopy();
  line5->Draw("same");
  line6->Draw("same");
  line7->Draw("same");
  line8->Draw("same");

  double Mean45210, Mean45220, Mean56210, Mean56220;
  
  for(int i=0;i<50;i++){
    for(int j=0;j<50;j++){
      Mean45210+=h45210tr->GetBinContent(h45210tr->GetXaxis()->FindBin(x1)+i,h45210tr->GetYaxis()->FindBin(y1)+j);
      Mean56210+=h56210tr->GetBinContent(h56210tr->GetXaxis()->FindBin(x1)+i,h56210tr->GetYaxis()->FindBin(y1)+j);
      Mean45220+=h45220tr->GetBinContent(h45220tr->GetXaxis()->FindBin(x2)+i,h45220tr->GetYaxis()->FindBin(y2)+j);
      Mean56220+=h56220tr->GetBinContent(h56220tr->GetXaxis()->FindBin(x2)+i,h56220tr->GetYaxis()->FindBin(y2)+j);
    }
  }

  Mean45210=Mean45210/2500;
  Mean45220=Mean45220/2500;
  Mean56210=Mean56210/2500;
  Mean56220=Mean56220/2500;

  double Mean45210err = sqrt(Mean45210*0.00027777/lumi)/50;
  double Mean45220err = sqrt(Mean45220*0.00027777/lumi)/50;
  double Mean56210err = sqrt(Mean56210*0.00027777/lumi)/50;
  double Mean56220err = sqrt(Mean56220*0.00027777/lumi)/50;

  cout<<"45-210: "<<Mean45210<<" +- "<<Mean45210err<<endl;
  cout<<"45-220: "<<Mean45220<<" +- "<<Mean45220err<<endl;
  cout<<"56-210: "<<Mean56210<<" +- "<<Mean56210err<<endl;
  cout<<"56-220: "<<Mean56220<<" +- "<<Mean56220err<<endl;

  double xtest = 5;
  cout<<endl;
  cout<<"Integrale 45210: "<<h45210tr->Integral()<<endl;
  cout<<"Integrale 45220: "<<h45220tr->Integral()<<endl;
  cout<<"Integrale 56210: "<<h56210tr->Integral()<<endl;
  cout<<"Integrale 56220: "<<h56220tr->Integral()<<endl; 

  string plottype;
  if(tracks==1) plottype = "tracks";
  else plottype = "pixelsplane1";
  string p_png = "plots/"+to_string(run)+plottype+".png";
  c2->Print(p_png.c_str());

  h45210tr->Write();
  h45220tr->Write();
  h56210tr->Write();
  h56220tr->Write();}

    
