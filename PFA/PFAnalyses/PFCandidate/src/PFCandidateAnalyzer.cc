#include "PFAnalyses/CommonTools/interface/FWLiteTreeAnalyzer.h"
#include "PFAnalyses/PFCandidate/interface/PFCandidateAnalyzer.h"
#include "PFAnalyses/PFCandidate/interface/PFCandidateHistograms.h"

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlock.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlockElement.h"
#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/EgammaReco/interface/ElectronSeed.h"
#include "DataFormats/EgammaReco/interface/ElectronSeedFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlockElementGsfTrack.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlockElementTrack.h"
#include "DataFormats/ParticleFlowReco/interface/PFRecTrackFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFRecTrack.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "FWCore/Utilities/interface/Algorithms.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlockElementBrem.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlockElementCluster.h"
#include "RecoParticleFlow/PFClusterTools/interface/PFClusterWidthAlgo.h"

#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"

#include "DataFormats/METReco/interface/PFMET.h"
#include "RecoParticleFlow/PFClusterTools/interface/PFEnergyCalibration.h"

#include <iostream>

#include <TLorentzVector.h>

using namespace std;
using namespace PF;
using namespace reco;

typedef std::multimap<double, unsigned>::iterator IE;


PFCandidateAnalyzer:: PFCandidateAnalyzer(const std::string & aName) : 
  FWLiteAnalyzer(aName)

 {
   
   tChargedHadrons_ = new vector< ChargedHadron > ();
   tPhotons_ = new vector< Photon > ();
   tMuons_ = new vector< Muon > ();
   tElectrons_ = new vector< Electron > ();
   
   calibration_ =  new PFEnergyCalibration( 0., 0., 0., 0., 0., 0., 0., 0., 2);

 }


PFCandidateAnalyzer::~PFCandidateAnalyzer(){

  std::cout<<"PFCandidateAnalyzer::~PFCandidateAnalyzer()"<<std::endl;

  delete myHistos_;

}


void PFCandidateAnalyzer::initialize(const edm::ParameterSet& ps, 
				    const TFileDirectory& aDir,
				    std::strbitset *aSelections){
  

  pfCandidateLabel_ = ps.getParameter<edm::InputTag>("pfCandidateLabel");
  fillChargedHadrons_ = ps.getUntrackedParameter<bool>("fillChargedHadrons",true);
  if( fillChargedHadrons_ ) {
    fillChargedHadronsIsoDep_ = ps.getUntrackedParameter<bool>("fillChargedHadronsIsoDep",false);
  }
  fillPhotons_ = ps.getUntrackedParameter<bool>("fillPhotons", true);
  fillMuons_ = ps.getUntrackedParameter<bool>("fillMuons", true);
  if(fillMuons_){
    fillMuonsIsoDep_ = ps.getUntrackedParameter<bool>("fillMuonsIsoDep",false);
  }
  if(fillPhotons_){
    usePhotonRawEnergy_ = ps.getParameter<bool>("usePhotonRawEnergy");
    fillPhotonsIsoDep_ = ps.getUntrackedParameter<bool>("fillPhotonsIsoDep",false);
  }
  fillElectrons_ = ps.getUntrackedParameter<bool>("fillElectrons", true);
  if (fillElectrons_){ 
    pfRecTrackLabel_ = ps.getParameter<edm::InputTag>("pfRecTrackLabel");
    fillElectronsIsoDep_ = ps.getUntrackedParameter<bool>("fillElectronsIsoDep",false);
  }
  maxDeltaRForIsoDep_ = ps.getUntrackedParameter<double>("maxDeltaRForIsoDep", 1.0);
  tkRefLabel_ = ps.getParameter<edm::InputTag>("tkRefLabel");

  ///The histograms for this analyser will be saved into "TestHistos"
  ///directory of the ROOT file
  myHistos_ = new PFCandidateHistograms(&aDir);  
  
  mySelections_ = aSelections;

  entry_ = 0;

  registerCuts();
  
}


void PFCandidateAnalyzer::registerCuts(){

  ///It is possible to have many versions of the selection flow,
  ///eg. compare PF and classic approach. Here we use only PF
  ///The cuts reported in the CutCounter histogram will
  ///appear in the order set below.
  //   std::string labels[1] = {"PF"};
  //   for(int i =0;i<1;++i){  
  //       mySelections_->push_back("pfCandidateEtCut"+labels[i]);   
  //   }
}


