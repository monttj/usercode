import FWCore.ParameterSet.Config as cms

process = cms.Process("PWRITE")

##################
# message logger #
##################

process.MessageLogger = cms.Service(
    "MessageLogger",
    destinations = cms.untracked.vstring('readFromFile_RUNNUMBER'),
    readFromFile_RUNNUMBER = cms.untracked.PSet(threshold = cms.untracked.string('DEBUG')),
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
        authenticationPath = cms.untracked.string('AUTHENTICATIONPATH')
    ),
    timetype = cms.untracked.string('runnumber'),
    connect = cms.string('DATABASE'),
    toPut = cms.VPSet(cms.PSet(
        record = cms.string("HDQMSummary"),
        tag = cms.string("TAGNAME")
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
        since = cms.untracked.uint32(RUNNUMBER),
        debug = cms.untracked.bool(False)
    )
)

#####################
# HistoryDQMService #
#####################

process.RPCHistoryDQMService = cms.Service(
    "RPCHistoryDQMService",
    RunNb = cms.uint32(RUNNUMBER),
    accessDQMFile = cms.bool(True),
    FILE_NAME = cms.untracked.string("FILENAME"),
    ME_DIR = cms.untracked.string("Run RUNNUMBER/RPC/"),
    histoList = cms.VPSet(
    
    # quantities are 'stat', 'landau', 'gauss'
    # where 
    #'stat' includes entries, mean, rms
    #'landau' includes
    #'gauss' includes gaussMean, gaussSigma

    cms.PSet( keyName = cms.untracked.string("BxDistribution_Disk_-3"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("BxDistribution_Disk_-2"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("BxDistribution_Disk_-1"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("BxDistribution_Disk_1"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("BxDistribution_Disk_2"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("BxDistribution_Disk_3"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("BxDistribution_Wheel_-2"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("BxDistribution_Wheel_-1"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("BxDistribution_Wheel_0"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("BxDistribution_Wheel_1"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("BxDistribution_Wheel_2"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    
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

    cms.PSet( keyName = cms.untracked.string("NumberOfDigi_Mean_Distribution_Disk_-3"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("NumberOfDigi_Mean_Distribution_Disk_-2"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("NumberOfDigi_Mean_Distribution_Disk_-1"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("NumberOfDigi_Mean_Distribution_Disk_1"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("NumberOfDigi_Mean_Distribution_Disk_2"), quantitiesToExtract  = cms.untracked.vstring("stat") ), 
    cms.PSet( keyName = cms.untracked.string("NumberOfDigi_Mean_Distribution_Disk_3"), quantitiesToExtract  = cms.untracked.vstring("stat") ), 
    cms.PSet( keyName = cms.untracked.string("NumberOfDigi_Mean_Distribution_Wheel_-2"), quantitiesToExtract  = cms.untracked.vstring("stat") ), 
    cms.PSet( keyName = cms.untracked.string("NumberOfDigi_Mean_Distribution_Wheel_-1"), quantitiesToExtract  = cms.untracked.vstring("stat") ), 
    cms.PSet( keyName = cms.untracked.string("NumberOfDigi_Mean_Distribution_Wheel_0"), quantitiesToExtract  = cms.untracked.vstring("stat") ), 
    cms.PSet( keyName = cms.untracked.string("NumberOfDigi_Mean_Distribution_Wheel_1"), quantitiesToExtract  = cms.untracked.vstring("stat") ), 
    cms.PSet( keyName = cms.untracked.string("NumberOfDigi_Mean_Distribution_Wheel_2"), quantitiesToExtract  = cms.untracked.vstring("stat") ), 

    cms.PSet( keyName = cms.untracked.string("RPCChamberQuality_Good_Disk_-3"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("RPCChamberQuality_Good_Disk_-2"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("RPCChamberQuality_Good_Disk_-1"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("RPCChamberQuality_Good_Disk_1"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("RPCChamberQuality_Good_Disk_2"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("RPCChamberQuality_Good_Disk_3"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("RPCChamberQuality_Good_Wheel_-2"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("RPCChamberQuality_Good_Wheel_-1"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("RPCChamberQuality_Good_Wheel_0"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("RPCChamberQuality_Good_Wheel_1"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("RPCChamberQuality_Good_Wheel_2"), quantitiesToExtract  = cms.untracked.vstring("stat") ),

    cms.PSet( keyName = cms.untracked.string("EffDistro"), quantitiesToExtract  = cms.untracked.vstring("stat") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Disk_-3near"), quantitiesToExtract  = cms.untracked.vstring("statnear") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Disk_-2near"), quantitiesToExtract  = cms.untracked.vstring("statnear") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Disk_-1near"), quantitiesToExtract  = cms.untracked.vstring("statnear") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Disk_1near"), quantitiesToExtract  = cms.untracked.vstring("statnear") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Disk_2near"), quantitiesToExtract  = cms.untracked.vstring("statnear") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Disk_3near"), quantitiesToExtract  = cms.untracked.vstring("statnear") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Wheel_-2near"), quantitiesToExtract  = cms.untracked.vstring("statnear") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Wheel_-1near"), quantitiesToExtract  = cms.untracked.vstring("statnear") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Wheel_0near"), quantitiesToExtract  = cms.untracked.vstring("statnear") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Wheel_1near"), quantitiesToExtract  = cms.untracked.vstring("statnear") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Wheel_2near"), quantitiesToExtract  = cms.untracked.vstring("statnear") ),

    cms.PSet( keyName = cms.untracked.string("EffDistro_Disk_-3far"), quantitiesToExtract  = cms.untracked.vstring("statfar") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Disk_-2far"), quantitiesToExtract  = cms.untracked.vstring("statfar") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Disk_-1far"), quantitiesToExtract  = cms.untracked.vstring("statfar") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Disk_1far"), quantitiesToExtract  = cms.untracked.vstring("statfar") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Disk_2far"), quantitiesToExtract  = cms.untracked.vstring("statfar") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Disk_3far"), quantitiesToExtract  = cms.untracked.vstring("statfar") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Wheel_-2far"), quantitiesToExtract  = cms.untracked.vstring("statfar") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Wheel_-1far"), quantitiesToExtract  = cms.untracked.vstring("statfar") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Wheel_0far"), quantitiesToExtract  = cms.untracked.vstring("statfar") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Wheel_1far"), quantitiesToExtract  = cms.untracked.vstring("statfar") ),
    cms.PSet( keyName = cms.untracked.string("EffDistro_Wheel_2far"), quantitiesToExtract  = cms.untracked.vstring("statfar") ),

    cms.PSet( keyName = cms.untracked.string("FEDFatal"), quantitiesToExtract  = cms.untracked.vstring("stat") ),

    )
)


# Schedule

process.p = cms.Path(process.siStripDQMHistoryPopCon)




