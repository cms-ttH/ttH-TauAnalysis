// Author: Nil Valls <nvallsve@nd.edu>

#include "HighMassAnalysis/Analysis/interface/DitauFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
DitauFiller::DitauFiller(const ParameterSet& iConfig): NtupleFiller(iConfig){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

DitauFiller::DitauFiller(const ParameterSet& iConfig, TTree* iTree) : NtupleFiller(iConfig) {
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
DitauFiller::~DitauFiller(){}

// ------------ method called to for each event  ------------
void DitauFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void DitauFiller::SetupBranches(){

	// Set up tree branches
	_Tree->Branch("TT_NumCombos",&_NumCombos);
	_Tree->Branch("TT_ComboNumber",&_ComboNumber);
}

// === Clear vectors that will be used to fill ntuple === //
void DitauFiller::ClearVectors(){

	_NumCombos			=	0;	
	_ComboNumber		.clear();

}

// === Fill ntuple === //
void DitauFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();


}


//define this as a plug-in
DEFINE_FWK_MODULE(DitauFiller);
