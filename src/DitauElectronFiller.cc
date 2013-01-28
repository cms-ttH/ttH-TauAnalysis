// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/DitauElectronFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
DitauElectronFiller::DitauElectronFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

DitauElectronFiller::DitauElectronFiller(const ParameterSet& iConfig, TTree* iTree, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper) {
	_FillerName	= __FILE__;
	_Tree = iTree;
	SetupBranches();
	
    /*_recoTauMatchedToGenHadTauFromH1 = NULL;
	_recoTauMatchedToGenHadTauFromH2 = NULL;
	_recoTauMatchedToGenHadTauFromW1 = NULL;
	_recoTauMatchedToGenHadTauFromW2 = NULL;//*/

}

// === Destructor === //
DitauElectronFiller::~DitauElectronFiller(){}

// ------------ method called to for each event  ------------
void DitauElectronFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void DitauElectronFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("TTE_NumTaus",&_NumTaus);
	_Tree->Branch("TTE_NumElectrons",&_NumElectrons);
	_Tree->Branch("TTE_NumCombos",&_NumCombos);
	_Tree->Branch("TTE_MomentumRank",&_MomentumRank);

	// === Tau1 === //
	_Tree->Branch("TTE_Tau1MomentumRank", &_Tau1MomentumRank);
	_Tree->Branch("TTE_Tau1Pt", &_Tau1Pt);
	_Tree->Branch("TTE_Tau1Eta", &_Tau1Eta);
	_Tree->Branch("TTE_Tau1Phi", &_Tau1Phi);
	_Tree->Branch("TTE_Tau1NProngs", &_Tau1NProngs);
	_Tree->Branch("TTE_Tau1NSignalGammas", &_Tau1NSignalGammas);
	_Tree->Branch("TTE_Tau1NSignalNeutrals", &_Tau1NSignalNeutrals);
	_Tree->Branch("TTE_Tau1DecayMode", &_Tau1DecayMode);
	_Tree->Branch("TTE_Tau1EmFraction", &_Tau1EmFraction);
	_Tree->Branch("TTE_Tau1IsInTheCracks", &_Tau1IsInTheCracks);
	_Tree->Branch("TTE_Tau1HPSagainstElectronLoose", &_Tau1HPSagainstElectronLoose);
	_Tree->Branch("TTE_Tau1HPSagainstElectronMVA", &_Tau1HPSagainstElectronMVA);
	_Tree->Branch("TTE_Tau1HPSagainstElectronMedium", &_Tau1HPSagainstElectronMedium);
	_Tree->Branch("TTE_Tau1HPSagainstElectronTight", &_Tau1HPSagainstElectronTight);
	_Tree->Branch("TTE_Tau1HPSagainstMuonLoose", &_Tau1HPSagainstMuonLoose);
	_Tree->Branch("TTE_Tau1HPSagainstMuonMedium", &_Tau1HPSagainstMuonMedium);
	_Tree->Branch("TTE_Tau1HPSagainstMuonTight", &_Tau1HPSagainstMuonTight);
	_Tree->Branch("TTE_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTE_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTE_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTE_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTE_Tau1HPSdecayModeFinding", &_Tau1HPSdecayModeFinding);
	_Tree->Branch("TTE_Tau1LTPt", &_Tau1LTPt);
	_Tree->Branch("TTE_Tau1Charge", &_Tau1Charge);
	_Tree->Branch("TTE_Tau1LTvalid", &_Tau1LTvalid);
	_Tree->Branch("TTE_Tau1LTIpVtdxy", &_Tau1LTIpVtdxy);
	_Tree->Branch("TTE_Tau1LTIpVtdz", &_Tau1LTIpVtdz);
	_Tree->Branch("TTE_Tau1LTIpVtdxyError", &_Tau1LTIpVtdxyError);
	_Tree->Branch("TTE_Tau1LTIpVtdzError", &_Tau1LTIpVtdzError);
	_Tree->Branch("TTE_Tau1LTvx", &_Tau1LTvx);
	_Tree->Branch("TTE_Tau1LTvy", &_Tau1LTvy);
	_Tree->Branch("TTE_Tau1LTvz", &_Tau1LTvz);
	_Tree->Branch("TTE_Tau1LTValidHits", &_Tau1LTValidHits);
	_Tree->Branch("TTE_Tau1LTNormChiSqrd", &_Tau1LTNormChiSqrd);
	_Tree->Branch("TTE_Tau1MatchesGenHadTauFromH1", &_Tau1MatchesGenHadTauFromH1);
	_Tree->Branch("TTE_Tau1MatchesGenHadTauFromH2", &_Tau1MatchesGenHadTauFromH2);
	_Tree->Branch("TTE_Tau1MatchesGenHadTauFromW1", &_Tau1MatchesGenHadTauFromW1);
	_Tree->Branch("TTE_Tau1MatchesGenHadTauFromW2", &_Tau1MatchesGenHadTauFromW2);
	_Tree->Branch("TTE_Tau1GenMatchDaughter0Id", &_Tau1GenMatchDaughter0Id);
	_Tree->Branch("TTE_Tau1GenMatchDaughter1Id", &_Tau1GenMatchDaughter1Id);
	_Tree->Branch("TTE_Tau1GenMatchId", &_Tau1GenMatchId);
	_Tree->Branch("TTE_Tau1GenMatchMother0Id", &_Tau1GenMatchMother0Id);
	_Tree->Branch("TTE_Tau1GenMatchMother1Id", &_Tau1GenMatchMother1Id);
	_Tree->Branch("TTE_Tau1GenMatchGrandmother00Id", &_Tau1GenMatchGrandmother00Id);
	_Tree->Branch("TTE_Tau1GenMatchGrandmother01Id", &_Tau1GenMatchGrandmother01Id);
	_Tree->Branch("TTE_Tau1GenMatchGrandmother10Id", &_Tau1GenMatchGrandmother10Id);
	_Tree->Branch("TTE_Tau1GenMatchGrandmother11Id", &_Tau1GenMatchGrandmother11Id);
	_Tree->Branch("TTE_Tau1GenMatchDaughter0Status", &_Tau1GenMatchDaughter0Status);
	_Tree->Branch("TTE_Tau1GenMatchDaughter1Status", &_Tau1GenMatchDaughter1Status);
	_Tree->Branch("TTE_Tau1GenMatchStatus", &_Tau1GenMatchStatus);
	_Tree->Branch("TTE_Tau1GenMatchMother0Status", &_Tau1GenMatchMother0Status);
	_Tree->Branch("TTE_Tau1GenMatchMother1Status", &_Tau1GenMatchMother1Status);
	_Tree->Branch("TTE_Tau1GenMatchGrandmother00Status", &_Tau1GenMatchGrandmother00Status);
	_Tree->Branch("TTE_Tau1GenMatchGrandmother01Status", &_Tau1GenMatchGrandmother01Status);
	_Tree->Branch("TTE_Tau1GenMatchGrandmother10Status", &_Tau1GenMatchGrandmother10Status);
	_Tree->Branch("TTE_Tau1GenMatchGrandmother11Status", &_Tau1GenMatchGrandmother11Status);

	// === Tau2 === //
	_Tree->Branch("TTE_Tau2MomentumRank", &_Tau2MomentumRank);
	_Tree->Branch("TTE_Tau2Pt", &_Tau2Pt);
	_Tree->Branch("TTE_Tau2Eta", &_Tau2Eta);
	_Tree->Branch("TTE_Tau2Phi", &_Tau2Phi);
	_Tree->Branch("TTE_Tau2NProngs", &_Tau2NProngs);
	_Tree->Branch("TTE_Tau2NSignalGammas", &_Tau2NSignalGammas);
	_Tree->Branch("TTE_Tau2NSignalNeutrals", &_Tau2NSignalNeutrals);
	_Tree->Branch("TTE_Tau2DecayMode", &_Tau2DecayMode);
	_Tree->Branch("TTE_Tau2EmFraction", &_Tau2EmFraction);
	_Tree->Branch("TTE_Tau2IsInTheCracks", &_Tau2IsInTheCracks);
	_Tree->Branch("TTE_Tau2HPSagainstElectronLoose", &_Tau2HPSagainstElectronLoose);
	_Tree->Branch("TTE_Tau2HPSagainstElectronMVA", &_Tau2HPSagainstElectronMVA);
	_Tree->Branch("TTE_Tau2HPSagainstElectronMedium", &_Tau2HPSagainstElectronMedium);
	_Tree->Branch("TTE_Tau2HPSagainstElectronTight", &_Tau2HPSagainstElectronTight);
	_Tree->Branch("TTE_Tau2HPSagainstMuonLoose", &_Tau2HPSagainstMuonLoose);
	_Tree->Branch("TTE_Tau2HPSagainstMuonMedium", &_Tau2HPSagainstMuonMedium);
	_Tree->Branch("TTE_Tau2HPSagainstMuonTight", &_Tau2HPSagainstMuonTight);
	_Tree->Branch("TTE_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTE_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTE_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTE_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TTE_Tau2HPSdecayModeFinding", &_Tau2HPSdecayModeFinding);
	_Tree->Branch("TTE_Tau2LTPt", &_Tau2LTPt);
	_Tree->Branch("TTE_Tau2Charge", &_Tau2Charge);
	_Tree->Branch("TTE_Tau2LTvalid", &_Tau2LTvalid);
	_Tree->Branch("TTE_Tau2LTIpVtdxy", &_Tau2LTIpVtdxy);
	_Tree->Branch("TTE_Tau2LTIpVtdz", &_Tau2LTIpVtdz);
	_Tree->Branch("TTE_Tau2LTIpVtdxyError", &_Tau2LTIpVtdxyError);
	_Tree->Branch("TTE_Tau2LTIpVtdzError", &_Tau2LTIpVtdzError);
	_Tree->Branch("TTE_Tau2LTvx", &_Tau2LTvx);
	_Tree->Branch("TTE_Tau2LTvy", &_Tau2LTvy);
	_Tree->Branch("TTE_Tau2LTvz", &_Tau2LTvz);
	_Tree->Branch("TTE_Tau2LTValidHits", &_Tau2LTValidHits);
	_Tree->Branch("TTE_Tau2LTNormChiSqrd", &_Tau2LTNormChiSqrd);
	_Tree->Branch("TTE_Tau2MatchesGenHadTauFromH1", &_Tau2MatchesGenHadTauFromH1);
	_Tree->Branch("TTE_Tau2MatchesGenHadTauFromH2", &_Tau2MatchesGenHadTauFromH2);
	_Tree->Branch("TTE_Tau2MatchesGenHadTauFromW1", &_Tau2MatchesGenHadTauFromW1);
	_Tree->Branch("TTE_Tau2MatchesGenHadTauFromW2", &_Tau2MatchesGenHadTauFromW2);
	_Tree->Branch("TTE_Tau2GenMatchDaughter0Id", &_Tau2GenMatchDaughter0Id);
	_Tree->Branch("TTE_Tau2GenMatchDaughter1Id", &_Tau2GenMatchDaughter1Id);
	_Tree->Branch("TTE_Tau2GenMatchId", &_Tau2GenMatchId);
	_Tree->Branch("TTE_Tau2GenMatchMother0Id", &_Tau2GenMatchMother0Id);
	_Tree->Branch("TTE_Tau2GenMatchMother1Id", &_Tau2GenMatchMother1Id);
	_Tree->Branch("TTE_Tau2GenMatchGrandmother00Id", &_Tau2GenMatchGrandmother00Id);
	_Tree->Branch("TTE_Tau2GenMatchGrandmother01Id", &_Tau2GenMatchGrandmother01Id);
	_Tree->Branch("TTE_Tau2GenMatchGrandmother10Id", &_Tau2GenMatchGrandmother10Id);
	_Tree->Branch("TTE_Tau2GenMatchGrandmother11Id", &_Tau2GenMatchGrandmother11Id);
	_Tree->Branch("TTE_Tau2GenMatchDaughter0Status", &_Tau2GenMatchDaughter0Status);
	_Tree->Branch("TTE_Tau2GenMatchDaughter1Status", &_Tau2GenMatchDaughter1Status);
	_Tree->Branch("TTE_Tau2GenMatchStatus", &_Tau2GenMatchStatus);
	_Tree->Branch("TTE_Tau2GenMatchMother0Status", &_Tau2GenMatchMother0Status);
	_Tree->Branch("TTE_Tau2GenMatchMother1Status", &_Tau2GenMatchMother1Status);
	_Tree->Branch("TTE_Tau2GenMatchGrandmother00Status", &_Tau2GenMatchGrandmother00Status);
	_Tree->Branch("TTE_Tau2GenMatchGrandmother01Status", &_Tau2GenMatchGrandmother01Status);
	_Tree->Branch("TTE_Tau2GenMatchGrandmother10Status", &_Tau2GenMatchGrandmother10Status);
	_Tree->Branch("TTE_Tau2GenMatchGrandmother11Status", &_Tau2GenMatchGrandmother11Status);

	// === Electron === //
	_Tree->Branch("TTE_ElectronMomentumRank", &_ElectronMomentumRank);
	_Tree->Branch("TTE_ElectronPt", &_ElectronPt);
	_Tree->Branch("TTE_ElectronEta", &_ElectronEta);
	_Tree->Branch("TTE_ElectronPhi", &_ElectronPhi);
	_Tree->Branch("TTE_ElectronRelIso", &_ElectronRelIso);
	_Tree->Branch("TTE_ElectronIsLooseElectron", &_ElectronIsLooseElectron);
	_Tree->Branch("TTE_ElectronIsTightElectron", &_ElectronIsTightElectron);
	_Tree->Branch("TTE_NumOtherLooseMuons",&_NumOtherLooseMuons);
	_Tree->Branch("TTE_NumOtherTightMuons",&_NumOtherTightMuons);
	_Tree->Branch("TTE_NumOtherLooseElectrons",&_NumOtherLooseElectrons);
	_Tree->Branch("TTE_NumOtherTightElectrons",&_NumOtherTightElectrons);
	_Tree->Branch("TTE_LeptonEventWeight",&_LeptonEventWeight);
	_Tree->Branch("TTE_ElectronGenMatchDaughter0Id", &_ElectronGenMatchDaughter0Id);
	_Tree->Branch("TTE_ElectronGenMatchDaughter1Id", &_ElectronGenMatchDaughter1Id);
	_Tree->Branch("TTE_ElectronGenMatchId", &_ElectronGenMatchId);
	_Tree->Branch("TTE_ElectronGenMatchMother0Id", &_ElectronGenMatchMother0Id);
	_Tree->Branch("TTE_ElectronGenMatchMother1Id", &_ElectronGenMatchMother1Id);
	_Tree->Branch("TTE_ElectronGenMatchGrandmother00Id", &_ElectronGenMatchGrandmother00Id);
	_Tree->Branch("TTE_ElectronGenMatchGrandmother01Id", &_ElectronGenMatchGrandmother01Id);
	_Tree->Branch("TTE_ElectronGenMatchGrandmother10Id", &_ElectronGenMatchGrandmother10Id);
	_Tree->Branch("TTE_ElectronGenMatchGrandmother11Id", &_ElectronGenMatchGrandmother11Id);
	_Tree->Branch("TTE_ElectronGenMatchDaughter0Status", &_ElectronGenMatchDaughter0Status);
	_Tree->Branch("TTE_ElectronGenMatchDaughter1Status", &_ElectronGenMatchDaughter1Status);
	_Tree->Branch("TTE_ElectronGenMatchStatus", &_ElectronGenMatchStatus);
	_Tree->Branch("TTE_ElectronGenMatchMother0Status", &_ElectronGenMatchMother0Status);
	_Tree->Branch("TTE_ElectronGenMatchMother1Status", &_ElectronGenMatchMother1Status);
	_Tree->Branch("TTE_ElectronGenMatchGrandmother00Status", &_ElectronGenMatchGrandmother00Status);
	_Tree->Branch("TTE_ElectronGenMatchGrandmother01Status", &_ElectronGenMatchGrandmother01Status);
	_Tree->Branch("TTE_ElectronGenMatchGrandmother10Status", &_ElectronGenMatchGrandmother10Status);
	_Tree->Branch("TTE_ElectronGenMatchGrandmother11Status", &_ElectronGenMatchGrandmother11Status);

	// === Combo === //
	_Tree->Branch("TTE_DitauVisibleMass", &_DitauVisibleMass);
	_Tree->Branch("TTE_DitauMETMass", &_DitauMETMass);
	_Tree->Branch("TTE_DitauCosDeltaPhi", &_DitauCosDeltaPhi);
	_Tree->Branch("TTE_DitauDeltaR", 	&_DitauDeltaR);
	_Tree->Branch("TTE_Tau1ElectronDeltaR", &_Tau1ElectronDeltaR);
	_Tree->Branch("TTE_Tau2ElectronDeltaR", &_Tau2ElectronDeltaR);
	_Tree->Branch("TTE_HT", &_HT);
	_Tree->Branch("TTE_NumCSVLbtagJets", &_NumCSVLbtagJets);
	_Tree->Branch("TTE_NumCSVMbtagJets", &_NumCSVMbtagJets);
	_Tree->Branch("TTE_NumCSVTbtagJets", &_NumCSVTbtagJets);
	_Tree->Branch("TTE_NumNonCSVLbtagJets", &_NumNonCSVLbtagJets);
	_Tree->Branch("TTE_NumNonCSVMbtagJets", &_NumNonCSVMbtagJets);
	_Tree->Branch("TTE_NumNonCSVTbtagJets", &_NumNonCSVTbtagJets);
}

