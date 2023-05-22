#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TSystem.h>

#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/FWLite/interface/FWLiteEnabler.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"


#include "DataFormats/CTPPSDetId/interface/CTPPSDetId.h"
#include "DataFormats/CTPPSDetId/interface/CTPPSPixelDetId.h"
#include "DataFormats/CTPPSReco/interface/CTPPSPixelRecHit.h"
#include "DataFormats/CTPPSReco/interface/CTPPSLocalTrackLite.h"
#include "DataFormats/Common/interface/DetSet.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h"

#include "filesA.C"
#include "filesB.C"
#include "filesC.C"
#include "filesD.C"

int main(int argc, char* argv[]) {
  // define what muon you are using; this is necessary as FWLite is not
  // capable of reading edm::Views

  // ----------------------------------------------------------------------
  // First Part:
  //
  //  * enable FWLite
  //  * book the histograms of interest
  //  * open the input file
  // ----------------------------------------------------------------------

  // load framework libraries
  gSystem->Load("libFWCoreFWLite");
  FWLiteEnabler::enable();

  // initialize command line parser
  optutl::CommandLineParser parser("Analyze FWLite Histograms");

  // set defaults
  parser.integerValue("maxEvents") = 1000000000;
  parser.integerValue("outputEvery") = 1000;
  //parser.stringValue("outputFile") = "pixelHistogramsRecHits"+run_+".root";

  // parse arguments
  parser.parseArguments(argc, argv);
  int maxEvents_ = parser.integerValue("maxEvents");
  unsigned int outputEvery_ = parser.integerValue("outputEvery");
  std::string outputFile_ = parser.stringValue("outputFile");
  std::vector<std::string> inputFiles_; // = parser.stringVector("inputFiles");
  int run_ = parser.integerValue("section");
  std::string outputname= "pixelHistogramsRecHits";
  //outputname.append(std::to_string(run_));
  outputname.append(".root");
  parser.stringValue("outputFile") = outputname.c_str();

  // Set lumisection range
  int MinLumiSection1 = 1;
  int MaxLumiSection1 = 10000;
  int MinLumiSection2 = 345000;
  int MaxLumiSection2 = 362000;

  float lumi_;

  if(run_<316996){
    addfilenamesA(run_,inputFiles_,lumi_);
  }
  else if(run_>316996 && run_<319311){
    addfilenamesB(run_,inputFiles_,lumi_);
  }
  else if(run_> 319312&& run_<320066){
    addfilenamesC(run_,inputFiles_,lumi_);
  }
  else if(run_> 320065){
    addfilenamesD(run_,inputFiles_,lumi_);
  }

  // book a set of histograms
  fwlite::TFileService fs = fwlite::TFileService(outputFile_);
  TFileDirectory dir = fs.mkdir("histograms");
  /*
  TH2F *trxy45210_ = dir.make<TH2F>("trxy45210","trxy45210",500,-5,25,500,-15,15);
  TH2F *trxy45220_ = dir.make<TH2F>("trxy45220","trxy45220",500,-5,25,500,-15,15);
  TH2F *trxy56210_ = dir.make<TH2F>("trxy56210","trxy56210",500,-5,25,500,-15,15);
  TH2F *trxy56220_ = dir.make<TH2F>("trxy56220","trxy56220",500,-5,25,500,-15,15);

  TH2F *xy45210pl0_ = dir.make<TH2F>("xy45210pl0","xy45210pl0",250,-15,15,250,-15,15);
  TH2F *xy45220pl0_ = dir.make<TH2F>("xy45220pl0","xy45220pl0",250,-15,15,250,-15,15);
  TH2F *xy56210pl0_ = dir.make<TH2F>("xy56210pl0","xy56210pl0",250,-15,15,250,-15,15);
  TH2F *xy56220pl0_ = dir.make<TH2F>("xy56220pl0","xy56220pl0",250,-15,15,250,-15,15);

  TH2F *xy45210pl1_ = dir.make<TH2F>("xy45210pl1","xy45210pl1",250,-15,15,250,-15,15);
  TH2F *xy45220pl1_ = dir.make<TH2F>("xy45220pl1","xy45220pl1",250,-15,15,250,-15,15);
  TH2F *xy56210pl1_ = dir.make<TH2F>("xy56210pl1","xy56210pl1",250,-15,15,250,-15,15);
  TH2F *xy56220pl1_ = dir.make<TH2F>("xy56220pl1","xy56220pl1",250,-15,15,250,-15,15);

  TH2F *xy45210pl2_ = dir.make<TH2F>("xy45210pl2","xy45210pl2",250,-15,15,250,-15,15);
  TH2F *xy45220pl2_ = dir.make<TH2F>("xy45220pl2","xy45220pl2",250,-15,15,250,-15,15);
  TH2F *xy56210pl2_ = dir.make<TH2F>("xy56210pl2","xy56210pl2",250,-15,15,250,-15,15);
  TH2F *xy56220pl2_ = dir.make<TH2F>("xy56220pl2","xy56220pl2",250,-15,15,250,-15,15);
  */
  TH2F *xy45210pl3_ = new TH2F("xy45210pl3","xy45210pl3",250,-15,15,250,-15,15);
  TH2F *xy45220pl3_ = new TH2F("xy45220pl3","xy45220pl3",250,-15,15,250,-15,15);
  TH2F *xy56210pl3_ = new TH2F("xy56210pl3","xy56210pl3",250,-15,15,250,-15,15);
  TH2F *xy56220pl3_ = new TH2F("xy56220pl3","xy56220pl3",250,-15,15,250,-15,15);
  /*
  TH2F *xy45210pl4_ = dir.make<TH2F>("xy45210pl4","xy45210pl4",250,-15,15,250,-15,15);
  TH2F *xy45220pl4_ = dir.make<TH2F>("xy45220pl4","xy45220pl4",250,-15,15,250,-15,15);
  TH2F *xy56210pl4_ = dir.make<TH2F>("xy56210pl4","xy56210pl4",250,-15,15,250,-15,15);
  TH2F *xy56220pl4_ = dir.make<TH2F>("xy56220pl4","xy56220pl4",250,-15,15,250,-15,15);

  TH2F *xy45210pl5_ = dir.make<TH2F>("xy45210pl5","xy45210pl5",250,-15,15,250,-15,15);
  TH2F *xy45220pl5_ = dir.make<TH2F>("xy45220pl5","xy45220pl5",250,-15,15,250,-15,15);
  TH2F *xy56210pl5_ = dir.make<TH2F>("xy56210pl5","xy56210pl5",250,-15,15,250,-15,15);
  TH2F *xy56220pl5_ = dir.make<TH2F>("xy56220pl5","xy56220pl5",250,-15,15,250,-15,15);
  */
  TH1F *ls = dir.make<TH1F>("ls","ls",2000,0,2000);
  
  TH1F *th1fin45210 = dir.make<TH1F>("th1fin","th1fin",11001,314999.5,326000.5);
  TH1F *th1fin45220 = dir.make<TH1F>("th1fin","th1fin",11001,314999.5,326000.5);
  TH1F *th1fin56210 = dir.make<TH1F>("th1fin","th1fin",11001,314999.5,326000.5);
  TH1F *th1fin56220 = dir.make<TH1F>("th1fin","th1fin",11001,314999.5,326000.5);

  // loop the events
  int ievt = 0;

  int lumiblock_ = -99;

  for (unsigned int iFile = 0; iFile < inputFiles_.size(); ++iFile) {
    // open input file (can be located on castor)
    TFile* inFile = TFile::Open(inputFiles_[iFile].c_str());
    if (inFile) {
      std::cout << "Opening " << inputFiles_[iFile].c_str() << std::endl;
      // ----------------------------------------------------------------------
      // Second Part:
      //
      //  * loop the events in the input file
      //  * receive the collections of interest via fwlite::Handle
      //  * fill the histograms
      //  * after the loop close the input file
      // ----------------------------------------------------------------------
      fwlite::Event ev(inFile);
      for (ev.toBegin(); !ev.atEnd(); ++ev, ++ievt) {
        edm::EventBase const& event = ev;
        // break loop if maximal number of events is reached
        if (maxEvents_ > 0 ? ievt + 1 > maxEvents_ : false)
          break;
        // simple event counter
        if (outputEvery_ != 0 ? (ievt > 0 && ievt % outputEvery_ == 0) : false)
          std::cout << "  processing event: " << ievt << std::endl;

	lumiblock_ = ev.luminosityBlock();

	if((lumiblock_ < MinLumiSection1 || lumiblock_ > MaxLumiSection2) || (lumiblock_>MaxLumiSection1 && lumiblock_<MinLumiSection2))
	  continue;
	
	//        BX = ev.bunchCrossing();
        int passhlt = 0;

	edm::Handle<edm::TriggerResults> hltResults;
        event.getByLabel(edm::InputTag("TriggerResults","","HLT"),hltResults);
        const edm::TriggerNames & trigNames = event.triggerNames(*hltResults);
        for(unsigned int i=0; i<trigNames.size();i++)
          {
	    // Lumi = 0.099170851 nb-1
	    std::string TriggerName = trigNames.triggerName(i);
            if((hltResults->accept(i)>0)&&(TriggerName == "HLT_ZeroBias_v6"))
              passhlt=1;
          }

        if(passhlt==0)
          continue;

	ls->Fill(lumiblock_);

	edm::Handle<std::vector<CTPPSLocalTrackLite> > ppstracks;
        // Use this for running on standard Physics AOD                                                                                                                 
        event.getByLabel(std::string("ctppsLocalTrackLiteProducer"), ppstracks);
	/*
        for (std::vector<CTPPSLocalTrackLite>::const_iterator track0 = ppstracks->begin(); track0 != ppstracks->end(); ++track0)
          {
            if(track0->rpId() == 2014838784)
              {
                trxy45210_->Fill(track0->x(),track0->y());
              }
            if(track0->rpId() == 2031616000)
              {
                trxy56210_->Fill(track0->x(),track0->y());
              }
            if(track0->rpId() == 2040004608)
	      {
		trxy56220_->Fill(track0->x(),track0->y());
	      }
            if(track0->rpId() == 2023227392)
              {
                trxy45220_->Fill(track0->x(),track0->y());
              }
          }
	*/

	edm::Handle< edm::DetSetVector<CTPPSPixelRecHit> > pixelRecHits;
	event.getByLabel(std::string("ctppsPixelRecHits"), pixelRecHits);

	for ( const auto& rechits_ds : *pixelRecHits ) 
	  {
	    const CTPPSPixelDetId detidforrh( rechits_ds.detId() );
	    for ( const auto& rechit : rechits_ds ){ 
	      
                int arm = detidforrh.arm();                                                                               
		int plane = detidforrh.plane();                                                                           
		int station = detidforrh.station();

                //cout<<ev<<"  "<<arm<<"  "<<plane<<"  "<<station<<"  "<<rechit.point().x()<<"  "<<rechit.point().y()<<endl;

		if(arm == 0 && station == 0)
		  {
		    /*
		    if(plane == 0)
		      xy45210pl0_->Fill(rechit.point().x(),rechit.point().y());
		    if(plane == 1)
                      xy45210pl1_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 2)
                      xy45210pl2_->Fill(rechit.point().x(),rechit.point().y());
		    */
                    if(plane == 3)
                      xy45210pl3_->Fill(rechit.point().x(),rechit.point().y());
		    /*
                    if(plane == 4)
                      xy45210pl4_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 5)
                      xy45210pl5_->Fill(rechit.point().x(),rechit.point().y());
		    */
		  }
		if(arm == 0 && station == 2)
		  {
		    /*
		    if(plane == 0)
		      xy45220pl0_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 1)
                      xy45220pl1_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 2)
                      xy45220pl2_->Fill(rechit.point().x(),rechit.point().y());
		    */
                    if(plane == 3)
                      xy45220pl3_->Fill(rechit.point().x(),rechit.point().y());
		    /*
                    if(plane == 4)
                      xy45220pl4_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 5)
                      xy45220pl5_->Fill(rechit.point().x(),rechit.point().y());
		    */
		  }
                if(arm == 1 && station == 0)
                  {
		    /*
		    if(plane == 0)
		      xy56210pl0_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 1)
                      xy56210pl1_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 2)
                      xy56210pl2_->Fill(rechit.point().x(),rechit.point().y());
		    */
                    if(plane == 3)
                      xy56210pl3_->Fill(rechit.point().x(),rechit.point().y());
		    /*
                    if(plane == 4)
                      xy56210pl4_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 5)
                      xy56210pl5_->Fill(rechit.point().x(),rechit.point().y());
		    */
                  }
                if(arm == 1 && station == 2)
                  {
		    /*
		    if(plane == 0)
		      xy56220pl0_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 1)
                      xy56220pl1_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 2)
                      xy56220pl2_->Fill(rechit.point().x(),rechit.point().y());
		    */
                    if(plane == 3)
                      xy56220pl3_->Fill(rechit.point().x(),rechit.point().y());
		    /*
                    if(plane == 4)
                      xy56220pl4_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 5)
                      xy56220pl5_->Fill(rechit.point().x(),rechit.point().y());
		    */
                  }
	      }
	  }
      }

      // close input file
      inFile->Close();
    }
    // break loop if maximal number of events is reached:
    // this has to be done twice to stop the file loop as well
    if (maxEvents_ > 0 ? ievt + 1 > maxEvents_ : false)
      break;

    // close input file                                                                                                                                                                                  
    //inFile->Close();
  }

  Float_t lumiscaled = 1000.0*1000.0/lumi_; // 1 fb-1                                                                                                                                                    
  Float_t areascale = 27777.778; // 30mm/500 bins => cm2                                                                                                                                                 
  Float_t totalscale = lumiscaled*areascale/1E14; // p/cm2/fb-1 * 1E14                                                                                                                                   

  int x1=4;
  int x2=4;
  int y1=-11;
  int y2=8;

  double Mean45210=0;
  double Mean45220=0;
  double Mean56210=0;
  double Mean56220=0;

  for(int i=0;i<50;i++){
    for(int j=0;j<50;j++){
      Mean45210+=xy45210pl3_->GetBinContent(xy45210pl3_->GetXaxis()->FindBin(x1)+i,xy45210pl3_->GetYaxis()->FindBin(y1)+j);
      Mean56210+=xy56210pl3_->GetBinContent(xy56210pl3_->GetXaxis()->FindBin(x1)+i,xy56210pl3_->GetYaxis()->FindBin(y1)+j);
      Mean45220+=xy45220pl3_->GetBinContent(xy45220pl3_->GetXaxis()->FindBin(x2)+i,xy45220pl3_->GetYaxis()->FindBin(y2)+j);
      Mean56220+=xy56220pl3_->GetBinContent(xy56220pl3_->GetXaxis()->FindBin(x2)+i,xy56220pl3_->GetYaxis()->FindBin(y2)+j);
    }
  }

  Mean45210=Mean45210/2500;
  Mean45220=Mean45220/2500;
  Mean56210=Mean56210/2500;
  Mean56220=Mean56220/2500;

  double Mean45210err = Mean45210/50;
  double Mean45220err = Mean45220/50;                                                                                                                                                                  
  double Mean56210err = Mean56210/50;                                                                                                                                                                  
  double Mean56220err = Mean56220/50;                                                                                                                                                                  

  th1fin45210->SetBinContent(run_-314999,Mean45210*totalscale);
  th1fin45210->SetBinError(run_-314999,Mean45210err*totalscale);
  th1fin45220->SetBinContent(run_-314999,Mean45220*totalscale);
  th1fin45220->SetBinError(run_-314999,Mean45220err*totalscale);
  th1fin56210->SetBinContent(run_-314999,Mean56210*totalscale);
  th1fin56210->SetBinError(run_-314999,Mean56210err*totalscale);
  th1fin56220->SetBinContent(run_-314999,Mean56220*totalscale);
  th1fin56220->SetBinError(run_-314999,Mean56220err*totalscale);

  cout<<"bin: "<<run_-31499<<endl;
  cout<<"Mean: "<<Mean45210<<endl;
  cout<<"err: "<<Mean45210err<<endl;
  cout<<"Content: "<<Mean45210*totalscale<<endl;
  cout<<"Error: "<<Mean45210err*totalscale<<endl;
  
  delete xy45210pl3_;
  delete xy45220pl3_;
  delete xy56210pl3_;
  delete xy56220pl3_;


  return 0;}

