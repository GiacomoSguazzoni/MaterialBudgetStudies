import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("Tests.MaterialNtuplizer.commonIncludes_MC_altTrig_cff")

# Top level replacement
#from Configuration.GlobalRuns.customise_Collision_38X import customise
#customise(process)

#process.GlobalTag.globaltag = "START38_V12::All"
process.GlobalTag.globaltag = 'START39_V6::All'
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
#readFiles.extend( ['rfio:/castor/cern.ch/cms/store/user/giordano/GammaConversion/SinglePhotonGun_cmst3_01/SinglePhoton_E_.5_10_GEN_SIM_DIGI_RAW_RECO_1.root']);
readFiles.extend( ['rfio:/castor/cern.ch/cms/store/user/giordano/GammaConversion/SinglePhotonGun_CMSSW392_04/SinglePhoton_E_.5_10_GEN_SIM_DIGI_RAW_RECO_86_1_xfS.root']);
process.source = source

#from Tests.MaterialNtuplizer.LumiList import *
#runLister = LumiList(filename = 'Cert_132440-147454_7TeV_StreamExpress_Collisions10_JSON.txt')
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(str(runLister.getCMSSWString()).split(","))
#print runLister.getCMSSWString()

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(100))
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.conv.outfile = cms.string('ntuple_conversion_MinBiasMC_altTrig.root')
process.conv.simulation = cms.bool(True)
process.conv.redovtx = cms.bool(False)
process.nucl.outfile = cms.string('ntuple_nuclint_MinBiasMC_altTrig.root')
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
process.seventhPLSeeds.OrderedHitsFactoryPSet.maxElement = cms.uint32(10000) #Default 1000

#=====================================================================================

##process.p = cms.Path(process.bit40*process.noScraping*process.oneGoodVertexFilter*process.default)
process.p = cms.Path(process.localReco
                     *process.finaltrackCollectionMerging
                     *process.default)

##process.p = cms.Path(process.default)




