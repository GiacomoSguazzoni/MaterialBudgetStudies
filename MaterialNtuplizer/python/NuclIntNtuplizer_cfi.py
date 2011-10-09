from FWCore.MessageService.MessageLogger_cfi import *

nucl = cms.EDAnalyzer('NuclIntNtuplizer',
                      outfile = cms.string('ntuple_NI.root'),
                      hitassoc = cms.bool(False),
                      simulation = cms.bool(True),
                      prints = cms.bool(False)
)
