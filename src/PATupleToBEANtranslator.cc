// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/PATupleToBEANtranslator.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
PATupleToBEANtranslator::PATupleToBEANtranslator(){
}

// === Destructor === //
PATupleToBEANtranslator::~PATupleToBEANtranslator(){}

BNmcparticleCollection	PATupleToBEANtranslator::RECOtoBN(reco::GenParticleCollection const* iCollection){
    BNmcparticleCollection result;
    return result;
}


BNgenjetCollection		PATupleToBEANtranslator::RECOtoBN(reco::GenJetCollection const* iCollection){
    BNgenjetCollection result;
    return result;
}


BNtauCollection			PATupleToBEANtranslator::PATtoBN(pat::TauCollection	const* iCollection){
    BNtauCollection result;
    return result;
}

BNelectronCollection	PATupleToBEANtranslator::PATtoBN(pat::ElectronCollection const* iCollection){
	BNelectronCollection result;
	return result;
}


BNmuonCollection		PATupleToBEANtranslator::PATtoBN(pat::MuonCollection const* iCollection){
    BNmuonCollection result;
    return result;
}


BNjetCollection			PATupleToBEANtranslator::PATtoBN(pat::JetCollection const* iCollection){
	BNjetCollection result;
	return result;
}


BNmetCollection			PATupleToBEANtranslator::PATtoBN(pat::METCollection const* iCollection){
	BNmetCollection result;
	return result;
}


BNprimaryvertexCollection	PATupleToBEANtranslator::RECOtoBN(reco::VertexCollection const* iCollection){
	BNprimaryvertexCollection result;
	return result;
}


BNtriggerCollection	PATupleToBEANtranslator::EDMtoBN(edm::TriggerResults const* iCollection){
	BNtriggerCollection result;
	return result;
}


