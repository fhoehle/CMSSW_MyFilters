import FWCore.ParameterSet.Config as cms

myTTbarGenEvent10Parts= cms.EDProducer('MyTTbarGenEvent10Parts',
        genTag = cms.untracked.InputTag("genParticles"),
        )
DiLepMcFilter = cms.EDFilter('DiLepMcFilter',
        ttbarEventTag = cms.untracked.InputTag("myTTbarGenEvent10Parts"),
        )
pdgIdTest = cms.PSet(min          = cms.untracked.double(     -30.5),
                          max          = cms.untracked.double(    30.5),
                          nbins        = cms.untracked.int32 (     122),
                          name         = cms.untracked.string('GenPartPt'),
                          description  = cms.untracked.string(     ''),
                          plotquantity = cms.untracked.string(   'pdgId')
                          )
genHists = cms.EDAnalyzer(
    'CandViewHistoAnalyzer',
    src = cms.InputTag('myTTbarGenEvent10Parts'),
    histograms = cms.VPSet(pdgIdTest)
)