bool PFCandidateAnalyzer::analyze(const edm::EventBase& iEvent){

  //std::cout<<iEvent.id()<<std::endl;


  eventWeight_ = 1.0;

  clear();

  iEvent.getByLabel(tkRefLabel_,tkRef_);    
  const reco::TrackCollection* tkColl = tkRef_.product();

  //std::cout << "Total Number of Tracks " << tkColl->size() << endl;

  bool accepted = false;
  int numhighpurity=0;
  double fraction = 1.;
  reco::TrackBase::TrackQuality _trackQuality = reco::TrackBase::qualityByName("highPurity");

  if(tkColl->size()>10){ 
    reco::TrackCollection::const_iterator itk = tkColl->begin();
    reco::TrackCollection::const_iterator itk_e = tkColl->end();
    for(;itk!=itk_e;++itk){
      // std::cout << "HighPurity?  " << itk->quality(_trackQuality) << std::endl;
      if(itk->quality(_trackQuality)) numhighpurity++;
    }
    fraction = (float)numhighpurity/(float)tkColl->size();
    if(fraction>0.25) accepted=true;
  }else{
    //if less than 10 Tracks accept the event anyway    
    accepted= true;
  }
  if ( !accepted ) return false;
  
  iEvent.getByLabel(pfCandidateLabel_,pfCandidates_);

  // check if the RecTracks (display event content) 
  // or track-extra (RECO event contennt )are available. Only needed if electrons are used

  if(fillElectrons_)
    {
      PFRecTracksAvailable_=iEvent.getByLabel(pfRecTrackLabel_,pfRecTracks_);
    }

  run_ = iEvent.id().run();
  event_ = iEvent.id().event();
  lumisection_ = iEvent.luminosityBlock();

  //if ( run_ == 123596 && event_ == 9262130 )   
  /*
  int ils = iEvent.luminosityBlock();
  int bx = iEvent.bunchCrossing();
  if ( !accepted ) 
    std::cout << "Entry " << entry_ << " Run " << run_ << " Event " << event_ 
	      << " Lumi Block " << ils << " Bunch Crossing " << bx 
	      << " Fraction " << fraction << " NTracks " << tkColl->size() 
	      << " Accepted " << accepted << std::endl;
  */
  // std::cout << "Entry = " << entry_ << ", Run/Event " << run_ << " " << event_ << std::endl;
  entry_++;

  for( CI ci  = pfCandidates_->begin(); 
       ci!=pfCandidates_->end(); ++ci)  {
    const reco::PFCandidate& pfc = *ci;
    myHistos_->fill1DHistogram("hPFCandidateEt",pfc.et(),eventWeight_);    
    myHistos_->fill2DHistogram("hPFCandidateEtVsEta",pfc.eta(),pfc.et(), eventWeight_);    
    
    LorentzVector pvi(pfc.p4());

    if ( pfc.particleId() == 1 && fillChargedHadrons_ ) {
      // Run on charged particle tracks
      // Fill only if pt > 1.
      if ( pfc.pt() < 1. ) continue;
      tChargedHadrons_->push_back(ChargedHadron( pvi, 
						 pfc.rawEcalEnergy(), 
						 pfc.rawHcalEnergy(),
						 pfc.particleId() ) );
      
      tChargedHadrons_->back().setPosEcal( math::XYZPoint( pfc.positionAtECALEntrance().x(),
						  pfc.positionAtECALEntrance().y(),
						  pfc.positionAtECALEntrance().z()) ); 

      
      setChargedInfo( tChargedHadrons_->back(), pfc);
      if(fillChargedHadronsIsoDep_) {
        setIsoDeposits( (PF::Particle&)tChargedHadrons_->back(), pfc); 
      }
      
    } else if ( pfc.particleId() == 2 && fillElectrons_){
      // Run on electrons
      addElectron (pfc ) ;      
    }
    else if( pfc.particleId() == 3 && fillMuons_) { 
      // Run on Muons
      
      tMuons_->push_back(Muon( pvi, 
			       pfc.rawEcalEnergy(), 
			       pfc.rawHcalEnergy(),
			       pfc.particleId() ) );
      
      tMuons_->back().setPosEcal( math::XYZPoint( pfc.positionAtECALEntrance().x(),
						  pfc.positionAtECALEntrance().y(),
						  pfc.positionAtECALEntrance().z()) ); 

      
      setMuonInfo( tMuons_->back(), pfc);
      if(fillMuonsIsoDep_) {
        setIsoDeposits( (PF::Particle&)tMuons_->back(), pfc);
      }

    }
    else if ( pfc.particleId() == 4 && fillPhotons_) { 
      // Run on photons
      addPhoton( pfc );
    } else if ( pfc.particleId() == 5 ) { 
      // Run on neutral hadrons
      ;
    }
  }

  return true;
}


