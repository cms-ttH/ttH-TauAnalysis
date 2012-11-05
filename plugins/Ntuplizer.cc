// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/Ntuplizer.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
Ntuplizer::Ntuplizer(const ParameterSet& iConfig) {

	// Necessary to propagate iConfig 
	jobConfig						= new ParameterSet(iConfig);

	// Analysis type
	_DebugLevel						= iConfig.getParameter<unsigned int>("DebugLevel");
	_AnalysisType					= iConfig.getParameter<string>("AnalysisType");
	_FromBEAN						= iConfig.getParameter<bool>("FromBEAN");

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

	// Initialize TFileService
	Service<TFileService> fs;
	_EventsRead	= fs->make<TH1I>("EventsRead", "EventsRead",1,0,1);
	_Tree		= fs->make<TTree>(_TreeName.c_str(), _TreeName.c_str());

	// Declare and store here NtupleFillers
	if(IsFillerEnabled("Event")){			ntupleFillers.push_back(new EventFiller(*jobConfig, _Tree));			}
	if(IsFillerEnabled("GenLevel")){		ntupleFillers.push_back(new GenLevelFiller(*jobConfig, _Tree));			}
	if(IsFillerEnabled("GenTau")){			ntupleFillers.push_back(new GenTauFiller(*jobConfig, _Tree));			}
	if(IsFillerEnabled("GenJet")){			ntupleFillers.push_back(new GenJetFiller(*jobConfig, _Tree));			}
	if(IsFillerEnabled("Tau")){				ntupleFillers.push_back(new TauFiller(*jobConfig, _Tree));				}
	if(IsFillerEnabled("Electron")){		ntupleFillers.push_back(new ElectronFiller(*jobConfig, _Tree));			}
	if(IsFillerEnabled("Muon")){			ntupleFillers.push_back(new MuonFiller(*jobConfig, _Tree));				}
	if(IsFillerEnabled("Jet")){				ntupleFillers.push_back(new JetFiller(*jobConfig, _Tree));				}
	if(IsFillerEnabled("Ditau")){			ntupleFillers.push_back(new DitauFiller(*jobConfig, _Tree));			}
	if(IsFillerEnabled("DitauMuon")){		ntupleFillers.push_back(new DitauMuonFiller(*jobConfig, _Tree));		}
	if(IsFillerEnabled("DitauElectron")){	ntupleFillers.push_back(new DitauElectronFiller(*jobConfig, _Tree));	}
	
}

// === Method called once each job just after ending the event loop === //
void Ntuplizer::endJob(){
	
	// Delete NtupleFillers
	for(unsigned int n=0; n<ntupleFillers.size(); n++){ delete ntupleFillers.at(n); ntupleFillers.at(n) = NULL; }

}



// ------------ method called to for each event  ------------
void Ntuplizer::analyze(const Event& iEvent, const EventSetup& iSetup) {

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
		if(_enabledFillers.at(f).compare(iName)==0){ return true; }	
	}

	return false;
}

//define this as a plug-in
DEFINE_FWK_MODULE(Ntuplizer);
