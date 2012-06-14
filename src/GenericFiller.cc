// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/GenericFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
GenericFiller::GenericFiller(const ParameterSet& iConfig): NtupleFiller(iConfig){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

GenericFiller::GenericFiller(const ParameterSet& iConfig, TTree* iTree) : NtupleFiller(iConfig) {
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
GenericFiller::~GenericFiller(){}

// ------------ method called to for each event  ------------
void GenericFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void GenericFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("NumCombos",&_NumCombos);
	_Tree->Branch("MomentumRank",&_MomentumRank);
}

// === Clear vectors that will be used to fill ntuple === //
void GenericFiller::ClearVectors(){

	_NumCombos			=	0;	
	_MomentumRank		.clear();

}

// === Fill ntuple === //
void GenericFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();


}


//define this as a plug-in
DEFINE_FWK_MODULE(GenericFiller);
