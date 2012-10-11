import FWCore.ParameterSet.Config as cms
import copy
import sys


# === Give values to some basic parameters === #
maxEvents	= -1
reportEvery	= 100
tauMaxEta	= 9
tauMinPt	= 0

# collection postfix for running on PF2APT
postfix = ''
# postfix = 'PFlow'

# === Parse external arguments === #
import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing("analysis")
# analysisType parameter form: 
# 
# <era>_<type>_<lepton flavor>
#
# <era> = Fall11,Spring12,2011A,2011B,2012X
# <type> = MC_sig, MC_bg, data_PR, data_RR
# <lepton flaor> = muon, electron
#
# Examples:
# Fall11_MC_sig_muon
# 2011B_data_PR_electron
# Summer12_MC_bg_electron
# 2012B_data_PR_muon
options.register ('analysisType', # 
                  'Fall11_MC_sig_muon', # default value
                  VarParsing.VarParsing.multiplicity.singleton,
                  VarParsing.VarParsing.varType.string )
options.maxEvents = maxEvents
options.outputFile = 'ntuple.root'
options.inputFiles = 'file:/store/user/jkolb/TTH_HtoTauTau_M_125_7TeV_FullSim_Pythia6_v2/skimTTHiggsToDiTau_428_v8_TTH_125_FullSim/25a6c8a18b2b0964299388fc37b7979d/ttHiggsToDiTauSkim_100_1_NwK.root'
options.parseArguments() # get and parse the command line arguments 

if options.analysisType.find('muon') == -1 and options.analysisType.find('electron') == -1:
    print 'analysisType must contain "muon" or "electron"'
    exit(1)

# === Print some basic info about the job setup === #
print ''
print '	========================================='
print '		Ntuple Making Job'
print '	========================================='
print ''
print '		Sample ID......%s' % options.analysisType
print '		Max events.....%d' % options.maxEvents
print '		Report every...%d' % reportEvery
print ''
print '	========================================='
print ''

# === Set up triggers and GEN collections based on analysis type === # 
if options.analysisType.find('MC') != -1:
    inputForGenParticles = 'genParticles'
    inputForGenJets     = 'selectedPatJets:genJets:'
    triggerConditions = (
        'HLT_IsoMu24_v*',
        'HLT_IsoMu24_eta2p1_v*'
    )
    if options.analysisType.find('electron') != -1:
        triggerConditions = (
            'HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30_v*',
            'HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30_v*',
            'HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30_v*'
        )

if options.analysisType.find('data') != -1:
    inputForGenParticles = ''
    inputForGenJets         = ''
    triggerConditions = (
        'HLT_IsoMu24_v*',
        'HLT_IsoMu24_eta2p1_v*'
    )
    if options.analysisType.find('electron') != -1:
        triggerConditions = (
            'HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30_v*',
            'HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30_v*',
            'HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30_v*'
        )


# === make analysis-specific selections for skims, fillers, etc. === #
SkimTriggerRequirements	= cms.vstring()
        #	'ttHiggsElectronSkim',
        #   'ttHiggsMuonSkim',
        #	'ttElectronHiggsToElecTauSkim',
        #	'ttMuonHiggsToElecTauSkim',
        #	'ttElectronHiggsToMuTauSkim',
        #	'ttMuonHiggsToMuTauSkim',
        #	'ttElectronHiggsToTauTauSkim',
        #	'ttMuonHiggsToTauTauSkim',
        #	'ttHiggsToElecTauSkim',
        #	'ttHiggsToMuTauSkim',
        #   'ttHiggsToTauTauSkim',

if (options.analysisType.find('sig') != -1 ) and (options.analysisType.find('muon') != -1):
    SkimTriggerRequirements = cms.vstring('ttMuonHiggsToTauTauSkim')
if (options.analysisType.find('sig') != -1 ) and (options.analysisType.find('electron') != -1):
    SkimTriggerRequirements = cms.vstring('ttElectronHiggsToTauTauSkim')
if (options.analysisType.find('bg') != -1 ) and (options.analysisType.find('muon') != -1):
    SkimTriggerRequirements = cms.vstring('ttHiggsMuonSkim')
if (options.analysisType.find('bg') != -1 ) and (options.analysisType.find('electron') != -1):
    SkimTriggerRequirements = cms.vstring('ttHiggsElectronSkim')
