# vim: sta:et:sw=4:ts=4
import FWCore.ParameterSet.Config as cms
import copy
import sys
import inspect

# === Give values to some basic parameters === #
maxEvents	= -1
reportEvery	= 100
debugLevel	= 0
tauMaxEta	= 9
tauMinPt	= 10
baseTreeName = 'TTbarHTauTau'
dataRange   = 'All'
runExtraBEANhelpers = False

# === Parse external arguments === #
import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing("analysis")
# 'jobParams' parameter form: 
# 
# <era>_<subera>_<era release>_<type>_<sample number>_<jet selection>_<lep selection>_<systematic type>
#
# <era>                     = 2011, 2012
# <subera> [N/A for MC]     = A, B, C...
# <type>                    = MC-sigFullSim, MC-sigFastSim, MC-sig, MC-bg, data-PR, data-RR, data-RRr
# <sample number>           = See https://twiki.cern.ch/twiki/bin/view/CMS/TTbarHiggsTauTau#Process_info
# <skim jet selection>      = Sets of four numbers, separated by a "/", and ORed
#                             - 1st is min. num. of total jets
#                             - 2nd is min. num. loose Btags
#                             - 3rd is min. num. med. Btags
#                             - 4th is min. num. tight Btags
# <skim lep selecton>      = Set of four numbers:
#                             - 1st/2nd are min num. "base"/iso taus, as defined in TTHTauTau/Skimming/pluginsBEANskimmer.cc
#                             - 3th is a bitmap for num. of leptons - used to switch the trigger path
#                             - 4th (optional) is the number of extra partons
# <systematic type>         = dash-separated systematic uncertainty shift type(s). 
#                             Options are defined in BEAN/BEANmaker/interface/BEANhelper.h
#                             Must include 'NA'
#
# Examples:
# 2011_X_MC-sig_0_NA
# 2011_B_data-PR_0_JESup-JESdown
# 2012_X_MC-bg_30101_NA
# 2012_B_data-PR_0_NA
options.register(
        'jobParams',
        '2012_X_MC-bg_2523_2110/2200_112_NA',
        VarParsing.VarParsing.multiplicity.singleton,
        VarParsing.VarParsing.varType.string )

options.maxEvents = maxEvents
options.outputFile = 'ntuple{s}.root'

## 7TeV/2011 sample
#options.inputFiles = '/store/user/jkolb/TTH_HtoTauTau_M_125_7TeV_FullSim_Pythia6_v2/skimTTHiggsToDiTau_428_v8_TTH_125_FullSim/25a6c8a18b2b0964299388fc37b7979d/ttHiggsToDiTauSkim_100_1_NwK.root'
#options.inputFiles = '/store/user/jkolb/TTJets_TuneZ2_7TeV-madgraph-tauola/skimTTHiggsToDiTau_428_v8_TTbar_fall11//e8b575bbba85cc8369f2a58b1d9ff532/ttHiggsToDiTauSkim_1504_1_pn7.root'
#options.inputFiles = '/store/user/jkolb/SingleMu/skimTTHiggsToDiTau_428_v8_data_SingleMu_2011A_PRv4/de416a70484169d21ef326580ea52c59/ttHiggsToDiTauSkim_100_1_UgW.root'
## 8TeV/2012 sample
#options.inputFiles = '/store/user/lannon/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/skimDilep_Summer12-PU_S7_START52_V9_53xOn52x_V02_CV01_ttjets_unpublished/skimDilep_ttjets_v2_job011.root'
# 2012B SingleMu - Spring 2013 BEAN
#options.inputFiles = '/store/user/awoodard/SingleMu/BEAN_GTV7G_V01_CV03/2b5bf57d4ab2a303a22b86a50ccffab2/ttH_pat2bean_53x_3185_1_BJl.root'
# ttbar semi-leptonic - Spring2013 BEAN
options.inputFiles = [
        '/store/user/muell149/TTZJets_8TeV-madgraph_v2/chPrj_bean_ca4dc66a977e4c96a421596b5b795aeb/merged_bean_1853.root',
        ]
options.parseArguments() # get and parse the command line arguments 

# === Parse Job Params === #
import shlex
my_splitter = shlex.shlex(options.jobParams, posix=True)
my_splitter.whitespace = '_'
my_splitter.whitespace_split = True
jobParams       = list(my_splitter)

# === Job params error checking === #
if len(jobParams) != 7:
    print "ERROR: jobParams set to '" + options.jobParams + "' must have exactly 7 arguments (check config file for details). Terminating."
    sys.exit(1)

