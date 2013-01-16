// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/DitauMuonFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
DitauMuonFiller::DitauMuonFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

DitauMuonFiller::DitauMuonFiller(const ParameterSet& iConfig, TTree* iTree, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper) {
	_FillerName	= __FILE__;
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
DitauMuonFiller::~DitauMuonFiller(){}

// ------------ method called to for each event  ------------
void DitauMuonFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void DitauMuonFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("TTM_NumTaus",&_NumTaus);
	_Tree->Branch("TTM_NumMuons",&_NumMuons);
	_Tree->Branch("TTM_NumCombos",&_NumCombos);
	_Tree->Branch("TTM_MomentumRank",&_MomentumRank);

	// === Tau1 === //
	_Tree->Branch("TTM_Tau1MomentumRank", &_Tau1MomentumRank);
	_Tree->Branch("TTM_Tau1Pt", &_Tau1Pt);
	_Tree->Branch("TTM_Tau1Eta", &_Tau1Eta);
	_Tree->Branch("TTM_Tau1Phi", &_Tau1Phi);
	_Tree->Branch("TTM_Tau1NProngs", &_Tau1NProngs);
	_Tree->Branch("TTM_Tau1NSignalGammas", &_Tau1NSignalGammas);
	_Tree->Branch("TTM_Tau1NSignalNeutrals", &_Tau1NSignalNeutrals);
	_Tree->Branch("TTM_Tau1DecayMode", &_Tau1DecayMode);
	_Tree->Branch("TTM_Tau1EmFraction", &_Tau1EmFraction);
	_Tree->Branch("TTM_Tau1IsInTheCracks", &_Tau1IsInTheCracks);
	_Tree->Branch("TTM_Tau1HPSagainstElectronLoose", &_Tau1HPSagainstElectronLoose);
	_Tree->Branch("TTM_Tau1HPSagainstElectronMVA", &_Tau1HPSagainstElectronMVA);
	_Tree->Branch("TTM_Tau1HPSagainstElectronMedium", &_Tau1HPSagainstElectronMedium);
	_Tree->Branch("TTM_Tau1HPSagainstElectronTight", &_Tau1HPSagainstElectronTight);
	_Tree->Branch("TTM_Tau1HPSagainstMuonLoose", &_Tau1HPSagainstMuonLoose);
	_Tree->Branch("TTM_Tau1HPSagainstMuonMedium", &_Tau1HPSagainstMuonMedium);
	_Tree->Branch("TTM_Tau1HPSagainstMuonTight", &_Tau1HPSagainstMuonTight);
	_Tree->Branch("TTM_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTM_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTM_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTM_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTM_Tau1HPSdecayModeFinding", &_Tau1HPSdecayModeFinding);
	_Tree->Branch("TTM_Tau1LTPt", &_Tau1LTPt);
	_Tree->Branch("TTM_Tau1Charge", &_Tau1Charge);
	_Tree->Branch("TTM_Tau1LTvalid", &_Tau1LTvalid);
	_Tree->Branch("TTM_Tau1LTIpVtdxy", &_Tau1LTIpVtdxy);
	_Tree->Branch("TTM_Tau1LTIpVtdz", &_Tau1LTIpVtdz);
	_Tree->Branch("TTM_Tau1LTIpVtdxyError", &_Tau1LTIpVtdxyError);
	_Tree->Branch("TTM_Tau1LTIpVtdzError", &_Tau1LTIpVtdzError);
	_Tree->Branch("TTM_Tau1LTvx", &_Tau1LTvx);
	_Tree->Branch("TTM_Tau1LTvy", &_Tau1LTvy);
	_Tree->Branch("TTM_Tau1LTvz", &_Tau1LTvz);
	_Tree->Branch("TTM_Tau1LTValidHits", &_Tau1LTValidHits);
	_Tree->Branch("TTM_Tau1LTNormChiSqrd", &_Tau1LTNormChiSqrd);
	_Tree->Branch("TTM_Tau1MatchesGenHadTauFromH1", &_Tau1MatchesGenHadTauFromH1);
	_Tree->Branch("TTM_Tau1MatchesGenHadTauFromH2", &_Tau1MatchesGenHadTauFromH2);
	_Tree->Branch("TTM_Tau1MatchesGenHadTauFromW1", &_Tau1MatchesGenHadTauFromW1);
	_Tree->Branch("TTM_Tau1MatchesGenHadTauFromW2", &_Tau1MatchesGenHadTauFromW2);

	_Tree->Branch("TTM_Tau1GenMatchDaughter0Id", &_Tau1GenMatchDaughter0Id);
	_Tree->Branch("TTM_Tau1GenMatchDaughter1Id", &_Tau1GenMatchDaughter1Id);
	_Tree->Branch("TTM_Tau1GenMatchId", &_Tau1GenMatchId);
	_Tree->Branch("TTM_Tau1GenMatchMother0Id", &_Tau1GenMatchMother0Id);
	_Tree->Branch("TTM_Tau1GenMatchMother1Id", &_Tau1GenMatchMother1Id);
	_Tree->Branch("TTM_Tau1GenMatchGrandmother00Id", &_Tau1GenMatchGrandmother00Id);
	_Tree->Branch("TTM_Tau1GenMatchGrandmother01Id", &_Tau1GenMatchGrandmother01Id);
	_Tree->Branch("TTM_Tau1GenMatchGrandmother10Id", &_Tau1GenMatchGrandmother10Id);
	_Tree->Branch("TTM_Tau1GenMatchGrandmother11Id", &_Tau1GenMatchGrandmother11Id);
	_Tree->Branch("TTM_Tau1GenMatchDaughter0Status", &_Tau1GenMatchDaughter0Status);
	_Tree->Branch("TTM_Tau1GenMatchDaughter1Status", &_Tau1GenMatchDaughter1Status);
	_Tree->Branch("TTM_Tau1GenMatchStatus", &_Tau1GenMatchStatus);
	_Tree->Branch("TTM_Tau1GenMatchMother0Status", &_Tau1GenMatchMother0Status);
	_Tree->Branch("TTM_Tau1GenMatchMother1Status", &_Tau1GenMatchMother1Status);
	_Tree->Branch("TTM_Tau1GenMatchGrandmother00Status", &_Tau1GenMatchGrandmother00Status);
	_Tree->Branch("TTM_Tau1GenMatchGrandmother01Status", &_Tau1GenMatchGrandmother01Status);
	_Tree->Branch("TTM_Tau1GenMatchGrandmother10Status", &_Tau1GenMatchGrandmother10Status);
	_Tree->Branch("TTM_Tau1GenMatchGrandmother11Status", &_Tau1GenMatchGrandmother11Status);

	// === Tau2 === //
	_Tree->Branch("TTM_Tau2MomentumRank", &_Tau2MomentumRank);
	_Tree->Branch("TTM_Tau2Pt", &_Tau2Pt);
	_Tree->Branch("TTM_Tau2Eta", &_Tau2Eta);
	_Tree->Branch("TTM_Tau2Phi", &_Tau2Phi);
	_Tree->Branch("TTM_Tau2NProngs", &_Tau2NProngs);
	_Tree->Branch("TTM_Tau2NSignalGammas", &_Tau2NSignalGammas);
	_Tree->Branch("TTM_Tau2NSignalNeutrals", &_Tau2NSignalNeutrals);
	_Tree->Branch("TTM_Tau2DecayMode", &_Tau2DecayMode);
	_Tree->Branch("TTM_Tau2EmFraction", &_Tau2EmFraction);
	_Tree->Branch("TTM_Tau2IsInTheCracks", &_Tau2IsInTheCracks);
	_Tree->Branch("TTM_Tau2HPSagainstElectronLoose", &_Tau2HPSagainstElectronLoose);
	_Tree->Branch("TTM_Tau2HPSagainstElectronMVA", &_Tau2HPSagainstElectronMVA);
	_Tree->Branch("TTM_Tau2HPSagainstElectronMedium", &_Tau2HPSagainstElectronMedium);
	_Tree->Branch("TTM_Tau2HPSagainstElectronTight", &_Tau2HPSagainstElectronTight);
	_Tree->Branch("TTM_Tau2HPSagainstMuonLoose", &_Tau2HPSagainstMuonLoose);
	_Tree->Branch("TTM_Tau2HPSagainstMuonMedium", &_Tau2HPSagainstMuonMedium);
	_Tree->Branch("TTM_Tau2HPSagainstMuonTight", &_Tau2HPSagainstMuonTight);
	_Tree->Branch("TTM_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTM_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTM_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTM_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTM_Tau2HPSdecayModeFinding", &_Tau2HPSdecayModeFinding);
	_Tree->Branch("TTM_Tau2LTPt", &_Tau2LTPt);
	_Tree->Branch("TTM_Tau2Charge", &_Tau2Charge);
	_Tree->Branch("TTM_Tau2LTvalid", &_Tau2LTvalid);
	_Tree->Branch("TTM_Tau2LTIpVtdxy", &_Tau2LTIpVtdxy);
	_Tree->Branch("TTM_Tau2LTIpVtdz", &_Tau2LTIpVtdz);
	_Tree->Branch("TTM_Tau2LTIpVtdxyError", &_Tau2LTIpVtdxyError);
	_Tree->Branch("TTM_Tau2LTIpVtdzError", &_Tau2LTIpVtdzError);
	_Tree->Branch("TTM_Tau2LTvx", &_Tau2LTvx);
	_Tree->Branch("TTM_Tau2LTvy", &_Tau2LTvy);
	_Tree->Branch("TTM_Tau2LTvz", &_Tau2LTvz);
	_Tree->Branch("TTM_Tau2LTValidHits", &_Tau2LTValidHits);
	_Tree->Branch("TTM_Tau2LTNormChiSqrd", &_Tau2LTNormChiSqrd);
	_Tree->Branch("TTM_Tau2MatchesGenHadTauFromH1", &_Tau2MatchesGenHadTauFromH1);
	_Tree->Branch("TTM_Tau2MatchesGenHadTauFromH2", &_Tau2MatchesGenHadTauFromH2);
	_Tree->Branch("TTM_Tau2MatchesGenHadTauFromW1", &_Tau2MatchesGenHadTauFromW1);
	_Tree->Branch("TTM_Tau2MatchesGenHadTauFromW2", &_Tau2MatchesGenHadTauFromW2);

	_Tree->Branch("TTM_Tau2GenMatchDaughter0Id", &_Tau2GenMatchDaughter0Id);
	_Tree->Branch("TTM_Tau2GenMatchDaughter1Id", &_Tau2GenMatchDaughter1Id);
	_Tree->Branch("TTM_Tau2GenMatchId", &_Tau2GenMatchId);
	_Tree->Branch("TTM_Tau2GenMatchMother0Id", &_Tau2GenMatchMother0Id);
	_Tree->Branch("TTM_Tau2GenMatchMother1Id", &_Tau2GenMatchMother1Id);
	_Tree->Branch("TTM_Tau2GenMatchGrandmother00Id", &_Tau2GenMatchGrandmother00Id);
	_Tree->Branch("TTM_Tau2GenMatchGrandmother01Id", &_Tau2GenMatchGrandmother01Id);
	_Tree->Branch("TTM_Tau2GenMatchGrandmother10Id", &_Tau2GenMatchGrandmother10Id);
	_Tree->Branch("TTM_Tau2GenMatchGrandmother11Id", &_Tau2GenMatchGrandmother11Id);
	_Tree->Branch("TTM_Tau2GenMatchDaughter0Status", &_Tau2GenMatchDaughter0Status);
	_Tree->Branch("TTM_Tau2GenMatchDaughter1Status", &_Tau2GenMatchDaughter1Status);
	_Tree->Branch("TTM_Tau2GenMatchStatus", &_Tau2GenMatchStatus);
	_Tree->Branch("TTM_Tau2GenMatchMother0Status", &_Tau2GenMatchMother0Status);
	_Tree->Branch("TTM_Tau2GenMatchMother1Status", &_Tau2GenMatchMother1Status);
	_Tree->Branch("TTM_Tau2GenMatchGrandmother00Status", &_Tau2GenMatchGrandmother00Status);
	_Tree->Branch("TTM_Tau2GenMatchGrandmother01Status", &_Tau2GenMatchGrandmother01Status);
	_Tree->Branch("TTM_Tau2GenMatchGrandmother10Status", &_Tau2GenMatchGrandmother10Status);
	_Tree->Branch("TTM_Tau2GenMatchGrandmother11Status", &_Tau2GenMatchGrandmother11Status);

	// === Muon === //
	_Tree->Branch("TTM_MuonMomentumRank", &_MuonMomentumRank);
	_Tree->Branch("TTM_MuonPt", &_MuonPt);
	_Tree->Branch("TTM_MuonEta", &_MuonEta);
	_Tree->Branch("TTM_MuonPhi", &_MuonPhi);
	_Tree->Branch("TTM_MuonRelIso", &_MuonRelIso);
	_Tree->Branch("TTM_MuonIsLooseMuon", &_MuonIsLooseMuon);
	_Tree->Branch("TTM_MuonIsTightMuon", &_MuonIsTightMuon);
	_Tree->Branch("TTM_MuonGenMatchDaughter0Id", &_MuonGenMatchDaughter0Id);
	_Tree->Branch("TTM_MuonGenMatchDaughter1Id", &_MuonGenMatchDaughter1Id);
	_Tree->Branch("TTM_MuonGenMatchId", &_MuonGenMatchId);
	_Tree->Branch("TTM_MuonGenMatchMother0Id", &_MuonGenMatchMother0Id);
	_Tree->Branch("TTM_MuonGenMatchMother1Id", &_MuonGenMatchMother1Id);
	_Tree->Branch("TTM_MuonGenMatchGrandmother00Id", &_MuonGenMatchGrandmother00Id);
	_Tree->Branch("TTM_MuonGenMatchGrandmother01Id", &_MuonGenMatchGrandmother01Id);
	_Tree->Branch("TTM_MuonGenMatchGrandmother10Id", &_MuonGenMatchGrandmother10Id);
	_Tree->Branch("TTM_MuonGenMatchGrandmother11Id", &_MuonGenMatchGrandmother11Id);
	_Tree->Branch("TTM_MuonGenMatchDaughter0Status", &_MuonGenMatchDaughter0Status);
	_Tree->Branch("TTM_MuonGenMatchDaughter1Status", &_MuonGenMatchDaughter1Status);
	_Tree->Branch("TTM_MuonGenMatchStatus", &_MuonGenMatchStatus);
	_Tree->Branch("TTM_MuonGenMatchMother0Status", &_MuonGenMatchMother0Status);
	_Tree->Branch("TTM_MuonGenMatchMother1Status", &_MuonGenMatchMother1Status);
	_Tree->Branch("TTM_MuonGenMatchGrandmother00Status", &_MuonGenMatchGrandmother00Status);
	_Tree->Branch("TTM_MuonGenMatchGrandmother01Status", &_MuonGenMatchGrandmother01Status);
	_Tree->Branch("TTM_MuonGenMatchGrandmother10Status", &_MuonGenMatchGrandmother10Status);
	_Tree->Branch("TTM_MuonGenMatchGrandmother11Status", &_MuonGenMatchGrandmother11Status);

	// === Combo === //
	_Tree->Branch("TTM_DitauVisibleMass", &_DitauVisibleMass);
	_Tree->Branch("TTM_DitauMETMass", &_DitauMETMass);
	_Tree->Branch("TTM_DitauCosDeltaPhi", &_DitauCosDeltaPhi);
	_Tree->Branch("TTM_DitauDeltaR", 	&_DitauDeltaR);
	_Tree->Branch("TTM_Tau1MuonDeltaR", &_Tau1MuonDeltaR);
	_Tree->Branch("TTM_Tau2MuonDeltaR", &_Tau2MuonDeltaR);
	_Tree->Branch("TTM_HT", &_HT);
	_Tree->Branch("TTM_NumCSVLbtagJets", &_NumCSVLbtagJets);
	_Tree->Branch("TTM_NumCSVMbtagJets", &_NumCSVMbtagJets);
	_Tree->Branch("TTM_NumCSVTbtagJets", &_NumCSVTbtagJets);
	_Tree->Branch("TTM_NumNonCSVLbtagJets", &_NumNonCSVLbtagJets);
	_Tree->Branch("TTM_NumNonCSVMbtagJets", &_NumNonCSVMbtagJets);
	_Tree->Branch("TTM_NumNonCSVTbtagJets", &_NumNonCSVTbtagJets);
}

