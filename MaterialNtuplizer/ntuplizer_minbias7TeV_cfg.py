import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("Tests.MaterialNtuplizer.commonIncludes_cff")

process.GlobalTag.globaltag = "START3X_V25B::All"
process.load("Tests.MaterialNtuplizer.filesMinBiasSTART3X_V25B")

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(5000))
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.conv.outfile = cms.string('ntuple_conversion_minbias7TeV.root')
process.conv.simulation = cms.bool(True)
process.convHit.outfile = cms.string('ntuple_conversion_minbias7TeV_hit.root')
process.convHit.simulation = cms.bool(True)
process.nucl.outfile = cms.string('ntuple_nuclint_minbias7TeV.root')
process.nucl.simulation = cms.bool(True)

process.p = cms.Path(process.bit40*process.noScraping*process.oneGoodVertexFilter*process.default)

