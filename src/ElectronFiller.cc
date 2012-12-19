// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/ElectronFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
ElectronFiller::ElectronFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

ElectronFiller::ElectronFiller(const ParameterSet& iConfig, TTree* iTree, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper) {
	_FillerName	= __FILE__;
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
ElectronFiller::~ElectronFiller(){}

// ------------ method called to for each event  ------------
void ElectronFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void ElectronFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("E_NumElectrons",&_NumElectrons);
	_Tree->Branch("E_MomentumRank",&_MomentumRank);
	_Tree->Branch("E_Pt",&_ElectronPt);
	_Tree->Branch("E_Eta",&_ElectronEta);
	_Tree->Branch("E_Phi",&_ElectronPhi);
	_Tree->Branch("E_IsTightElectron",&_IsTightElectron);
	_Tree->Branch("E_IsLooseElectron",&_IsLooseElectron);

	_Tree->Branch("E_ElectronGenMatchDaughter0Id", &_ElectronGenMatchDaughter0Id);
	_Tree->Branch("E_ElectronGenMatchDaughter1Id", &_ElectronGenMatchDaughter1Id);
	_Tree->Branch("E_ElectronGenMatchId", &_ElectronGenMatchId);
	_Tree->Branch("E_ElectronGenMatchMother0Id", &_ElectronGenMatchMother0Id);
	_Tree->Branch("E_ElectronGenMatchMother1Id", &_ElectronGenMatchMother1Id);
	_Tree->Branch("E_ElectronGenMatchGrandmother00Id", &_ElectronGenMatchGrandmother00Id);
	_Tree->Branch("E_ElectronGenMatchGrandmother01Id", &_ElectronGenMatchGrandmother01Id);
	_Tree->Branch("E_ElectronGenMatchGrandmother10Id", &_ElectronGenMatchGrandmother10Id);
	_Tree->Branch("E_ElectronGenMatchGrandmother11Id", &_ElectronGenMatchGrandmother11Id);
	_Tree->Branch("E_ElectronGenMatchDaughter0Status", &_ElectronGenMatchDaughter0Status);
	_Tree->Branch("E_ElectronGenMatchDaughter1Status", &_ElectronGenMatchDaughter1Status);
	_Tree->Branch("E_ElectronGenMatchStatus", &_ElectronGenMatchStatus);
	_Tree->Branch("E_ElectronGenMatchMother0Status", &_ElectronGenMatchMother0Status);
	_Tree->Branch("E_ElectronGenMatchMother1Status", &_ElectronGenMatchMother1Status);
	_Tree->Branch("E_ElectronGenMatchGrandmother00Status", &_ElectronGenMatchGrandmother00Status);
	_Tree->Branch("E_ElectronGenMatchGrandmother01Status", &_ElectronGenMatchGrandmother01Status);
	_Tree->Branch("E_ElectronGenMatchGrandmother10Status", &_ElectronGenMatchGrandmother10Status);
	_Tree->Branch("E_ElectronGenMatchGrandmother11Status", &_ElectronGenMatchGrandmother11Status);
}

// === Clear vectors that will be used to fill ntuple === //
void ElectronFiller::ClearVectors(){

	_NumElectrons		=	0;	
	_MomentumRank		.clear();
	_ElectronPt	   		.clear();
	_ElectronEta   		.clear();
	_ElectronPhi   		.clear();
	_ElectronRelIso		.clear();
	_IsTightElectron    .clear();
	_IsLooseElectron 	.clear();
	_ElectronGenMatchDaughter0Id						.clear();
	_ElectronGenMatchDaughter1Id						.clear();
	_ElectronGenMatchId									.clear();
	_ElectronGenMatchMother0Id							.clear();
	_ElectronGenMatchMother1Id							.clear();
	_ElectronGenMatchGrandmother00Id					.clear();
	_ElectronGenMatchGrandmother01Id					.clear();
	_ElectronGenMatchGrandmother10Id					.clear();
	_ElectronGenMatchGrandmother11Id					.clear();
	_ElectronGenMatchDaughter0Status	   				.clear();
	_ElectronGenMatchDaughter1Status	   				.clear();
	_ElectronGenMatchStatus			   					.clear();
	_ElectronGenMatchMother0Status	   					.clear();
	_ElectronGenMatchMother1Status	   					.clear();
	_ElectronGenMatchGrandmother00Status				.clear();
	_ElectronGenMatchGrandmother01Status				.clear();
	_ElectronGenMatchGrandmother10Status				.clear();
	_ElectronGenMatchGrandmother11Status				.clear();

}

// === Fill ntuple === //
void ElectronFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();

	unsigned int theNumberOfElectrons = 0;

	BNelectronCollection selectedElectrons = beanHelper->GetSelectedElectrons(_BNelectrons, electronID::electronLoose);
	//BNelectronCollection selectedElectrons = _BNelectrons;

	_NumElectrons = selectedElectrons.size();
	theNumberOfElectrons = 0;
	for ( BNelectronCollection::const_iterator Electron = selectedElectrons.begin(); Electron != selectedElectrons.end(); ++Electron ) {
		theNumberOfElectrons++;

		_NumElectrons++;
		_MomentumRank.push_back(_MomentumRank.size());
		_ElectronPt.push_back(Electron->pt);
		_ElectronEta.push_back(Electron->eta);
		_ElectronPhi.push_back(Electron->phi);
		_ElectronRelIso.push_back(beanHelper->GetElectronRelIso(*Electron));
		_IsLooseElectron.push_back(beanHelper->IsLooseElectron(*Electron));
		_IsTightElectron.push_back(beanHelper->IsTightElectron(*Electron));

		BNmcparticle electronGenMatch = beanHelper->GetMatchedMCparticle(_BNmcparticles, *Electron, 0.25);
		_ElectronGenMatchDaughter0Id			.push_back(electronGenMatch.daughter0Id);
		_ElectronGenMatchDaughter1Id			.push_back(electronGenMatch.daughter1Id);
		_ElectronGenMatchId						.push_back(electronGenMatch.id);
		_ElectronGenMatchMother0Id				.push_back(electronGenMatch.mother0Id);
		_ElectronGenMatchMother1Id				.push_back(electronGenMatch.mother1Id);
		_ElectronGenMatchGrandmother00Id		.push_back(electronGenMatch.grandMother00Id);
		_ElectronGenMatchGrandmother01Id		.push_back(electronGenMatch.grandMother01Id);
		_ElectronGenMatchGrandmother10Id		.push_back(electronGenMatch.grandMother10Id);
		_ElectronGenMatchGrandmother11Id		.push_back(electronGenMatch.grandMother11Id);
		_ElectronGenMatchDaughter0Status	   	.push_back(electronGenMatch.daughter0Status);
		_ElectronGenMatchDaughter1Status	   	.push_back(electronGenMatch.daughter1Status);
		_ElectronGenMatchStatus			   		.push_back(electronGenMatch.status);
		_ElectronGenMatchMother0Status		  	.push_back(electronGenMatch.mother0Status);
		_ElectronGenMatchMother1Status		   	.push_back(electronGenMatch.mother1Status);
		_ElectronGenMatchGrandmother00Status	.push_back(electronGenMatch.grandMother00Status);
		_ElectronGenMatchGrandmother01Status	.push_back(electronGenMatch.grandMother01Status);
		_ElectronGenMatchGrandmother10Status	.push_back(electronGenMatch.grandMother10Status);
		_ElectronGenMatchGrandmother11Status	.push_back(electronGenMatch.grandMother11Status);
	}
}
