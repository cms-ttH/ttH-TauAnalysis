// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/MuonFiller.h"
#include "fillerAuxFunctions.cc"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
MuonFiller::MuonFiller(const ParameterSet& iConfig): NtupleFiller(iConfig){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

MuonFiller::MuonFiller(const ParameterSet& iConfig, TTree* iTree) : NtupleFiller(iConfig) {
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
MuonFiller::~MuonFiller(){}

// ------------ method called to for each event  ------------
void MuonFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void MuonFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("M_NumMuons",&_NumMuons);
	_Tree->Branch("M_MomentumRank",&_MomentumRank);
	_Tree->Branch("M_Pt",&_MuonPt);
	_Tree->Branch("M_Eta",&_MuonEta);
	_Tree->Branch("M_Phi",&_MuonPhi);
	_Tree->Branch("M_pfIso",&_pfIso); // 0.4 cone size
	_Tree->Branch("M_isTightMuon",&_isTightMuon);
	_Tree->Branch("M_isLooseMuon",&_isLooseMuon);
}

// === Clear vectors that will be used to fill ntuple === //
void MuonFiller::ClearVectors(){

	_NumMuons		=	0;	
	_MomentumRank	.clear();
	_MuonPt	   		.clear();
	_MuonEta   		.clear();
	_MuonPhi   		.clear();
	_pfIso  		.clear();
	_isTightMuon    .clear();
	_isLooseMuon 	.clear();

}

// === Fill ntuple === //
void MuonFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();

    // get beamspot
    math::XYZPoint beamSpotPosition;
    beamSpotPosition.SetCoordinates(0,0,0);

    edm::Handle<reco::BeamSpot> bsHandle;
    iEvent.getByLabel("offlineBeamSpot",bsHandle);

    if( (bsHandle.isValid()) ){
        beamSpotPosition = bsHandle->position();
    }
    
    // get vertex
    math::XYZPoint vertexPosition;
    vertexPosition.SetCoordinates(0,0,0);

    edm::Handle<reco::VertexCollection> vtxHandle;
    iEvent.getByLabel("offlinePrimaryVerticesBS",vtxHandle);
    
    int numPVs = 0;
    if( (vtxHandle.isValid()) ){
        numPVs = vtxHandle->size();
        
        reco::VertexCollection vtxs = *vtxHandle;
        if (numPVs > 0) {
            vertexPosition = vtxs[0].position();
        }
        //bool firstPV = true;
        //for( reco::VertexCollection::const_iterator vtx = vtxs.begin(); vtx!=vtxs.end(); ++vtx ){
    }

	_NumMuons = _patMuons->size();
    for ( pat::MuonCollection::const_iterator Muon = _patMuons->begin(); Muon != _patMuons->end(); ++Muon ) {
        _MomentumRank.push_back(_MomentumRank.size());
        _MuonPt.push_back(Muon->pt());
        _MuonEta.push_back(Muon->eta());
        _MuonPhi.push_back(Muon->phi());

        float pfIso = -1;
        pfIso = getLeptonIso <pat::Muon> (*Muon, 0, 0, 0); // is reco::Muon, no charged hadron PU subtraction, and no delta(B) corr.
        _pfIso.push_back( pfIso );

        int isLooseMuon = -1;
        int isTightMuon = -1;
        isLooseMuon = Muon->isGlobalMuon();
        isTightMuon = isLooseMuon;
        if( !(Muon->isTrackerMuon()) ) isTightMuon = 0;
        if( !(Muon->isGood("GlobalMuonPromptTight")) ) isTightMuon = 0;
        if( !(Muon->numberOfMatches() > 1) ) isTightMuon = 0;
        if( !(Muon->numberOfValidHits() > 10) ) isTightMuon = 0;
        if( !(Muon->dB(pat::Muon::PV2D) < 0.02) ) isTightMuon = 0;
        if(Muon->innerTrack().isAvailable() ) { 
            if( !(Muon->innerTrack()->hitPattern().pixelLayersWithMeasurement() > 0) ) isTightMuon = 0;
            if( !(Muon->innerTrack()->dz(vertexPosition) < 1) ) isTightMuon = 0;
        } else {  // for now, keep muons without embedded track (skim v1)
            //_MuonIsLooseMuon.push_back(-1);
            //_MuonIsTightMuon.push_back(-1);
            //return;
        }
        _isLooseMuon.push_back(isLooseMuon);
        _isTightMuon.push_back(isTightMuon);
	}

}


//define this as a plug-in
DEFINE_FWK_MODULE(MuonFiller);
