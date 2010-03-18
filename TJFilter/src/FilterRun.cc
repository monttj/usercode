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

class FilterRun : public edm::EDFilter {
   public:
      explicit FilterRun(const edm::ParameterSet&);
      ~FilterRun();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      std::vector<int> run_;
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
FilterRun::FilterRun(const edm::ParameterSet& iConfig)
 : run_(iConfig.getUntrackedParameter< std::vector<int> >("runs")),
   applyfilter_(iConfig.getUntrackedParameter<bool>("applyRunFilter",true))   
{
   //now do what ever initialization is needed

}


FilterRun::~FilterRun()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
FilterRun::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  if (!applyfilter_)
    return true;

  int irun = iEvent.id().run();

  bool accepted = false;
  for(size_t i=0; i< run_.size() ; i++){
    if (irun == run_[i]) {
      accepted=true;
      break;
    }
  }
  return accepted;
}

// ------------ method called once each job just before starting event loop  ------------
void 
FilterRun::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FilterRun::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(FilterRun);
