import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("Tests.MaterialNtuplizer.commonIncludes_cff")

process.GlobalTag.globaltag = "START3X_V26::All" #7
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

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(5000))
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.conv.outfile = cms.string('ntuple_conversion_minbias7TeV_relval.root')
process.conv.simulation = cms.bool(True)
process.convHit.outfile = cms.string('ntuple_conversion_minbias7TeV_relval_hit.root')
process.convHit.simulation = cms.bool(True)
process.nucl.outfile = cms.string('ntuple_nuclint_minbias7TeV_relval.root')
process.nucl.simulation = cms.bool(True)

process.p = cms.Path(process.bit40*process.noScraping*process.oneGoodVertexFilter*process.default)

