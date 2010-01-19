#ifndef __PFAnalyses_PFCandidate_TreePFCandidate__
#define __PFAnalyses_PFCandidate_TreePFCandidate__

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "Math/GenVector/VectorUtil.h"

namespace PF {
  
  typedef math::PtEtaPhiMLorentzVector LorentzVector;

    
  class Particle : public LorentzVector {
  public:
    Particle() : type_(reco::PFCandidate::X) {}
      Particle( const LorentzVector& mom, int type ) 
	: LorentzVector(mom), type_(type) {}
    int type() const { return type_; }
  private:
    int type_;
  };

  class PhotonPSInfo {
  public:
  PhotonPSInfo() : sumE_(0) {}
    void addPS( const math::XYZPoint& pos, float E) {
      z_ = pos.z();
      positions_.push_back(pos);
      sumE_ += E; 
    }
    int size() const {return positions_.size();}
    
  private:
    std::vector<math::XYZPoint> positions_;
    float              sumE_;
    float              z_;
  };

  
  

  // classes for the various types of PFCandidates
  // depending on the type, the information stored will 
  // be different, hence different classes
  
  class Photon : public Particle {
  public:
    Photon() {}
    virtual ~Photon() {}
  Photon( const LorentzVector& mom, 
	  const reco::PFCluster& clust) 
    : Particle( mom, reco::PFCandidate::gamma ), cluster_ (clust) {}
  Photon( const  ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >& mom, 
	  const reco::PFCluster& clust)
    : Particle( LorentzVector(mom), reco::PFCandidate::gamma ), cluster_ (clust) {}
    

    PhotonPSInfo&  ps1() {return ps1_;};
    PhotonPSInfo&  ps2() {return ps2_;};
    
  private:
    PhotonPSInfo ps1_;
    PhotonPSInfo ps2_;
    reco::PFCluster cluster_;
  };

  
  class Electron: public Particle{
  public:
    Electron() {}
    virtual ~Electron(){}
    
    Electron(const LorentzVector& mom,
	     int charge) : Particle(mom, reco::PFCandidate::e), charge_(charge) {}
    Electron(const  ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >& mom,
	     int charge): Particle( LorentzVector(mom), reco::PFCandidate::e), charge_(charge) {}    
    void addCluster(const math::XYZPoint & pos, float E){
      clusterPos_.push_back(pos);
      clusterE_.push_back(E);
    }

    void setMVA(float m) {
      mva_ = m;
    }
    // Gsf
    void setGsfTrackIn(const math::XYZPoint & pos, const math::XYZVector & mom)    {
      gsfPin_=mom;
      gsfPosin_=pos;
    }
    void setGsfTrackOut(const math::XYZPoint & pos, const math::XYZVector & mom)     {
      gsfPout_=mom;
      gsfPosout_=pos;
    }
    void setGsfOutMean(const math::XYZVector & mom){
      gsfPoutMean_=mom;
    }
    void setGsfInMean(const math::XYZVector & mom){
      gsfPinMean_=mom;
    }
    void setGsfInMode(const math::XYZVector & mom){
      gsfPinMode_=mom;
    }
    void setGsfNhits(unsigned n)     {
      gsfNhits_=n;
    }
    void setGsfdptopt(float gsfdptopt) {
      gsfdptopt_ = gsfdptopt;
    }    
    void setGsfChi2(float gsfchi2){
      gsfChi2_= gsfchi2;
    }
    
    // KF
    void setKfTrackIn(const math::XYZPoint & pos, const math::XYZVector & mom)    {
      kfPin_=mom;
      kfPosin_=pos;
    }
    void setKfTrackOut(const math::XYZPoint & pos, const math::XYZVector & mom)      {
      kfPout_=mom;
      kfPosout_=pos;
    }
    void setKfNhits(float kfnhits) { kfnhits_ = kfnhits;}
    void setKfChi2(float kfchi2) {kfchi2_ = kfchi2;}
    void setKfCharge(int charge){
      kfcharge_=charge;
    }
    
