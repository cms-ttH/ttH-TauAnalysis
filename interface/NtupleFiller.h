// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _NtupleFiller_h
#define _NtupleFiller_h


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

#include <TTree.h>

using namespace std;
using namespace edm;

typedef reco::Candidate::LorentzVector LorentzVector;
typedef std::vector< reco::Candidate::LorentzVector > LVCollection;

class NtupleFiller : public EDAnalyzer {
	public:
		explicit NtupleFiller(const ParameterSet&);
		~NtupleFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);
		virtual void ClearVectors();

	protected:
		// === Core functions === //
		virtual void analyze(const Event&, const EventSetup&);
		virtual void SetupBranches();
		virtual void GetCollections(const Event&, const EventSetup&);



		// === Helper functions === //
/*		template <typename PatObject> pair<bool, reco::Candidate::LorentzVector> matchToGen(const PatObject&, int);
		pair<bool, reco::Candidate::LorentzVector> matchToGen(const pat::Tau&);
		double matchToGenParentMass(const pat::Tau&);
		virtual pair<bool, reco::Candidate::LorentzVector> MatchesGenHadronicTau(const pat::Tau&, double);
		virtual pair<bool, reco::Candidate::LorentzVector> matchToGen(const pat::Tau&, double, int, int iMotherPdgId=0, int iGrandMotherPdgId=0, bool iCheckNeutrinos=true);//*/
		template <typename PatObject> double CalculateLeptonMetMt(const PatObject&);
		template <typename PatObject1, typename PatObject2> double CalculatePZeta(const PatObject1&, const PatObject2&);
		template <typename PatObject1, typename PatObject2> double CalculatePZetaVis(const PatObject1&, const PatObject2&);
		template <typename PatObject1, typename PatObject2> double GetVisMass(const PatObject1&, const PatObject2&);
		template <typename PatObject1, typename PatObject2> double GetVisPlusMETMass(const PatObject1&, const PatObject2&);
		template <typename PatObject1, typename PatObject2, typename MetObject> double GetVisPlusMETMass(const PatObject1&, const PatObject2&, const MetObject&);
		template <typename PatObject1, typename PatObject2> double GetCollinearApproxMass(const PatObject1&, const PatObject2&);
		bool IsInTheCracks(float);
		template <typename PatObject> std::pair<unsigned int, unsigned int> getMatchedPdgId(const PatObject&);
		
	protected:
		TTree* _Tree;

		string _AnalysisType;

		// === Generator level Inputs === //
		InputTag _GenParticleSource;

		// === Tau and Leptons Inputs === //
		InputTag _RecoTauSource;
		InputTag _RecoMuonSource;
		InputTag _RecoElectronSource;
		bool _UseHeepInfo;
		InputTag _RecoParticleFlowSource;

		// === Jet Inputs === //
		InputTag _RecoJetSource;
		double _RecoJetMinEt;
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

		// === Topology Inputs
		InputTag _RecoPATMetSource;
		InputTag _RecoPFMetSource;


		// === Handles to collections === //
		Handle< reco::GenParticleCollection >				_genParticles;
		Handle< pat::TauCollection >						_patTaus;
		Handle< pat::ElectronCollection >					_patElectrons;
		Handle< pat::MuonCollection >						_patMuons;
		Handle< pat::JetCollection >						_patJets;
		Handle< pat::METCollection >						_patMETs;
		Handle< edm::View<pat::MET> >						_pfMETs;
		Handle< reco::VertexCollection >					_primaryVertices;
		Handle< std::vector< PileupSummaryInfo > >			_puInfo;
	

};

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
