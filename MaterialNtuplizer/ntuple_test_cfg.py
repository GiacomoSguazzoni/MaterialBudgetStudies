from Base_cfg import *
#process.photonConvTrajSeedFromSingleLeg.ClusterCheckPSet.MaxNumberOfCosmicClusters=cms.uint32(50000)
#process.sca.switchOnGammaSelection = True
#process.sca.wantConversionHighPurity = True
process.maxEvents.input = 10
## process.TFileService.fileName = cms.string('monitor_ntuplizer_ref.root')
##process.load("Tests.MaterialNtuplizer.commonIncludes_MC_cff")
process.newConv.simulation = cms.bool(True)
process.newConv.prints = cms.bool(False)
process.newConv.redovtx = cms.bool(False)
process.newConv.hitassoc = cms.bool(True)
process.newConv.dataType = cms.untracked.string('DATARECO') # It can be:  "MCAOD, "MCRECO", "DATAAOD", "DATARECO"
process.newConv.outfile = cms.string('ntuple_conversion.root')
process.nucl.outfile = cms.string('ntuple_nuclint.root')
process.nucl.simulation = cms.bool(True)
process.nucl.prints = cms.bool(False)
process.nucl.dataType = cms.untracked.string('DATARECO') # It can be:  "MCAOD, "MCRECO", "DATAAOD", "DATARECO"
process.load("SimTracker.TrackAssociation.TrackAssociatorByHits_cfi")
process.TrackAssociatorByHits.SimToRecoDenominator = 'reco'
process.TrackAssociatorByHits.Quality_SimToReco = 0.5
process.TrackAssociatorByHits.Purity_SimToReco = 0.5
process.TrackAssociatorByHits.Cut_RecoToSim = 0.5
#process.s = cms.Schedule(process.p, process.convNtupl, process.nuclNtupl)
process.s = cms.Schedule(process.convNtupl, process.nuclNtupl)
