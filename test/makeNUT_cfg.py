import FWCore.ParameterSet.Config as cms
import copy
import sys


# === Give values to some basic parameters === #
maxEvents	= -1
reportEvery	= 100
maxEvents	= 100
reportEvery	= 1
tauMaxEta	= 9
tauMinPt	= 0

debugLevel	= 0 # 0: no debug, 5: full debug

# collection postfix for running on PF2APT
postfix = ''
# postfix = 'PFlow'

# === Parse external arguments === #
import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing("analysis")
# 'analysisType' parameter form: 
# 
# <era>_<subera>_<type>_<lepton flavor>_<sample number>
#
# <era>					= 2011, 2012
# <subera> [N/A for MC]	= A, B, C...
# <type>				= MC-sig, MC-bg, data-PR, data-RR
# <lepton flavor>		= muon, electron
# <sample number>		= See https://twiki.cern.ch/twiki/bin/view/CMS/TTbarHiggsTauTau#Process_info
#
# Examples:
# 2011_X_MC-sig_muon
# 2011_B_data-PR_electron
# 2012_X_MC-bg_electron
# 2012_B_data-PR_muon
options.register ('analysisType', # 
				  #'2012_X_data-PR_muon_-11',	# -1		2012A collisions
				  #'2012_X_MC-bg_muon_-1',	# -1		2012A collisions
				  #'2012_X_MC-bg_muon_-11',	# -11		2012B collisions
				  #'2012_X_MC-bg_muon_2500',	# 2500	TTbar
				  #'2012_X_MC-bg_muon_2524',	# 2524	TTbar + W
				  #'2012_X_MC-bg_muon_2523',	# 2523	TTbar + Z
				  #'2012_X_MC-bg_muon_2400',	# 2400	W+jets
				  #'2012_X_MC-bg_muon_2800',	# 2800	Z+jets (50<M)
				  #'2012_X_MC-bg_muon_2850',	# 2850	Z+jets (10<M<50)
				  #'2012_X_MC-bg_muon_2700',	# 2700	WW	
				  #'2012_X_MC-bg_muon_2701',	# 2701	WZ
				  #'2012_X_MC-bg_muon_2702',	# 2702	ZZ
				  #'2012_X_MC-bg_muon_2504',	# 2504	sT+W
				  #'2012_X_MC-bg_muon_2505',	# 2505	sTbar+W	
				  #'2012_X_MC-bg_muon_2600',	# 2600	sT-sCh
				  #'2012_X_MC-bg_muon_2501',	# 2501	sTbar-sCh
				  #'2012_X_MC-bg_muon_2602',	# 2602	sT-tCh
				  #'2012_X_MC-bg_muon_2503',	# 2503	sTbar-tCh
				  #'2012_X_MC-sig_muon_9115',	# 9115	TTH_115_Fast
				  '2011_X_MC-sig_muon_9120',	# 9120	TTH_120_Fast
				  #'2012_X_MC-sig_muon_9125',	# 9125	TTH_125_Fast
                  VarParsing.VarParsing.multiplicity.singleton,
                  VarParsing.VarParsing.varType.string )
options.maxEvents = maxEvents
options.outputFile = 'NUT.root'
#options.inputFiles = 'file:/store/user/jkolb/TTH_HtoTauTau_M_125_7TeV_FullSim_Pythia6_v2/skimTTHiggsToDiTau_428_v8_TTH_125_FullSim/25a6c8a18b2b0964299388fc37b7979d/ttHiggsToDiTauSkim_100_1_NwK.root'
#options.inputFiles = 'file:/afs/crc.nd.edu/user/n/nvallsve/CMSSW_5_2_5/src/NtupleMaker/BEANmaker/TTbar_summer12_BEAN.root'
#options.inputFiles = '/store/user/lannon/T_s-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1_BEAN_53xOn52x_V01_CV01//74c4602d4f424e29e54ad6a04efd57f1/pat2bean_53x_9_1_1yE.root'
#options.inputFiles = '/store/user/lannon/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/skimDilep_Summer12-PU_S7_START52_V9_53xOn52x_V02_CV01_ttjets_unpublished/skimDilep_ttjets_v2_job011.root'
#options.inputFiles = '/store/user/lwming/TTH_HToAll_M_125_8TeV_FastSim_pythia6/TTH_HToAll_M_125_8TeV_FastSim_pythia6/191b19832235558f2b51f7486e9bfa14/TTH_HToAll_M_125_8TeV_FastSim_v1_117_1_dO5.root'
#options.inputFiles = '/store/user/lannon/MuEG/skimDilep_53xOn52x_V02_CV01_MuEG_Run2012B/a9860641c79dea2455e3b18f5a7c9285/output_10_1_smT.root'
options.inputFiles = '/store/user/lannon/TTH_HToAll_M_110_8TeV_FastSim_pythia6/TTH_Fastsim_BEAN_53xOn52x_V01_CV01//1ffa50b9e8fddadad25e9301b4aa6ffb/pat2bean_53x_12_1_bEw.root'
options.parseArguments() # get and parse the command line arguments 

