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
    
    _Tree->Branch("TTE_Tau1HPSagainstElectronDeadECAL", &_Tau1HPSagainstElectronDeadECAL);
    _Tree->Branch("TTE_Tau1HPSagainstElectronLoose", &_Tau1HPSagainstElectronLoose);
    _Tree->Branch("TTE_Tau1HPSagainstElectronLooseMVA2", &_Tau1HPSagainstElectronLooseMVA2);
    _Tree->Branch("TTE_Tau1HPSagainstElectronLooseMVA3", &_Tau1HPSagainstElectronLooseMVA3);
    _Tree->Branch("TTE_Tau1HPSagainstElectronMVA", &_Tau1HPSagainstElectronMVA);
    _Tree->Branch("TTE_Tau1HPSagainstElectronMVA2category", &_Tau1HPSagainstElectronMVA2category);
    _Tree->Branch("TTE_Tau1HPSagainstElectronMVA2raw", &_Tau1HPSagainstElectronMVA2raw);
    _Tree->Branch("TTE_Tau1HPSagainstElectronMVA3category", &_Tau1HPSagainstElectronMVA3category);
    _Tree->Branch("TTE_Tau1HPSagainstElectronMVA3raw", &_Tau1HPSagainstElectronMVA3raw);
    _Tree->Branch("TTE_Tau1HPSagainstElectronMedium", &_Tau1HPSagainstElectronMedium);
    _Tree->Branch("TTE_Tau1HPSagainstElectronMediumMVA2", &_Tau1HPSagainstElectronMediumMVA2);
    _Tree->Branch("TTE_Tau1HPSagainstElectronMediumMVA3", &_Tau1HPSagainstElectronMediumMVA3);
    _Tree->Branch("TTE_Tau1HPSagainstElectronTight", &_Tau1HPSagainstElectronTight);
    _Tree->Branch("TTE_Tau1HPSagainstElectronTightMVA2", &_Tau1HPSagainstElectronTightMVA2);
    _Tree->Branch("TTE_Tau1HPSagainstElectronTightMVA3", &_Tau1HPSagainstElectronTightMVA3);
    _Tree->Branch("TTE_Tau1HPSagainstElectronVLooseMVA2", &_Tau1HPSagainstElectronVLooseMVA2);
    _Tree->Branch("TTE_Tau1HPSagainstElectronVTightMVA3", &_Tau1HPSagainstElectronVTightMVA3);
    _Tree->Branch("TTE_Tau1HPSagainstMuonLoose", &_Tau1HPSagainstMuonLoose);
    _Tree->Branch("TTE_Tau1HPSagainstMuonLoose2", &_Tau1HPSagainstMuonLoose2);
    _Tree->Branch("TTE_Tau1HPSagainstMuonMedium", &_Tau1HPSagainstMuonMedium);
    _Tree->Branch("TTE_Tau1HPSagainstMuonMedium2", &_Tau1HPSagainstMuonMedium2);
    _Tree->Branch("TTE_Tau1HPSagainstMuonTight", &_Tau1HPSagainstMuonTight);
    _Tree->Branch("TTE_Tau1HPSagainstMuonTight2", &_Tau1HPSagainstMuonTight2);
    _Tree->Branch("TTE_Tau1HPSbyCombinedIsolationDeltaBetaCorrRaw", &_Tau1HPSbyCombinedIsolationDeltaBetaCorrRaw);
    _Tree->Branch("TTE_Tau1HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits", &_Tau1HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits);
    _Tree->Branch("TTE_Tau1HPSbyIsolationMVA2raw", &_Tau1HPSbyIsolationMVA2raw);
    _Tree->Branch("TTE_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr);
    _Tree->Branch("TTE_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits", &_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits);
    _Tree->Branch("TTE_Tau1HPSbyLooseIsolationMVA", &_Tau1HPSbyLooseIsolationMVA);
    _Tree->Branch("TTE_Tau1HPSbyLooseIsolationMVA2", &_Tau1HPSbyLooseIsolationMVA2);
    _Tree->Branch("TTE_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr);
    _Tree->Branch("TTE_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits", &_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits);
    _Tree->Branch("TTE_Tau1HPSbyMediumIsolationMVA", &_Tau1HPSbyMediumIsolationMVA);
    _Tree->Branch("TTE_Tau1HPSbyMediumIsolationMVA2", &_Tau1HPSbyMediumIsolationMVA2);
    _Tree->Branch("TTE_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr);
    _Tree->Branch("TTE_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr3Hits", &_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr3Hits);
    _Tree->Branch("TTE_Tau1HPSbyTightIsolationMVA", &_Tau1HPSbyTightIsolationMVA);
    _Tree->Branch("TTE_Tau1HPSbyTightIsolationMVA2", &_Tau1HPSbyTightIsolationMVA2);
    _Tree->Branch("TTE_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr);
    _Tree->Branch("TTE_Tau1HPSdecayModeFinding", &_Tau1HPSdecayModeFinding);
    _Tree->Branch("TTE_Tau1HPSbyIsolationMVAraw", &_Tau1HPSbyIsolationMVAraw);

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
    
    _Tree->Branch("TTE_Tau2HPSagainstElectronDeadECAL", &_Tau2HPSagainstElectronDeadECAL);
    _Tree->Branch("TTE_Tau2HPSagainstElectronLoose", &_Tau2HPSagainstElectronLoose);
    _Tree->Branch("TTE_Tau2HPSagainstElectronLooseMVA2", &_Tau2HPSagainstElectronLooseMVA2);
    _Tree->Branch("TTE_Tau2HPSagainstElectronLooseMVA3", &_Tau2HPSagainstElectronLooseMVA3);
    _Tree->Branch("TTE_Tau2HPSagainstElectronMVA", &_Tau2HPSagainstElectronMVA);
    _Tree->Branch("TTE_Tau2HPSagainstElectronMVA2category", &_Tau2HPSagainstElectronMVA2category);
    _Tree->Branch("TTE_Tau2HPSagainstElectronMVA2raw", &_Tau2HPSagainstElectronMVA2raw);
    _Tree->Branch("TTE_Tau2HPSagainstElectronMVA3category", &_Tau2HPSagainstElectronMVA3category);
    _Tree->Branch("TTE_Tau2HPSagainstElectronMVA3raw", &_Tau2HPSagainstElectronMVA3raw);
    _Tree->Branch("TTE_Tau2HPSagainstElectronMedium", &_Tau2HPSagainstElectronMedium);
    _Tree->Branch("TTE_Tau2HPSagainstElectronMediumMVA2", &_Tau2HPSagainstElectronMediumMVA2);
    _Tree->Branch("TTE_Tau2HPSagainstElectronMediumMVA3", &_Tau2HPSagainstElectronMediumMVA3);
    _Tree->Branch("TTE_Tau2HPSagainstElectronTight", &_Tau2HPSagainstElectronTight);
    _Tree->Branch("TTE_Tau2HPSagainstElectronTightMVA2", &_Tau2HPSagainstElectronTightMVA2);
    _Tree->Branch("TTE_Tau2HPSagainstElectronTightMVA3", &_Tau2HPSagainstElectronTightMVA3);
    _Tree->Branch("TTE_Tau2HPSagainstElectronVLooseMVA2", &_Tau2HPSagainstElectronVLooseMVA2);
    _Tree->Branch("TTE_Tau2HPSagainstElectronVTightMVA3", &_Tau2HPSagainstElectronVTightMVA3);
    _Tree->Branch("TTE_Tau2HPSagainstMuonLoose", &_Tau2HPSagainstMuonLoose);
    _Tree->Branch("TTE_Tau2HPSagainstMuonLoose2", &_Tau2HPSagainstMuonLoose2);
    _Tree->Branch("TTE_Tau2HPSagainstMuonMedium", &_Tau2HPSagainstMuonMedium);
    _Tree->Branch("TTE_Tau2HPSagainstMuonMedium2", &_Tau2HPSagainstMuonMedium2);
    _Tree->Branch("TTE_Tau2HPSagainstMuonTight", &_Tau2HPSagainstMuonTight);
    _Tree->Branch("TTE_Tau2HPSagainstMuonTight2", &_Tau2HPSagainstMuonTight2);
    _Tree->Branch("TTE_Tau2HPSbyCombinedIsolationDeltaBetaCorrRaw", &_Tau2HPSbyCombinedIsolationDeltaBetaCorrRaw);
    _Tree->Branch("TTE_Tau2HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits", &_Tau2HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits);
    _Tree->Branch("TTE_Tau2HPSbyIsolationMVA2raw", &_Tau2HPSbyIsolationMVA2raw);
    _Tree->Branch("TTE_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr);
    _Tree->Branch("TTE_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits", &_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits);
    _Tree->Branch("TTE_Tau2HPSbyLooseIsolationMVA", &_Tau2HPSbyLooseIsolationMVA);
    _Tree->Branch("TTE_Tau2HPSbyLooseIsolationMVA2", &_Tau2HPSbyLooseIsolationMVA2);
    _Tree->Branch("TTE_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr);
    _Tree->Branch("TTE_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits", &_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits);
    _Tree->Branch("TTE_Tau2HPSbyMediumIsolationMVA", &_Tau2HPSbyMediumIsolationMVA);
    _Tree->Branch("TTE_Tau2HPSbyMediumIsolationMVA2", &_Tau2HPSbyMediumIsolationMVA2);
    _Tree->Branch("TTE_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr);
    _Tree->Branch("TTE_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr3Hits", &_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr3Hits);
    _Tree->Branch("TTE_Tau2HPSbyTightIsolationMVA", &_Tau2HPSbyTightIsolationMVA);
    _Tree->Branch("TTE_Tau2HPSbyTightIsolationMVA2", &_Tau2HPSbyTightIsolationMVA2);
    _Tree->Branch("TTE_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr);
    _Tree->Branch("TTE_Tau2HPSdecayModeFinding", &_Tau2HPSdecayModeFinding);
    _Tree->Branch("TTE_Tau2HPSbyIsolationMVAraw", &_Tau2HPSbyIsolationMVAraw);

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
	_Tree->Branch("TTE_NumOtherExLooseMuons",&_NumOtherExLooseMuons);
	_Tree->Branch("TTE_NumOtherTightMuons",&_NumOtherTightMuons);
	_Tree->Branch("TTE_NumOtherLooseElectrons",&_NumOtherLooseElectrons);
	_Tree->Branch("TTE_NumOtherExLooseElectrons",&_NumOtherExLooseElectrons);
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
	_NumOtherExLooseMuons							= 0;
	_NumOtherTightMuons								= 0;
	_NumOtherLooseElectrons							.clear();
	_NumOtherExLooseElectrons						.clear();
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
	GetCollections(iEvent, iSetup);

	// Clear vectors
	ClearVectors();

	// Other leptons
	BNmuonCollection looseMuons				= beanHelper->GetSelectedMuons(_BNmuons, muonID::muonLoose);
	BNmuonCollection tightMuons				= beanHelper->GetSelectedMuons(_BNmuons, muonID::muonTight);
	BNmuonCollection exLooseMuons			= beanHelper->GetDifference(looseMuons, tightMuons);
	_NumOtherLooseMuons		= looseMuons.size();
	_NumOtherExLooseMuons	= exLooseMuons.size();
	_NumOtherTightMuons		= tightMuons.size();

	BNelectronCollection looseElectrons		= beanHelper->GetSelectedElectrons(_BNelectrons, electronID::electronLoose);
	BNelectronCollection tightElectrons		= beanHelper->GetSelectedElectrons(_BNelectrons, electronID::electronTight);
	BNelectronCollection exLooseElectrons	= beanHelper->GetDifference(looseElectrons, tightElectrons);

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

				// Other electrons
				bool isTight = beanHelper->IsTightElectron(*Electron);
				bool isLoose = beanHelper->IsLooseElectron(*Electron);
					  if(  isLoose &&  isTight){ // This Electron will be in: tight, loose
						_NumOtherLooseElectrons		.push_back(looseElectrons.size()-1);
						_NumOtherExLooseElectrons	.push_back(exLooseElectrons.size());
						_NumOtherTightElectrons		.push_back(tightElectrons.size()-1);
				}else if(  isLoose && !isTight){ // This Electron will be in: loose, exLoose
						_NumOtherLooseElectrons		.push_back(looseElectrons.size()-1);
						_NumOtherExLooseElectrons	.push_back(exLooseElectrons.size()-1);
						_NumOtherTightElectrons		.push_back(tightElectrons.size());
				}else if( !isLoose &&  isTight){ // This Electron will be in: tight
						_NumOtherLooseElectrons		.push_back(looseElectrons.size());
						_NumOtherExLooseElectrons	.push_back(exLooseElectrons.size());
						_NumOtherTightElectrons		.push_back(tightElectrons.size()-1);
				}else{ // Redundant
						_NumOtherLooseElectrons		.push_back(looseElectrons.size());
						_NumOtherExLooseElectrons	.push_back(exLooseElectrons.size());
						_NumOtherTightElectrons		.push_back(tightElectrons.size());
				}

				
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

    // HPS discriminants
    _Tau1HPSagainstElectronDeadECAL                     .push_back(Tau.HPSagainstElectronDeadECAL);
    _Tau1HPSagainstElectronLoose                        .push_back(Tau.HPSagainstElectronLoose);
    _Tau1HPSagainstElectronLooseMVA2                    .push_back(Tau.HPSagainstElectronLooseMVA2);
    _Tau1HPSagainstElectronLooseMVA3                    .push_back(Tau.HPSagainstElectronLooseMVA3);
    _Tau1HPSagainstElectronMVA                          .push_back(Tau.HPSagainstElectronMVA);
    _Tau1HPSagainstElectronMVA2category                 .push_back(Tau.HPSagainstElectronMVA2category);
    _Tau1HPSagainstElectronMVA2raw                      .push_back(Tau.HPSagainstElectronMVA2raw);
    _Tau1HPSagainstElectronMVA3category                 .push_back(Tau.HPSagainstElectronMVA3category);
    _Tau1HPSagainstElectronMVA3raw                      .push_back(Tau.HPSagainstElectronMVA3raw);
    _Tau1HPSagainstElectronMedium                       .push_back(Tau.HPSagainstElectronMedium);
    _Tau1HPSagainstElectronMediumMVA2                   .push_back(Tau.HPSagainstElectronMediumMVA2);
    _Tau1HPSagainstElectronMediumMVA3                   .push_back(Tau.HPSagainstElectronMediumMVA3);
    _Tau1HPSagainstElectronTight                        .push_back(Tau.HPSagainstElectronTight);
    _Tau1HPSagainstElectronTightMVA2                    .push_back(Tau.HPSagainstElectronTightMVA2);
    _Tau1HPSagainstElectronTightMVA3                    .push_back(Tau.HPSagainstElectronTightMVA3);
    _Tau1HPSagainstElectronVLooseMVA2                   .push_back(Tau.HPSagainstElectronVLooseMVA2);
    _Tau1HPSagainstElectronVTightMVA3                   .push_back(Tau.HPSagainstElectronVTightMVA3);
    _Tau1HPSagainstMuonLoose                            .push_back(Tau.HPSagainstMuonLoose);
    _Tau1HPSagainstMuonLoose2                           .push_back(Tau.HPSagainstMuonLoose2);
    _Tau1HPSagainstMuonMedium                           .push_back(Tau.HPSagainstMuonMedium);
    _Tau1HPSagainstMuonMedium2                          .push_back(Tau.HPSagainstMuonMedium2);
    _Tau1HPSagainstMuonTight                            .push_back(Tau.HPSagainstMuonTight);
    _Tau1HPSagainstMuonTight2                           .push_back(Tau.HPSagainstMuonTight2);
    _Tau1HPSbyCombinedIsolationDeltaBetaCorrRaw         .push_back(Tau.HPSbyCombinedIsolationDeltaBetaCorrRaw);
    _Tau1HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits    .push_back(Tau.HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits);
    _Tau1HPSbyIsolationMVA2raw                          .push_back(Tau.HPSbyIsolationMVA2raw);
    _Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr       .push_back(Tau.HPSbyLooseCombinedIsolationDeltaBetaCorr);
    _Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits  .push_back(Tau.HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits);
    _Tau1HPSbyLooseIsolationMVA                         .push_back(Tau.HPSbyLooseIsolationMVA);
    _Tau1HPSbyLooseIsolationMVA2                        .push_back(Tau.HPSbyLooseIsolationMVA2);
    _Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr      .push_back(Tau.HPSbyMediumCombinedIsolationDeltaBetaCorr);
    _Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits .push_back(Tau.HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits);
    _Tau1HPSbyMediumIsolationMVA                        .push_back(Tau.HPSbyMediumIsolationMVA);
    _Tau1HPSbyMediumIsolationMVA2                       .push_back(Tau.HPSbyMediumIsolationMVA2);
    _Tau1HPSbyTightCombinedIsolationDeltaBetaCorr       .push_back(Tau.HPSbyTightCombinedIsolationDeltaBetaCorr);
    _Tau1HPSbyTightCombinedIsolationDeltaBetaCorr3Hits  .push_back(Tau.HPSbyTightCombinedIsolationDeltaBetaCorr3Hits);
    _Tau1HPSbyTightIsolationMVA                         .push_back(Tau.HPSbyTightIsolationMVA);
    _Tau1HPSbyTightIsolationMVA2                        .push_back(Tau.HPSbyTightIsolationMVA2);
    _Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr      .push_back(Tau.HPSbyVLooseCombinedIsolationDeltaBetaCorr);
    _Tau1HPSdecayModeFinding                            .push_back(Tau.HPSdecayModeFinding);
    _Tau1HPSbyIsolationMVAraw                           .push_back(Tau.HPSbyIsolationMVAraw);

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
    
    // HPS discriminants
    _Tau2HPSagainstElectronDeadECAL                     .push_back(Tau.HPSagainstElectronDeadECAL);
    _Tau2HPSagainstElectronLoose                        .push_back(Tau.HPSagainstElectronLoose);
    _Tau2HPSagainstElectronLooseMVA2                    .push_back(Tau.HPSagainstElectronLooseMVA2);
    _Tau2HPSagainstElectronLooseMVA3                    .push_back(Tau.HPSagainstElectronLooseMVA3);
    _Tau2HPSagainstElectronMVA                          .push_back(Tau.HPSagainstElectronMVA);
    _Tau2HPSagainstElectronMVA2category                 .push_back(Tau.HPSagainstElectronMVA2category);
    _Tau2HPSagainstElectronMVA2raw                      .push_back(Tau.HPSagainstElectronMVA2raw);
    _Tau2HPSagainstElectronMVA3category                 .push_back(Tau.HPSagainstElectronMVA3category);
    _Tau2HPSagainstElectronMVA3raw                      .push_back(Tau.HPSagainstElectronMVA3raw);
    _Tau2HPSagainstElectronMedium                       .push_back(Tau.HPSagainstElectronMedium);
    _Tau2HPSagainstElectronMediumMVA2                   .push_back(Tau.HPSagainstElectronMediumMVA2);
    _Tau2HPSagainstElectronMediumMVA3                   .push_back(Tau.HPSagainstElectronMediumMVA3);
    _Tau2HPSagainstElectronTight                        .push_back(Tau.HPSagainstElectronTight);
    _Tau2HPSagainstElectronTightMVA2                    .push_back(Tau.HPSagainstElectronTightMVA2);
    _Tau2HPSagainstElectronTightMVA3                    .push_back(Tau.HPSagainstElectronTightMVA3);
    _Tau2HPSagainstElectronVLooseMVA2                   .push_back(Tau.HPSagainstElectronVLooseMVA2);
    _Tau2HPSagainstElectronVTightMVA3                   .push_back(Tau.HPSagainstElectronVTightMVA3);
    _Tau2HPSagainstMuonLoose                            .push_back(Tau.HPSagainstMuonLoose);
    _Tau2HPSagainstMuonLoose2                           .push_back(Tau.HPSagainstMuonLoose2);
    _Tau2HPSagainstMuonMedium                           .push_back(Tau.HPSagainstMuonMedium);
    _Tau2HPSagainstMuonMedium2                          .push_back(Tau.HPSagainstMuonMedium2);
    _Tau2HPSagainstMuonTight                            .push_back(Tau.HPSagainstMuonTight);
    _Tau2HPSagainstMuonTight2                           .push_back(Tau.HPSagainstMuonTight2);
    _Tau2HPSbyCombinedIsolationDeltaBetaCorrRaw         .push_back(Tau.HPSbyCombinedIsolationDeltaBetaCorrRaw);
    _Tau2HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits    .push_back(Tau.HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits);
    _Tau2HPSbyIsolationMVA2raw                          .push_back(Tau.HPSbyIsolationMVA2raw);
    _Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr       .push_back(Tau.HPSbyLooseCombinedIsolationDeltaBetaCorr);
    _Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits  .push_back(Tau.HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits);
    _Tau2HPSbyLooseIsolationMVA                         .push_back(Tau.HPSbyLooseIsolationMVA);
    _Tau2HPSbyLooseIsolationMVA2                        .push_back(Tau.HPSbyLooseIsolationMVA2);
    _Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr      .push_back(Tau.HPSbyMediumCombinedIsolationDeltaBetaCorr);
    _Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits .push_back(Tau.HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits);
    _Tau2HPSbyMediumIsolationMVA                        .push_back(Tau.HPSbyMediumIsolationMVA);
    _Tau2HPSbyMediumIsolationMVA2                       .push_back(Tau.HPSbyMediumIsolationMVA2);
    _Tau2HPSbyTightCombinedIsolationDeltaBetaCorr       .push_back(Tau.HPSbyTightCombinedIsolationDeltaBetaCorr);
    _Tau2HPSbyTightCombinedIsolationDeltaBetaCorr3Hits  .push_back(Tau.HPSbyTightCombinedIsolationDeltaBetaCorr3Hits);
    _Tau2HPSbyTightIsolationMVA                         .push_back(Tau.HPSbyTightIsolationMVA);
    _Tau2HPSbyTightIsolationMVA2                        .push_back(Tau.HPSbyTightIsolationMVA2);
    _Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr      .push_back(Tau.HPSbyVLooseCombinedIsolationDeltaBetaCorr);
    _Tau2HPSdecayModeFinding                            .push_back(Tau.HPSdecayModeFinding);
    _Tau2HPSbyIsolationMVAraw                           .push_back(Tau.HPSbyIsolationMVAraw);


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