void PFCandidateAnalyzer::setChargedInfo( PF::ChargedHadron& chargedHadron, 
					  const reco::PFCandidate& pfc ) const {
  // Find the corresponding block
  const PFCandidate::ElementsInBlocks& theElements = pfc.elementsInBlocks();
  const reco::PFBlockRef blockRef = theElements[0].first;
  PFBlock::LinkData linkData =  blockRef->linkData();
  // And the block elements
  const edm::OwnVector<reco::PFBlockElement>& elements = blockRef->elements();
  unsigned iTrack = 999;

  // counts the tracks
  unsigned int nTracks = 0;
  for(unsigned iEle=0; iEle<elements.size(); iEle++) {
    // Find the tracks in the block
    PFBlockElement::Type type = elements[iEle].type();
    switch( type ) {
    case PFBlockElement::TRACK:
      iTrack = iEle;
      nTracks++;
      break;
    default:
      continue;
    }
  }
  //std::cout << "N tracks = " << nTracks << std::endl;
  if ( nTracks != 1 ) return;

  const reco::PFBlockElementTrack& et =
    dynamic_cast<const reco::PFBlockElementTrack &>( elements[iTrack] );
//   double p = et.trackRef()->p();  
  double pt = et.trackRef()->pt();  
  unsigned int nHits = et.trackRef()->found();
  unsigned int tobN = 0;
  unsigned int tecN = 0;
  unsigned int tibN = 0;
  unsigned int tidN = 0;
  unsigned int pxbN = 0;
  unsigned int pxdN = 0;
  const reco::HitPattern& hp = et.trackRef()->hitPattern();
  switch ( et.trackRef()->algo() ) {
  case TrackBase::ctf:
  case TrackBase::iter0:
  case TrackBase::iter1:
  case TrackBase::iter2:
    tobN += hp.numberOfValidStripTOBHits();
    tecN += hp.numberOfValidStripTECHits();
    tibN += hp.numberOfValidStripTIBHits();
    tidN += hp.numberOfValidStripTIDHits();
    pxbN += hp.numberOfValidPixelBarrelHits(); 
    pxdN += hp.numberOfValidPixelEndcapHits(); 
    break;
  case TrackBase::iter3:
  case TrackBase::iter4:
  case TrackBase::iter5:
  default:
    break;
  }
  //unsigned int inner = et.trackRef()->innerDetId();
  //unsigned int outer = et.trackRef()->outerDetId();
  unsigned int inner = pxbN+pxdN;
  unsigned int outer = tibN+tobN+tidN+tecN;
  if ( pt < 1. ) return; 
  // double etat = et.trackRef()->eta();

  /*
  // Find the closest photon and neutral hadron.
  double drgMin = 1E6;
  double drhMin = 1E6;
  math::XYZVector ecalV(pfc.positionAtECALEntrance().X(),
			pfc.positionAtECALEntrance().Y(),
			pfc.positionAtECALEntrance().Z());
  double etaT = ecalV.Eta();
  double phiT = ecalV.Phi();
  
  for( CI di = pfCandidates_->begin(); 
       di!=pfCandidates_->end(); ++di)  {
    const reco::PFCandidate& pfcj = *di;
    if ( pfcj.particleId() < 4 || pfcj.particleId() > 5 ) continue;
    double etaC = pfcj.eta();
    const PFCandidate::ElementsInBlocks& theElementsJ = pfcj.elementsInBlocks();
    const reco::PFBlockRef blockRefJ = theElementsJ[0].first;
    ///if ( blockRefJ == blockRef ) { 
    ///  if ( pfcj.particleId() == 4 ) 
    ///	std::cout << "Warning : an additional photon in the block : " << pfcj.energy() << std::endl;
    ///   if ( pfcj.particleId() == 5 ) 
    ///std::cout << "Warning : an additional neutral hadron in the block : " << pfcj.energy() << std::endl;
    ///}
    double phiC = pfcj.phi();
    double dR = std::sqrt((etaT-etaC)*(etaT-etaC) + (phiT-phiC)*(phiT-phiC));
    if ( pfcj.particleId() == 4 && dR < drgMin ) drgMin = dR;
    if ( pfcj.particleId() == 5 && dR < drhMin ) drhMin = dR;
  }
  */
  
  // Find the ECAL clusters linked to the track
  std::multimap<double, unsigned> ecalElems;
  blockRef->associatedElements( iTrack,  linkData,
				ecalElems ,
				reco::PFBlockElement::ECAL,
				reco::PFBlock::LINKTEST_ALL );
  // Determine the distance to the closest element
  double distEcal = -1.;
  unsigned indexEcal = 100000;
  if ( ecalElems.size() ) { 
    IE ie = ecalElems.begin(); 
    indexEcal = ie->second;
    distEcal  = ie->first;
    // cout<<"\telement "<<elements[indexEcal]<<" linked with distance = "<< distEcal <<endl;
  }
  
  // Find the HCAL clusters linked to the track  
  std::multimap<double, unsigned> hcalElems;
  blockRef->associatedElements( iTrack,  linkData,
				hcalElems,
				reco::PFBlockElement::HCAL,
				reco::PFBlock::LINKTEST_ALL );
  // Determine the distance to the closest element
  double distHcal = -1.;
  unsigned indexHcal = 100000;
  if ( hcalElems.size() ) { 
    IE ih = hcalElems.begin(); 
    indexHcal = ih->second;
    distHcal  = ih->first;
    // cout<<"\telement "<<elements[indexHcal]<<" linked with distance = "<< distHcal <<endl;
  }
  
  
  double e = pfc.rawEcalEnergy();
  double h = pfc.rawHcalEnergy();
  double t = pfc.p();
  double eta = pfc.eta();
  double phi = pfc.phi();
  calibration_->energyEmHad(t, e, h, eta, phi);

  // Update the candidate content
  double drgMin = -1;
  double drhMin = -1;
  chargedHadron.setChargeInfo(distEcal,distHcal,e,h,drgMin,drhMin,nHits,inner,outer);

}



