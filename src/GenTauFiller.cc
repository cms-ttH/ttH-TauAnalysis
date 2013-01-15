// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/GenTauFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
GenTauFiller::GenTauFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

GenTauFiller::GenTauFiller(const ParameterSet& iConfig, TTree* iTree, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper) {
	_FillerName	= __FILE__;
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
GenTauFiller::~GenTauFiller(){}

// ------------ method called to for each event  ------------
void GenTauFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void GenTauFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("GT_NumGenTaus",&_NumGenTaus);
	_Tree->Branch("GT_MomentumRank", &_MomentumRank);
	_Tree->Branch("GT_Pt", &_Pt);
	_Tree->Branch("GT_Eta", &_Eta);
	_Tree->Branch("GT_Phi", &_Phi);
	_Tree->Branch("GT_VisPt", &_VisPt);
	_Tree->Branch("GT_VisEta", &_VisEta);
	_Tree->Branch("GT_VisPhi", &_VisPhi);
	_Tree->Branch("GT_ToElectron", &_ToElectron);
	_Tree->Branch("GT_ToMuon", &_ToMuon);
	_Tree->Branch("GT_ToHadrons", &_ToHadrons);
	_Tree->Branch("GT_ParentId", &_ParentId);
	_Tree->Branch("GT_ParentP", &_ParentP);
	_Tree->Branch("GT_ParentPt", &_ParentPt);
	_Tree->Branch("GT_ParentEta", &_ParentEta);
	_Tree->Branch("GT_ParentPhi", &_ParentPhi);

}

// === Clear vectors that will be used to fill ntuple === //
void GenTauFiller::ClearVectors(){

	_NumGenTaus	=	0;	
	_MomentumRank		.clear();
	_Pt	   		.clear();
	_Eta   		.clear();
	_Phi   		.clear();
	_Pt	   		.clear();
	_Eta   		.clear();
	_Phi   		.clear();
	_VisPt		.clear();
	_VisEta		.clear();
	_VisPhi		.clear();
	_ToElectron	.clear();
	_ToMuon		.clear();
	_ToHadrons	.clear();
	_ParentId	.clear();
	_ParentP	.clear();
	_ParentPt	.clear();
	_ParentEta	.clear();
	_ParentPhi	.clear();

}

// === Fill ntuple === //
void GenTauFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){

	// Only run this on MC
	if(SampleTypeContains("data")){ return; }

	GetCollections(iEvent, iSetup);
	ClearVectors();


	vector<int> tauIDs; tauIDs.push_back(15); tauIDs.push_back(-15);
	BNmcparticleCollection mcTaus		= beanHelper->GetSelectedMCparticlesByPDGid(_BNmcparticles, tauIDs);
	BNmcparticleCollection status2taus	= beanHelper->GetSelectedMCparticlesByStatus(mcTaus, false, true,  false); 

	for(BNmcparticleCollection::const_iterator status2tau = status2taus.begin(); status2tau != status2taus.end(); ++status2tau){

		_NumGenTaus++;
		_MomentumRank	.push_back(_NumGenTaus-1);

		// Fill visGenTau info
		_Pt		.push_back(status2tau->pt);
		_Eta	.push_back(status2tau->eta);
		_Phi	.push_back(status2tau->phi);

		// Fill visGenTau info
		BNmcparticle visGenTau = beanHelper->GetVisGenTau(*status2tau, _BNmcparticles);
		_VisPt	.push_back(visGenTau.pt);
		_VisEta	.push_back(visGenTau.eta);
		_VisPhi	.push_back(visGenTau.phi);

		// Info about parent
		BNmcparticleCollection tauParents = beanHelper->GetParents(*status2tau,_BNmcparticles);
		_ParentId.push_back(tauParents.begin()->id);
		_ParentP.push_back(sqrt(pow(tauParents.begin()->px,2) + pow(tauParents.begin()->py,2) + pow(tauParents.begin()->pz,2)));
		_ParentPt.push_back(tauParents.begin()->pt);
		_ParentEta.push_back(tauParents.begin()->eta);
		_ParentPhi.push_back(tauParents.begin()->phi);

		// Fill decay mode
		if(abs(status2tau->daughter0Id) == 11 || abs(status2tau->daughter1Id) == 11){
			_ToElectron	.push_back(true);
			_ToMuon		.push_back(false);
			_ToHadrons	.push_back(false);
		}else if(abs(status2tau->daughter0Id) == 13 || abs(status2tau->daughter1Id) == 13){
			_ToElectron	.push_back(false);
			_ToMuon		.push_back(true);
			_ToHadrons	.push_back(false);
		}else{
			_ToElectron	.push_back(false);
			_ToMuon		.push_back(false);
			_ToHadrons	.push_back(true);
		}

	}

}
