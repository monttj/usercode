#ifndef PFCandidateAnalyzer_H
#define PFCandidateAnalyzer_H

// -*- C++ -*-
//
//
// Original Author:  Artur Kalinowski
//         Created:  Wed Jul 22 14:16:44 CEST 2009
// $Id: PFCandidateAnalyzer.h,v 1.12 2010/01/07 10:44:18 cbern Exp $
//
//

#include "PFAnalyses/CommonTools/interface/FWLiteAnalyzer.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlock.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlockElement.h"

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include <map>

#include <TClonesArray.h>
#include <TLorentzVector.h>

#include "PFAnalyses/PFCandidate/interface/TreePFCandidate.h"

class PFEnergyCalibration;


namespace PF {
  class PFCandidateHistograms;
  

  class PFCandidateAnalyzer:public FWLiteAnalyzer{

  public:

    typedef reco::PFCandidateCollection::const_iterator CI;

    ///Default contructor
    PFCandidateAnalyzer(const std::string & aName);

    ///Default destructor
    virtual ~PFCandidateAnalyzer();

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

    ///Here we define histogram to be filled after each cut.
    ///Notice: only 1D here.
    ///Notice: name of the histogram the same as the name of the TBranch registered
    ///        in the relevant Analser, EXCEPT "h" at the beggining
    ///Notice: PF suffix in the name is necessary
    virtual void addCutHistos(TList *aList);


  protected:

    ///Method for registering the selections for this analyzer
    virtual void registerCuts();

    ///Method reseting the values of class data members
    virtual void clear();

    // bool accepted( const reco::PFCandidate& cand ) const;

    void setChargedInfo( PF::ChargedHadron& chargedHadron, 
			 const reco::PFCandidate& pfc ) const; 
    void addPhoton( const reco::PFCandidate& pfc ) const; 
    void addElectron( const reco::PFCandidate& pfc ) const; 

    void lookForPSClusters( unsigned iEcal, 
			    const reco::PFBlock& block, 
			    reco::PFBlockElement::Type type, 
			    PhotonPSInfo& psInfo) const;

    void setMuonInfo( PF::Muon& muon, 
			 const reco::PFCandidate& pfc ) const; 

    const reco::PFRecTrack * findPFRecTrack(const reco::TrackRef& ref) const;
 
    ///Class holding all the histograms to be filled
    PFCandidateHistograms *myHistos_;

    ///Name of the analysed data sample, e.g. "ttbar"
    ///This name will be part of the output ROOT file
    std::string sampleName_;

    ///Weight of a event
    float eventWeight_;

    ///InputTags for physics objects
    edm::InputTag pfCandidateLabel_;
    edm::InputTag pfRecTrackLabel_;
    edm::InputTag tkRefLabel_;

    /// switches to process the various types of particles
    bool fillChargedHadrons_;
    bool fillPhotons_;
    bool fillMuons_;
    bool usePhotonRawEnergy_;
    bool fillElectrons_;
    bool PFRecTracksAvailable_;

    ///Hadles to the collections used by this 
    ///selector
    edm::Handle< reco::PFCandidateCollection > pfCandidates_;
    edm::Handle< reco::PFRecTrackCollection > pfRecTracks_;
    edm::Handle<reco::TrackCollection> tkRef_;

    int         run_;
    int         event_;
    int         lumisection_;

    std::vector<ChargedHadron>*  tChargedHadrons_;
    std::vector<Photon>* tPhotons_;
    std::vector<Muon>* tMuons_;
    std::vector<Electron>* tElectrons_;

    PFEnergyCalibration* calibration_;
    unsigned entry_;
  
  };

}
#endif
