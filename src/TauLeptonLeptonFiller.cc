// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/TauLeptonLeptonFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
TauLeptonLeptonFiller::TauLeptonLeptonFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

TauLeptonLeptonFiller::TauLeptonLeptonFiller(const ParameterSet& iConfig, TTree* iTree, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper) {
	_FillerName	= __FILE__;
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
TauLeptonLeptonFiller::~TauLeptonLeptonFiller(){}

// ------------ method called to for each event  ------------
void TauLeptonLeptonFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void TauLeptonLeptonFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("TLL_NumTaus",&_NumTaus);
	_Tree->Branch("TLL_NumLooseMuons",&_NumLooseMuons);
	_Tree->Branch("TLL_NumExLooseMuons",&_NumExLooseMuons);
	_Tree->Branch("TLL_NumTightMuons",&_NumTightMuons);
	_Tree->Branch("TLL_NumLooseElectrons",&_NumLooseElectrons);
	_Tree->Branch("TLL_NumExLooseElectrons",&_NumExLooseElectrons);
	_Tree->Branch("TLL_NumTightElectrons",&_NumTightElectrons);
	_Tree->Branch("TLL_NumCombos",&_NumCombos);
	_Tree->Branch("TLL_MomentumRank",&_MomentumRank);

	// === Tau === //
	_Tree->Branch("TLL_TauMomentumRank", &_TauMomentumRank);
	_Tree->Branch("TLL_TauPt", &_TauPt);
	_Tree->Branch("TLL_TauEta", &_TauEta);
	_Tree->Branch("TLL_TauPhi", &_TauPhi);
	_Tree->Branch("TLL_TauNProngs", &_TauNProngs);
	_Tree->Branch("TLL_TauNSignalGammas", &_TauNSignalGammas);
	_Tree->Branch("TLL_TauNSignalNeutrals", &_TauNSignalNeutrals);
	_Tree->Branch("TLL_TauDecayMode", &_TauDecayMode);
	_Tree->Branch("TLL_TauEmFraction", &_TauEmFraction);
	_Tree->Branch("TLL_TauIsInTheCracks", &_TauIsInTheCracks);

    _Tree->Branch("TLL_TauHPSagainstElectronDeadECAL", &_TauHPSagainstElectronDeadECAL);
    _Tree->Branch("TLL_TauHPSagainstElectronLoose", &_TauHPSagainstElectronLoose);
    _Tree->Branch("TLL_TauHPSagainstElectronLooseMVA2", &_TauHPSagainstElectronLooseMVA2);
    _Tree->Branch("TLL_TauHPSagainstElectronLooseMVA3", &_TauHPSagainstElectronLooseMVA3);
    _Tree->Branch("TLL_TauHPSagainstElectronMVA", &_TauHPSagainstElectronMVA);
    _Tree->Branch("TLL_TauHPSagainstElectronMVA2category", &_TauHPSagainstElectronMVA2category);
    _Tree->Branch("TLL_TauHPSagainstElectronMVA2raw", &_TauHPSagainstElectronMVA2raw);
    _Tree->Branch("TLL_TauHPSagainstElectronMVA3category", &_TauHPSagainstElectronMVA3category);
    _Tree->Branch("TLL_TauHPSagainstElectronMVA3raw", &_TauHPSagainstElectronMVA3raw);
    _Tree->Branch("TLL_TauHPSagainstElectronMedium", &_TauHPSagainstElectronMedium);
    _Tree->Branch("TLL_TauHPSagainstElectronMediumMVA2", &_TauHPSagainstElectronMediumMVA2);
    _Tree->Branch("TLL_TauHPSagainstElectronMediumMVA3", &_TauHPSagainstElectronMediumMVA3);
    _Tree->Branch("TLL_TauHPSagainstElectronTight", &_TauHPSagainstElectronTight);
    _Tree->Branch("TLL_TauHPSagainstElectronTightMVA2", &_TauHPSagainstElectronTightMVA2);
    _Tree->Branch("TLL_TauHPSagainstElectronTightMVA3", &_TauHPSagainstElectronTightMVA3);
    _Tree->Branch("TLL_TauHPSagainstElectronVLooseMVA2", &_TauHPSagainstElectronVLooseMVA2);
    _Tree->Branch("TLL_TauHPSagainstElectronVTightMVA3", &_TauHPSagainstElectronVTightMVA3);
    _Tree->Branch("TLL_TauHPSagainstMuonLoose", &_TauHPSagainstMuonLoose);
    _Tree->Branch("TLL_TauHPSagainstMuonLoose2", &_TauHPSagainstMuonLoose2);
    _Tree->Branch("TLL_TauHPSagainstMuonMedium", &_TauHPSagainstMuonMedium);
    _Tree->Branch("TLL_TauHPSagainstMuonMedium2", &_TauHPSagainstMuonMedium2);
    _Tree->Branch("TLL_TauHPSagainstMuonTight", &_TauHPSagainstMuonTight);
    _Tree->Branch("TLL_TauHPSagainstMuonTight2", &_TauHPSagainstMuonTight2);
    _Tree->Branch("TLL_TauHPSbyCombinedIsolationDeltaBetaCorrRaw", &_TauHPSbyCombinedIsolationDeltaBetaCorrRaw);
    _Tree->Branch("TLL_TauHPSbyCombinedIsolationDeltaBetaCorrRaw3Hits", &_TauHPSbyCombinedIsolationDeltaBetaCorrRaw3Hits);
    _Tree->Branch("TLL_TauHPSbyIsolationMVA2raw", &_TauHPSbyIsolationMVA2raw);
    _Tree->Branch("TLL_TauHPSbyLooseCombinedIsolationDeltaBetaCorr", &_TauHPSbyLooseCombinedIsolationDeltaBetaCorr);
    _Tree->Branch("TLL_TauHPSbyLooseCombinedIsolationDeltaBetaCorr3Hits", &_TauHPSbyLooseCombinedIsolationDeltaBetaCorr3Hits);
    _Tree->Branch("TLL_TauHPSbyLooseIsolationMVA", &_TauHPSbyLooseIsolationMVA);
    _Tree->Branch("TLL_TauHPSbyLooseIsolationMVA2", &_TauHPSbyLooseIsolationMVA2);
    _Tree->Branch("TLL_TauHPSbyMediumCombinedIsolationDeltaBetaCorr", &_TauHPSbyMediumCombinedIsolationDeltaBetaCorr);
    _Tree->Branch("TLL_TauHPSbyMediumCombinedIsolationDeltaBetaCorr3Hits", &_TauHPSbyMediumCombinedIsolationDeltaBetaCorr3Hits);
    _Tree->Branch("TLL_TauHPSbyMediumIsolationMVA", &_TauHPSbyMediumIsolationMVA);
    _Tree->Branch("TLL_TauHPSbyMediumIsolationMVA2", &_TauHPSbyMediumIsolationMVA2);
    _Tree->Branch("TLL_TauHPSbyTightCombinedIsolationDeltaBetaCorr", &_TauHPSbyTightCombinedIsolationDeltaBetaCorr);
    _Tree->Branch("TLL_TauHPSbyTightCombinedIsolationDeltaBetaCorr3Hits", &_TauHPSbyTightCombinedIsolationDeltaBetaCorr3Hits);
    _Tree->Branch("TLL_TauHPSbyTightIsolationMVA", &_TauHPSbyTightIsolationMVA);
    _Tree->Branch("TLL_TauHPSbyTightIsolationMVA2", &_TauHPSbyTightIsolationMVA2);
    _Tree->Branch("TLL_TauHPSbyVLooseCombinedIsolationDeltaBetaCorr", &_TauHPSbyVLooseCombinedIsolationDeltaBetaCorr);
    _Tree->Branch("TLL_TauHPSdecayModeFinding", &_TauHPSdecayModeFinding);
    _Tree->Branch("TLL_TauHPSbyIsolationMVAraw", &_TauHPSbyIsolationMVAraw);
	
    _Tree->Branch("TLL_TauLTPt", &_TauLTPt);
	_Tree->Branch("TLL_TauCharge", &_TauCharge);
	_Tree->Branch("TLL_TauLTvalid", &_TauLTvalid);
	_Tree->Branch("TLL_TauLTIpVtdxy", &_TauLTIpVtdxy);
	_Tree->Branch("TLL_TauLTIpVtdz", &_TauLTIpVtdz);
	_Tree->Branch("TLL_TauLTIpVtdxyError", &_TauLTIpVtdxyError);
	_Tree->Branch("TLL_TauLTIpVtdzError", &_TauLTIpVtdzError);
	_Tree->Branch("TLL_TauLTvx", &_TauLTvx);
	_Tree->Branch("TLL_TauLTvy", &_TauLTvy);
	_Tree->Branch("TLL_TauLTvz", &_TauLTvz);
	_Tree->Branch("TLL_TauLTValidHits", &_TauLTValidHits);
	_Tree->Branch("TLL_TauLTNormChiSqrd", &_TauLTNormChiSqrd);

	_Tree->Branch("TLL_TauGenMatchDaughter0Id", &_TauGenMatchDaughter0Id);
	_Tree->Branch("TLL_TauGenMatchDaughter1Id", &_TauGenMatchDaughter1Id);
	_Tree->Branch("TLL_TauGenMatchId", &_TauGenMatchId);
	_Tree->Branch("TLL_TauGenMatchMother0Id", &_TauGenMatchMother0Id);
	_Tree->Branch("TLL_TauGenMatchMother1Id", &_TauGenMatchMother1Id);
	_Tree->Branch("TLL_TauGenMatchGrandmother00Id", &_TauGenMatchGrandmother00Id);
	_Tree->Branch("TLL_TauGenMatchGrandmother01Id", &_TauGenMatchGrandmother01Id);
	_Tree->Branch("TLL_TauGenMatchGrandmother10Id", &_TauGenMatchGrandmother10Id);
	_Tree->Branch("TLL_TauGenMatchGrandmother11Id", &_TauGenMatchGrandmother11Id);
	_Tree->Branch("TLL_TauGenMatchDaughter0Status", &_TauGenMatchDaughter0Status);
	_Tree->Branch("TLL_TauGenMatchDaughter1Status", &_TauGenMatchDaughter1Status);
	_Tree->Branch("TLL_TauGenMatchStatus", &_TauGenMatchStatus);
	_Tree->Branch("TLL_TauGenMatchMother0Status", &_TauGenMatchMother0Status);
	_Tree->Branch("TLL_TauGenMatchMother1Status", &_TauGenMatchMother1Status);
	_Tree->Branch("TLL_TauGenMatchGrandmother00Status", &_TauGenMatchGrandmother00Status);
	_Tree->Branch("TLL_TauGenMatchGrandmother01Status", &_TauGenMatchGrandmother01Status);
	_Tree->Branch("TLL_TauGenMatchGrandmother10Status", &_TauGenMatchGrandmother10Status);
	_Tree->Branch("TLL_TauGenMatchGrandmother11Status", &_TauGenMatchGrandmother11Status);

	// === Lepton1 === //
	_Tree->Branch("TLL_Lepton1IsMuon", &_Lepton1IsMuon);
	_Tree->Branch("TLL_Lepton1IsElectron", &_Lepton1IsElectron);
	_Tree->Branch("TLL_Lepton1Pt", &_Lepton1Pt);
	_Tree->Branch("TLL_Lepton1Eta", &_Lepton1Eta);
	_Tree->Branch("TLL_Lepton1Phi", &_Lepton1Phi);
	_Tree->Branch("TLL_Lepton1RelIso", &_Lepton1RelIso);
	_Tree->Branch("TLL_Lepton1IsLoose", &_Lepton1IsLoose);
	_Tree->Branch("TLL_Lepton1IsTight", &_Lepton1IsTight);
	_Tree->Branch("TLL_Lepton1EventWeight",&_Lepton1EventWeight);
	_Tree->Branch("TLL_Lepton1GenMatchDaughter0Id", &_Lepton1GenMatchDaughter0Id);
	_Tree->Branch("TLL_Lepton1GenMatchDaughter1Id", &_Lepton1GenMatchDaughter1Id);
	_Tree->Branch("TLL_Lepton1GenMatchId", &_Lepton1GenMatchId);
	_Tree->Branch("TLL_Lepton1GenMatchMother0Id", &_Lepton1GenMatchMother0Id);
	_Tree->Branch("TLL_Lepton1GenMatchMother1Id", &_Lepton1GenMatchMother1Id);
	_Tree->Branch("TLL_Lepton1GenMatchGrandmother00Id", &_Lepton1GenMatchGrandmother00Id);
	_Tree->Branch("TLL_Lepton1GenMatchGrandmother01Id", &_Lepton1GenMatchGrandmother01Id);
	_Tree->Branch("TLL_Lepton1GenMatchGrandmother10Id", &_Lepton1GenMatchGrandmother10Id);
	_Tree->Branch("TLL_Lepton1GenMatchGrandmother11Id", &_Lepton1GenMatchGrandmother11Id);
	_Tree->Branch("TLL_Lepton1GenMatchDaughter0Status", &_Lepton1GenMatchDaughter0Status);
	_Tree->Branch("TLL_Lepton1GenMatchDaughter1Status", &_Lepton1GenMatchDaughter1Status);
	_Tree->Branch("TLL_Lepton1GenMatchStatus", &_Lepton1GenMatchStatus);
	_Tree->Branch("TLL_Lepton1GenMatchMother0Status", &_Lepton1GenMatchMother0Status);
	_Tree->Branch("TLL_Lepton1GenMatchMother1Status", &_Lepton1GenMatchMother1Status);
	_Tree->Branch("TLL_Lepton1GenMatchGrandmother00Status", &_Lepton1GenMatchGrandmother00Status);
	_Tree->Branch("TLL_Lepton1GenMatchGrandmother01Status", &_Lepton1GenMatchGrandmother01Status);
	_Tree->Branch("TLL_Lepton1GenMatchGrandmother10Status", &_Lepton1GenMatchGrandmother10Status);
	_Tree->Branch("TLL_Lepton1GenMatchGrandmother11Status", &_Lepton1GenMatchGrandmother11Status);

	// === Lepton2 === //
	_Tree->Branch("TLL_Lepton2IsMuon", &_Lepton2IsMuon);
	_Tree->Branch("TLL_Lepton2IsElectron", &_Lepton2IsElectron);
	_Tree->Branch("TLL_Lepton2Pt", &_Lepton2Pt);
	_Tree->Branch("TLL_Lepton2Eta", &_Lepton2Eta);
	_Tree->Branch("TLL_Lepton2Phi", &_Lepton2Phi);
	_Tree->Branch("TLL_Lepton2RelIso", &_Lepton2RelIso);
	_Tree->Branch("TLL_Lepton2IsLoose", &_Lepton2IsLoose);
	_Tree->Branch("TLL_Lepton2IsTight", &_Lepton2IsTight);
	_Tree->Branch("TLL_Lepton2EventWeight",&_Lepton2EventWeight);
	_Tree->Branch("TLL_Lepton2GenMatchDaughter0Id", &_Lepton2GenMatchDaughter0Id);
	_Tree->Branch("TLL_Lepton2GenMatchDaughter1Id", &_Lepton2GenMatchDaughter1Id);
	_Tree->Branch("TLL_Lepton2GenMatchId", &_Lepton2GenMatchId);
	_Tree->Branch("TLL_Lepton2GenMatchMother0Id", &_Lepton2GenMatchMother0Id);
	_Tree->Branch("TLL_Lepton2GenMatchMother1Id", &_Lepton2GenMatchMother1Id);
	_Tree->Branch("TLL_Lepton2GenMatchGrandmother00Id", &_Lepton2GenMatchGrandmother00Id);
	_Tree->Branch("TLL_Lepton2GenMatchGrandmother01Id", &_Lepton2GenMatchGrandmother01Id);
	_Tree->Branch("TLL_Lepton2GenMatchGrandmother10Id", &_Lepton2GenMatchGrandmother10Id);
	_Tree->Branch("TLL_Lepton2GenMatchGrandmother11Id", &_Lepton2GenMatchGrandmother11Id);
	_Tree->Branch("TLL_Lepton2GenMatchDaughter0Status", &_Lepton2GenMatchDaughter0Status);
	_Tree->Branch("TLL_Lepton2GenMatchDaughter1Status", &_Lepton2GenMatchDaughter1Status);
	_Tree->Branch("TLL_Lepton2GenMatchStatus", &_Lepton2GenMatchStatus);
	_Tree->Branch("TLL_Lepton2GenMatchMother0Status", &_Lepton2GenMatchMother0Status);
	_Tree->Branch("TLL_Lepton2GenMatchMother1Status", &_Lepton2GenMatchMother1Status);
	_Tree->Branch("TLL_Lepton2GenMatchGrandmother00Status", &_Lepton2GenMatchGrandmother00Status);
	_Tree->Branch("TLL_Lepton2GenMatchGrandmother01Status", &_Lepton2GenMatchGrandmother01Status);
	_Tree->Branch("TLL_Lepton2GenMatchGrandmother10Status", &_Lepton2GenMatchGrandmother10Status);
	_Tree->Branch("TLL_Lepton2GenMatchGrandmother11Status", &_Lepton2GenMatchGrandmother11Status);


	// === Combo === //
	_Tree->Branch("TLL_TauLepton1VisibleMass", &_TauLepton1VisibleMass);
	_Tree->Branch("TLL_TauLepton2VisibleMass", &_TauLepton2VisibleMass);
	_Tree->Branch("TLL_TauLepton1METMass", &_TauLepton1METMass);
	_Tree->Branch("TLL_TauLepton2METMass", &_TauLepton2METMass);
	_Tree->Branch("TLL_Lepton1Lepton2VisibleMass", &_Lepton1Lepton2VisibleMass);
	_Tree->Branch("TLL_TauLepton1CosDeltaPhi", &_TauLepton1CosDeltaPhi);
	_Tree->Branch("TLL_TauLepton2CosDeltaPhi", &_TauLepton2CosDeltaPhi);
	_Tree->Branch("TLL_Lepton1Lepton2CosDeltaPhi", &_Lepton1Lepton2CosDeltaPhi);
	_Tree->Branch("TLL_TauLepton1DeltaR", &_TauLepton1DeltaR);
	_Tree->Branch("TLL_TauLepton2DeltaR", &_TauLepton2DeltaR);
	_Tree->Branch("TLL_Lepton1Lepton2DeltaR", &_Lepton1Lepton2DeltaR);
	_Tree->Branch("TLL_HT", &_HT);
	_Tree->Branch("TLL_NumCSVLbtagJets", &_NumCSVLbtagJets);
	_Tree->Branch("TLL_NumCSVMbtagJets", &_NumCSVMbtagJets);
	_Tree->Branch("TLL_NumCSVTbtagJets", &_NumCSVTbtagJets);
	_Tree->Branch("TLL_NumNonCSVLbtagJets", &_NumNonCSVLbtagJets);
	_Tree->Branch("TLL_NumNonCSVMbtagJets", &_NumNonCSVMbtagJets);
	_Tree->Branch("TLL_NumNonCSVTbtagJets", &_NumNonCSVTbtagJets);
	_Tree->Branch("TLL_NumCleanCSVLbtagJets", &_NumCleanCSVLbtagJets);
	_Tree->Branch("TLL_NumCleanCSVMbtagJets", &_NumCleanCSVMbtagJets);
	_Tree->Branch("TLL_NumCleanCSVTbtagJets", &_NumCleanCSVTbtagJets);
	_Tree->Branch("TLL_NumCleanNonCSVLbtagJets", &_NumCleanNonCSVLbtagJets);
	_Tree->Branch("TLL_NumCleanNonCSVMbtagJets", &_NumCleanNonCSVMbtagJets);
	_Tree->Branch("TLL_NumCleanNonCSVTbtagJets", &_NumCleanNonCSVTbtagJets);
}