void PFCandidateAnalyzer::addPhoton( const reco::PFCandidate& pfc ) const {
  
  // Find the corresponding block
  
  // Loop over elements in block 
 
  
  const PFCandidate::ElementsInBlocks& theElements = pfc.elementsInBlocks();
  
  typedef PFCandidate::ElementsInBlocks::const_iterator IEB; 
  
  int iEcal = 99999999;
  bool foundEcal = false;
  for (IEB ieb=theElements.begin(); ieb<theElements.end(); ++ieb) {
    const PFBlock& block = *(ieb->first);
    const PFBlockElement& elem = block.elements()[ieb->second];
    PFBlockElement::Type type = elem.type();
    
    switch( type ) {
    case PFBlockElement::ECAL:
      if( foundEcal ) {
	//  several ECAL clusters involved in the creation of a photon PFCandidate. this is a merged photon. removing them for now.
	cout<<"photon coming from several ECAL clusters."<<endl;
// 	cout<<pfc<<endl;
// 	cout<<block<<endl;
      }
      foundEcal = true;
      iEcal = ieb->second;
      break;
    default:
      continue;
    }

    // look for tracks linked to this ECAL cluster. 

    std::multimap<double, unsigned> trackElems;
    block.associatedElements( iEcal,  block.linkData(),
			      trackElems ,
			      reco::PFBlockElement::TRACK,
			      reco::PFBlock::LINKTEST_ALL );
    
    if( !trackElems.empty() ) {
      //       cout<<"warning : track linked to ECAL cluster giving a photon."<<endl;
      //       cout<<"photon "<<pfc<<endl;
      //       cout<<block<<endl;
      // continue;
      ;
    }

    // here, no track linked to our ECAL cluster 
    // looking for associated PS clusters
    
    if(usePhotonRawEnergy_) {
      math::XYZVector vec(pfc.positionAtECALEntrance().x()-pfc.vertex().x(),
			  pfc.positionAtECALEntrance().y()-pfc.vertex().y(),
			  pfc.positionAtECALEntrance().z()-pfc.vertex().z());
      math::XYZVector momentum = vec.unit() * pfc.rawEcalEnergy();
      math::XYZTLorentzVector rawLorentz(momentum.x(),momentum.y(),momentum.z(), pfc.rawEcalEnergy());    
      tPhotons_->push_back( Photon( rawLorentz,  *(elem.clusterRef())) );
    }else {
      tPhotons_->push_back( Photon( pfc.p4(),  *(elem.clusterRef())) );
    }

    if(fillPhotonsIsoDep_) setIsoDeposits( (PF::Particle&)tPhotons_->back(), pfc);;
    lookForPSClusters( iEcal, block, PFBlockElement::PS1, 
		       tPhotons_->back().ps1() );
    lookForPSClusters( iEcal, block, PFBlockElement::PS2, 
		       tPhotons_->back().ps2() );
  }

  
  if( !foundEcal ) {
    cout<<"photon, but ECAL cluster not found!"<<endl;
    cout<<pfc<<endl;
    
  }

}

