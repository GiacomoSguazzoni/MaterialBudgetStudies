from FWCore.MessageService.MessageLogger_cfi import *

conv = cms.EDAnalyzer('ConversionNtuplizer',
                      outfile = cms.string('ntuple_conversion.root'),
                      generalTkOnly = cms.bool(True),#if do only generalTracks or all merged tracks
                      hitassoc = cms.bool(True),
		      retracking = cms.bool(False),#if re-doing tracking, for dedicated tracking test ONLY
                      minPhoPtForEffic = cms.double(0.3),#when hardcoded it was 2.5
                      maxPhoEtaForEffic = cms.double(2.5),
                      maxPhoZForEffic = cms.double(200.),
                      maxPhoRForEffic = cms.double(100.),
                      minPhoPtForPurity = cms.double(0.3),#when hardcoded it was 0.5
                      maxPhoEtaForPurity = cms.double(2.5),
                      maxPhoZForPurity = cms.double(200.),
                      maxPhoRForPurity = cms.double(100.),
                      simulation = cms.bool(True),
                      prints = cms.bool(False)
                      )

newConv = cms.EDAnalyzer('NewConversionNtuplizer',
                         outfile = cms.string('newNtuple_conversion.root'),
                         primaryVerticesTag = cms.InputTag('offlinePrimaryVertices'),
                         generalTkOnly = cms.bool(True),#if do only generalTracks or all merged tracks
                         redovtx = cms.bool(False),
                         hitassoc = cms.bool(True),
                         retracking = cms.bool(False),#if re-doing tracking, for dedicated tracking test ONLY
                         minPhoPtForEffic = cms.double(0.3),#when hardcoded it was 2.5
                         maxPhoEtaForEffic = cms.double(2.5),
                         maxPhoZForEffic = cms.double(200.),
                         maxPhoRForEffic = cms.double(100.),
                         minPhoPtForPurity = cms.double(0.3),#when hardcoded it was 0.5
                         maxPhoEtaForPurity = cms.double(2.5),
                         maxPhoZForPurity = cms.double(200.),
                         maxPhoRForPurity = cms.double(100.),
                         simulation = cms.bool(True),
                         dataType = cms.untracked.string('AOD'), # It can be either "AOD or "RECO"
                         prints = cms.bool(False)
                         )
