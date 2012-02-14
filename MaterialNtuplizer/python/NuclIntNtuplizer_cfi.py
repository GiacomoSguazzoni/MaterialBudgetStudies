from FWCore.MessageService.MessageLogger_cfi import *

nucl = cms.EDAnalyzer('NuclIntNtuplizer',
                      outfile = cms.string('ntuple_NI.root'),
                      hitassoc = cms.bool(False),
                      simulation = cms.bool(True),
                      prints = cms.bool(False),
                      pfDisplacedVertex = cms.InputTag("particleFlowDisplacedVertex"),
                      generalTracks = cms.InputTag("generalTracks"),
                      dataType = cms.untracked.string('MCRECO') # It can be:  "MCAOD, "MCRECO", "DATAAOD", "DATARECO"
)