void PFCandidateAnalyzer::addElectron( const reco::PFCandidate & pfc) const {
  const PFCandidate::ElementsInBlocks& theElements = pfc.elementsInBlocks();
  typedef PFCandidate::ElementsInBlocks::const_iterator IEB; 
  Electron myElectron(pfc.p4(),pfc.charge());
  int firstEcal = 0;
  unsigned int ecalGsf_index = 10000;
  unsigned int gsf_index = 10000;
  unsigned int kf_index = 10000;
  int lateBrem = -1;
  int earlyBrem = -1;
  bool isBrem = false;
  double sigmaEtaEta = -1;
  float Ene_hcalgsf = 0.;
  double pout = -1;
  int printTrackerDri = -1;
  int printEcalDri = -1;


  for (IEB ieb=theElements.begin(); ieb<theElements.end(); ++ieb) {
    const PFBlock& block = *(ieb->first);
    const PFBlockElement& pfbe = block.elements()[ieb->second];
    if(pfbe.type()==reco::PFBlockElement::ECAL) {
      if(firstEcal == 0) {
	ecalGsf_index = ieb->second;
	reco::PFClusterRef clusterRef = pfbe.clusterRef();
	vector< const reco::PFCluster * > pfClust_vec(0);
	pfClust_vec.clear();
	pfClust_vec.push_back(&(*clusterRef));
	
	PFClusterWidthAlgo pfwidth(pfClust_vec);
	sigmaEtaEta = pfwidth.pflowSigmaEtaEta();
	
      }
      firstEcal++;
    }
    if(pfbe.type()==reco::PFBlockElement::GSF) {
      gsf_index = ieb->second;
    } 
    if(pfbe.type()==reco::PFBlockElement::TRACK) {
      kf_index = ieb->second;
    }
  }

  for (IEB ieb=theElements.begin(); ieb<theElements.end(); ++ieb) {
    const PFBlock& block = *(ieb->first);
    PFBlock::LinkData linkData =  block.linkData();
    const PFBlockElement& pfbe = block.elements()[ieb->second];
    if(pfbe.type()==reco::PFBlockElement::ECAL)
      {
	reco::PFClusterRef myPFClusterRef= pfbe.clusterRef();
	const reco::PFCluster & myPFCluster (*myPFClusterRef);
	myElectron.addCluster(myPFCluster.position(),myPFCluster.energy());
      }
    if(pfbe.type()==reco::PFBlockElement::TRACK)
      {
	const reco::PFBlockElementTrack& et =
          dynamic_cast<const reco::PFBlockElementTrack &>( pfbe );
	
	// does not work  because transient
	//	reco::PFRecTrackRef myTrackRef = et.trackRefPF();
	myElectron.setKfTrackIn(et.trackRef()->referencePoint(),et.trackRef()->momentum());
	myElectron.setKfCharge(et.trackRef()->charge());

	
 	myElectron.setKfNhits(et.trackRef()->hitPattern().trackerLayersWithMeasurement());
 	myElectron.setKfChi2(et.trackRef()->normalizedChi2());

	// The following works on display event content. The PFRecTrack has to be found by hand
	// because the PFRecTrackRef is only transient (arrghg! )
	if(PFRecTracksAvailable_)
	  {
	    const reco::PFRecTrack * myPFRecTrack=findPFRecTrack(et.trackRef());
	    if(myPFRecTrack)
	      {
		//		std::cout << " from pfrectrack " << std::endl;
		std::vector< reco::PFTrajectoryPoint >::const_iterator outermost=myPFRecTrack->outermostMeasurement();
		myElectron.setKfTrackOut(outermost->position(),math::XYZVector(outermost->momentum().X(),
									       outermost->momentum().Y(),
									       outermost->momentum().Z()));
		
	      }
	  }
	else // otherwise, we are probably running on RECO, therefore the trackextra should be available
	  {
	    //	    std::cout << " From track extra " << std::endl;
	    if(et.trackRef()->extra().isAvailable())
	      {
		myElectron.setKfTrackOut(et.trackRef()->outerPosition(),et.trackRef()->outerMomentum());
	      }
	  }
      }
    if(pfbe.type()==reco::PFBlockElement::GSF) {
      // take the mode pout from the PFBlockElement
      const reco::PFBlockElementGsfTrack *  GsfEl =  dynamic_cast<const reco::PFBlockElementGsfTrack*>(&pfbe); 
      reco::GsfTrackRef myTrackRef = GsfEl->GsftrackRef();
      
      // set seed provenance
      int isEcalDriven = -1;
      int isTrackerDriven = -1;
      if(myTrackRef->extra().isAvailable()){
	if(myTrackRef->extra()->seedRef().isAvailable()){
	  ElectronSeedRef seedRef= myTrackRef->extra()->seedRef().castTo<ElectronSeedRef>();
	  if(&(*seedRef)) {
	    if(seedRef->isEcalDriven()){
	      isEcalDriven = 1;
	    }
	    else{
	      isEcalDriven = 0;
	    }

	    if(seedRef->isTrackerDriven()){
	      isTrackerDriven = 1;
	    }
	    else{
	      isTrackerDriven = 0;
	    }
	  }
	}
      }
      myElectron.setTrackerDrivenSeed(isTrackerDriven);
      myElectron.setEcalDrivenSeed(isEcalDriven);
      printTrackerDri = isTrackerDriven;
      printEcalDri = isEcalDriven;
      
      // get as outer position, the position at the ecal entrance
      // in the future add another methods
      
      if(myTrackRef->extra().isAvailable())
	
	myElectron.setGsfTrackOut(myTrackRef->outerPosition(),math::XYZVector(GsfEl->Pout().X(),
									      GsfEl->Pout().Y(),
									      GsfEl->Pout().Z()));

      pout = GsfEl->Pout().t();
      
      myElectron.setPosEcal( math::XYZPoint(GsfEl->positionAtECALEntrance().x(),
					    GsfEl->positionAtECALEntrance().y(),
					    GsfEl->positionAtECALEntrance().z()));
      
      
      myElectron.setDistance(-1.);
      if(ecalGsf_index < 10000) {
	float distance_ele = block.dist(ieb->second,ecalGsf_index,
					linkData,reco::PFBlock::LINKTEST_ALL);
	myElectron.setDistance(distance_ele);
      }
      

      vector<unsigned int> hcal_index;
      hcal_index.clear();
      // Find the closest cluster 
      float distance_gsfecal  = block.dist(gsf_index,ecalGsf_index,
					   linkData,reco::PFBlock::LINKTEST_ALL);
      float distance_kfecal = -1.;
      if(kf_index < 1000) 
	distance_kfecal  = block.dist(kf_index,ecalGsf_index,
				      linkData,reco::PFBlock::LINKTEST_ALL);

      if(distance_gsfecal > 0.) {
	std::multimap<double, unsigned int> hcalGsfElems;
	block.associatedElements( gsf_index,linkData,
				  hcalGsfElems,
				  reco::PFBlockElement::HCAL,
				  reco::PFBlock::LINKTEST_ALL );	
	for( std::multimap<double, unsigned int>::iterator it = hcalGsfElems.begin();
	     it != hcalGsfElems.end();it++) {
	  unsigned int index = it->second;
	  std::multimap<double, unsigned> sortedGsf;
	  block.associatedElements( index,  linkData,
				    sortedGsf,
				    reco::PFBlockElement::GSF,
				    reco::PFBlock::LINKTEST_ALL );
	  unsigned jGsf = sortedGsf.begin()->second;
	  if ( jGsf != gsf_index) continue; 
	  hcal_index.push_back(index);
	}
      }
      else if( distance_kfecal >0.) {
	std::multimap<double, unsigned int> hcalKfElems;
	block.associatedElements( kf_index,linkData,
				  hcalKfElems,
				  reco::PFBlockElement::HCAL,
				  reco::PFBlock::LINKTEST_ALL );	
	for( std::multimap<double, unsigned int>::iterator it = hcalKfElems.begin();
	     it != hcalKfElems.end();it++) {
	  unsigned int index = it->second;
	  
	  // Check that this cluster is not closer to another KF
	  std::multimap<double, unsigned> sortedKf;
	  block.associatedElements( index,  linkData,
				    sortedKf,
				    reco::PFBlockElement::TRACK,
				    reco::PFBlock::LINKTEST_ALL );
	  unsigned jKf = sortedKf.begin()->second;
	  if ( jKf != kf_index) continue; 
	  hcal_index.push_back(index);
	}
      }
      
      for(unsigned int ihcal = 0; ihcal<hcal_index.size();ihcal++){
	const PFBlockElement& pfhcal = block.elements()[(hcal_index[ihcal])];
	const reco::PFBlockElementCluster * clust =  
	  dynamic_cast<const reco::PFBlockElementCluster*>(&pfhcal); 
	Ene_hcalgsf+=clust->clusterRef()->energy();
      }
      

    }
    if(pfbe.type()==reco::PFBlockElement::BREM) {
      isBrem = true;
      const reco::PFBlockElementBrem * BremEl =  
	dynamic_cast<const reco::PFBlockElementBrem*>(&pfbe);
      int TrajPos = (BremEl->indTrajPoint())-2;
      if (TrajPos <= 3) earlyBrem = 1;
      

      if(ecalGsf_index < 1000) {
	float distance_bremecal = block.dist(ieb->second,ecalGsf_index,
					     linkData,reco::PFBlock::LINKTEST_ALL);
	float distance_gsfecal  = block.dist(gsf_index,ecalGsf_index,
					     linkData,reco::PFBlock::LINKTEST_ALL);
	
	if(distance_gsfecal > 0. &&  distance_bremecal > 0.) {
	  if((distance_bremecal + 0.0012) < distance_gsfecal)
	    lateBrem = 1;
	}
      }
    } // endif brem
  }
  
  if(isBrem == true) {
    if(earlyBrem < 1) 
      earlyBrem = 0;
    if(lateBrem < 1) 
      lateBrem = 0;
  }
  // take the mode pin from the GsfTrack
   myElectron.setEarlyBrem(earlyBrem);
   myElectron.setLateBrem(lateBrem);
   myElectron.setSigmaEtaEta(log(sigmaEtaEta));

  reco::GsfTrackRef myTrackRef = pfc.gsfTrackRef();
  if(myTrackRef->extra().isAvailable()){
    myElectron.setGsfTrackIn(myTrackRef->innerPosition(),myTrackRef->momentumMode());
    myElectron.setGsfInMean(myTrackRef->innerMomentum());
    myElectron.setGsfOutMean(myTrackRef->outerMomentum());
    myElectron.setGsfNhits(myTrackRef->hitPattern().trackerLayersWithMeasurement());
    myElectron.setGsfChi2(myTrackRef->normalizedChi2());
    
  }
  myElectron.setGsfInMode(math::XYZVector(myTrackRef->pxMode(),
					  myTrackRef->pyMode(),
					  myTrackRef->pzMode()));
  if(myTrackRef->ptModeError() > 0.)
    myElectron.setGsfdptopt(myTrackRef->ptModeError()/myTrackRef->ptMode());
  
  myElectron.setHcal(Ene_hcalgsf);
  myElectron.setSeedEcal(pfc.rawEcalEnergy());// this in the seed energy corrected
  myElectron.setTotalEcal(pfc.ecalEnergy());
  myElectron.setPS(pfc.pS1Energy(),pfc.pS2Energy());
  myElectron.setMVA(pfc.mva_e_pi());


  // Print Good Electrons
  bool print = false;
  if (print) {
    if((pfc.mva_e_pi() > -0.1)) {
      float eseed = pfc.rawEcalEnergy();
      float ene = pfc.ecalEnergy();
      float pin = myTrackRef->pMode();
      float Ebrem = pfc.ecalEnergy() - pfc.rawEcalEnergy();
      float DP = pin - pout;
      
      if(ene/pin > 0.8 && ene/pin < 1.2 && Ebrem > 0.) {
	cout << " **************************** FOUND ELECTRON ************************ " << endl
	     << " ele_pt " << pfc.pt() << endl
	     << " gsf_pin " << pin <<  " ene " << ene << " e/p " << ene/pin
	     << " eseed " << eseed << " pout " << pout << " eseed/pout " <<  eseed/pout << endl
	     << " eta,phi " << pfc.eta() << ", " << pfc.phi() 
	     << " mva " << pfc.mva_e_pi() 
	     << " Ebrem " << Ebrem << " DP " << DP 
	     << " trackerDriven " << printTrackerDri 
	     << " ecalDriven " << printEcalDri << endl;
	cout << " ----------------------------" << endl;
	cout << "EVNUMBER '"<< run_ <<":"<<  event_ <<"-"<< run_ <<":"<< event_+1 << "'," << endl;
      }
    }
  }
  
  tElectrons_->push_back(myElectron);
  if(fillElectronsIsoDep_) setIsoDeposits((PF::Particle&)tElectrons_->back(), pfc);

}


