// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _NtupleFiller_h
#define _NtupleFiller_h

#include <algorithm>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/normalizedPhi.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "../src/fillerAuxFunctions.cc"
#include "NtupleMaker/BEANmaker/interface/BEANhelper.h"

// Headers for the BEAN data items
#include "ProductArea/BNcollections/interface/BNevent.h"
#include "ProductArea/BNcollections/interface/BNjet.h"
#include "ProductArea/BNcollections/interface/BNmcparticle.h"
#include "ProductArea/BNcollections/interface/BNmet.h"
#include "ProductArea/BNcollections/interface/BNelectron.h"
#include "ProductArea/BNcollections/interface/BNmuon.h"
#include "ProductArea/BNcollections/interface/BNtau.h"
#include "ProductArea/BNcollections/interface/BNphoton.h"
#include "ProductArea/BNcollections/interface/BNsupercluster.h"
#include "ProductArea/BNcollections/interface/BNtrack.h"
#include "ProductArea/BNcollections/interface/BNtrigger.h"
#include "ProductArea/BNcollections/interface/BNskimbits.h"
#include "ProductArea/BNcollections/interface/BNtrigobj.h"
#include "ProductArea/BNcollections/interface/BNprimaryvertex.h"


#include <TTree.h>

using namespace std;
using namespace edm;

typedef reco::Candidate::LorentzVector LorentzVector;
typedef std::vector< reco::Candidate::LorentzVector > LVCollection;

class NtupleFiller : public EDAnalyzer {
	public:
		BEANhelper beanHelper;
		explicit NtupleFiller(const ParameterSet&);
		~NtupleFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);
		virtual void ClearVectors();

	protected:
		// === Core functions === //
		virtual void analyze(const Event&, const EventSetup&);
		virtual void SetupBranches();
		virtual void GetCollections(const Event&, const EventSetup&);
		string GetAnalysisTypeParameter(unsigned int);
		unsigned int GetEra();
		const char GetSubera();
		string GetSampleType();
		string GetLeptonFlavor();
		bool EraIs(unsigned int);
		bool SuberaIs(const char);
		bool SampleTypeIs(const string);
		bool SampleTypeContains(const string);
		bool LeptonFlavorIs(const string);

		// === Helper functions === //
		template <typename PatObject1, typename PatObject2> double GetComboMass(const PatObject1&, const PatObject2&);
		template <typename BNObject1, typename BNObject2> double GetComboMassBN(const BNObject1&, const BNObject2&);
		template <typename PatObject1, typename PatObject2, typename MetObject> double GetComboMass(const PatObject1&, const PatObject2&, const MetObject&);
		template <typename BNObject1, typename BNObject2, typename MetObject> double GetComboMassBN(const BNObject1&, const BNObject2&, const MetObject&);
		template <typename PatObject, typename MetObject> double GetTransverseMass(const PatObject&, const MetObject&);
		template <typename PatObject1, typename PatObject2, typename MetObject> double GetPZeta(const PatObject1&, const PatObject2&, const MetObject&);
		template <typename PatObject1, typename PatObject2> double GetPZetaVis(const PatObject1&, const PatObject2&);
		bool IsInTheCracks(float);

		unsigned int GetNumCSVbtags(const pat::Tau&, const pat::Tau&, const string); 
		unsigned int GetNumCSVextraJets(const pat::Tau&, const pat::Tau&, const string); 

		unsigned int GetNumCSVbtags(const pat::Tau&, const pat::Tau&, const pat::Electron&, const string); 
		unsigned int GetNumCSVextraJets(const pat::Tau&, const pat::Tau&, const pat::Electron&, const string); 
		unsigned int GetNumCSVbtags(const BNtau&, const BNtau&, const BNelectron&, const string); 
		unsigned int GetNumCSVextraJets(const BNtau&, const BNtau&, const BNelectron&, const string); 
		unsigned int GetNumCSVbtags(const pat::Electron&, const pat::Electron&, const pat::Tau&, const string); 
		unsigned int GetNumCSVextraJets(const pat::Electron&, const pat::Electron&, const pat::Tau&, const string); 
		unsigned int GetNumCSVbtags(const BNelectron&, const BNelectron&, const BNtau&, const string); 
		unsigned int GetNumCSVextraJets(const BNelectron&, const BNelectron&, const BNtau&, const string); 

		unsigned int GetNumCSVbtags(const pat::Tau&, const pat::Tau&, const pat::Muon&, const string); 
		unsigned int GetNumCSVextraJets(const pat::Tau&, const pat::Tau&, const pat::Muon&, const string); 
		unsigned int GetNumCSVbtags(const BNtau&, const BNtau&, const BNmuon&, const string); 
		unsigned int GetNumCSVextraJets(const BNtau&, const BNtau&, const BNmuon&, const string); 
		unsigned int GetNumCSVbtags(const pat::Muon&, const pat::Muon&, const pat::Tau&, const string); 
		unsigned int GetNumCSVextraJets(const pat::Muon&, const pat::Muon&, const pat::Tau&, const string); 
		unsigned int GetNumCSVbtags(const BNmuon&, const BNmuon&, const BNtau&, const string); 
		unsigned int GetNumCSVextraJets(const BNmuon&, const BNmuon&, const BNtau&, const string); 
