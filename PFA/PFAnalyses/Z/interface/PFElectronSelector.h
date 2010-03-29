#ifndef PFAnalyses_Z_interface_PFElectronSelector_h
#define PFAnalyses_Z_interface_PFElectronSelector_h


/**
   \class PFElectronSelector    
   \brief    
*/
#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "PhysicsTools/SelectorUtils/interface/Selector.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"

#include <vector>

using namespace std;

class PFElectronSelector : public Selector<pat::Electron>  {

 public: // interface

  enum Version_t { APRIL10=0, V_NONE };
   
  PFElectronSelector();
  
  /// initialize all parameters and cuts from a parameter set
  void initialize( const edm::ParameterSet& ps );
  
  /// initialize all parameters and cuts 
  void initialize(Version_t version,
		  double PT, double E,
		  double absoluteIso, double relativeIso );

  /// does jet pass the cuts? 
  bool operator()( const pat::Electron & electron, std::strbitset & ret );

  /// kinematical cuts
  bool april10Cuts( const pat::Electron& electron, std::strbitset & ret  );

  
 private: // member variables
  
  typedef std::vector<reco::IsoDeposit::Veto> Vetos;

  Version_t version_;
  
  bool      verbose_;
  
  /// parameters to configure the definitions of isodeposit
  vector<double> isoParForCharged_ ;
  vector<double> isoParForNeutral_;
  vector<double> isoParForPhotons_;
  vector<double> isoParForRectangularVeto_;
    
     
};

#endif
