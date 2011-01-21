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
readFiles.extend( ['dummy.root']);
process.source = source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(5000))

#from Tests.MaterialNtuplizer.LumiList import *
#runLister = LumiList(filename = 'Cert_132440-147454_7TeV_StreamExpress_Collisions10_JSON.txt')
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(str(runLister.getCMSSWString()).split(","))
#print runLister.getCMSSWString()

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(5000))
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.conv.outfile = cms.string('ntuple_conversion_MinBiasMC_altTrig.root')
process.conv.simulation = cms.bool(True)
process.conv.hitassoc = cms.bool(True)
process.conv.redovtx = cms.bool(False)
process.TrackAssociatorByHits.Quality_SimToReco = 0.75
process.TrackAssociatorByHits.Purity_SimToReco = 0.75
process.TrackAssociatorByHits.Cut_RecoToSim = 0.75

##process.p = cms.Path(process.bit40*process.noScraping*process.oneGoodVertexFilter*process.default)
##process.p = cms.Path(process.bptxAnd*process.hltMinimumBiasSelection*process.noScraping*process.oneGoodVertexFilter*process.default)
process.p = cms.Path(process.bit34*process.noScraping*process.oneGoodVertexFilter*process.default_conv)