/*		template <typename PatObject> pair<bool, reco::Candidate::LorentzVector> matchToGen(const PatObject&, int);
		pair<bool, reco::Candidate::LorentzVector> matchToGen(const pat::Tau&);
		double matchToGenParentMass(const pat::Tau&);
		virtual pair<bool, reco::Candidate::LorentzVector> MatchesGenHadronicTau(const pat::Tau&, double);
		template <typename PatObject> std::pair<unsigned int, unsigned int> getMatchedPdgId(const PatObject&);
		virtual pair<bool, reco::Candidate::LorentzVector> matchToGen(const pat::Tau&, double, int, int iMotherPdgId=0, int iGrandMotherPdgId=0, bool iCheckNeutrinos=true);//*/
		
	protected:
		TTree* _Tree;

		string _AnalysisType;
		vector<string> _AnalysisTypeVector;
		bool _FromBEAN;
		string _Era;
		//BEANhelper beanHelper;

		// === Generator level Inputs === //
		InputTag _GenParticleSource;
		InputTag _GenJetSource;

		// === Tau and Leptons Inputs === //
		InputTag _RecoTauSource;
		InputTag _RecoMuonSource;
		InputTag _RecoElectronSource;
		bool _UseHeepInfo;
		InputTag _RecoParticleFlowSource;
		double _RecoTauMinPt;
		double _RecoTauMaxAbsEta;
		bool _RecoTauRequireDMF;

		// === Jet Inputs === //
		InputTag _RecoJetSource;
		double _RecoJetMinPt;
		double _RecoJetMinAbsEta;
		double _RecoJetMaxAbsEta;
		double _JetAntiMatchingDeltaR;
		double _CSVlooseWP;
		double _CSVmediumWP;
		double _CSVtightWP;

		// === Vertex Inputs === //
		InputTag _RecoVertexSource;
		double _RecoVertexMaxZposition;
		double _RecoVertexTrackWeight;
		int _RecoVertexMinTracks;

        // === HLT input === //
        InputTag _HLTriggerSource;

		// === Topology Inputs
		InputTag _RecoPATMetSource;
		InputTag _RecoPFMetSource;


		// === Handles to collections === //
		Handle<BNeventCollection>				_BNevent;
		Handle<BNelectronCollection>			_BNelectrons;
		Handle<BNmuonCollection>				_BNmuons;
		Handle<BNtauCollection>					_BNtaus;
		Handle<BNjetCollection>					_BNjets;
		Handle<BNmetCollection>					_BNmet;
		Handle<BNprimaryvertexCollection>		_BNprimaryVertices;
		Handle<BNtriggerCollection>				_BNtrigger;

		Handle< reco::GenParticleCollection >				_genParticles;
		Handle< reco::GenJetCollection >					_genJets;
		Handle< pat::TauCollection >						_patTaus;
		Handle< pat::ElectronCollection >					_patElectrons;
		Handle< pat::MuonCollection >						_patMuons;
		Handle< pat::JetCollection >						_patJets;
		Handle< pat::METCollection >						_patMETs;
		Handle< edm::View<pat::MET> >						_pfMETs;
		Handle< reco::VertexCollection >					_primaryVertices;
		Handle< std::vector< PileupSummaryInfo > >			_puInfo;
        Handle< edm::TriggerResults >                       _triggerResults;

	

};


