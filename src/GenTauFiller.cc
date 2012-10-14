// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/GenTauFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
GenTauFiller::GenTauFiller(const ParameterSet& iConfig): NtupleFiller(iConfig){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

GenTauFiller::GenTauFiller(const ParameterSet& iConfig, TTree* iTree) : NtupleFiller(iConfig) {
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

	if(_FromBEAN){
	
	}else{
		// Loop over all gen particles looking for taus
		for(GenParticleCollection::const_iterator genParticle = _genParticles->begin(); genParticle != _genParticles->end(); ++genParticle){

			// Only care for taus
			if((abs(genParticle->pdgId()) != 15) || (genParticle->status() == 3)){ continue; }

			_NumGenTaus++;
			_MomentumRank	.push_back(_NumGenTaus-1);
			reco::Candidate::LorentzVector visGenTau = genParticle->p4();

			// Fill visGenTau info
			_Pt		.push_back(genParticle->pt());
			_Eta	.push_back(genParticle->eta());
			_Phi	.push_back(genParticle->phi());

			// Figure out info about parent
			const reco::Candidate* parent;
			if(genParticle->mother(0)->pdgId() == genParticle->pdgId()){	parent = genParticle->mother(0)->mother(0);	}
			else{															parent = genParticle->mother(0);			}
			_ParentId.push_back(parent->pdgId());
			_ParentP.push_back(parent->p());
			_ParentPt.push_back(parent->pt());
			_ParentEta.push_back(parent->eta());
			_ParentPhi.push_back(parent->phi());

			// Examine number of neutrinos
			bool foundElectron	= false;
			bool foundMuon		= false;
			for( unsigned int i=0; i < (genParticle->numberOfDaughters()); i++) {
				const reco::Candidate* daughterCand = genParticle->daughter(i);

				// Figure out the decay mode
				if( abs(daughterCand->pdgId()) == 12 ){ foundElectron	= true; }    
				if( abs(daughterCand->pdgId()) == 14 ){ foundMuon		= true; }    

				// Obtain visible momentum by subtracting the p4 of neutrinos
				if( (abs(daughterCand->pdgId()) == 12) || (abs(daughterCand->pdgId()) == 14) || (abs(daughterCand->pdgId()) == 16) ) {
					visGenTau = visGenTau - daughterCand->p4();
				}    
			}    

			// Fill decay mode
			if(foundElectron){
				_ToElectron	.push_back(true);
				_ToMuon		.push_back(false);
				_ToHadrons	.push_back(false);
			}else if(foundMuon){
				_ToElectron	.push_back(false);
				_ToMuon		.push_back(true);
				_ToHadrons	.push_back(false);
			}else{
				_ToElectron	.push_back(false);
				_ToMuon		.push_back(false);
				_ToHadrons	.push_back(true);
			}

			// Fill visGenTau info
			_VisPt	.push_back(visGenTau.pt());
			_VisEta	.push_back(visGenTau.eta());
			_VisPhi	.push_back(visGenTau.phi());

		}
	}

}


//define this as a plug-in
DEFINE_FWK_MODULE(GenTauFiller);
