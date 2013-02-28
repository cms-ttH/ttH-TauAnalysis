// Author: Nil Valls <nvallsve@nd.edu>

#include "..//interface/Ntuplizer.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
Ntuplizer::Ntuplizer(const ParameterSet& iConfig) {

	// Necessary to propagate iConfig 
	jobConfig						= new ParameterSet(iConfig);

	// Analysis type
	_DebugLevel						= iConfig.getParameter<unsigned int>("DebugLevel");
	_FromBEAN						= iConfig.getParameter<bool>("FromBEAN");
	_AnalysisType					= iConfig.getParameter<string>("AnalysisType");
	_EraRelease						= iConfig.getParameter<string>("EraRelease");
    _UsePfLeptons                   = ( iConfig.exists("UsePfLeptons") ) ? iConfig.getParameter<bool>("UsePfLeptons") : true;

	// Name of the ntuple tree
	_TreeName						= iConfig.getUntrackedParameter<std::string>("TreeName");

	// Fillers to use
	_enabledFillers					= iConfig.getUntrackedParameter<std::vector<std::string> >("NtupleFillers");

	// Skim trigger
	_ApplySkimTriggerRequirements	= iConfig.getParameter<bool>("ApplySkimTriggerRequirements");
	_SkimTriggerSource				= iConfig.getParameter<InputTag>("SkimTriggerSource");
	_SkimTriggerRequirements		= iConfig.getParameter<vector<string> >("SkimTriggerRequirements");

}

// === Destructor === //
Ntuplizer::~Ntuplizer(){
	delete jobConfig; jobConfig = NULL;	
}

// ------------ method called once each job just before starting event loop  ------------
void  Ntuplizer::beginJob() {

    //std::cout << "<Ntuplizer::beginJob>: enter function" << std::endl;

	// Initialize TFileService
	Service<TFileService> fs;
	_EventsRead	= fs->make<TH1I>("EventsRead", "EventsRead",1,0,1);
	_Tree		= fs->make<TTree>(_TreeName.c_str(), _TreeName.c_str());


	// Instantiate and set up beanHelper
	string eraForBEANhelper = (GetAnalysisTypeParameter(0) == "2011") ? GetAnalysisTypeParameter(0) : (GetAnalysisTypeParameter(0) + "_" + _EraRelease);
	beanHelper.SetUp(eraForBEANhelper, atoi(GetAnalysisTypeParameter(4).c_str()), false, SampleTypeContains("data"), std::string("SingleMu"), true, _UsePfLeptons);

	// Declare and store here NtupleFillers
	if(IsFillerEnabled("Event")){			ntupleFillers.push_back(new EventFiller(*jobConfig, _Tree, &beanHelper));			}
	if(IsFillerEnabled("GenLevel")){		ntupleFillers.push_back(new GenLevelFiller(*jobConfig, _Tree, &beanHelper));		}
	if(IsFillerEnabled("GenTau")){			ntupleFillers.push_back(new GenTauFiller(*jobConfig, _Tree, &beanHelper));			}
	if(IsFillerEnabled("GenJet")){			ntupleFillers.push_back(new GenJetFiller(*jobConfig, _Tree, &beanHelper));			}
	if(IsFillerEnabled("Tau")){				ntupleFillers.push_back(new TauFiller(*jobConfig, _Tree, &beanHelper));				}
	if(IsFillerEnabled("Electron")){		ntupleFillers.push_back(new ElectronFiller(*jobConfig, _Tree, &beanHelper));		}
	if(IsFillerEnabled("Muon")){			ntupleFillers.push_back(new MuonFiller(*jobConfig, _Tree, &beanHelper));			}
	if(IsFillerEnabled("Jet")){				ntupleFillers.push_back(new JetFiller(*jobConfig, _Tree, &beanHelper));				}
	if(IsFillerEnabled("Ditau")){			ntupleFillers.push_back(new DitauFiller(*jobConfig, _Tree, &beanHelper));			}
	if(IsFillerEnabled("DitauLepton")){		ntupleFillers.push_back(new DitauLeptonFiller(*jobConfig, _Tree, &beanHelper));		}
	if(IsFillerEnabled("DitauMuon")){		ntupleFillers.push_back(new DitauMuonFiller(*jobConfig, _Tree, &beanHelper));		}
	if(IsFillerEnabled("DitauElectron")){	ntupleFillers.push_back(new DitauElectronFiller(*jobConfig, _Tree, &beanHelper));	}
	if(IsFillerEnabled("Quick")){			ntupleFillers.push_back(new QuickFiller(*jobConfig, _Tree, &fs, &beanHelper));		}
	
}

// === Method called once each job just after ending the event loop === //
void Ntuplizer::endJob(){
	
	// Delete NtupleFillers
	for(unsigned int n=0; n<ntupleFillers.size(); n++){ delete ntupleFillers.at(n); ntupleFillers.at(n) = NULL; }

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
		if(_enabledFillers.at(f).compare(iName)==0){ std::cout << " ---> found " << iName << std::endl; return true; }	
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
