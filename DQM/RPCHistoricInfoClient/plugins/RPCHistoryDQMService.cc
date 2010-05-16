#include "DQM/RPCHistoricInfoClient/plugins/RPCHistoryDQMService.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DQMServices/Core/interface/MonitorElement.h"
#include "DQMServices/Diagnostic/interface/HDQMfitUtilities.h"
#include "TH1F.h"
#include "TF1.h"

using namespace std;
RPCHistoryDQMService::RPCHistoryDQMService(const edm::ParameterSet& iConfig,const edm::ActivityRegistry& aReg)
: DQMHistoryServiceBase::DQMHistoryServiceBase(iConfig, aReg), iConfig_(iConfig){
  edm::LogInfo("RPCHistoryDQMService") <<  "[RPCHistoryDQMService::RPCHistoryDQMService]";
  
  _strAss = new RPCDetIdStringAssociation;
}

RPCHistoryDQMService::~RPCHistoryDQMService() { 
  edm::LogInfo("RPCHistoryDQMService") <<  "[RPCHistoryDQMService::~RPCHistoryDQMService]";
}

uint32_t RPCHistoryDQMService::returnDetComponent(const MonitorElement* ME){
  LogTrace("RPCHistoryDQMService") <<  "[RPCHistoryDQMService::returnDetComponent]";
  string str=ME->getName();

  //cout << "ME= " << str << endl;
  if ( str.find("RPCChamberQuality_Distribution_Wheel")!=string::npos){
    str.replace(str.find("RPCChamberQuality_Distribution_Wheel"), 36, "RPCChamberQuality_Distribution_Wheel_");
  }
  if ( str.find("RPCChamberQuality_Distribution_Disk")!=string::npos ){
    str.replace(str.find("RPCChamberQuality_Distribution_Disk"), 35, "RPCChamberQuality_Distribution_Disk_");
  } 
  //cout << "modified ME= " << str << endl;

  vector<string> vstring;
  
  size_t i = 0;
  while( i != str.size()) {
    while( i != str.size() && str[i] == '_')
      i++;
    size_t j=i;
    while( j != str.size() && str[j] != '_')
      ++j;
    if( i != j) {
      vstring.push_back(str.substr(i, j-i));
      i = j;
    }
  }
  cout<< "VString size: "<< vstring.size()<< endl;

  //FED errors
  if(str.find("FEDFatal")!= string::npos){
    return _strAss->getKeyStringValue("RPC");
  }

  string globname;
  if(vstring.size() == 2) globname = vstring[0].substr(vstring[0].find("o")+1,string::npos)+"_" + vstring[1];
  if(vstring.size() == 3 ) globname = vstring[1]+"_" + vstring[2];
  if(vstring.size() == 4 ) globname = vstring[2]+"_" + vstring[3];
  if(vstring.size() == 5) globname = vstring[1]+"_" + vstring[2]+"_" + vstring[3]+"_" + vstring[4];

  for (unsigned int i = 0; i < vstring.size(); ++i)
    cout<<  vstring[i]<<endl;

  cout<<"Global name:  "<< globname << endl;

//   const map<string, int> &  prova =_strAss->getKeyString();
//   cout<< "Ho chiamato mappa" << &prova<< endl;
//   for(map<string,int>::const_iterator it = prova.begin(); it != prova.end(); ++it)
//     cout<< it->first<< "  "<< it->second<< endl;
  return _strAss->getKeyStringValue(globname);
//   if ((str.find("BxDistribution_")!= string::npos 
//        || str.find("ClusterSize_")!= string::npos)){
//     cout<<" Global PLots------"<<endl;
//     return _strAss->getKeyStringValue(globname); 
//   }
//   else if ((str.find("BXN_")!= string::npos || 
// 	    str.find("ClusterSize_")!= string::npos ||
// 	    str.find("Profile_")!= string::npos)){
        

//     return _strAss->getKeyStringValue(globname);
//   }
}

//Example on how to define an user function for the statistic extraction
bool RPCHistoryDQMService::setDBLabelsForUser  (string& keyName, vector<string>& userDBContent){
  userDBContent.push_back(keyName+string("@")+string("GlobalEfficiency"));
  userDBContent.push_back(keyName+string("@")+string("good")); //added by TJ
  userDBContent.push_back(keyName+string("@")+string("off")); //added by TJ
  userDBContent.push_back(keyName+string("@")+string("noiseSt")); //added by TJ
  userDBContent.push_back(keyName+string("@")+string("noiseCh")); //added by TJ
  userDBContent.push_back(keyName+string("@")+string("partDead")); //added by TJ
  userDBContent.push_back(keyName+string("@")+string("dead")); //added by TJ
  userDBContent.push_back(keyName+string("@")+string("badShape")); //added by TJ
  return true;
}

bool RPCHistoryDQMService::setDBValuesForUser(vector<MonitorElement*>::const_iterator iterMes, HDQMSummary::InputVector& values  ){
  float eff = 0.;
  TF1* f = new TF1("func","pol0",0.,90.);
  TH1F * h1 = (*iterMes)->getTH1F();
  h1->Fit(f);
  eff = f->GetParameter(0);
  values.push_back( eff );
  values.push_back( (*iterMes)->getTH1F()->GetBinContent(1) );
  values.push_back( (*iterMes)->getTH1F()->GetBinContent(2) );
  values.push_back( (*iterMes)->getTH1F()->GetBinContent(3) );
  values.push_back( (*iterMes)->getTH1F()->GetBinContent(4) );
  values.push_back( (*iterMes)->getTH1F()->GetBinContent(5) );
  values.push_back( (*iterMes)->getTH1F()->GetBinContent(6) );
  values.push_back( (*iterMes)->getTH1F()->GetBinContent(7) );
  
  return true;
}