if options.analysisType.find('muon') == -1 and options.analysisType.find('electron') == -1:
    print 'ERROR: analysisType must contain "muon" or "electron"'
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
    inputForGenParticles = 'BNproducer:MCstatus3:'
    inputForGenJets     = 'BNproducer:ak5GenJets:'
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
#        'Event',
#        'GenLevel',
#        'GenTau',
#        'GenJet',
#        'Tau',
#        'Electron',
#        'Muon',
#        'Jet',
        'DitauMuon',
#        'DitauElectron',
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
        #hltResults = cms.InputTag('TriggerResults::HLT'),
        hltResults = cms.InputTag(''),
        triggerConditions = cms.vstring(triggerConditions),
        l1tResults = '',
        throw = False
)


# === Define and setup main module === #
process.makeNtuple = cms.EDAnalyzer('Ntuplizer',

	# === Analysis setup === #
	DebugLevel							= cms.uint32(debugLevel),
	AnalysisType						= cms.string(options.analysisType),				
	FromBEAN							= cms.bool(True),
    TreeName							= cms.untracked.string('TTbarHTauTau'),

	# === HL Trigger === # (not in use)
    HLTriggerSource		    			= cms.InputTag("BNproducer:HLT"),

	# === Skim Trigger === #
    ApplySkimTriggerRequirements		= cms.bool(True),
    SkimTriggerSource					= cms.InputTag("TriggerResults","","skimTTHiggsToDiTau"),
    SkimTriggerRequirements				= SkimTriggerRequirements,

	# === Which branches to fill? === #
	NtupleFillers						= NtupleFillers,

    # === Input collections === #
    GenParticleSource                   = cms.untracked.InputTag(inputForGenParticles),
    GenJetSource                        = cms.untracked.InputTag(inputForGenJets),
    RecoPATMetSource                    = cms.InputTag('patMETs'+postfix),
    RecoVertexSource                    = cms.InputTag('BNproducer:offlinePrimaryVertices'),
    RecoElectronSource                  = cms.InputTag('BNproducer:selectedPatElectronsPFlow'+postfix),
    RecoMuonSource                      = cms.InputTag('BNproducer:selectedPatMuonsPFlow'+postfix),
    RecoTauSource                       = cms.InputTag('BNproducer:selectedPatTaus'+postfix),
    RecoJetSource                       = cms.InputTag('BNproducer:selectedPatJetsPFlow'+postfix),
    RecoPFMetSource                     = cms.InputTag('BNproducer:patMETsPFlow'+postfix),

    RecoTauMinPt                        = cms.double(tauMinPt),
    RecoTauMaxAbsEta                    = cms.double(tauMaxEta),
    RecoTauRequireDMF                   = cms.bool(True),

	# === Jet stuff === #
    RecoJetMinPt						= cms.double(30.0),
    RecoJetMinAbsEta					= cms.double(0.0),
    RecoJetMaxAbsEta					= cms.double(2.4),
    JetAntiMatchingDeltaR               = cms.double(0.25),
	CSVlooseWP							= cms.double(0.244),
	CSVmediumWP							= cms.double(0.679),
	CSVtightWP							= cms.double(0.898),

	# === === #
)

# === Run sequence === # 
if (options.analysisType.find('data') != -1):
    process.p = cms.Path( process.hltFilter + process.makeNtuple )
    #process.p = cms.Path( process.makeNtuple )
else:
    process.p = cms.Path( process.makeNtuple )

# === Write-out all python configuration parameter information === #
#pythonDump = open("dumpedPython.py", "write"); print >> pythonDump,  process.dumpPython()

