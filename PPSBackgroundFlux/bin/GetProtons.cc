#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

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

#include "filenames.C"

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
  parser.integerValue("outputEvery") = 10;
  parser.stringValue("outputFile") = "protons.root";

  // parse arguments
  parser.parseArguments(argc, argv);
  int maxEvents_ = parser.integerValue("maxEvents");
  unsigned int outputEvery_ = parser.integerValue("outputEvery");
  std::string outputFile_ = parser.stringValue("outputFile");
  std::vector<std::string> inputFiles_; // = parser.stringVector("inputFiles");

  // Set lumisection range
  int MinLumiSection1 = 1;
  int MaxLumiSection1 = 30000;
  int MinLumiSection2 = 350000;
  int MaxLumiSection2 = 360000;


  addfilenames(315557,inputFiles_);

  // book a set of histograms
  fwlite::TFileService fs = fwlite::TFileService(outputFile_);
  TH1F *xi45 = dir.make<TH1F>("xi45","xi45",10000,0,0.3);
  TH1F *xi56 = dir.make<TH1F>("xi56","xi56",10000,0,0.3);
  TH1F *mult45 = dir.make<TH1F>("mult45","mult45",11,-0.5,10.5);
  TH1F *mult56 = dir.make<TH1F>("mult56","mult56",11,-0.5,10.5);

  
  TFileDirectory dir = fs.mkdir("histograms");

  TH1F *ls = dir.make<TH1F>("ls","ls",2000,0,2000);

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

	edm::Handle<std::vector<recoForwardProton> > protons;
        // Use this for running on standard Physics AOD                                                                                                                 
        event.getByLabel(std::string("multiRP"), protons);
        for (std::vector<recoForwardProton>::const_iterator proton0 = protons->begin(); proton0 != protons->end(); ++proton0)
          {
            if(proton0.lhcSector()==proton0.LHCSector::sector45){
              xi45->Fill(proton0.xi());
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
  }
  return 0;}

