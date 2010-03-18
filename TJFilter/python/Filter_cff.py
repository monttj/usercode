import FWCore.ParameterSet.Config as cms

collisionBunchCrossings = cms.EDFilter("TJFilter",
    crossings = cms.untracked.vint32(),
    coltype = cms.untracked.int32(1)
)

emptyBunchCrossings = cms.EDFilter("TJFilter",
    crossings = cms.untracked.vint32(),
    coltype = cms.untracked.int32(2)
)

parasiticBunchCrossings = cms.EDFilter("TJFilter",
    crossings = cms.untracked.vint32(1830,1831,1832,1833)
)

