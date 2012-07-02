// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/DitauFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
DitauFiller::DitauFiller(const ParameterSet& iConfig): NtupleFiller(iConfig){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

DitauFiller::DitauFiller(const ParameterSet& iConfig, TTree* iTree) : NtupleFiller(iConfig) {
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
DitauFiller::~DitauFiller(){}

// ------------ method called to for each event  ------------
void DitauFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void DitauFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("TT_NumTaus",&_NumTaus);
	_Tree->Branch("TT_NumCombos",&_NumCombos);
	_Tree->Branch("TT_MomentumRank",&_MomentumRank);

	// === Tau1 === //
	_Tree->Branch("TT_Tau1MomentumRank", &_Tau1MomentumRank);
	_Tree->Branch("TT_Tau1Pt", &_Tau1Pt);
	_Tree->Branch("TT_Tau1Eta", &_Tau1Eta);
	_Tree->Branch("TT_Tau1Phi", &_Tau1Phi);
	_Tree->Branch("TT_Tau1NProngs", &_Tau1NProngs);
	_Tree->Branch("TT_Tau1NSignalGammas", &_Tau1NSignalGammas);
	_Tree->Branch("TT_Tau1NSignalNeutrals", &_Tau1NSignalNeutrals);
	_Tree->Branch("TT_Tau1NSignalPiZeros", &_Tau1NSignalPiZeros);
	_Tree->Branch("TT_Tau1DecayMode", &_Tau1DecayMode);
	_Tree->Branch("TT_Tau1EmFraction", &_Tau1EmFraction);
	_Tree->Branch("TT_Tau1IsInTheCracks", &_Tau1IsInTheCracks);
	_Tree->Branch("TT_Tau1HPSagainstElectronLoose", &_Tau1HPSagainstElectronLoose);
	_Tree->Branch("TT_Tau1HPSagainstElectronMVA", &_Tau1HPSagainstElectronMVA);
	_Tree->Branch("TT_Tau1HPSagainstElectronMedium", &_Tau1HPSagainstElectronMedium);
	_Tree->Branch("TT_Tau1HPSagainstElectronTight", &_Tau1HPSagainstElectronTight);
	_Tree->Branch("TT_Tau1HPSagainstMuonLoose", &_Tau1HPSagainstMuonLoose);
	_Tree->Branch("TT_Tau1HPSagainstMuonMedium", &_Tau1HPSagainstMuonMedium);
	_Tree->Branch("TT_Tau1HPSagainstMuonTight", &_Tau1HPSagainstMuonTight);
	_Tree->Branch("TT_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TT_Tau1HPSbyLooseIsolation", &_Tau1HPSbyLooseIsolation);
	_Tree->Branch("TT_Tau1HPSbyLooseIsolationDeltaBetaCorr", &_Tau1HPSbyLooseIsolationDeltaBetaCorr);
	_Tree->Branch("TT_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TT_Tau1HPSbyMediumIsolation", &_Tau1HPSbyMediumIsolation);
	_Tree->Branch("TT_Tau1HPSbyMediumIsolationDeltaBetaCorr", &_Tau1HPSbyMediumIsolationDeltaBetaCorr);
	_Tree->Branch("TT_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TT_Tau1HPSbyTightIsolation", &_Tau1HPSbyTightIsolation);
	_Tree->Branch("TT_Tau1HPSbyTightIsolationDeltaBetaCorr", &_Tau1HPSbyTightIsolationDeltaBetaCorr);
	_Tree->Branch("TT_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr", &_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TT_Tau1HPSbyVLooseIsolation", &_Tau1HPSbyVLooseIsolation);
	_Tree->Branch("TT_Tau1HPSbyVLooseIsolationDeltaBetaCorr", &_Tau1HPSbyVLooseIsolationDeltaBetaCorr);
	_Tree->Branch("TT_Tau1HPSdecayModeFinding", &_Tau1HPSdecayModeFinding);
	_Tree->Branch("TT_Tau1LTPt", &_Tau1LTPt);
	_Tree->Branch("TT_Tau1Charge", &_Tau1Charge);
	_Tree->Branch("TT_Tau1LTvalid", &_Tau1LTvalid);
	_Tree->Branch("TT_Tau1LTIpVtdxy", &_Tau1LTIpVtdxy);
	_Tree->Branch("TT_Tau1LTIpVtdz", &_Tau1LTIpVtdz);
	_Tree->Branch("TT_Tau1LTIpVtdxyError", &_Tau1LTIpVtdxyError);
	_Tree->Branch("TT_Tau1LTIpVtdzError", &_Tau1LTIpVtdzError);
	_Tree->Branch("TT_Tau1LTvx", &_Tau1LTvx);
	_Tree->Branch("TT_Tau1LTvy", &_Tau1LTvy);
	_Tree->Branch("TT_Tau1LTvz", &_Tau1LTvz);
	_Tree->Branch("TT_Tau1LTValidHits", &_Tau1LTValidHits);
	_Tree->Branch("TT_Tau1LTNormChiSqrd", &_Tau1LTNormChiSqrd);
	_Tree->Branch("TT_Tau1METCosDeltaPhi", &_Tau1METCosDeltaPhi);
	_Tree->Branch("TT_Tau1METMt", &_Tau1METMt);

	// === Tau2 === //
	_Tree->Branch("TT_Tau2MomentumRank", &_Tau2MomentumRank);
	_Tree->Branch("TT_Tau2Pt", &_Tau2Pt);
	_Tree->Branch("TT_Tau2Eta", &_Tau2Eta);
	_Tree->Branch("TT_Tau2Phi", &_Tau2Phi);
	_Tree->Branch("TT_Tau2NProngs", &_Tau2NProngs);
	_Tree->Branch("TT_Tau2NSignalGammas", &_Tau2NSignalGammas);
	_Tree->Branch("TT_Tau2NSignalNeutrals", &_Tau2NSignalNeutrals);
	_Tree->Branch("TT_Tau2NSignalPiZeros", &_Tau2NSignalPiZeros);
	_Tree->Branch("TT_Tau2DecayMode", &_Tau2DecayMode);
	_Tree->Branch("TT_Tau2EmFraction", &_Tau2EmFraction);
	_Tree->Branch("TT_Tau2IsInTheCracks", &_Tau2IsInTheCracks);
	_Tree->Branch("TT_Tau2HPSagainstElectronLoose", &_Tau2HPSagainstElectronLoose);
	_Tree->Branch("TT_Tau2HPSagainstElectronMVA", &_Tau2HPSagainstElectronMVA);
	_Tree->Branch("TT_Tau2HPSagainstElectronMedium", &_Tau2HPSagainstElectronMedium);
	_Tree->Branch("TT_Tau2HPSagainstElectronTight", &_Tau2HPSagainstElectronTight);
	_Tree->Branch("TT_Tau2HPSagainstMuonLoose", &_Tau2HPSagainstMuonLoose);
	_Tree->Branch("TT_Tau2HPSagainstMuonMedium", &_Tau2HPSagainstMuonMedium);
	_Tree->Branch("TT_Tau2HPSagainstMuonTight", &_Tau2HPSagainstMuonTight);
	_Tree->Branch("TT_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TT_Tau2HPSbyLooseIsolation", &_Tau2HPSbyLooseIsolation);
	_Tree->Branch("TT_Tau2HPSbyLooseIsolationDeltaBetaCorr", &_Tau2HPSbyLooseIsolationDeltaBetaCorr);
	_Tree->Branch("TT_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TT_Tau2HPSbyMediumIsolation", &_Tau2HPSbyMediumIsolation);
	_Tree->Branch("TT_Tau2HPSbyMediumIsolationDeltaBetaCorr", &_Tau2HPSbyMediumIsolationDeltaBetaCorr);
	_Tree->Branch("TT_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TT_Tau2HPSbyTightIsolation", &_Tau2HPSbyTightIsolation);
	_Tree->Branch("TT_Tau2HPSbyTightIsolationDeltaBetaCorr", &_Tau2HPSbyTightIsolationDeltaBetaCorr);
	_Tree->Branch("TT_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr", &_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("TT_Tau2HPSbyVLooseIsolation", &_Tau2HPSbyVLooseIsolation);
	_Tree->Branch("TT_Tau2HPSbyVLooseIsolationDeltaBetaCorr", &_Tau2HPSbyVLooseIsolationDeltaBetaCorr);
	_Tree->Branch("TT_Tau2HPSdecayModeFinding", &_Tau2HPSdecayModeFinding);
	_Tree->Branch("TT_Tau2LTPt", &_Tau2LTPt);
	_Tree->Branch("TT_Tau2Charge", &_Tau2Charge);
	_Tree->Branch("TT_Tau2LTvalid", &_Tau2LTvalid);
	_Tree->Branch("TT_Tau2LTIpVtdxy", &_Tau2LTIpVtdxy);
	_Tree->Branch("TT_Tau2LTIpVtdz", &_Tau2LTIpVtdz);
	_Tree->Branch("TT_Tau2LTIpVtdxyError", &_Tau2LTIpVtdxyError);
	_Tree->Branch("TT_Tau2LTIpVtdzError", &_Tau2LTIpVtdzError);
	_Tree->Branch("TT_Tau2LTvx", &_Tau2LTvx);
	_Tree->Branch("TT_Tau2LTvy", &_Tau2LTvy);
	_Tree->Branch("TT_Tau2LTvz", &_Tau2LTvz);
	_Tree->Branch("TT_Tau2LTValidHits", &_Tau2LTValidHits);
	_Tree->Branch("TT_Tau2LTNormChiSqrd", &_Tau2LTNormChiSqrd);
	_Tree->Branch("TT_Tau2METCosDeltaPhi", &_Tau2METCosDeltaPhi);
	_Tree->Branch("TT_Tau2METMt", &_Tau2METMt);

	// === Combo === //
	_Tree->Branch("TT_DitauVisibleMass", &_DitauVisibleMass);
	_Tree->Branch("TT_DitauMETMass", &_DitauMETMass);
	_Tree->Branch("TT_DitauCosDeltaPhi", &_DitauCosDeltaPhi);
	_Tree->Branch("TT_DitauDeltaR", 	&_DitauDeltaR);
	_Tree->Branch("TT_HT", &_HT);
	_Tree->Branch("TT_NumCSVLbtags", &_NumCSVLbtags);
	_Tree->Branch("TT_NumCSVMbtags", &_NumCSVMbtags);
	_Tree->Branch("TT_NumCSVTbtags", &_NumCSVTbtags);
	_Tree->Branch("TT_NumCSVLextraJets", &_NumCSVLextraJets);
	_Tree->Branch("TT_NumCSVMextraJets", &_NumCSVMextraJets);
	_Tree->Branch("TT_NumCSVTextraJets", &_NumCSVTextraJets);
	_Tree->Branch("TT_DitauMETpZeta", &_DitauMETpZeta);
	_Tree->Branch("TT_DitauMETpZetaVis", &_DitauMETpZetaVis);
}

// === Clear vectors that will be used to fill ntuple === //
void DitauFiller::ClearVectors(){

	_NumTaus										= 0;
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
	_Tau1NSignalPiZeros								.clear();
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
	_Tau1HPSbyLooseIsolation						.clear();
	_Tau1HPSbyLooseIsolationDeltaBetaCorr			.clear();
	_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr	.clear();
	_Tau1HPSbyMediumIsolation						.clear();
	_Tau1HPSbyMediumIsolationDeltaBetaCorr			.clear();
	_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr	.clear();
	_Tau1HPSbyTightIsolation						.clear();
	_Tau1HPSbyTightIsolationDeltaBetaCorr			.clear();
	_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr	.clear();
	_Tau1HPSbyVLooseIsolation						.clear();
	_Tau1HPSbyVLooseIsolationDeltaBetaCorr			.clear();
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
	_Tau1METCosDeltaPhi								.clear();
	_Tau1METMt										.clear();

	// === Tau2 === //
	_Tau2MomentumRank								.clear();
	_Tau2Pt											.clear();
	_Tau2Eta										.clear();
	_Tau2Phi										.clear();
	_Tau2NProngs									.clear();
	_Tau2NSignalGammas								.clear();
	_Tau2NSignalNeutrals							.clear();
	_Tau2NSignalPiZeros								.clear();
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
	_Tau2HPSbyLooseIsolation						.clear();
	_Tau2HPSbyLooseIsolationDeltaBetaCorr			.clear();
	_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr	.clear();
	_Tau2HPSbyMediumIsolation						.clear();
	_Tau2HPSbyMediumIsolationDeltaBetaCorr			.clear();
	_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr	.clear();
	_Tau2HPSbyTightIsolation						.clear();
	_Tau2HPSbyTightIsolationDeltaBetaCorr			.clear();
	_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr	.clear();
	_Tau2HPSbyVLooseIsolation						.clear();
	_Tau2HPSbyVLooseIsolationDeltaBetaCorr			.clear();
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
	_Tau2METCosDeltaPhi								.clear();
	_Tau2METMt										.clear();

	// === Combo === //
	_DitauVisibleMass								.clear();
	_DitauMETMass									.clear();
	_DitauCosDeltaPhi								.clear();
	_DitauDeltaR									.clear();
	_HT												.clear();
	_NumCSVLbtags									.clear();
	_NumCSVMbtags									.clear();
	_NumCSVTbtags									.clear();
	_NumCSVLextraJets								.clear();
	_NumCSVMextraJets								.clear();
	_NumCSVTextraJets								.clear();
	_DitauMETpZeta									.clear();
	_DitauMETpZetaVis								.clear();

}

// === Fill ntuple === //
void DitauFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){

	// Get the object collections from the event
	GetCollections(iEvent, iSetup);

	// Clear vectors
	ClearVectors();
	
	// Require at least 2 taus
	if(_patTaus->size() < 2){ return; }

	// Get primary vertex
	const reco::Vertex& primaryVertex = (*(_primaryVertices)->begin());

	// Tau loops: Tau1 is always leads in pT
	unsigned int theNumberOfTaus1 = 0;
	unsigned int theNumberOfTaus2 = 0;

	// Start loop over patTaus so select two (if applicable) that form a good (and heaviest) pair
	_NumTaus = _patTaus->size();
	theNumberOfTaus1 = 0;
	for ( pat::TauCollection::const_iterator Tau1 = _patTaus->begin(); Tau1 != _patTaus->end(); ++Tau1 ) {
		theNumberOfTaus1++;
	//	if (Tau1->pt() < _RecoTauPtMinCut){ continue; }

		theNumberOfTaus2 = theNumberOfTaus1 + 1;
		for ( pat::TauCollection::const_iterator Tau2 = (Tau1 + 1); Tau2 != _patTaus->end(); ++Tau2 ) {
			theNumberOfTaus2++;
	//		if (Tau2->pt() < _RecoTau2PtMinCut){ continue; }

			if( theNumberOfTaus2 <= theNumberOfTaus1 ){ continue; }// Make sure we don't double-count: only compare pairs in which the tau2 iterator is larger than the tau 1 iterator, else skip combo

			// pat::TauCollection should be sorted by pT in descending order, but let's make sure, and if not, flip them so Tau1 has the largest pT
			if (Tau1->pt() < Tau2->pt()){
				pat::TauCollection::const_iterator TauTemp = Tau1;
				Tau1 = Tau2;
				Tau2 = TauTemp;
			}

			if(Tau1->pt() < _RecoTauMinPt){ continue; }
			if(Tau2->pt() < _RecoTauMinPt){ continue; }
			if(fabs(Tau1->eta()) > _RecoTauMaxAbsEta ){ continue; }
			if(fabs(Tau2->eta()) > _RecoTauMaxAbsEta ){ continue; }
			if(_RecoTauRequireDMF && !(Tau1->tauID("decayModeFinding"))){ continue; }
			if(_RecoTauRequireDMF && !(Tau2->tauID("decayModeFinding"))){ continue; }


				// =========   NO VECTOR FILLING BEFORE THIS POINT   ========= //
					
				_NumCombos++;
				_MomentumRank.push_back(_MomentumRank.size());
				FillDitau(*Tau1, *Tau2, primaryVertex);

				_Tau1MomentumRank.push_back(theNumberOfTaus1-1);
				FillTau1(*Tau1, primaryVertex);

				_Tau2MomentumRank.push_back(theNumberOfTaus2-1);
				FillTau2(*Tau2, primaryVertex);

		} // end of tau2 loop
	} // end of tau1 loop

	//*/


}

void DitauFiller::FillTau1(const pat::Tau& Tau1, const reco::Vertex& primaryVertex){
				_Tau1Pt											.push_back(Tau1.pt());
				_Tau1Eta										.push_back(Tau1.eta());
				_Tau1Phi										.push_back(Tau1.phi());
				_Tau1NProngs									.push_back(Tau1.signalPFChargedHadrCands().size());
				_Tau1NSignalGammas								.push_back(Tau1.signalPFGammaCands().size());
				_Tau1NSignalNeutrals							.push_back(Tau1.signalPFNeutrHadrCands().size());
				//_Tau1NSignalPiZeros							.push_back(Tau1.signalPiZeroCandidates().size());
				_Tau1NSignalPiZeros								.push_back(-1);
				_Tau1DecayMode									.push_back(Tau1.decayMode());
				_Tau1EmFraction									.push_back(Tau1.emFraction());
				_Tau1IsInTheCracks								.push_back(IsInTheCracks(Tau1.eta()));
				_Tau1HPSagainstElectronLoose					.push_back(Tau1.tauID("againstElectronLoose") );
				_Tau1HPSagainstElectronMVA						.push_back(Tau1.tauID("againstElectronMVA") );
				_Tau1HPSagainstElectronMedium					.push_back(Tau1.tauID("againstElectronMedium") );
				_Tau1HPSagainstElectronTight					.push_back(Tau1.tauID("againstElectronTight") );
				_Tau1HPSagainstMuonLoose						.push_back(Tau1.tauID("againstMuonLoose") );
				_Tau1HPSagainstMuonMedium						.push_back(Tau1.tauID("againstMuonMedium") );
				_Tau1HPSagainstMuonTight						.push_back(Tau1.tauID("againstMuonTight") );
				_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr	.push_back(Tau1.tauID("byLooseCombinedIsolationDeltaBetaCorr") );
				_Tau1HPSbyLooseIsolation						.push_back(Tau1.tauID("byLooseIsolation") );
				_Tau1HPSbyLooseIsolationDeltaBetaCorr			.push_back(Tau1.tauID("byLooseIsolationDeltaBetaCorr") );
				_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr	.push_back(Tau1.tauID("byMediumCombinedIsolationDeltaBetaCorr") );
				_Tau1HPSbyMediumIsolation						.push_back(Tau1.tauID("byMediumIsolation") );
				_Tau1HPSbyMediumIsolationDeltaBetaCorr			.push_back(Tau1.tauID("byMediumIsolationDeltaBetaCorr") );
				_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr	.push_back(Tau1.tauID("byTightCombinedIsolationDeltaBetaCorr") );
				_Tau1HPSbyTightIsolation						.push_back(Tau1.tauID("byTightIsolation") );
				_Tau1HPSbyTightIsolationDeltaBetaCorr			.push_back(Tau1.tauID("byTightIsolationDeltaBetaCorr") );
				_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr	.push_back(Tau1.tauID("byVLooseCombinedIsolationDeltaBetaCorr") );
				_Tau1HPSbyVLooseIsolation						.push_back(Tau1.tauID("byVLooseIsolation") );
				_Tau1HPSbyVLooseIsolationDeltaBetaCorr			.push_back(Tau1.tauID("byVLooseIsolationDeltaBetaCorr") );
				_Tau1HPSdecayModeFinding						.push_back(Tau1.tauID("decayModeFinding") );
			
				// Leading track variables
				if(Tau1.leadPFChargedHadrCand().isNonnull()){
					_Tau1LTPt       .push_back(Tau1.leadPFChargedHadrCand()->pt());
					_Tau1Charge     .push_back(Tau1.leadPFChargedHadrCand()->charge());

					if(false&& Tau1.leadPFChargedHadrCand()->trackRef().isNonnull()){
						_Tau1LTvalid        .push_back(true);
						_Tau1LTIpVtdxy      .push_back(Tau1.leadPFChargedHadrCand()->trackRef()->dxy(primaryVertex.position()));
						_Tau1LTIpVtdz       .push_back(Tau1.leadPFChargedHadrCand()->trackRef()->dz(primaryVertex.position()));
						_Tau1LTIpVtdxyError .push_back(Tau1.leadPFChargedHadrCand()->trackRef()->dxyError());
						_Tau1LTIpVtdzError  .push_back(Tau1.leadPFChargedHadrCand()->trackRef()->dzError());
						_Tau1LTvx           .push_back(Tau1.leadPFChargedHadrCand()->trackRef()->vx());
						_Tau1LTvy           .push_back(Tau1.leadPFChargedHadrCand()->trackRef()->vy());
						_Tau1LTvz           .push_back(Tau1.leadPFChargedHadrCand()->trackRef()->vz());
						_Tau1LTValidHits    .push_back(Tau1.leadPFChargedHadrCand()->trackRef()->numberOfValidHits());
						_Tau1LTNormChiSqrd  .push_back(Tau1.leadPFChargedHadrCand()->trackRef()->normalizedChi2());
					}else{
						_Tau1LTvalid        .push_back(false);
						_Tau1LTIpVtdxy      .push_back(-1);
						_Tau1LTIpVtdz       .push_back(-1);
						_Tau1LTIpVtdxyError .push_back(-1);
						_Tau1LTIpVtdzError  .push_back(-1);
						_Tau1LTvx           .push_back(-1);
						_Tau1LTvy           .push_back(-1);
						_Tau1LTvz           .push_back(-1);
						_Tau1LTValidHits    .push_back(-1);
						_Tau1LTNormChiSqrd  .push_back(-1);
					}
				}else{
					_Tau1LTvalid        .push_back(false);
					_Tau1LTPt           .push_back(-1);
					_Tau1Charge         .push_back(0);
					_Tau1LTIpVtdxy      .push_back(-1);
					_Tau1LTIpVtdz       .push_back(-1);
					_Tau1LTIpVtdxyError .push_back(-1);
					_Tau1LTIpVtdzError  .push_back(-1);
					_Tau1LTvx           .push_back(-1);
					_Tau1LTvy           .push_back(-1);
					_Tau1LTvz           .push_back(-1);
					_Tau1LTValidHits    .push_back(-1);
					_Tau1LTNormChiSqrd  .push_back(-1);
				}

				_Tau1METCosDeltaPhi	.push_back(cos(TMath::Abs(normalizedPhi(Tau1.phi() - (*_patMETs->begin()).phi()))));
				_Tau1METMt			.push_back(GetTransverseMass(Tau1, (*_patMETs->begin())));
}

void DitauFiller::FillTau2(const pat::Tau& Tau2, const reco::Vertex& primaryVertex){
				_Tau2Pt											.push_back(Tau2.pt());
				_Tau2Eta										.push_back(Tau2.eta());
				_Tau2Phi										.push_back(Tau2.phi());
				_Tau2NProngs									.push_back(Tau2.signalPFChargedHadrCands().size());
				_Tau2NSignalGammas								.push_back(Tau2.signalPFGammaCands().size());
				_Tau2NSignalNeutrals							.push_back(Tau2.signalPFNeutrHadrCands().size());
				//_Tau2NSignalPiZeros							.push_back(Tau2.signalPiZeroCandidates().size());
				_Tau2NSignalPiZeros								.push_back(-1);
				_Tau2DecayMode									.push_back(Tau2.decayMode());
				_Tau2EmFraction									.push_back(Tau2.emFraction());
				_Tau2IsInTheCracks								.push_back(IsInTheCracks(Tau2.eta()));
				_Tau2HPSagainstElectronLoose					.push_back(Tau2.tauID("againstElectronLoose") );
				_Tau2HPSagainstElectronMVA						.push_back(Tau2.tauID("againstElectronMVA") );
				_Tau2HPSagainstElectronMedium					.push_back(Tau2.tauID("againstElectronMedium") );
				_Tau2HPSagainstElectronTight					.push_back(Tau2.tauID("againstElectronTight") );
				_Tau2HPSagainstMuonLoose						.push_back(Tau2.tauID("againstMuonLoose") );
				_Tau2HPSagainstMuonMedium						.push_back(Tau2.tauID("againstMuonMedium") );
				_Tau2HPSagainstMuonTight						.push_back(Tau2.tauID("againstMuonTight") );
				_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr	.push_back(Tau2.tauID("byLooseCombinedIsolationDeltaBetaCorr") );
				_Tau2HPSbyLooseIsolation						.push_back(Tau2.tauID("byLooseIsolation") );
				_Tau2HPSbyLooseIsolationDeltaBetaCorr			.push_back(Tau2.tauID("byLooseIsolationDeltaBetaCorr") );
				_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr	.push_back(Tau2.tauID("byMediumCombinedIsolationDeltaBetaCorr") );
				_Tau2HPSbyMediumIsolation						.push_back(Tau2.tauID("byMediumIsolation") );
				_Tau2HPSbyMediumIsolationDeltaBetaCorr			.push_back(Tau2.tauID("byMediumIsolationDeltaBetaCorr") );
				_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr	.push_back(Tau2.tauID("byTightCombinedIsolationDeltaBetaCorr") );
				_Tau2HPSbyTightIsolation						.push_back(Tau2.tauID("byTightIsolation") );
				_Tau2HPSbyTightIsolationDeltaBetaCorr			.push_back(Tau2.tauID("byTightIsolationDeltaBetaCorr") );
				_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr	.push_back(Tau2.tauID("byVLooseCombinedIsolationDeltaBetaCorr") );
				_Tau2HPSbyVLooseIsolation						.push_back(Tau2.tauID("byVLooseIsolation") );
				_Tau2HPSbyVLooseIsolationDeltaBetaCorr			.push_back(Tau2.tauID("byVLooseIsolationDeltaBetaCorr") );
				_Tau2HPSdecayModeFinding						.push_back(Tau2.tauID("decayModeFinding") );
				// Leading track variables
				if(Tau2.leadPFChargedHadrCand().isNonnull()){
					_Tau2LTPt       .push_back(Tau2.leadPFChargedHadrCand()->pt());
					_Tau2Charge     .push_back(Tau2.leadPFChargedHadrCand()->charge());

					if(false&& Tau2.leadPFChargedHadrCand()->trackRef().isNonnull()){
						_Tau2LTvalid        .push_back(true);
						_Tau2LTIpVtdxy      .push_back(Tau2.leadPFChargedHadrCand()->trackRef()->dxy(primaryVertex.position()));
						_Tau2LTIpVtdz       .push_back(Tau2.leadPFChargedHadrCand()->trackRef()->dz(primaryVertex.position()));
						_Tau2LTIpVtdxyError .push_back(Tau2.leadPFChargedHadrCand()->trackRef()->dxyError());
						_Tau2LTIpVtdzError  .push_back(Tau2.leadPFChargedHadrCand()->trackRef()->dzError());
						_Tau2LTvx           .push_back(Tau2.leadPFChargedHadrCand()->trackRef()->vx());
						_Tau2LTvy           .push_back(Tau2.leadPFChargedHadrCand()->trackRef()->vy());
						_Tau2LTvz           .push_back(Tau2.leadPFChargedHadrCand()->trackRef()->vz());
						_Tau2LTValidHits    .push_back(Tau2.leadPFChargedHadrCand()->trackRef()->numberOfValidHits());
						_Tau2LTNormChiSqrd  .push_back(Tau2.leadPFChargedHadrCand()->trackRef()->normalizedChi2());
					}else{
						_Tau2LTvalid        .push_back(false);
						_Tau2LTIpVtdxy      .push_back(-1);
						_Tau2LTIpVtdz       .push_back(-1);
						_Tau2LTIpVtdxyError .push_back(-1);
						_Tau2LTIpVtdzError  .push_back(-1);
						_Tau2LTvx           .push_back(-1);
						_Tau2LTvy           .push_back(-1);
						_Tau2LTvz           .push_back(-1);
						_Tau2LTValidHits    .push_back(-1);
						_Tau2LTNormChiSqrd  .push_back(-1);
					}
				}else{
					_Tau2LTvalid        .push_back(false);
					_Tau2LTPt           .push_back(-1);
					_Tau2Charge         .push_back(0);
					_Tau2LTIpVtdxy      .push_back(-1);
					_Tau2LTIpVtdz       .push_back(-1);
					_Tau2LTIpVtdxyError .push_back(-1);
					_Tau2LTIpVtdzError  .push_back(-1);
					_Tau2LTvx           .push_back(-1);
					_Tau2LTvy           .push_back(-1);
					_Tau2LTvz           .push_back(-1);
					_Tau2LTValidHits    .push_back(-1);
					_Tau2LTNormChiSqrd  .push_back(-1);
				}

				_Tau2METCosDeltaPhi	.push_back(cos(TMath::Abs(normalizedPhi(Tau2.phi() - (*_patMETs->begin()).phi()))));
				_Tau2METMt			.push_back(GetTransverseMass(Tau2, (*_patMETs->begin())));
}


void DitauFiller::FillDitau(const pat::Tau& Tau1, const pat::Tau& Tau2, const reco::Vertex& primaryVertex){
	_DitauVisibleMass	.push_back(GetComboMass(Tau1, Tau2));
	_DitauMETMass		.push_back(GetComboMass(Tau1, Tau2, (*_patMETs->begin())));
	_DitauCosDeltaPhi	.push_back(cos(TMath::Abs(normalizedPhi(Tau1.phi() - Tau2.phi()))));
	_DitauDeltaR		.push_back(reco::deltaR(Tau1.eta(), Tau1.phi(), Tau2.eta(), Tau2.phi()));

	_DitauMETpZeta		.push_back(GetPZeta(Tau1, Tau2, (*_patMETs->begin())));
	_DitauMETpZetaVis	.push_back(GetPZetaVis(Tau1, Tau2));

	_HT					.push_back(Tau1.pt() + Tau2.pt() + (_patMETs->begin()->pt()));
	_NumCSVLbtags		.push_back(GetNumCSVbtags(Tau1, Tau2, "L"));
	_NumCSVMbtags		.push_back(GetNumCSVbtags(Tau1, Tau2, "M"));
	_NumCSVTbtags		.push_back(GetNumCSVbtags(Tau1, Tau2, "T"));
	_NumCSVLextraJets	.push_back(GetNumCSVextraJets(Tau1, Tau2, "L"));
	_NumCSVMextraJets	.push_back(GetNumCSVextraJets(Tau1, Tau2, "M"));
	_NumCSVTextraJets	.push_back(GetNumCSVextraJets(Tau1, Tau2, "T"));
}

unsigned int DitauFiller::GetNumCSVbtags(const pat::Tau& Tau1, const pat::Tau& Tau2, const string iWP){ 
	unsigned int result = 0;

	// Define working points
	float wp = 0;
	if(iWP.compare("L")==0){		wp = _CSVlooseWP;	}	
	else if(iWP.compare("M")==0){	wp = _CSVmediumWP;	}	
	else if(iWP.compare("T")==0){	wp = _CSVtightWP;	}	
	else{ cerr << "ERROR in " << __FILE__ << "\tb-Tagging working point '" << iWP << "' not understood. Choose 'L' or 'M' or 'T'." << endl; exit(1); }

	// Loop over jets
	for(pat::JetCollection::const_iterator Jet = _patJets->begin(); Jet != _patJets->end(); ++Jet){

		// Antimatching to taus
		if(deltaR(Jet->eta(), Jet->phi(), Tau1.eta(), Tau1.phi()) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta(), Jet->phi(), Tau2.eta(), Tau2.phi()) < _JetAntiMatchingDeltaR){ continue; }

		// Kinematic requirements for jets
		if(Jet->et() < _RecoJetMinEt){ continue; }
		if(fabs(Jet->eta()) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta()) >_RecoJetMaxAbsEta){ continue; }

		// Count jets passing the required b-tagging
		float combSecVtxBTag = Jet->bDiscriminator("combinedSecondaryVertexBJetTags");
		if(combSecVtxBTag >= wp){ result++; } 
	}

	return result;
}

