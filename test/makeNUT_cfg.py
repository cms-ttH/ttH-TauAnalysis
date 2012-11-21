import FWCore.ParameterSet.Config as cms
import copy
import sys
import inspect


# === Terminates execution === #
def throwFatalError():
    print "ERROR in line %d" % (inspect.currentframe().f_back.f_lineno); sys.exit(1);


# === Give values to some basic parameters === #
maxEvents	= -1
reportEvery	= 100
debugLevel	= 0
tauMaxEta	= 9
tauMinPt	= 0

# collection postfix for running on PF2APT
postfix = ''
# postfix = 'PFlow'

# === Parse external arguments === #
import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing("analysis")
# 'jobParams' parameter form: 
# 
# <era>_<subera>_<type>_<lepton flavor>_<sample number>
#
# <era>					= 2011, 2012
# <subera> [N/A for MC]	= A, B, C...
# <type>				= MC-sigFullSim, MC-sigFastSim, MC-sig, MC-bg, data-PR, data-RR, data-RRr
# <lepton flavor>		= muon, electron
# <sample number>		= See https://twiki.cern.ch/twiki/bin/view/CMS/TTbarHiggsTauTau#Process_info
#
# Examples:
# 2011_X_MC-sig_muon
# 2011_B_data-PR_electron
# 2012_X_MC-bg_electron
# 2012_B_data-PR_muon
options.register ('jobParams', # 
                  '2011_X_MC-sigFullSim_muon_125',	    # 125   tth->tautau
				  #'2012_X_MC-bg_muon_-1',	    # -1	2012A collisions
				  #'2012_X_MC-bg_muon_-11',	    # -11	2012B collisions
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
				  #'2012_X_MC-bg_muon_9115',	# 9115	TTH_115_Fast
				  #'2012_X_MC-bg_muon_9120',	# 9120	TTH_120_Fast
				  #'2012_X_MC-bg_muon_9125',	# 9125	TTH_125_Fast
                  VarParsing.VarParsing.multiplicity.singleton,
                  VarParsing.VarParsing.varType.string )

options.maxEvents = maxEvents
options.outputFile = 'NUT.root'

## 7TeV/2011 sample
options.inputFiles = '/store/user/jkolb/TTH_HtoTauTau_M_125_7TeV_FullSim_Pythia6_v2/skimTTHiggsToDiTau_428_v8_TTH_125_FullSim/25a6c8a18b2b0964299388fc37b7979d/ttHiggsToDiTauSkim_100_1_NwK.root'
## 8TeV/2012 sample
#options.inputFiles = '/store/user/lannon/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/skimDilep_Summer12-PU_S7_START52_V9_53xOn52x_V02_CV01_ttjets_unpublished/skimDilep_ttjets_v2_job011.root'

options.parseArguments() # get and parse the command line arguments 

# === Parse Job Params === #
import shlex;
my_splitter = shlex.shlex(options.jobParams, posix=True);
my_splitter.whitespace = '_'; 
my_splitter.whitespace_split = True;
jobParams       = list(my_splitter);


# === Job params error checking === #
if len(jobParams) != 5:
    print "ERROR: jobParams set to '" + options.jobParams + "' must have exactly 5 arguments (check config file for details). Terminating."; sys.exit(1);

if (jobParams[0] != "2011") and (jobParams[0] != "2012"):
    print "ERROR: era set to '" + jobParams[0] + "' but it must be '2011' or '2012'"; sys.exit(1);
else:
	era = int(jobParams[0]);

runOnMC         = ((jobParams[2]).find('MC') != -1); 
runOnSignal		= ((jobParams[2]).find('MC-sig') != -1); 
runOnFastSim    = ((jobParams[2]).find('MC-sigFastSim') != -1); 
if (not runOnMC) and ((jobParams[1] != 'A') and (jobParams[1] != 'B') and (jobParams[1] != 'C')):
    print "ERROR: job set to run on collision data from subera '" + jobParams[1] + "' but it must be 'A', 'B', or 'C'."; sys.exit(1);

