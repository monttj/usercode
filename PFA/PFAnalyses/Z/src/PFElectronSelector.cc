#include "PFAnalyses/Z/interface/PFElectronSelector.h"

#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"

#include <vector>
#include <iostream>

#include "Math/VectorUtil.h"
#include "TMath.h"

using namespace std;
using namespace reco;
using namespace reco::isodeposit;

PFElectronSelector::PFElectronSelector()
  : version_(V_NONE), verbose_(false), isoParForCharged_( vector<double>(4,1.0) ),
    isoParForNeutral_( vector<double>(4,1.0) ),
    isoParForPhotons_( vector<double>(4,1.0) ),
    isoParForRectangularVeto_( vector<double>(2,1.0) ) {

  typedef std::vector<IsoDeposit::Veto> Vetos;

  /// push back selections    /// set selections to be taken into account
  push_back("PT", 0.);              set("PT");
  push_back("E",  0.);              set("E");
  push_back("ABSOLUTE_ISO",0.);     set("ABSOLUTE_ISO");
  push_back("RELATIVE_ISO",0.);     set("RELATIVE_ISO");
  push_back("INDEPENDENT_ISO");     set("INDEPENDENT_ISO");
  push_back("ABSOLUTE_ISO_RECT",0.);   set("ABSOLUTE_ISO_RECT");
  push_back("RELATIVE_ISO_RECT",0.);   set("RELATIVE_ISO_RECT");
  push_back("INDEPENDENT_ISO_RECT");set("INDEPENDENT_ISO_RECT");

}


void PFElectronSelector::initialize( const edm::ParameterSet& ps ) {

  initialize( static_cast<Version_t>( ps.getParameter<int>("version") ),
	      ps.getParameter<double>("PT"),
	      ps.getParameter<double>("E"),
	      ps.getParameter<double>("absoluteIso"),
	      ps.getParameter<double>("relativeIso") );

  verbose_ = ps.getUntrackedParameter<bool>("verbose", false);
  isoParForCharged_ = ps.getParameter< vector<double> >("isoParForCharged");
  isoParForNeutral_ = ps.getParameter< vector<double> >("isoParForNeutral");
  isoParForPhotons_ = ps.getParameter< vector<double> >("isoParForPhotons");
  isoParForRectangularVeto_ = ps.getParameter< vector<double> >("isoParForRectangularVeto");

  if( (considerCut("ABSOLUTE_ISO") || considerCut("RELATIVE_ISO") || considerCut("INDEPENDENT_ISO") ) && 
      (isoParForCharged_.size()!=4 ||
       isoParForNeutral_.size()!=4 ||
       isoParForPhotons_.size()!=4
       ) ) throw "PFElectronSelector: undefined iso parameters!" ;

  if( (considerCut("ABSOLUTE_ISO_RECT") || considerCut("RELATIVE_ISO_RECT") || considerCut("INDEPENDENT_ISO_RECT") ) && 
      isoParForRectangularVeto_.size()!=2)  throw "PFElectronSelector: undefined iso parameters!" ;
 

}

void PFElectronSelector::initialize(Version_t version,
				    double PT, double E, 
				    double absoluteIso, double relativeIso ) {
  version_ = version;
  set("PT", PT);
  set("E",E);
  set("ABSOLUTE_ISO",absoluteIso);
  set("RELATIVE_ISO",relativeIso);
  set("ABSOLUTE_ISO_RECT",absoluteIso);
  set("RELATIVE_ISO_RECT",relativeIso);
}


bool PFElectronSelector::operator()( const pat::Electron & electron, std::strbitset & ret ) {
  if ( version_ == APRIL10 ) return april10Cuts( electron, ret );

  else {
    throw "PFElectronSelector: undefined version!";
  }
}