    // Ecal
    void setTotalEcal(float e) {
      totalEcal_=e;
    }
    void setSeedEcal (float eseed){
      seedEcal_ = eseed;
    }
    void setPosEcal( const math::XYZPoint& pos ) { posEcal_ = pos;}
    void setSigmaEtaEta(float sigmaetaeta){
      sigmaetaeta_ = sigmaetaeta;
    }

    // PS
    void setPS(float ps1,float ps2) {
      ps1E_=ps1;
      ps2E_=ps2;
    }
    
    void setTrackerDrivenSeed ( int trackerDriven) {  
      isTrackerDriven_ = trackerDriven;
    }
    void setEcalDrivenSeed ( int ecalDriven) {  
      isEcalDriven_ = ecalDriven;
    }
 
    void setDistance( float distance) {
      distanceGsfEcal_ = distance;
    }
    void setEarlyBrem( int earlybrem) {
      earlyBrem_ = earlybrem;
    }
    void setLateBrem( int latebrem) {
      lateBrem_ = latebrem;
    }
    void setHcal(float hcalene) {
      hcalene_ = hcalene;
    }
    
    
  public:
       float mva() {return mva_;}
       float ps1() {return ps1E_;}
       float ps2() {return ps2E_;}
       float Etot() {return totalEcal_;}
       float Eseed() {return seedEcal_;}
       float Ebrem() {return totalEcal_-seedEcal_;}
       float pin() {return std::sqrt(gsfPinMode_.Mag2());}
       float pout() {return std::sqrt(gsfPout_.Mag2());}
       float pinMean() {return std::sqrt(gsfPinMean_.Mag2());}
       float poutMean() {return std::sqrt(gsfPoutMean_.Mag2());}
       math::XYZPoint in() {return gsfPosin_;}
       math::XYZPoint out() {return gsfPosout_;}

       float kfpin() {return std::sqrt(kfPin_.Mag2());}
       float kfpout() {return std::sqrt(kfPout_.Mag2());}
       math::XYZPoint kfin() {return kfPosin_;}
       math::XYZPoint kfout() {return kfPosout_;}
       float Eop() {return totalEcal_/pin();}
       float Eseedopout(){return seedEcal_/pout();}
       float EbremDp(){return Ebrem()/(pin() - pout());}
       //       float Eseedopout() {return (clusterE_.size()>0) ? clusterE_[0]/pout() : 0. ;}
       
       float fbrem() {
	 float p_in=pin();
	 if(p_in==0.) return -99;
	 return ((p_in-pout())/p_in);
       }
       unsigned Nclusters() {
	 return clusterE_.size(); 
       }
       
       float detaEcal() {return (clusterPos_.size() >0) ? 
	   posEcal_.eta() - clusterPos_[0].eta()  : 0. ;}
       
       float dphiEcal() {return (clusterPos_.size() >0) ? 
	   ROOT::Math::VectorUtil::DeltaPhi(posEcal_,clusterPos_[0])  : 0. ;}

       int isEcalDriven() { return isEcalDriven_;}
       int isTrackerDriven() { return isTrackerDriven_;}
       int charge() { return charge_;}
       int kfcharge() {return kfcharge_;}
       float distanceGsfEcal() { return distanceGsfEcal_;}
       float sigmaEtaEta() {return sigmaetaeta_;}
       float HoHE() {return hcalene_/(hcalene_+seedEcal_);}
      
