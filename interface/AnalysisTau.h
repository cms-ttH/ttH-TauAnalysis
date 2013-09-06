// vim: sta:et:sw=4:ts=4
// Authors: Matthias Wolf <matthias.wolf@cern.ch>

#ifndef __AnalysisTau_h
#define __AnalysisTau_h

#include <string>
#include <vector>

#include "TTree.h"

#include "BEAN/BEANmaker/interface/BEANhelper.h"
#include "BEAN/Collections/interface/BNmcparticle.h"
#include "BEAN/Collections/interface/BNtau.h"

class AnalysisTau {
    public:
        AnalysisTau(const std::string&, TTree*);

        void ClearVectors();
        void Fill(const BNtau&, const BEANhelper*, const BNmcparticleCollection&);

    protected:
        std::vector<int> _MomentumRank;
        std::vector<float> _Pt;
        std::vector<float> _Eta;
        std::vector<float> _Phi;
        std::vector<unsigned int> _NProngs;
        std::vector<unsigned int> _NSignalGammas;
        std::vector<unsigned int> _NSignalNeutrals;
        std::vector<unsigned int> _DecayMode;
        std::vector<float> _EmFraction;
        std::vector<bool> _IsInTheCracks;
        std::vector<bool> _HPSagainstElectronDeadECAL;
        std::vector<bool> _HPSagainstElectronLoose;
        std::vector<bool> _HPSagainstElectronLooseMVA2;
        std::vector<bool> _HPSagainstElectronLooseMVA3;
        std::vector<bool> _HPSagainstElectronMVA;
        std::vector<bool> _HPSagainstElectronMVA2category;
        std::vector<float> _HPSagainstElectronMVA2raw;
        std::vector<bool> _HPSagainstElectronMVA3category;
        std::vector<float> _HPSagainstElectronMVA3raw;
        std::vector<bool> _HPSagainstElectronMedium;
        std::vector<bool> _HPSagainstElectronMediumMVA2;
        std::vector<bool> _HPSagainstElectronMediumMVA3;
        std::vector<bool> _HPSagainstElectronTight;
        std::vector<bool> _HPSagainstElectronTightMVA2;
        std::vector<bool> _HPSagainstElectronTightMVA3;
        std::vector<bool> _HPSagainstElectronVLooseMVA2;
        std::vector<bool> _HPSagainstElectronVTightMVA3;
        std::vector<bool> _HPSagainstMuonLoose;
        std::vector<bool> _HPSagainstMuonLoose2;
        std::vector<bool> _HPSagainstMuonMedium;
        std::vector<bool> _HPSagainstMuonMedium2;
        std::vector<bool> _HPSagainstMuonTight;
        std::vector<bool> _HPSagainstMuonTight2;
        std::vector<float> _HPSbyCombinedIsolationDeltaBetaCorrRaw;
        std::vector<float> _HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits;
        std::vector<float> _HPSbyIsolationMVA2raw;
        std::vector<bool> _HPSbyLooseCombinedIsolationDeltaBetaCorr;
        std::vector<bool> _HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits;
        std::vector<bool> _HPSbyLooseIsolationMVA;
        std::vector<bool> _HPSbyLooseIsolationMVA2;
        std::vector<bool> _HPSbyMediumCombinedIsolationDeltaBetaCorr;
        std::vector<bool> _HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits;
        std::vector<bool> _HPSbyMediumIsolationMVA;
        std::vector<bool> _HPSbyMediumIsolationMVA2;
        std::vector<bool> _HPSbyTightCombinedIsolationDeltaBetaCorr;
        std::vector<bool> _HPSbyTightCombinedIsolationDeltaBetaCorr3Hits;
        std::vector<bool> _HPSbyTightIsolationMVA;
        std::vector<bool> _HPSbyTightIsolationMVA2;
        std::vector<bool> _HPSbyVLooseCombinedIsolationDeltaBetaCorr;
        std::vector<bool> _HPSdecayModeFinding;
        std::vector<float> _HPSbyIsolationMVAraw;
        std::vector<float> _LTPt;
        std::vector<float> _Charge;
        std::vector<bool> _LTvalid;
        std::vector<float> _LTIpVtdxy;
        std::vector<float> _LTIpVtdz;
        std::vector<float> _LTIpVtdxyError;
        std::vector<float> _LTIpVtdzError;
        std::vector<float> _LTvx;
        std::vector<float> _LTvy;
        std::vector<float> _LTvz;
        std::vector<unsigned int> _LTValidHits;
        std::vector<float> _LTNormChiSqrd;
        std::vector<int> _GenMatchDaughter0Id;
        std::vector<int> _GenMatchDaughter1Id;
        std::vector<int> _GenMatchId;
        std::vector<int> _GenMatchMother0Id;
        std::vector<int> _GenMatchMother1Id;
        std::vector<int> _GenMatchGrandmother00Id;
        std::vector<int> _GenMatchGrandmother01Id;
        std::vector<int> _GenMatchGrandmother10Id;
        std::vector<int> _GenMatchGrandmother11Id;
        std::vector<int> _GenMatchDaughter0Status;
        std::vector<int> _GenMatchDaughter1Status;
        std::vector<int> _GenMatchStatus;
        std::vector<int> _GenMatchMother0Status;
        std::vector<int> _GenMatchMother1Status;
        std::vector<int> _GenMatchGrandmother00Status;
        std::vector<int> _GenMatchGrandmother01Status;
        std::vector<int> _GenMatchGrandmother10Status;
        std::vector<int> _GenMatchGrandmother11Status;
};

#endif
