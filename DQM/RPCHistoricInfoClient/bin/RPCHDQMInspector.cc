#include "DQMServices/Diagnostic/interface/HDQMInspector.h"
#include "DQMServices/Diagnostic/interface/DQMHistoryTrendsConfig.h"
#include "DQMServices/Diagnostic/interface/DQMHistoryCreateTrend.h"
#include "DQM/RPCHistoricInfoClient/interface/RPCDetIdStringAssociation.h"
#include "DQM/RPCHistoricInfoClient/interface/HDQMInspectorConfigRPC.h"
#include <sstream>
#include <string>

using namespace std;
void runRPCInspector( const string & dbName, const string &tagName, const string & Password, const string & whiteListFile,
		      const int Start, const int End, const int nRuns )
{
  // IMPORTANT SETTINGS:
  string condition = "";
  string blackList = "";
  // -------------------

  HDQMInspectorConfigRPC RPCconfig;
  DQMHistoryCreateTrend makeTrend(&RPCconfig);

  RPCDetIdStringAssociation* _strAssoc = new RPCDetIdStringAssociation();
  const map<string, int> &  mapKeyString =_strAssoc->getKeyString();

  // Database and output configuration
  //  makeTrend.setDB("oracle://cms_orcoff_prep/CMS_DQM_31X_OFFLINE",tagName,"cms_dqm_31x_offline", Password,"");
  makeTrend.setDB(dbName, tagName,"cms_dqm_31x_offline", Password,"");
  makeTrend.setDebug(1);
  makeTrend.setDoStat(1);
  makeTrend.setBlackList(blackList);
  makeTrend.setWhiteListFromFile(whiteListFile);

  // Definition of trends
  typedef DQMHistoryTrendsConfig Trend;
  vector<Trend> config;

  vector<string> vstring;
  vstring.clear();
  stringstream label;

  for (int w = -2 ; w<=2; w++) {
    label.str("");
    label<<"Wheel_"<<w;
    vstring.push_back(label.str());

    label.str("");
    label<<"Wheel_"<<w<<"near";
    vstring.push_back(label.str());
  
    label.str("");
    label<<"Wheel_"<<w<<"far";
    vstring.push_back(label.str());
  }

  for (int d = -3 ; d<=3; d++) {
    if(d==0) continue;
    label.str("");
    label<<"Disk_"<<d;
    vstring.push_back(label.str());

    label.str("");
    label<<"Disk_"<<d<<"near";
    vstring.push_back(label.str());
  
    label.str("");
    label<<"Disk_"<<d<<"far";
    vstring.push_back(label.str());
  }

  // Added by TJ to get FEDFatal plot
  label.str("");
  label<<"RPC";
  vstring.push_back(label.str());


  //Loop on all labels and fill cinfig vector
  for(vector<string>::iterator it = vstring.begin(); it != vstring.end(); ++it ){
    map<string,int>::const_iterator itmap = mapKeyString.find(*it);
    if(itmap != mapKeyString.end()){
    
      stringstream temp;
      temp.str("");
      temp<<itmap->second;
 
      cout << "DEBUG: " << itmap->first << " " << temp.str() << endl;

      if((itmap->first).find("RPC") != string::npos ){
        cout << "FEDFatal ************ " << endl;
	stringstream out;
	out.str("");
	out<<itmap->second;
	
	string fedFatal =string(out.str()) +"@FEDFatal@mean";
	string nameFedFatal = "FEDFatal.gif";
	config.push_back(Trend( fedFatal.c_str(), nameFedFatal.c_str(), 0, condition, "", Start, End, nRuns ));
	
      }else if((itmap->first).find("near") == string::npos && 
	      (itmap->first).find("far") == string::npos){
	
	stringstream out;
	out << itmap->second;
	
	string bxmean = string(out.str())+"@BxDistribution_@mean";
	string namebxmean = "BxDistribution_"+string(itmap->first)+".gif";
	
	string clsmean = string(out.str())+"@ClusterSize_@mean";
	string nameclsmean = "ClusterSize_"+string(itmap->first)+".gif";

        string noiseCh = string(out.str())+"@RPCChamberQuality_Distribution_@noiseCh";
        string namenoiseCh = "RPCChamberQuality_Noise_Chamber_"+string(itmap->first)+".gif";

        config.push_back(Trend( bxmean.c_str(), namebxmean.c_str(), 0, condition, "", Start, End, nRuns ));
        config.push_back(Trend( clsmean.c_str(), nameclsmean.c_str(), 0, condition, "", Start, End, nRuns ));
        config.push_back(Trend( noiseCh.c_str(), namenoiseCh.c_str(), 0, condition, "", Start, End, nRuns ));
      }else{
	stringstream out;
	out << itmap->second;
	
	string effmean = string(out.str())+"@EffDistro@mean";
	string nameeffmean = "EffDistro"+string(itmap->first)+".gif";
	
	config.push_back(Trend( effmean.c_str(), nameeffmean.c_str(), 0, condition, "", Start, End, nRuns ));
      }
    }
  }//end loop on all labels

  // Creation of trends
  for_each(config.begin(), config.end(), makeTrend);

  // Close the output file
  makeTrend.closeFile();
}

void RPCHDQMInspector( const string & dbName, const string & tagName, const string & password, const std::string & whiteListFile,
		       const int start, const int end )
{
  runRPCInspector(dbName, tagName, password, whiteListFile, start, end, 0);
}

void RPCHDQMInspector( const string & dbName, const string & tagName, const string & password, const std::string & whiteListFile,
		       const int nRuns )
{
  runRPCInspector(dbName, tagName, password, whiteListFile, 0, 0, nRuns);
}

int main (int argc, char* argv[]){
  if (argc != 6 && argc != 7) {
    cerr << "Usage: " << argv[0] << " [Database] [TagName] [Password] [WhiteListFile] [NRuns] " << endl;
    cerr << "Or:    " << argv[0] << " [Database] [TagName] [Password] [WhiteListFile] [FirstRun] [LastRun] " << endl;
    return 1;
  }

  if (argc == 6) {
    cout << "Creating trends for NRuns = " << argv[5] << " for tag: " << argv[2] << endl;
    RPCHDQMInspector( argv[1], argv[2], argv[3], argv[4], atoi(argv[5]) );
  } else if(argc == 7) {
    cout << "Creating trends for range:  " << argv[5] << " " << argv[6] << " for tag: " << argv[2] <<endl;
    RPCHDQMInspector( argv[1], argv[2], argv[3], argv[4], atoi(argv[5]), atoi(argv[6]) );
  }

  return 0;
}
