// vim: et:sta:sw=4:ts=4
// Author: Nil Valls <nvallsve@nd.edu>

#include "boost/lexical_cast.hpp"

#include "..//interface/Ntuplizer.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
Ntuplizer::Ntuplizer(const ParameterSet& config) :
    _filename(config.getParameter<string>("outputFileName"))
{
	// Necessary to propagate config 
	jobConfig						= new ParameterSet(config);

	// Analysis type
	_DebugLevel						= config.getParameter<unsigned int>("DebugLevel");
	_FromBEAN						= config.getParameter<bool>("FromBEAN");
	_AnalysisType					= config.getParameter<string>("AnalysisType");
	_EraRelease						= config.getParameter<string>("EraRelease");
    _UsePfLeptons                   = ( config.exists("UsePfLeptons") ) ? config.getParameter<bool>("UsePfLeptons") : true;
    _DataRange                      = ( config.exists("DataRange") ) ? config.getParameter<string>("DataRange") : "All";
    _RunExtraBEANhelpers            = ( config.exists("RunExtraBEANhelpers") ) ? config.getParameter<bool>("RunExtraBEANhelpers") : false;

	// Fillers to use
	_enabledFillers					= config.getUntrackedParameter<std::vector<std::string> >("NtupleFillers");

	// Skim trigger
	_ApplySkimTriggerRequirements	= config.getParameter<bool>("ApplySkimTriggerRequirements");
	_SkimTriggerSource				= config.getParameter<InputTag>("SkimTriggerSource");
	_SkimTriggerRequirements		= config.getParameter<vector<string> >("SkimTriggerRequirements");
    
    // required for TTL event check
    _RecoTauSource                  = config.getParameter<InputTag>("RecoTauSource");
    _RecoMuonSource                 = config.getParameter<InputTag>("RecoMuonSource");
    _RecoElectronSource             = config.getParameter<InputTag>("RecoElectronSource");
    _RecoJetSource                  = config.getParameter<InputTag>("RecoJetSource");

    // required for TTL event check
    _num_leptons = boost::lexical_cast<int>(GetAnalysisTypeParameter(4)[6]);

    _an_type = config.getParameter<bool>("isDilepton") ? analysisType::TauDIL : analysisType::TauLJ;

    std::string sysTypeString       = config.getUntrackedParameter<std::string>("SysType");
    _sysType = sysType::NA;
    if( sysTypeString.compare("NA") == 0 ) _sysType = sysType::NA;
    if( sysTypeString.compare("JERup") == 0 ) _sysType = sysType::JERup;
    if( sysTypeString.compare("JERdown") == 0 ) _sysType = sysType::JERdown;
    if( sysTypeString.compare("JESup") == 0 ) _sysType = sysType::JESup;
    if( sysTypeString.compare("JESdown") == 0 ) _sysType = sysType::JESdown;
    if( sysTypeString.compare("TESup") == 0 ) _sysType = sysType::TESup;
    if( sysTypeString.compare("TESdown") == 0 ) _sysType = sysType::TESdown;
}

// === Destructor === //
Ntuplizer::~Ntuplizer(){
	delete jobConfig; jobConfig = NULL;	
}