// === Clear vectors that will be used to fill ntuple === //
void DitauElectronFiller::ClearVectors(){

	genHadTauFromH1 = reco::Candidate::LorentzVector(0,0,0,0);
	genHadTauFromH2 = reco::Candidate::LorentzVector(0,0,0,0);
	genHadTauFromW1 = reco::Candidate::LorentzVector(0,0,0,0);
	genHadTauFromW2 = reco::Candidate::LorentzVector(0,0,0,0);


	/*_recoTauMatchedToGenHadTauFromH1 = NULL;
	_recoTauMatchedToGenHadTauFromH2 = NULL;
	_recoTauMatchedToGenHadTauFromW1 = NULL;
	_recoTauMatchedToGenHadTauFromW2 = NULL;//*/

	_NumTaus	    								= 0;
	_NumElectrons									= 0;
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

	// === Electron === //
	_ElectronMomentumRank							.clear();
	_ElectronPt										.clear();
	_ElectronEta									.clear();
	_ElectronPhi									.clear();
    _ElectronRelIso                                 .clear();
    _ElectronIsTightElectron                        .clear();
    _ElectronIsLooseElectron                        .clear();
	_NumOtherLooseMuons								= 0;
	_NumOtherTightMuons								= 0;
	_NumOtherLooseElectrons							.clear();
	_NumOtherTightElectrons							.clear();
	_LeptonEventWeight								.clear();
	_ElectronGenMatchDaughter0Id					.clear();
	_ElectronGenMatchDaughter1Id					.clear();
	_ElectronGenMatchId								.clear();
	_ElectronGenMatchMother0Id						.clear();
	_ElectronGenMatchMother1Id						.clear();
	_ElectronGenMatchGrandmother00Id				.clear();
	_ElectronGenMatchGrandmother01Id				.clear();
	_ElectronGenMatchGrandmother10Id				.clear();
	_ElectronGenMatchGrandmother11Id				.clear();
	_ElectronGenMatchDaughter0Status				.clear();
	_ElectronGenMatchDaughter1Status				.clear();
	_ElectronGenMatchStatus							.clear();
	_ElectronGenMatchMother0Status					.clear();
	_ElectronGenMatchMother1Status					.clear();
	_ElectronGenMatchGrandmother00Status			.clear();
	_ElectronGenMatchGrandmother01Status			.clear();
	_ElectronGenMatchGrandmother10Status			.clear();
	_ElectronGenMatchGrandmother11Status			.clear();

	// === Combo === //
	_DitauVisibleMass								.clear();
	_DitauMETMass									.clear();
	_DitauCosDeltaPhi								.clear();
	_DitauDeltaR									.clear();
	_Tau1ElectronDeltaR								.clear();
	_Tau2ElectronDeltaR								.clear();
	_HT												.clear();
	_NumCSVLbtagJets								.clear();
	_NumCSVMbtagJets								.clear();
	_NumCSVTbtagJets								.clear();
	_NumNonCSVLbtagJets								.clear();
	_NumNonCSVMbtagJets								.clear();
	_NumNonCSVTbtagJets								.clear();
}

