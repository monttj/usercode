#include "PFAnalyses/Z/interface/PatMuonSelector.h"

#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"

#include <vector>
#include <iostream>

#include "Math/VectorUtil.h"
#include "TMath.h"

using namespace std;
using namespace reco;

PatMuonSelector::PatMuonSelector()
  : version_(V_NONE), verbose_(false){

  /// push back selections    /// set selections to be taken into account
  push_back("PT", 0.);              set("PT");
  push_back("E",  0.);              set("E");

}


void PatMuonSelector::initialize( const edm::ParameterSet& ps ) {

  initialize( static_cast<Version_t>( ps.getParameter<int>("version") ),
	      ps.getParameter<double>("PT"),
	      ps.getParameter<double>("E") );

  verbose_ = ps.getUntrackedParameter<bool>("verbose", false);

}

void PatMuonSelector::initialize(Version_t version,
				    double PT, double E ) {
  version_ = version;
  set("PT", PT);
  set("E",E);
}


bool PatMuonSelector::operator()( const pat::Muon & muon, std::strbitset & ret ) {
  if ( version_ == APRIL10 ) return april10Cuts( muon, ret );

  else {
    throw "PatMuonSelector: undefined version!";
  }
}


bool PatMuonSelector::april10Cuts( const pat::Muon& muon,
				      std::strbitset & ret)  {    
  
  if(verbose_) cout<<"Selecting muon: pT= "
		   <<muon.pt()
		   <<" , E= "
		   <<muon.p4().E()
		   <<" , eta= "
		   <<muon.eta()
		   <<endl;

  if( ignoreCut("PT") || muon.pt() > cut("PT", double() ) ) {
    passCut( ret, "PT");  
  }
  if(ignoreCut("E") || muon.p4().E() > cut("E",double() )) {
    passCut( ret, "E");
  }

  /// set to '1' the bits that you want to skip
  setIgnored( ret );
  
  if(verbose_) ret.print( cout );

  return (bool)ret;
}