if (jobParams[2] != "data-PR") and (jobParams[2] != "data-RR") and (jobParams[2] != "data-RRr")and (jobParams[2] != "MC-bg") and (jobParams[2] != "MC-sigFullSim") and (jobParams[2] != "MC-sigFastSim"):
    print "ERROR: sample type set to '" + jobParams[2] + "' but it can only be 'data-PR', 'data-RR', 'data-RRr', 'MC-bg', 'MC-sigFullSim', or 'MC-sigFastSim'."; sys.exit(1); 

if (jobParams[3] != "electron") and (jobParams[3] != "muon"):
    print "ERROR: skim type set to '" + jobParams[3] + "' but it must be either 'electron' or 'muon'."; exit(1);
else:
	skimType = jobParams[3];

sampleNumber    = int(jobParams[4]);
if (runOnMC and sampleNumber < 0):
    print "ERROR: job set to run on MC but sample number set to '" + sampleNumber + "' when it must be positive."; sys.exit(1);

if (not runOnMC and sampleNumber >= 0):
    print "ERROR: job set to run on collision data but sample number set to '" + sampleNumber + "' when it must be negative."; sys.exit(1);



# === Set up triggers and GEN collections based on analysis type === # 
if runOnMC:
    inputForGenParticles = 'genParticles'
    inputForGenJets     = 'selectedPatJets:genJets:'
    triggerConditions = (
        'HLT_IsoMu24_v*',
        'HLT_IsoMu24_eta2p1_v*'
    )
    if (skimType == 'electron'):
        triggerConditions = (
            'HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30_v*',
            'HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30_v*',
            'HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30_v*'
        )

if (not runOnMC):
    inputForGenParticles = ''
    inputForGenJets         = ''
    triggerConditions = (
        'HLT_IsoMu24_v*',
        'HLT_IsoMu24_eta2p1_v*'
    )
    if (skimType == 'electron'):
        triggerConditions = (
            'HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30_v*',
            'HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30_v*',
            'HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30_v*'
        )


# === Define Ntuplizer input collections === # 
## For 7TeV/2011 datasets, where we read PATuples
GenParticleSource                   = cms.untracked.InputTag((inputForGenParticles))
GenJetSource                        = cms.untracked.InputTag((inputForGenJets))
TriggerSource						= cms.InputTag('TriggerResults::HLT')
RecoVertexSource                    = cms.InputTag('offlinePrimaryVertices')
RecoPATMetSource                    = cms.InputTag('patMETs'+postfix)
RecoPFMetSource                     = cms.InputTag('patMETs'+postfix)
RecoElectronSource                  = cms.InputTag('selectedPatElectrons'+postfix)
RecoMuonSource                      = cms.InputTag('selectedPatMuons'+postfix)
RecoTauSource                       = cms.InputTag('selectedPatTaus'+postfix)
RecoJetSource                       = cms.InputTag('selectedPatJets'+postfix+'::skimTTHiggsToDiTau')
UsePfLeptons                        = cms.bool(False)
### For 8TeV/2012 datasets, where we read BEANs
if( era == 2012 ):
    UsePfLeptons                        = cms.bool(True)
    GenParticleSource                   = cms.untracked.InputTag('BNproducer:MCstatus3')
    GenJetSource                        = cms.untracked.InputTag('BNproducer:ak5GenJets')
    TriggerSource						= cms.InputTag('BNproducer:HLT')
    RecoVertexSource                    = cms.InputTag('BNproducer:offlinePrimaryVertices')
    RecoElectronSource                  = cms.InputTag('BNproducer:selectedPatElectronsPFlow'+postfix)
    RecoMuonSource                      = cms.InputTag('BNproducer:selectedPatMuonsPFlow'+postfix)
    RecoTauSource                       = cms.InputTag('BNproducer:selectedPatTaus'+postfix)
    RecoJetSource                       = cms.InputTag('BNproducer:selectedPatJetsPFlow'+postfix)
    RecoPFMetSource                     = cms.InputTag('BNproducer:patMETsPFlow'+postfix)


# === make analysis-specific selections for skims, fillers, etc. === #
SkimTriggerRequirements	= cms.vstring()

