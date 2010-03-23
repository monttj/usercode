import FWCore.ParameterSet.Config as cms

###### Luminosity blocks by run when tracker and pixel HV were on ######
FilterBeamHalo = cms.EDFilter("FilterL1Algo",
    applyFilter = cms.untracked.bool(True),
    algobits = cms.untracked.vint32(54),
)

FilterMuOpen = cms.EDFilter("FilterL1Algo",
    applyFilter = cms.untracked.bool(True),
    algobits = cms.untracked.vint32(55),
)

