# vim: sta:et:sw=4:ts=4
import FWCore.ParameterSet.Config as cms
import copy
import sys
import inspect

# === Give values to some basic parameters === #
maxEvents	= -1
reportEvery	= 100
era_release	= '53x' # '52x' (2012 ICHEP), '53x' (2012 full), 'NA' (2011 *)
debugLevel	= 0
tauMaxEta	= 9
tauMinPt	= 10
baseTreeName = 'TTbarHTauTau'
dataRange   = 'All'
runExtraBEANhelpers = True

# collection postfix for running on PF2PAT
postfix = ''
#postfix = 'PFlow'

# === Parse external arguments === #
import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing("analysis")
# 'jobParams' parameter form: 
# 
# <era>_<subera>_<era release>_<type>_<sample number>_<skim selection>_<systematic type>
#
# <era>                     = 2011, 2012
# <subera> [N/A for MC]     = A, B, C...
# <type>                    = MC-sigFullSim, MC-sigFastSim, MC-sig, MC-bg, data-PR, data-RR, data-RRr
# <sample number>           = See https://twiki.cern.ch/twiki/bin/view/CMS/TTbarHiggsTauTau#Process_info
# <skim selection>          = up to six numbers;
#                             - 1st is min. num. of total jets
#                             - 2nd is min. num. loose Btags
#                             - 3rd is min. num. med. Btags
#                             - 4th is min. num. tight Btags
#                             - 5th/6th are min num. "base"/iso taus, as defined in TTHTauTau/Skimming/pluginsBEANskimmer.cc
#                             - 7th is a bitmap for num. of leptons - used to switch the trigger path
#                             - 8th (optional) is the number of extra partons
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
        '2012_X_MC-sigFullSim_7125_0000101_JESup-JESdown-TESup-TESdown',
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
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_10_1_cDq.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_11_1_d1B.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_1_1_wbT.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_12_1_tvt.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_13_1_pGV.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_14_1_ZLL.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_15_1_gfw.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_16_1_Nrh.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_17_1_kDm.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_18_1_iq6.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_19_1_du0.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_20_1_ucc.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_21_1_eAB.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_2_1_yyk.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_22_1_VmK.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_23_1_qYx.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_24_1_FI1.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_25_1_fxB.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_26_1_8R9.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_27_1_oiT.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_28_1_H2O.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_29_1_F0P.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_30_1_sGc.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_31_1_PpF.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_3_1_afc.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_32_1_POe.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_33_1_ZZ9.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_34_1_Fxl.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_35_1_bcD.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_36_1_Xw4.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_37_1_n3k.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_38_1_Zq3.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_39_1_nng.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_40_1_QTp.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_41_1_aBY.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_4_1_rKk.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_42_1_XWF.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_43_1_D6A.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_44_1_1Ev.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_45_1_8OZ.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_46_1_Cue.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_47_1_1gM.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_48_1_cEu.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_49_1_tt9.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_50_1_4jC.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_51_1_fBK.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_5_1_hDn.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_6_1_sKU.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_7_1_kcC.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_8_1_Q6V.root',
        '/store/user/jkolb/TTH_HToTauTau_M-125_8TeV_pythia6/skimBEAN_Spring13_GTV7G_538_s1/4782b5a765d5e36ded22d6cd134b70b4/BEAN_9_1_vwH.root',
        ]
options.parseArguments() # get and parse the command line arguments 

# === Parse Job Params === #
import shlex
my_splitter = shlex.shlex(options.jobParams, posix=True)
my_splitter.whitespace = '_'
my_splitter.whitespace_split = True
jobParams       = list(my_splitter)

# === Job params error checking === #
if len(jobParams) != 6:
    print "ERROR: jobParams set to '" + options.jobParams + "' must have exactly 6 arguments (check config file for details). Terminating."
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

if (era == 2011):
	era_release = 'NA'
if (era == 2012) and ((era_release != '52x') and (era_release != '53x')):
    print "ERROR: era set to 2012 and era release set to '" + era_release + "' but it must be '52x' (2012 ICHEP) or '53x' (full 2012)."
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

skimParams = jobParams[4]
if len(skimParams) is 0:
    print 'ERROR: unable to determine skim conditions; options.jobParams is set to {0}'.format(options.jobParams)
    sys.exit(1)
