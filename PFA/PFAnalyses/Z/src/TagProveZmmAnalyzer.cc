#include "PFAnalyses/CommonTools/interface/FWLiteTreeAnalyzer.h"
#include "PFAnalyses/Z/interface/TagProveZmmAnalyzer.h"
#include "PFAnalyses/Z/interface/TestHistograms.h"
#include "PFAnalyses/Z/interface/PatMuonSelector.h"

#include "DataFormats/Math/interface/LorentzVector.h"

#include "FWCore/Utilities/interface/Algorithms.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include <TMath.h>
#include <bitset>



TagProveZmmAnalyzer:: TagProveZmmAnalyzer(const std::string & aName):FWLiteAnalyzer(aName){
  algo = new CompositePtrCandidateT1T2MEtAlgorithm<pat::Muon,pat::Muon>();
}



TagProveZmmAnalyzer::~TagProveZmmAnalyzer(){

  std::cout<<"TagProveZmmAnalyzer::~TagProveZmmAnalyzer()"<<std::endl;

  delete myHistos_;

}


void TagProveZmmAnalyzer::initialize(const edm::ParameterSet& ps, 
				    const TFileDirectory& aDir,
				    std::strbitset *aSelections){


  minMuons_ =   ps.getUntrackedParameter<unsigned int>("minMuons",0); 
  minZmass_ =   ps.getUntrackedParameter<double>("minZmass",0); 
  maxZmass_ =   ps.getUntrackedParameter<double>("maxZmass",9999); 
  patMuonsLabel_ =  ps.getParameter<edm::InputTag>("patMuonsLabel");
  muonSelector_.initialize( ps.getParameter<edm::ParameterSet>("muonSelector") ); 
  tagSelector_.initialize( ps.getParameter<edm::ParameterSet>("tagSelector") );
  proveSelector_.initialize( ps.getParameter<edm::ParameterSet>("proveSelector") );

  ///The histograms for this analyzer will be saved into "TestHistos"
  ///directory of the ROOT file
  myHistos_ = new TestHistograms(&aDir);

  mySelections_ = aSelections;

  registerCuts();

}



void TagProveZmmAnalyzer::registerCuts(){

  std::string labels[1] = {"PF"};
  for(int i =0;i<1;++i){  
    //mySelections_->push_back("All muons |#eta<2.4|"+labels[i]);     
    mySelections_->push_back("Minimum muon multiplicity"+labels[i]);   
    mySelections_->push_back("Z mass range"+labels[i]);   
    mySelections_->push_back("proved Z mass range"+labels[i]);   
  }
}



bool TagProveZmmAnalyzer::analyze(const edm::EventBase& iEvent){

  //std::cout<<iEvent.id()<<std::endl;

  using namespace reco;

  float eventWmight = 1.0;

  clear();

  iEvent.getByLabel(patMuonsLabel_,patMuons_);
  typedef pat::MuonCollection::const_iterator MI;

  size_t size =  patMuons_->size();
  muonMultiplicity_ = size;
  
  nMuons_ = 0;

  int muon1 = -1;
  int muon2 = -1;
  bool proved = false;
  int i = 0;
  for(MI mi = patMuons_->begin(); mi!=patMuons_->end(); ++mi)  {    
    std::strbitset muonSel = muonSelector_.getBitTemplate();
    bool passed = muonSelector_( *mi, muonSel ); 
    std::strbitset tagSel = tagSelector_.getBitTemplate();
    bool taged = tagSelector_( *mi, tagSel ); 
    std::strbitset proveSel = proveSelector_.getBitTemplate();

    if( passed ) {
      myHistos_->fill1DHistogram("hMuonPt",mi->pt(), eventWmight);
      myHistos_->fill1DHistogram("hMuonEta",mi->eta(), eventWmight);
      ++nMuons_; 
      if( muon1 == -1 && taged ) { muon1 = i; }
      else if ( muon2 == -1 ) { 
        muon2 = i; 
        proved = proveSelector_( *mi, proveSel );
      }
    }
    ++i;
  }
  
  if( nMuons_ >= 2 && muon1 > -1 ){ 
    reco::CandidatePtr metPtr;
    const reco::GenParticleCollection* genParticles=0;
    edm::Ptr<pat::Muon> muPtr1(patMuons_,muon1);
    edm::Ptr<pat::Muon> muPtr2(patMuons_,muon2);
    SelectedMuons_.push_back((*patMuons_)[muon1]);
    SelectedMuons_.push_back((*patMuons_)[muon2]);
    Z_= algo->buildCompositePtrCandidate(muPtr1,muPtr2,metPtr,genParticles);
    if(proved){
      provedZ_= algo->buildCompositePtrCandidate(muPtr1,muPtr2,metPtr,genParticles);
    }
  }

  Zmass_ = Z_.mass();
  provedZmass_ = provedZ_.mass();

  checkSelections(iEvent, "PF");

  return true;
}



bool  TagProveZmmAnalyzer::checkSelections(const edm::EventBase& iEvent, const std::string & type){

  mySelections_->set("Minimum muon multiplicity"+type, nMuons_ >= minMuons_ );
  mySelections_->set("Z mass range"+type, Zmass_ > minZmass_ && Z_.mass() < maxZmass_);
  mySelections_->set("proved Z mass range"+type, provedZmass_ > minZmass_ && provedZ_.mass() < maxZmass_);
  return true;
}


void  TagProveZmmAnalyzer::addBranch(TTree *tree){

  tree->Branch("muonMultiplicityPF",&muonMultiplicity_);
  tree->Branch("SelectedMuons", &SelectedMuons_);
  tree->Branch("Zmass", &Zmass_);
  tree->Branch("provedZmass", &provedZmass_);

}



void  TagProveZmmAnalyzer::addCutHistos(TList *aList){

  aList->Add(new TH1F("hmuonMultiplicityPF",";PF muons multiplicity;Events",21,-0.5,20.5));

}



void TagProveZmmAnalyzer::clear(){

  muonMultiplicity_ = 0;
  SelectedMuons_.clear();
  Zmass_ = 0; 
  //Z_.clear(); // no member function clear() 

}
