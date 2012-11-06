// Author: Nil Valls

#ifndef _PATupleToBEANtranslator_h
#define _PATupleToBEANtranslator_h

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Run.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"


#include "ProductArea/BNcollections/interface/BNevent.h"
#include "ProductArea/BNcollections/interface/BNjet.h"
#include "ProductArea/BNcollections/interface/BNgenjet.h"
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


class PATupleToBEANtranslator{

	// ----- Functions ----- //
	public:
		explicit PATupleToBEANtranslator();
		~PATupleToBEANtranslator();

		BNmcparticleCollection		RECOtoBN(reco::GenParticleCollection const*);
		BNgenjetCollection			RECOtoBN(reco::GenJetCollection const*);
		BNtauCollection				PATtoBN(pat::TauCollection const*, reco::Vertex const*);
		BNelectronCollection		PATtoBN(pat::ElectronCollection const*, reco::Vertex const*, reco::BeamSpot const*);
		BNmuonCollection			PATtoBN(pat::MuonCollection const*, reco::Vertex const*, reco::BeamSpot const*);
		BNjetCollection				PATtoBN(pat::JetCollection const*, reco::Vertex const*, const edm::Event&, const edm::EventSetup&);
		BNmetCollection				PATtoBN(pat::METCollection const*);
		BNprimaryvertexCollection	RECOtoBN(reco::VertexCollection const*);
		BNtriggerCollection			EDMtoBN(edm::TriggerResults const*, const edm::Event&, const edm::EventSetup&);

        void setMinJetPt(float minJetPt) {minJetPt_ = minJetPt;};
        void setMinNDOF(int minNDOF) {minNDOF_ = minNDOF;};
        void setMaxAbsZ(float maxAbsZ) {maxAbsZ_ = maxAbsZ;};
        void setMaxd0(float maxd0) {maxd0_ = maxd0;};
        const reco::Vertex* getPrimaryVertex(reco::VertexCollection const*);

	private:
		// === Core functions === //
        bool tauIsInTheCracks(float);

	// ----- Variables ----- //
	private:
        float minJetPt_;
        int minNDOF_;
        float maxAbsZ_;
        float maxd0_;

		
};

#endif
