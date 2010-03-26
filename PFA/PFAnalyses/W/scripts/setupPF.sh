cat > pack << END 
V11-02-06      RecoParticleFlow/Configuration  
END
addpkg -f pack
scram b -j 4
cvs co -r  Colin_March26 -d AnalysisDataFormats/PFAnalyses UserCode/PFAnalyses/AnalysisDataFormats/PFAnalyses      
cvs co -r  Colin_March26 -d   PFAnalyses/CommonTools   UserCode/PFAnalyses/CommonTools   
cvs co -r  Colin_March26 -d   PFAnalyses/RootTools  UserCode/PFAnalyses/RootTools                                                  
scram b -j 4
addpkg PhysicsTools/PFCandProducer
addpkg PhysicsTools/PatAlgos
scram b -j 4
cvs co -r Simone_March26 -d PFAnalyses/W UserCode/PFAnalyses/W
scram b -j 4

