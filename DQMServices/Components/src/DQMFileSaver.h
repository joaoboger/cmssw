#ifndef DQMFileSaver_H
#define DQMFileSaver_H

/*
 * \file DQMFileSaver.h
 *
 * $Date: 2007/11/15 23:59:41 $
 * $Revision: 1.2 $
 * \author A. Meyer, DESY
 *
*/

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include <FWCore/Framework/interface/EDAnalyzer.h>
#include <FWCore/Framework/interface/ESHandle.h>
#include <FWCore/Framework/interface/Event.h>
#include "FWCore/Framework/interface/Run.h"
#include <FWCore/Framework/interface/MakerMacros.h>
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DQMServices/Core/interface/DaqMonitorBEInterface.h"
#include "DQMServices/Core/interface/MonitorElementBaseT.h"
//#include "DQMServices/Daemon/interface/MonitorDaemon.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sys/time.h>

using namespace edm;

class DQMFileSaver: public EDAnalyzer{

public:

  /// Constructors  
  DQMFileSaver(const ParameterSet& ps);
  DQMFileSaver();
  
  /// Destructor
  virtual ~DQMFileSaver();

protected:

  /// to be used by derived class

  /// BeginJob
  void beginJob(const EventSetup& c);

  /// Endjob
  void endJob(void);
  
  /// BeginRun
  void beginRun(const Run& run, const EventSetup& c);

  /// EndRun
  void endRun(const Run& run, const EventSetup& c);

  
  /// Begin LumiBlock
  void beginLuminosityBlock(const LuminosityBlock& lumiSeg, 
                            const EventSetup& c) ;

  /// End LumiBlock
  void endLuminosityBlock(const LuminosityBlock& lumiSeg, 
                          const EventSetup& c);

  // Reset
  void reset(void);

  /// Analyze
  void analyze(const Event& e, const EventSetup& c) ;

  /// initialize parms
  void initialize();
  
private:
  // environment variables
  DaqMonitorBEInterface* dbe_;  
  ParameterSet parameters_;

  int irun_,ilumisec_,ievent_,itime_;
  
  /// counters and flags
  int counterEvt_;
  int counterLS_;

  int prescaleEvt_;
  int prescaleLS_;
  int prescaleTime_;

  struct{
    timeval startTV,updateTV;
    double startTime;
    double elapsedTime; 
    double updateTime;
  } psTime_;    

  std::string fileName_;
  std::string dirName_;
  bool isPlayback_;
  bool saveAtRunEnd_;
  bool saveAtJobEnd_;

};

#endif
