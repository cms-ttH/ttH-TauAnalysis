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
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"


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
		BNtauCollection				PATtoBN(pat::TauCollection const*);
		BNelectronCollection		PATtoBN(pat::ElectronCollection const*);
		BNmuonCollection			PATtoBN(pat::MuonCollection const*);
		BNjetCollection				PATtoBN(pat::JetCollection const*);
		BNmetCollection				PATtoBN(pat::METCollection const*);
		BNprimaryvertexCollection	RECOtoBN(reco::VertexCollection const*);
		BNtriggerCollection			EDMtoBN(edm::TriggerResults const*);

	private:
		// === Core functions === //

	// ----- Variables ----- //
	private:
		
};

#endif