if len(skimParams) > 8:
    print 'ERROR: skimParams is set to {0}, but requests for skimParams longer than 7 characters are not supported'.format(skimParams)
    sys.exit(1)

taus = int(skimParams[4])
leptons = int(skimParams[6])
partons = int(skimParams[7]) if len(skimParams) > 7 else -1

sys_splitter = shlex.shlex(jobParams[5], posix=True)
sys_splitter.whitespace = '-'
sys_splitter.whitespace_split = True
sysTypes= list(sys_splitter)

# === Set up triggers and GEN collections based on analysis type === # 
if runOnMC:
    inputForGenParticles = 'genParticles'
    inputForGenJets     = 'selectedPatJets:genJets:'
else:
    inputForGenParticles = ''
    inputForGenJets = ''

triggerConditions = []
if era == 2011:
    triggerConditions += [
            'HLT_IsoMu24_v*',
            'HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30_v*',
            'HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30_v*',
            'HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30_v*'
            ]
else:
    if leptons == 1:
        triggerConditions += ['HLT_IsoMu24_eta2p1', 'HLT_Ele27_WP80']
    elif leptons == 2:
        triggerConditions += [
                'HLT_Mu17_Mu8',
                'HLT_Mu17_TkMu8',
                'HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL',
                'HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL',
                'HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL']
    else:
        raise "Wrong lepton count!"

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
    RecoElectronSource                  = cms.InputTag('BNproducer:selectedPatElectronsPFlow')
    RecoMuonSource                      = cms.InputTag('BNproducer:selectedPatMuonsPFlow')
    RecoTauSource                       = cms.InputTag('BNproducer:selectedPatTaus'+postfix)
    RecoJetSource                       = cms.InputTag('BNproducer:selectedPatJetsPFlow')
    RecoPFMetSource                     = cms.InputTag('BNproducer:patMETsPFlow')


# === make analysis-specific selections for skims, fillers, etc. === #
SkimTriggerRequirements	= cms.vstring()


NtupleFillers = cms.untracked.vstring(
        'Event',
        'Vertex',
        #'GenLevel',
        'GenTau',
        'GenJet',
        'Tau',
        'Electron',
        'Muon',
        'Jet',
        #'DitauMuon',
        #'DitauElectron',
        #'Trigger', # not in use
        'Test',
)

if leptons == 1:
    is_dil = False
    if taus == 2:
        NtupleFillers.append('DitauLepton')
    elif taus == 1:
        NtupleFillers.append('TauLepton')
    else:
        raise
elif leptons == 2:
    is_dil = True
    NtupleFillers.append('TauLeptonLepton')
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
globalTag = get_tag(options.jobParams.rsplit('_',3)[0]) + '::All'
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
    config = cms.untracked.string(skimParams),
    tauSrc = RecoTauSource,
    jetSrc = RecoJetSource,
    genSrc = GenParticleSource,
    sample = cms.untracked.int32(sampleNumber),
    dilepton = cms.untracked.bool(is_dil),
    partons = cms.untracked.int32(partons)
)

# === Define and setup main module === #
process.makeNtuple = cms.EDAnalyzer('Ntuplizer',

	# === Analysis setup === #
	DebugLevel							= cms.uint32(debugLevel),
	AnalysisType						= cms.string(options.jobParams),				
	EraRelease							= cms.string(era_release),				
	FromBEAN							= cms.bool(era == 2012),
    TreeName							= cms.untracked.string(baseTreeName),
    UsePfLeptons                        = UsePfLeptons,
    DataRange                           = cms.string(dataRange),
    RunExtraBEANhelpers                 = cms.bool(runExtraBEANhelpers),
    isDilepton = cms.bool(is_dil),
    useEventVeto = cms.bool(True),

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
            Era Release......{2}
            Max events.......{3}
            Report every.....{4}
            Global tag.......{5}
            Triggers.........{6}
            Skim parameters..{7}
            Systematics......{8}
            Fillers..........{9}

        ====================================================
""".format(
        options.jobParams,
        era == 2011,
        era_release,
        options.maxEvents,
        reportEvery,
        globalTag,
        ', '.join(triggerConditions),
        skimParams,
        ', '.join(sysTypes),
        ', '.join(NtupleFillers))

# === Write-out all python configuration parameter information === #
#pythonDump = open("dumpedPython.py", "write"); print >> pythonDump,  process.dumpPython()

