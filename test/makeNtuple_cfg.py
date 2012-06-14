import FWCore.ParameterSet.Config as cms
import copy
import sys


# === Give values to some basic parameters === #
maxEvents	= 100
reportEvery	= 100
tauMaxEta	= 9
tauMinPt	= 0


# === Parse external arguments === #
import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing("analysis")
options.register("analysisType",
       #"coll",		# default value
       #"mc",		# default value
       "signal",	# default value
       VarParsing.VarParsing.multiplicity.singleton, # singleton or list
       VarParsing.VarParsing.varType.string,         # string, int, or float
       "is MC or is Data?"
       )   
options.parseArguments() # get and parse the command line arguments (or from Xcrab.cfg)
if( options.analysisType == "signal" ):
	isMC			= True
	isSignal		= True
	doMatching		= True
elif( options.analysisType=="mc" ):
	isMC			= True
	isSignal		= False
	doMatching		= False
elif( options.analysisType=="coll" ):
	isMC			= False
	isSignal		= False
	doMatching		= False
else:
	sys.exit("Analysis type not understood")	


# === Print some basic info about the job setup === #
print ''
print '	========================================='
print '		Ntuple Making Job'
print '	========================================='
print ''
print '		Analysis type...%s' % options.analysisType
print '		Max events......%d' % maxEvents
print '		Report every....%d' % reportEvery
print ''
print '		Is MC...........%d' % isMC
print '		Is signal.......%d' % isSignal
print '		Max tau |eta|...%d' % tauMaxEta
print '		Min tau pT......%d' % tauMinPt
print ''
print '	========================================='
print ''


# === Set up genparticles collection based on analysis type === #
if( isMC == 1 ): 
    inputForGenParticles = 'genParticles'
else:
    inputForGenParticles = ''


# === Python process === #
process = cms.Process('TTbarHTauTau')


# === Load and set up basic services === #
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = reportEvery
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( maxEvents ) )
process.source = cms.Source("PoolSource",
    skipEvents = cms.untracked.uint32(0),
    fileNames = cms.untracked.vstring(
		'file:/afs/crc.nd.edu/user/j/jkolb/Public/ForNil/ttHiggsToDiTauSkim.root'
    )
)
process.TFileService = cms.Service("TFileService", fileName = cms.string("ttbarHTauTau_nTuple.root") )


# === Define and setup main module === #
process.makeNtuple = cms.EDAnalyzer('Ntuplizer',

	# === Analysis setup === #
	AnalysisType						= cms.string(options.analysisType),					# Type of analysis, i.e. sample (coll, mc, signal)
    TreeName							= cms.untracked.string('TTbarHTauTau'),

	# === Skim Trigger === #
    ApplySkimTriggerRequirements		= cms.bool(True),
    SkimTriggerSource					= cms.InputTag("TriggerResults","","skimTTHiggsToDiTau"),
    SkimTriggerRequirements				= cms.vstring(
													#	'ttHiggsElectronSkim',
													#	'ttHiggsMuonSkim',
													#	'ttElectronHiggsToElecTauSkim',
													#	'ttMuonHiggsToElecTauSkim',
													#	'ttElectronHiggsToMuTauSkim',
														'ttMuonHiggsToMuTauSkim',
													#	'ttElectronHiggsToTauTauSkim',
													#	'ttMuonHiggsToTauTauSkim',
														),

	# === Trigger === #
    ApplyTriggerRequirements			= cms.bool(True),
    TriggerSource						= cms.InputTag("TriggerResults","","HLT"),
    TriggerRequirements					= cms.vstring(
														'HLT_IsoMu30_v1',
														),

	# === Which branches to fill? === #
	NtupleFillers						= cms.untracked.vstring(
																'Event',
																'GenLevel',
																'Tau',
																'Electron',
																'Muon',
																'Jet',
																'Ditau',
																'DitauElectron',
																'DitauMuon',
																),

	# === Input collections === #
    GenParticleSource					= cms.untracked.InputTag(inputForGenParticles),
    RecoTauSource						= cms.InputTag('selectedPatTaus'),
    RecoMuonSource						= cms.InputTag('selectedPatMuons'),
    RecoElectronSource					= cms.InputTag('selectedPatElectrons'),
    RecoJetSource                       = cms.InputTag('selectedPatJets::skimTTHiggsToDiTau'),
    RecoVertexSource					= cms.InputTag('offlinePrimaryVertices'),
    RecoPATMetSource					= cms.InputTag('patMETs'),
    RecoPFMetSource						= cms.InputTag('patMETs'),

	# === Jet stuff === #
    RecoJetMinEt						= cms.double(10.0),
    RecoJetMinAbsEta					= cms.double(0.0),
    RecoJetMaxAbsEta					= cms.double(2.5),
    JetAntiMatchingDeltaR               = cms.double(0.25),
	CSVlooseWP							= cms.double(0.244),
	CSVmediumWP							= cms.double(0.679),
	CSVtightWP							= cms.double(0.898),

	# === === #
)


# === Run sequence === #
process.p = cms.Path( process.makeNtuple )


# === Print-out all python configuration parameter information === #
#print process.dumpPython()


# === Write-out all python configuration parameter information === #
#pythonDump = open("dumpedPython.py", "write")
#print >> pythonDump,  process.dumpPython()

