
#ifndef TestHistograms_h
#define TestHistograms_h

// Base class for histogram managing.
//
// Original Author:  Artur Kalinowski
//         Created:  Wed Jul 22 12:56:54 CEST 2009
// $Id: TestHistograms.h,v 1.1 2010/03/19 11:00:54 cbern Exp $
//
//
#include "PFAnalyses/CommonTools/interface/AnalysisHistograms.h"

class TestHistograms: public AnalysisHistograms {
 public:

  TestHistograms(std::string fileName="TestHistos.root", int opt=0);

  TestHistograms(const TFileDirectory *myDir);

  virtual ~TestHistograms();

  void fillHistograms(float et);

 private:

  virtual void defineHistograms();


};

#endif
