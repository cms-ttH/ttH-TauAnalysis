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
	
	_Tree							= NULL;

	_AnalysisType					= iConfig.getParameter<string>("AnalysisType");

	_GenParticleSource				= iConfig.getUntrackedParameter<InputTag>("GenParticleSource");
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

	_RecoJetMinEt					= iConfig.getParameter<double>("RecoJetMinEt");
	_RecoJetMinAbsEta				= iConfig.getParameter<double>("RecoJetMinAbsEta");
	_RecoJetMaxAbsEta				= iConfig.getParameter<double>("RecoJetMaxAbsEta");
	_JetAntiMatchingDeltaR			= iConfig.getParameter<double>("JetAntiMatchingDeltaR");
	_CSVlooseWP						= iConfig.getParameter<double>("CSVlooseWP");
	_CSVmediumWP					= iConfig.getParameter<double>("CSVmediumWP");
	_CSVtightWP						= iConfig.getParameter<double>("CSVtightWP");

}

// === Destructor === //
NtupleFiller::~NtupleFiller(){}

// ------------ method called to for each event  ------------
void NtupleFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void NtupleFiller::SetupBranches(){}

// === Get relevant collections === //
void NtupleFiller::GetCollections(const Event& iEvent, const EventSetup& iSetup){

	iEvent.getByLabel(_RecoTauSource, 		_patTaus);
	iEvent.getByLabel(_RecoMuonSource, 		_patMuons);
	if(_GenParticleSource.label() != "") { iEvent.getByLabel(_GenParticleSource, _genParticles); }
	iEvent.getByLabel(_RecoElectronSource,	_patElectrons);
	iEvent.getByLabel(_RecoJetSource,		_patJets);
	iEvent.getByLabel(_RecoPATMetSource,	_patMETs);
	iEvent.getByLabel(_RecoPFMetSource,		_pfMETs);

	iEvent.getByLabel(_RecoVertexSource,	_primaryVertices);
	if(_AnalysisType.compare("coll") != 0){ iEvent.getByLabel("addPileupInfo", _puInfo); }

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


//define this as a plug-in
DEFINE_FWK_MODULE(NtupleFiller);
