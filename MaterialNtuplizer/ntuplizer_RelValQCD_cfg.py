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
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-RECO/START42_V10-v1/0026/2E6EB7BE-CC66-E011-991F-0018F3D09630.root',
#    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-RECO/MC_42_V10-v1/0029/1AF4A305-6D67-E011-8F95-002354EF3BE6.root',
#    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-RECO/MC_42_V10-v1/0026/3068F838-CA66-E011-AB8B-0018F3D095FA.root',
#    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-RECO/MC_42_V10-v1/0025/E86DAF96-B166-E011-93B9-002354EF3BE0.root',
#    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-RECO/MC_42_V10-v1/0025/C490DD1A-B566-E011-986F-002354EF3BDE.root',
#    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_80_120/GEN-SIM-RECO/MC_42_V10-v1/0025/78344618-B166-E011-A105-002618FDA211.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0042/DE3766D3-DD6D-E011-9195-003048678A80.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0026/AA4563A4-D866-E011-A410-001A92971BD8.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0026/584CF0F7-E366-E011-9ECE-003048B95B30.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0026/3E09E703-DF66-E011-880C-002354EF3BE0.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0026/2E4872A7-D666-E011-A5E8-0018F3D096FE.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0026/169D257D-4767-E011-A46C-001A928116FE.root',
    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/START42_V10-v1/0026/0C900BA8-D566-E011-A1F3-001A92971B0C.root'
#    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/MC_42_V10-v1/0056/F0ECA843-9474-E011-BAAB-001A92971B9C.root',
#    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/MC_42_V10-v1/0028/E4E1E142-5D67-E011-9461-00261894395A.root',
#    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/MC_42_V10-v1/0026/EA07ADA3-D866-E011-B2BB-001A928116B2.root',
#    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/MC_42_V10-v1/0025/E0E51A9F-B966-E011-84E3-002354EF3BE1.root',
#    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/MC_42_V10-v1/0025/70B6F814-BA66-E011-9376-002354EF3BE1.root',
#    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/MC_42_V10-v1/0025/342C6F65-C366-E011-A717-0018F3D0962A.root',
#    '/store/relval/CMSSW_4_2_1/RelValQCD_Pt_3000_3500/GEN-SIM-RECO/MC_42_V10-v1/0025/2A167FAE-BC66-E011-8B74-003048678ED4.root',
#    '/store/relval/CMSSW_4_2_1/RelValQCD_FlatPt_15_3000/GEN-SIM-RECO/MC_42_V10-v1/0026/DEC37B91-DF66-E011-8287-001A92810ACA.root',
#    '/store/relval/CMSSW_4_2_1/RelValQCD_FlatPt_15_3000/GEN-SIM-RECO/MC_42_V10-v1/0026/16EEDE57-CC66-E011-97D1-001A92971BDC.root',
#    '/store/relval/CMSSW_4_2_1/RelValQCD_FlatPt_15_3000/GEN-SIM-RECO/MC_42_V10-v1/0026/08BDD8DE-4867-E011-B3A5-001A92810AAE.root',
#    '/store/relval/CMSSW_4_2_1/RelValQCD_FlatPt_15_3000/GEN-SIM-RECO/MC_42_V10-v1/0026/00AE2A40-CB66-E011-9FA7-002618943908.root',
#    '/store/relval/CMSSW_4_2_1/RelValQCD_FlatPt_15_3000/GEN-SIM-RECO/MC_42_V10-v1/0025/7E885B9E-C066-E011-A476-003048678E2A.root'
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
