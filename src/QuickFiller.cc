// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/QuickFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
QuickFiller::QuickFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

QuickFiller::QuickFiller(const ParameterSet& iConfig, TTree* iTree, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper) {
	_FillerName	= __FILE__;
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
QuickFiller::~QuickFiller(){}

// ------------ method called to for each event  ------------
void QuickFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void QuickFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("Q_PUweight", &_PUweight);

}

// === Clear vectors that will be used to fill ntuple === //
void QuickFiller::ClearVectors(){

	_PUweight = 1.0;

}

// === Fill ntuple === //
void QuickFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();

	_PUweight               = beanHelper->GetPUweight(_BNevents.begin()->numTruePV);
	
}
