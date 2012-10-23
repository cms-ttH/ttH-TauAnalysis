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
	beanHelper.SetUp("Era",			 GetAnalysisTypeParameter(0));
	beanHelper.SetUp("IsLJ",		 "false");
	beanHelper.SetUp("ReshapeCSV",	 "true");
	beanHelper.SetUp("IsData",		 SampleTypeContains("data") ? "true" : "false");
	//beanHelper.SetUp("SampleNumber", GetAnalysisTypeParameter(4));
	beanHelper.setMCsample(atoi(GetAnalysisTypeParameter(4).c_str()), (atoi(GetAnalysisTypeParameter(0).c_str()) == 2012), false, "SingleMu");

}

// === Destructor === //
NtupleFiller::~NtupleFiller(){}


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
		iEvent.getByLabel("BNproducer",			_BNevent);
		iEvent.getByLabel(_RecoElectronSource,	_BNelectrons);
		iEvent.getByLabel(_RecoMuonSource, 		_BNmuons);
		iEvent.getByLabel(_RecoTauSource, 		_BNtaus);
		iEvent.getByLabel(_RecoJetSource, 		_BNjets);
		//iEvent.getByLabel(_RecoPATMetSource, 	_BNmet);
		iEvent.getByLabel(_RecoPFMetSource,		_BNmet);
		iEvent.getByLabel(_RecoVertexSource,	_BNprimaryVertices);
		iEvent.getByLabel("BNproducer::HLT",	_BNtrigger);
		iEvent.getByLabel(_HLTriggerSource,     _triggerResults);
	}else{
		iEvent.getByLabel(_RecoTauSource, 		_patTaus);
		iEvent.getByLabel(_RecoMuonSource, 		_patMuons);
		if(_GenParticleSource.label()	!= "") { iEvent.getByLabel(_GenParticleSource, _genParticles); }
		if(_GenJetSource.label()		!= "") { iEvent.getByLabel(_GenJetSource, _genJets); }
		iEvent.getByLabel(_RecoElectronSource,	_patElectrons);
		iEvent.getByLabel(_RecoJetSource,		_patJets);
		iEvent.getByLabel(_RecoPATMetSource,	_patMETs);
		iEvent.getByLabel(_RecoPFMetSource,		_pfMETs);
		iEvent.getByLabel(_RecoVertexSource,	_primaryVertices);
		if(!SampleTypeContains("data")){ iEvent.getByLabel("addPileupInfo", _puInfo); }
		iEvent.getByLabel(_HLTriggerSource,     _triggerResults);
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

// Btagging with electrons
unsigned int NtupleFiller::GetNumCSVbtags(const pat::Tau& Tau1, const pat::Tau& Tau2, const pat::Electron& Electron, const string iWP){ 
	unsigned int result = 0;

	// Define working points
	float wp = 0;
	if(iWP.compare("L")==0){		wp = _CSVlooseWP;	}	
	else if(iWP.compare("M")==0){	wp = _CSVmediumWP;	}	
	else if(iWP.compare("T")==0){	wp = _CSVtightWP;	}	
	else{ cerr << "ERROR in " << __FILE__ << "\tb-Tagging working point '" << iWP << "' not understood. Choose 'L' or 'M' or 'T'." << endl; exit(1); }

	// Loop over jets
	for(pat::JetCollection::const_iterator Jet = _patJets->begin(); Jet != _patJets->end(); ++Jet){

		// Antimatching to taus and Electron
		if(deltaR(Jet->eta(), Jet->phi(), Tau1.eta(), Tau1.phi()) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta(), Jet->phi(), Tau2.eta(), Tau2.phi()) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta(), Jet->phi(), Electron.eta(), Electron.phi()) < _JetAntiMatchingDeltaR){ continue; }

		// Kinematic requirements for jets
		if(Jet->pt() < _RecoJetMinPt){ continue; }
		if(fabs(Jet->eta()) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta()) >_RecoJetMaxAbsEta){ continue; }

		// Count jets passing the required b-tagging
		float combSecVtxBTag = Jet->bDiscriminator("combinedSecondaryVertexBJetTags");
		if(combSecVtxBTag >= wp){ result++; } 
	}

	return result;
}

