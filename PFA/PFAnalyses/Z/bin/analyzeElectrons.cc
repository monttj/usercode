#include <iostream>
#include <string>

#include "TFile.h"
#include "TStopwatch.h"

#include "FWCore/FWLite/interface/AutoLibraryLoader.h"

#include "PFAnalyses/CommonTools/interface/FWLiteTreeAnalyzer.h"
#include "PFAnalyses/Z/interface/TestAnalyzer.h"

int main(int argc, char ** argv){


  std::string cfgFileName = "ps.cfg";

  if(argc<2){
    std::cout<<"Usage: readEventsDemo cfg.py"<<std::endl;
    return 1;
  }
  else cfgFileName = argv[1];

  std::cout<<"Start"<<std::endl;
  TStopwatch timer;
  timer.Start();
  //----------------------------------------------------------
  AutoLibraryLoader::enable();

  std::vector<FWLiteAnalyzer*> myAnalyzers;

  myAnalyzers.push_back(new TestAnalyzer("TestAnalyzer")); 
  
  FWLiteTreeAnalyzer *tree = new FWLiteTreeAnalyzer("TreeAnalyzer",cfgFileName);
  tree->init(myAnalyzers);
  int nEventsAnalyzed = tree->loop();
  tree->finalize();
  //----------------------------------------------------------
  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  printf("Analyzed events: %d \n",nEventsAnalyzed);
  printf("RealTime=%f seconds, CpuTime=%f seconds\n",rtime,ctime);
  printf("%4.2f events / RealTime second .\n", nEventsAnalyzed/rtime);
  printf("%4.2f events / CpuTime second .\n", nEventsAnalyzed/ctime);

  for(unsigned int i=0;i<myAnalyzers.size();++i) delete myAnalyzers[i];
  delete tree;

  std::cout<<"Done"<<std::endl;
  return 0;
}
