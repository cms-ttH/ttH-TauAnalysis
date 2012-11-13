// Author: Nil Valls <nvallsve@nd.edu>, Jeff Kolb

#include "../interface/MuTauMuonFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
MuTauMuonFiller::MuTauMuonFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

MuTauMuonFiller::MuTauMuonFiller(const ParameterSet& iConfig, TTree* iTree, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper) {
	_FillerName	= __FILE__;
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
MuTauMuonFiller::~MuTauMuonFiller(){}

// ------------ method called to for each event  ------------
void MuTauMuonFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void MuTauMuonFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("MTM_NumTaus",&_NumTaus);
	_Tree->Branch("MTM_NumMuons",&_NumMuons);
	_Tree->Branch("MTM_NumCombos",&_NumCombos);
	_Tree->Branch("MTM_MomentumRank",&_MomentumRank);

	// === Tau1 === //
	_Tree->Branch("MTM_TauMomentumRank", &_TauMomentumRank);
	_Tree->Branch("MTM_TauPt", &_TauPt);
	_Tree->Branch("MTM_TauEta", &_TauEta);
	_Tree->Branch("MTM_TauPhi", &_TauPhi);
	_Tree->Branch("MTM_TauNProngs", &_TauNProngs);
	_Tree->Branch("MTM_TauNSignalGammas", &_TauNSignalGammas);
	_Tree->Branch("MTM_TauNSignalNeutrals", &_TauNSignalNeutrals);
	_Tree->Branch("MTM_TauNSignalPiZeros", &_TauNSignalPiZeros);
	_Tree->Branch("MTM_TauDecayMode", &_TauDecayMode);
	_Tree->Branch("MTM_TauEmFraction", &_TauEmFraction);
	_Tree->Branch("MTM_TauIsInTheCracks", &_TauIsInTheCracks);
	_Tree->Branch("MTM_TauHPSagainstElectronLoose", &_TauHPSagainstElectronLoose);
	_Tree->Branch("MTM_TauHPSagainstElectronMVA", &_TauHPSagainstElectronMVA);
	_Tree->Branch("MTM_TauHPSagainstElectronMedium", &_TauHPSagainstElectronMedium);
	_Tree->Branch("MTM_TauHPSagainstElectronTight", &_TauHPSagainstElectronTight);
	_Tree->Branch("MTM_TauHPSagainstMuonLoose", &_TauHPSagainstMuonLoose);
	_Tree->Branch("MTM_TauHPSagainstMuonMedium", &_TauHPSagainstMuonMedium);
	_Tree->Branch("MTM_TauHPSagainstMuonTight", &_TauHPSagainstMuonTight);
	_Tree->Branch("MTM_TauHPSbyLooseCombinedIsolationDeltaBetaCorr", &_TauHPSbyLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("MTM_TauHPSbyMediumCombinedIsolationDeltaBetaCorr", &_TauHPSbyMediumCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("MTM_TauHPSbyTightCombinedIsolationDeltaBetaCorr", &_TauHPSbyTightCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("MTM_TauHPSbyVLooseCombinedIsolationDeltaBetaCorr", &_TauHPSbyVLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("MTM_TauHPSdecayModeFinding", &_TauHPSdecayModeFinding);
	_Tree->Branch("MTM_TauLTPt", &_TauLTPt);
	_Tree->Branch("MTM_TauCharge", &_TauCharge);
	_Tree->Branch("MTM_TauLTvalid", &_TauLTvalid);
	_Tree->Branch("MTM_TauLTIpVtdxy", &_TauLTIpVtdxy);
	_Tree->Branch("MTM_TauLTIpVtdz", &_TauLTIpVtdz);
	_Tree->Branch("MTM_TauLTIpVtdxyError", &_TauLTIpVtdxyError);
	_Tree->Branch("MTM_TauLTIpVtdzError", &_TauLTIpVtdzError);
	_Tree->Branch("MTM_TauLTvx", &_TauLTvx);
	_Tree->Branch("MTM_TauLTvy", &_TauLTvy);
	_Tree->Branch("MTM_TauLTvz", &_TauLTvz);
	_Tree->Branch("MTM_TauLTValidHits", &_TauLTValidHits);
	_Tree->Branch("MTM_TauLTNormChiSqrd", &_TauLTNormChiSqrd);


	// === Muon1 === //
	_Tree->Branch("MTM_Muon1MomentumRank", &_Muon1MomentumRank);
	_Tree->Branch("MTM_Muon1Pt", &_Muon1Pt);
	_Tree->Branch("MTM_Muon1Eta", &_Muon1Eta);
	_Tree->Branch("MTM_Muon1Phi", &_Muon1Phi);
	_Tree->Branch("MTM_Muon1PfRelIso", &_Muon1PfIso);
	_Tree->Branch("MTM_Muon1IsLooseMuon", &_Muon1IsLooseMuon);
	_Tree->Branch("MTM_Muon1IsTightMuon", &_Muon1IsTightMuon);

	// === Muon2 === //
	_Tree->Branch("MTM_Muon2MomentumRank", &_Muon2MomentumRank);
	_Tree->Branch("MTM_Muon2Pt", &_Muon2Pt);
	_Tree->Branch("MTM_Muon2Eta", &_Muon2Eta);
	_Tree->Branch("MTM_Muon2Phi", &_Muon2Phi);
	_Tree->Branch("MTM_Muon2PfRelIso", &_Muon2PfIso);
	_Tree->Branch("MTM_Muon2IsLooseMuon", &_Muon2IsLooseMuon);
	_Tree->Branch("MTM_Muon2IsTightMuon", &_Muon2IsTightMuon);

	// === Combo === //
	_Tree->Branch("MTM_MuTauVisibleMass", &_MuTauVisibleMass);
	_Tree->Branch("MTM_MuTauMETMass", &_MuTauMETMass);
	_Tree->Branch("MTM_MuTauCosDeltaPhi", &_MuTauCosDeltaPhi);
	_Tree->Branch("MTM_MuTauDeltaR", 	&_MuTauDeltaR);
	_Tree->Branch("MTM_TauMuon1DeltaR", &_TauMuon1DeltaR);
	_Tree->Branch("MTM_TauMuon2DeltaR", &_TauMuon2DeltaR);
	_Tree->Branch("MTM_HT", &_HT);
	_Tree->Branch("MTM_NumCSVLbtags", &_NumCSVLbtags);
	_Tree->Branch("MTM_NumCSVMbtags", &_NumCSVMbtags);
	_Tree->Branch("MTM_NumCSVTbtags", &_NumCSVTbtags);
	_Tree->Branch("MTM_NumCSVLextraJets", &_NumCSVLextraJets);
	_Tree->Branch("MTM_NumCSVMextraJets", &_NumCSVMextraJets);
	_Tree->Branch("MTM_NumCSVTextraJets", &_NumCSVTextraJets);
}

// === Clear vectors that will be used to fill ntuple === //
void MuTauMuonFiller::ClearVectors(){

	_NumTaus										= 0;
	_NumMuons										= 0;
	_NumCombos										= 0;	
	_MomentumRank									.clear();

	// === Tau === //
	_TauMomentumRank										.clear();
	_TauPt											.clear();
	_TauEta										.clear();
	_TauPhi										.clear();
	_TauNProngs									.clear();
	_TauNSignalGammas								.clear();
	_TauNSignalNeutrals							.clear();
	_TauNSignalPiZeros								.clear();
	_TauDecayMode									.clear();
	_TauEmFraction									.clear();
	_TauIsInTheCracks								.clear();
	_TauHPSagainstElectronLoose					.clear();
	_TauHPSagainstElectronMVA						.clear();
	_TauHPSagainstElectronMedium					.clear();
	_TauHPSagainstElectronTight					.clear();
	_TauHPSagainstMuonLoose						.clear();
	_TauHPSagainstMuonMedium						.clear();
	_TauHPSagainstMuonTight						.clear();
	_TauHPSbyLooseCombinedIsolationDeltaBetaCorr	.clear();
	_TauHPSbyMediumCombinedIsolationDeltaBetaCorr	.clear();
	_TauHPSbyTightCombinedIsolationDeltaBetaCorr	.clear();
	_TauHPSbyVLooseCombinedIsolationDeltaBetaCorr	.clear();
	_TauHPSdecayModeFinding						.clear();
	_TauLTPt										.clear();
	_TauCharge										.clear();
	_TauLTvalid									.clear();
	_TauLTIpVtdxy									.clear();
	_TauLTIpVtdz									.clear();
	_TauLTIpVtdxyError								.clear();
	_TauLTIpVtdzError								.clear();
	_TauLTvx										.clear();
	_TauLTvy										.clear();
	_TauLTvz										.clear();
	_TauLTValidHits								.clear();
	_TauLTNormChiSqrd								.clear();


	// === Muon1 === //
	_Muon1MomentumRank								.clear();
	_Muon1Pt											.clear();
	_Muon1Eta										.clear();
	_Muon1Phi										.clear();
    _Muon1PfIso                                      .clear();
    _Muon1IsTightMuon                                .clear();
    _Muon1IsLooseMuon                                .clear();

	// === Muon2 === //
	_Muon2MomentumRank								.clear();
	_Muon2Pt											.clear();
	_Muon2Eta										.clear();
	_Muon2Phi										.clear();
    _Muon2PfIso                                      .clear();
    _Muon2IsTightMuon                                .clear();
    _Muon2IsLooseMuon                                .clear();

	// === Combo === //
	_MuTauVisibleMass								.clear();
	_MuTauMETMass									.clear();
	_MuTauCosDeltaPhi								.clear();
	_MuTauDeltaR									.clear();
	_TauMuon1DeltaR									.clear();
	_TauMuon2DeltaR									.clear();
	_HT												.clear();
	_NumCSVLbtags									.clear();
	_NumCSVMbtags									.clear();
	_NumCSVTbtags									.clear();
	_NumCSVLextraJets								.clear();
	_NumCSVMextraJets								.clear();
	_NumCSVTextraJets								.clear();

}

// === Fill ntuple === //
void MuTauMuonFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){

	// Get the object collections from the event
	GetCollections(iEvent, iSetup);

	// Clear vectors
	ClearVectors();


}