// === Fill ntuple === //
void DitauElectronFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){

	// Get the object collections from the event
    //std::cout << "<DitauElectronFiller::FillNtuple>: enter function" << std::endl;
	GetCollections(iEvent, iSetup);

	// Clear vectors
	ClearVectors();

    // Match Reco and GenHadTaus from H                                                               
	if(_AnalysisType.compare("signal") == 0 ){ MatchRecoAndGenHadTausFromH(); } 

	// Other leptons
	BNmuonCollection looseMuons				= beanHelper->GetSelectedMuons(_BNmuons, muonID::muonLoose);
	BNmuonCollection tightMuons				= beanHelper->GetSelectedMuons(_BNmuons, muonID::muonTight);
	_NumOtherLooseMuons	= looseMuons.size();
	_NumOtherTightMuons	= tightMuons.size();

	BNelectronCollection looseElectrons		= beanHelper->GetSelectedElectrons(_BNelectrons, electronID::electronLoose);
	BNelectronCollection tightElectrons		= beanHelper->GetSelectedElectrons(_BNelectrons, electronID::electronTight);

	// Select electrons (tight)
	BNelectronCollection selectedElectrons	= tightElectrons;



	if(_BNtaus.size() < 2 || selectedElectrons.size() < 1){ return; }

	// Tau loops: Tau1 is always leads in pT
	unsigned int theNumberOfTaus1 = 0;
	unsigned int theNumberOfTaus2 = 0;
	unsigned int theNumberOfElectrons = 0;

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

			_NumElectrons = selectedElectrons.size();
			theNumberOfElectrons = 0;
			for ( BNelectronCollection::const_iterator Electron = selectedElectrons.begin(); Electron != selectedElectrons.end(); ++Electron ) {
				theNumberOfElectrons++;

				// =========   NO VECTOR FILLING BEFORE THIS POINT   ========= //

				_NumCombos++;
				_MomentumRank.push_back(_MomentumRank.size());

				FillDitauElectron(*Tau1, *Tau2, *Electron);

				_Tau1MomentumRank.push_back(theNumberOfTaus1-1);
				FillTau1(*Tau1);

				_Tau2MomentumRank.push_back(theNumberOfTaus2-1);
				FillTau2(*Tau2);

				_ElectronMomentumRank.push_back(theNumberOfElectrons-1);
				FillElectron(*Electron);

				_NumOtherLooseElectrons.push_back( beanHelper->IsTightElectron(*Electron) ? (looseElectrons.size())		:	(looseElectrons.size()-1)	);
				_NumOtherTightElectrons.push_back( beanHelper->IsTightElectron(*Electron) ? (tightElectrons.size()-1)	:	(tightElectrons.size())		);

				
				// Jets and MET and related quantities
				// Correct for jet pT
				BNjetCollection correctedJets                           = beanHelper->GetCorrectedJets(_BNjets);

				// Apply kinematic requirements on corrected jets
				BNjetCollection selCorrJets                             = beanHelper->GetSelectedJets(correctedJets, 30, 2.4, jetID::jetLoose, '-');

				// Clean jets from taus and electron
				vector<TLorentzVector> tausAndElectron;
				tausAndElectron.push_back(TLorentzVector(Tau1->px, Tau1->py, Tau1->pz, Tau1->energy));
				tausAndElectron.push_back(TLorentzVector(Tau2->px, Tau2->py, Tau2->pz, Tau2->energy));
				tausAndElectron.push_back(TLorentzVector(Electron->px, Electron->py, Electron->pz, Electron->energy));
				BNjetCollection cleanSelCorrJets						= beanHelper->GetCleanJets(selCorrJets, tausAndElectron, 0.25);

				// Derive quantities based on the corrected MET based on the clean, corrected, kinematically-selected jets
				BNmet correctedMET  = beanHelper->GetCorrectedMET(*(_BNmets.begin()), beanHelper->GetUncorrectedJets(cleanSelCorrJets, _BNjets));

				_HT					.push_back(Tau1->pt + Tau2->pt + Electron->pt + correctedMET.pt + beanHelper->GetHT(cleanSelCorrJets));
				_DitauMETMass		.push_back(GetComboMassBN(*Tau1, *Tau2, correctedMET));

				_NumCSVLbtagJets	.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'L'));
				_NumCSVMbtagJets	.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'M'));
				_NumCSVTbtagJets	.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'T'));
				_NumNonCSVLbtagJets .push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'L'));
				_NumNonCSVMbtagJets .push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'M'));
				_NumNonCSVTbtagJets .push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'T'));


			} // end of electron loop
		} // end of tau2 loop
	} // end of tau1 loop
		
}

