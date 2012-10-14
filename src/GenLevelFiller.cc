// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/GenLevelFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
GenLevelFiller::GenLevelFiller(const ParameterSet& iConfig): NtupleFiller(iConfig){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

GenLevelFiller::GenLevelFiller(const ParameterSet& iConfig, TTree* iTree) : NtupleFiller(iConfig) {
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
GenLevelFiller::~GenLevelFiller(){}

// ------------ method called to for each event  ------------
void GenLevelFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void GenLevelFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
}

// === Clear vectors that will be used to fill ntuple === //
void GenLevelFiller::ClearVectors(){


}

// === Fill ntuple === //
void GenLevelFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();

	if(_FromBEAN){
	
	}else{

	}


}


//define this as a plug-in
DEFINE_FWK_MODULE(GenLevelFiller);
