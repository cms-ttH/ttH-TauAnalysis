#ifndef _fillerAuxFunctions_cc
#define _fillerAuxFunctions_cc

#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"

#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/PatCandidates/interface/Muon.h"


inline int getMuonID(const pat::Muon& Muon, math::XYZPoint& vertexPosition, bool returnLooseID = 0, bool requireTrackInfo = 0) {
    
    int isLooseMuon = -1;
    int isTightMuon = -1;
    isLooseMuon = Muon.isGlobalMuon();
    if(returnLooseID) 
        return isLooseMuon;

    isTightMuon = isLooseMuon;
    if(Muon.globalTrack().isAvailable() && Muon.globalTrack().isNonnull() ) { 
        if( !(Muon.isTrackerMuon()) ) isTightMuon = 0;
        if( !(Muon.isGood("GlobalMuonPromptTight")) ) isTightMuon = 0;
        std::cout << "finished GlobalMuonPromptTight " << std::endl;
        if( !(Muon.numberOfMatches() > 1) ) isTightMuon = 0;
        std::cout << "finished number of matches " << std::endl;
        if( !(Muon.numberOfValidHits() > 10) ) isTightMuon = 0;
        std::cout << "finished number of valid hits " << std::endl;
        if( !(Muon.dB(pat::Muon::PV2D) < 0.02) ) isTightMuon = 0;
        std::cout << "finished d0 " << std::endl;
        if(Muon.innerTrack().isAvailable() && Muon.innerTrack().isNonnull() ) { 
            std::cout << "doing track info " << std::endl;
            if( !(Muon.innerTrack()->hitPattern().pixelLayersWithMeasurement() > 0) ) isTightMuon = 0;
            if( !(Muon.innerTrack()->dz(vertexPosition) < 1) ) isTightMuon = 0;
        } else {
            if(requireTrackInfo) return -1;
        }
    } else {
        if(requireTrackInfo) return -1;
    }
    return isTightMuon;
}
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
#endif