  private:
       float totalEcal_;
       float seedEcal_;
       int charge_;
       int kfcharge_;
       float kfchi2_;
       float kfnhits_;
       float ps1E_;
       float ps2E_;
       float mva_;
       float distanceGsfEcal_;
       math::XYZVector gsfPin_;
       math::XYZVector gsfPout_;
       math::XYZVector gsfPinMean_;
       math::XYZVector gsfPinMode_;
       math::XYZVector gsfPoutMean_;
       math::XYZPoint gsfPosin_;
       math::XYZPoint gsfPosout_;
       unsigned gsfNhits_;
       float gsfChi2_;
       float gsfdptopt_;
       math::XYZVector kfPin_;
       math::XYZVector kfPout_;
       math::XYZPoint kfPosin_;
       math::XYZPoint kfPosout_;
       std::vector<math::XYZPoint> clusterPos_;
       std::vector<float>  clusterE_;
       math::XYZPoint   posEcal_;
       int isEcalDriven_;
       int isTrackerDriven_;
       float sigmaetaeta_;
       int lateBrem_;
       int earlyBrem_;
       float hcalene_;

  };
  
  
  class ChargedHadron : public Particle {
  public:
    ChargedHadron() {}
    virtual ~ChargedHadron() {}
  ChargedHadron( const LorentzVector& mom, 
		 double ecal, double hcal, int id) 
    : Particle( mom, reco::PFCandidate::h),
      ecalRaw_(ecal), 
      hcalRaw_(hcal), 
      id_(id) { setChargeInfo(-1.,-1.,-1.,-1.,-1.,-1.,0,0,0);} 
    
    void setChargeInfo(double distEcal, double distHcal, 
		       double ecal, double hcal, 
		       double drg, double drh,
		       unsigned int nHits=0, unsigned int inner=0, unsigned int outer=0) {
      distEcal_= distEcal;
      distHcal_= distHcal;
      ecal_ = ecal;
      hcal_ = hcal;
      drg_ = drg;
      drh_ = drh;
      nHits_ = nHits;
      inner_ = inner;
      outer_ = outer;
    }

    double ecalRaw() const { return ecalRaw_; }
    double hcalRaw() const { return hcalRaw_; }
    double ecal() const { return ecal_; }
    double hcal() const { return hcal_; }
    double distEcal() const { return distEcal_; }
    double distHcal() const { return distHcal_; }
    double drg() const { return drg_; }
    double drh() const { return drh_; }
    int id() const { return id_; }
    unsigned nHits() const { return nHits_; } 
    unsigned inner() const { return inner_; } 
    unsigned outer() const { return outer_; } 

    void setPosEcal( const math::XYZPoint& pos ) { posEcal_ = pos;}


  private:
    double ecalRaw_;
    double hcalRaw_;
    int id_;
    double distEcal_;
    double distHcal_;
    double ecal_;
    double hcal_;
    double drg_;
    double drh_;
    unsigned int nHits_;
    unsigned int inner_;
    unsigned int outer_;
    
    math::XYZPoint   posEcal_;

  };

  
  class Muon : public Particle {
  public:
    Muon() {}
    virtual ~Muon() {}
  Muon( const LorentzVector& mom, 
		 double ecal, double hcal, int id) 
    : Particle( mom, reco::PFCandidate::mu ),
      ecalRaw_(ecal), 
      hcalRaw_(hcal), 
      id_(id) { setChargeInfo(-1.,-1.,-1.,-1.,-1.,-1.);} 
    
    void setChargeInfo(double distEcal, double distHcal, 
		       double ecal, double hcal, 
		       double drg, double drh) {
      distEcal_= distEcal;
      distHcal_= distHcal;
      ecal_ = ecal;
      hcal_ = hcal;
      drg_ = drg;
      drh_ = drh;
    }

    double ecalRaw() const { return ecalRaw_; }
    double hcalRaw() const { return hcalRaw_; }
    double ecal() const { return ecal_; }
    double hcal() const { return hcal_; }
    double distEcal() const { return distEcal_; }
    double distHcal() const { return distHcal_; }
    double drg() const { return drg_; }
    double drh() const { return drh_; }
    int id() const { return id_; }

    void setPosEcal( const math::XYZPoint& pos ) { posEcal_ = pos;}


  private:
    double ecalRaw_;
    double hcalRaw_;
    int id_;
    double distEcal_;
    double distHcal_;
    double ecal_;
    double hcal_;
    double drg_;
    double drh_;
    
    math::XYZPoint   posEcal_;

  };
  


 
}
#endif
