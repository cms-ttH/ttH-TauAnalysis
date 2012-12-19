// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/TauFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
TauFiller::TauFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

TauFiller::TauFiller(const ParameterSet& iConfig, TTree* iTree, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper) {
	_FillerName	= __FILE__;
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
TauFiller::~TauFiller(){}

// === Setup branches going into the ntuple === //
void TauFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("T_NumTaus",&_NumTaus);
	_Tree->Branch("T_MomentumRank",&_MomentumRank);
	_Tree->Branch("T_Pt",&_TauPt);
	_Tree->Branch("T_Eta",&_TauEta);
	_Tree->Branch("T_Phi",&_TauPhi);
	_Tree->Branch("T_NProngs", &_TauNProngs);
	_Tree->Branch("T_NSignalGammas", &_TauNSignalGammas);
	_Tree->Branch("T_NSignalNeutrals", &_TauNSignalNeutrals);
	_Tree->Branch("T_DecayMode", &_TauDecayMode);
	_Tree->Branch("T_EmFraction", &_TauEmFraction);
	_Tree->Branch("T_IsInTheCracks", &_TauIsInTheCracks);
	_Tree->Branch("T_HPSagainstElectronLoose", &_TauHPSagainstElectronLoose);
	_Tree->Branch("T_HPSagainstElectronMVA", &_TauHPSagainstElectronMVA);
	_Tree->Branch("T_HPSagainstElectronMedium", &_TauHPSagainstElectronMedium);
	_Tree->Branch("T_HPSagainstElectronTight", &_TauHPSagainstElectronTight);
	_Tree->Branch("T_HPSagainstMuonLoose", &_TauHPSagainstMuonLoose);
	_Tree->Branch("T_HPSagainstMuonMedium", &_TauHPSagainstMuonMedium);
	_Tree->Branch("T_HPSagainstMuonTight", &_TauHPSagainstMuonTight);
	_Tree->Branch("T_HPSbyLooseCombinedIsolationDeltaBetaCorr", &_TauHPSbyLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("T_HPSbyMediumCombinedIsolationDeltaBetaCorr", &_TauHPSbyMediumCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("T_HPSbyTightCombinedIsolationDeltaBetaCorr", &_TauHPSbyTightCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("T_HPSbyVLooseCombinedIsolationDeltaBetaCorr", &_TauHPSbyVLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("T_HPSdecayModeFinding", &_TauHPSdecayModeFinding);
	_Tree->Branch("T_LTPt", &_TauLTPt);
	_Tree->Branch("T_Charge", &_TauCharge);
	_Tree->Branch("T_LTvalid", &_TauLTvalid);
	_Tree->Branch("T_LTIpVtdxy", &_TauLTIpVtdxy);
	_Tree->Branch("T_LTIpVtdz", &_TauLTIpVtdz);
	_Tree->Branch("T_LTIpVtdxyError", &_TauLTIpVtdxyError);
	_Tree->Branch("T_LTIpVtdzError", &_TauLTIpVtdzError);
	_Tree->Branch("T_LTvx", &_TauLTvx);
	_Tree->Branch("T_LTvy", &_TauLTvy);
	_Tree->Branch("T_LTvz", &_TauLTvz);
	_Tree->Branch("T_LTValidHits", &_TauLTValidHits);
	_Tree->Branch("T_LTNormChiSqrd", &_TauLTNormChiSqrd);

	_Tree->Branch("T_TauGenMatchDaughter0Id", &_TauGenMatchDaughter0Id);
	_Tree->Branch("T_TauGenMatchDaughter1Id", &_TauGenMatchDaughter1Id);
	_Tree->Branch("T_TauGenMatchId", &_TauGenMatchId);
	_Tree->Branch("T_TauGenMatchMother0Id", &_TauGenMatchMother0Id);
	_Tree->Branch("T_TauGenMatchMother1Id", &_TauGenMatchMother1Id);
	_Tree->Branch("T_TauGenMatchGrandmother00Id", &_TauGenMatchGrandmother00Id);
	_Tree->Branch("T_TauGenMatchGrandmother01Id", &_TauGenMatchGrandmother01Id);
	_Tree->Branch("T_TauGenMatchGrandmother10Id", &_TauGenMatchGrandmother10Id);
	_Tree->Branch("T_TauGenMatchGrandmother11Id", &_TauGenMatchGrandmother11Id);
	_Tree->Branch("T_TauGenMatchDaughter0Status", &_TauGenMatchDaughter0Status);
	_Tree->Branch("T_TauGenMatchDaughter1Status", &_TauGenMatchDaughter1Status);
	_Tree->Branch("T_TauGenMatchStatus", &_TauGenMatchStatus);
	_Tree->Branch("T_TauGenMatchMother0Status", &_TauGenMatchMother0Status);
	_Tree->Branch("T_TauGenMatchMother1Status", &_TauGenMatchMother1Status);
	_Tree->Branch("T_TauGenMatchGrandmother00Status", &_TauGenMatchGrandmother00Status);
	_Tree->Branch("T_TauGenMatchGrandmother01Status", &_TauGenMatchGrandmother01Status);
	_Tree->Branch("T_TauGenMatchGrandmother10Status", &_TauGenMatchGrandmother10Status);
	_Tree->Branch("T_TauGenMatchGrandmother11Status", &_TauGenMatchGrandmother11Status);
}

// === Clear vectors that will be used to fill ntuple === //
void TauFiller::ClearVectors(){

	_NumTaus										=	0;	
	_MomentumRank									.clear();
	_TauPt											.clear();
	_TauEta											.clear();
	_TauPhi											.clear();
	_TauNProngs										.clear();
	_TauNSignalGammas								.clear();
	_TauNSignalNeutrals								.clear();
	_TauDecayMode									.clear();
	_TauEmFraction									.clear();
	_TauIsInTheCracks								.clear();
	_TauHPSagainstElectronLoose						.clear();
	_TauHPSagainstElectronMVA						.clear();
	_TauHPSagainstElectronMedium					.clear();
	_TauHPSagainstElectronTight						.clear();
	_TauHPSagainstMuonLoose							.clear();
	_TauHPSagainstMuonMedium						.clear();
	_TauHPSagainstMuonTight							.clear();
	_TauHPSbyLooseCombinedIsolationDeltaBetaCorr	.clear();
	_TauHPSbyMediumCombinedIsolationDeltaBetaCorr	.clear();
	_TauHPSbyTightCombinedIsolationDeltaBetaCorr	.clear();
	_TauHPSbyVLooseCombinedIsolationDeltaBetaCorr	.clear();
	_TauHPSdecayModeFinding							.clear();
	_TauLTPt										.clear();
	_TauCharge										.clear();
	_TauLTvalid										.clear();
	_TauLTIpVtdxy									.clear();
	_TauLTIpVtdz									.clear();
	_TauLTIpVtdxyError								.clear();
	_TauLTIpVtdzError								.clear();
	_TauLTvx										.clear();
	_TauLTvy										.clear();
	_TauLTvz										.clear();
	_TauLTValidHits									.clear();
	_TauLTNormChiSqrd								.clear();
	_TauGenMatchDaughter0Id							.clear();
	_TauGenMatchDaughter1Id							.clear();
	_TauGenMatchId									.clear();
	_TauGenMatchMother0Id							.clear();
	_TauGenMatchMother1Id							.clear();
	_TauGenMatchGrandmother00Id						.clear();
	_TauGenMatchGrandmother01Id						.clear();
	_TauGenMatchGrandmother10Id						.clear();
	_TauGenMatchGrandmother11Id						.clear();
	_TauGenMatchDaughter0Status	   					.clear();
	_TauGenMatchDaughter1Status	   					.clear();
	_TauGenMatchStatus			   					.clear();
	_TauGenMatchMother0Status	   					.clear();
	_TauGenMatchMother1Status	   					.clear();
	_TauGenMatchGrandmother00Status					.clear();
	_TauGenMatchGrandmother01Status					.clear();
	_TauGenMatchGrandmother10Status					.clear();
	_TauGenMatchGrandmother11Status					.clear();

}

// === Fill ntuple === //
void TauFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();

	unsigned int theNumberOfTaus = 0;

	BNtauCollection selectedTaus = _BNtaus;

	_NumTaus = selectedTaus.size();
	theNumberOfTaus = 0;
	for ( BNtauCollection::const_iterator Tau = selectedTaus.begin(); Tau != selectedTaus.end(); ++Tau ) {
		theNumberOfTaus++;

		_NumTaus++;
		_MomentumRank.push_back(_MomentumRank.size());
		_TauPt											.push_back(Tau->pt);
		_TauEta											.push_back(Tau->eta);
		_TauPhi											.push_back(Tau->phi);
		_TauNProngs										.push_back(Tau->numProngs);
		_TauNSignalGammas								.push_back(Tau->numSignalGammas);
		_TauNSignalNeutrals								.push_back(Tau->numSignalNeutrals);
		_TauDecayMode									.push_back(Tau->decayMode);
		_TauEmFraction									.push_back(Tau->emFraction);
		_TauIsInTheCracks								.push_back(Tau->inTheCracks);
		_TauHPSagainstElectronMVA						.push_back(Tau->HPSagainstElectronMVA);
		_TauHPSagainstElectronLoose						.push_back(Tau->HPSagainstElectronLoose);
		_TauHPSagainstElectronMedium					.push_back(Tau->HPSagainstElectronMedium);
		_TauHPSagainstElectronTight						.push_back(Tau->HPSagainstElectronTight);
		_TauHPSagainstMuonLoose							.push_back(Tau->HPSagainstMuonLoose);
		_TauHPSagainstMuonMedium						.push_back(Tau->HPSagainstMuonMedium);
		_TauHPSagainstMuonTight							.push_back(Tau->HPSagainstMuonTight);
		_TauHPSbyVLooseCombinedIsolationDeltaBetaCorr	.push_back(Tau->HPSbyVLooseCombinedIsolationDeltaBetaCorr);
		_TauHPSbyLooseCombinedIsolationDeltaBetaCorr	.push_back(Tau->HPSbyLooseCombinedIsolationDeltaBetaCorr);
		_TauHPSbyMediumCombinedIsolationDeltaBetaCorr	.push_back(Tau->HPSbyMediumCombinedIsolationDeltaBetaCorr);
		_TauHPSbyTightCombinedIsolationDeltaBetaCorr	.push_back(Tau->HPSbyTightCombinedIsolationDeltaBetaCorr);
		_TauHPSdecayModeFinding							.push_back(Tau->HPSdecayModeFinding);

		// Leading track variables
		_TauLTPt			.push_back(Tau->leadingTrackPt);
		_TauCharge			.push_back(Tau->charge);
		_TauLTvalid			.push_back(Tau->leadingTrackValid);
		_TauLTIpVtdxy		.push_back(Tau->leadingTrackIpVtdxy);
		_TauLTIpVtdz		.push_back(Tau->leadingTrackIpVtdz);
		_TauLTIpVtdxyError	.push_back(Tau->leadingTrackIpVtdxyError);
		_TauLTIpVtdzError	.push_back(Tau->leadingTrackIpVtdzError);
		_TauLTvx			.push_back(Tau->leadingTrackVx);
		_TauLTvy			.push_back(Tau->leadingTrackVy);
		_TauLTvz			.push_back(Tau->leadingTrackVz);
		_TauLTValidHits		.push_back(Tau->leadingTrackValidHits);
		_TauLTNormChiSqrd	.push_back(Tau->leadingTrackNormChiSqrd);

		// Provenance
		BNmcparticle tauGenMatch = beanHelper->GetMatchedMCparticle(_BNmcparticles, *Tau, 0.25);
		_TauGenMatchDaughter0Id			.push_back(tauGenMatch.daughter0Id);
		_TauGenMatchDaughter1Id			.push_back(tauGenMatch.daughter1Id);
		_TauGenMatchId					.push_back(tauGenMatch.id);
		_TauGenMatchMother0Id			.push_back(tauGenMatch.mother0Id);
		_TauGenMatchMother1Id			.push_back(tauGenMatch.mother1Id);
		_TauGenMatchGrandmother00Id		.push_back(tauGenMatch.grandMother00Id);
		_TauGenMatchGrandmother01Id		.push_back(tauGenMatch.grandMother01Id);
		_TauGenMatchGrandmother10Id		.push_back(tauGenMatch.grandMother10Id);
		_TauGenMatchGrandmother11Id		.push_back(tauGenMatch.grandMother11Id);
		_TauGenMatchDaughter0Status	   	.push_back(tauGenMatch.daughter0Status);
		_TauGenMatchDaughter1Status	   	.push_back(tauGenMatch.daughter1Status);
		_TauGenMatchStatus			   	.push_back(tauGenMatch.status);
		_TauGenMatchMother0Status	  	.push_back(tauGenMatch.mother0Status);
		_TauGenMatchMother1Status	   	.push_back(tauGenMatch.mother1Status);
		_TauGenMatchGrandmother00Status	.push_back(tauGenMatch.grandMother00Status);
		_TauGenMatchGrandmother01Status	.push_back(tauGenMatch.grandMother01Status);
		_TauGenMatchGrandmother10Status	.push_back(tauGenMatch.grandMother10Status);
		_TauGenMatchGrandmother11Status	.push_back(tauGenMatch.grandMother11Status);
	}
}
