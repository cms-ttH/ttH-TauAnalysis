// Author: Nil Valls <nvallsve@nd.edu>, Jeff Kolb

#include "../interface/MuTauMuonFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
MuTauMuonFiller::MuTauMuonFiller(const ParameterSet& iConfig): NtupleFiller(iConfig){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

MuTauMuonFiller::MuTauMuonFiller(const ParameterSet& iConfig, TTree* iTree) : NtupleFiller(iConfig) {
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
	_Tree->Branch("MTM_TauHPSbyLooseIsolation", &_TauHPSbyLooseIsolation);
	_Tree->Branch("MTM_TauHPSbyLooseIsolationDeltaBetaCorr", &_TauHPSbyLooseIsolationDeltaBetaCorr);
	_Tree->Branch("MTM_TauHPSbyMediumCombinedIsolationDeltaBetaCorr", &_TauHPSbyMediumCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("MTM_TauHPSbyMediumIsolation", &_TauHPSbyMediumIsolation);
	_Tree->Branch("MTM_TauHPSbyMediumIsolationDeltaBetaCorr", &_TauHPSbyMediumIsolationDeltaBetaCorr);
	_Tree->Branch("MTM_TauHPSbyTightCombinedIsolationDeltaBetaCorr", &_TauHPSbyTightCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("MTM_TauHPSbyTightIsolation", &_TauHPSbyTightIsolation);
	_Tree->Branch("MTM_TauHPSbyTightIsolationDeltaBetaCorr", &_TauHPSbyTightIsolationDeltaBetaCorr);
	_Tree->Branch("MTM_TauHPSbyVLooseCombinedIsolationDeltaBetaCorr", &_TauHPSbyVLooseCombinedIsolationDeltaBetaCorr);
	_Tree->Branch("MTM_TauHPSbyVLooseIsolation", &_TauHPSbyVLooseIsolation);
	_Tree->Branch("MTM_TauHPSbyVLooseIsolationDeltaBetaCorr", &_TauHPSbyVLooseIsolationDeltaBetaCorr);
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
	_TauHPSbyLooseIsolation						.clear();
	_TauHPSbyLooseIsolationDeltaBetaCorr			.clear();
	_TauHPSbyMediumCombinedIsolationDeltaBetaCorr	.clear();
	_TauHPSbyMediumIsolation						.clear();
	_TauHPSbyMediumIsolationDeltaBetaCorr			.clear();
	_TauHPSbyTightCombinedIsolationDeltaBetaCorr	.clear();
	_TauHPSbyTightIsolation						.clear();
	_TauHPSbyTightIsolationDeltaBetaCorr			.clear();
	_TauHPSbyVLooseCombinedIsolationDeltaBetaCorr	.clear();
	_TauHPSbyVLooseIsolation						.clear();
	_TauHPSbyVLooseIsolationDeltaBetaCorr			.clear();
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
	
	// Require at least 2 muons and at least one tau
	if(_patTaus->size() < 1 || _patMuons->size() < 2){ return; }

	// Get primary vertex
	const reco::Vertex& primaryVertex = (*(_primaryVertices)->begin());

	// Muon loops: Muon1 is always leads in pT
	unsigned int theNumberOfTaus = 0;
	unsigned int theNumberOfMuons1 = 0;
	unsigned int theNumberOfMuons2 = 0;

	// Start loop 
	_NumMuons = _patMuons->size();
	theNumberOfMuons1 = 0;
	for ( pat::MuonCollection::const_iterator Muon1 = _patMuons->begin(); Muon1 != _patMuons->end(); ++Muon1 ) {
		theNumberOfMuons1++;

		theNumberOfMuons2 = theNumberOfMuons1 + 1;
		for ( pat::MuonCollection::const_iterator Muon2 = (Muon1 + 1); Muon2 != _patMuons->end(); ++Muon2 ) {
			theNumberOfMuons2++;

			if( theNumberOfMuons2 <= theNumberOfMuons1 ){ continue; }// Make sure we don't double-count: only compare pairs in which the muon2 iterator is larger than the muon1 iterator, else skip combo

			// pat::MuonCollection should be sorted by pT in descending order, but let's make sure, and if not, flip them so Muon1 has the largest pT
			if (Muon1->pt() < Muon2->pt()){
				pat::MuonCollection::const_iterator MuonTemp = Muon1;
				Muon1 = Muon2;
				Muon2 = MuonTemp;
			}

			_NumTaus = _patTaus->size();
			theNumberOfTaus = 0;
			for ( pat::TauCollection::const_iterator Tau = _patTaus->begin(); Tau != _patTaus->end(); ++Tau ) {
				theNumberOfTaus++;

				// =========   NO VECTOR FILLING BEFORE THIS POINT   ========= //
					
				_NumCombos++;
			
                // do tau + muon1 combos
                _MomentumRank.push_back(_MomentumRank.size());
				FillMuTauMuon(*Muon1, *Muon2, *Tau, primaryVertex);

				_Muon1MomentumRank.push_back(theNumberOfMuons1-1);
				FillMuon1(*Muon1, primaryVertex);

				_Muon2MomentumRank.push_back(theNumberOfMuons2-1);
				FillMuon2(*Muon2, primaryVertex);

				_TauMomentumRank.push_back(theNumberOfTaus-1);
				FillTau(*Tau, primaryVertex);

                // do tau + muon2 combos
                _MomentumRank.push_back(_MomentumRank.size());
				FillMuTauMuon(*Muon2, *Muon1, *Tau, primaryVertex);

				_Muon1MomentumRank.push_back(theNumberOfMuons1-1);
				FillMuon1(*Muon2, primaryVertex);

				_Muon2MomentumRank.push_back(theNumberOfMuons2-1);
				FillMuon2(*Muon1, primaryVertex);

				_TauMomentumRank.push_back(theNumberOfTaus-1);
				FillTau(*Tau, primaryVertex);

			} // end of tau loop
		} // end of muon2 loop
	} // end of muon1 loop

	//*/


}

void MuTauMuonFiller::FillTau(const pat::Tau& Tau, const reco::Vertex& primaryVertex){
				_TauPt											.push_back(Tau.pt());
				_TauEta										.push_back(Tau.eta());
				_TauPhi										.push_back(Tau.phi());
				_TauNProngs									.push_back(Tau.signalPFChargedHadrCands().size());
				_TauNSignalGammas								.push_back(Tau.signalPFGammaCands().size());
				_TauNSignalNeutrals							.push_back(Tau.signalPFNeutrHadrCands().size());
				//_TauNSignalPiZeros							.push_back(Tau.signalPiZeroCandidates().size());
				_TauNSignalPiZeros								.push_back(-1);
				_TauDecayMode									.push_back(Tau.decayMode());
				_TauEmFraction									.push_back(Tau.emFraction());
				_TauIsInTheCracks								.push_back(IsInTheCracks(Tau.eta()));
				_TauHPSagainstElectronLoose					.push_back(Tau.tauID("againstElectronLoose") );
				_TauHPSagainstElectronMVA						.push_back(Tau.tauID("againstElectronMVA") );
				_TauHPSagainstElectronMedium					.push_back(Tau.tauID("againstElectronMedium") );
				_TauHPSagainstElectronTight					.push_back(Tau.tauID("againstElectronTight") );
				_TauHPSagainstMuonLoose						.push_back(Tau.tauID("againstMuonLoose") );
				_TauHPSagainstMuonMedium						.push_back(Tau.tauID("againstMuonMedium") );
				_TauHPSagainstMuonTight						.push_back(Tau.tauID("againstMuonTight") );
				_TauHPSbyLooseCombinedIsolationDeltaBetaCorr	.push_back(Tau.tauID("byLooseCombinedIsolationDeltaBetaCorr") );
				_TauHPSbyLooseIsolation						.push_back(Tau.tauID("byLooseIsolation") );
				_TauHPSbyLooseIsolationDeltaBetaCorr			.push_back(Tau.tauID("byLooseIsolationDeltaBetaCorr") );
				_TauHPSbyMediumCombinedIsolationDeltaBetaCorr	.push_back(Tau.tauID("byMediumCombinedIsolationDeltaBetaCorr") );
				_TauHPSbyMediumIsolation						.push_back(Tau.tauID("byMediumIsolation") );
				_TauHPSbyMediumIsolationDeltaBetaCorr			.push_back(Tau.tauID("byMediumIsolationDeltaBetaCorr") );
				_TauHPSbyTightCombinedIsolationDeltaBetaCorr	.push_back(Tau.tauID("byTightCombinedIsolationDeltaBetaCorr") );
				_TauHPSbyTightIsolation						.push_back(Tau.tauID("byTightIsolation") );
				_TauHPSbyTightIsolationDeltaBetaCorr			.push_back(Tau.tauID("byTightIsolationDeltaBetaCorr") );
				_TauHPSbyVLooseCombinedIsolationDeltaBetaCorr	.push_back(Tau.tauID("byVLooseCombinedIsolationDeltaBetaCorr") );
				_TauHPSbyVLooseIsolation						.push_back(Tau.tauID("byVLooseIsolation") );
				_TauHPSbyVLooseIsolationDeltaBetaCorr			.push_back(Tau.tauID("byVLooseIsolationDeltaBetaCorr") );
				_TauHPSdecayModeFinding						.push_back(Tau.tauID("decayModeFinding") );
			
				// Leading track variables
				if(Tau.leadPFChargedHadrCand().isNonnull()){
					_TauLTPt       .push_back(Tau.leadPFChargedHadrCand()->pt());
					_TauCharge     .push_back(Tau.leadPFChargedHadrCand()->charge());

					if(false&& Tau.leadPFChargedHadrCand()->trackRef().isNonnull()){
						_TauLTvalid        .push_back(true);
						_TauLTIpVtdxy      .push_back(Tau.leadPFChargedHadrCand()->trackRef()->dxy(primaryVertex.position()));
						_TauLTIpVtdz       .push_back(Tau.leadPFChargedHadrCand()->trackRef()->dz(primaryVertex.position()));
						_TauLTIpVtdxyError .push_back(Tau.leadPFChargedHadrCand()->trackRef()->dxyError());
						_TauLTIpVtdzError  .push_back(Tau.leadPFChargedHadrCand()->trackRef()->dzError());
						_TauLTvx           .push_back(Tau.leadPFChargedHadrCand()->trackRef()->vx());
						_TauLTvy           .push_back(Tau.leadPFChargedHadrCand()->trackRef()->vy());
						_TauLTvz           .push_back(Tau.leadPFChargedHadrCand()->trackRef()->vz());
						_TauLTValidHits    .push_back(Tau.leadPFChargedHadrCand()->trackRef()->numberOfValidHits());
						_TauLTNormChiSqrd  .push_back(Tau.leadPFChargedHadrCand()->trackRef()->normalizedChi2());
					}else{
						_TauLTvalid        .push_back(false);
						_TauLTIpVtdxy      .push_back(-1);
						_TauLTIpVtdz       .push_back(-1);
						_TauLTIpVtdxyError .push_back(-1);
						_TauLTIpVtdzError  .push_back(-1);
						_TauLTvx           .push_back(-1);
						_TauLTvy           .push_back(-1);
						_TauLTvz           .push_back(-1);
						_TauLTValidHits    .push_back(-1);
						_TauLTNormChiSqrd  .push_back(-1);
					}
				}else{
					_TauLTvalid        .push_back(false);
					_TauLTPt           .push_back(-1);
					_TauCharge         .push_back(0);
					_TauLTIpVtdxy      .push_back(-1);
					_TauLTIpVtdz       .push_back(-1);
					_TauLTIpVtdxyError .push_back(-1);
					_TauLTIpVtdzError  .push_back(-1);
					_TauLTvx           .push_back(-1);
					_TauLTvy           .push_back(-1);
					_TauLTvz           .push_back(-1);
					_TauLTValidHits    .push_back(-1);
					_TauLTNormChiSqrd  .push_back(-1);
				}
}


void MuTauMuonFiller::FillMuon1(const pat::Muon& Muon, const reco::Vertex& primaryVertex){
    
    // get beamspot
    math::XYZPoint beamSpotPosition;
    beamSpotPosition.SetCoordinates(0,0,0);

    //edm::Handle<reco::BeamSpot> bsHandle;
    //iEvent.getByLabel("offlineBeamSpot",bsHandle);
    //if( (bsHandle.isValid()) ){
    //    beamSpotPosition = bsHandle->position();
    //}
    
    // get vertex
    math::XYZPoint vertexPosition;
    vertexPosition.SetCoordinates(0,0,0);

    vertexPosition = primaryVertex.position();

    _Muon1Pt.push_back(Muon.pt());
    _Muon1Eta.push_back(Muon.eta());
    _Muon1Phi.push_back(Muon.phi());
    
    float pfIso = -1;
    pfIso = getLeptonIso <pat::Muon> (Muon, 
            0, // not PF muons 
            0, //no charged hadron PU subtraction
            0); // no delta(B) corr.
    _Muon1PfIso.push_back( pfIso );
   
    _Muon1IsLooseMuon.push_back(getMuonID(Muon,vertexPosition,
                1, // return loose ID
                1)); // require muon track info
    _Muon1IsTightMuon.push_back(getMuonID(Muon,vertexPosition,0,1));
	
}

void MuTauMuonFiller::FillMuon2(const pat::Muon& Muon, const reco::Vertex& primaryVertex){
    
    // get beamspot
    math::XYZPoint beamSpotPosition;
    beamSpotPosition.SetCoordinates(0,0,0);

    //edm::Handle<reco::BeamSpot> bsHandle;
    //iEvent.getByLabel("offlineBeamSpot",bsHandle);
    //if( (bsHandle.isValid()) ){
    //    beamSpotPosition = bsHandle->position();
    //}
    
    // get vertex
    math::XYZPoint vertexPosition;
    vertexPosition.SetCoordinates(0,0,0);

    vertexPosition = primaryVertex.position();

    _Muon2Pt.push_back(Muon.pt());
    _Muon2Eta.push_back(Muon.eta());
    _Muon2Phi.push_back(Muon.phi());
    
    float pfIso = -1;
    pfIso = getLeptonIso <pat::Muon> (Muon, 
            0, // not PF muons 
            0, //no charged hadron PU subtraction
            0); // no delta(B) corr.
    _Muon2PfIso.push_back( pfIso );
   
    _Muon2IsLooseMuon.push_back(getMuonID(Muon,vertexPosition,
                1, // return loose ID
                1)); // require muon track info
    _Muon2IsTightMuon.push_back(getMuonID(Muon,vertexPosition,0,1));
	
}

void MuTauMuonFiller::FillMuTauMuon(const pat::Muon& Muon1, const pat::Muon& Muon2, const pat::Tau& Tau, const reco::Vertex& primaryVertex){
	_MuTauVisibleMass	.push_back(GetComboMass(Muon1, Tau));
	_MuTauMETMass		.push_back(GetComboMass(Muon1, Tau, (*_patMETs->begin())));
	_MuTauCosDeltaPhi	.push_back(cos(TMath::Abs(normalizedPhi(Muon1.phi() - Tau.phi()))));
	_MuTauDeltaR		.push_back(reco::deltaR(Muon1.eta(), Muon1.phi(), Tau.eta(), Tau.phi()));
	_TauMuon1DeltaR		.push_back(reco::deltaR(Tau.eta(), Tau.phi(), Muon1.eta(), Muon1.phi()));
	_TauMuon2DeltaR		.push_back(reco::deltaR(Tau.eta(), Tau.phi(), Muon2.eta(), Muon2.phi()));
	_HT					.push_back(Tau.pt() + Muon1.pt() + Muon2.pt() + (_patMETs->begin()->pt()));
	_NumCSVLbtags		.push_back(GetNumCSVbtags(Muon1, Muon2, Tau, "L"));
	_NumCSVMbtags		.push_back(GetNumCSVbtags(Muon1, Muon2, Tau, "M"));
	_NumCSVTbtags		.push_back(GetNumCSVbtags(Muon1, Muon2, Tau, "T"));
	_NumCSVLextraJets	.push_back(GetNumCSVextraJets(Muon1, Muon2, Tau, "L"));
	_NumCSVMextraJets	.push_back(GetNumCSVextraJets(Muon1, Muon2, Tau, "M"));
	_NumCSVTextraJets	.push_back(GetNumCSVextraJets(Muon1, Muon2, Tau, "T"));
}

unsigned int MuTauMuonFiller::GetNumCSVbtags(const pat::Muon& Muon1, const pat::Muon& Muon2, const pat::Tau& Tau, const string iWP){ 
	unsigned int result = 0;

	// Define working points
	float wp = 0;
	if(iWP.compare("L")==0){		wp = _CSVlooseWP;	}	
	else if(iWP.compare("M")==0){	wp = _CSVmediumWP;	}	
	else if(iWP.compare("T")==0){	wp = _CSVtightWP;	}	
	else{ cerr << "ERROR in " << __FILE__ << "\tb-Tagging working point '" << iWP << "' not understood. Choose 'L' or 'M' or 'T'." << endl; exit(1); }

	// Loop over jets
	for(pat::JetCollection::const_iterator Jet = _patJets->begin(); Jet != _patJets->end(); ++Jet){

		// Antimatching to taus and muon
		if(deltaR(Jet->eta(), Jet->phi(), Muon1.eta(), Muon1.phi()) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta(), Jet->phi(), Muon2.eta(), Muon2.phi()) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta(), Jet->phi(), Tau.eta(), Tau.phi()) < _JetAntiMatchingDeltaR){ continue; }

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

unsigned int MuTauMuonFiller::GetNumCSVextraJets(const pat::Muon& Muon1, const pat::Muon& Muon2, const pat::Tau& Tau, const string iWP){ 
	unsigned int result = 0;

	// Define working points
	float wp = 0;
	if(iWP.compare("L")==0){		wp = _CSVlooseWP;	}	
	else if(iWP.compare("M")==0){	wp = _CSVmediumWP;	}	
	else if(iWP.compare("T")==0){	wp = _CSVtightWP;	}	
	else{ cerr << "ERROR in " << __FILE__ << "\tb-Tagging working point '" << iWP << "' not understood. Choose 'L' or 'M' or 'T'." << endl; exit(1); }

	// Loop over jets
	for(pat::JetCollection::const_iterator Jet = _patJets->begin(); Jet != _patJets->end(); ++Jet){

		// Antimatching to taus and muon
		if(deltaR(Jet->eta(), Jet->phi(), Muon1.eta(), Muon1.phi()) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta(), Jet->phi(), Muon2.eta(), Muon2.phi()) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta(), Jet->phi(), Tau.eta(), Tau.phi()) < _JetAntiMatchingDeltaR){ continue; }

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
DEFINE_FWK_MODULE(MuTauMuonFiller);
