import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("Tests.MaterialNtuplizer.commonIncludes_MC_altTrig_cff")

# Top level replacement
from Configuration.GlobalRuns.customise_Collision_38X import customise
customise(process)

process.GlobalTag.globaltag = "START38_V12::All"
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend(['/store/relval/CMSSW_3_9_2//RelValZmumuJets_Pt_20_300_GEN/GEN-SIM-RECO/MC_39Y_V3_PU_E7TeV_AVE_2_BX2808-v1/0011/003ABB1C-07EC-DF11-8AFC-0030487CD700.root']);

process.source = source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(5000))

#from Tests.MaterialNtuplizer.LumiList import *
#runLister = LumiList(filename = 'Cert_132440-147454_7TeV_StreamExpress_Collisions10_JSON.txt')
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(str(runLister.getCMSSWString()).split(","))
#print runLister.getCMSSWString()

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(5000))
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.conv.outfile = cms.string('ntuple_conversion_MinBiasMC_DG.root')
process.conv.simulation = cms.bool(True)
process.conv.redovtx = cms.bool(False)
process.nucl.outfile = cms.string('ntuple_nuclint_MinBiasMC_DG.root')
process.nucl.simulation = cms.bool(True)

#=====================================================================================

#------------------------------------------------------------------------------------
# Track re-reco for conversion
#------------------------------------------------------------------------------------

process.load('GammaConversion.TrackingForConversion.ModifyStdSequence_Slim_cff')

process.localReco = cms.Sequence(process.siPixelRecHits*process.siStripMatchedRecHits)

process.seventhSeedsTk.takeAll = False
process.seventhSeeds.takeAll = False

##---- Customize cut on max seed (increased of a factor 10)
process.seventhPLSeeds.OrderedHitsFactoryPSet.maxElement = cms.uint32(1000) #Default 

#=====================================================================================

##process.p = cms.Path(process.bit40*process.noScraping*process.oneGoodVertexFilter*process.default)
process.p = cms.Path(
#    process.bit34*process.noScraping*process.oneGoodVertexFilter*
                     process.localReco*
                     process.finaltrackCollectionMerging*
                     process.default)

#----- Printout
print '-----> conversionStep'
print process.conversionStep.dumpSequenceConfig
print '-----> trackCollectionMerging'
print process.trackCollectionMerging.dumpSequenceConfig
print '-----> generalTracks'
print process.generalTracks.dumpSequenceConfig
print '-----> iterTracking'
print process.iterTracking.dumpSequenceConfig
print '-----> ckftracks'
print process.ckftracks_wodEdX.dumpSequenceConfig
print '-----> seventhSeedsTk'
print process.seventhSeedsTk.dumpSequenceConfig
print '-----> sixthClusters'
print process.sixthClusters.dumpSequenceConfig