// === Clear vectors that will be used to fill ntuple === //
void DitauMuonFiller::ClearVectors(){

	_NumTaus										= 0;
	_NumMuons										= 0;
	_NumCombos										= 0;	
	_MomentumRank									.clear();

	// === Tau1 === //
	_Tau1MomentumRank								.clear();
	_Tau1Pt											.clear();
	_Tau1Eta										.clear();
	_Tau1Phi										.clear();
	_Tau1NProngs									.clear();
	_Tau1NSignalGammas								.clear();
	_Tau1NSignalNeutrals							.clear();
	_Tau1DecayMode									.clear();
	_Tau1EmFraction									.clear();
	_Tau1IsInTheCracks								.clear();
	_Tau1HPSagainstElectronLoose					.clear();
	_Tau1HPSagainstElectronMVA						.clear();
	_Tau1HPSagainstElectronMedium					.clear();
	_Tau1HPSagainstElectronTight					.clear();
	_Tau1HPSagainstMuonLoose						.clear();
	_Tau1HPSagainstMuonMedium						.clear();
	_Tau1HPSagainstMuonTight						.clear();
	_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr	.clear();
	_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr	.clear();
	_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr	.clear();
	_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr	.clear();
	_Tau1HPSdecayModeFinding						.clear();
	_Tau1LTPt										.clear();
	_Tau1Charge										.clear();
	_Tau1LTvalid									.clear();
	_Tau1LTIpVtdxy									.clear();
	_Tau1LTIpVtdz									.clear();
	_Tau1LTIpVtdxyError								.clear();
	_Tau1LTIpVtdzError								.clear();
	_Tau1LTvx										.clear();
	_Tau1LTvy										.clear();
	_Tau1LTvz										.clear();
	_Tau1LTValidHits								.clear();
	_Tau1LTNormChiSqrd								.clear();
	_Tau1MatchesGenHadTauFromH1						.clear();
	_Tau1MatchesGenHadTauFromH2						.clear();
	_Tau1MatchesGenHadTauFromW1						.clear();
	_Tau1MatchesGenHadTauFromW2						.clear();
	_Tau1GenMatchDaughter0Id						.clear();
	_Tau1GenMatchDaughter1Id						.clear();
	_Tau1GenMatchId									.clear();
	_Tau1GenMatchMother0Id							.clear();
	_Tau1GenMatchMother1Id							.clear();
	_Tau1GenMatchGrandmother00Id					.clear();
	_Tau1GenMatchGrandmother01Id					.clear();
	_Tau1GenMatchGrandmother10Id					.clear();
	_Tau1GenMatchGrandmother11Id					.clear();
	_Tau1GenMatchDaughter0Status					.clear();
	_Tau1GenMatchDaughter1Status					.clear();
	_Tau1GenMatchStatus								.clear();
	_Tau1GenMatchMother0Status						.clear();
	_Tau1GenMatchMother1Status						.clear();
	_Tau1GenMatchGrandmother00Status				.clear();
	_Tau1GenMatchGrandmother01Status				.clear();
	_Tau1GenMatchGrandmother10Status				.clear();
	_Tau1GenMatchGrandmother11Status				.clear();

	// === Tau2 === //
	_Tau2MomentumRank								.clear();
	_Tau2Pt											.clear();
	_Tau2Eta										.clear();
	_Tau2Phi										.clear();
	_Tau2NProngs									.clear();
	_Tau2NSignalGammas								.clear();
	_Tau2NSignalNeutrals							.clear();
	_Tau2DecayMode									.clear();
	_Tau2EmFraction									.clear();
	_Tau2IsInTheCracks								.clear();
	_Tau2HPSagainstElectronLoose					.clear();
	_Tau2HPSagainstElectronMVA						.clear();
	_Tau2HPSagainstElectronMedium					.clear();
	_Tau2HPSagainstElectronTight					.clear();
	_Tau2HPSagainstMuonLoose						.clear();
	_Tau2HPSagainstMuonMedium						.clear();
	_Tau2HPSagainstMuonTight						.clear();
	_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr	.clear();
	_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr	.clear();
	_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr	.clear();
	_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr	.clear();
	_Tau2HPSdecayModeFinding						.clear();
	_Tau2LTPt										.clear();
	_Tau2Charge										.clear();
	_Tau2LTvalid									.clear();
	_Tau2LTIpVtdxy									.clear();
	_Tau2LTIpVtdz									.clear();
	_Tau2LTIpVtdxyError								.clear();
	_Tau2LTIpVtdzError								.clear();
	_Tau2LTvx										.clear();
	_Tau2LTvy										.clear();
	_Tau2LTvz										.clear();
	_Tau2LTValidHits								.clear();
	_Tau2LTNormChiSqrd								.clear();
	_Tau2MatchesGenHadTauFromH1						.clear();
	_Tau2MatchesGenHadTauFromH2						.clear();
	_Tau2MatchesGenHadTauFromW1						.clear();
	_Tau2MatchesGenHadTauFromW2						.clear();
	_Tau2GenMatchDaughter0Id						.clear();
	_Tau2GenMatchDaughter1Id						.clear();
	_Tau2GenMatchId									.clear();
	_Tau2GenMatchMother0Id							.clear();
	_Tau2GenMatchMother1Id							.clear();
	_Tau2GenMatchGrandmother00Id					.clear();
	_Tau2GenMatchGrandmother01Id					.clear();
	_Tau2GenMatchGrandmother10Id					.clear();
	_Tau2GenMatchGrandmother11Id					.clear();
	_Tau2GenMatchDaughter0Status					.clear();
	_Tau2GenMatchDaughter1Status					.clear();
	_Tau2GenMatchStatus								.clear();
	_Tau2GenMatchMother0Status						.clear();
	_Tau2GenMatchMother1Status						.clear();
	_Tau2GenMatchGrandmother00Status				.clear();
	_Tau2GenMatchGrandmother01Status				.clear();
	_Tau2GenMatchGrandmother10Status				.clear();
	_Tau2GenMatchGrandmother11Status				.clear();

	// === Muon === //
	_MuonMomentumRank								.clear();
	_MuonPt											.clear();
	_MuonEta										.clear();
	_MuonPhi										.clear();
    _MuonRelIso                                     .clear();
    _MuonIsTightMuon                                .clear();
    _MuonIsLooseMuon                                .clear();
	_MuonGenMatchDaughter0Id						.clear();
	_MuonGenMatchDaughter1Id						.clear();
	_MuonGenMatchId									.clear();
	_MuonGenMatchMother0Id							.clear();
	_MuonGenMatchMother1Id							.clear();
	_MuonGenMatchGrandmother00Id					.clear();
	_MuonGenMatchGrandmother01Id					.clear();
	_MuonGenMatchGrandmother10Id					.clear();
	_MuonGenMatchGrandmother11Id					.clear();
	_MuonGenMatchDaughter0Status					.clear();
	_MuonGenMatchDaughter1Status					.clear();
	_MuonGenMatchStatus								.clear();
	_MuonGenMatchMother0Status						.clear();
	_MuonGenMatchMother1Status						.clear();
	_MuonGenMatchGrandmother00Status				.clear();
	_MuonGenMatchGrandmother01Status				.clear();
	_MuonGenMatchGrandmother10Status				.clear();
	_MuonGenMatchGrandmother11Status				.clear();

	// === Combo === //
	_DitauVisibleMass								.clear();
	_DitauMETMass									.clear();
	_DitauCosDeltaPhi								.clear();
	_DitauDeltaR									.clear();
	_Tau1MuonDeltaR									.clear();
	_Tau2MuonDeltaR									.clear();
	_HT												.clear();
	_NumCSVLbtagJets								.clear();
	_NumCSVMbtagJets								.clear();
	_NumCSVTbtagJets								.clear();
	_NumNonCSVLbtagJets								.clear();
	_NumNonCSVMbtagJets								.clear();
	_NumNonCSVTbtagJets								.clear();

}

