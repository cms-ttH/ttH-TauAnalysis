// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/GenJetFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
GenJetFiller::GenJetFiller(const ParameterSet& iConfig): NtupleFiller(iConfig){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

GenJetFiller::GenJetFiller(const ParameterSet& iConfig, TTree* iTree) : NtupleFiller(iConfig) {
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
GenJetFiller::~GenJetFiller(){}

// ------------ method called to for each event  ------------
void GenJetFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void GenJetFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("GJ_NumGenJets",&_NumGenJets);
	_Tree->Branch("GJ_MomentumRank", &_MomentumRank);
	_Tree->Branch("GJ_Pt", &_Pt);
	_Tree->Branch("GJ_Eta", &_Eta);
	_Tree->Branch("GJ_Phi", &_Phi);
	_Tree->Branch("GJ_IsBjet", &_IsBjet);

}

// === Clear vectors that will be used to fill ntuple === //
void GenJetFiller::ClearVectors(){

	_NumGenJets		= 0;	
	_MomentumRank	.clear();
	_Pt				.clear();
	_Eta			.clear();
	_Phi			.clear();
	_IsBjet			.clear();

}

// === Fill ntuple === //
void GenJetFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){

	// Only run this on MC
	if(_AnalysisType.compare("coll") == 0){ return; }

	GetCollections(iEvent, iSetup);
	ClearVectors();

	// Loop over all gen Jets looking for taus
	for(GenJetCollection::const_iterator genJet = _genJets->begin(); genJet != _genJets->end(); ++genJet){

		_NumGenJets++;
		_MomentumRank	.push_back(_NumGenJets-1);

		// Fill visGenJet info
		_Pt		.push_back(genJet->pt());
		_Eta	.push_back(genJet->eta());
		_Phi	.push_back(genJet->phi());

		 // Loop over all gen particles looking for b
		bool foundBquark = false;
		vector<const GenParticle*> genJetParticles = genJet->getGenConstituents();
		for(vector<const GenParticle*>::const_iterator genJetParticle = genJetParticles.begin(); genJetParticle != genJetParticles.end(); ++genJetParticle){
			const Candidate* mother = (*genJetParticle);
			do{
				if( abs(mother->pdgId()) == 5 ){ foundBquark = true; break; }
				mother = mother->mother(0);
			}while(mother != NULL);
			if(foundBquark){ break; }
		}

		_IsBjet	.push_back(foundBquark);

	}

}


//define this as a plug-in
DEFINE_FWK_MODULE(GenJetFiller);