// === Clear vectors that will be used to fill ntuple === //
void TauLeptonLeptonFiller::ClearVectors(){

	_NumTaus										= 0;
	_NumCombos										= 0;	
	_MomentumRank									.clear();

	// === Tau === //
	_TauMomentumRank								.clear();
	_TauPt											.clear();
	_TauEta										.clear();
	_TauPhi										.clear();
	_TauNProngs									.clear();
	_TauNSignalGammas								.clear();
	_TauNSignalNeutrals							.clear();
	_TauDecayMode									.clear();
	_TauEmFraction									.clear();
	_TauIsInTheCracks								.clear();
	_TauHPSagainstElectronDeadECAL                      .clear();
	_TauHPSagainstElectronLoose                         .clear();
	_TauHPSagainstElectronLooseMVA2                     .clear();
	_TauHPSagainstElectronLooseMVA3                     .clear();
	_TauHPSagainstElectronMVA                           .clear();
	_TauHPSagainstElectronMVA2category                  .clear();
	_TauHPSagainstElectronMVA2raw                       .clear();
	_TauHPSagainstElectronMVA3category                  .clear();
	_TauHPSagainstElectronMVA3raw                       .clear();
	_TauHPSagainstElectronMedium                        .clear();
	_TauHPSagainstElectronMediumMVA2                    .clear();
	_TauHPSagainstElectronMediumMVA3                    .clear();
	_TauHPSagainstElectronTight                         .clear();
	_TauHPSagainstElectronTightMVA2                     .clear();
	_TauHPSagainstElectronTightMVA3                     .clear();
	_TauHPSagainstElectronVLooseMVA2                    .clear();
	_TauHPSagainstElectronVTightMVA3                    .clear();
	_TauHPSagainstMuonLoose                             .clear();
	_TauHPSagainstMuonLoose2                            .clear();
	_TauHPSagainstMuonMedium                            .clear();
	_TauHPSagainstMuonMedium2                           .clear();
	_TauHPSagainstMuonTight                             .clear();
	_TauHPSagainstMuonTight2                            .clear();
	_TauHPSbyCombinedIsolationDeltaBetaCorrRaw          .clear();
	_TauHPSbyCombinedIsolationDeltaBetaCorrRaw3Hits     .clear();
	_TauHPSbyIsolationMVA2raw                           .clear();
	_TauHPSbyLooseCombinedIsolationDeltaBetaCorr        .clear();
	_TauHPSbyLooseCombinedIsolationDeltaBetaCorr3Hits   .clear();
	_TauHPSbyLooseIsolationMVA                          .clear();
	_TauHPSbyLooseIsolationMVA2                         .clear();
	_TauHPSbyMediumCombinedIsolationDeltaBetaCorr       .clear();
	_TauHPSbyMediumCombinedIsolationDeltaBetaCorr3Hits  .clear();
	_TauHPSbyMediumIsolationMVA                         .clear();
	_TauHPSbyMediumIsolationMVA2                        .clear();
	_TauHPSbyTightCombinedIsolationDeltaBetaCorr        .clear();
	_TauHPSbyTightCombinedIsolationDeltaBetaCorr3Hits   .clear();
	_TauHPSbyTightIsolationMVA                          .clear();
	_TauHPSbyTightIsolationMVA2                         .clear();
	_TauHPSbyVLooseCombinedIsolationDeltaBetaCorr       .clear();
	_TauHPSdecayModeFinding                             .clear();
	_TauHPSbyIsolationMVAraw                            .clear();
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
	_TauGenMatchDaughter0Id						.clear();
	_TauGenMatchDaughter1Id						.clear();
	_TauGenMatchId									.clear();
	_TauGenMatchMother0Id							.clear();
	_TauGenMatchMother1Id							.clear();
	_TauGenMatchGrandmother00Id					.clear();
	_TauGenMatchGrandmother01Id					.clear();
	_TauGenMatchGrandmother10Id					.clear();
	_TauGenMatchGrandmother11Id					.clear();
	_TauGenMatchDaughter0Status					.clear();
	_TauGenMatchDaughter1Status					.clear();
	_TauGenMatchStatus								.clear();
	_TauGenMatchMother0Status						.clear();
	_TauGenMatchMother1Status						.clear();
	_TauGenMatchGrandmother00Status				.clear();
	_TauGenMatchGrandmother01Status				.clear();
	_TauGenMatchGrandmother10Status				.clear();
	_TauGenMatchGrandmother11Status				.clear();

	// === Lepton === //
	_NumLooseMuons									.clear();
	_NumExLooseMuons								.clear();
	_NumTightMuons									.clear();
	_NumLooseElectrons								.clear();
	_NumExLooseElectrons							.clear();
	_NumTightElectrons								.clear();
	_Lepton1Pt										.clear();
	_Lepton1Eta										.clear();
	_Lepton1Phi										.clear();
    _Lepton1RelIso									.clear();
    _Lepton1IsTight									.clear();
    _Lepton1IsLoose									.clear();
	_Lepton1EventWeight								.clear();
	_Lepton1GenMatchDaughter0Id						.clear();
	_Lepton1GenMatchDaughter1Id						.clear();
	_Lepton1GenMatchId								.clear();
	_Lepton1GenMatchMother0Id						.clear();
	_Lepton1GenMatchMother1Id						.clear();
	_Lepton1GenMatchGrandmother00Id					.clear();
	_Lepton1GenMatchGrandmother01Id					.clear();
	_Lepton1GenMatchGrandmother10Id					.clear();
	_Lepton1GenMatchGrandmother11Id					.clear();
	_Lepton1GenMatchDaughter0Status					.clear();
	_Lepton1GenMatchDaughter1Status					.clear();
	_Lepton1GenMatchStatus							.clear();
	_Lepton1GenMatchMother0Status					.clear();
	_Lepton1GenMatchMother1Status					.clear();
	_Lepton1GenMatchGrandmother00Status				.clear();
	_Lepton1GenMatchGrandmother01Status				.clear();
	_Lepton1GenMatchGrandmother10Status				.clear();
	_Lepton1GenMatchGrandmother11Status				.clear();
	_Lepton2Pt										.clear();
	_Lepton2Eta										.clear();
	_Lepton2Phi										.clear();
    _Lepton2RelIso									.clear();
    _Lepton2IsTight									.clear();
    _Lepton2IsLoose									.clear();
	_Lepton2EventWeight								.clear();
	_Lepton2GenMatchDaughter0Id						.clear();
	_Lepton2GenMatchDaughter1Id						.clear();
	_Lepton2GenMatchId								.clear();
	_Lepton2GenMatchMother0Id						.clear();
	_Lepton2GenMatchMother1Id						.clear();
	_Lepton2GenMatchGrandmother00Id					.clear();
	_Lepton2GenMatchGrandmother01Id					.clear();
	_Lepton2GenMatchGrandmother10Id					.clear();
	_Lepton2GenMatchGrandmother11Id					.clear();
	_Lepton2GenMatchDaughter0Status					.clear();
	_Lepton2GenMatchDaughter1Status					.clear();
	_Lepton2GenMatchStatus							.clear();
	_Lepton2GenMatchMother0Status					.clear();
	_Lepton2GenMatchMother1Status					.clear();
	_Lepton2GenMatchGrandmother00Status				.clear();
	_Lepton2GenMatchGrandmother01Status				.clear();
	_Lepton2GenMatchGrandmother10Status				.clear();
	_Lepton2GenMatchGrandmother11Status				.clear();

	// === Combo === //
	_TauLepton1VisibleMass							.clear();
	_TauLepton2VisibleMass							.clear();
	_TauLepton1METMass								.clear();
	_TauLepton2METMass								.clear();
	_Lepton1Lepton2VisibleMass						.clear();
	_TauLepton1CosDeltaPhi							.clear();
	_TauLepton2CosDeltaPhi							.clear();
	_Lepton1Lepton2CosDeltaPhi						.clear();
	_TauLepton1DeltaR								.clear();
	_TauLepton2DeltaR								.clear();
	_Lepton1Lepton2DeltaR							.clear();
	_HT												.clear();
	_NumCSVLbtagJets								.clear();
	_NumCSVMbtagJets								.clear();
	_NumCSVTbtagJets								.clear();
	_NumNonCSVLbtagJets								.clear();
	_NumNonCSVMbtagJets								.clear();
	_NumNonCSVTbtagJets								.clear();
	_NumCleanCSVLbtagJets							.clear();
	_NumCleanCSVMbtagJets							.clear();
	_NumCleanCSVTbtagJets							.clear();
	_NumCleanNonCSVLbtagJets						.clear();
	_NumCleanNonCSVMbtagJets						.clear();
	_NumCleanNonCSVTbtagJets						.clear();
}