unsigned int NtupleFiller::GetNumCSVextraJets(const pat::Tau& Tau1, const pat::Tau& Tau2, const pat::Electron& Electron, const string iWP){ 
	unsigned int result = 0;

	// Define working points
	float wp = 0;
	if(iWP.compare("L")==0){		wp = _CSVlooseWP;	}	
	else if(iWP.compare("M")==0){	wp = _CSVmediumWP;	}	
	else if(iWP.compare("T")==0){	wp = _CSVtightWP;	}	
	else{ cerr << "ERROR in " << __FILE__ << "\tb-Tagging working point '" << iWP << "' not understood. Choose 'L' or 'M' or 'T'." << endl; exit(1); }

	// Loop over jets
	for(pat::JetCollection::const_iterator Jet = _patJets->begin(); Jet != _patJets->end(); ++Jet){

		// Antimatching to taus and Electron
		if(deltaR(Jet->eta(), Jet->phi(), Tau1.eta(), Tau1.phi()) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta(), Jet->phi(), Tau2.eta(), Tau2.phi()) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta(), Jet->phi(), Electron.eta(), Electron.phi()) < _JetAntiMatchingDeltaR){ continue; }

		// Kinematic requirements for jets
		if(Jet->pt() < _RecoJetMinPt){ continue; }
		if(fabs(Jet->eta()) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta()) >_RecoJetMaxAbsEta){ continue; }

		// Count jets failing the required b-tagging
		float combSecVtxBTag = Jet->bDiscriminator("combinedSecondaryVertexBJetTags");
		if(combSecVtxBTag < wp){ result++; } 
	}

	return result;
}

unsigned int NtupleFiller::GetNumCSVbtags(const BNtau& Tau1, const BNtau& Tau2, const BNelectron& Electron, const string iWP){ 
	unsigned int result = 0;

	// Define working points
	float wp = 0;
	if(iWP.compare("L")==0){		wp = _CSVlooseWP;	}	
	else if(iWP.compare("M")==0){	wp = _CSVmediumWP;	}	
	else if(iWP.compare("T")==0){	wp = _CSVtightWP;	}	
	else{ cerr << "ERROR in " << __FILE__ << "\tb-Tagging working point '" << iWP << "' not understood. Choose 'L' or 'M' or 'T'." << endl; exit(1); }

	// Loop over jets
	for ( BNjetCollection::const_iterator Jet = _BNjets->begin(); Jet != _BNjets->end(); ++Jet ) {

		// Antimatching to taus and Electron
		if(deltaR(Jet->eta, Jet->phi, Tau1.eta, Tau1.phi) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta, Jet->phi, Tau2.eta, Tau2.phi) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta, Jet->phi, Electron.eta, Electron.phi) < _JetAntiMatchingDeltaR){ continue; }

		// Kinematic requirements for jets
		if(Jet->pt < _RecoJetMinPt){ continue; }
		if(fabs(Jet->eta) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta) >_RecoJetMaxAbsEta){ continue; }

		// Count jets passing the required b-tagging
		float combSecVtxBTag = Jet->btagCombinedSecVertex;
		if(combSecVtxBTag >= wp){ result++; } 
	}

	return result;
}

unsigned int NtupleFiller::GetNumCSVextraJets(const BNtau& Tau1, const BNtau& Tau2, const BNelectron& Electron, const string iWP){ 
	unsigned int result = 0;

	// Define working points
	float wp = 0;
	if(iWP.compare("L")==0){		wp = _CSVlooseWP;	}	
	else if(iWP.compare("M")==0){	wp = _CSVmediumWP;	}	
	else if(iWP.compare("T")==0){	wp = _CSVtightWP;	}	
	else{ cerr << "ERROR in " << __FILE__ << "\tb-Tagging working point '" << iWP << "' not understood. Choose 'L' or 'M' or 'T'." << endl; exit(1); }

	// Loop over jets
	for ( BNjetCollection::const_iterator Jet = _BNjets->begin(); Jet != _BNjets->end(); ++Jet ) {

		// Antimatching to taus and Electron
		if(deltaR(Jet->eta, Jet->phi, Tau1.eta, Tau1.phi) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta, Jet->phi, Tau2.eta, Tau2.phi) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta, Jet->phi, Electron.eta, Electron.phi) < _JetAntiMatchingDeltaR){ continue; }

		// Kinematic requirements for jets
		if(Jet->pt < _RecoJetMinPt){ continue; }
		if(fabs(Jet->eta) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta) >_RecoJetMaxAbsEta){ continue; }

		// Count jets failing the required b-tagging
		float combSecVtxBTag = Jet->btagCombinedSecVertex;
		if(combSecVtxBTag < wp){ result++; } 
	}

	return result;
}


