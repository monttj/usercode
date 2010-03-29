import FWCore.ParameterSet.Config as cms


process = cms.Process("Zmm")

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100



process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(2000) )


process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        #'rfio:/castor/cern.ch/user/t/tjkim/pfa/pat/Zmm/patLayer1_fromAOD_PF2PAT_full.root'
        'rfio:/castor/cern.ch/user/t/tjkim/pfa/pat/Zmm/patLayer1_fromAOD_PF2PAT_full_0.root'
    )
)

##In the metadata we pass the preselection efficiency and the
##sample name. The sample name will be addedto the name of the
##output ROOT file with the histograms
process.configurationMetadata = cms.untracked.PSet(
     version = cms.untracked.string('1.0'),
     name = cms.untracked.string('Zmm'),
     annotation = cms.untracked.string('None'),
     preselectionEff = cms.untracked.double(1.0)
 )

process.Summary =  cms.PSet(
    selectionFlavours = cms.untracked.vstring("PF")
    )


process.TagProveZmmAnalyzer = cms.PSet(
    genParticlesLabel = cms.InputTag('genParticles'),
    patMuonsLabel = cms.InputTag('selectedPatMuons'),
    minMuons = cms.untracked.uint32(2),
    minZmass = cms.untracked.double(60.0),
    maxZmass = cms.untracked.double(120.0),
    muonSelector = cms.PSet(
       version = cms.int32(0),
       quality = cms.int32(0),
       PT = cms.double(0),
       E = cms.double(0),
       # turn me to True to see the results of the jet selection:
       verbose = cms.untracked.bool( False )
    ),
     tagSelector = cms.PSet(
       version = cms.int32(0),
       quality = cms.int32(0),
       PT = cms.double(15),
       E = cms.double(0),
       # turn me to True to see the results of the jet selection:
       verbose = cms.untracked.bool( False )
    ),
     proveSelector = cms.PSet(
       version = cms.int32(0),
       quality = cms.int32(0),
       PT = cms.double(15),
       E = cms.double(0),
       # turn me to True to see the results of the jet selection:
       verbose = cms.untracked.bool( False )
    ),

    #minMassEE = cms.double(70.),
    #deltaRMatching = cms.double(0.05),
    )



process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.printTree = cms.EDAnalyzer("ParticleListDrawer",
     src = cms.InputTag("prunedGenParticles"),
     maxEventsToPrint  = cms.untracked.int32(10)
)

process.p = cms.Path(process.printTree)