if (options.analysisType.find('data') != -1 ) and (options.analysisType.find('muon') != -1):
    SkimTriggerRequirements = cms.vstring('ttHiggsMuonSkim')
if (options.analysisType.find('data') != -1 ) and (options.analysisType.find('electron') != -1):
    SkimTriggerRequirements = cms.vstring('ttHiggsElectronSkim')

NtupleFillers = cms.untracked.vstring(
        'Event',
        'GenLevel',
        'GenTau',
        'GenJet',
        'Tau',
        'Electron',
        'Muon',
        'Jet',
        'DitauMuon',
        'DitauElectron',
        #'Trigger' # not in use
)

# === Python process === #
process = cms.Process('TTbarHTauTau')


# === Load and set up basic services === #
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = reportEvery
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( options.maxEvents ) )
process.source = cms.Source("PoolSource",
    skipEvents = cms.untracked.uint32(0),
    fileNames = cms.untracked.vstring(options.inputFiles)
)
process.TFileService = cms.Service("TFileService", fileName = cms.string(options.outputFile) )

# === Collision data trigger requirements === #
import HLTrigger.HLTfilters.triggerResultsFilter_cfi as hlt
process.hltFilter = hlt.triggerResultsFilter.clone(
        hltResults = cms.InputTag('TriggerResults::HLT'),
        triggerConditions = cms.vstring(triggerConditions),
        l1tResults = '',
        throw = False
)

analysisTypeForNtuplizer = 'coll'
if options.analysisType.find('sig') != -1 :
    analysisTypeForNtuplizer = 'signal'
if options.analysisType.find('bg') != -1 :
    analysisTypeForNtuplizer = 'mc'


# === Define and setup main module === #
process.makeNtuple = cms.EDAnalyzer('Ntuplizer',

	# === Analysis setup === #
	AnalysisType						= cms.string(analysisTypeForNtuplizer),				
    TreeName							= cms.untracked.string('TTbarHTauTau'),

	# === HL Trigger === # (not in use)
    HLTriggerSource		    			= cms.InputTag("TriggerResults::HLT"),

	# === Skim Trigger === #
    ApplySkimTriggerRequirements		= cms.bool(True),
    SkimTriggerSource					= cms.InputTag("TriggerResults","","skimTTHiggsToDiTau"),
    SkimTriggerRequirements				= SkimTriggerRequirements,

	# === Which branches to fill? === #
	NtupleFillers						= NtupleFillers,

	# === Input collections === #
    GenParticleSource					= cms.untracked.InputTag(inputForGenParticles),
    GenJetSource                        = cms.untracked.InputTag(inputForGenJets),
    RecoTauSource						= cms.InputTag('selectedPatTaus'+postfix),
    RecoMuonSource						= cms.InputTag('selectedPatMuons'+postfix),
    RecoElectronSource					= cms.InputTag('selectedPatElectrons'+postfix),
    RecoJetSource                       = cms.InputTag('selectedPatJets'+postfix+'::skimTTHiggsToDiTau'),
    RecoVertexSource					= cms.InputTag('offlinePrimaryVertices'),
    RecoPATMetSource					= cms.InputTag('patMETs'+postfix),
    RecoPFMetSource						= cms.InputTag('patMETs'+postfix),

    RecoTauMinPt                        = cms.double(tauMinPt),
    RecoTauMaxAbsEta                    = cms.double(tauMaxEta),
    RecoTauRequireDMF                   = cms.bool(False),

	# === Jet stuff === #
    RecoJetMinEt						= cms.double(30.0),
    RecoJetMinAbsEta					= cms.double(0.0),
    RecoJetMaxAbsEta					= cms.double(2.4),
    JetAntiMatchingDeltaR               = cms.double(0.25),
	CSVlooseWP							= cms.double(0.244),
	CSVmediumWP							= cms.double(0.679),
	CSVtightWP							= cms.double(0.898),

	# === === #
)

# === Run sequence === # 
if options.analysisType.find('data') != -1:
    process.p = cms.Path( process.hltFilter + process.makeNtuple )
else:
    process.p = cms.Path( process.makeNtuple )

# === Write-out all python configuration parameter information === #
#pythonDump = open("dumpedPython.py", "write")
#print >> pythonDump,  process.dumpPython()

