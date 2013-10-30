// vim: et:sta:sw=4:ts=4
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
    _Tree->Branch("J_CSV", &_JetCSV);
    _Tree->Branch("J_Charge", &_JetCharge);
    _Tree->Branch("J_PartonId", &_JetPartonId);
    _Tree->Branch("J_PartonParentId", &_JetPartonParentId);
    _Tree->Branch("J_PartonMother0Id", &_JetPartonMother0Id);
    _Tree->Branch("J_PartonMother1Id", &_JetPartonMother1Id);
    _Tree->Branch("J_PartonGrandParentId", &_JetPartonGrandParentId);
    _Tree->Branch("J_PartonGrandmother00Id", &_JetPartonGrandmother00Id);
    _Tree->Branch("J_PartonGrandmother01Id", &_JetPartonGrandmother01Id);
    _Tree->Branch("J_PartonGrandmother10Id", &_JetPartonGrandmother10Id);
    _Tree->Branch("J_PartonGrandmother11Id", &_JetPartonGrandmother11Id);
    _Tree->Branch("J_PartonStatus", &_JetPartonStatus);
    _Tree->Branch("J_PartonMother0Status", &_JetPartonMother0Status);
    _Tree->Branch("J_PartonMother1Status", &_JetPartonMother1Status);
    _Tree->Branch("J_PartonGrandmother00Status", &_JetPartonGrandmother00Status);
    _Tree->Branch("J_PartonGrandmother01Status", &_JetPartonGrandmother01Status);
    _Tree->Branch("J_PartonGrandmother10Status", &_JetPartonGrandmother10Status);
    _Tree->Branch("J_PartonGrandmother11Status", &_JetPartonGrandmother11Status);
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
    _JetCSV.clear();
    _JetCharge.clear();
    _JetPartonId.clear();
    _JetPartonParentId.clear();
    _JetPartonMother0Id.clear();
    _JetPartonMother1Id.clear();
    _JetPartonGrandParentId.clear();
    _JetPartonGrandmother00Id.clear();
    _JetPartonGrandmother01Id.clear();
    _JetPartonGrandmother10Id.clear();
    _JetPartonGrandmother11Id.clear();
    _JetPartonStatus.clear();
    _JetPartonMother0Status.clear();
    _JetPartonMother1Status.clear();
    _JetPartonGrandmother00Status.clear();
    _JetPartonGrandmother01Status.clear();
    _JetPartonGrandmother10Status.clear();
    _JetPartonGrandmother11Status.clear();
	_combSecVtxBTag			.clear();
	_combSecVtxLooseBTag	.clear();
	_combSecVtxMediumBTag	.clear();
	_combSecVtxTightBTag	.clear();

}

// === Fill ntuple === //
void JetFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();

	BNjetCollection correctedJets	= beanHelper->GetCorrectedJets(_BNjets, _sysType);
	BNjetCollection selCorrJets		= beanHelper->GetSelectedJets(correctedJets, 30, 2.4, jetID::jetLoose,'-');

    _JetCSV = beanHelper->GetCSVweights(selCorrJets, _sysType);

	_NumJets = selCorrJets.size();
	for ( BNjetCollection::const_iterator Jet = selCorrJets.begin(); Jet != selCorrJets.end(); ++Jet ) {
		_MomentumRank.push_back(_MomentumRank.size());
		_JetPt.push_back(Jet->pt);
		_JetEta.push_back(Jet->eta);
		_JetPhi.push_back(Jet->phi);
        _JetCharge.push_back(Jet->charge);

		_combSecVtxBTag			.push_back(Jet->btagCombinedSecVertex);
		_combSecVtxLooseBTag	.push_back(beanHelper->PassesCSV(*Jet, 'L'));
		_combSecVtxMediumBTag	.push_back(beanHelper->PassesCSV(*Jet, 'M'));
		_combSecVtxTightBTag	.push_back(beanHelper->PassesCSV(*Jet, 'T'));

        auto gen_match = beanHelper->GetMatchedMCparticle(_BNmcparticles, *Jet, 0.25);
        _JetPartonId.push_back(gen_match.id);
        _JetPartonMother0Id.push_back(gen_match.mother0Id);
        _JetPartonMother1Id.push_back(gen_match.mother1Id);
        _JetPartonGrandmother00Id.push_back(gen_match.grandMother00Id);
        _JetPartonGrandmother01Id.push_back(gen_match.grandMother01Id);
        _JetPartonGrandmother10Id.push_back(gen_match.grandMother10Id);
        _JetPartonGrandmother11Id.push_back(gen_match.grandMother11Id);
        _JetPartonStatus   .push_back(gen_match.status);
        _JetPartonMother0Status  .push_back(gen_match.mother0Status);
        _JetPartonMother1Status   .push_back(gen_match.mother1Status);
        _JetPartonGrandmother00Status.push_back(gen_match.grandMother00Status);
        _JetPartonGrandmother01Status.push_back(gen_match.grandMother01Status);
        _JetPartonGrandmother10Status.push_back(gen_match.grandMother10Status);
        _JetPartonGrandmother11Status.push_back(gen_match.grandMother11Status);

        auto parent = gen_match.mother0Id;
        if (parent == -99)
            parent = gen_match.mother1Id;
        _JetPartonParentId.push_back(parent);

        auto grandparent = gen_match.grandMother00Id;
        if (grandparent == -99)
            grandparent = gen_match.grandMother01Id;
        if (grandparent == -99)
            grandparent = gen_match.grandMother10Id;
        if (grandparent == -99)
            grandparent = gen_match.grandMother11Id;
        _JetPartonGrandParentId.push_back(grandparent);
	}
}
