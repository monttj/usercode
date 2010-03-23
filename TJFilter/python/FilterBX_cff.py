import FWCore.ParameterSet.Config as cms

###### Luminosity blocks by run when tracker and pixel HV were on ######
FilterBX = cms.EDFilter("FilterBX",
    applyFilter = cms.untracked.bool(True),
    crossings = cms.untracked.vint32(51),
)

