// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/MuonFiller.h"
//#include "fillerAuxFunctions.cc"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
MuonFiller::MuonFiller(const ParameterSet& iConfig): NtupleFiller(iConfig){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

MuonFiller::MuonFiller(const ParameterSet& iConfig, TTree* iTree) : NtupleFiller(iConfig) {
	_FillerName	= __FILE__;
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
MuonFiller::~MuonFiller(){}

// ------------ method called to for each event  ------------
void MuonFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void MuonFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("M_NumMuons",&_NumMuons);
	_Tree->Branch("M_MomentumRank",&_MomentumRank);
	_Tree->Branch("M_Pt",&_MuonPt);
	_Tree->Branch("M_Eta",&_MuonEta);
	_Tree->Branch("M_Phi",&_MuonPhi);
	_Tree->Branch("M_RelIso",&_MuonRelIso); 
	_Tree->Branch("M_IsTightMuon",&_IsTightMuon);
	_Tree->Branch("M_IsLooseMuon",&_IsLooseMuon);
}

// === Clear vectors that will be used to fill ntuple === //
void MuonFiller::ClearVectors(){

	_NumMuons		=	0;	
	_MomentumRank	.clear();
	_MuonPt	   		.clear();
	_MuonEta   		.clear();
	_MuonPhi   		.clear();
	_MuonRelIso		.clear();
	_IsTightMuon    .clear();
	_IsLooseMuon 	.clear();

}

// === Fill ntuple === //
void MuonFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	
    GetCollections(iEvent, iSetup);
	ClearVectors();

	unsigned int theNumberOfMuons = 0;

	//BNmuonCollection selectedMuons = beanHelper.GetSelectedMuons(*(_BNmuons->product()), BEANhelper::MuonID::looseTight);
	BNmuonCollection selectedMuons = _BNmuons;
	
	_NumMuons = selectedMuons.size();
	theNumberOfMuons = 0;
	for ( BNmuonCollection::const_iterator Muon = selectedMuons.begin(); Muon != selectedMuons.end(); ++Muon ) {
		theNumberOfMuons++;

		_NumMuons++;
		_MomentumRank.push_back(_MomentumRank.size());
		_MuonPt.push_back(Muon->pt);
		_MuonEta.push_back(Muon->eta);
		_MuonPhi.push_back(Muon->phi);
		_MuonRelIso.push_back(beanHelper.GetMuonRelIso(*Muon));
		_IsLooseMuon.push_back(beanHelper.IsLooseMuon(*Muon));
		_IsTightMuon.push_back(beanHelper.IsTightMuon(*Muon));
	}


}
