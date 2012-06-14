// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/ElectronFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
ElectronFiller::ElectronFiller(const ParameterSet& iConfig): NtupleFiller(iConfig){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

ElectronFiller::ElectronFiller(const ParameterSet& iConfig, TTree* iTree) : NtupleFiller(iConfig) {
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
}

// === Clear vectors that will be used to fill ntuple === //
void ElectronFiller::ClearVectors(){

	_NumElectrons		=	0;	
	_MomentumRank		.clear();
	_ElectronPt	   		.clear();
	_ElectronEta   		.clear();
	_ElectronPhi   		.clear();

}

// === Fill ntuple === //
void ElectronFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();

	_NumElectrons = _patElectrons->size();
	for ( pat::ElectronCollection::const_iterator Electron = _patElectrons->begin(); Electron != _patElectrons->end(); ++Electron ) {
		_MomentumRank.push_back(_MomentumRank.size());
		_ElectronPt.push_back(Electron->pt());
		_ElectronEta.push_back(Electron->eta());
		_ElectronPhi.push_back(Electron->phi());
	}

}


//define this as a plug-in
DEFINE_FWK_MODULE(ElectronFiller);
