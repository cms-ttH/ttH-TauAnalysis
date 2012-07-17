// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/MuonFiller.h"
//#include "fillerAuxFunctions.cc"

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
	_Tree->Branch("M_RelIso",&_MuonRelIso); 
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
	_MuonRelIso  		.clear();
	_isTightMuon    .clear();
	_isLooseMuon 	.clear();

}

// === Fill ntuple === //
void MuonFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	
    //std::cout << "entering MuonFiller::FillNtuple" << std::endl;
    
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

        float iso = -1;
        iso = getLeptonIso <pat::Muon> (*Muon, 0,  // is not PF muon
                                               0,  // no charged hadron PU subtraction
                                               0); // no delta(beta) correction
        _MuonRelIso.push_back( iso );
        
        _isLooseMuon.push_back(getMuonID(*Muon,vertexPosition,
                    1, // return loose ID
                    1)); // require track info for ID
        _isTightMuon.push_back(getMuonID(*Muon,vertexPosition,0,1));
	}

    //std::cout << "leave MuonFiller::FillNtuple" << std::endl;
}


//define this as a plug-in
DEFINE_FWK_MODULE(MuonFiller);
