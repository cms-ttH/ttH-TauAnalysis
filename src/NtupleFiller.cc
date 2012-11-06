// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/NtupleFiller.h"

#include <TMath.h>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
NtupleFiller::NtupleFiller(const ParameterSet& iConfig){
	
	_FillerName						= "NtupleFiller";
	_Tree							= NULL;

	_DebugLevel						= iConfig.getParameter<unsigned int>("DebugLevel");
	_AnalysisType					= iConfig.getParameter<string>("AnalysisType");
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
	_CSVlooseWP						= iConfig.getParameter<double>("CSVlooseWP");
	_CSVmediumWP					= iConfig.getParameter<double>("CSVmediumWP");
	_CSVtightWP						= iConfig.getParameter<double>("CSVtightWP");

    _HLTriggerSource				= iConfig.getParameter<InputTag>("HLTriggerSource");

	// Setup BEANhelper
	beanHelper.SetUp(atoi(GetAnalysisTypeParameter(0).c_str()), atoi(GetAnalysisTypeParameter(4).c_str()), false, SampleTypeContains("data"), "SingleMu", true);

}

// === Destructor === //
NtupleFiller::~NtupleFiller(){}

// === Get name of the filler === //
string NtupleFiller::GetName(){ return _FillerName; }

// === Check whether an analysis type is how we want === //
string NtupleFiller::GetAnalysisTypeParameter(unsigned int iParam){

	// Parse analysisType and store parts in the vector
	if(_AnalysisTypeVector.size() == 0){	
		if(_AnalysisType.length()==0){ cerr << "ERROR: 'AnalysisType' is empty." << endl; exit(1); }
		char separator = '_';
		string remainder = _AnalysisType;
		while(remainder.length() > 0){
			unsigned int pos = remainder.find(separator);
			if(pos < remainder.size()){
				_AnalysisTypeVector.push_back(remainder.substr(0, pos));
				remainder = remainder.substr(pos+1);
			}else{
				_AnalysisTypeVector.push_back(remainder);
				remainder = "";
			}	
		}
	}

	// Return the requested piece if it's there 
	if(iParam >= _AnalysisTypeVector.size()){ cerr << "ERROR: Requesting AnalysisType parameter " << iParam << " but vector only has " << _AnalysisTypeVector.size() << " elements." << endl; exit(1); }
	return _AnalysisTypeVector.at(iParam);
}

unsigned int NtupleFiller::GetEra(){ return abs(atoi(GetAnalysisTypeParameter(0).c_str())); }
const char NtupleFiller::GetSubera(){ return *(GetAnalysisTypeParameter(1).c_str()); }
string NtupleFiller::GetSampleType(){ return GetAnalysisTypeParameter(2); }
string NtupleFiller::GetLeptonFlavor(){ return GetAnalysisTypeParameter(3); }
bool NtupleFiller::EraIs(unsigned int iEra){ return (iEra==GetEra()); }
bool NtupleFiller::SuberaIs(const char iSubera){ return (iSubera==GetSubera()); }
bool NtupleFiller::SampleTypeIs(const string iSampleType){ return (iSampleType.compare(GetSampleType())==0); }
bool NtupleFiller::SampleTypeContains(const string iSampleType){ string sampleType = GetSampleType(); return (sampleType.find(iSampleType) < sampleType.length()); }
bool NtupleFiller::LeptonFlavorIs(const string iLeptonFlavor){ return (iLeptonFlavor.compare(GetLeptonFlavor())==0); }

// ------------ method called to for each event  ------------
void NtupleFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void NtupleFiller::SetupBranches(){}