// ------------ method called once each job just before starting event loop  ------------
void
Ntuplizer::beginJob()
{
    _file = new TFile(_filename.c_str(), "RECREATE");
    if (!_file->IsOpen()) {
        edm::LogError("Ntuplizer") << "Can't open file '" << _filename << "' for writing!" << std::endl;
        throw;
    }
    _file->cd();

    _EventsRead = new TH1I(("EventsRead" + _filename).c_str(), "EventsRead",1,0,1);
    _Tree = new TTree("TTbarHTauTau", "TTbarHTauTau");
    // FIXME Set the flushing threshold to a lower level.  With the default
    // setting of ROOT 5.32 (CMSSW 5_3_8), the basket size of the tree
    // grows significantly after a while and does not decrease.  This
    // causes jobs to fail, as they exceed 2.3 GB RSS memory and get killed
    // by the crab watchdog.
    _Tree->SetAutoFlush(1000);

    _numFailedTauEventCheck = 0;


	// Instantiate and set up beanHelper
	string eraForBEANhelper = (GetAnalysisTypeParameter(0) == "2011") ? GetAnalysisTypeParameter(0) : (GetAnalysisTypeParameter(0) + "_" + _EraRelease);
	beanHelper.SetUp(eraForBEANhelper, // 2011, 2012_52x, 2012_53x
            atoi(GetAnalysisTypeParameter(3).c_str()), // sample number
            _an_type,
            SampleTypeContains("data"), // is data
            std::string("SingleMu"), // data set
            false, // do CSV reshaping
            _UsePfLeptons, 
            _DataRange // 2012A_13July,2012A_06Aug,2012B_13July,2012C_PR,2012C_24Aug,2012D_PR,All,all
    );
    map<string,BEANhelper*> beanHelpers;
    beanHelpers["2012ABCD"] = &beanHelper;
    if(_RunExtraBEANhelpers) {
        beanHelpers["2012A"] = new BEANhelper();
        beanHelpers["2012A"]->SetUp(eraForBEANhelper,
            atoi(GetAnalysisTypeParameter(3).c_str()),
            _an_type,
            SampleTypeContains("data"),
            std::string("SingleMu"), 
            false, 
            _UsePfLeptons, 
            string("2012A_13July,2012A_06Aug")
        );
        beanHelpers["2012AB"] = new BEANhelper();
        beanHelpers["2012AB"]->SetUp(eraForBEANhelper,
            atoi(GetAnalysisTypeParameter(3).c_str()),
            _an_type,
            SampleTypeContains("data"),
            std::string("SingleMu"), 
            false, 
            _UsePfLeptons, 
            string("2012A_13July,2012A_06Aug,2012B_13July")
        );
        beanHelpers["2012B"] = new BEANhelper();
        beanHelpers["2012B"]->SetUp(eraForBEANhelper,
            atoi(GetAnalysisTypeParameter(3).c_str()),
            _an_type,
            SampleTypeContains("data"),
            std::string("SingleMu"), 
            false, 
            _UsePfLeptons, 
            string("2012B_13July")
        );
        beanHelpers["2012C"] = new BEANhelper();
        beanHelpers["2012C"]->SetUp(eraForBEANhelper,
            atoi(GetAnalysisTypeParameter(3).c_str()),
            _an_type,
            SampleTypeContains("data"),
            std::string("SingleMu"), 
            false, 
            _UsePfLeptons, 
            string("2012C_PR,2012C_24Aug")
        );
        beanHelpers["2012ABC"] = new BEANhelper();
        beanHelpers["2012ABC"]->SetUp(eraForBEANhelper,
            atoi(GetAnalysisTypeParameter(3).c_str()),
            _an_type,
            SampleTypeContains("data"),
            std::string("SingleMu"), 
            false, 
            _UsePfLeptons, 
            string("2012A_13July,2012A_06Aug,2012B_13July,2012C_PR,2012C_24Aug")
        );
        beanHelpers["2012BC"] = new BEANhelper();
        beanHelpers["2012BC"]->SetUp(eraForBEANhelper,
            atoi(GetAnalysisTypeParameter(3).c_str()),
            _an_type,
            SampleTypeContains("data"),
            std::string("SingleMu"), 
            false, 
            _UsePfLeptons, 
            string("2012B_13July,2012C_PR,2012C_24Aug")
        );
        beanHelpers["2012D"] = new BEANhelper();
        beanHelpers["2012D"]->SetUp(eraForBEANhelper,
            atoi(GetAnalysisTypeParameter(3).c_str()),
            _an_type,
            SampleTypeContains("data"),
            std::string("SingleMu"), 
            false, 
            _UsePfLeptons, 
            string("2012D_PR")
        );
        beanHelpers["2012CD"] = new BEANhelper();
        beanHelpers["2012CD"]->SetUp(eraForBEANhelper,
            atoi(GetAnalysisTypeParameter(3).c_str()),
            _an_type,
            SampleTypeContains("data"),
            std::string("SingleMu"), 
            false, 
            _UsePfLeptons, 
            string("2012C_PR,2012C_24Aug,2012D_PR")
        );
    }

	// Declare and store here NtupleFillers
	if(IsFillerEnabled("Event")){				ntupleFillers.push_back(new EventFiller(*jobConfig, _Tree, beanHelpers));			}
	if(IsFillerEnabled("Vertex")){				ntupleFillers.push_back(new VertexFiller(*jobConfig, _Tree, &beanHelper));			}
	if(IsFillerEnabled("GenLevel")){			ntupleFillers.push_back(new GenLevelFiller(*jobConfig, _Tree, &beanHelper));		}
	if(IsFillerEnabled("GenTau")){				ntupleFillers.push_back(new GenTauFiller(*jobConfig, _Tree, &beanHelper));			}
	if(IsFillerEnabled("GenJet")){				ntupleFillers.push_back(new GenJetFiller(*jobConfig, _Tree, &beanHelper));			}
	if(IsFillerEnabled("Tau")){					ntupleFillers.push_back(new TauFiller(*jobConfig, _Tree, &beanHelper));				}
	if(IsFillerEnabled("Electron")){			ntupleFillers.push_back(new ElectronFiller(*jobConfig, _Tree, &beanHelper));		}
	if(IsFillerEnabled("Muon")){				ntupleFillers.push_back(new MuonFiller(*jobConfig, _Tree, &beanHelper));			}
	if(IsFillerEnabled("Jet")){					ntupleFillers.push_back(new JetFiller(*jobConfig, _Tree, &beanHelper));				}
	if(IsFillerEnabled("Ditau")){				ntupleFillers.push_back(new DitauFiller(*jobConfig, _Tree, &beanHelper));			}
	if(IsFillerEnabled("DitauLepton")){			ntupleFillers.push_back(new DitauLeptonFiller(*jobConfig, _Tree, &beanHelper));		}
	if(IsFillerEnabled("DitauMuon")){			ntupleFillers.push_back(new DitauMuonFiller(*jobConfig, _Tree, &beanHelper));		}
	if(IsFillerEnabled("DitauElectron")){		ntupleFillers.push_back(new DitauElectronFiller(*jobConfig, _Tree, &beanHelper));	}
	if(IsFillerEnabled("TauLeptonLepton")){		ntupleFillers.push_back(new TauLeptonLeptonFiller(*jobConfig, _Tree, &beanHelper));	}
	//if(IsFillerEnabled("Quick")){				ntupleFillers.push_back(new QuickFiller(*jobConfig, _Tree, &fs, &beanHelper));		}
	
}

