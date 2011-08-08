import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("Tests.MaterialNtuplizer.commonIncludes_MC_cff")

# Top level replacement
#from Configuration.GlobalRuns.reco_TLR_42X import customisePPMC
#customisePPMC(process)

process.GlobalTag.globaltag = "START44_V2::All"
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
#readFiles.extend( ['dummy.root']);
readFiles.extend( [
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-RECO/START42_V10-v1/0042/168A34DF-DD6D-E011-9259-002618943886.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-RECO/START42_V10-v1/0027/9A5DD7D6-4C67-E011-949C-002618943904.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-RECO/START42_V10-v1/0026/902A2CAA-CB66-E011-BF96-002618943916.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-RECO/START42_V10-v1/0026/702F87AA-D166-E011-B8F7-0018F3D0961E.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-RECO/START42_V10-v1/0026/42672887-DB66-E011-AA88-002618943970.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-RECO/START42_V10-v1/0026/2E6EB7BE-CC66-E011-991F-0018F3D09630.root'
    ]);

secFiles.extend( [
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0042/922B7EBE-DD6D-E011-979A-002618943910.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0027/F43A27D7-4C67-E011-A1AB-002618FDA28E.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/FAA7C7B8-CB66-E011-822A-0018F3D095FE.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/F08BB72A-CC66-E011-9F87-002354EF3BDB.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/B63C0737-CC66-E011-BDD1-001A92971AA8.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/AEE7352A-CB66-E011-99CE-003048678B94.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/8C9E80B8-CB66-E011-8CF9-001A92810A94.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/8A34B22D-CD66-E011-AB13-0026189438B3.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/7E538D9B-D066-E011-912B-00261894389E.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/72E52112-D666-E011-A4D6-002618943867.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/645751C4-CC66-E011-A8FE-001A92811728.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/3C321818-DC66-E011-B1A5-001A92971B9C.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/36422A33-CD66-E011-B4C8-003048679048.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/2EC934F9-CD66-E011-BF59-001A92810AEA.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/125F6B96-D566-E011-9082-002354EF3BE1.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/029794A3-D666-E011-B671-0030486792AC.root'
]);

process.source = source
#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(5000))
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

#from Tests.MaterialNtuplizer.LumiList import *
#runLister = LumiList(filename = 'Cert_132440-147454_7TeV_StreamExpress_Collisions10_JSON.txt')
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(str(runLister.getCMSSWString()).split(","))
#print runLister.getCMSSWString()

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1)
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.conv.simulation = cms.bool(True)
process.conv.redovtx = cms.bool(False)
process.conv.hitassoc = cms.bool(False)
process.newConv.simulation = cms.bool(True)
process.newConv.redovtx = cms.bool(False)
process.newConv.hitassoc = cms.bool(False)
process.nucl.simulation = cms.bool(True)

##process.p = cms.Path(process.bit40*process.noScraping*process.oneGoodVertexFilter*process.default)
##process.p = cms.Path(process.bptxAnd*process.hltMinimumBiasSelection*process.noScraping*process.oneGoodVertexFilter*process.default)
##process.p = cms.Path(process.bit34*process.noScraping*process.oneGoodVertexFilter*process.default)
##process.p = cms.Path(process.default)
process.p = cms.Path(process.defaultOnlyNewConv)
