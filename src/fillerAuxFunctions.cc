#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"

template <class T> float getLeptonIso(const pat::Lepton<T>& lepton, bool isPfMuon = 0, bool subtractChargedPU = 0, bool doDeltaBeta = 0) {

    float sum = 0;
    if( lepton.pfCandidateRef().isNull() ) {// regular muon
        //std::cout << "standard muon" << std::endl;
        sum += lepton.trackIso();
        sum += lepton.ecalIso();
        sum += lepton.hcalIso();
    }
    else { // PF muon
        //std::cout << "PF muon" << std::endl;
        
        //float puChargedHadronIso = lepton.puChargedHadronIso(); not present until 4_4_X
        float puChargedHadronIso = 0;

        float chargedHadronIso = lepton.chargedHadronIso();
        float neutralHadronIso = lepton.neutralHadronIso();
        float photonIso = lepton.photonIso();

        float sum = chargedHadronIso + neutralHadronIso + photonIso; 
        if(subtractChargedPU) sum -= puChargedHadronIso; 

        float deltaBetaCorr = 0; //to be implemented
        if(doDeltaBeta) sum -= deltaBetaCorr;
    }

    return sum;
}
