// -*- C++ -*-
//
// Package:    TJFilter
// Class:      TJFilter
// 
/**\class TJFilter TJFilter.cc UserCode/TJFilter/src/TJFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Tae Jeong Kim
//         Created:  Mon Dec 14 01:29:35 CET 2009
// $Id: TJFilter.cc,v 1.1 2010/03/18 21:14:15 tjkim Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

//
// class declaration
//
using namespace edm;
using namespace std;

class TJFilter : public edm::EDFilter {
   public:
      explicit TJFilter(const edm::ParameterSet&);
      ~TJFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      std::vector<int> crossings_;
      int type_;
      bool applyfilter_;
      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TJFilter::TJFilter(const edm::ParameterSet& iConfig)
 : crossings_(iConfig.getUntrackedParameter< std::vector<int> >("crossings")),
   type_(iConfig.getUntrackedParameter<int>("coltype",1)),
   applyfilter_(iConfig.getUntrackedParameter<bool>("applyfilter",true))   
{
   //now do what ever initialization is needed

}


TJFilter::~TJFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
TJFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   bool accepted = false;
   int bx = iEvent.bunchCrossing();
   for(unsigned int ibunch = 0; ibunch < crossings_.size(); ibunch++){
     if(bx == crossings_[ibunch]){
       accepted = true;
       break;
     }
   }

  unsigned int irun = iEvent.id().run();

  if (irun==123596 || irun==123615) {
    if (type_==1) {
      if ((bx==51) || (bx==2724))
        accepted=true;
    } else if (type_==2) {
      if ((bx==2276) || (bx==3170))
        accepted=true;
    }
  } else if (irun==123732) {
    if (type_==1) {
      if ((bx==3487) || (bx==2596))
        accepted=true;
    } else if (type_==2) {
      if ((bx==2148) || (bx==3042))
        accepted=true;
    }
  }

  bool lumiblock = false;
  unsigned int ilum = iEvent.luminosityBlock();

  if (irun==123596) {
    if ( (ilum>=69 && ilum<=144) )
      lumiblock=true;
  } else if (irun==123615) {
    if(ilum>=71) 
      lumiblock=true;
  } else if (irun==123732) {
    if(ilum>=57) 
      lumiblock=true;
  }

  if(applyfilter_) {
    accepted = accepted && lumiblock;
  }

  return accepted;
}

// ------------ method called once each job just before starting event loop  ------------
void 
TJFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TJFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(TJFilter);
