import FWCore.ParameterSet.Config as cms

########

process = cms.Process("ConvAndNuclInt")


# Message logger and Debug
process.load("FWCore.MessageService.MessageLogger_cfi")
#Debug = True 
Debug = False
if Debug:    
      process.MessageLogger.cerr.threshold = cms.untracked.string("INFO")
      process.MessageLogger.categories+=cms.vstring("BeamConditions",
                                                    "PhotonConversionTrajectorySeedProducerFromSingleLegAlgo",
                                                    "PhotonConversionTrajectorySeedProducerFromSingleLeg",
                                                    "debugTrajSeedFromSingleLeg"
                                                    )
      process.MessageLogger.cerr.FwkReport.reportEvery = 1
else:
      process.MessageLogger.cerr.FwkReport.reportEvery = 100
      
      
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
      
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)


# Load standard sequences
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.load("SimGeneral.MixingModule.mixNoPU_cfi"                                ) 
#process.load("Configuration.StandardSequences.RawToDigi_cff"                      )
#process.load("Configuration.EventContent.EventContent_cff"                        )
#process.load("RecoVertex.BeamSpotProducer.BeamSpot_cff"                           )
process.load("RecoTracker.TrackProducer.TrackRefitters_cff")

# Global tag
process.GlobalTag.globaltag = "GR_R_44_V12::All"


# HLT trigger selection
process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltfilter = process.hltHighLevel.clone(
#      HLTPaths = ["*"],
      HLTPaths = ["HLT_ZeroBias_*"],
      andOr = True,  # False = and, True = or
      throw = False)


# Top level replacement
##process.reconstruction_step = cms.Sequence(process.reconstruction)
##from Configuration.GlobalRuns.reco_TLR_42X import customisePPData
##customisePPData(process)
#------------------------------------------------------



#------------------------------------------------------
# MONITORING PART
#------------------------------------------------------                                                                                                                                                                                    
# Vertex monitoring. the results are in another root file                                                                                                                                                                                
#process.TFileService = cms.Service('TFileService',
#                                   fileName = cms.string('vertices.root')
#                                   )

# Single leg part
# not working!!!

#process.load('RecoEgamma.EgammaPhotonProducers.conversionTrackSequence_cff')
#process.localReco = cms.Sequence(process.siPixelRecHits*process.siStripMatchedRecHits)
#process.p = cms.Path(
#      process.offlineBeamSpot
#      *process.localReco
#      *process.ckftracks  
#      *process.ecalClusters
#### process.egammaGlobalReco = cms.Sequence(process.electronGsfTracking+process.conversionTrackSequence+process.allConversionSequence)
#      *process.egammaGlobalReco
#      )


# Photon Conversions Ntuplizer
process.load('Tests.MaterialNtuplizer.ConversionNtuplizer_cfi')
process.convNtupl = cms.Path(process.hltfilter*process.newConv)


# Nuclear Interactions Ntuplizer
from RecoParticleFlow.PFTracking.particleFlowDisplacedVertexCandidate_cff import *
from RecoParticleFlow.PFTracking.particleFlowDisplacedVertex_cff import *
particleFlowDisplacedVertex.primaryVertexCut = cms.double(2.0)
particleFlowDisplacedVertexCandidate.primaryVertexCut = cms.double(1.8)
disp = cms.Sequence(
    particleFlowDisplacedVertexCandidate +
    particleFlowDisplacedVertex
)
process.load('Tests.MaterialNtuplizer.NuclIntNtuplizer_cfi')
process.nuclNtupl = cms.Path(process.hltfilter*disp*process.nucl)


# I/O
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
#readFiles.extend( ['dummy.root']);
readFiles.extend( [
#      'file:/nfs/data36/cms/dinardo/MaterialStudies/myAOD_E033A79D-4D21-E111-B453-002618943970.root',
#      'file:/nfs/data36/cms/dinardo/MaterialStudies/aod_182C7A8D-C411-E111-AB23-0026189438DD.root'
      'file:/nfs/data36/cms/dinardo/MaterialStudies/reco_9288DF20-CEFC-E011-8962-003048678B8E.root'
] );
## secFiles.extend( [
##                ] )
process.source = source
#----------------------------------
