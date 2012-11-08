// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/EventFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
EventFiller::EventFiller(const ParameterSet& iConfig): NtupleFiller(iConfig){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

EventFiller::EventFiller(const ParameterSet& iConfig, TTree* iTree) : NtupleFiller(iConfig) {
	_FillerName	= __FILE__;
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
EventFiller::~EventFiller(){}

// ------------ method called to for each event  ------------
void EventFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void EventFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("Ev_runNumber", &_runNumber);
	_Tree->Branch("Ev_eventNumber", &_eventNumber);
	_Tree->Branch("Ev_lumiBlock", &_lumiBlock);
	_Tree->Branch("Ev_numInteractionsBXm1", &_numInteractionsBXm1);
	_Tree->Branch("Ev_numInteractionsBX0", &_numInteractionsBX0);
	_Tree->Branch("Ev_numInteractionsBXp1", &_numInteractionsBXp1);
	_Tree->Branch("Ev_numPrimaryVertices", &_numPrimaryVertices);

	_Tree->Branch("Ev_MET", &_MET);
	_Tree->Branch("Ev_METphi", &_METphi);
}

// === Clear vectors that will be used to fill ntuple === //
void EventFiller::ClearVectors(){

	_runNumber					= 0;
	_eventNumber				= 0;
	_lumiBlock					= 0;
	_numInteractionsBXm1		= 0;
	_numInteractionsBX0			= 0;
	_numInteractionsBXp1		= 0;
	_numPrimaryVertices			= 0;

	_MET						= 0;
	_METphi						= 0;

}

// === Fill ntuple === //
void EventFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();

	_runNumber			= iEvent.id().run();
	_eventNumber		= iEvent.id().event();
	_lumiBlock			= iEvent.id().luminosityBlock();

	// MET
	BNjetCollection correctedJets							= beanHelper.GetCorrectedJets(_BNjets);
	BNjetCollection selCorrJets								= beanHelper.GetSelectedJets(correctedJets, 30, 2.4, BEANhelper::jetID::jetLoose, '-');
	BNjetCollection uncorrectedJetsFromCorrectedSelection	= beanHelper.GetUncorrectedJets(selCorrJets, _BNjets);
	BNmet correctedMET	= beanHelper.GetCorrectedMET(*(_BNmets.begin()), uncorrectedJetsFromCorrectedSelection);
	_MET				= correctedMET.pt;
	_METphi				= correctedMET.phi;

	// Pileup
	_PUweight			= beanHelper.GetPUweight(_BNevents.begin()->numTruePV);
	_numPrimaryVertices	= _BNprimaryVertices.size();

}
