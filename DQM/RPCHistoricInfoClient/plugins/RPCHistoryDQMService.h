#ifndef DQM_RPCHistoricInfoClient_RPCHistoryDQMService_H
#define DQM_RPCHistoricInfoClient_RPCHistoryDQMService_H

#include "DQMServices/Diagnostic/interface/DQMHistoryServiceBase.h" 
#include "DQM/RPCHistoricInfoClient/interface/RPCDetIdStringAssociation.h"
// #include "DQM/RPCHistoricInfoClient/plugins/RPCDetIdStringAssociation.h"
#include "boost/shared_ptr.hpp"
using namespace std;
class RPCHistoryDQMService : public DQMHistoryServiceBase {
 public:

  explicit RPCHistoryDQMService(const edm::ParameterSet&,const edm::ActivityRegistry&);
  ~RPCHistoryDQMService();
  
 private:
  //Methods to be specified by each subdet
  uint32_t returnDetComponent(const MonitorElement* ME);
  bool setDBLabelsForUser  (std::string& keyName, std::vector<std::string>& userDBContent);
  bool setDBValuesForUser(std::vector<MonitorElement*>::const_iterator iterMes, HDQMSummary::InputVector& values  );
   
  edm::ParameterSet iConfig_;
  // boost::shared_ptr<RPCDetIdStringAssociation> _strAss;
  RPCDetIdStringAssociation* _strAss;
};

#endif //DQM_RPCHistoricInfoClient_RPCHistoryDQMService_H
