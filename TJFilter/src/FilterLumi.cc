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

class FilterLumi : public edm::EDFilter {
   public:
      explicit FilterLumi(const edm::ParameterSet&);
      ~FilterLumi();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
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
FilterLumi::FilterLumi(const edm::ParameterSet& iConfig)
 : applyfilter_(iConfig.getUntrackedParameter<bool>("applyLumiFilter",true))   
{
   //now do what ever initialization is needed

}


FilterLumi::~FilterLumi()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
FilterLumi::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  if (!applyfilter_)
    return true;

  unsigned int irun = iEvent.id().run();


  bool accepted = false;
  unsigned int ilum = iEvent.luminosityBlock();

  if (irun==123596) {
    if ( (ilum>=69 && ilum<=144) )
      accepted=true;
  } else if (irun==123615) {
    if(ilum>=71) 
      accepted=true;
  } else if (irun==123732) {
    if(ilum>=57) 
      accepted=true;
  }

  return accepted;
}

// ------------ method called once each job just before starting event loop  ------------
void 
FilterLumi::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FilterLumi::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(FilterLumi);
