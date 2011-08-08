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
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0042/DE3766D3-DD6D-E011-9195-003048678A80.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0026/AA4563A4-D866-E011-A410-001A92971BD8.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0026/584CF0F7-E366-E011-9ECE-003048B95B30.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0026/3E09E703-DF66-E011-880C-002354EF3BE0.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0026/2E4872A7-D666-E011-A5E8-0018F3D096FE.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0026/169D257D-4767-E011-A46C-001A928116FE.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0026/0C900BA8-D566-E011-A1F3-001A92971B0C.root'
    ]);

secFiles.extend( [
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0042/686D7DB1-DD6D-E011-9E67-0026189437F0.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0027/3AFB9C9C-4C67-E011-866A-00261894396B.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/FABDD80A-DF66-E011-A37A-001A92810AD8.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/FA4CF49B-DF66-E011-9AB2-001A9281173A.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/F8978C9D-D966-E011-BE91-0018F3D09654.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/D2A688CA-FE66-E011-9330-003048678F0C.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/CC4F49FF-E366-E011-A44A-0018F3D0969A.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/CC3E4A27-D666-E011-B8C2-003048678F84.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/BA9C3799-D566-E011-B0FB-00248C0BE012.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/B0A17136-D666-E011-9C3E-001A92971B0C.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/AEC2FB09-DC66-E011-A82A-0030486792BA.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/9ED4B497-D466-E011-AF98-002618943953.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/9ECC6486-DE66-E011-9878-003048679296.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/9E87B69B-D566-E011-AE9F-002618943916.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/7E1F04F1-E266-E011-8E6F-002618943811.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/7A0CFEEB-E666-E011-99F0-003048678D6C.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/6E6B2D07-E066-E011-B103-003048678FC6.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/6C7DC117-D666-E011-9612-003048678FF8.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/60B3E90E-D866-E011-B991-0026189437F2.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/5EB7DF26-D766-E011-B531-003048679188.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/2AAAAB1B-D566-E011-AF0F-002618943849.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/28CED022-D766-E011-8364-003048678A72.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/20996A21-D666-E011-BE99-003048678BEA.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/START42_V10-v1/0026/02EF69EF-E466-E011-8331-002354EF3BE3.root'
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
