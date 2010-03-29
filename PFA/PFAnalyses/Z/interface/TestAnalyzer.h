#ifndef TestAnalyzer_H
#define TestAnalyzer_H

// -*- C++ -*-
//
//
// Original Author:  Artur Kalinowski
//         Created:  Wed Jul 22 14:16:44 CEST 2009
// $Id: TestAnalyzer.h,v 1.3 2010/03/25 08:09:01 bianchi Exp $
//
//

#include "PFAnalyses/CommonTools/interface/FWLiteAnalyzer.h"

#include "DataFormats/PatCandidates/interface/Electron.h"

#include "PFAnalyses/Z/interface/PFElectronSelector.h"

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include <string>

class TestHistograms;

class TestAnalyzer:public FWLiteAnalyzer{

 public:

  ///Default contructor
  TestAnalyzer(const std::string & aName);

  ///Default destructor
  virtual ~TestAnalyzer();

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
  ///        in the relevant Analyzer, EXCEPT "h" at the beggining
  ///Notice: PF suffix in the name is necessary
  virtual void addCutHistos(TList *aList);

 private:

  ///Method for registering the selections for this analyzer
  void registerCuts();

  ///Method reseting the values of class data members
  void clear();

  ///Class holding all the histograms to be filled
  TestHistograms *myHistos_;

  ///This name will be part of the output ROOT file
  std::string sampleName_;

  float maxEleEta_;
  float minElePt_;

  edm::Handle<pat::ElectronCollection> patElectrons_;
  edm::InputTag patElectronsLabel_;

  float eleMultiplicity_;
  PFElectronSelector electronSelector_;

  
};

#endif
