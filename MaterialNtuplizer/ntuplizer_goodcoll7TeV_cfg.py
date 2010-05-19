import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("Tests.MaterialNtuplizer.commonIncludes_cff")

process.GlobalTag.globaltag = "GR_R_35X_V8B::All"
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( ['dummy.root']);
process.source = source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(5000))

from Tests.MaterialNtuplizer.LumiList import *
runLister = LumiList(filename = 'Cert_132440-134725_7TeV_MinimumBias_May6ReReco_Collisions10_JSON.txt')
process.source.lumisToProcess = cms.string(str(runLister.getCMSSWString()))
print process.source.lumisToProcess

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(5000))
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.conv.outfile = cms.string('ntuple_conversion_goodcoll7TeV.root')
process.conv.simulation = cms.bool(False)
process.convHit.outfile = cms.string('ntuple_conversion_goodcoll7TeV_hit.root')
process.convHit.simulation = cms.bool(False)
process.nucl.outfile = cms.string('ntuple_nuclint_goodcoll7TeV.root')
process.nucl.simulation = cms.bool(False)

process.p = cms.Path(process.bit40*process.noScraping*process.oneGoodVertexFilter*process.default)