unsigned int DitauFiller::GetNumCSVextraJets(const pat::Tau& Tau1, const pat::Tau& Tau2, const string iWP){ 
	unsigned int result = 0;

	// Define working points
	float wp = 0;
	if(iWP.compare("L")==0){		wp = _CSVlooseWP;	}	
	else if(iWP.compare("M")==0){	wp = _CSVmediumWP;	}	
	else if(iWP.compare("T")==0){	wp = _CSVtightWP;	}	
	else{ cerr << "ERROR in " << __FILE__ << "\tb-Tagging working point '" << iWP << "' not understood. Choose 'L' or 'M' or 'T'." << endl; exit(1); }

	// Loop over jets
	for(pat::JetCollection::const_iterator Jet = _patJets->begin(); Jet != _patJets->end(); ++Jet){

		// Antimatching to taus
		if(deltaR(Jet->eta(), Jet->phi(), Tau1.eta(), Tau1.phi()) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta(), Jet->phi(), Tau2.eta(), Tau2.phi()) < _JetAntiMatchingDeltaR){ continue; }

		// Kinematic requirements for jets
		if(Jet->et() < _RecoJetMinEt){ continue; }
		if(fabs(Jet->eta()) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta()) >_RecoJetMaxAbsEta){ continue; }

		// Count jets failing the required b-tagging
		float combSecVtxBTag = Jet->bDiscriminator("combinedSecondaryVertexBJetTags");
		if(combSecVtxBTag < wp){ result++; } 
	}

	return result;
}

//define this as a plug-in
DEFINE_FWK_MODULE(DitauFiller);
