import FWCore.ParameterSet.Config as cms

from FWCore.MessageService.MessageLogger_cfi import *

from Configuration.StandardSequences.MagneticField_cff import *
from Configuration.StandardSequences.Services_cff import *
from Configuration.StandardSequences.Geometry_cff import *
from TrackingTools.TransientTrack.TransientTrackBuilder_cfi import *
from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *

from Configuration.StandardSequences.Reconstruction_cff import *
from RecoParticleFlow.PFTracking.particleFlowDisplacedVertexCandidate_cff import *
from RecoParticleFlow.PFTracking.particleFlowDisplacedVertex_cff import *

from SimTracker.TrackAssociation.TrackAssociatorByHits_cfi import *
TrackAssociatorByHits.SimToRecoDenominator = 'reco'
TrackAssociatorByHits.Quality_SimToReco = 0.5
TrackAssociatorByHits.Purity_SimToReco = 0.5
TrackAssociatorByHits.Cut_RecoToSim = 0.5

from Tests.MaterialNtuplizer.ConversionNtuplizer_cfi import conv
from Tests.MaterialNtuplizer.NuclIntNtuplizer_cfi import nucl
convHit = conv.clone(hitassoc = cms.bool(True))

from L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff import *
from HLTrigger.HLTfilters.hltLevel1GTSeed_cfi import hltLevel1GTSeed
bit40 = hltLevel1GTSeed.clone(L1TechTriggerSeeding = cms.bool(True), L1SeedsLogicalExpression = cms.string('40 AND NOT (36 OR 37 OR 38 OR 39)'))

oneGoodVertexFilter = cms.EDFilter("VertexSelector",
                                   src = cms.InputTag("offlinePrimaryVertices"),
                                   cut = cms.string("!isFake && ndof > 4 && abs(z) <= 15 && position.Rho <= 2"),
                                   filter = cms.bool(True)
)

noScraping = cms.EDFilter("FilterOutScraping",
                          applyfilter = cms.untracked.bool(True),
                          debugOn = cms.untracked.bool(False),
                          numtrack = cms.untracked.uint32(10),
                          thresh = cms.untracked.double(0.2)
)

disp = cms.Sequence(
    particleFlowDisplacedVertexCandidate +
    particleFlowDisplacedVertex
)

default = cms.Sequence(siPixelRecHits*siStripMatchedRecHits*ckftracks_wodEdX*
                       trackerOnlyConversionSequence*disp*conv*convHit*nucl)

#####################################################################################################
####
####  Top level replaces for handling strange scenarios of early collisions
####

## TRACKING:
## Skip events with HV off
newSeedFromTriplets.ClusterCheckPSet.MaxNumberOfPixelClusters=2000
newSeedFromPairs.ClusterCheckPSet.MaxNumberOfCosmicClusters=10000
secTriplets.ClusterCheckPSet.MaxNumberOfPixelClusters=2000
fifthSeeds.ClusterCheckPSet.MaxNumberOfCosmicClusters = 10000
fourthPLSeeds.ClusterCheckPSet.MaxNumberOfCosmicClusters=10000
thPLSeeds.ClusterCheckPSet.MaxNumberOfCosmicClusters = 10000
thPLSeeds.ClusterCheckPSet.MaxNumberOfPixelClusters = 2000

###### FIXES TRIPLETS FOR LARGE BS DISPLACEMENT ######

### prevent bias in pixel vertex
pixelVertices.useBeamConstraint = False

### pixelTracks
#---- new parameters ----
pixelTracks.RegionFactoryPSet.RegionPSet.nSigmaZ  = cms.double(4.06) # was originHalfLength = 15.9; translated assuming sigmaZ ~ 3.8

### 0th step of iterative tracking
#---- replaces ----
newSeedFromTriplets.RegionFactoryPSet.ComponentName = 'GlobalRegionProducerFromBeamSpot' # was GlobalRegionProducer
#---- new parameters ----
newSeedFromTriplets.RegionFactoryPSet.RegionPSet.nSigmaZ   = cms.double(4.06)  # was originHalfLength = 15.9; translated assuming sigmaZ ~ 3.8
newSeedFromTriplets.RegionFactoryPSet.RegionPSet.beamSpot = cms.InputTag("offlineBeamSpot")

### 2nd step of iterative tracking
#---- replaces ----
secTriplets.RegionFactoryPSet.ComponentName = 'GlobalRegionProducerFromBeamSpot' # was GlobalRegionProducer
#---- new parameters ----
secTriplets.RegionFactoryPSet.RegionPSet.nSigmaZ  = cms.double(4.47)  # was originHalfLength = 17.5; translated assuming sigmaZ ~ 3.8
secTriplets.RegionFactoryPSet.RegionPSet.beamSpot = cms.InputTag("offlineBeamSpot")

## Primary Vertex
offlinePrimaryVerticesWithBS.PVSelParameters.maxDistanceToBeam = 2
offlinePrimaryVerticesWithBS.TkFilterParameters.maxNormalizedChi2 = 20
offlinePrimaryVerticesWithBS.TkFilterParameters.minSiliconHits = 6
offlinePrimaryVerticesWithBS.TkFilterParameters.maxD0Significance = 100
offlinePrimaryVerticesWithBS.TkFilterParameters.minPixelHits = 1
offlinePrimaryVerticesWithBS.TkClusParameters.zSeparation = 1
offlinePrimaryVertices.PVSelParameters.maxDistanceToBeam = 2
offlinePrimaryVertices.TkFilterParameters.maxNormalizedChi2 = 20
offlinePrimaryVertices.TkFilterParameters.minSiliconHits = 6
offlinePrimaryVertices.TkFilterParameters.maxD0Significance = 100
offlinePrimaryVertices.TkFilterParameters.minPixelHits = 1
offlinePrimaryVertices.TkClusParameters.zSeparation = 1

## ECAL 
ecalRecHit.ChannelStatusToBeExcluded = [ 1, 2, 3, 4, 8, 9, 10, 11, 12, 13, 14, 78, 142 ]

##Preshower
ecalPreshowerRecHit.ESBaseline = 0

##Preshower algo for data is different than for MC
ecalPreshowerRecHit.ESRecoAlgo = cms.untracked.int32(1)

## HCAL temporary fixes
hfreco.firstSample  = 3
hfreco.samplesToAdd = 4

## EGAMMA
photons.minSCEtBarrel = 5.
photons.minSCEtEndcap =5.
photonCore.minSCEt = 5.
conversionTrackCandidates.minSCEt =5.
conversions.minSCEt =5.
trackerOnlyConversions.AllowTrackBC = False
trackerOnlyConversions.AllowRightBC = False
trackerOnlyConversions.rCut = 2.
trackerOnlyConversions.vtxChi2 = 0.0005

###
###  end of top level replacements
###
###############################################################################################
