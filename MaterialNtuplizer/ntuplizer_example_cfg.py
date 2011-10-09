import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("Tests.MaterialNtuplizer.commonIncludes_example_cff")

## Top level replacement
#from Configuration.GlobalRuns.customise_Collision_38X import customise
#customise(process)

process.GlobalTag.globaltag = 'START311_V2::All'





readFiles = cms.untracked.vstring(
    'rfio:/castor/cern.ch/cms/store/relval/CMSSW_4_2_4/RelValMinBias/GEN-SIM-RECO/MC_42_V12-v1/0087/740BE641-EB8F-E011-8C14-0026189438BC.root')


secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
process.source = source



process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.pixClus = cms.EDProducer("SiPixelClusterMultiplicityProducer",
                                 clusterdigiCollection = cms.InputTag("siPixelClusters"),
                                 wantedSubDets = cms.VPSet(    
                                 cms.PSet(detSelection = cms.uint32(0),detLabel = cms.string("Pixel")),
                                 cms.PSet(detSelection = cms.uint32(1),detLabel = cms.string("BPIX")),
                                 cms.PSet(detSelection = cms.uint32(2),detLabel = cms.string("FPIX")) 
                                 )
                                 )


process.tkClus = cms.EDProducer("SiStripClusterMultiplicityProducer",
                                   clusterdigiCollection = cms.InputTag("siStripClusters"),
                                   wantedSubDets = cms.VPSet(    
                                                          cms.PSet(detSelection = cms.uint32(0),detLabel = cms.string("TK")),
                                                          cms.PSet(detSelection = cms.uint32(3),detLabel = cms.string("TIB")),
                                                          cms.PSet(detSelection = cms.uint32(4),detLabel = cms.string("TID")),
                                                          cms.PSet(detSelection = cms.uint32(5),detLabel = cms.string("TOB")),
                                                          cms.PSet(detSelection = cms.uint32(6),detLabel = cms.string("TEC"))
                                                          )
                                )


process.p = cms.Path(process.default)

