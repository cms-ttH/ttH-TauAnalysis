#ifndef _fillerAuxFunctions_cc
#define _fillerAuxFunctions_cc

#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"

#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"


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
        if( !(Muon.numberOfMatches() > 1) ) isTightMuon = 0;
        if( !(Muon.numberOfValidHits() > 10) ) isTightMuon = 0;
        if( !(Muon.dB(pat::Muon::PV2D) < 0.02) ) isTightMuon = 0;
        if(Muon.innerTrack().isAvailable() && Muon.innerTrack().isNonnull() ) { 
            if( !(Muon.innerTrack()->hitPattern().pixelLayersWithMeasurement() > 0) ) isTightMuon = 0;
            if( !(Muon.innerTrack()->dz(vertexPosition) < 1) ) isTightMuon = 0;
        } else {
            //std::cout << "  --> no inner track info; returning -1 for muon ID" << std::endl;
            if(requireTrackInfo) return -1;
        }
    } else {
        //std::cout << "  --> no global track info; returning -1 for muon ID" << std::endl;
        if(requireTrackInfo) return -1;
    }
    return isTightMuon;
}
//template <class T> float getLeptonIso(const pat::Lepton<T>& lepton, bool subtractChargedPU = 0, bool doDeltaBeta = 0) {
inline float getMuonIso(const pat::Muon& muon, bool subtractChargedPU = 0, bool doDeltaBeta = 0) {

    float sum = 0;
    if( muon.pfCandidateRef().isNull() ) { // standard muon
        //std::cout << "standard muon" << std::endl;
        sum += muon.isolationR03().sumPt;
        sum += muon.isolationR03().emEt;
        sum += muon.isolationR03().hadEt;
    }
    else { // PF muon
        return -1;
        //std::cout << "PF muon" << std::endl;
        
        //float puChargedHadronIso = muon.puChargedHadronIso(); not present until 4_4_X
        float puChargedHadronIso = 0;

        float chargedHadronIso = muon.chargedHadronIso();
        float neutralHadronIso = muon.neutralHadronIso();
        float photonIso = muon.photonIso();

        float sum = chargedHadronIso + neutralHadronIso + photonIso; 
        if(subtractChargedPU) sum -= puChargedHadronIso; 

        float deltaBetaCorr = 0; //to be implemented
        if(doDeltaBeta) sum -= deltaBetaCorr;
    }

    return sum;
}
inline float getElectronIso(const pat::Electron& electron, bool subtractChargedPU = 0, bool doDeltaBeta = 0) {

    float sum = 0;
    if( electron.pfCandidateRef().isNull() ) { // standard electron
        //std::cout << "standard electron" << std::endl;
        sum += electron.trackIso();
        sum += electron.ecalIso();
        sum += electron.hcalIso();
    }
    else { // PF electron
        return -1;
        //std::cout << "PF electron" << std::endl;
        
        //float puChargedHadronIso = electron.puChargedHadronIso(); not present until 4_4_X
        float puChargedHadronIso = 0;

        float chargedHadronIso = electron.chargedHadronIso();
        float neutralHadronIso = electron.neutralHadronIso();
        float photonIso = electron.photonIso();

        float sum = chargedHadronIso + neutralHadronIso + photonIso; 
        if(subtractChargedPU) sum -= puChargedHadronIso; 

        float deltaBetaCorr = 0; //to be implemented
        if(doDeltaBeta) sum -= deltaBetaCorr;
    }

    return sum;
}
#endif
