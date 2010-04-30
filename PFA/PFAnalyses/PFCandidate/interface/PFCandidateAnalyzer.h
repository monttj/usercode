#ifndef PFCandidateAnalyzer_H
#define PFCandidateAnalyzer_H

// -*- C++ -*-
//
//
// Original Author:  Artur Kalinowski
//         Created:  Wed Jul 22 14:16:44 CEST 2009
// $Id: PFCandidateAnalyzer.h,v 1.20 2010/03/31 15:52:43 pjanot Exp $
//
//

#include "PFAnalyses/CommonTools/interface/FWLiteAnalyzer.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlock.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlockElement.h"
#include "DataFormats/ParticleFlowReco/interface/PFRecHit.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include <map>

#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <TRandom3.h>

#include "PFAnalyses/PFCandidate/interface/TreePFCandidate.h"
#include "PFAnalyses/PFCandidate/interface/TreeTrigger.h"

class PFEnergyCalibration;


namespace PF {
  class PFCandidateHistograms;
  

  class PFCandidateAnalyzer:public FWLiteAnalyzer{

  public:

    typedef reco::PFCandidateCollection::const_iterator CI;
    typedef reco::PFRecHitCollection::const_iterator CIR;

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
    
    // try to simulate the BSC trigger: 
    // energy in both HFs.
    bool simulatedBSCTrigger( float eThresh ) const; 


  protected:

    ///Method for registering the selections for this analyzer
    virtual void registerCuts();

    ///Method reseting the values of class data members
    virtual void clear();

    // bool accepted( const reco::PFCandidate& cand ) const;

    void setChargedInfo( PF::ChargedHadron& chargedHadron, 
			 const reco::PFCandidate& pfc ) const; 
    void addChargedHadron( const reco::PFCandidate& pfc ) const;
    void addPhoton( const reco::PFCandidate& pfc ) const; 
    void addElectron( const reco::PFCandidate& pfc ) const; 
    void addNeutralHadron( const reco::PFCandidate& pfc ) const;
    void addMuon( const reco::PFCandidate& pfc ) const;
    void addHF( const reco::PFCandidate& pfc) const;
    void addRandomCones(const unsigned int& numOfSeeds, const double& etaMax) const;
    void addCleanedChannel( const reco::PFRecHit& pfr, int type, double rescale=0.) const;
    
    void lookForPSClusters( unsigned iEcal, 
			    const reco::PFBlock& block, 
			    reco::PFBlockElement::Type type, 
			    PhotonPSInfo& psInfo) const;

    void setMuonInfo( PF::Muon& muon, 
		      const reco::PFCandidate& pfc ) const; 

    void setTriggerInformation(); 
   
    void setIsoDeposits(PF::Particle& particle, const reco::PFCandidate* pfCandidate) const; 

    const reco::PFRecTrack * findPFRecTrack(const reco::TrackRef& ref) const;

    /// for electrons - used to retrieve the corrected energy of a given PFblockelement
    const reco::PFCandidate & correspondingDaughterCandidate(const reco::PFCandidate & cand, 
							     const reco::PFBlockElement & pfbe) const;
 
    ///Class holding all the histograms to be filled
    PFCandidateHistograms *myHistos_;

    ///Name of the analysed data sample, e.g. "ttbar"
    ///This name will be part of the output ROOT file
    std::string sampleName_;

    ///Weight of a event
    float eventWeight_;

    ///InputTags for physics objects
    bool useMuonDirForRandom_;
    edm::InputTag muonLabel_;
    typedef pat::MuonCollection::const_iterator MI;
    edm::Handle<pat::MuonCollection> muons_;

    edm::InputTag pfCandidateLabel_;
    edm::InputTag pfRecTrackLabel_;
    edm::InputTag tkRefLabel_;
    edm::InputTag cleanedHFShortLabel_;
    edm::InputTag cleanedHCALLabel_;
    edm::InputTag cleanedECALLabel_;
    edm::InputTag cleanedHFEMLabel_;
    edm::InputTag cleanedHFHADLabel_;

    /// switches to process the various types of particles
    bool fillChargedHadrons_;
    double ptMinChargedHadrons_;
    int    nTracksInBlockMax_;
    
    bool fillNeutralHadrons_;
    bool fillPhotons_;
    bool fillMuons_;
    bool usePhotonRawEnergy_;
    bool fillElectrons_;
    bool PFRecTracksAvailable_;
    bool fillCleanedChannels_;
    bool cleanedHFShortAvailable_;
    bool cleanedHFEMAvailable_;
    bool cleanedHFHADAvailable_;
    bool cleanedHCALAvailable_;
    bool cleanedECALAvailable_;
    bool fillHF_;

    /// iso deposit 
    bool fillChargedHadronsIsoDep_;
    bool fillPhotonsIsoDep_;
    bool fillMuonsIsoDep_;
    bool fillElectronsIsoDep_;
    bool fillRandomCones_;

    unsigned int numOfRandomCones_;
    double maxEtaRandomCones_;

    /// upper bound for iso deposit
    double maxDeltaRForIsoDep_;

    ///Hadles to the collections used by this 
    ///selector
    edm::Handle< reco::PFCandidateCollection > pfCandidates_;
    edm::Handle< reco::PFRecTrackCollection > pfRecTracks_;
    edm::Handle<reco::TrackCollection> tkRef_;
    edm::Handle<reco::PFRecHitCollection> cleanedHFShort_;
    edm::Handle<reco::PFRecHitCollection> cleanedHFEM_;
    edm::Handle<reco::PFRecHitCollection> cleanedHFHAD_;
    edm::Handle<reco::PFRecHitCollection> cleanedHCAL_;
    edm::Handle<reco::PFRecHitCollection> cleanedECAL_;

    int         run_;
    int         event_;
    int         lumisection_;

    TriggerInformation*          tTriggerInformation_;
    std::vector<CleanedChannel>*  tCleanedChannels_;
    std::vector<ChargedHadron>*  tChargedHadrons_;
    std::vector<Photon>* tPhotons_;
    std::vector<Muon>* tMuons_;
    std::vector<Electron>* tElectrons_;
    std::vector<Particle>* tNeutralHadrons_;
    std::vector<Particle>* tHFs_;
    std::vector<RandomCone>*  tRandomCones_;
    TRandom3* tRandom_;
    
    PFEnergyCalibration* calibration_;
    unsigned entry_;
  
  };

}
#endif
