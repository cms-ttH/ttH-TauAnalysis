// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/MuonFiller.h"
//#include "fillerAuxFunctions.cc"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
MuonFiller::MuonFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

MuonFiller::MuonFiller(const ParameterSet& iConfig, TTree* iTree, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper) {
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

	_Tree->Branch("M_MuonGenMatchDaughter0Id", &_MuonGenMatchDaughter0Id);
	_Tree->Branch("M_MuonGenMatchDaughter1Id", &_MuonGenMatchDaughter1Id);
	_Tree->Branch("M_MuonGenMatchId", &_MuonGenMatchId);
	_Tree->Branch("M_MuonGenMatchMother0Id", &_MuonGenMatchMother0Id);
	_Tree->Branch("M_MuonGenMatchMother1Id", &_MuonGenMatchMother1Id);
	_Tree->Branch("M_MuonGenMatchGrandmother00Id", &_MuonGenMatchGrandmother00Id);
	_Tree->Branch("M_MuonGenMatchGrandmother01Id", &_MuonGenMatchGrandmother01Id);
	_Tree->Branch("M_MuonGenMatchGrandmother10Id", &_MuonGenMatchGrandmother10Id);
	_Tree->Branch("M_MuonGenMatchGrandmother11Id", &_MuonGenMatchGrandmother11Id);
	_Tree->Branch("M_MuonGenMatchDaughter0Status", &_MuonGenMatchDaughter0Status);
	_Tree->Branch("M_MuonGenMatchDaughter1Status", &_MuonGenMatchDaughter1Status);
	_Tree->Branch("M_MuonGenMatchStatus", &_MuonGenMatchStatus);
	_Tree->Branch("M_MuonGenMatchMother0Status", &_MuonGenMatchMother0Status);
	_Tree->Branch("M_MuonGenMatchMother1Status", &_MuonGenMatchMother1Status);
	_Tree->Branch("M_MuonGenMatchGrandmother00Status", &_MuonGenMatchGrandmother00Status);
	_Tree->Branch("M_MuonGenMatchGrandmother01Status", &_MuonGenMatchGrandmother01Status);
	_Tree->Branch("M_MuonGenMatchGrandmother10Status", &_MuonGenMatchGrandmother10Status);
	_Tree->Branch("M_MuonGenMatchGrandmother11Status", &_MuonGenMatchGrandmother11Status);
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

	_MuonGenMatchDaughter0Id						.clear();
	_MuonGenMatchDaughter1Id						.clear();
	_MuonGenMatchId									.clear();
	_MuonGenMatchMother0Id							.clear();
	_MuonGenMatchMother1Id							.clear();
	_MuonGenMatchGrandmother00Id					.clear();
	_MuonGenMatchGrandmother01Id					.clear();
	_MuonGenMatchGrandmother10Id					.clear();
	_MuonGenMatchGrandmother11Id					.clear();
	_MuonGenMatchDaughter0Status	   				.clear();
	_MuonGenMatchDaughter1Status	   				.clear();
	_MuonGenMatchStatus			   					.clear();
	_MuonGenMatchMother0Status	   					.clear();
	_MuonGenMatchMother1Status	   					.clear();
	_MuonGenMatchGrandmother00Status				.clear();
	_MuonGenMatchGrandmother01Status				.clear();
	_MuonGenMatchGrandmother10Status				.clear();
	_MuonGenMatchGrandmother11Status				.clear();

}

// === Fill ntuple === //
void MuonFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	
    GetCollections(iEvent, iSetup);
	ClearVectors();

	unsigned int theNumberOfMuons = 0;

	BNmuonCollection selectedMuons = beanHelper->GetSelectedMuons(_BNmuons, muonID::muonTight);
	//BNmuonCollection selectedMuons = _BNmuons;
	
	_NumMuons = selectedMuons.size();
	theNumberOfMuons = 0;
	for ( BNmuonCollection::const_iterator Muon = selectedMuons.begin(); Muon != selectedMuons.end(); ++Muon ) {
		theNumberOfMuons++;

		_NumMuons++;
		_MomentumRank.push_back(_MomentumRank.size());
		_MuonPt.push_back(Muon->pt);
		_MuonEta.push_back(Muon->eta);
		_MuonPhi.push_back(Muon->phi);
		_MuonRelIso.push_back(beanHelper->GetMuonRelIso(*Muon));
		_IsLooseMuon.push_back(beanHelper->IsLooseMuon(*Muon));
		_IsTightMuon.push_back(beanHelper->IsTightMuon(*Muon));

		// Provenance
		BNmcparticle muonGenMatch = beanHelper->GetMatchedMCparticle(_BNmcparticles, *Muon, 0.25);
		_MuonGenMatchDaughter0Id			.push_back(muonGenMatch.daughter0Id);
		_MuonGenMatchDaughter1Id			.push_back(muonGenMatch.daughter1Id);
		_MuonGenMatchId						.push_back(muonGenMatch.id);
		_MuonGenMatchMother0Id				.push_back(muonGenMatch.mother0Id);
		_MuonGenMatchMother1Id				.push_back(muonGenMatch.mother1Id);
		_MuonGenMatchGrandmother00Id		.push_back(muonGenMatch.grandMother00Id);
		_MuonGenMatchGrandmother01Id		.push_back(muonGenMatch.grandMother01Id);
		_MuonGenMatchGrandmother10Id		.push_back(muonGenMatch.grandMother10Id);
		_MuonGenMatchGrandmother11Id		.push_back(muonGenMatch.grandMother11Id);
		_MuonGenMatchDaughter0Status	   	.push_back(muonGenMatch.daughter0Status);
		_MuonGenMatchDaughter1Status	   	.push_back(muonGenMatch.daughter1Status);
		_MuonGenMatchStatus			   		.push_back(muonGenMatch.status);
		_MuonGenMatchMother0Status		  	.push_back(muonGenMatch.mother0Status);
		_MuonGenMatchMother1Status		   	.push_back(muonGenMatch.mother1Status);
		_MuonGenMatchGrandmother00Status	.push_back(muonGenMatch.grandMother00Status);
		_MuonGenMatchGrandmother01Status	.push_back(muonGenMatch.grandMother01Status);
		_MuonGenMatchGrandmother10Status	.push_back(muonGenMatch.grandMother10Status);
		_MuonGenMatchGrandmother11Status	.push_back(muonGenMatch.grandMother11Status);
	}


}
