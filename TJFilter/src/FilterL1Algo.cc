// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
// global trigger stuff
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerEvmReadoutRecord.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutCollection.h"


//
// class declaration
//
using namespace edm;
using namespace std;

class FilterL1Algo : public edm::EDFilter {
   public:
      explicit FilterL1Algo(const edm::ParameterSet&);
      ~FilterL1Algo();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      std::vector<int> algobits_;
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
FilterL1Algo::FilterL1Algo(const edm::ParameterSet& iConfig)
 : algobits_(iConfig.getUntrackedParameter< std::vector<int> >("algobits")),
   applyfilter_(iConfig.getUntrackedParameter<bool>("applyFilter",true))   
{
   //now do what ever initialization is needed

}


FilterL1Algo::~FilterL1Algo()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
FilterL1Algo::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  if (!applyfilter_)
    return true;

  bool accepted = false;

  using namespace edm;

  //int fBX = iEvent.bunchCrossing();  // LHC bunch crossing;
  /// get Global Trigger algo and technical triger bit statistics
  Handle<L1GlobalTriggerReadoutRecord> gtReadoutRecord;
  iEvent.getByLabel("gtDigis",gtReadoutRecord);

  const DecisionWord& gtDecisionWord = gtReadoutRecord->decisionWord();

  int dbitNumber = 0;
  DecisionWord::const_iterator GTdbitItr;
  for(GTdbitItr = gtDecisionWord.begin(); GTdbitItr != gtDecisionWord.end(); GTdbitItr++) {
    if (*GTdbitItr) {
      //      cout << "Trigger Bit Number " << dbitNumber << endl;
      for(size_t i=0; i < algobits_.size() ; i++){    
        if (dbitNumber == algobits_[i]) accepted = true; // beamHalo trigger
      }
    }
    dbitNumber++;
  }

  //for (int ibx=-2; ibx<3; ibx++) {
  //  const DecisionWord& gtDecisionWord = gtReadoutRecord->decisionWord(ibx);

  //  int dbitNumber = 0;
  //  DecisionWord::const_iterator GTdbitItr;
  //  for(GTdbitItr = gtDecisionWord.begin(); GTdbitItr != gtDecisionWord.end(); GTdbitItr++) {
  //    if (*GTdbitItr) {
        //      cout << "Trigger Bit Number " << dbitNumber << endl;
  //      if (dbitNumber == 54) cout << "LHC BX " << fBX << " trg BX " << ibx << " trg54" << endl;
  //      if (dbitNumber == 55) cout << "LHC BX " << fBX << " trg BX " << ibx << " trg55" << endl;
  //    }
  //    dbitNumber++;
  //  }
  //}


  return accepted;
}

// ------------ method called once each job just before starting event loop  ------------
void 
FilterL1Algo::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FilterL1Algo::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(FilterL1Algo);
