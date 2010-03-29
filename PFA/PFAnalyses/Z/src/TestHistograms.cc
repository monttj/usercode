#include <iostream>

#include "PFAnalyses/Z/interface/TestHistograms.h"



TestHistograms::TestHistograms(std::string fileName, int opt){

  AnalysisHistograms::init(fileName);

}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
TestHistograms::TestHistograms(const TFileDirectory *myDir){

  AnalysisHistograms::init(myDir);

}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
TestHistograms::~TestHistograms(){ 

  std::cout<<"TestHistograms::~TestHistograms()"<<std::endl;

}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
void TestHistograms::defineHistograms(){

  using namespace std;

 if(!histosInitialized_){

   add1DHistogram("hElectronEt","PF electrons E_{T};E_{T} [GeV];Events",100,0,100,file_);
   add1DHistogram("hMuonPt","PF muons P_{T};P_{T} [GeV];Muons",100,0,100,file_);
   add1DHistogram("hMuonEta","PF muons Eta;Eta [Radian];Muons",60,-3,3,file_);

   histosInitialized_ = true;
 }
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