// === Fill ntuple === //
void TauLeptonLeptonFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){

	// Get the object collections from the event
	GetCollections(iEvent, iSetup);

	// Clear vectors
	ClearVectors();

	// Leptons
	BNelectronCollection tightElectrons		= beanHelper->GetSelectedElectrons(_BNelectrons, electronID::electronTight);
	BNmuonCollection tightMuons				= beanHelper->GetSelectedMuons(_BNmuons, muonID::muonTight);
	BNleptonCollection tightLeptons;
	tightLeptons.push_back(tightElectrons);
	tightLeptons.push_back(tightMuons);
	tightLeptons.sort();

	BNelectronCollection looseElectrons		= beanHelper->GetSelectedElectrons(_BNelectrons, electronID::electronLoose);
	BNmuonCollection looseMuons				= beanHelper->GetSelectedMuons(_BNmuons, muonID::muonLoose);
	BNleptonCollection looseLeptons;
	looseLeptons.push_back(looseElectrons);
	looseLeptons.push_back(looseMuons);
	looseLeptons.sort();

	BNelectronCollection exLooseElectrons	= beanHelper->GetDifference(looseElectrons, tightElectrons);
	BNmuonCollection exLooseMuons			= beanHelper->GetDifference(looseMuons, tightMuons);
	BNleptonCollection exLooseLeptons;
	exLooseLeptons.push_back(exLooseElectrons);
	exLooseLeptons.push_back(exLooseMuons);
	exLooseLeptons.sort();

	// Make sure we can at least make one TLL combo
	if(looseLeptons.size() < 2){ return; } // At least two tight or loose leptons
	if(tightLeptons.size() < 1){ return; } // At least one tight lepton

    // Taus  (corrected taus currently just account for systematic shifts)
    BNtauCollection correctedTaus =  beanHelper->GetCorrectedTaus(_BNtaus, _sysType);
	BNtauCollection selectedTaus = beanHelper->GetSelectedTaus(correctedTaus, tauID::tauNonIso);

	// Make sure we can at least make one TLL combo
	if(correctedTaus.size() < 1){ return; } // At least one tau

	// Tau loops: Tau1 is always leads in pT
	unsigned int theNumberOfTaus		= 0;

	// Start loop over Taus so select two (if applicable) that form a good combo
	_NumTaus = selectedTaus.size();
	theNumberOfTaus = 0;
	for ( BNtauCollection::const_iterator Tau = selectedTaus.begin(); Tau != selectedTaus.end(); ++Tau ) {
		theNumberOfTaus++;

			// Clean leptons
			BNleptonCollection cleanLooseLeptons	= GetUnmatchedLeptons(*Tau, looseLeptons,	0.15);
			BNleptonCollection cleanExLooseLeptons	= GetUnmatchedLeptons(*Tau, exLooseLeptons,	0.15);
			BNleptonCollection cleanTightLeptons	= GetUnmatchedLeptons(*Tau, tightLeptons,	0.15);

			// Make sure we can at least make one TLL combo
			if(cleanLooseLeptons.size() != 2){ continue; } // Exactly two tight or loose leptons
			if(cleanTightLeptons.size() < 1){ continue; } // At least one tight lepton


			// Count loose leptons
			unsigned int numLooseElectrons = 0;
			unsigned int numLooseMuons = 0;
			for(BNleptonCollection::const_iterator it = cleanLooseLeptons.begin(); it != cleanLooseLeptons.end(); ++it){
				if((*it)->isElectron){ numLooseElectrons++; }
				else if((*it)->isMuon){ numLooseMuons++; }
			}
			_NumLooseElectrons		.push_back(numLooseElectrons);
			_NumLooseMuons			.push_back(numLooseMuons);

			// Count exLoose leptons
			unsigned int numExLooseElectrons = 0;
			unsigned int numExLooseMuons = 0;
			for(BNleptonCollection::const_iterator it = cleanExLooseLeptons.begin(); it != cleanExLooseLeptons.end(); ++it){
				if((*it)->isElectron){ numExLooseElectrons++; }
				else if((*it)->isMuon){ numExLooseMuons++; }
			}
			_NumExLooseElectrons	.push_back(numExLooseElectrons);
			_NumExLooseMuons		.push_back(numExLooseMuons);

			// Count tight leptons
			unsigned int numTightElectrons = 0;
			unsigned int numTightMuons = 0;
			for(BNleptonCollection::const_iterator it = cleanTightLeptons.begin(); it != cleanTightLeptons.end(); ++it){
				if((*it)->isElectron){ numTightElectrons++; }
				else if((*it)->isMuon){ numTightMuons++; }
			}
			_NumTightElectrons		.push_back(numTightElectrons);//*/
			_NumTightMuons			.push_back(numTightMuons);


			// Get the two leptons in question
			BNlepton* Lepton1 = cleanLooseLeptons.at(0);
			BNlepton* Lepton2 = cleanLooseLeptons.at(1);


			// Jets and MET and related quantities
			// Correct for jet pT
			BNjetCollection correctedJets                           = beanHelper->GetCorrectedJets(_BNjets, _sysType);
			// Apply kinematic requirements on corrected jets
			BNjetCollection selCorrJets                             = beanHelper->GetSelectedJets(correctedJets, 30, 2.4, jetID::jetLoose, '-');
			vector<TLorentzVector> tauAndLeptons; // Clean jets from taus and leptons
			tauAndLeptons.push_back(TLorentzVector(Tau->px, Tau->py, Tau->pz, Tau->energy));
			tauAndLeptons.push_back(TLorentzVector(Lepton1->px, Lepton1->py, Lepton1->pz, Lepton1->energy));
			tauAndLeptons.push_back(TLorentzVector(Lepton2->px, Lepton2->py, Lepton2->pz, Lepton2->energy));
			
			// Clean jets
			BNjetCollection cleanSelCorrJets						= beanHelper->GetCleanJets(selCorrJets, tauAndLeptons, 0.25);

			// Derive quantities based on the corrected MET based on the clean, corrected, kinematically-selected jets
			BNmet correctedMET  = beanHelper->GetCorrectedMET(*(_BNmets.begin()), beanHelper->GetUncorrectedJets(cleanSelCorrJets, _BNjets), _sysType);

			_HT.push_back(Tau->pt + Lepton1->pt + Lepton2->pt + correctedMET.pt + beanHelper->GetHT(cleanSelCorrJets));

			_NumCSVLbtagJets	.push_back(beanHelper->GetNumCSVbtags(selCorrJets, 'L'));
			_NumCSVMbtagJets	.push_back(beanHelper->GetNumCSVbtags(selCorrJets, 'M'));
			_NumCSVTbtagJets	.push_back(beanHelper->GetNumCSVbtags(selCorrJets, 'T'));
			_NumNonCSVLbtagJets .push_back(beanHelper->GetNumNonCSVbtags(selCorrJets, 'L'));
			_NumNonCSVMbtagJets .push_back(beanHelper->GetNumNonCSVbtags(selCorrJets, 'M'));
			_NumNonCSVTbtagJets .push_back(beanHelper->GetNumNonCSVbtags(selCorrJets, 'T'));

			_NumCleanCSVLbtagJets	.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'L'));
			_NumCleanCSVMbtagJets	.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'M'));
			_NumCleanCSVTbtagJets	.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'T'));
			_NumCleanNonCSVLbtagJets .push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'L'));
			_NumCleanNonCSVMbtagJets .push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'M'));
			_NumCleanNonCSVTbtagJets .push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'T'));


			// TLL stuff
			_MomentumRank.push_back(_MomentumRank.size());
			_NumCombos++;

			_TauMomentumRank.push_back(theNumberOfTaus-1);

			FillTau(*Tau);
			FillLepton1(Lepton1);
			FillLepton2(Lepton2);
			FillTauLeptonLepton(*Tau, Lepton1, Lepton2, correctedMET);

	} // End of tau loop

}


