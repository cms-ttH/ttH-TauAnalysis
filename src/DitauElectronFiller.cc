// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/DitauElectronFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
DitauElectronFiller::DitauElectronFiller(const ParameterSet& iConfig): NtupleFiller(iConfig){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

DitauElectronFiller::DitauElectronFiller(const ParameterSet& iConfig, TTree* iTree) : NtupleFiller(iConfig) {
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
DitauElectronFiller::~DitauElectronFiller(){}

// ------------ method called to for each event  ------------
void DitauElectronFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void DitauElectronFiller::SetupBranches(){

	// Set up tree branches
	_Tree->Branch("TTE_NumCombos",&_NumCombos);
	_Tree->Branch("TTE_ComboNumber",&_ComboNumber);
}

// === Clear vectors that will be used to fill ntuple === //
void DitauElectronFiller::ClearVectors(){

	_NumCombos			= 0;	
	_ComboNumber		.clear();

}

// === Fill ntuple === //
void DitauElectronFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();


}


//define this as a plug-in
DEFINE_FWK_MODULE(DitauElectronFiller);
