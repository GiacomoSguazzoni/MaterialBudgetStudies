import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = "START3X_V26::All" #7

process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("RecoParticleFlow.PFTracking.particleFlowDisplacedVertexCandidate_cff")
process.load("RecoParticleFlow.PFTracking.particleFlowDisplacedVertex_cff")

process.load("SimTracker.TrackAssociation.TrackAssociatorByHits_cfi");

readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
'/store/relval/CMSSW_3_5_7/RelValMinBias/GEN-SIM-RECO/START3X_V26-v1/0012/B8D5AE61-6949-DF11-879B-00261894393F.root',
'/store/relval/CMSSW_3_5_7/RelValMinBias/GEN-SIM-RECO/START3X_V26-v1/0012/5A8D65DF-4449-DF11-816E-003048678AC0.root'
]);
secFiles.extend( [
'/store/relval/CMSSW_3_5_7/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/START3X_V26-v1/0013/A6789918-6949-DF11-B7C9-001A928116FA.root',
'/store/relval/CMSSW_3_5_7/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/START3X_V26-v1/0012/DABE674A-4449-DF11-8744-00304867915A.root',
'/store/relval/CMSSW_3_5_7/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/START3X_V26-v1/0012/D09F5CD7-4549-DF11-9B93-003048B95B30.root',
'/store/relval/CMSSW_3_5_7/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/START3X_V26-v1/0012/545488DD-4449-DF11-B803-003048678BAA.root',
'/store/relval/CMSSW_3_5_7/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/START3X_V26-v1/0012/46307C48-4549-DF11-B0BB-003048678F6C.root'
 ]);
process.source = source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1000))

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.conv = cms.EDAnalyzer('ConversionNtuplizer',
                              outfile = cms.string('ntuple_conversion_minbias7TeV_relval.root'),
                              kinevtx = cms.bool(True),
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

process.convHit = process.conv.clone(outfile = cms.string('ntuple_conversion_minbias7TeV_relval_hit.root'),hitassoc = cms.bool(True))

process.nucl = cms.EDAnalyzer('NuclIntNtuplizer',
                              outfile = cms.string('ntuple_nuclint_minbias7TeV_relval.root'),
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

process.p = cms.Path(process.bit40*process.noScraping*process.oneGoodVertexFilter*process.default)

