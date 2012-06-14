// Author: Nil Valls <nvallsve@nd.edu>

#include "HighMassAnalysis/Analysis/interface/TauFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
TauFiller::TauFiller(const ParameterSet& iConfig): NtupleFiller(iConfig){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

TauFiller::TauFiller(const ParameterSet& iConfig, TTree* iTree) : NtupleFiller(iConfig) {
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
TauFiller::~TauFiller(){}

// ------------ method called to for each event  ------------
void TauFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void TauFiller::SetupBranches(){

	// Set up tree branches
	_Tree->Branch("T_NumTaus",&_NumTaus);
	_Tree->Branch("T_Number",&_TauNumber);
	_Tree->Branch("T_Pt",&_TauPt);
	_Tree->Branch("T_Eta",&_TauEta);
	_Tree->Branch("T_Phi",&_TauPhi);
}

// === Clear vectors that will be used to fill ntuple === //
void TauFiller::ClearVectors(){

	_NumTaus		=	0;	
	_TauNumber		.clear();
	_TauPt	   		.clear();
	_TauEta   		.clear();
	_TauPhi   		.clear();

}

// === Fill ntuple === //
void TauFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();

	_NumTaus = _patTaus->size();
	for ( pat::TauCollection::const_iterator Tau = _patTaus->begin(); Tau != _patTaus->end(); ++Tau ) {
		_TauNumber.push_back(_TauNumber.size());
		_TauPt.push_back(Tau->pt());
		_TauEta.push_back(Tau->eta());
		_TauPhi.push_back(Tau->phi());
	}

}


//define this as a plug-in
DEFINE_FWK_MODULE(TauFiller);
