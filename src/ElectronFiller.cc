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

}

// === Fill ntuple === //
void ElectronFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();

	unsigned int theNumberOfElectrons = 0;

	BNelectronCollection selectedElectrons = _BNelectrons;

	_NumElectrons = selectedElectrons.size();
	theNumberOfElectrons = 0;
	for ( BNelectronCollection::const_iterator Electron = selectedElectrons.begin(); Electron != selectedElectrons.end(); ++Electron ) {
		theNumberOfElectrons++;

		_NumElectrons++;
		_MomentumRank.push_back(_MomentumRank.size());
		_ElectronPt.push_back(Electron->pt);
		_ElectronEta.push_back(Electron->eta);
		_ElectronPhi.push_back(Electron->phi);
		_ElectronRelIso.push_back(beanHelper.GetElectronRelIso(*Electron));
		_IsLooseElectron.push_back(beanHelper.IsLooseElectron(*Electron));
		_IsTightElectron.push_back(beanHelper.IsTightElectron(*Electron));
	}
}
