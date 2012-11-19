// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/JetFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
JetFiller::JetFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

JetFiller::JetFiller(const ParameterSet& iConfig, TTree* iTree, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper) {
	_FillerName	= __FILE__;
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
JetFiller::~JetFiller(){}

// ------------ method called to for each event  ------------
void JetFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void JetFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("J_NumJets", &_NumJets);
	_Tree->Branch("J_MomentumRank", &_MomentumRank);
	_Tree->Branch("J_Pt", &_JetPt);
	_Tree->Branch("J_Eta", &_JetEta);
	_Tree->Branch("J_Phi", &_JetPhi);
	_Tree->Branch("J_combSecVtxBTag", &_combSecVtxBTag);
	_Tree->Branch("J_combSecVtxLooseBTag", &_combSecVtxLooseBTag);
	_Tree->Branch("J_combSecVtxMediumBTag", &_combSecVtxMediumBTag);
	_Tree->Branch("J_combSecVtxTightBTag", &_combSecVtxTightBTag);
}

// === Clear vectors that will be used to fill ntuple === //
void JetFiller::ClearVectors(){

	_NumJets				=	0;	
	_MomentumRank				.clear();
	_JetPt					.clear();
	_JetEta					.clear();
	_JetPhi					.clear();
	_combSecVtxBTag			.clear();
	_combSecVtxLooseBTag	.clear();
	_combSecVtxMediumBTag	.clear();
	_combSecVtxTightBTag	.clear();

}

// === Fill ntuple === //
void JetFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();

	unsigned int theNumberOfJets = 0;

	BNjetCollection correctedJets	= beanHelper->GetCorrectedJets(_BNjets);
	BNjetCollection selCorrJets		= beanHelper->GetSelectedJets(correctedJets, 30, 2.4, jetID::jetLoose,'-');

	_NumJets = selCorrJets.size();
	theNumberOfJets = 0;
	for ( BNjetCollection::const_iterator Jet = selCorrJets.begin(); Jet != selCorrJets.end(); ++Jet ) {
		theNumberOfJets++;

		_NumJets++;
		_MomentumRank.push_back(_MomentumRank.size());
		_JetPt.push_back(Jet->pt);
		_JetEta.push_back(Jet->eta);
		_JetPhi.push_back(Jet->phi);

		_combSecVtxBTag			.push_back(Jet->btagCombinedSecVertex);
		_combSecVtxLooseBTag	.push_back(beanHelper->PassesCSV(*Jet, 'L'));
		_combSecVtxMediumBTag	.push_back(beanHelper->PassesCSV(*Jet, 'M'));
		_combSecVtxTightBTag	.push_back(beanHelper->PassesCSV(*Jet, 'T'));
	}
}
