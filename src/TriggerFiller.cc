// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/TriggerFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
TriggerFiller::TriggerFiller(const ParameterSet& iConfig): NtupleFiller(iConfig){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

TriggerFiller::TriggerFiller(const ParameterSet& iConfig, TTree* iTree) : NtupleFiller(iConfig) {
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
TriggerFiller::~TriggerFiller(){}

// ------------ method called to for each event  ------------
void TriggerFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void TriggerFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30", &_HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30);
	_Tree->Branch("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30", &_HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30);
	_Tree->Branch("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30", &_HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30);
	_Tree->Branch("HLT_IsoMu24", &_HLT_IsoMu24);
	_Tree->Branch("HLT_IsoMu24_eta2p1", &_HLT_IsoMu24_eta2p1);
}

// === Clear vectors that will be used to fill ntuple === //
void TriggerFiller::ClearVectors(){

    _HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30 = 0;
    _HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30 = 0;
    _HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30 = 0;
    _HLT_IsoMu24 = 0;
    _HLT_IsoMu24_eta2p1 = 0;

}

// === Fill ntuple === //
void TriggerFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();

    // just give me a friggin dictionary! This is a mess...
    const edm::TriggerNames & triggerNames = iEvent.triggerNames(*_triggerResults);

    /*
    std::vector<string> pathNames;
    pathNames.push_back("HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30");
    pathNames.push_back("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30");
    pathNames.push_back("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30");
    pathNames.push_back("HLT_IsoMu24");
    pathNames.push_back("HLT_IsoMu24_eta2p1");

    std::vector<int> pathResults;
    for( std::vector<string>::const_iterator pathIt = pathNames.begin
    for( TriggerNames::Strings::const_iterator triggerName = triggerNames.triggerNames().begin(); triggerName != triggerNames.triggerNames().end(); ++triggerName ){
        unsigned int index  = triggerNames.triggerIndex(*triggerName);

    unsigned int indexE0 = triggerNames.triggerIndex(nameE0);
    unsigned int indexE1 = triggerNames.triggerIndex(nameE1);
    unsigned int indexE2 = triggerNames.triggerIndex(nameE2);
    unsigned int indexM0 = triggerNames.triggerIndex(nameM0);
    unsigned int indexM1 = triggerNames.triggerIndex(nameM1);

    if( indexE0 < triggerNames.size() )
        _HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30 = _triggerResults->accept(indexE0);
    else {
        _HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30 = -1;
        std::cout << "Couldn't find HLT path " << nameE0 << std::endl;
        std::cout << " options are: " << std::endl;
        for( TriggerNames::Strings::const_iterator triggerName = triggerNames.triggerNames().begin(); triggerName != triggerNames.triggerNames().end(); ++triggerName ){
            unsigned int index  = triggerNames.triggerIndex(*triggerName);
            string name = (*triggerName);
            std::cout << index << " " << name << std::endl;
        }

    }
    if( indexE1 < triggerNames.size() )
         _HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30 = _triggerResults->accept(indexE1);
    else 
         _HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30 = -1;
    if( indexE2 < triggerNames.size() )
         _HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30 = _triggerResults->accept(indexE2);
    else 
         _HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30 = -1;
    if( indexM0 < triggerNames.size() )
         _HLT_IsoMu24 = _triggerResults->accept(indexM0);
    else 
         _HLT_IsoMu24 = -1;
    if( indexM1 < triggerNames.size() )
         _HLT_IsoMu24_eta2p1 = _triggerResults->accept(indexM1);
    else 
         _HLT_IsoMu24_eta2p1 = -1;
    std::cout << _HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30 << std::endl;
     */
}


//define this as a plug-in
DEFINE_FWK_MODULE(TriggerFiller);
