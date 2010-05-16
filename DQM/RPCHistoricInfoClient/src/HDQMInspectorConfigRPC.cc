#include "DQM/RPCHistoricInfoClient/interface/HDQMInspectorConfigRPC.h"
// #include "DQM/RPCHistoricInfoClient/test/HDQMInspectorConfigRPC.h"
#include "Geometry/RPCGeometry/interface/RPCGeomServ.h"

#include <iostream>

using namespace std;

HDQMInspectorConfigRPC::HDQMInspectorConfigRPC ()
{
  // _strAssoc = boost::shared_ptr<RPCDetIdStringAssociation> (new RPCDetIdStringAssociation);
  _strAssoc = new RPCDetIdStringAssociation();
}

HDQMInspectorConfigRPC::~HDQMInspectorConfigRPC ()
{
}

std::string HDQMInspectorConfigRPC::translateDetId(const uint32_t id) const
{
  std::map<int,std::string>::const_iterator it = _strAssoc->getKeyRawId().find(id);
  if( it != _strAssoc->getKeyRawId().end() ) {
    cout << "String = " << it->second << endl;
    return it->second;
  }
  else {
    cout << "ERROR" << endl;

    return "0000";
  }
}