unsigned int NtupleFiller::GetNumCSVextraJets(const pat::Tau& Tau1, const pat::Tau& Tau2, const string iWP){ 
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
		if(Jet->pt() < _RecoJetMinPt){ continue; }
		if(fabs(Jet->eta()) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta()) >_RecoJetMaxAbsEta){ continue; }

		// Count jets failing the required b-tagging
		float combSecVtxBTag = Jet->bDiscriminator("combinedSecondaryVertexBJetTags");
		if(combSecVtxBTag < wp){ result++; } 
	}

	return result;
}

unsigned int NtupleFiller::GetNumCSVbtags(const pat::Electron& Electron1, const pat::Electron& Electron2, const pat::Tau& Tau, const string iWP){ 
	unsigned int result = 0;

	// Define working points
	float wp = 0;
	if(iWP.compare("L")==0){		wp = _CSVlooseWP;	}	
	else if(iWP.compare("M")==0){	wp = _CSVmediumWP;	}	
	else if(iWP.compare("T")==0){	wp = _CSVtightWP;	}	
	else{ cerr << "ERROR in " << __FILE__ << "\tb-Tagging working point '" << iWP << "' not understood. Choose 'L' or 'M' or 'T'." << endl; exit(1); }

	// Loop over jets
	for(pat::JetCollection::const_iterator Jet = _patJets->begin(); Jet != _patJets->end(); ++Jet){

		// Antimatching to taus and Electron
		if(deltaR(Jet->eta(), Jet->phi(), Electron1.eta(), Electron1.phi()) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta(), Jet->phi(), Electron2.eta(), Electron2.phi()) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta(), Jet->phi(), Tau.eta(), Tau.phi()) < _JetAntiMatchingDeltaR){ continue; }

		// Kinematic requirements for jets
		if(Jet->pt() < _RecoJetMinPt){ continue; }
		if(fabs(Jet->eta()) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta()) >_RecoJetMaxAbsEta){ continue; }

		// Count jets passing the required b-tagging
		float combSecVtxBTag = Jet->bDiscriminator("combinedSecondaryVertexBJetTags");
		if(combSecVtxBTag >= wp){ result++; } 
	}

	return result;
}

unsigned int NtupleFiller::GetNumCSVextraJets(const pat::Electron& Electron1, const pat::Electron& Electron2, const pat::Tau& Tau, const string iWP){ 
	unsigned int result = 0;

	// Define working points
	float wp = 0;
	if(iWP.compare("L")==0){		wp = _CSVlooseWP;	}	
	else if(iWP.compare("M")==0){	wp = _CSVmediumWP;	}	
	else if(iWP.compare("T")==0){	wp = _CSVtightWP;	}	
	else{ cerr << "ERROR in " << __FILE__ << "\tb-Tagging working point '" << iWP << "' not understood. Choose 'L' or 'M' or 'T'." << endl; exit(1); }

	// Loop over jets
	for(pat::JetCollection::const_iterator Jet = _patJets->begin(); Jet != _patJets->end(); ++Jet){

		// Antimatching to taus and Electron
		if(deltaR(Jet->eta(), Jet->phi(), Electron1.eta(), Electron1.phi()) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta(), Jet->phi(), Electron2.eta(), Electron2.phi()) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta(), Jet->phi(), Tau.eta(), Tau.phi()) < _JetAntiMatchingDeltaR){ continue; }

		// Kinematic requirements for jets
		if(Jet->pt() < _RecoJetMinPt){ continue; }
		if(fabs(Jet->eta()) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta()) >_RecoJetMaxAbsEta){ continue; }

		// Count jets failing the required b-tagging
		float combSecVtxBTag = Jet->bDiscriminator("combinedSecondaryVertexBJetTags");
		if(combSecVtxBTag < wp){ result++; } 
	}

	return result;
}