void DitauElectronFiller::FillTau1(const BNtau& Tau){
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

void DitauElectronFiller::FillTau2(const BNtau& Tau){
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

void DitauElectronFiller::FillElectron(const BNelectron& Electron){
    _ElectronPt.push_back(Electron.pt);
    _ElectronEta.push_back(Electron.eta);
    _ElectronPhi.push_back(Electron.phi);
    _ElectronRelIso.push_back(beanHelper->GetElectronRelIso(Electron));
    _ElectronIsLooseElectron.push_back(beanHelper->IsLooseElectron(Electron));
    _ElectronIsTightElectron.push_back(beanHelper->IsTightElectron(Electron));
	_LeptonEventWeight.push_back(beanHelper->GetElectronSF(Electron));

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
	BNmcparticle electronGenMatch = beanHelper->GetMatchedMCparticle(selectedMCparticles, Electron, 0.25);
	_ElectronGenMatchDaughter0Id			.push_back(electronGenMatch.daughter0Id);
	_ElectronGenMatchDaughter1Id			.push_back(electronGenMatch.daughter1Id);
	_ElectronGenMatchId						.push_back(electronGenMatch.id);
	_ElectronGenMatchMother0Id				.push_back(electronGenMatch.mother0Id);
	_ElectronGenMatchMother1Id				.push_back(electronGenMatch.mother1Id);
	_ElectronGenMatchGrandmother00Id		.push_back(electronGenMatch.grandMother00Id);
	_ElectronGenMatchGrandmother01Id		.push_back(electronGenMatch.grandMother01Id);
	_ElectronGenMatchGrandmother10Id		.push_back(electronGenMatch.grandMother10Id);
	_ElectronGenMatchGrandmother11Id		.push_back(electronGenMatch.grandMother11Id);
	_ElectronGenMatchDaughter0Status		.push_back(electronGenMatch.daughter0Status);
	_ElectronGenMatchDaughter1Status		.push_back(electronGenMatch.daughter1Status);
	_ElectronGenMatchStatus					.push_back(electronGenMatch.status);
	_ElectronGenMatchMother0Status			.push_back(electronGenMatch.mother0Status);
	_ElectronGenMatchMother1Status			.push_back(electronGenMatch.mother1Status);
	_ElectronGenMatchGrandmother00Status	.push_back(electronGenMatch.grandMother00Status);
	_ElectronGenMatchGrandmother01Status	.push_back(electronGenMatch.grandMother01Status);
	_ElectronGenMatchGrandmother10Status	.push_back(electronGenMatch.grandMother10Status);
	_ElectronGenMatchGrandmother11Status	.push_back(electronGenMatch.grandMother11Status);
   
}

void DitauElectronFiller::FillDitauElectron(const BNtau& Tau1, const BNtau& Tau2, const BNelectron& Electron){
	_DitauVisibleMass	.push_back(GetComboMassBN(Tau1, Tau2));
	_DitauCosDeltaPhi	.push_back(cos(TMath::Abs(normalizedPhi(Tau1.phi - Tau2.phi))));
	_DitauDeltaR		.push_back(reco::deltaR(Tau1.eta, Tau1.phi, Tau2.eta, Tau2.phi));
	_Tau1ElectronDeltaR		.push_back(reco::deltaR(Tau1.eta, Tau1.phi, Electron.eta, Electron.phi));
	_Tau2ElectronDeltaR		.push_back(reco::deltaR(Tau2.eta, Tau2.phi, Electron.eta, Electron.phi));
}


void DitauElectronFiller::MatchRecoAndGenHadTausFromH(){
	//FindGenTausFromHandW();

	/*_recoTauMatchedToGenHadTauFromH1 = FindClosestRecoTau(&genHadTauFromH1);
	_recoTauMatchedToGenHadTauFromH2 = FindClosestRecoTau(&genHadTauFromH2);
	_recoTauMatchedToGenHadTauFromW1 = FindClosestRecoTau(&genHadTauFromW1);
	_recoTauMatchedToGenHadTauFromW2 = FindClosestRecoTau(&genHadTauFromW2);//*/
}

/*pat::Tau * DitauElectronFiller::FindClosestRecoTau(reco::Candidate::LorentzVector * iParticle){

	if(iParticle->mag2()==0){ return NULL; }

	float minDeltaR = 999;
	pat::TauCollection::const_iterator closestTau;
	for ( pat::TauCollection::const_iterator Tau = _patTaus->begin(); Tau != _patTaus->end(); ++Tau ) {

			float thisDeltaR = reco::deltaR(Tau->eta(), Tau->phi(), iParticle->eta(), iParticle->phi());
			if(thisDeltaR < minDeltaR){
				minDeltaR = thisDeltaR;	
				closestTau = (Tau);
			}
	}

	return const_cast<pat::Tau*>(&(*closestTau));
}//*/

void DitauElectronFiller::FindGenTausFromHandW(){
/*	genHadTauFromH1 = reco::Candidate::LorentzVector(0,0,0,0);
	genHadTauFromH2 = reco::Candidate::LorentzVector(0,0,0,0);
	genHadTauFromW1 = reco::Candidate::LorentzVector(0,0,0,0);
	genHadTauFromW2 = reco::Candidate::LorentzVector(0,0,0,0);

	// Loop over all gen particles looking for taus
	unsigned int numGenHadTau		= 0;
	unsigned int numGenHadTauFromH	= 0;
	for(GenParticleCollection::const_iterator genParticle = _genParticles->begin(); genParticle != _genParticles->end(); ++genParticle){

		// Only care for taus
		if((abs(genParticle->pdgId()) != 15) || (genParticle->status() == 3)){ continue; }
		reco::Candidate::LorentzVector visGenTau = genParticle->p4();

		// Examine number of neutrinos
		bool foundElectron	= false;
		bool foundMuon		= false;
		for( unsigned int i=0; i < (genParticle->numberOfDaughters()); i++) {
			const reco::Candidate* daughterCand = genParticle->daughter(i);

			// Figure out the decay mode
			if( abs(daughterCand->pdgId()) == 12 ){ foundElectron	= true; }    
			if( abs(daughterCand->pdgId()) == 14 ){ foundMuon		= true; }    

			// Obtain visible momentum by subtracting the p4 of neutrinos
			if( (abs(daughterCand->pdgId()) == 12) || (abs(daughterCand->pdgId()) == 14) || (abs(daughterCand->pdgId()) == 16) ) {
				visGenTau = visGenTau - daughterCand->p4();
			}    
		}    
		// Fill decay mode
		if(foundElectron || foundMuon){ continue; }
		numGenHadTau++;

		const reco::Candidate* parent;
		if(genParticle->mother(0)->pdgId() == genParticle->pdgId()){    parent = genParticle->mother(0)->mother(0); }
		else{                                                           parent = genParticle->mother(0);            }  
		if(parent->pdgId() == 25){

			if(genHadTauFromH1.mag2() ==0){
				genHadTauFromH1 = visGenTau;
			}else if(genHadTauFromH1.pt() > visGenTau.pt()){
				genHadTauFromH2 = visGenTau;
			}else{
				genHadTauFromH2 = genHadTauFromH1;
				genHadTauFromH1 = visGenTau;
			}
		}else{
			if(genHadTauFromW1.mag2() == 0){
				genHadTauFromW1 = visGenTau;
			}else if(genHadTauFromW1.pt() > visGenTau.pt()){
				genHadTauFromW2 = visGenTau;
			}else{
				genHadTauFromW2 = genHadTauFromW1;
				genHadTauFromW1 = visGenTau;
			}
		
		}

	}
//*/
}

