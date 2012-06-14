// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/MuonFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
MuonFiller::MuonFiller(const ParameterSet& iConfig): NtupleFiller(iConfig){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

MuonFiller::MuonFiller(const ParameterSet& iConfig, TTree* iTree) : NtupleFiller(iConfig) {
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
MuonFiller::~MuonFiller(){}

// ------------ method called to for each event  ------------
void MuonFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void MuonFiller::SetupBranches(){

	// Set up tree branches
	_Tree->Branch("M_NumMuons",&_NumMuons);
	_Tree->Branch("M_Number",&_MuonNumber);
	_Tree->Branch("M_Pt",&_MuonPt);
	_Tree->Branch("M_Eta",&_MuonEta);
	_Tree->Branch("M_Phi",&_MuonPhi);
}

// === Clear vectors that will be used to fill ntuple === //
void MuonFiller::ClearVectors(){

	_NumMuons		=	0;	
	_MuonNumber		.clear();
	_MuonPt	   		.clear();
	_MuonEta   		.clear();
	_MuonPhi   		.clear();

}

// === Fill ntuple === //
void MuonFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();

	_NumMuons = _patMuons->size();
	for ( pat::MuonCollection::const_iterator Muon = _patMuons->begin(); Muon != _patMuons->end(); ++Muon ) {
		_MuonNumber.push_back(_MuonNumber.size());
		_MuonPt.push_back(Muon->pt());
		_MuonEta.push_back(Muon->eta());
		_MuonPhi.push_back(Muon->phi());
	}

}


//define this as a plug-in
DEFINE_FWK_MODULE(MuonFiller);