if (skimType == 'electron'):
	if (runOnSignal):
		SkimTriggerRequirements = cms.vstring('ttElectronHiggsToTauTauSkim')
	elif (runOnMC and (not runOnSignal)):
		SkimTriggerRequirements = cms.vstring('ttHiggsElectronSkim')
	elif (not runOnMC):
		SkimTriggerRequirements = cms.vstring('ttHiggsElectronSkim')
	else:
		throwFatalError();
elif (skimType == 'muon'):
	if (runOnSignal):
		SkimTriggerRequirements = cms.vstring('ttMuonHiggsToTauTauSkim')
	elif (runOnMC and (not runOnSignal)):
		SkimTriggerRequirements = cms.vstring('ttHiggsMuonSkim')
	elif (not runOnMC):
		SkimTriggerRequirements = cms.vstring('ttHiggsMuonSkim')
	else:
		throwFatalError();
else:
	throwFatalError();


NtupleFillers = cms.untracked.vstring(
        'Event',
        'GenLevel',
        'GenTau',
        'GenJet',
        'Tau',
        'Electron',
        'Muon',
        'Jet',
        #'DitauMuon',
        #'DitauElectron',
        #'Trigger' # not in use
)
if(skimType == 'muon'):
	NtupleFillers.append('DitauMuon')
elif(skimType == 'electron'):
	NtupleFillers.append('DitauElectron')
else:
	throwFatalError();


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


# === Conditions === #
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
from TTHTauTau.Analysis.globalTagMap_cfi import globalTagMap
globalTag = globalTagMap[options.jobParams.rsplit('_',2)[0]] + '::All'
process.GlobalTag.globaltag = cms.string(globalTag)


# === Collision data trigger requirements === #
import HLTrigger.HLTfilters.triggerResultsFilter_cfi as hlt
process.hltFilter = hlt.triggerResultsFilter.clone(
        hltResults = cms.InputTag('TriggerResults::HLT'),
        triggerConditions = cms.vstring(triggerConditions),
        l1tResults = '',
        throw = False)


# === Define and setup main module === #
process.makeNtuple = cms.EDAnalyzer('Ntuplizer',

	# === Analysis setup === #
	DebugLevel							= cms.uint32(debugLevel),
	AnalysisType						= cms.string(options.jobParams),				
	FromBEAN							= cms.bool(era == 2012),
    TreeName							= cms.untracked.string('TTbarHTauTau'),
    UsePfLeptons                        = UsePfLeptons,

	# === HL Trigger === # (not in use)
    #HLTriggerSource		    			= cms.InputTag("TriggerResults::HLT"),
    HLTriggerSource		    			= TriggerSource,

	# === Skim Trigger === #
    ApplySkimTriggerRequirements		= cms.bool(False),
    SkimTriggerSource					= cms.InputTag("TriggerResults::"),
    SkimTriggerRequirements				= SkimTriggerRequirements,

	# === Which branches to fill? === #
	NtupleFillers						= NtupleFillers,

    # === Input collections === #
    GenParticleSource                   = GenParticleSource,
    GenJetSource                        = GenJetSource,
    RecoVertexSource                    = RecoVertexSource,
    RecoPATMetSource                    = RecoPATMetSource,
    RecoPFMetSource                     = RecoPFMetSource,
    RecoElectronSource                  = RecoElectronSource,
    RecoMuonSource                      = RecoMuonSource,
    RecoTauSource                       = RecoTauSource,
    RecoJetSource                       = RecoJetSource,

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
	CSVtightWP							= cms.double(0.898)

	# === === #
)

# === Run sequence === # 
if(not runOnMC):
    process.p = cms.Path( process.hltFilter + process.makeNtuple )
else:
    process.p = cms.Path( process.makeNtuple )


# === Print some basic info about the job setup === #
print ''
print '	===================================================='
print '		Ntuple Making Job'
print '	===================================================='
print ''
print '		Analysis type....%s' % options.jobParams
print '		Running on PAT?..%s' % (era == 2011)
print '		Max events.......%d' % options.maxEvents
print '		Report every.....%d' % reportEvery
print '		Global tag.......%s' % globalTag
print ''
print '	===================================================='
print ''

# === Write-out all python configuration parameter information === #
#pythonDump = open("dumpedPython.py", "write"); print >> pythonDump,  process.dumpPython()