void PFCandidateAnalyzer::lookForPSClusters( unsigned iEcal, 
					 const PFBlock& block, 
					 PFBlockElement::Type type, 
					 PhotonPSInfo& psInfo ) const {
  std::multimap<double, unsigned> psElems;    
  block.associatedElements( iEcal,  
			    block.linkData(),
			    psElems ,
			    type,
			    reco::PFBlock::LINKTEST_ALL ); 

//  if(!psElems.empty() ) {
//     cout<<block<<endl;
//   }

  for( IE ie = psElems.begin(); ie!=psElems.end(); ++ie) {
    const reco::PFClusterRef& cluster = block.elements()[ie->second].clusterRef();    
    
    psInfo.addPS( cluster->position(),  
		  cluster->energy() );
  }

}



void PFCandidateAnalyzer::setMuonInfo( PF::Muon& muon, 
					  const reco::PFCandidate& pfc ) const {
  // Find the corresponding block
  const PFCandidate::ElementsInBlocks& theElements = pfc.elementsInBlocks();
  const reco::PFBlock& block = *(theElements[0].first);
  PFBlock::LinkData linkData =  block.linkData();
  // And the block elements
  const edm::OwnVector<reco::PFBlockElement>& elements = block.elements();
  unsigned iTrack = 999;
  // Loop over elements
  for(unsigned iEle=0; iEle<elements.size(); iEle++) {
    // Find the tracks in the block
    PFBlockElement::Type type = elements[iEle].type();
    switch( type ) {
    case PFBlockElement::TRACK:
      iTrack = iEle;
      break;
    default:
      continue;
    }
    // Find the ECAL clusters linked to the track
    std::multimap<double, unsigned> ecalElems;
    block.associatedElements( iTrack,  linkData,
			      ecalElems ,
			      reco::PFBlockElement::ECAL,
			      reco::PFBlock::LINKTEST_ALL );
    // Determine the distance to the closest element
    double distEcal = -1.;
    unsigned indexEcal = 100000;
    if ( ecalElems.size() ) { 
      IE ie = ecalElems.begin(); 
      indexEcal = ie->second;
      distEcal  = ie->first;
      // cout<<"\telement "<<elements[indexEcal]<<" linked with distance = "<< distEcal <<endl;
    }

    // Find the HCAL clusters linked to the track  
    std::multimap<double, unsigned> hcalElems;
    block.associatedElements( iTrack,  linkData,
			      hcalElems,
			      reco::PFBlockElement::HCAL,
			      reco::PFBlock::LINKTEST_ALL );
    // Determine the distance to the closest element
    double distHcal = -1.;
    unsigned indexHcal = 100000;
    if ( hcalElems.size() ) { 
      IE ih = hcalElems.begin(); 
      indexHcal = ih->second;
      distHcal  = ih->first;
      // cout<<"\telement "<<elements[indexHcal]<<" linked with distance = "<< distHcal <<endl;
    }

    // Find the closest photon and neutral hadron.
    double drgMin = 1E6;
    double drhMin = 1E6;
    math::XYZVector ecalV(pfc.positionAtECALEntrance().X(),
			  pfc.positionAtECALEntrance().Y(),
			  pfc.positionAtECALEntrance().Z());
    double etaT = ecalV.Eta();
    double phiT = ecalV.Phi();

    for( CI di = pfCandidates_->begin(); 
	 di!=pfCandidates_->end(); ++di)  {
      const reco::PFCandidate& pfcj = *di;
      if ( pfcj.particleId() < 4 || pfcj.particleId() > 5 ) continue;
      double etaC = pfcj.eta();
      if ( fabs(etaC) > 2.4 ) continue;
      double phiC = pfcj.phi();
      double dR = std::sqrt((etaT-etaC)*(etaT-etaC) + (phiT-phiC)*(phiT-phiC));
      if ( pfcj.particleId() == 4 && dR < drgMin ) drgMin = dR;
      if ( pfcj.particleId() == 5 && dR < drhMin ) drhMin = dR;
    }

    // Update the candidate content
    muon.setChargeInfo(distEcal,distHcal,pfc.ecalEnergy(),pfc.hcalEnergy(),drgMin,drhMin);
  }
}


