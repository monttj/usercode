// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <DataFormats/CSCRecHit/interface/CSCSegmentCollection.h>
//
// class declaration
//
using namespace edm;
using namespace std;

class FilterCSCSeg : public edm::EDFilter {
   public:
      explicit FilterCSCSeg(const edm::ParameterSet&);
      ~FilterCSCSeg();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      int min_;
      int max_;
      InputTag cscSegments_;
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
FilterCSCSeg::FilterCSCSeg(const edm::ParameterSet& iConfig)
 : min_(iConfig.getUntrackedParameter<int>("min")),
   max_(iConfig.getUntrackedParameter<int>("max")),
   cscSegments_(iConfig.getUntrackedParameter<InputTag>("cscSegments")),
   applyfilter_(iConfig.getUntrackedParameter<bool>("applyFilter",true))   
{
   //now do what ever initialization is needed

}


FilterCSCSeg::~FilterCSCSeg()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
FilterCSCSeg::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  if (!applyfilter_)
    return true;

  bool accepted = false;

  int nCSCSegpos = 0;
  int nCSCSegneg = 0;

  edm::Handle<CSCSegmentCollection> allCSCSegments;
  iEvent.getByLabel(cscSegments_, allCSCSegments);

  for (CSCSegmentCollection::const_iterator seg = allCSCSegments->begin(); seg!=allCSCSegments->end(); ++seg){
    CSCDetId CSCId = seg->cscDetId();
    if( CSCId.endcap() == 1 ) nCSCSegpos++;
    if( CSCId.endcap() == 2 ) nCSCSegneg++;
  }

  if( nCSCSegpos >= min_ && nCSCSegpos <= max_ && nCSCSegneg >= min_ && nCSCSegneg <=max_ ) accepted = true;

  return accepted;
}

// ------------ method called once each job just before starting event loop  ------------
void 
FilterCSCSeg::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FilterCSCSeg::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(FilterCSCSeg);
