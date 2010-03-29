#include "PFAnalyses/CommonTools/interface/FWLiteTreeAnalyzer.h"
#include "PFAnalyses/Z/interface/TestAnalyzer.h"
#include "PFAnalyses/Z/interface/TestHistograms.h"
#include "PFAnalyses/Z/interface/PFElectronSelector.h"

#include "DataFormats/Math/interface/LorentzVector.h"

#include "FWCore/Utilities/interface/Algorithms.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include <TMath.h>
#include <bitset>



TestAnalyzer:: TestAnalyzer(const std::string & aName):FWLiteAnalyzer(aName){}



TestAnalyzer::~TestAnalyzer(){

  std::cout<<"TestAnalyzer::~TestAnalyzer()"<<std::endl;

  delete myHistos_;

}


void TestAnalyzer::initialize(const edm::ParameterSet& ps, 
				    const TFileDirectory& aDir,
				    std::strbitset *aSelections){


  minElePt_ =   ps.getUntrackedParameter<double>("minElePt",5.); 
  maxEleEta_ = ps.getUntrackedParameter<double>("maxEleEta",3.);
  patElectronsLabel_ =  ps.getParameter<edm::InputTag>("patElectronsLabel");
  electronSelector_.initialize( ps.getParameter<edm::ParameterSet>("electronSelector") ); 


  ///The histograms for this analyzer will be saved into "TestHistos"
  ///directory of the ROOT file
  myHistos_ = new TestHistograms(&aDir);

  mySelections_ = aSelections;

  registerCuts();

}



void TestAnalyzer::registerCuts(){

  std::string labels[1] = {"PF"};
  for(int i =0;i<1;++i){  
    //mySelections_->push_back("All electrons |#eta<2.4|"+labels[i]);     
    mySelections_->push_back("Minimum electron p_{T}"+labels[i]);   
  }
}



bool TestAnalyzer::analyze(const edm::EventBase& iEvent){

  //std::cout<<iEvent.id()<<std::endl;

  using namespace reco;

  float eventWeight = 1.0;

  clear();

  iEvent.getByLabel(patElectronsLabel_,patElectrons_);
  typedef pat::ElectronCollection::const_iterator EI;

  checkSelections(iEvent, "PF");  
  
  size_t size =  patElectrons_->size();
  eleMultiplicity_ = size;

  for(EI ei = patElectrons_->begin(); ei!=patElectrons_->end(); ++ei)  {    

    std::strbitset eleSel = electronSelector_.getBitTemplate();
    bool passed = electronSelector_( *ei, eleSel ); 

    if( passed ) myHistos_->fill1DHistogram("hElectronEt",ei->et(), eventWeight);
  }


  return true;
}



bool  TestAnalyzer::checkSelections(const edm::EventBase& iEvent, const std::string & type){

  //mySelections_->set("All electrons |#eta<2.4|"+type, true );
  mySelections_->set("Minimum electron p_{T}"+type, patElectrons_->size() && (*patElectrons_)[patElectrons_->size()-1].pt()>minElePt_ );

  return true;
}


void  TestAnalyzer::addBranch(TTree *tree){

  tree->Branch("eleMultiplicityPF",&eleMultiplicity_);

}



void  TestAnalyzer::addCutHistos(TList *aList){

  aList->Add(new TH1F("heleMultiplicityPF",";PF electrons multiplicity;Events",21,-0.5,20.5));

}



void TestAnalyzer::clear(){

  eleMultiplicity_ = 0;

}
