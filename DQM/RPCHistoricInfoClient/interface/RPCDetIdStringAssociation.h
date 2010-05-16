#ifndef DQM_RPCHistoricInfoClient_RPCDetIdStringAssociation_H
#define DQM_RPCHistoricInfoClient_RPCDetIdStringAssociation_H
#include <map>
#include "Geometry/RPCGeometry/interface/RPCGeomServ.h"
#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include <FWCore/Framework/interface/ESHandle.h>


class RPCDetIdStringAssociation{
 public:

  explicit RPCDetIdStringAssociation();
  ~RPCDetIdStringAssociation() {}
  
  const std::map<std::string, int> &  getKeyString(){return _keyString;}
  const std::map<int,std::string> &  getKeyRawId(){return _keyRawId;}

  std::string getKeyRawIdValue(int id);
  int getKeyStringValue(std::string chname);
  std::string int2string(int i);

 private:

  void fillKeyString(std::string,int);
  void fillKeyRawId(int,std::string);

  std::map<std::string,int> _keyString;
  std::map<int, std::string> _keyRawId;

};

#endif //DQM_RPCHistoricInfoClient_RPCDetIdStringAssociation_H