void TauLeptonLeptonFiller::FillTau(const BNtau& Tau){
				_TauPt										.push_back(Tau.pt);
				_TauEta										.push_back(Tau.eta);
				_TauPhi										.push_back(Tau.phi);
				_TauNProngs									.push_back(Tau.numProngs);
				_TauNSignalGammas							.push_back(Tau.numSignalGammas);
				_TauNSignalNeutrals							.push_back(Tau.numSignalNeutrals);
				_TauDecayMode								.push_back(Tau.decayMode);
				_TauEmFraction								.push_back(Tau.emFraction);
				_TauIsInTheCracks							.push_back(Tau.inTheCracks);
			
                // HPS discriminants
                _TauHPSagainstElectronDeadECAL                     .push_back(Tau.HPSagainstElectronDeadECAL);
                _TauHPSagainstElectronLoose                        .push_back(Tau.HPSagainstElectronLoose);
                _TauHPSagainstElectronLooseMVA2                    .push_back(Tau.HPSagainstElectronLooseMVA2);
                _TauHPSagainstElectronLooseMVA3                    .push_back(Tau.HPSagainstElectronLooseMVA3);
                _TauHPSagainstElectronMVA                          .push_back(Tau.HPSagainstElectronMVA);
                _TauHPSagainstElectronMVA2category                 .push_back(Tau.HPSagainstElectronMVA2category);
                _TauHPSagainstElectronMVA2raw                      .push_back(Tau.HPSagainstElectronMVA2raw);
                _TauHPSagainstElectronMVA3category                 .push_back(Tau.HPSagainstElectronMVA3category);
                _TauHPSagainstElectronMVA3raw                      .push_back(Tau.HPSagainstElectronMVA3raw);
                _TauHPSagainstElectronMedium                       .push_back(Tau.HPSagainstElectronMedium);
                _TauHPSagainstElectronMediumMVA2                   .push_back(Tau.HPSagainstElectronMediumMVA2);
                _TauHPSagainstElectronMediumMVA3                   .push_back(Tau.HPSagainstElectronMediumMVA3);
                _TauHPSagainstElectronTight                        .push_back(Tau.HPSagainstElectronTight);
                _TauHPSagainstElectronTightMVA2                    .push_back(Tau.HPSagainstElectronTightMVA2);
                _TauHPSagainstElectronTightMVA3                    .push_back(Tau.HPSagainstElectronTightMVA3);
                _TauHPSagainstElectronVLooseMVA2                   .push_back(Tau.HPSagainstElectronVLooseMVA2);
                _TauHPSagainstElectronVTightMVA3                   .push_back(Tau.HPSagainstElectronVTightMVA3);
                _TauHPSagainstMuonLoose                            .push_back(Tau.HPSagainstMuonLoose);
                _TauHPSagainstMuonLoose2                           .push_back(Tau.HPSagainstMuonLoose2);
                _TauHPSagainstMuonMedium                           .push_back(Tau.HPSagainstMuonMedium);
                _TauHPSagainstMuonMedium2                          .push_back(Tau.HPSagainstMuonMedium2);
                _TauHPSagainstMuonTight                            .push_back(Tau.HPSagainstMuonTight);
                _TauHPSagainstMuonTight2                           .push_back(Tau.HPSagainstMuonTight2);
                _TauHPSbyCombinedIsolationDeltaBetaCorrRaw         .push_back(Tau.HPSbyCombinedIsolationDeltaBetaCorrRaw);
                _TauHPSbyCombinedIsolationDeltaBetaCorrRaw3Hits    .push_back(Tau.HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits);
                _TauHPSbyIsolationMVA2raw                          .push_back(Tau.HPSbyIsolationMVA2raw);
                _TauHPSbyLooseCombinedIsolationDeltaBetaCorr       .push_back(Tau.HPSbyLooseCombinedIsolationDeltaBetaCorr);
                _TauHPSbyLooseCombinedIsolationDeltaBetaCorr3Hits  .push_back(Tau.HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits);
                _TauHPSbyLooseIsolationMVA                         .push_back(Tau.HPSbyLooseIsolationMVA);
                _TauHPSbyLooseIsolationMVA2                        .push_back(Tau.HPSbyLooseIsolationMVA2);
                _TauHPSbyMediumCombinedIsolationDeltaBetaCorr      .push_back(Tau.HPSbyMediumCombinedIsolationDeltaBetaCorr);
                _TauHPSbyMediumCombinedIsolationDeltaBetaCorr3Hits .push_back(Tau.HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits);
                _TauHPSbyMediumIsolationMVA                        .push_back(Tau.HPSbyMediumIsolationMVA);
                _TauHPSbyMediumIsolationMVA2                       .push_back(Tau.HPSbyMediumIsolationMVA2);
                _TauHPSbyTightCombinedIsolationDeltaBetaCorr       .push_back(Tau.HPSbyTightCombinedIsolationDeltaBetaCorr);
                _TauHPSbyTightCombinedIsolationDeltaBetaCorr3Hits  .push_back(Tau.HPSbyTightCombinedIsolationDeltaBetaCorr3Hits);
                _TauHPSbyTightIsolationMVA                         .push_back(Tau.HPSbyTightIsolationMVA);
                _TauHPSbyTightIsolationMVA2                        .push_back(Tau.HPSbyTightIsolationMVA2);
                _TauHPSbyVLooseCombinedIsolationDeltaBetaCorr      .push_back(Tau.HPSbyVLooseCombinedIsolationDeltaBetaCorr);
                _TauHPSdecayModeFinding                            .push_back(Tau.HPSdecayModeFinding);
                _TauHPSbyIsolationMVAraw                           .push_back(Tau.HPSbyIsolationMVAraw);

				// Leading track variables
				_TauLTPt			.push_back(Tau.leadingTrackPt);
				_TauCharge			.push_back(Tau.charge);
				_TauLTvalid			.push_back(Tau.leadingTrackValid);
				_TauLTIpVtdxy		.push_back(Tau.leadingTrackIpVtdxy);
				_TauLTIpVtdz		.push_back(Tau.leadingTrackIpVtdz);
				_TauLTIpVtdxyError	.push_back(Tau.leadingTrackIpVtdxyError);
				_TauLTIpVtdzError	.push_back(Tau.leadingTrackIpVtdzError);
				_TauLTvx			.push_back(Tau.leadingTrackVx);
				_TauLTvy			.push_back(Tau.leadingTrackVy);
				_TauLTvz			.push_back(Tau.leadingTrackVz);
				_TauLTValidHits		.push_back(Tau.leadingTrackValidHits);
				_TauLTNormChiSqrd	.push_back(Tau.leadingTrackNormChiSqrd);

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
				_TauGenMatchDaughter0Id			.push_back(tauGenMatch.daughter0Id);
				_TauGenMatchDaughter1Id			.push_back(tauGenMatch.daughter1Id);
				_TauGenMatchId					.push_back(tauGenMatch.id);
				_TauGenMatchMother0Id			.push_back(tauGenMatch.mother0Id);
				_TauGenMatchMother1Id			.push_back(tauGenMatch.mother1Id);
				_TauGenMatchGrandmother00Id		.push_back(tauGenMatch.grandMother00Id);
				_TauGenMatchGrandmother01Id		.push_back(tauGenMatch.grandMother01Id);
				_TauGenMatchGrandmother10Id		.push_back(tauGenMatch.grandMother10Id);
				_TauGenMatchGrandmother11Id		.push_back(tauGenMatch.grandMother11Id);
				_TauGenMatchDaughter0Status		.push_back(tauGenMatch.daughter0Status);
				_TauGenMatchDaughter1Status		.push_back(tauGenMatch.daughter1Status);
				_TauGenMatchStatus				.push_back(tauGenMatch.status);
				_TauGenMatchMother0Status		.push_back(tauGenMatch.mother0Status);
				_TauGenMatchMother1Status		.push_back(tauGenMatch.mother1Status);
				_TauGenMatchGrandmother00Status	.push_back(tauGenMatch.grandMother00Status);
				_TauGenMatchGrandmother01Status	.push_back(tauGenMatch.grandMother01Status);
				_TauGenMatchGrandmother10Status	.push_back(tauGenMatch.grandMother10Status);
				_TauGenMatchGrandmother11Status	.push_back(tauGenMatch.grandMother11Status);

}


