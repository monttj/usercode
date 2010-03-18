import FWCore.ParameterSet.Config as cms

###### Luminosity blocks by run when tracker and pixel HV were on ######
FilterRuns = cms.EDFilter("FilterRun",
    applyRunFilter = cms.untracked.bool(True),
    #runs = cms.untracked.vint32(130434)
    runs = cms.untracked.vint32(130445)
)

