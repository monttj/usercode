import FWCore.ParameterSet.Config as cms
from PFAnalyses.PFCandidate.Tools.inputFiles import restrictInput as restrictInput

process = cms.Process("ttbar")

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

# real data or MC ? just change this switch.
MC = False 


extName = 'Test'
if MC:
    ## Simulated and reco'ed with 342patch1
    #process.load("PFAnalyses.PFCandidate.Sources.MC.source_MinBias7TeV_cff")
    #process.load("PFAnalyses.PFCandidate.Sources.MC.source_MinBias900GeV_Feb9th_342_DisplayD6T_cff")
    #process.load("PFAnalyses.PFCandidate.Sources.MC.source_MinBias900GeV_Feb9th_342_DisplayDW_cff")
    #process.load("PFAnalyses.PFCandidate.Sources.MC.source_MinBias2360GeV_Feb9th_342_DisplayD6T_cff")
    #process.load("PFAnalyses.Z.MC.Minbias_cff")
    #process.load("PFAnalyses.Z.MC.Minbias_jets_cff")
    #process.load("PFAnalyses.Z.MC.Minbias_jets20_cff")
    extName = 'MC'
else:
    ## Re-reco with 336patch4, display.root produced with 341 + PF tags, with or wihtout cleaning
    #process.load("PFAnalyses.PFCandidate.Sources.RD.source_Run132440_cff")
    #process.load("PFAnalyses.PFCandidate.Sources.RD.source_BSCSkim_ReReco_Feb9th_342_DisplayReReco_900GeV_cff")
    #process.load("PFAnalyses.PFCandidate.Sources.RD.source_BSCSkim_ReReco_Feb9th_342_DisplayReRecoNoCleaning_900GeV_cff")
    #process.load("PFAnalyses.PFCandidate.Sources.RD.source_BSCSkim_ReReco_Feb9th_342_DisplayReReco_2360GeV_cff")
    #process.load("PFAnalyses.PFCandidate.Sources.RD.source_BSCSkim_ReReco_Feb9th_342_DisplayReRecoNoCleaning_2360GeV_cff")
    #process.load("PFAnalyses.Z.RD.Minbias_cff")
    #process.load("PFAnalyses.Z.RD.Minbias_nojet_cff")
    process.load("PFAnalyses.Z.RD.Minbias_jets_cff")
    extName = 'RD'

#process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring(
        #'file:pf2pat_tnp.root',
#        'file:/tmp/tjkim/PFA/Wmunu/pf2pat_tnp_1_1.root',
#        'file:/tmp/tjkim/PFA/Wmunu/pf2pat_tnp_2_1.root',
#        'file:/tmp/tjkim/PFA/Wmunu/pf2pat_tnp_3_1.root',
#        'file:/tmp/tjkim/PFA/Wmunu/pf2pat_tnp_4_1.root',
        #'rfio:/castor/cern.ch/user/t/tjkim/pf2pat/tnp/Spring10/Wmunu_v2/pf2pat_tnp_1_1.root',
        #'rfio:/castor/cern.ch/user/t/tjkim/pf2pat/tnp/Spring10/Wmunu_v2/pf2pat_tnp_2_1.root',
        #'rfio:/castor/cern.ch/user/t/tjkim/pf2pat/tnp/Spring10/Wmunu_v2/pf2pat_tnp_3_1.root',
        #'rfio:/castor/cern.ch/user/t/tjkim/pf2pat/tnp/Spring10/Wmunu_v2/pf2pat_tnp_4_1.root',
        #'rfio:/castor/cern.ch/user/t/tjkim/pf2pat/tnp/Spring10/Wmunu/pf2pat_tnp_3_1.root',
        #'rfio:/castor/cern.ch/user/t/tjkim/pf2pat/tnp/Spring10/Wmunu/pf2pat_tnp_4_1.root',
        #'rfio:/castor/cern.ch/user/t/tjkim/pf2pat/tnp/Spring10/Minbias_v2/pf2pat_tnp_1_1.root',
        #'rfio:/castor/cern.ch/user/t/tjkim/pf2pat/tnp/Spring10/Minbias_v2/pf2pat_tnp_2_1.root',
#    )
#)


# to debug your code, just uncomment the following line
# to restrict the input to the first file -> fast start up of the analysis
#process.source.fileNames = restrictInput( process.source.fileNames, 1)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

print process.source.fileNames

##In the metadata we pass the preselection efficiency and the
##sample name. The sample name will be addedto the name of the
##output ROOT file with the histograms
process.configurationMetadata = cms.untracked.PSet(
     version = cms.untracked.string('1.0'),
     name = cms.untracked.string( extName ),
     annotation = cms.untracked.string('None'),
     preselectionEff = cms.untracked.double(1.0)
 )


process.PFCandidateAnalyzer =  cms.PSet(
        pfCandidateLabel = cms.InputTag("particleFlow"),
        pfRecTrackLabel = cms.InputTag("trackerDrivenElectronSeeds"),
        muonLabel = cms.InputTag("selectedPatMuons"),
        useMuonDirForRandom = cms.untracked.bool( False ),
        tkRefLabel = cms.InputTag("generalTracks"),
        cleanedHFShortLabel = cms.InputTag("particleFlowRecHitHCAL","Cleaned"),
        cleanedHCALLabel = cms.InputTag("particleFlowClusterHCAL","Cleaned"),
        cleanedHFEMLabel = cms.InputTag("particleFlowClusterHFEM","Cleaned"),
        cleanedHFHADLabel = cms.InputTag("particleFlowClusterHFHAD","Cleaned"),
        cleanedECALLabel = cms.InputTag("particleFlowClusterECAL","Cleaned"),
        fillRandomCones = cms.untracked.bool( True ),
        numOfRandomCones = cms.untracked.uint32(40),
        maxEtaRandomCones = cms.untracked.double(2.1),
        fillCleanedChannels = cms.untracked.bool( False ),
        fillChargedHadrons = cms.untracked.bool( False ),
        fillChargedHadronsIsoDep = cms.untracked.bool( False ),
        fillPhotons = cms.untracked.bool( False ),
        fillPhotonsIsoDep = cms.untracked.bool( False ),
        fillMuons = cms.untracked.bool( False ),
        fillMuonsIsoDep = cms.untracked.bool( False ),
        fillElectrons = cms.untracked.bool( False ),
        fillElectronsIsoDep = cms.untracked.bool( False ),
        maxDeltaRForIsoDep = cms.untracked.double(1), 
        usePhotonRawEnergy = cms.bool(False),
        ptMinChargedHadrons = cms.untracked.double(-1.),
        nTracksInBlockMax  = cms.untracked.int32(1000000)
    )


process.PFObjectsAnalyzer =  cms.PSet(
        pfJetLabel = cms.InputTag("ak5PFJets"),
        pfMetLabel = cms.InputTag("pfMet"),
        caloMetLabel = cms.InputTag("met")
    )

process.Summary =  cms.PSet(
    selectionFlavours = cms.untracked.vstring("PF")
    )
#############################################
#Here we have an ordinary CMSSW plugin, just in case we wany to run it on the same events
# as the FWLite 
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.printTree = cms.EDAnalyzer("ParticleListDrawer",
     src = cms.InputTag("prunedGenParticles"),
     maxEventsToPrint  = cms.untracked.int32(10)
)

process.p = cms.Path(process.printTree)




