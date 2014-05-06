
#include "../interface/VertexFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
VertexFiller::VertexFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

VertexFiller::VertexFiller(const ParameterSet& iConfig, TTree* iTree, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper) {
	_FillerName	= __FILE__;
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
VertexFiller::~VertexFiller(){}

// ------------ method called to for each event  ------------
void VertexFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void VertexFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("V_NumVertices",&_numVertices);
	_Tree->Branch("V_NumInteractionsBXm1",&_numInteractionsBXm1);
	_Tree->Branch("V_NumInteractionsBX0",&_numInteractionsBX0);
	_Tree->Branch("V_NumInteractionsBXp1",&_numInteractionsBXp1);
	_Tree->Branch("V_Xcoord",&_xCoord);
	_Tree->Branch("V_XcoordErr",&_xCoordErr);
	_Tree->Branch("V_Ycoord",&_yCoord);
	_Tree->Branch("V_YcoordErr",&_yCoordErr);
	_Tree->Branch("V_Zcoord",&_zCoord);
	_Tree->Branch("V_ZcoordErr",&_zCoordErr);
	_Tree->Branch("V_Rho",&_rho);
	_Tree->Branch("V_NumDOF",&_ndof);
	_Tree->Branch("V_NormChiSquared",&_normChiSq);
}

// === Clear vectors that will be used to fill ntuple === //
void VertexFiller::ClearVectors(){

    _numInteractionsBXm1    = 0;
    _numInteractionsBX0     = 0;
    _numInteractionsBXp1    = 0;
    _numVertices            = 0;
	
    _xCoord      .clear();
    _xCoordErr   .clear();
    _yCoord      .clear();
    _yCoordErr   .clear();
    _zCoord      .clear();
    _zCoordErr   .clear();
    _rho         .clear();
    _ndof        .clear();
    _normChiSq      .clear();


}

// === Fill ntuple === //
bool
VertexFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	
    GetCollections(iEvent, iSetup);
	ClearVectors();

    _numInteractionsBXm1    = _BNevents.begin()->nm1_true;
    _numInteractionsBX0     = _BNevents.begin()->n0_true;
    _numInteractionsBXp1    = _BNevents.begin()->np1_true;
    _numVertices            = _BNvertices.size();

	
	for ( BNprimaryvertexCollection::const_iterator VertexIt = _BNvertices.begin(); VertexIt != _BNvertices.end(); ++VertexIt ) {

		_xCoord.push_back(VertexIt->x);
		_xCoordErr.push_back(VertexIt->xError);
		_yCoord.push_back(VertexIt->y);
		_yCoordErr.push_back(VertexIt->yError);
		_zCoord.push_back(VertexIt->z);
        _zCoordErr.push_back(VertexIt->zError);
        _normChiSq.push_back(VertexIt->normalizedChi2);
        _rho.push_back(VertexIt->rho);
        _ndof.push_back(VertexIt->ndof);
	}
    return true;
}