// === Visible mass === //
template <typename PatObject1, typename PatObject2> double NtupleFiller::GetComboMass(const PatObject1& patObject1, const PatObject2& patObject2){
	reco::Candidate::LorentzVector The_LorentzVect = patObject1.p4() + patObject2.p4();
	return The_LorentzVect.M();
}
template <typename BNObject1, typename BNObject2> double NtupleFiller::GetComboMassBN(const BNObject1& bnObject1, const BNObject2& bnObject2){
	reco::Candidate::LorentzVector object1p4(bnObject1.px, bnObject1.py, bnObject1.pz, bnObject1.energy);
	reco::Candidate::LorentzVector object2p4(bnObject2.px, bnObject2.py, bnObject2.pz, bnObject2.energy);
	reco::Candidate::LorentzVector The_LorentzVect = object1p4 + object2p4;
	return The_LorentzVect.M();
}

// === Visible + MET mass === //
template <typename PatObject1, typename PatObject2, typename MetObject> double NtupleFiller::GetComboMass(const PatObject1& patObject1, const PatObject2& patObject2, const MetObject& metObject){
	double px = patObject1.px() + patObject2.px() + metObject.px();
	double py = patObject1.py() + patObject2.py() + metObject.py();
	double pz = patObject1.pz() + patObject2.pz();
	double e = patObject1.energy() + patObject2.energy() + TMath::Sqrt((metObject.px() * metObject.px()) + (metObject.py() * metObject.py()));
	reco::Candidate::LorentzVector The_LorentzVect(px, py, pz, e); 
	return The_LorentzVect.M();
}

template <typename BNObject1, typename BNObject2, typename MetObject> double NtupleFiller::GetComboMassBN(const BNObject1& bnObject1, const BNObject2& bnObject2, const MetObject& metObject){
	reco::Candidate::LorentzVector object1p4(bnObject1.px, bnObject1.py, bnObject1.pz, bnObject1.energy);
	reco::Candidate::LorentzVector object2p4(bnObject2.px, bnObject2.py, bnObject2.pz, bnObject2.energy);
	//reco::Candidate::LorentzVector object1p4(0,0,0,0);
	//reco::Candidate::LorentzVector object2p4(0,0,0,0);
	double px = object1p4.px() + object2p4.px() + metObject.px;
	double py = object1p4.py() + object2p4.py() + metObject.py;
	double pz = object1p4.pz() + object2p4.pz();
	double e = 0;
//	double e = bnObject1.energy + bnObject2.energy + TMath::Sqrt((metObject.px * metObject.px) + (metObject.py * metObject.py));
	reco::Candidate::LorentzVector The_LorentzVect(px, py, pz, e); 
	return The_LorentzVect.M();
}

// === Lepton + MET mass === //
template <typename PatObject, typename MetObject> double NtupleFiller::GetTransverseMass(const PatObject& patObject, const MetObject& metObject){
	double px = patObject.px() + metObject.px();
	double py = patObject.py() + metObject.py();
	double et = patObject.et() + TMath::Sqrt((metObject.px() * metObject.px()) + (metObject.py() * metObject.py()));
	double mt2 = et*et - (px*px + py*py);
	if ( mt2 < 0 ) { return -1.; }
	else { return sqrt(mt2); }
}

// === p zeta === //
template <typename PatObject1, typename PatObject2, typename MetObject> double NtupleFiller::GetPZeta(const PatObject1& patObject1, const PatObject2& patObject2, const MetObject& metObject){
	double zetaX = cos(patObject1.phi()) + cos(patObject2.phi());
	double zetaY = sin(patObject1.phi()) + sin(patObject2.phi());
	double zetaR = TMath::Sqrt(zetaX*zetaX + zetaY*zetaY);
	if ( zetaR > 0. ) { zetaX /= zetaR; zetaY /= zetaR; }
	double visPx = patObject1.px() + patObject2.px();
	double visPy = patObject1.py() + patObject2.py();
	double px = visPx + metObject.px();
	double py = visPy + metObject.py();
	double pZeta = px*zetaX + py*zetaY;
	return pZeta;
}