unsigned int NtupleFiller::GetNumCSVbtags(const BNelectron& Electron1, const BNelectron& Electron2, const BNtau& Tau, const string iWP){ 
	unsigned int result = 0;

	// Define working points
	float wp = 0;
	if(iWP.compare("L")==0){		wp = _CSVlooseWP;	}	
	else if(iWP.compare("M")==0){	wp = _CSVmediumWP;	}	
	else if(iWP.compare("T")==0){	wp = _CSVtightWP;	}	
	else{ cerr << "ERROR in " << __FILE__ << "\tb-Tagging working point '" << iWP << "' not understood. Choose 'L' or 'M' or 'T'." << endl; exit(1); }

	// Loop over jets
	for ( BNjetCollection::const_iterator Jet = _BNjets->begin(); Jet != _BNjets->end(); ++Jet ) {

		// Antimatching to taus and Electron
		if(deltaR(Jet->eta, Jet->phi, Electron1.eta, Electron1.phi) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta, Jet->phi, Electron2.eta, Electron2.phi) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta, Jet->phi, Tau.eta, Tau.phi) < _JetAntiMatchingDeltaR){ continue; }

		// Kinematic requirements for jets
		if(Jet->pt < _RecoJetMinPt){ continue; }
		if(fabs(Jet->eta) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta) >_RecoJetMaxAbsEta){ continue; }

		// Count jets passing the required b-tagging
		float combSecVtxBTag = Jet->btagCombinedSecVertex;
		if(combSecVtxBTag >= wp){ result++; } 
	}

	return result;
}

unsigned int NtupleFiller::GetNumCSVextraJets(const BNelectron& Electron1, const BNelectron& Electron2, const BNtau& Tau, const string iWP){ 
	unsigned int result = 0;

	// Define working points
	float wp = 0;
	if(iWP.compare("L")==0){		wp = _CSVlooseWP;	}	
	else if(iWP.compare("M")==0){	wp = _CSVmediumWP;	}	
	else if(iWP.compare("T")==0){	wp = _CSVtightWP;	}	
	else{ cerr << "ERROR in " << __FILE__ << "\tb-Tagging working point '" << iWP << "' not understood. Choose 'L' or 'M' or 'T'." << endl; exit(1); }

	// Loop over jets
	for ( BNjetCollection::const_iterator Jet = _BNjets->begin(); Jet != _BNjets->end(); ++Jet ) {

		// Antimatching to taus and Electron
		if(deltaR(Jet->eta, Jet->phi, Electron1.eta, Electron1.phi) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta, Jet->phi, Electron2.eta, Electron2.phi) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta, Jet->phi, Tau.eta, Tau.phi) < _JetAntiMatchingDeltaR){ continue; }

		// Kinematic requirements for jets
		if(Jet->pt < _RecoJetMinPt){ continue; }
		if(fabs(Jet->eta) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta) >_RecoJetMaxAbsEta){ continue; }

		// Count jets failing the required b-tagging
		float combSecVtxBTag = Jet->btagCombinedSecVertex;
		if(combSecVtxBTag < wp){ result++; } 
	}

	return result;
}





// Btagging with muons

unsigned int NtupleFiller::GetNumCSVbtags(const pat::Tau& Tau1, const pat::Tau& Tau2, const pat::Muon& Muon, const string iWP){ 
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
		if(deltaR(Jet->eta(), Jet->phi(), Tau1.eta(), Tau1.phi()) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta(), Jet->phi(), Tau2.eta(), Tau2.phi()) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta(), Jet->phi(), Muon.eta(), Muon.phi()) < _JetAntiMatchingDeltaR){ continue; }

		// Kinematic requirements for jets
		if(Jet->pt() < _RecoJetMinPt){ continue; }
		if(fabs(Jet->eta()) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta()) >_RecoJetMaxAbsEta){ continue; }

		// Count jets passing the required b-tagging
		float combSecVtxBTag = Jet->bDiscriminator("combinedSecondaryVertexBJetTags");
		if(combSecVtxBTag >= wp){ result++; } 
	}

	return result;
}

unsigned int NtupleFiller::GetNumCSVextraJets(const pat::Tau& Tau1, const pat::Tau& Tau2, const pat::Muon& Muon, const string iWP){ 
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
		if(deltaR(Jet->eta(), Jet->phi(), Tau1.eta(), Tau1.phi()) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta(), Jet->phi(), Tau2.eta(), Tau2.phi()) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta(), Jet->phi(), Muon.eta(), Muon.phi()) < _JetAntiMatchingDeltaR){ continue; }

		// Kinematic requirements for jets
		if(Jet->pt() < _RecoJetMinPt){ continue; }
		if(fabs(Jet->eta()) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta()) >_RecoJetMaxAbsEta){ continue; }

		// Count jets failing the required b-tagging
		float combSecVtxBTag = Jet->bDiscriminator("combinedSecondaryVertexBJetTags");
		if(combSecVtxBTag < wp){ result++; } 
	}

	return result;
}

