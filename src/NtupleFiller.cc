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
	_FromBEAN						= iConfig.getParameter<bool>("FromBEAN");

	_GenParticleSource				= iConfig.getUntrackedParameter<InputTag>("GenParticleSource");
	_GenJetSource					= iConfig.getUntrackedParameter<InputTag>("GenJetSource");
	_RecoTauSource					= iConfig.getParameter<InputTag>("RecoTauSource");
	_RecoMuonSource					= iConfig.getParameter<InputTag>("RecoMuonSource");
	_RecoElectronSource				= iConfig.getParameter<InputTag>("RecoElectronSource");
	_RecoJetSource					= iConfig.getParameter<InputTag>("RecoJetSource");
	_RecoVertexSource				= iConfig.getParameter<InputTag>("RecoVertexSource");
	_RecoPATMetSource				= iConfig.getParameter<InputTag>("RecoPATMetSource");
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
	beanHelper = iBEANhelper;

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
	if(_FromBEAN){
		Handle<BNeventCollection>				hBNevents;
		iEvent.getByLabel("BNproducer",			hBNevents);
		_BNevents			= *(hBNevents.product());

        if (!params_.is_data()) {
            Handle<BNmcparticleCollection>			hBNmcparticles;
            iEvent.getByLabel(_GenParticleSource,	hBNmcparticles);
            _BNmcparticles		= *(hBNmcparticles.product());

            Handle<BNgenjetCollection>				hBNgenjets;
            iEvent.getByLabel(_GenJetSource, 	hBNgenjets);
            _BNgenjets			= *(hBNgenjets.product());
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

	}else{
		_BNevents			= patTupleToBEANtranslator.EDMtoBN(&iEvent);
       /* 
		//Handle< reco::VertexCollection >					hVertices;
		//iEvent.getByLabel(_RecoVertexSource,	hVertices);
		//_BNvertices	= patTupleToBEANtranslator.RECOtoBN(hVertices.product());
	
        const reco::Vertex* vertex = patTupleToBEANtranslator.getPrimaryVertex(hVertices.product());

        // get beam spot   BeamSpot collection not in current 7TeV PAT-tuples
        //edm::Handle<reco::BeamSpot> bsHandle;
        //iEvent.getByLabel("offlineBeamSpot",bsHandle);
        //const reco::BeamSpot* beamSpot = bsHandle.product();
        const reco::BeamSpot* beamSpot = 0;

        if( !SampleTypeContains("data") ) {
            //std::cout << " --> Getting genParticles " << std::endl;
            Handle< reco::GenParticleCollection >				hGenParticles;
            if(_GenParticleSource.label()	!= "") { iEvent.getByLabel(_GenParticleSource, hGenParticles); }
            _BNmcparticles		= patTupleToBEANtranslator.RECOtoBN(hGenParticles.product());

            //std::cout << " --> Getting genJets " << std::endl;
            Handle< reco::GenJetCollection >					hGenJets;
            if(_GenJetSource.label()		!= "") { iEvent.getByLabel(_GenJetSource, hGenJets); }
            _BNgenjets			= patTupleToBEANtranslator.RECOtoBN(hGenJets.product());
        }

        //std::cout << " --> Getting patTaus " << std::endl;
		Handle< pat::TauCollection >						hPatTaus;
		iEvent.getByLabel(_RecoTauSource, 		hPatTaus);
		_BNtaus				= patTupleToBEANtranslator.PATtoBN(hPatTaus.product(), vertex);
		
        //std::cout << " --> Getting electrons " << std::endl;
		Handle< pat::ElectronCollection >					hPatElectrons;
		iEvent.getByLabel(_RecoElectronSource,	hPatElectrons);
		_BNelectrons		= patTupleToBEANtranslator.PATtoBN(hPatElectrons.product(), vertex, beamSpot);
		
        //std::cout << " --> Getting muons " << std::endl;
		Handle< pat::MuonCollection >						hPatMuons;
		iEvent.getByLabel(_RecoMuonSource, 		hPatMuons);
		_BNmuons			= patTupleToBEANtranslator.PATtoBN(hPatMuons.product(), vertex, beamSpot);
		
        //std::cout << " --> Getting jets " << std::endl;
		Handle< pat::JetCollection >						hPatJets;
		iEvent.getByLabel(_RecoJetSource,		hPatJets);
		_BNjets				= patTupleToBEANtranslator.PATtoBN(hPatJets.product(), vertex, iEvent, iSetup);
	
        //std::cout << " --> Getting MET " << std::endl;
		Handle< pat::METCollection >						hPatMETs;
		iEvent.getByLabel(_RecoPATMetSource,	hPatMETs);
		_BNmets				= patTupleToBEANtranslator.PATtoBN(hPatMETs.product());
		
		//Handle< edm::TriggerResults >                       hTriggerResults;
		//iEvent.getByLabel(_HLTriggerSource,     hTriggerResults);
		//_BNtrigger				= patTupleToBEANtranslator.EDMtoBN(hTriggerResults.product(), iEvent, iSetup, iEvent.id().run());
		//_BNtrigger				= patTupleToBEANtranslator.EDMtoBN(hTriggerResults.product(), iEvent, iSetup);
	*/}

}

// === Clear vectors that will be used to fill ntuple === //
void NtupleFiller::ClearVectors(){}

// === Fill ntuple === //
void NtupleFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();
}

// === Crack veto === //
bool NtupleFiller::IsInTheCracks(float etaValue){
	return (fabs(etaValue) < 0.018 || 
			(fabs(etaValue)>0.423 && fabs(etaValue)<0.461) ||
			(fabs(etaValue)>0.770 && fabs(etaValue)<0.806) ||
			(fabs(etaValue)>1.127 && fabs(etaValue)<1.163) ||
			(fabs(etaValue)>1.460 && fabs(etaValue)<1.558));
}
