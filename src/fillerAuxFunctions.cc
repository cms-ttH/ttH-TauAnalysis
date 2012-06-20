#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"

template <class T> float getLeptonPfIso(const pat::Lepton<T>& lepton, bool subtractChargedPU = 0, bool doDeltaBeta = 0) {
    
    //float puChargedHadronIso = lepton.puChargedHadronIso(); not present until 4_4_X
    float puChargedHadronIso = 0;
    float chargedHadronIso = lepton.chargedHadronIso();
    float neutralHadronIso = lepton.neutralHadronIso();
    float photonIso = lepton.photonIso();

    float sum = chargedHadronIso + neutralHadronIso + photonIso; 
    if(subtractChargedPU) sum -= puChargedHadronIso; 

    float deltaBetaCorr = 0; //to be implemented
    if(doDeltaBeta) sum -= deltaBetaCorr;

    return sum;
}
