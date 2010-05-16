#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/SourceFactory.h"
DEFINE_SEAL_MODULE();

#include "FWCore/ServiceRegistry/interface/ServiceMaker.h"

#include "DQM/RPCHistoricInfoClient/plugins/RPCHistoryDQMService.h"
DEFINE_ANOTHER_FWK_SERVICE(RPCHistoryDQMService);

#include "CondCore/PopCon/interface/PopConAnalyzer.h"
#include "DQMServices/Diagnostic/interface/DQMHistoryPopConHandler.h"
typedef popcon::PopConAnalyzer< popcon::DQMHistoryPopConHandler<RPCHistoryDQMService > > RPCDQMHistoryPopCon;
DEFINE_ANOTHER_FWK_MODULE(RPCDQMHistoryPopCon);