/*
bool PFCandidateAnalyzer::accepted( const PFCandidate& cand ) const {
  
  if(cand.pdgId()!=22) return false;

  if(cand.pt() < minPhotonPt_) return false;

  return true;
}
*/

void  PFCandidateAnalyzer::addBranch(TTree *tree){

  tree->Branch("Run",&run_);
  tree->Branch("Event",&event_);
  tree->Branch("LumiSection",&lumisection_);

  tree->Branch("ChargedHadrons","std::vector< PF::ChargedHadron >", &tChargedHadrons_);
  tree->Branch("Photons","std::vector< PF::Photon >", &tPhotons_);
  tree->Branch("Muons","std::vector< PF::Muon >", &tMuons_);
  tree->Branch("Electron","std::vector< PF::Electron >", &tElectrons_);


}



void  PFCandidateAnalyzer::addCutHistos(TList *aList){

}


void PFCandidateAnalyzer::clear(){

  tChargedHadrons_->clear();
  tPhotons_->clear();
  tMuons_->clear();
  tElectrons_->clear();
}

const reco::PFRecTrack * PFCandidateAnalyzer::findPFRecTrack(const reco::TrackRef& ref) const
{
  if(!PFRecTracksAvailable_) return 0;
  reco::PFRecTrackCollection::const_iterator it=pfRecTracks_->begin();
  reco::PFRecTrackCollection::const_iterator itend=pfRecTracks_->end();
  for(;it!=itend;++it)
    {
      if(it->trackRef()==ref)
	return &(*it);
    }
  return 0;
}