if (jobParams[0] != "2011") and (jobParams[0] != "2012"):
    print "ERROR: era set to '" + jobParams[0] + "' but it must be '2011' or '2012'"
    sys.exit(1)
else:
	era = int(jobParams[0])

runOnMC         = ((jobParams[2]).find('MC') != -1)
runOnSignal		= ((jobParams[2]).find('MC-sig') != -1)
runOnFastSim    = ((jobParams[2]).find('MC-sigFastSim') != -1)
if (not runOnMC) and ((jobParams[1] != 'A') and (jobParams[1] != 'B') and (jobParams[1] != 'C') and (jobParams[1] != 'D')):
    print "ERROR: job set to run on collision data from subera '" + jobParams[1] + "' but it must be 'A', 'B', 'C', or 'D'."
    sys.exit(1)

if (jobParams[2] != "data-PR") and (jobParams[2] != "data-RR") and (jobParams[2] != "data-RRr")and (jobParams[2] != "MC-bg") and (jobParams[2] != "MC-sigFullSim") and (jobParams[2] != "MC-sigFastSim"):
    print "ERROR: sample type set to '" + jobParams[2] + "' but it can only be 'data-PR', 'data-RR', 'data-RRr', 'MC-bg', 'MC-sigFullSim', or 'MC-sigFastSim'."
    sys.exit(1)

sampleNumber    = int(jobParams[3])
if (runOnMC and sampleNumber < 0):
    print "ERROR: job set to run on MC but sample number set to '" + sampleNumber + "' when it must be positive."
    sys.exit(1)

if (not runOnMC and sampleNumber >= 0):
    print "ERROR: job set to run on collision data but sample number set to '" + sampleNumber + "' when it must be negative."
    sys.exit(1)

jet_skim_params = jobParams[4].split("/")
if len(filter(lambda s: len(s) != 4, jet_skim_params)) > 0:
    print "ERROR: all jet skimming parameters must have a lenght of 4!"
    sys.exit(1)

skimParams = jobParams[5]
if len(skimParams) is 0:
    print 'ERROR: unable to determine skim conditions; options.jobParams is set to {0}'.format(options.jobParams)
    sys.exit(1)
if len(skimParams) > 4:
    print 'ERROR: skimParams is set to {0}, but requests for skimParams longer than 4 characters are not supported'.format(skimParams)
    sys.exit(1)

taus = int(skimParams[0])
leptons = int(skimParams[2])
partons = int(skimParams[3]) if len(skimParams) > 3 else -1

sys_splitter = shlex.shlex(jobParams[6], posix=True)
sys_splitter.whitespace = '-'
sys_splitter.whitespace_split = True
sysTypes= list(sys_splitter)

# === Set up triggers and GEN collections based on analysis type === # 

if leptons == 1:
    triggerConditions = ['HLT_IsoMu24_eta2p1', 'HLT_Ele27_WP80']
elif leptons == 2:
    triggerConditions = [
            'HLT_Mu17_Mu8',
            'HLT_Mu17_TkMu8',
            'HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL',
            'HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL',
            'HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL']
else:
    raise "Wrong lepton count!"

UsePfLeptons       = cms.bool(True)
GenParticleSource  = cms.untracked.InputTag('BNproducer:MCstatus3')
GenJetSource       = cms.untracked.InputTag('BNproducer:ak5GenJets')
TriggerSource      = cms.InputTag('BNproducer:HLT')
RecoVertexSource   = cms.InputTag('BNproducer:offlinePrimaryVertices')
RecoElectronSource = cms.InputTag('BNproducer:selectedPatElectrons')
RecoMuonSource     = cms.InputTag('BNproducer:selectedPatMuons')
RecoTauSource      = cms.InputTag('BNproducer:selectedPatTaus')
RecoJetSource      = cms.InputTag('BNproducer:selectedPatJets')
RecoPFMetSource    = cms.InputTag('BNproducer:patMETs')

# === make analysis-specific selections for skims, fillers, etc. === #
SkimTriggerRequirements	= cms.vstring()

use_veto = True
if leptons == 1:
    is_dil = False
    if taus == 1:
        use_veto = False
    elif taus != 2:
        raise
elif leptons == 2:
    is_dil = True
    if taus == 0:
        use_veto = False
    elif taus != 1:
        raise
else:
    raise

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

# === Conditions === #
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
from ttH.TauAnalysis.globalTagMap_cfi import get_tag
globalTag = get_tag(options.jobParams.rsplit('_', 4)[0]) + '::All'
process.GlobalTag.globaltag = cms.string(globalTag)

