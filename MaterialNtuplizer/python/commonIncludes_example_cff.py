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

#from Tests.MaterialNtuplizer.ConversionNtuplizer_cfi import conv
from Tests.MaterialNtuplizer.NuclIntNtuplizer_cfi import nucl
#convHit = conv.clone(hitassoc = cms.bool(True))

#
# Hi stuff
#from HeavyIonsAnalysis.Configuration.collisionEventSelection_cff import *
#
# HI HLT Filter
#from HLTrigger.special.hltPixelActivityFilter_cfi import *
#hltPixelActivityFilter.maxClusters = cms.uint32( 1000 )
#hltPixelActivityFilter.inputTag    = 'siPixelClusters'

particleFlowDisplacedVertexCandidate.debug = cms.untracked.bool(False)
particleFlowDisplacedVertexCandidate.verbose = cms.untracked.bool(False)
particleFlowDisplacedVertex.debug = cms.untracked.bool(False)
particleFlowDisplacedVertex.verbose = cms.untracked.bool(False)

particleFlowDisplacedVertex.tracksSelectorParameters.dxy_min = cms.double(0.0)
particleFlowDisplacedVertex.primaryVertexCut = cms.double(2.0)
particleFlowDisplacedVertex.primaryVertexCut = cms.double(2.0)
particleFlowDisplacedVertexCandidate.primaryVertexCut = cms.double(1.8)

disp = cms.Sequence(
    particleFlowDisplacedVertexCandidate +
    particleFlowDisplacedVertex
)

#default = cms.Sequence(siPixelRecHits*siStripMatchedRecHits*ckftracks_wodEdX*
#                       trackerOnlyConversionSequence*disp*conv#*convHit
#                       *nucl
#		       )

default = cms.Sequence(disp*nucl)
##default = cms.Sequence(collisionEventSelection*siPixelRecHits*siStripMatchedRecHits*ckftracks_wodEdX*disp*nucl)
###default = cms.Sequence(collisionEventSelection*offlineBeamSpot*hltPixelActivityFilter*siPixelRecHits*siStripMatchedRecHits*ckftracks_wodEdX*disp*nucl)


