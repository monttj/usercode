import FWCore.ParameterSet.Config as cms


process = cms.Process("Zee")

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100



process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )


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
     name = cms.untracked.string('Zee'),
     annotation = cms.untracked.string('None'),
     preselectionEff = cms.untracked.double(1.0)
 )

process.Summary =  cms.PSet(
    selectionFlavours = cms.untracked.vstring("PF")
    )


process.TestAnalyzer = cms.PSet(
    genParticlesLabel = cms.InputTag('genParticles'),
    patElectronsLabel = cms.InputTag('selectedPatElectrons'),
    minElePt = cms.untracked.double(15.),
    maxEleEta = cms.untracked.double(2.4),
    electronSelector = cms.PSet(
       version = cms.int32(0),
       quality = cms.int32(0),
       PT = cms.double(15),
       E = cms.double(20),
       # cuts for isolation: deltaR, Et cut deposit, coeff in comb iso, Et cut on isodeposit)                              
       isoParForCharged = cms.vdouble(0.5, 0.1, 1.0, 1.0),
       isoParForNeutral = cms.vdouble(0.5, 0.1, 1.0, 1.0),
       isoParForPhotons = cms.vdouble(0.5, 0.1, 1.0, 1.0),
       # rectangular veto = (eta, phi)
       isoParForRectangularVeto = cms.vdouble(0.02,0.3),
       absoluteIso = cms.double(0.5),
       relativeIso = cms.double(0.1),
       # turn me to True to see the results of the jet selection:
       verbose = cms.untracked.bool( True )
    )

    #minMassEE = cms.double(70.),
    #deltaRMatching = cms.double(0.05),
    )



process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.printTree = cms.EDAnalyzer("ParticleListDrawer",
     src = cms.InputTag("prunedGenParticles"),
     maxEventsToPrint  = cms.untracked.int32(10)
)

process.p = cms.Path(process.printTree)



'''
       coneRadiusCharged = cms.double(0.4),
       coneRadiusNeutral = cms.double(0.4),
       coneRadiusPhotons = cms.double(0.4),
       minDepositEtCharged = cms.double(0.5),
       minDepositEtNeutral = cms.double(0.5),
       minDepositEtPhotons = cms.double(0.5),
       relativeWeightInCombinedIsoCharged = cms.double(1.0),
       relativeWeightInCombinedIsoNeutral = cms.double(1.0),
       relativeWeightInCombinedIsoPhotons = cms.double(1.0),
'''