// === Fill ntuple === //
void DitauMuonFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){

	// Get the object collections from the event
	GetCollections(iEvent, iSetup);

	// Clear vectors
	ClearVectors();

	// Select muons (tight)
	BNmuonCollection selectedMuons = beanHelper->GetSelectedMuons(_BNmuons, muonID::muonTight);

	if(_BNtaus.size() < 2 || selectedMuons.size() < 1){ return; }

	// Tau provenance
	BNmcparticleCollection genTaus	= beanHelper->GetHadronicGenTaus(_BNmcparticles);
	BNmcparticle			genTau1FromH, genTau2FromH, genTau1FromW, genTau2FromW;

	// From H
	for(BNmcparticleCollection::const_iterator genTau = genTaus.begin(); genTau != genTaus.end(); ++genTau){
		//cout << "gentau mother id: " << genTau->motherId << "   " << genTau->grandMotherId << endl;
		if((genTau->mother0Id==25) || (genTau->mother1Id==25)){
			if(genTau->pt > genTau1FromH.pt){ 
				genTau2FromH = genTau1FromH;
				genTau1FromH = *genTau;
				//cout << "GOT IT!" << endl;
			}
			if(genTau2FromH.pt > 0){ break; }
		}
	}
	// From ttbar system
	for(BNmcparticleCollection::const_iterator genTau = genTaus.begin(); genTau != genTaus.end(); ++genTau){
		if(((abs(genTau->mother0Id)==24) || (abs(genTau->mother1Id)==24)) && 
			((abs(genTau->grandMother00Id)==6) || (abs(genTau->grandMother01Id)==6) || (abs(genTau->grandMother10Id)==6) || (abs(genTau->grandMother11Id)==6))){
			if(genTau->pt > genTau1FromW.pt){ 
				genTau2FromW = genTau1FromW;
				genTau1FromW = *genTau;
			}
			if(genTau2FromW.pt > 0){ break; }
		}
	}

	// Tau loops: Tau1 is always leads in pT
	unsigned int theNumberOfTaus1 = 0;
	unsigned int theNumberOfTaus2 = 0;
	unsigned int theNumberOfMuons = 0;

	// Start loop over Taus so select two (if applicable) that form a good (and heaviest) pair
	_NumTaus = _BNtaus.size();
	theNumberOfTaus1 = 0;
	for ( BNtauCollection::const_iterator Tau1 = _BNtaus.begin(); Tau1 != _BNtaus.end(); ++Tau1 ) {
		theNumberOfTaus1++;

		theNumberOfTaus2 = theNumberOfTaus1 + 1;
		for ( BNtauCollection::const_iterator Tau2 = (Tau1 + 1); Tau2 != _BNtaus.end(); ++Tau2 ) {
			theNumberOfTaus2++;

			if( theNumberOfTaus2 <= theNumberOfTaus1 ){ continue; }// Make sure we don't double-count: only compare pairs in which the tau2 iterator is larger than the tau 1 iterator, else skip combo


			// BNtauCollection should be sorted by pT in descending order, but let's make sure, and if not, flip them so Tau1 has the largest pT
			if (Tau1->pt < Tau2->pt){
				BNtauCollection::const_iterator TauTemp = Tau1;
				Tau1 = Tau2;
				Tau2 = TauTemp;
			}

			if(Tau1->pt < _RecoTauMinPt){ continue; }
			if(Tau2->pt < _RecoTauMinPt){ continue; }
			if(fabs(Tau1->eta) > _RecoTauMaxAbsEta ){ continue; }
			if(fabs(Tau2->eta) > _RecoTauMaxAbsEta ){ continue; }
			if(_RecoTauRequireDMF && !(Tau1->HPSdecayModeFinding)){ continue; }
			if(_RecoTauRequireDMF && !(Tau2->HPSdecayModeFinding)){ continue; }

			_NumMuons = selectedMuons.size();
			theNumberOfMuons = 0;
			for ( BNmuonCollection::const_iterator Muon = selectedMuons.begin(); Muon != selectedMuons.end(); ++Muon ) {
				theNumberOfMuons++;

				// =========   NO VECTOR FILLING BEFORE THIS POINT   ========= //

				_NumCombos++;
				_MomentumRank.push_back(_MomentumRank.size());

				FillDitauMuon(*Tau1, *Tau2, *Muon);

				_Tau1MomentumRank.push_back(theNumberOfTaus1-1);
				FillTau1(*Tau1);

				_Tau2MomentumRank.push_back(theNumberOfTaus2-1);
				FillTau2(*Tau2);

				_MuonMomentumRank.push_back(theNumberOfMuons-1);
				FillMuon(*Muon);

				
				// Jets and MET and related quantities
				// Correct for jet pT
				BNjetCollection correctedJets                           = beanHelper->GetCorrectedJets(_BNjets);

				// Apply kinematic requirements on corrected jets
				BNjetCollection selCorrJets                             = beanHelper->GetSelectedJets(correctedJets, 30, 2.4, jetID::jetLoose, '-');

				// Clean jets from taus and muon
				vector<TLorentzVector> tausAndMuon;
				tausAndMuon.push_back(TLorentzVector(Tau1->px, Tau1->py, Tau1->pz, Tau1->energy));
				tausAndMuon.push_back(TLorentzVector(Tau2->px, Tau2->py, Tau2->pz, Tau2->energy));
				tausAndMuon.push_back(TLorentzVector(Muon->px, Muon->py, Muon->pz, Muon->energy));
				BNjetCollection cleanSelCorrJets						= beanHelper->GetCleanJets(selCorrJets, tausAndMuon, 0.25);

				// Derive quantities based on the corrected MET based on the clean, corrected, kinematically-selected jets
				BNmet correctedMET  = beanHelper->GetCorrectedMET(*(_BNmets.begin()), beanHelper->GetUncorrectedJets(cleanSelCorrJets, _BNjets));

				_HT					.push_back(Tau1->pt + Tau2->pt + Muon->pt + correctedMET.pt + beanHelper->GetHT(cleanSelCorrJets));
				_DitauMETMass		.push_back(GetComboMassBN(*Tau1, *Tau2, correctedMET));

				_NumCSVLbtagJets	.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'L'));
				_NumCSVMbtagJets	.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'M'));
				_NumCSVTbtagJets	.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'T'));
				_NumNonCSVLbtagJets .push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'L'));
				_NumNonCSVMbtagJets .push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'M'));
				_NumNonCSVTbtagJets .push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'T'));

				// Provenance
				_Tau1MatchesGenHadTauFromH1.push_back( (genTau1FromH.pt>0) && (deltaR(genTau1FromH.eta, genTau1FromH.phi, Tau1->eta, Tau1->phi) < 0.25) );
				_Tau2MatchesGenHadTauFromH1.push_back( (genTau1FromH.pt>0) && (deltaR(genTau1FromH.eta, genTau1FromH.phi, Tau2->eta, Tau2->phi) < 0.25) );
				_Tau1MatchesGenHadTauFromH2.push_back( (genTau2FromH.pt>0) && (deltaR(genTau2FromH.eta, genTau2FromH.phi, Tau1->eta, Tau1->phi) < 0.25) );
				_Tau2MatchesGenHadTauFromH2.push_back( (genTau2FromH.pt>0) && (deltaR(genTau2FromH.eta, genTau2FromH.phi, Tau2->eta, Tau2->phi) < 0.25) );
				_Tau1MatchesGenHadTauFromW1.push_back( (genTau1FromW.pt>0) && (deltaR(genTau1FromW.eta, genTau1FromW.phi, Tau1->eta, Tau1->phi) < 0.25) );
				_Tau2MatchesGenHadTauFromW1.push_back( (genTau1FromW.pt>0) && (deltaR(genTau1FromW.eta, genTau1FromW.phi, Tau2->eta, Tau2->phi) < 0.25) );
				_Tau1MatchesGenHadTauFromW2.push_back( (genTau2FromW.pt>0) && (deltaR(genTau2FromW.eta, genTau2FromW.phi, Tau1->eta, Tau1->phi) < 0.25) );
				_Tau2MatchesGenHadTauFromW2.push_back( (genTau2FromW.pt>0) && (deltaR(genTau2FromW.eta, genTau2FromW.phi, Tau2->eta, Tau2->phi) < 0.25) );

			} // end of muon loop
		} // end of tau2 loop
	} // end of tau1 loop
		
}