void TauLeptonLeptonFiller::FillLepton1(const BNlepton* iLepton){

		_Lepton1IsMuon.push_back(iLepton->isMuon);
		_Lepton1IsElectron.push_back(iLepton->isElectron);
		_Lepton1Pt.push_back(iLepton->pt);
		_Lepton1Eta.push_back(iLepton->eta);
		_Lepton1Phi.push_back(iLepton->phi);

		if(iLepton->isMuon){
			BNmuon* Muon = (BNmuon*)iLepton;
			_Lepton1RelIso.push_back(beanHelper->GetMuonRelIso(*Muon));
			_Lepton1IsLoose.push_back(beanHelper->IsLooseMuon(*Muon));
			_Lepton1IsTight.push_back(beanHelper->IsTightMuon(*Muon));
			_Lepton1EventWeight.push_back(beanHelper->GetMuonSF(*Muon));
		}else if(iLepton->isElectron){
			BNelectron* Electron = (BNelectron*)iLepton;
			_Lepton1RelIso.push_back(beanHelper->GetElectronRelIso(*Electron));
			_Lepton1IsLoose.push_back(beanHelper->IsLooseElectron(*Electron));
			_Lepton1IsTight.push_back(beanHelper->IsTightElectron(*Electron));
			_Lepton1EventWeight.push_back(beanHelper->GetElectronSF(*Electron));
		}

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
		BNmcparticle leptonGenMatch = beanHelper->GetMatchedMCparticle(selectedMCparticles, *iLepton, 0.25);
		_Lepton1GenMatchDaughter0Id			.push_back(leptonGenMatch.daughter0Id);
		_Lepton1GenMatchDaughter1Id			.push_back(leptonGenMatch.daughter1Id);
		_Lepton1GenMatchId					.push_back(leptonGenMatch.id);
		_Lepton1GenMatchMother0Id			.push_back(leptonGenMatch.mother0Id);
		_Lepton1GenMatchMother1Id			.push_back(leptonGenMatch.mother1Id);
		_Lepton1GenMatchGrandmother00Id		.push_back(leptonGenMatch.grandMother00Id);
		_Lepton1GenMatchGrandmother01Id		.push_back(leptonGenMatch.grandMother01Id);
		_Lepton1GenMatchGrandmother10Id		.push_back(leptonGenMatch.grandMother10Id);
		_Lepton1GenMatchGrandmother11Id		.push_back(leptonGenMatch.grandMother11Id);
		_Lepton1GenMatchDaughter0Status		.push_back(leptonGenMatch.daughter0Status);
		_Lepton1GenMatchDaughter1Status		.push_back(leptonGenMatch.daughter1Status);
		_Lepton1GenMatchStatus				.push_back(leptonGenMatch.status);
		_Lepton1GenMatchMother0Status		.push_back(leptonGenMatch.mother0Status);
		_Lepton1GenMatchMother1Status		.push_back(leptonGenMatch.mother1Status);
		_Lepton1GenMatchGrandmother00Status	.push_back(leptonGenMatch.grandMother00Status);
		_Lepton1GenMatchGrandmother01Status	.push_back(leptonGenMatch.grandMother01Status);
		_Lepton1GenMatchGrandmother10Status	.push_back(leptonGenMatch.grandMother10Status);
		_Lepton1GenMatchGrandmother11Status	.push_back(leptonGenMatch.grandMother11Status);
}