// === Method called once each job just after ending the event loop === //
void
Ntuplizer::endJob()
{
    if( _RunExtraBEANhelpers )
        for (auto& pair: beanHelpers)
            delete pair.second;
    for (auto& filler: ntupleFillers)
       delete filler;

    LogWarning("TauNtuplizer") << _numFailedTauEventCheck << " events failed BEANhelper::IsTauEvent" << endl;

    _file->WriteObject(_Tree, "TTbarHTauTau");
    delete _Tree;
    _file->WriteObject(_EventsRead, "EventsRead");
    _file->Close();

    delete _file;
}



// ------------ method called to for each event  ------------
void Ntuplizer::analyze(const Event& iEvent, const EventSetup& iSetup) {

    //std::cout << "<Ntuplizer::analyze>: enter function" << std::endl;

	/*// Generic event info (commented out, but available if needed here)
	double eventNum		= iEvent.id().event();
	double lumiBlock	= iEvent.id().luminosityBlock();
	double runNum		= iEvent.id().run();//*/


	// Fill histogram that keeps track of the number of events read
	_EventsRead->Fill(0);

    // Remove non-TTL events
    Handle<BNelectronCollection>			hBNelectrons;
    Handle<BNmuonCollection>				hBNmuons;
    Handle<BNtauCollection>					hBNtaus;
    Handle<BNjetCollection>					hBNjets;
    
    iEvent.getByLabel(_RecoElectronSource,	hBNelectrons);
    iEvent.getByLabel(_RecoMuonSource, 		hBNmuons);
    iEvent.getByLabel(_RecoTauSource, 		hBNtaus);
    iEvent.getByLabel(_RecoJetSource, 		hBNjets);
    
    BNelectronCollection BNelectrons	= *(hBNelectrons.product());
    BNmuonCollection BNmuons			= *(hBNmuons.product());
    BNtauCollection BNtaus				= *(hBNtaus.product());
    BNjetCollection BNjets				= *(hBNjets.product());

    if (((_num_leptons & 1) && !beanHelper.IsTauTauLeptonEvent(BNtaus, BNjets, BNelectrons, BNmuons, _sysType)) ||
        ((_num_leptons & 2) && !beanHelper.IsTauLeptonLeptonEvent(BNtaus, BNjets, BNelectrons, BNmuons, _sysType))) {
        _numFailedTauEventCheck++;
        return;
    } else if (!(_num_leptons & 3)) {
        throw;
    }

	// See if event meets skim trigger requirements
	if((!_FromBEAN) && _ApplySkimTriggerRequirements){
		if(!MeetsTriggerRequirements(iEvent, _SkimTriggerSource, _SkimTriggerRequirements)){ return; }
	}

	// Analyze and fill ntuple
	for(unsigned int n=0; n<ntupleFillers.size(); n++){
		if(_DebugLevel>0){ cout << "[DEBUG]\t" << ntupleFillers.at(n)->GetName() << "->FillNtuple" << endl; }
		ntupleFillers.at(n)->FillNtuple(iEvent, iSetup);
	}

	// Write to tree
	_Tree->Fill();

}

