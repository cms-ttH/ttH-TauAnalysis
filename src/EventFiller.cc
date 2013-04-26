// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/EventFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
EventFiller::EventFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

EventFiller::EventFiller(const ParameterSet& iConfig, TTree* iTree, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper) {
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
	_Tree->Branch("Ev_puWeight", &_PUweight);
	_Tree->Branch("Ev_puWeightUp", &_PUweightUp);
	_Tree->Branch("Ev_puWeightDown", &_PUweightDown);
    _Tree->Branch("Ev_topPtWeight", &_topPtWeight);
	_Tree->Branch("Ev_topPtWeightUp", &_topPtWeightUp);
	_Tree->Branch("Ev_topPtWeightDown", &_topPtWeightDown);
	_Tree->Branch("Ev_q2WeightUp", &_q2WeightUp);
	_Tree->Branch("Ev_q2WeightDown", &_q2WeightDown);
	_Tree->Branch("Ev_MET", &_MET);
	_Tree->Branch("Ev_METphi", &_METphi);
	_Tree->Branch("Ev_IsTauEvent", &_isTauEvent);
}

// === Clear vectors that will be used to fill ntuple === //
void EventFiller::ClearVectors(){

	_runNumber					= 0;
	_eventNumber				= 0;
	_lumiBlock					= 0;
	_PUweight					= 1.0;
	_PUweightUp					= 1.0;
	_PUweightDown   			= 1.0;
    _topPtWeight                = 1.0;
    _topPtWeightUp              = 1.0;
    _topPtWeightDown            = 1.0;
    _q2WeightUp                 = 1.0;
    _q2WeightDown               = 1.0;
    _isTauEvent                 = false;
	_MET						= 0;
	_METphi						= 0;

}

// === Fill ntuple === //
void EventFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();

	// Event info
	_runNumber			= iEvent.id().run();
	_eventNumber		= iEvent.id().event();
	_lumiBlock			= iEvent.id().luminosityBlock();
	_isTauTauLepton		= beanHelper->IsTauTauLeptonEvent(_BNtaus, _BNjets, _BNelectrons, _BNmuons, _sysType);

	// Pileup weights
	_PUweight				= beanHelper->GetPUweight(_BNevents.begin()->numTruePV);
	_PUweightUp				= beanHelper->GetPUweightUp(_BNevents.begin()->numTruePV);
	_PUweightDown			= beanHelper->GetPUweightDown(_BNevents.begin()->numTruePV);

	// MET
	BNjetCollection correctedJets							= beanHelper->GetCorrectedJets(_BNjets, _sysType);
	BNjetCollection selCorrJets								= beanHelper->GetSelectedJets(correctedJets, 30, 2.4, jetID::jetLoose, '-');
	BNjetCollection uncorrectedJetsFromCorrectedSelection	= beanHelper->GetUncorrectedJets(selCorrJets, _BNjets);
	BNmet correctedMET	= beanHelper->GetCorrectedMET(*(_BNmets.begin()), uncorrectedJetsFromCorrectedSelection, _sysType);
	_MET				= correctedMET.pt;
	_METphi				= correctedMET.phi;

    // top PT
    _topPtWeight = beanHelper->GetTopPtweight(_BNmcparticles);
    _topPtWeightUp = beanHelper->GetTopPtweightUp(_BNmcparticles);
    _topPtWeightDown = beanHelper->GetTopPtweightDown(_BNmcparticles);
    
    // tau
    _isTauEvent         = beanHelper->IsTauTauLeptonEvent(_BNtaus, _BNjets, _BNelectrons, _BNmuons, _sysType);

    // Q^2 weights
    _q2WeightUp = beanHelper->GetQ2ScaleUp(*(_BNevents.begin()));
    _q2WeightDown = beanHelper->GetQ2ScaleDown(*(_BNevents.begin()));

}
