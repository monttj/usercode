#ifndef GUARD_HDQMInspectorConfigRPC_h
#define GUARD_HDQMInspectorConfigRPC_h

#include <string>
#include <boost/shared_ptr.hpp>

#include "DQMServices/Diagnostic/interface/HDQMInspectorConfigBase.h"
#include "DQM/RPCHistoricInfoClient/interface/RPCDetIdStringAssociation.h"
// #include "DQM/RPCHistoricInfoClient/plugins/RPCDetIdStringAssociation.h"

class HDQMInspectorConfigRPC : public HDQMInspectorConfigBase
{
 public:
  HDQMInspectorConfigRPC();
  virtual ~HDQMInspectorConfigRPC();
    
  std::string translateDetId(const uint32_t) const;
  // boost::shared_ptr<RPCDetIdStringAssociation> _strAssoc;
  RPCDetIdStringAssociation * _strAssoc;
};

#endif
