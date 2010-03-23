// -*- C++ -*-
//
// Package:    FilterBX
// Class:      FilterBX
// 
/**\class FilterBX FilterBX.cc UserCode/FilterBX/src/FilterBX.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Tae Jeong Kim
//         Created:  Mon Dec 14 01:29:35 CET 2009
// $Id: FilterBX.cc,v 1.3 2010/03/18 21:24:18 tjkim Exp $
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

class FilterBX : public edm::EDFilter {
   public:
      explicit FilterBX(const edm::ParameterSet&);
      ~FilterBX();

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
FilterBX::FilterBX(const edm::ParameterSet& iConfig)
 : crossings_(iConfig.getUntrackedParameter< std::vector<int> >("crossings")),
   applyfilter_(iConfig.getUntrackedParameter<bool>("applyfilter",true))   
{
   //now do what ever initialization is needed

}


FilterBX::~FilterBX()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
FilterBX::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   if(!applyfilter_) return true;
   bool accepted = false;
   int bx = iEvent.bunchCrossing();
   for(unsigned int ibunch = 0; ibunch < crossings_.size(); ibunch++){
     if(bx == crossings_[ibunch]){
       accepted = true;
       break;
     }
   }

  return accepted;
}

// ------------ method called once each job just before starting event loop  ------------
void 
FilterBX::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FilterBX::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(FilterBX);