void DitauMuonFiller::FillTau1(const BNtau& Tau){
				_Tau1Pt											.push_back(Tau.pt);
				_Tau1Eta										.push_back(Tau.eta);
				_Tau1Phi										.push_back(Tau.phi);
				_Tau1NProngs									.push_back(Tau.numProngs);
				_Tau1NSignalGammas								.push_back(Tau.numSignalGammas);
				_Tau1NSignalNeutrals							.push_back(Tau.numSignalNeutrals);
				_Tau1DecayMode									.push_back(Tau.decayMode);
				_Tau1EmFraction									.push_back(Tau.emFraction);
				_Tau1IsInTheCracks								.push_back(Tau.inTheCracks);
				_Tau1HPSagainstElectronMVA						.push_back(Tau.HPSagainstElectronMVA);
				_Tau1HPSagainstElectronLoose					.push_back(Tau.HPSagainstElectronLoose);
				_Tau1HPSagainstElectronMedium					.push_back(Tau.HPSagainstElectronMedium);
				_Tau1HPSagainstElectronTight					.push_back(Tau.HPSagainstElectronTight);
				_Tau1HPSagainstMuonLoose						.push_back(Tau.HPSagainstMuonLoose);
				_Tau1HPSagainstMuonMedium						.push_back(Tau.HPSagainstMuonMedium);
				_Tau1HPSagainstMuonTight						.push_back(Tau.HPSagainstMuonTight);
				_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr	.push_back(Tau.HPSbyVLooseCombinedIsolationDeltaBetaCorr);
				_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr	.push_back(Tau.HPSbyLooseCombinedIsolationDeltaBetaCorr);
				_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr	.push_back(Tau.HPSbyMediumCombinedIsolationDeltaBetaCorr);
				_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr	.push_back(Tau.HPSbyTightCombinedIsolationDeltaBetaCorr);
				_Tau1HPSdecayModeFinding						.push_back(Tau.HPSdecayModeFinding);
			
				// Leading track variables
				_Tau1LTPt			.push_back(Tau.leadingTrackPt);
				_Tau1Charge			.push_back(Tau.charge);
				_Tau1LTvalid		.push_back(Tau.leadingTrackValid);
				_Tau1LTIpVtdxy		.push_back(Tau.leadingTrackIpVtdxy);
				_Tau1LTIpVtdz		.push_back(Tau.leadingTrackIpVtdz);
				_Tau1LTIpVtdxyError	.push_back(Tau.leadingTrackIpVtdxyError);
				_Tau1LTIpVtdzError	.push_back(Tau.leadingTrackIpVtdzError);
				_Tau1LTvx			.push_back(Tau.leadingTrackVx);
				_Tau1LTvy			.push_back(Tau.leadingTrackVy);
				_Tau1LTvz			.push_back(Tau.leadingTrackVz);
				_Tau1LTValidHits	.push_back(Tau.leadingTrackValidHits);
				_Tau1LTNormChiSqrd	.push_back(Tau.leadingTrackNormChiSqrd);

				// Provenance
				vector<int> undesiredIDs;
				undesiredIDs.push_back(6);	undesiredIDs.push_back(-6);		// No tops
				undesiredIDs.push_back(12);	undesiredIDs.push_back(-12);	// No e neutrinos
				undesiredIDs.push_back(14);	undesiredIDs.push_back(-14);	// No mu neutrinos
				undesiredIDs.push_back(16);	undesiredIDs.push_back(-16);	// No tau neutrinos
				//undesiredIDs.push_back(24);	undesiredIDs.push_back(-24);	// No W
				undesiredIDs.push_back(25);									// No H
				//undesiredIDs.push_back(21);									// No g

				BNmcparticleCollection status3MCparticles	= beanHelper->GetSelectedMCparticlesByStatus(_BNmcparticles, false, false, true); 
				BNmcparticleCollection selectedMCparticles	= beanHelper->GetUnrejectedMCparticlesByPDGid(status3MCparticles, undesiredIDs);

				BNmcparticle tauGenMatch = beanHelper->GetMatchedMCparticle(selectedMCparticles, Tau, 0.25);
				_Tau1GenMatchDaughter0Id			.push_back(tauGenMatch.daughter0Id);
				_Tau1GenMatchDaughter1Id			.push_back(tauGenMatch.daughter1Id);
				_Tau1GenMatchId						.push_back(tauGenMatch.id);
				_Tau1GenMatchMother0Id				.push_back(tauGenMatch.mother0Id);
				_Tau1GenMatchMother1Id				.push_back(tauGenMatch.mother1Id);
				_Tau1GenMatchGrandmother00Id		.push_back(tauGenMatch.grandMother00Id);
				_Tau1GenMatchGrandmother01Id		.push_back(tauGenMatch.grandMother01Id);
				_Tau1GenMatchGrandmother10Id		.push_back(tauGenMatch.grandMother10Id);
				_Tau1GenMatchGrandmother11Id		.push_back(tauGenMatch.grandMother11Id);
				_Tau1GenMatchDaughter0Status		.push_back(tauGenMatch.daughter0Status);
				_Tau1GenMatchDaughter1Status		.push_back(tauGenMatch.daughter1Status);
				_Tau1GenMatchStatus					.push_back(tauGenMatch.status);
				_Tau1GenMatchMother0Status			.push_back(tauGenMatch.mother0Status);
				_Tau1GenMatchMother1Status			.push_back(tauGenMatch.mother1Status);
				_Tau1GenMatchGrandmother00Status	.push_back(tauGenMatch.grandMother00Status);
				_Tau1GenMatchGrandmother01Status	.push_back(tauGenMatch.grandMother01Status);
				_Tau1GenMatchGrandmother10Status	.push_back(tauGenMatch.grandMother10Status);
				_Tau1GenMatchGrandmother11Status	.push_back(tauGenMatch.grandMother11Status);

}