# === Collision data trigger requirements === #
import HLTrigger.HLTfilters.triggerResultsFilter_cfi as hlt
process.hltFilter = hlt.triggerResultsFilter.clone(
        hltResults = TriggerSource,
        triggerConditions = cms.vstring(triggerConditions),
        l1tResults = '',
        throw = False)
if era == 2012:
  process.hltFilter = cms.EDFilter("BEANhltFilter",
      HLTacceptPaths = cms.vstring(triggerConditions),
      debug = cms.bool(False)
  )

# === Skim === #
process.beanSkimmer = cms.EDFilter("BEANskimmer",
    jetConfig = cms.untracked.vstring(jet_skim_params),
    lepConfig = cms.untracked.string(skimParams),
    tauSrc = RecoTauSource,
    jetSrc = RecoJetSource,
    genSrc = GenParticleSource,
    sample = cms.untracked.int32(sampleNumber),
    dilepton = cms.untracked.bool(is_dil),
    partons = cms.untracked.int32(partons)
)

# === Define and setup main module === #
process.makeNtuple = cms.EDAnalyzer('Ntuplizer',
    requiredLeptons = cms.uint32(leptons),
    requiredTaus = cms.uint32(taus),

	# === Analysis setup === #
	DebugLevel							= cms.uint32(debugLevel),
    AnalysisParameters = cms.vstring(jobParams),
	EraRelease							= cms.string('53x'),				
    TreeName							= cms.untracked.string(baseTreeName),
    UsePfLeptons                        = UsePfLeptons,
    DataRange                           = cms.string(dataRange),
    RunExtraBEANhelpers                 = cms.bool(runExtraBEANhelpers),
    isDilepton = cms.bool(is_dil),
    useEventVeto = cms.bool(use_veto),

	# === HL Trigger === # (not in use)
    #HLTriggerSource		    			= cms.InputTag("TriggerResults::HLT"),
    HLTriggerSource		    			= TriggerSource,

	# === Skim Trigger === #
    ApplySkimTriggerRequirements		= cms.bool(False),
    SkimTriggerSource					= cms.InputTag("TriggerResults::"),
    SkimTriggerRequirements				= SkimTriggerRequirements,

    # === Input collections === #
    GenParticleSource                   = GenParticleSource,
    GenJetSource                        = GenJetSource,
    RecoVertexSource                    = RecoVertexSource,
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
    #CSVlooseWP							= cms.double(0.244),
    #CSVmediumWP							= cms.double(0.679),
    #CSVtightWP							= cms.double(0.898)

	# === Systematics stuff === #
    SysType                             = cms.untracked.string('NA'),

    # output file: name depends on systematics used
    outputFileName = cms.string(options.outputFile.format(s="")),
)
process.makeNtupleSeq = cms.Sequence(process.makeNtuple)

# add modules for systematic shifts
for unc in sysTypes:
    if unc == 'NA':
        continue
    mod = copy.deepcopy(process.makeNtuple)
    mod.SysType = unc
    # For historical reasons, case is inconsistent.  This removes some code
    # downstream dealing with inconsistent case.
    unc = unc.replace("up", "Up").replace("down", "Down")
    mod.outputFileName = cms.string(options.outputFile.format(s="_" + unc))
    setattr(process,'makeNtuple_'+unc,mod)
    process.makeNtupleSeq += mod

# === Run sequence === #
if not runOnMC:
    process.p = cms.Path( process.beanSkimmer + process.hltFilter + process.makeNtupleSeq )
else:
    process.p = cms.Path( process.beanSkimmer + process.hltFilter + process.makeNtupleSeq )


# === Print some basic info about the job setup === #
print """
        ====================================================
            Ntuple Making Job
        ====================================================

            Analysis type....{0}
            Running on PAT?..{1}
            Max events.......{2}
            Report every.....{3}
            Global tag.......{4}
            Tau event veto...{8}
            Triggers.........{5}
            Skim parameters..{6}
            Jet parameters...{9}
            Systematics......{7}

        ====================================================
""".format(
        options.jobParams,
        era == 2011,
        options.maxEvents,
        reportEvery,
        globalTag,
        ', '.join(triggerConditions),
        skimParams,
        ', '.join(sysTypes),
        use_veto,
        jet_skim_params)

# === Write-out all python configuration parameter information === #
#pythonDump = open("dumpedPython.py", "write"); print >> pythonDump,  process.dumpPython()