unsigned int NtupleFiller::GetNumCSVbtags(const BNtau& Tau1, const BNtau& Tau2, const BNmuon& Muon, const string iWP){ 
	unsigned int result = 0;

	// Define working points
	float wp = 0;
	if(iWP.compare("L")==0){		wp = _CSVlooseWP;	}	
	else if(iWP.compare("M")==0){	wp = _CSVmediumWP;	}	
	else if(iWP.compare("T")==0){	wp = _CSVtightWP;	}	
	else{ cerr << "ERROR in " << __FILE__ << "\tb-Tagging working point '" << iWP << "' not understood. Choose 'L' or 'M' or 'T'." << endl; exit(1); }

	// Loop over jets
	for ( BNjetCollection::const_iterator Jet = _BNjets->begin(); Jet != _BNjets->end(); ++Jet ) {

		// Antimatching to taus and muon
		if(deltaR(Jet->eta, Jet->phi, Tau1.eta, Tau1.phi) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta, Jet->phi, Tau2.eta, Tau2.phi) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta, Jet->phi, Muon.eta, Muon.phi) < _JetAntiMatchingDeltaR){ continue; }

		// Kinematic requirements for jets
		if(Jet->pt < _RecoJetMinPt){ continue; }
		if(fabs(Jet->eta) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta) >_RecoJetMaxAbsEta){ continue; }

		// Count jets passing the required b-tagging
		float combSecVtxBTag = Jet->btagCombinedSecVertex;
		if(combSecVtxBTag >= wp){ result++; } 
	}

	return result;
}

unsigned int NtupleFiller::GetNumCSVextraJets(const BNtau& Tau1, const BNtau& Tau2, const BNmuon& Muon, const string iWP){ 
	unsigned int result = 0;

	// Define working points
	float wp = 0;
	if(iWP.compare("L")==0){		wp = _CSVlooseWP;	}	
	else if(iWP.compare("M")==0){	wp = _CSVmediumWP;	}	
	else if(iWP.compare("T")==0){	wp = _CSVtightWP;	}	
	else{ cerr << "ERROR in " << __FILE__ << "\tb-Tagging working point '" << iWP << "' not understood. Choose 'L' or 'M' or 'T'." << endl; exit(1); }

	// Loop over jets
	for ( BNjetCollection::const_iterator Jet = _BNjets->begin(); Jet != _BNjets->end(); ++Jet ) {

		// Antimatching to taus and muon
		if(deltaR(Jet->eta, Jet->phi, Tau1.eta, Tau1.phi) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta, Jet->phi, Tau2.eta, Tau2.phi) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta, Jet->phi, Muon.eta, Muon.phi) < _JetAntiMatchingDeltaR){ continue; }

		// Kinematic requirements for jets
		if(Jet->pt < _RecoJetMinPt){ continue; }
		if(fabs(Jet->eta) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta) >_RecoJetMaxAbsEta){ continue; }

		// Count jets failing the required b-tagging
		float combSecVtxBTag = Jet->btagCombinedSecVertex;
		if(combSecVtxBTag < wp){ result++; } 
	}

	return result;
}

unsigned int NtupleFiller::GetNumCSVbtags(const pat::Tau& Tau1, const pat::Tau& Tau2, const string iWP){ 
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
		if(Jet->pt() < _RecoJetMinPt){ continue; }
		if(fabs(Jet->eta()) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta()) >_RecoJetMaxAbsEta){ continue; }

		// Count jets passing the required b-tagging
		float combSecVtxBTag = Jet->bDiscriminator("combinedSecondaryVertexBJetTags");
		if(combSecVtxBTag >= wp){ result++; } 
	}

	return result;
}