void TauLeptonLeptonFiller::FillLepton2(const BNlepton* iLepton){
		_Lepton2IsMuon.push_back(iLepton->isMuon);
		_Lepton2IsElectron.push_back(iLepton->isElectron);
		_Lepton2Pt.push_back(iLepton->pt);
		_Lepton2Eta.push_back(iLepton->eta);
		_Lepton2Phi.push_back(iLepton->phi);

		if(iLepton->isMuon){
			BNmuon* Muon = (BNmuon*)iLepton;
			_Lepton2RelIso.push_back(beanHelper->GetMuonRelIso(*Muon));
			_Lepton2IsLoose.push_back(beanHelper->IsLooseMuon(*Muon));
			_Lepton2IsTight.push_back(beanHelper->IsTightMuon(*Muon));
			_Lepton2EventWeight.push_back(beanHelper->GetMuonSF(*Muon));
		}else if(iLepton->isElectron){
			BNelectron* Electron = (BNelectron*)iLepton;
			_Lepton2RelIso.push_back(beanHelper->GetElectronRelIso(*Electron));
			_Lepton2IsLoose.push_back(beanHelper->IsLooseElectron(*Electron));
			_Lepton2IsTight.push_back(beanHelper->IsTightElectron(*Electron));
			_Lepton2EventWeight.push_back(beanHelper->GetElectronSF(*Electron));
		}

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
		BNmcparticle leptonGenMatch = beanHelper->GetMatchedMCparticle(selectedMCparticles, *iLepton, 0.25);
		_Lepton2GenMatchDaughter0Id			.push_back(leptonGenMatch.daughter0Id);
		_Lepton2GenMatchDaughter1Id			.push_back(leptonGenMatch.daughter1Id);
		_Lepton2GenMatchId					.push_back(leptonGenMatch.id);
		_Lepton2GenMatchMother0Id			.push_back(leptonGenMatch.mother0Id);
		_Lepton2GenMatchMother1Id			.push_back(leptonGenMatch.mother1Id);
		_Lepton2GenMatchGrandmother00Id		.push_back(leptonGenMatch.grandMother00Id);
		_Lepton2GenMatchGrandmother01Id		.push_back(leptonGenMatch.grandMother01Id);
		_Lepton2GenMatchGrandmother10Id		.push_back(leptonGenMatch.grandMother10Id);
		_Lepton2GenMatchGrandmother11Id		.push_back(leptonGenMatch.grandMother11Id);
		_Lepton2GenMatchDaughter0Status		.push_back(leptonGenMatch.daughter0Status);
		_Lepton2GenMatchDaughter1Status		.push_back(leptonGenMatch.daughter1Status);
		_Lepton2GenMatchStatus				.push_back(leptonGenMatch.status);
		_Lepton2GenMatchMother0Status		.push_back(leptonGenMatch.mother0Status);
		_Lepton2GenMatchMother1Status		.push_back(leptonGenMatch.mother1Status);
		_Lepton2GenMatchGrandmother00Status	.push_back(leptonGenMatch.grandMother00Status);
		_Lepton2GenMatchGrandmother01Status	.push_back(leptonGenMatch.grandMother01Status);
		_Lepton2GenMatchGrandmother10Status	.push_back(leptonGenMatch.grandMother10Status);
		_Lepton2GenMatchGrandmother11Status	.push_back(leptonGenMatch.grandMother11Status);
}

