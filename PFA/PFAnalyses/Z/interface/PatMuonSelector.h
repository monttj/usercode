#ifndef PFAnalyses_Z_interface_PatMuonSelector_h
#define PFAnalyses_Z_interface_PatMuonSelector_h


/**
   \class PatMuonSelector    
   \brief    
*/
#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "PhysicsTools/SelectorUtils/interface/Selector.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"

#include <vector>

using namespace std;

class PatMuonSelector : public Selector<pat::Muon>  {

 public: // interface

  enum Version_t { APRIL10=0, V_NONE };
   
  PatMuonSelector();
  
  /// initialize all parameters and cuts from a parameter set
  void initialize( const edm::ParameterSet& ps );
  
  /// initialize all parameters and cuts 
  void initialize(Version_t version,
		  double PT, double E);

  /// does jet pass the cuts? 
  bool operator()( const pat::Muon & muon, std::strbitset & ret );

  /// kinematical cuts
  bool april10Cuts( const pat::Muon& muon, std::strbitset & ret  );

  
 private: // member variables
  
  typedef std::vector<reco::IsoDeposit::Veto> Vetos;

  Version_t version_;
  
  bool      verbose_;
  
};

#endif