bool PFElectronSelector::april10Cuts( const pat::Electron& electron,
				      std::strbitset & ret)  {    
  
  if(verbose_) cout<<"Selecting electron: pT= "
		   <<electron.pt()
		   <<" , E= "
		   <<electron.p4().E()
		   <<" , eta= "
		   <<electron.eta()
		   <<endl;

  if( ignoreCut("PT") || electron.pt() > cut("PT", double() ) ) {
    passCut( ret, "PT");  
  }
  if(ignoreCut("E") || electron.p4().E() > cut("E",double() )) {
    passCut( ret, "E");
  }


  double chIso = (electron.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin( isoParForCharged_[0], Vetos(), isoParForCharged_[1],false ).first) * isoParForCharged_[2];
  double nhIso = (electron.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin( isoParForNeutral_[0], Vetos(), isoParForNeutral_[1],false ).first) * isoParForNeutral_[2];
  double phIso = (electron.isoDeposit(pat::PfGammaIso)->depositAndCountWithin( isoParForPhotons_[0], Vetos(), isoParForPhotons_[1],false ).first) * isoParForPhotons_[2];

  if(verbose_) cout << "Ch iso = "
		    << chIso
		    << " , Nh iso = "
		    << nhIso
		    << " , Ph iso = "
		    << phIso
		    << endl;


  if(ignoreCut("ABSOLUTE_ISO") || ((chIso + nhIso + phIso) < cut("ABSOLUTE_ISO",double())) ) {
    passCut( ret, "ABSOLUTE_ISO");
  }
  if(ignoreCut("RELATIVE_ISO") || ((chIso + nhIso + phIso)/(electron.pt()) < cut("RELATIVE_ISO",double()) )) {
    passCut( ret, "RELATIVE_ISO");
  }

  bool isIndependentCut = (chIso < isoParForCharged_[3]) && (nhIso < isoParForNeutral_[3]) && (phIso < isoParForPhotons_[3]) ;

  if(ignoreCut("INDEPENDENT_ISO") || isIndependentCut ) {
    passCut( ret, "INDEPENDENT_ISO");
  }

 
  /// add a rectangular veto on the photons deposit

  
  double etaVeto = isoParForRectangularVeto_[0];
  double phiVeto = isoParForRectangularVeto_[1];

  Direction eleDirection(electron.eta(), electron.phi());
  AbsVetos photonVetos;
  photonVetos.push_back( new RectangularEtaPhiVeto(eleDirection, -etaVeto, etaVeto, -phiVeto,phiVeto ));
  photonVetos.push_back( new ThresholdVeto( isoParForPhotons_[1] ) );
  double phIsoRect = (electron.isoDeposit(pat::PfGammaIso)->depositAndCountWithin( isoParForPhotons_[0], photonVetos ,isoParForPhotons_[1]).first) * isoParForPhotons_[2];

  if(ignoreCut("ABSOLUTE_ISO_RECT") || ((chIso + nhIso + phIsoRect) < cut("ABSOLUTE_ISO_RECT",double())) ) {
    passCut( ret, "ABSOLUTE_ISO_RECT");
  }
  if(ignoreCut("RELATIVE_ISO_RECT") || ((chIso + nhIso + phIsoRect)/(electron.pt()) < cut("RELATIVE_ISO_RECT",double()) )) {
    passCut( ret, "RELATIVE_ISO_RECT");
  }

  bool isIndependentCutRect = (chIso < isoParForCharged_[3]) && (nhIso < isoParForNeutral_[3]) && (phIsoRect < isoParForPhotons_[3]) ;

  if(ignoreCut("INDEPENDENT_ISO_RECT") || isIndependentCutRect ) {
    passCut( ret, "INDEPENDENT_ISO_RECT");
  }


  for(unsigned i = 0; i < photonVetos.size(); i++ ){
    delete photonVetos[i];
  }


  /// set to '1' the bits that you want to skip
  setIgnored( ret );
  
  if(verbose_) ret.print( cout );

  return (bool)ret;
}