void TauLeptonLeptonFiller::FillTauLeptonLepton(const BNtau& iTau, const BNlepton* iLepton1, const BNlepton* iLepton2, const BNmet& iMET){

	_TauLepton1VisibleMass.push_back(GetComboMassBN(iTau, *iLepton1));
	_TauLepton2VisibleMass.push_back(GetComboMassBN(iTau, *iLepton2));
	_TauLepton1METMass.push_back(GetComboMassBN(iTau, *iLepton1, iMET));
	_TauLepton2METMass.push_back(GetComboMassBN(iTau, *iLepton2, iMET));
	_Lepton1Lepton2VisibleMass.push_back(GetComboMassBN(*iLepton1, *iLepton2));
	_TauLepton1CosDeltaPhi.push_back(cos(TMath::Abs(normalizedPhi(iTau.phi - iLepton1->phi))));
	_TauLepton2CosDeltaPhi.push_back(cos(TMath::Abs(normalizedPhi(iTau.phi - iLepton2->phi))));
	_Lepton1Lepton2CosDeltaPhi.push_back(cos(TMath::Abs(normalizedPhi(iLepton1->phi - iLepton2->phi))));
	_TauLepton1DeltaR.push_back(deltaR(iTau.eta, iTau.phi, iLepton1->eta, iLepton2->phi));
	_TauLepton2DeltaR.push_back(deltaR(iTau.eta, iTau.phi, iLepton2->eta, iLepton2->phi));
	_Lepton1Lepton2DeltaR.push_back(deltaR(iLepton1->eta, iLepton1->phi, iLepton2->eta, iLepton2->phi));

}
