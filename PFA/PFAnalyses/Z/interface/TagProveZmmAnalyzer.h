#ifndef TagProveZmmAnalyzer_H
#define TagProveZmmAnalyzer_H

// -*- C++ -*-
//
//
// Original Author:  Artur Kalinowski
//         Created:  Wed Jul 22 14:16:44 CEST 2009
// $Id: TagProveZmmAnalyzer.h,v 1.3 2010/03/25 08:09:01 bianchi Exp $
//
//

#include "PFAnalyses/CommonTools/interface/FWLiteAnalyzer.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "PFAnalyses/CommonTools/interface/CompositePtrCandidateT1T2MEtAlgorithm.h"

#include "PFAnalyses/Z/interface/PatMuonSelector.h"

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include <string>

class TestHistograms;

class TagProveZmmAnalyzer:public FWLiteAnalyzer{

 public:

  ///Default contructor
  TagProveZmmAnalyzer(const std::string & aName);

  ///Default destructor
  virtual ~TagProveZmmAnalyzer();

  ///Method to initialise the object.
  ///It is called by the top level FWLiteTreeAnalyzer
  ///class.
  virtual void initialize(const edm::ParameterSet&, 
			  const TFileDirectory&,
			  std::strbitset *aSelections);
  
  ///Method where the analysis is done.
  virtual bool analyze(const edm::EventBase& iEvent);

  ///Method which defined the branches to be added
  ///to the analysis TTree
  virtual void addBranch(TTree *tree);

  virtual bool checkSelections(const edm::EventBase& iEvent, const std::string & type);

  ///Here we define histogram to be filled after each cut.
  ///Notice: only 1D here.
  ///Notice: name of the histogram the same as the name of the TBranch registered
  ///        in the rmuonvant Analyzer, EXCEPT "h" at the beggining
  ///Notice: PF suffix in the name is necessary
  virtual void addCutHistos(TList *aList);

 private:

  ///Method for registering the smuonctions for this analyzer
  void registerCuts();

  ///Method reseting the values of class data members
  void clear();

  ///Class holding all the histograms to be filled
  TestHistograms *myHistos_;

  ///This name will be part of the output ROOT file
  std::string sampleName_;

  unsigned int minMuons_;
  double minZmass_;
  double maxZmass_;
  double Zmass_;
  double provedZmass_;

  unsigned int nMuons_;

  edm::Handle<pat::MuonCollection> patMuons_;
  edm::InputTag patMuonsLabel_;

  float muonMultiplicity_;
  PatMuonSelector muonSelector_;
  PatMuonSelector tagSelector_;
  PatMuonSelector proveSelector_;

  CompositePtrCandidateT1T2MEtAlgorithm<pat::Muon,pat::Muon> *algo;
  CompositePtrCandidateT1T2MEt<pat::Muon,pat::Muon> Z_;
  CompositePtrCandidateT1T2MEt<pat::Muon,pat::Muon> provedZ_;
  std::vector<pat::Muon> SelectedMuons_;
  
};

#endif
