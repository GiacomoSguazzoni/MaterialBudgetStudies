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
#convHit = conv.clone(hitassoc = cms.bool(True))

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

#default = cms.Sequence(siPixelRecHits*siStripMatchedRecHits*ckftracks_wodEdX*
#                       trackerOnlyConversionSequence*disp*conv#*convHit
#                       *nucl
#		       )
#
# No more trackerOnlyConversionSequence but probably just conversionSequence
#
# but do we really need?

default = cms.Sequence(disp*conv*nucl)