// === p zeta vis === //
template <typename PatObject1, typename PatObject2> double NtupleFiller::GetPZetaVis(const PatObject1& patObject1, const PatObject2& patObject2){
	double zetaX = cos(patObject1.phi()) + cos(patObject2.phi());
	double zetaY = sin(patObject1.phi()) + sin(patObject2.phi());
	double zetaR = TMath::Sqrt(zetaX*zetaX + zetaY*zetaY);
	if ( zetaR > 0. ) { zetaX /= zetaR; zetaY /= zetaR; }
	double visPx = patObject1.px() + patObject2.px();
	double visPy = patObject1.py() + patObject2.py();
	double pZetaVis = visPx*zetaX + visPy*zetaY;
	return pZetaVis;
}


/*
template <typename PatObject>
pair<unsigned int, unsigned int> Ntuplizer::getMatchedPdgId(const PatObject& patObject){
	pair<unsigned int, unsigned int> theTrackAndMotherPdgId;
	float minDeltaPt = 1000.;
	float minDeltaR = 0.2;
	unsigned int thePdgId = 0;
	unsigned int theMotherPdgId = 0;

	for(reco::GenParticleCollection::const_iterator genParticle = _genParticles->begin();genParticle != _genParticles->end();++genParticle){
		if(patObject.charge() != genParticle->charge() || genParticle->status() != 1)continue;  // match only to final states...
		if(reco::deltaR(patObject.eta(), patObject.phi(), genParticle->eta(), genParticle->phi()) > minDeltaR) continue ;
		float theDeltaPt = fabs(patObject.pt() - genParticle->pt());
		if(theDeltaPt < minDeltaPt){
			minDeltaPt = theDeltaPt;
			thePdgId = abs(genParticle->pdgId());
			theMotherPdgId = abs(genParticle->mother()->pdgId());
		}
	}
	theTrackAndMotherPdgId = make_pair<unsigned int, unsigned int>(thePdgId, theMotherPdgId);
	return theTrackAndMotherPdgId;
}

template <typename PatObject1, typename PatObject2>
double Ntuplizer::GetVisMass(const PatObject1& patObject1, const PatObject2& patObject2){
	reco::Candidate::LorentzVector The_LorentzVect = patObject1.p4() + patObject2.p4();
	return The_LorentzVect.M();
}

template <typename PatObject1, typename PatObject2>
double Ntuplizer::GetVisPlusMETMass(const PatObject1& patObject1, const PatObject2& patObject2){
	double px = patObject1.px() + patObject2.px() + (*(_patMETs->begin())).px();
	double py = patObject1.py() + patObject2.py() + (*(_patMETs->begin())).py();
	double pz = patObject1.pz() + patObject2.pz();
	double e = patObject1.energy() + patObject2.energy() + TMath::Sqrt(((*(_patMETs->begin())).px() * (*(_patMETs->begin())).px()) + ((*(_patMETs->begin())).py() * (*(_patMETs->begin())).py()));
	reco::Candidate::LorentzVector The_LorentzVect(px, py, pz, e);
	return The_LorentzVect.M();
}

template <typename PatObject1, typename PatObject2, typename MetObject>
double Ntuplizer::GetVisPlusMETMass(const PatObject1& patObject1, const PatObject2& patObject2, const MetObject& metObject){
	double px = patObject1.px() + patObject2.px() + metObject.px();
	double py = patObject1.py() + patObject2.py() + metObject.py();
	double pz = patObject1.pz() + patObject2.pz();
	double e = patObject1.energy() + patObject2.energy() + TMath::Sqrt((metObject.px() * metObject.px()) + (metObject.py() * metObject.py()));
	reco::Candidate::LorentzVector The_LorentzVect(px, py, pz, e);
	return The_LorentzVect.M();
}

//*/

#endif