unsigned int NtupleFiller::GetNumCSVbtags(const pat::Muon& Muon1, const pat::Muon& Muon2, const pat::Tau& Tau, const string iWP){ 
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
		if(Jet->pt() < _RecoJetMinPt){ continue; }
		if(fabs(Jet->eta()) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta()) >_RecoJetMaxAbsEta){ continue; }

		// Count jets passing the required b-tagging
		float combSecVtxBTag = Jet->bDiscriminator("combinedSecondaryVertexBJetTags");
		if(combSecVtxBTag >= wp){ result++; } 
	}

	return result;
}

unsigned int NtupleFiller::GetNumCSVextraJets(const pat::Muon& Muon1, const pat::Muon& Muon2, const pat::Tau& Tau, const string iWP){ 
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
		if(Jet->pt() < _RecoJetMinPt){ continue; }
		if(fabs(Jet->eta()) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta()) >_RecoJetMaxAbsEta){ continue; }

		// Count jets failing the required b-tagging
		float combSecVtxBTag = Jet->bDiscriminator("combinedSecondaryVertexBJetTags");
		if(combSecVtxBTag < wp){ result++; } 
	}

	return result;
}

unsigned int NtupleFiller::GetNumCSVbtags(const BNmuon& Muon1, const BNmuon& Muon2, const BNtau& Tau, const string iWP){ 
	unsigned int result = 0;

	// Define working points
	float wp = 0;
	if(iWP.compare("L")==0){		wp = _CSVlooseWP;	}	
	else if(iWP.compare("M")==0){	wp = _CSVmediumWP;	}	
	else if(iWP.compare("T")==0){	wp = _CSVtightWP;	}	
	else{ cerr << "ERROR in " << __FILE__ << "\tb-Tagging working point '" << iWP << "' not understood. Choose 'L' or 'M' or 'T'." << endl; exit(1); }

	// Loop over jets
	for ( BNjetCollection::const_iterator Jet = _BNjets->begin(); Jet != _BNjets->end(); ++Jet ) {

		// Antimatching to taus and muon
		if(deltaR(Jet->eta, Jet->phi, Muon1.eta, Muon1.phi) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta, Jet->phi, Muon2.eta, Muon2.phi) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta, Jet->phi, Tau.eta, Tau.phi) < _JetAntiMatchingDeltaR){ continue; }

		// Kinematic requirements for jets
		if(Jet->pt < _RecoJetMinPt){ continue; }
		if(fabs(Jet->eta) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta) >_RecoJetMaxAbsEta){ continue; }

		// Count jets passing the required b-tagging
		float combSecVtxBTag = Jet->btagCombinedSecVertex;
		if(combSecVtxBTag >= wp){ result++; } 
	}

	return result;
}

unsigned int NtupleFiller::GetNumCSVextraJets(const BNmuon& Muon1, const BNmuon& Muon2, const BNtau& Tau, const string iWP){ 
	unsigned int result = 0;

	// Define working points
	float wp = 0;
	if(iWP.compare("L")==0){		wp = _CSVlooseWP;	}	
	else if(iWP.compare("M")==0){	wp = _CSVmediumWP;	}	
	else if(iWP.compare("T")==0){	wp = _CSVtightWP;	}	
	else{ cerr << "ERROR in " << __FILE__ << "\tb-Tagging working point '" << iWP << "' not understood. Choose 'L' or 'M' or 'T'." << endl; exit(1); }

	// Loop over jets
	for ( BNjetCollection::const_iterator Jet = _BNjets->begin(); Jet != _BNjets->end(); ++Jet ) {

		// Antimatching to taus and muon
		if(deltaR(Jet->eta, Jet->phi, Muon1.eta, Muon1.phi) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta, Jet->phi, Muon2.eta, Muon2.phi) < _JetAntiMatchingDeltaR){ continue; }
		if(deltaR(Jet->eta, Jet->phi, Tau.eta, Tau.phi) < _JetAntiMatchingDeltaR){ continue; }

		// Kinematic requirements for jets
		if(Jet->pt < _RecoJetMinPt){ continue; }
		if(fabs(Jet->eta) <_RecoJetMinAbsEta){ continue; }
		if(fabs(Jet->eta) >_RecoJetMaxAbsEta){ continue; }

		// Count jets failing the required b-tagging
		float combSecVtxBTag = Jet->btagCombinedSecVertex;
		if(combSecVtxBTag < wp){ result++; } 
	}

	return result;
}



//define this as a plug-in
DEFINE_FWK_MODULE(NtupleFiller);
