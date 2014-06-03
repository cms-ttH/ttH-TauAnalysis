// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/NtupleFiller.h"

#include <TMath.h>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
NtupleFiller::NtupleFiller(){ cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); }

NtupleFiller::NtupleFiller(const ParameterSet& iConfig, BEANhelper* iBEANhelper) :
    params_(iConfig)
{
	_FillerName						= "NtupleFiller";
	_Tree							= NULL;

	_DebugLevel						= ( iConfig.exists("DebugLevel") ) ? iConfig.getParameter<unsigned int>("DebugLevel") : 0;

	_GenParticleSource				= iConfig.getUntrackedParameter<InputTag>("GenParticleSource");
	_GenJetSource					= iConfig.getUntrackedParameter<InputTag>("GenJetSource");
	_RecoTauSource					= iConfig.getParameter<InputTag>("RecoTauSource");
	_RecoMuonSource					= iConfig.getParameter<InputTag>("RecoMuonSource");
	_RecoElectronSource				= iConfig.getParameter<InputTag>("RecoElectronSource");
	_RecoJetSource					= iConfig.getParameter<InputTag>("RecoJetSource");
	_RecoVertexSource				= iConfig.getParameter<InputTag>("RecoVertexSource");
	_RecoPFMetSource				= iConfig.getParameter<InputTag>("RecoPFMetSource");

	_RecoTauMinPt					= iConfig.getParameter<double>("RecoTauMinPt");
	_RecoTauMaxAbsEta				= iConfig.getParameter<double>("RecoTauMaxAbsEta");
	_RecoTauRequireDMF				= iConfig.getParameter<bool>("RecoTauRequireDMF");

	_RecoJetMinPt					= iConfig.getParameter<double>("RecoJetMinPt");
	_RecoJetMinAbsEta				= iConfig.getParameter<double>("RecoJetMinAbsEta");
	_RecoJetMaxAbsEta				= iConfig.getParameter<double>("RecoJetMaxAbsEta");
	_JetAntiMatchingDeltaR			= iConfig.getParameter<double>("JetAntiMatchingDeltaR");
	//_CSVlooseWP						= iConfig.getParameter<double>("CSVlooseWP");
	//_CSVmediumWP					= iConfig.getParameter<double>("CSVmediumWP");
	//_CSVtightWP						= iConfig.getParameter<double>("CSVtightWP");

    _HLTriggerSource				= iConfig.getParameter<InputTag>("HLTriggerSource");

    // set up systematic shift options
    std::string sysTypeString       = iConfig.getUntrackedParameter<std::string>("SysType");
    _sysType = sysType::NA;
    if( sysTypeString.compare("NA") == 0 ) _sysType = sysType::NA;
    if( sysTypeString.compare("JERup") == 0 ) _sysType = sysType::JERup;
    if( sysTypeString.compare("JERdown") == 0 ) _sysType = sysType::JERdown;
    if( sysTypeString.compare("JESup") == 0 ) _sysType = sysType::JESup;
    if( sysTypeString.compare("JESdown") == 0 ) _sysType = sysType::JESdown;
    if( sysTypeString.compare("TESup") == 0 ) _sysType = sysType::TESup;
    if( sysTypeString.compare("TESdown") == 0 ) _sysType = sysType::TESdown;

	// Setup BEANhelper
	helper = iBEANhelper;

}

// === Destructor === //
NtupleFiller::~NtupleFiller(){}

// === Get name of the filler === //
string NtupleFiller::GetName(){ return _FillerName; }

// ------------ method called to for each event  ------------
void NtupleFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void NtupleFiller::SetupBranches(){}

// === Get relevant collections === //
void NtupleFiller::GetCollections(const Event& iEvent, const EventSetup& iSetup){
    //std::cout << "<NtupleFiller::GetCollections>: enter function" << std::endl;
    Handle<BNeventCollection>				hBNevents;
    iEvent.getByLabel("BNproducer",			hBNevents);
    _BNevents			= *(hBNevents.product());

    if (!params_.is_data()) {
        Handle<BNmcparticleCollection> hBNmcparticles;
        iEvent.getByLabel(_GenParticleSource, hBNmcparticles);
        _BNmcparticles = *(hBNmcparticles.product());

        Handle<BNgenjetCollection> hBNgenjets;
        iEvent.getByLabel(_GenJetSource,  hBNgenjets);
        _BNgenjets = *(hBNgenjets.product());
    }

    Handle<BNelectronCollection>			hBNelectrons;
    iEvent.getByLabel(_RecoElectronSource,	hBNelectrons);
    _BNelectrons		= *(hBNelectrons.product());

    Handle<BNmuonCollection>				hBNmuons;
    iEvent.getByLabel(_RecoMuonSource, 		hBNmuons);
    _BNmuons			= *(hBNmuons.product());

    Handle<BNtauCollection>					hBNtaus;
    iEvent.getByLabel(_RecoTauSource, 		hBNtaus);
    _BNtaus				= *(hBNtaus.product());

    Handle<BNjetCollection>					hBNjets;
    iEvent.getByLabel(_RecoJetSource, 		hBNjets);
    _BNjets				= *(hBNjets.product());

    Handle<BNmetCollection>					hBNmets;
    iEvent.getByLabel(_RecoPFMetSource,		hBNmets);
    _BNmets				= *(hBNmets.product());

    Handle<BNprimaryvertexCollection>		hBNvertices;
    iEvent.getByLabel(_RecoVertexSource,	hBNvertices);
    _BNvertices	        = *(hBNvertices.product());

    Handle<BNtriggerCollection>				hBNtrigger;
    iEvent.getByLabel(_HLTriggerSource,		hBNtrigger);
    _BNtrigger			= *(hBNtrigger.product());
}

// === Clear vectors that will be used to fill ntuple === //
void NtupleFiller::ClearVectors(){}

// === Fill ntuple === //
bool NtupleFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
    GetCollections(iEvent, iSetup);
    ClearVectors();
    return true;
}

// === Crack veto === //
bool NtupleFiller::IsInTheCracks(float etaValue){
    return (fabs(etaValue) < 0.018 || 
            (fabs(etaValue)>0.423 && fabs(etaValue)<0.461) ||
            (fabs(etaValue)>0.770 && fabs(etaValue)<0.806) ||
            (fabs(etaValue)>1.127 && fabs(etaValue)<1.163) ||
            (fabs(etaValue)>1.460 && fabs(etaValue)<1.558));
}
