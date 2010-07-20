import FWCore.ParameterSet.Config as cms

process = cms.Process("PWRITE")

##################
# message logger #
##################

process.MessageLogger = cms.Service(
    "MessageLogger",
    destinations = cms.untracked.vstring('readFromFile_140180'),
    readFromFile_140180 = cms.untracked.PSet(threshold = cms.untracked.string('DEBUG')),
    debugModules = cms.untracked.vstring('*')
)

#################
# maxEvents ... #
#################

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)

process.source = cms.Source(
    "EmptySource",
    timetype = cms.string("runnumber"),
    firstRun = cms.untracked.uint32(1),
    lastRun  = cms.untracked.uint32(1),
    interval = cms.uint32(1)
)

################
# DQM services #
################

process.load("DQMServices.Core.DQM_cfg")

#################
# DB parameters #
#################

process.PoolDBOutputService = cms.Service(
    "PoolDBOutputService",
    BlobStreamerName = cms.untracked.string('TBufferBlobStreamingService'),
    outOfOrder = cms.untracked.bool(True),
    DBParameters = cms.PSet(
        messageLevel = cms.untracked.int32(2),
        authenticationPath = cms.untracked.string('/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/HDQM/Cron/Scripts/Authentication')
    ),
    timetype = cms.untracked.string('runnumber'),
    connect = cms.string('sqlite_file:dbfile.db'),
    toPut = cms.VPSet(cms.PSet(
        record = cms.string("HDQMSummary"),
        tag = cms.string("HDQM_RPC_V1")
    )),
    logconnect = cms.untracked.string("sqlite_file:log.db") 
)

######################
# POPCON Application #
######################
process.siStripDQMHistoryPopCon = cms.EDAnalyzer(
    "RPCDQMHistoryPopCon",
    record = cms.string("HDQMSummary"),
    loggingOn = cms.untracked.bool(True),
    SinceAppendMode = cms.bool(True),
    Source = cms.PSet(
        since = cms.untracked.uint32(140180),
        debug = cms.untracked.bool(False)
    )
)

#####################
# HistoryDQMService #
#####################

process.RPCHistoryDQMService = cms.Service(
    "RPCHistoryDQMService",
    RunNb = cms.uint32(140180),
    accessDQMFile = cms.bool(True),
    FILE_NAME = cms.untracked.string(
          "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/data/OfflineData/Run2010/MinimumBias/0001401xx/DQM_V0001_R000140180__MinimumBias__Run2010A-PromptReco-v4__RECO.root"
    ),
    ME_DIR = cms.untracked.string("Run 140180/RPC/"),
    histoList = cms.VPSet(
    
    # quantities are 'stat', 'landau', 'gauss'
    # where 
    #'stat' includes entries, mean, rms
    #'landau' includes
    #'gauss' includes gaussMean, gaussSigma

    cms.PSet( keyName = cms.untracked.string("ClusterSize_for_EndcapNegative"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("ClusterSize_for_EndcapPositive"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("ClusterSize_Disk_-3"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("ClusterSize_Disk_-2"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("ClusterSize_Disk_-1"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("ClusterSize_Disk_1"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("ClusterSize_Disk_2"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("ClusterSize_Disk_3"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("ClusterSize_Wheel_-2"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("ClusterSize_Wheel_-1"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("ClusterSize_Wheel_0"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("ClusterSize_Wheel_1"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("ClusterSize_Wheel_2"), quantitiesToExtract  = cms.untracked.vstring("stat") ),

    #cms.PSet( keyName = cms.untracked.string("BxDistribution_"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    #cms.PSet( keyName = cms.untracked.string("ClusterSize_"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    #cms.PSet( keyName = cms.untracked.string("EffDistro"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    #cms.PSet( keyName = cms.untracked.string("NumberOfDigi_Mean_Distribution_"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    #cms.PSet( keyName = cms.untracked.string("RPCChamberQuality_Distribution_"), quantitiesToExtract  = cms.untracked.vstring("user") ),
    #cms.PSet( keyName = cms.untracked.string("FEDFatal"), quantitiesToExtract  = cms.untracked.vstring("stat") )

    )
)


# Schedule

process.p = cms.Path(process.siStripDQMHistoryPopCon)



