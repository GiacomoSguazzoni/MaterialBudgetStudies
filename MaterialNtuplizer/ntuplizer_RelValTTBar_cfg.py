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
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-RECO/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/A6F99528-1A69-E011-8891-003048678F74.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-RECO/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/78A4A263-2369-E011-AB4D-003048678B08.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-RECO/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/606B87D7-2069-E011-A9AC-003048678DA2.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-RECO/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/5E3925AA-1B69-E011-947A-001A92971B82.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-RECO/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/44132980-1869-E011-81E8-001A92971B32.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-RECO/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/3ED0A5CC-1A69-E011-9B1B-001A92810AD2.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-RECO/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/3E9967E0-1C69-E011-AA9B-003048678B20.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-RECO/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/0ECAB00E-4069-E011-B8DB-00261894389D.root'
    ]);

secFiles.extend( [
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/E41F15F0-1969-E011-A12A-0030486792AC.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/E0D7860C-2369-E011-B582-0018F3D0961A.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/CCECEBEE-1B69-E011-AE71-00304867C16A.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/C27C5267-1B69-E011-8BD5-00261894397B.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/B4BFC372-1969-E011-9E24-003048679044.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/B43CAD61-1E69-E011-9919-00304867BFF2.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/AE165B8E-1F69-E011-86EC-001A92971B5E.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/A8BAC762-2269-E011-B2FB-0018F3D096F8.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/A25BA0EF-1769-E011-A173-002618943974.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/A07A538A-2569-E011-B7C1-002354EF3BCE.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/9E812055-3D69-E011-92D6-001A92971B64.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/98FDCE70-1B69-E011-963B-003048679010.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/98E5AC66-2369-E011-97D9-0018F3D0961A.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/929BFC6F-1A69-E011-834F-0026189437FE.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/804F2B57-2169-E011-A542-002618943856.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/72F0975D-2069-E011-B0BA-003048679076.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/6A0CE763-1B69-E011-84B5-00304866C398.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/667F676D-1869-E011-9530-00261894387B.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/5C845F2E-1969-E011-8162-003048679044.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/56F61F62-1D69-E011-8968-0030486792DE.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/461C9FFC-1A69-E011-96F4-002618FDA208.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/2E06D56D-1A69-E011-893D-003048679228.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/1A1CC567-1A69-E011-98D1-00261894390B.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/1835F913-1969-E011-8B46-001A92971B32.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/0E66DF67-1C69-E011-8B1B-003048678BF4.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/0A857172-1969-E011-A710-00304867BEDE.root'
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

