from FWCore.MessageService.MessageLogger_cfi import *

conv = cms.EDAnalyzer('ConversionNtuplizer',
                      outfile = cms.string('ntuple_conversion.root'),
                      generalTkOnly = cms.bool(False),#if do only generalTracks or all merged tracks
                      hitassoc = cms.bool(False),
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
