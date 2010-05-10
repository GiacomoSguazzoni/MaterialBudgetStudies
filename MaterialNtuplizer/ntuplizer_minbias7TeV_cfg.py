import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = "START3X_V26A::All"

process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("RecoParticleFlow.PFTracking.particleFlowDisplacedVertexCandidate_cff")
process.load("RecoParticleFlow.PFTracking.particleFlowDisplacedVertex_cff")

process.load("Tests.MaterialNtuplizer.filesMinBiasSTART3X_V25B")

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(5000))

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.conv = cms.EDAnalyzer('ConversionNtuplizer',
                              outfile = cms.string('ntuple_conversion_minbias7TeV.root'),
                              redovtx = cms.bool(True),
                              hitassoc = cms.bool(False),
                              minPhoPtForEffic = cms.double(0.3),#when hardcoded it was 2.5
                              maxPhoEtaForEffic = cms.double(2.5),
                              maxPhoZForEffic = cms.double(200.),
                              maxPhoRForEffic = cms.double(100.),
                              minPhoPtForPurity = cms.double(0.3),#when hardcoded it was 0.5
                              maxPhoEtaForPurity = cms.double(2.5),
                              maxPhoZForPurity = cms.double(200.),
                              maxPhoRForPurity = cms.double(100.),
                              simulation = cms.bool(True),
                              prints = cms.bool(False)
)

process.load("SimTracker.TrackAssociation.TrackAssociatorByHits_cfi")
process.convHit = process.conv.clone(outfile = cms.string('ntuple_conversion_minbias7TeV_hit.root'),hitassoc = cms.bool(True))

process.nucl = cms.EDAnalyzer('NuclIntNtuplizer',
                              outfile = cms.string('ntuple_nuclint_minbias7TeV.root'),
                              hitassoc = cms.bool(False),
                              simulation = cms.bool(True),
                              prints = cms.bool(False)
)

process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
from HLTrigger.HLTfilters.hltLevel1GTSeed_cfi import hltLevel1GTSeed
process.bit40 = hltLevel1GTSeed.clone(L1TechTriggerSeeding = cms.bool(True), L1SeedsLogicalExpression = cms.string('40 AND NOT (36 OR 37 OR 38 OR 39)'))

process.oneGoodVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof > 4 && abs(z) <= 15 && position.Rho <= 2"),
   filter = cms.bool(True)
)

process.noScraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False),
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.2)
)

process.disp = cms.Sequence(
    process.particleFlowDisplacedVertexCandidate +
    process.particleFlowDisplacedVertex
    )

process.default = cms.Sequence(process.siPixelRecHits*process.siStripMatchedRecHits*process.ckftracks_wodEdX*
                               process.trackerOnlyConversionSequence*process.disp*process.conv*process.convHit*process.nucl)

#####################################################################################################
####
####  Top level replaces for handling strange scenarios of early collisions
####

## TRACKING:
## Skip events with HV off
process.newSeedFromTriplets.ClusterCheckPSet.MaxNumberOfPixelClusters=2000
process.newSeedFromPairs.ClusterCheckPSet.MaxNumberOfCosmicClusters=10000
process.secTriplets.ClusterCheckPSet.MaxNumberOfPixelClusters=2000
process.fifthSeeds.ClusterCheckPSet.MaxNumberOfCosmicClusters = 10000
process.fourthPLSeeds.ClusterCheckPSet.MaxNumberOfCosmicClusters=10000
    ###### FIXES TRIPLETS FOR LARGE BS DISPLACEMENT ######
    ### prevent bias in pixel vertex
process.pixelVertices.useBeamConstraint = False

### pixelTracks
#---- new parameters ----
process.pixelTracks.RegionFactoryPSet.RegionPSet.nSigmaZ  = cms.double(4.06) # was originHalfLength = 15.9; translated assuming sigmaZ ~ 3.8

### 0th step of iterative tracking
#---- replaces ----
process.newSeedFromTriplets.RegionFactoryPSet.ComponentName = 'GlobalRegionProducerFromBeamSpot' # was GlobalRegionProducer
#---- new parameters ----
process.newSeedFromTriplets.RegionFactoryPSet.RegionPSet.nSigmaZ   = cms.double(4.06)  # was originHalfLength = 15.9; translated assuming sigmaZ ~ 3.8
process.newSeedFromTriplets.RegionFactoryPSet.RegionPSet.beamSpot = cms.InputTag("offlineBeamSpot")
    ### 2nd step of iterative tracking
#---- replaces ----
process.secTriplets.RegionFactoryPSet.ComponentName = 'GlobalRegionProducerFromBeamSpot' # was GlobalRegionProducer
#---- new parameters ----
process.secTriplets.RegionFactoryPSet.RegionPSet.nSigmaZ  = cms.double(4.47)  # was originHalfLength = 17.5; translated assuming sigmaZ ~ 3.8
process.secTriplets.RegionFactoryPSet.RegionPSet.beamSpot = cms.InputTag("offlineBeamSpot")
    ## Primary Vertex
process.offlinePrimaryVerticesWithBS.PVSelParameters.maxDistanceToBeam = 2
process.offlinePrimaryVerticesWithBS.TkFilterParameters.maxNormalizedChi2 = 20
process.offlinePrimaryVerticesWithBS.TkFilterParameters.minSiliconHits = 6
process.offlinePrimaryVerticesWithBS.TkFilterParameters.maxD0Significance = 100
process.offlinePrimaryVerticesWithBS.TkFilterParameters.minPixelHits = 1
process.offlinePrimaryVerticesWithBS.TkClusParameters.zSeparation = 1
process.offlinePrimaryVertices.PVSelParameters.maxDistanceToBeam = 2
process.offlinePrimaryVertices.TkFilterParameters.maxNormalizedChi2 = 20
process.offlinePrimaryVertices.TkFilterParameters.minSiliconHits = 6
process.offlinePrimaryVertices.TkFilterParameters.maxD0Significance = 100
process.offlinePrimaryVertices.TkFilterParameters.minPixelHits = 1
process.offlinePrimaryVertices.TkClusParameters.zSeparation = 1
    ## ECAL 
process.ecalRecHit.ChannelStatusToBeExcluded = [ 1, 2, 3, 4, 8, 9, 10, 11, 12, 13, 14, 78, 142 ]
    ##Preshower
process.ecalPreshowerRecHit.ESBaseline = 0
    ##Preshower algo for data is different than for MC
process.ecalPreshowerRecHit.ESRecoAlgo = cms.untracked.int32(1)
    ## HCAL temporary fixes
process.hfreco.firstSample  = 3
process.hfreco.samplesToAdd = 4

## EGAMMA
process.gsfElectrons.applyPreselection = cms.bool(False)
process.photons.minSCEtBarrel = 2.
process.photons.minSCEtEndcap =2.
process.photonCore.minSCEt = 2.
process.conversionTrackCandidates.minSCEt =1.
process.conversions.minSCEt =1.
process.trackerOnlyConversions.AllowTrackBC = cms.bool(False)
process.trackerOnlyConversions.AllowRightBC = cms.bool(False)
process.trackerOnlyConversions.MinApproach = cms.double(-.25)
process.trackerOnlyConversions.DeltaCotTheta = cms.double(.07)
process.trackerOnlyConversions.DeltaPhi = cms.double(.2)

###
###  end of top level replacements
###
###############################################################################################

process.p = cms.Path(process.bit40*process.noScraping*process.oneGoodVertexFilter*process.default)

