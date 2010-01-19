cat > pack << END 
V03-03-04      Validation/RecoParticleFlow 
V11-02-04      RecoParticleFlow/Configuration  
V11-02-02      RecoParticleFlow/PFClusterTools
V11-02-05      RecoParticleFlow/PFProducer
V11-04-07      RecoParticleFlow/PFRootEvent
V11-04-00      RecoParticleFlow/PFTracking
V12-03-00      DataFormats/ParticleFlowReco
END
addpkg -f pack
checkdeps -a
scram b -j 4

cvs co -r V00-00-02 -d AnalysisDataFormats/PFAnalyses UserCode/PFAnalyses/AnalysisDataFormats/PFAnalyses      
cvs co -r v31X_021009    AnalysisDataFormats/TauAnalysis                  
cvs co -r  Patrick_Dec24 -d   PFAnalyses/CommonTools   UserCode/PFAnalyses/CommonTools   
cvs co  -r Patrick_Dec24 -d   PFAnalyses/RootTools  UserCode/PFAnalyses/RootTools                                                  
cvs co -r v31X_021009    TauAnalysis/CandidateTools                       
cvs co -r v31X_021009    TauAnalysis/GenSimTools 

cvs co  -r Colin_Cleaning_Jan19 -d PFAnalyses/PFCandidate  UserCode/PFAnalyses/PFCandidate  
addpkg DPGAnalysis/Skims
cvs co -d TKDPG/BXSelect UserCode/lowette/TKDPG/BXSelect
scram b -j 4

rm -rf UserCode/Tjkim