void PFCandidateAnalyzer::setIsoDeposits(PF::Particle& particle, const reco::PFCandidate& pfCandidate) const{
  std::cout << "test" <<std::endl;
  reco::isodeposit::Direction pfDir(pfCandidate.eta(), pfCandidate.phi());
  reco::IsoDeposit::Veto veto;
  veto.vetoDir = pfDir;
  veto.dR = 0.05; 

  std::vector<PF::IsoDeposit> deps;
  //initialization
  for(int i=0; i<4 ; i++){
    PF::IsoDeposit dep(pfDir);
    //dep.setVeto(veto);
    deps.push_back(dep);
  }

  for(reco::PFCandidateCollection::const_iterator ci  = pfCandidates_->begin(); ci!=pfCandidates_->end(); ++ci) {  
    const reco::PFCandidate& pfc = *ci;
    if( &pfCandidate == &pfc) continue; 
    LorentzVector pvi(pfc.p4());
    reco::isodeposit::Direction dirPfc(pfc.eta(), pfc.phi());
    double dR = pfDir.deltaR(dirPfc);
    if(dR > maxDeltaRForIsoDep_) continue;
    double et = pvi.Et();
    deps[0].addDeposit(dirPfc, et); //all
    if( pfc.particleId() == 1) deps[1].addDeposit(dirPfc, et); //charged
    if( pfc.particleId() == 5) deps[2].addDeposit(dirPfc, et); //neutral
    if( pfc.particleId() == 4) deps[3].addDeposit(dirPfc, et); //gamma
  }

  particle.setIsoDeposit(deps);
 
}
       