// -------------Apply Trigger Requirements
bool Ntuplizer::MeetsTriggerRequirements(const Event& iEvent, InputTag iTriggerSource, vector<string> iTriggerRequirements){

	// Get a relevant collections
	Handle< edm::TriggerResults > _triggerResults;
	iEvent.getByLabel(iTriggerSource, _triggerResults);

	const edm::TriggerNames & TheTriggerNames = iEvent.triggerNames(*_triggerResults);
	for(vector<string>::const_iterator TheTriggerPath = iTriggerRequirements.begin(); TheTriggerPath != iTriggerRequirements.end(); ++TheTriggerPath ) {

		unsigned int index = TheTriggerNames.triggerIndex(*TheTriggerPath);

		if(index < TheTriggerNames.size()){
			if(_triggerResults->accept(index)){ return true; }
		}else{
			cerr << "\nERROR: Specified trigger '" << (*TheTriggerPath) << "' not found." << endl;
			cerr << "Please use one of the following triggers:" << endl;

			for(TriggerNames::Strings::const_iterator triggerName = TheTriggerNames.triggerNames().begin(); triggerName != TheTriggerNames.triggerNames().end(); ++triggerName ){
					unsigned int index	= TheTriggerNames.triggerIndex(*triggerName);
					string name			= (*triggerName);
					//string decision		= (_triggerResults->accept(index)) ? "passed" : "failed";
					//cerr 	<< "\t" << index << "\t'" << name << "'" << string((50-name.length()),'.') << decision << endl;
					cerr 	<< " " << index << "\t" << name << endl;
			}
			cerr << "\n" << endl;
			exit(1);
		}
	}
	return false;
}

bool Ntuplizer::IsFillerEnabled(const string iName){
	for(unsigned int f=0; f<_enabledFillers.size(); f++){
        if (_enabledFillers.at(f).compare(iName) == 0) {
            std::cout << "---> found " << iName << std::endl;
            return true;
        }
	}

	return false;
}

// === Check whether an analysis type is how we want === //
string Ntuplizer::GetAnalysisTypeParameter(unsigned int iParam){

	// Parse analysisType and store parts in the vector
	if(_AnalysisTypeVector.size() == 0){	
		if(_AnalysisType.length()==0){ cerr << "ERROR: 'AnalysisType' is empty." << endl; exit(1); }
		char separator = '_';
		string remainder = _AnalysisType;
		while(remainder.length() > 0){
			unsigned int pos = remainder.find(separator);
			if(pos < remainder.size()){
				_AnalysisTypeVector.push_back(remainder.substr(0, pos));
				remainder = remainder.substr(pos+1);
			}else{
				_AnalysisTypeVector.push_back(remainder);
				remainder = "";
			}	
		}
	}

	// Return the requested piece if it's there 
	if(iParam >= _AnalysisTypeVector.size()){ cerr << "ERROR: Requesting AnalysisType parameter " << iParam << " but vector only has " << _AnalysisTypeVector.size() << " elements." << endl; exit(1); }
	return _AnalysisTypeVector.at(iParam);
}

unsigned int Ntuplizer::GetEra(){ return abs(atoi(GetAnalysisTypeParameter(0).c_str())); }
const char Ntuplizer::GetSubera(){ return *(GetAnalysisTypeParameter(1).c_str()); }
string Ntuplizer::GetSampleType(){ return GetAnalysisTypeParameter(2); }
string Ntuplizer::GetLeptonFlavor(){ return GetAnalysisTypeParameter(3); }
bool Ntuplizer::EraIs(unsigned int iEra){ return (iEra==GetEra()); }
bool Ntuplizer::SuberaIs(const char iSubera){ return (iSubera==GetSubera()); }
bool Ntuplizer::SampleTypeIs(const string iSampleType){ return (iSampleType.compare(GetSampleType())==0); }
bool Ntuplizer::SampleTypeContains(const string iSampleType){ string sampleType = GetSampleType(); return (sampleType.find(iSampleType) < sampleType.length()); }
bool Ntuplizer::LeptonFlavorIs(const string iLeptonFlavor){ return (iLeptonFlavor.compare(GetLeptonFlavor())==0); }


//define this as a plug-in
DEFINE_FWK_MODULE(Ntuplizer);
