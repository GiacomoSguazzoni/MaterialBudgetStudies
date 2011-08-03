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
#QCD
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-RECO/START42_V10-v1/0042/168A34DF-DD6D-E011-9259-002618943886.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-RECO/START42_V10-v1/0027/9A5DD7D6-4C67-E011-949C-002618943904.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-RECO/START42_V10-v1/0026/902A2CAA-CB66-E011-BF96-002618943916.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-RECO/START42_V10-v1/0026/702F87AA-D166-E011-B8F7-0018F3D0961E.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-RECO/START42_V10-v1/0026/42672887-DB66-E011-AA88-002618943970.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-RECO/START42_V10-v1/0026/2E6EB7BE-CC66-E011-991F-0018F3D09630.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0042/DE3766D3-DD6D-E011-9195-003048678A80.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0026/AA4563A4-D866-E011-A410-001A92971BD8.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0026/584CF0F7-E366-E011-9ECE-003048B95B30.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0026/3E09E703-DF66-E011-880C-002354EF3BE0.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0026/2E4872A7-D666-E011-A5E8-0018F3D096FE.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0026/169D257D-4767-E011-A46C-001A928116FE.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0026/0C900BA8-D566-E011-A1F3-001A92971B0C.root',
#TTBar
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-RECO/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/A6F99528-1A69-E011-8891-003048678F74.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-RECO/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/78A4A263-2369-E011-AB4D-003048678B08.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-RECO/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/606B87D7-2069-E011-A9AC-003048678DA2.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-RECO/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/5E3925AA-1B69-E011-947A-001A92971B82.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-RECO/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/44132980-1869-E011-81E8-001A92971B32.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-RECO/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/3ED0A5CC-1A69-E011-9B1B-001A92810AD2.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-RECO/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/3E9967E0-1C69-E011-AA9B-003048678B20.root',
    '/store/relval/CMSSW_4_2_1/RelValTTbar_Tauola/GEN-SIM-RECO/START42_V10_PU_E7TeV_FlatDist10_2011EarlyData_inTimeOnly-v1/0030/0ECAB00E-4069-E011-B8DB-00261894389D.root'
    ]);


process.source = source
#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(5000))
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

#from Tests.MaterialNtuplizer.LumiList import *
#runLister = LumiList(filename = 'Cert_132440-147454_7TeV_StreamExpress_Collisions10_JSON.txt')
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(str(runLister.getCMSSWString()).split(","))
#print runLister.getCMSSWString()

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.conv.outfile = cms.string('ntuple_conversion.root')
process.conv.simulation = cms.bool(True)
process.conv.redovtx = cms.bool(False)
process.nucl.outfile = cms.string('ntuple_nuclint.root')
process.nucl.simulation = cms.bool(True)

##process.p = cms.Path(process.bit40*process.noScraping*process.oneGoodVertexFilter*process.default)
##process.p = cms.Path(process.bptxAnd*process.hltMinimumBiasSelection*process.noScraping*process.oneGoodVertexFilter*process.default)
##process.p = cms.Path(process.bit34*process.noScraping*process.oneGoodVertexFilter*process.default)
##process.p = cms.Path(process.default)
process.p = cms.Path(process.defaultOnlyConv)