void DitauMuonFiller::FillTau2(const BNtau& Tau){
				_Tau2Pt											.push_back(Tau.pt);
				_Tau2Eta										.push_back(Tau.eta);
				_Tau2Phi										.push_back(Tau.phi);
				_Tau2NProngs									.push_back(Tau.numProngs);
				_Tau2NSignalGammas								.push_back(Tau.numSignalGammas);
				_Tau2NSignalNeutrals							.push_back(Tau.numSignalNeutrals);
				_Tau2DecayMode									.push_back(Tau.decayMode);
				_Tau2EmFraction									.push_back(Tau.emFraction);
				_Tau2IsInTheCracks								.push_back(Tau.inTheCracks);
				_Tau2HPSagainstElectronMVA						.push_back(Tau.HPSagainstElectronMVA);
				_Tau2HPSagainstElectronLoose					.push_back(Tau.HPSagainstElectronLoose);
				_Tau2HPSagainstElectronMedium					.push_back(Tau.HPSagainstElectronMedium);
				_Tau2HPSagainstElectronTight					.push_back(Tau.HPSagainstElectronTight);
				_Tau2HPSagainstMuonLoose						.push_back(Tau.HPSagainstMuonLoose);
				_Tau2HPSagainstMuonMedium						.push_back(Tau.HPSagainstMuonMedium);
				_Tau2HPSagainstMuonTight						.push_back(Tau.HPSagainstMuonTight);
				_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr	.push_back(Tau.HPSbyVLooseCombinedIsolationDeltaBetaCorr);
				_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr	.push_back(Tau.HPSbyLooseCombinedIsolationDeltaBetaCorr);
				_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr	.push_back(Tau.HPSbyMediumCombinedIsolationDeltaBetaCorr);
				_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr	.push_back(Tau.HPSbyTightCombinedIsolationDeltaBetaCorr);
				_Tau2HPSdecayModeFinding						.push_back(Tau.HPSdecayModeFinding);
			
				// Leading track variables
				_Tau2LTPt										.push_back(Tau.leadingTrackPt);
				_Tau2Charge										.push_back(Tau.charge);
				_Tau2LTvalid									.push_back(Tau.leadingTrackValid);
				_Tau2LTIpVtdxy									.push_back(Tau.leadingTrackIpVtdxy);
				_Tau2LTIpVtdz									.push_back(Tau.leadingTrackIpVtdz);
				_Tau2LTIpVtdxyError								.push_back(Tau.leadingTrackIpVtdxyError);
				_Tau2LTIpVtdzError								.push_back(Tau.leadingTrackIpVtdzError);
				_Tau2LTvx										.push_back(Tau.leadingTrackVx);
				_Tau2LTvy										.push_back(Tau.leadingTrackVy);
				_Tau2LTvz										.push_back(Tau.leadingTrackVz);
				_Tau2LTValidHits								.push_back(Tau.leadingTrackValidHits);
				_Tau2LTNormChiSqrd								.push_back(Tau.leadingTrackNormChiSqrd);

				// Provenance
				vector<int> undesiredIDs;
				undesiredIDs.push_back(6);	undesiredIDs.push_back(-6);		// No tops
				undesiredIDs.push_back(12);	undesiredIDs.push_back(-12);	// No e neutrinos
				undesiredIDs.push_back(14);	undesiredIDs.push_back(-14);	// No mu neutrinos
				undesiredIDs.push_back(16);	undesiredIDs.push_back(-16);	// No tau neutrinos
				//undesiredIDs.push_back(24);	undesiredIDs.push_back(-24);	// No W
				undesiredIDs.push_back(25);									// No H
				//undesiredIDs.push_back(21);									// No g

				BNmcparticleCollection status3MCparticles	= beanHelper->GetSelectedMCparticlesByStatus(_BNmcparticles, false, false, true); 
				BNmcparticleCollection selectedMCparticles	= beanHelper->GetUnrejectedMCparticlesByPDGid(status3MCparticles, undesiredIDs);
				BNmcparticle tauGenMatch = beanHelper->GetMatchedMCparticle(selectedMCparticles, Tau, 0.25);
				_Tau2GenMatchDaughter0Id			.push_back(tauGenMatch.daughter0Id);
				_Tau2GenMatchDaughter1Id			.push_back(tauGenMatch.daughter1Id);
				_Tau2GenMatchId						.push_back(tauGenMatch.id);
				_Tau2GenMatchMother0Id				.push_back(tauGenMatch.mother0Id);
				_Tau2GenMatchMother1Id				.push_back(tauGenMatch.mother1Id);
				_Tau2GenMatchGrandmother00Id		.push_back(tauGenMatch.grandMother00Id);
				_Tau2GenMatchGrandmother01Id		.push_back(tauGenMatch.grandMother01Id);
				_Tau2GenMatchGrandmother10Id		.push_back(tauGenMatch.grandMother10Id);
				_Tau2GenMatchGrandmother11Id		.push_back(tauGenMatch.grandMother11Id);
				_Tau2GenMatchDaughter0Status		.push_back(tauGenMatch.daughter0Status);
				_Tau2GenMatchDaughter1Status		.push_back(tauGenMatch.daughter1Status);
				_Tau2GenMatchStatus					.push_back(tauGenMatch.status);
				_Tau2GenMatchMother0Status			.push_back(tauGenMatch.mother0Status);
				_Tau2GenMatchMother1Status			.push_back(tauGenMatch.mother1Status);
				_Tau2GenMatchGrandmother00Status	.push_back(tauGenMatch.grandMother00Status);
				_Tau2GenMatchGrandmother01Status	.push_back(tauGenMatch.grandMother01Status);
				_Tau2GenMatchGrandmother10Status	.push_back(tauGenMatch.grandMother10Status);
				_Tau2GenMatchGrandmother11Status	.push_back(tauGenMatch.grandMother11Status);
}

