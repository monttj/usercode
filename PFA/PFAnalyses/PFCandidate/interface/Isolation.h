#ifndef __PFAnalyses_PFCandidate_Isolation__
#define __PFAnalyses_PFCandidate_Isolation__

#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"

namespace PF {
 
  typedef reco::IsoDeposit IsoDeposit;

  /// Enum defining isolation keys
  enum IsolationKeys { TrackIso=0, EcalIso=1, HcalIso=2, 
                       PfAllParticleIso=3,PfChargedHadronIso=4, PfNeutralHadronIso=5, PfGammaIso=6,
                       User1Iso=7, User2Iso=8, User3Iso=9, User4Iso=10, User5Iso=11,
                       UserBaseIso=7, // offset of the first user isolation
                       CaloIso=-1     // keys which are not real indices are mapped to negative numbers.
  };

}

#endif

