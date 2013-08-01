import FWCore.ParameterSet.Config as cms
import copy
import sys
import inspect


# === Terminates execution === #
def throwFatalError():
    print "ERROR in line %d" % (inspect.currentframe().f_back.f_lineno); sys.exit(1);


# === Give values to some basic parameters === #
maxEvents	= -1
reportEvery	= 10000
era_release	= '53x' # '52x' (2012 ICHEP), '53x' (2012 full), 'NA' (2011 *)
debugLevel	= 0
# name for tau collection
postfix = ''

# === Parse external arguments === #
import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing("analysis")
options.register ('skimParams', # 
                  '111021',
                  VarParsing.VarParsing.multiplicity.singleton,
                  VarParsing.VarParsing.varType.string )

options.maxEvents = maxEvents
options.outputFile = 'BEAN.root'

## 8TeV/2012 sample - Fall12/HCP BEAN
#options.inputFiles = '/store/user/lannon/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/skimDilep_Summer12-PU_S7_START52_V9_53xOn52x_V02_CV01_ttjets_unpublished/skimDilep_ttjets_v2_job011.root'
# 2012B SingleMu - Spring 2013 BEAN
#options.inputFiles = '/store/user/awoodard/SingleMu/BEAN_GTV7G_V01_CV03/2b5bf57d4ab2a303a22b86a50ccffab2/ttH_pat2bean_53x_3185_1_BJl.root'
# ttbar semi-leptonic - Spring2013 BEAN
options.inputFiles = '/store/user/awoodard/TTJets_SemiLeptMGDecays_8TeV-madgraph/TTJets_SemiLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1_BEAN_GTV7G_V01_CV02/d0a71c5bb6f6754a25e53f49b1990e4b/ttH_pat2bean_53x_2222_1_nqg.root'
options.parseArguments() # get and parse the command line arguments 

skimParams = options.skimParams
if len(skimParams) is 0:
    print 'ERROR: unable to determine skim conditions; options.jobParams is set to {0}'.format(options.jobParams); sys.exit(1)
if len(skimParams) > 6:
    print 'ERROR: skimParams is set to {0}, but requests for skimParams longer than 6 characters are not supported'.format(skimParams); sys.exit(1)

# === Collections === #

RecoTauSource = cms.InputTag('BNproducer:selectedPatTaus'+postfix)
RecoJetSource = cms.InputTag('BNproducer:selectedPatJetsPFlow')


# === Python process === #
process = cms.Process('skimBEAN')


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

# === Output module === #
process.out = cms.OutputModule("PoolOutputModule",
        fileName = cms.untracked.string(options.outputFile),
        SelectEvents = cms.untracked.PSet(
            SelectEvents = cms.vstring('skimPath')
        ),
        dropMetaData = cms.untracked.string('ALL'),
        outputCommands = cms.untracked.vstring('drop *',
            'keep *_BNproducer_*_*',
            'keep double_kt6PFJets*_rho_*')
)


process.TFileService = cms.Service("TFileService", fileName = cms.string(options.outputFile) )


# === Conditions === #
#process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
#from ttH.TauAnalysis.globalTagMap_cfi import globalTagMap
#globalTag = globalTagMap[options.jobParams.rsplit('_',3)[0]] + '::All'
#process.GlobalTag.globaltag = cms.string(globalTag)

# === Skim === #
process.beanSkimmer = cms.EDFilter("BEANskimmer",
    config = cms.untracked.string(skimParams),
    tauSrc = RecoTauSource,
    jetSrc = RecoJetSource
)


# === Run sequence === # 
process.skimPath = cms.Path( process.beanSkimmer )

# === EndPath === # 
process.endpath = cms.EndPath(process.out)

# === Print some basic info about the job setup === #
print ''
print '	===================================================='
print '		Ntuple Making Job'
print '	===================================================='
print ''
print '		Max events.......%d' % options.maxEvents
print '		Report every.....%d' % reportEvery
#print '		Global tag.......%s' % globalTag
print '		Skim parameters..%s' % skimParams
print ''
print '	===================================================='
print ''

# === Write-out all python configuration parameter information === #
#pythonDump = open("dumpedPython.py", "write"); print >> pythonDump,  process.dumpPython()