void DitauMuonFiller::FillMuon(const BNmuon& Muon){
	_MuonPt.push_back(Muon.pt);
	_MuonEta.push_back(Muon.eta);
	_MuonPhi.push_back(Muon.phi);
	_MuonRelIso.push_back(beanHelper->GetMuonRelIso(Muon));
	_MuonIsLooseMuon.push_back(beanHelper->IsLooseMuon(Muon));
	_MuonIsTightMuon.push_back(beanHelper->IsTightMuon(Muon));

	// Provenance
	vector<int> undesiredIDs;
	undesiredIDs.push_back(6);	undesiredIDs.push_back(-6);		// No tops
	undesiredIDs.push_back(12);	undesiredIDs.push_back(-12);	// No e neutrinos
	undesiredIDs.push_back(14);	undesiredIDs.push_back(-14);	// No mu neutrinos
	undesiredIDs.push_back(16);	undesiredIDs.push_back(-16);	// No tau neutrinos
	//undesiredIDs.push_back(24);	undesiredIDs.push_back(-24);	// No W
	undesiredIDs.push_back(25);									// No H
	//undesiredIDs.push_back(21);									// No g

	BNmcparticleCollection status3MCparticles	= beanHelper->GetSelectedMCparticlesByStatus(_BNmcparticles, false, false, true); 
	BNmcparticleCollection selectedMCparticles	= beanHelper->GetUnrejectedMCparticlesByPDGid(status3MCparticles, undesiredIDs);
	BNmcparticle muonGenMatch = beanHelper->GetMatchedMCparticle(selectedMCparticles, Muon, 0.25);
	_MuonGenMatchDaughter0Id			.push_back(muonGenMatch.daughter0Id);
	_MuonGenMatchDaughter1Id			.push_back(muonGenMatch.daughter1Id);
	_MuonGenMatchId						.push_back(muonGenMatch.id);
	_MuonGenMatchMother0Id				.push_back(muonGenMatch.mother0Id);
	_MuonGenMatchMother1Id				.push_back(muonGenMatch.mother1Id);
	_MuonGenMatchGrandmother00Id		.push_back(muonGenMatch.grandMother00Id);
	_MuonGenMatchGrandmother01Id		.push_back(muonGenMatch.grandMother01Id);
	_MuonGenMatchGrandmother10Id		.push_back(muonGenMatch.grandMother10Id);
	_MuonGenMatchGrandmother11Id		.push_back(muonGenMatch.grandMother11Id);
	_MuonGenMatchDaughter0Status		.push_back(muonGenMatch.daughter0Status);
	_MuonGenMatchDaughter1Status		.push_back(muonGenMatch.daughter1Status);
	_MuonGenMatchStatus					.push_back(muonGenMatch.status);
	_MuonGenMatchMother0Status			.push_back(muonGenMatch.mother0Status);
	_MuonGenMatchMother1Status			.push_back(muonGenMatch.mother1Status);
	_MuonGenMatchGrandmother00Status	.push_back(muonGenMatch.grandMother00Status);
	_MuonGenMatchGrandmother01Status	.push_back(muonGenMatch.grandMother01Status);
	_MuonGenMatchGrandmother10Status	.push_back(muonGenMatch.grandMother10Status);
	_MuonGenMatchGrandmother11Status	.push_back(muonGenMatch.grandMother11Status);


}

void DitauMuonFiller::FillDitauMuon(const BNtau& Tau1, const BNtau& Tau2, const BNmuon& Muon){
	_DitauVisibleMass	.push_back(GetComboMassBN(Tau1, Tau2));
	_DitauCosDeltaPhi	.push_back(cos(TMath::Abs(normalizedPhi(Tau1.phi - Tau2.phi))));
	_DitauDeltaR		.push_back(reco::deltaR(Tau1.eta, Tau1.phi, Tau2.eta, Tau2.phi));
	_Tau1MuonDeltaR		.push_back(reco::deltaR(Tau1.eta, Tau1.phi, Muon.eta, Muon.phi));
	_Tau2MuonDeltaR		.push_back(reco::deltaR(Tau2.eta, Tau2.phi, Muon.eta, Muon.phi));
}