// === Get relevant collections === //
void NtupleFiller::GetCollections(const Event& iEvent, const EventSetup& iSetup){


	if(_FromBEAN){
		Handle<BNeventCollection>				hBNevent;
		iEvent.getByLabel("BNproducer",			hBNevent);
		_BNevent			= *(hBNevent.product());

		Handle<BNmcparticleCollection>			hBNmcparticles;
		iEvent.getByLabel("",	hBNmcparticles);
		_BNmcparticles		= *(hBNmcparticles.product());

		Handle<BNgenjetCollection>				hBNgenjets;
		iEvent.getByLabel(_GenJetSource, 	hBNgenjets);
		_BNgenjets			= *(hBNgenjets.product());

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

		Handle<BNprimaryvertexCollection>		hBNprimaryVertices;
		iEvent.getByLabel(_RecoVertexSource,	hBNprimaryVertices);
		_BNprimaryVertices	= *(hBNprimaryVertices.product());

		Handle<BNtriggerCollection>				hBNtrigger;
		//if(!SampleTypeContains("data")){ iEvent.getByLabel("BNproducer::HLT",	hBNtrigger); }
		iEvent.getByLabel("BNproducer::HLT",	hBNtrigger);
		_BNtrigger			= *(hBNtrigger.product());

	}else{
        
        // get vertex collection first, so we can identify PV
		Handle< reco::VertexCollection >					hPrimaryVertices;
		iEvent.getByLabel(_RecoVertexSource,	hPrimaryVertices);
		_BNprimaryVertices	= patTupleToBEANtranslator.RECOtoBN(hPrimaryVertices.product());
	
        const reco::Vertex* primaryVertex = patTupleToBEANtranslator.getPrimaryVertex(hPrimaryVertices.product());

        // get beam spot
        edm::Handle<reco::BeamSpot> bsHandle;
        iEvent.getByLabel("offlineBeamSpot",bsHandle);
        const reco::BeamSpot* beamSpot = bsHandle.product();

		Handle< reco::GenParticleCollection >				hGenParticles;
		if(_GenParticleSource.label()	!= "") { iEvent.getByLabel(_GenParticleSource, hGenParticles); }
		_BNmcparticles		= patTupleToBEANtranslator.RECOtoBN(hGenParticles.product());

		Handle< reco::GenJetCollection >					hGenJets;
		if(_GenJetSource.label()		!= "") { iEvent.getByLabel(_GenJetSource, hGenJets); }
		_BNgenjets			= patTupleToBEANtranslator.RECOtoBN(hGenJets.product());

		Handle< pat::TauCollection >						hPatTaus;
		iEvent.getByLabel(_RecoTauSource, 		hPatTaus);
		_BNtaus				= patTupleToBEANtranslator.PATtoBN(hPatTaus.product(), primaryVertex);
		
		Handle< pat::ElectronCollection >					hPatElectrons;
		iEvent.getByLabel(_RecoElectronSource,	hPatElectrons);
		_BNelectrons		= patTupleToBEANtranslator.PATtoBN(hPatElectrons.product(), primaryVertex, beamSpot);
		
		Handle< pat::MuonCollection >						hPatMuons;
		iEvent.getByLabel(_RecoMuonSource, 		hPatMuons);
		_BNmuons			= patTupleToBEANtranslator.PATtoBN(hPatMuons.product(), primaryVertex, beamSpot);
		
		Handle< pat::JetCollection >						hPatJets;
		iEvent.getByLabel(_RecoJetSource,		hPatJets);
		_BNjets				= patTupleToBEANtranslator.PATtoBN(hPatJets.product(), primaryVertex, iEvent, iSetup);
	
		Handle< pat::METCollection >						hPatMETs;
		iEvent.getByLabel(_RecoPATMetSource,	hPatMETs);
		_BNmets				= patTupleToBEANtranslator.PATtoBN(hPatMETs.product());
		
//		Handle< std::vector< PileupSummaryInfo > >			hPuInfo;
//		if(!SampleTypeContains("data")){ iEvent.getByLabel("addPileupInfo", _puInfo); }
//		_BNtaus				= patTupleToBEANtranslator.PATtoBN(hPatTaus.product());
        
		Handle< edm::TriggerResults >                       hTriggerResults;
		iEvent.getByLabel(_HLTriggerSource,     hTriggerResults);
		//_BNtrigger				= patTupleToBEANtranslator.EDMtoBN(hTriggerResults.product(), iEvent, iSetup, iEvent.id().run());
		_BNtrigger				= patTupleToBEANtranslator.EDMtoBN(hTriggerResults.product(), iEvent, iSetup);
	}

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
