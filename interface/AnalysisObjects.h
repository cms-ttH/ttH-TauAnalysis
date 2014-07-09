// vim: sta:et:sw=4:ts=4
// Authors: Matthias Wolf <matthias.wolf@cern.ch>

#ifndef __AnalysisObjects_h
#define __AnalysisObjects_h

#include <string>
#include <vector>

#include "Math/LorentzVector.h"
#include "TTree.h"

#include "BEAN/BEANmaker/interface/BEANhelper.h"
#include "BEAN/Collections/interface/BNjet.h"
#include "BEAN/Collections/interface/BNlepton.h"
#include "BEAN/Collections/interface/BNmcparticle.h"
#include "BEAN/Collections/interface/BNtau.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector;

template<typename T> LorentzVector p4(const T&);
template<> LorentzVector p4(const BNmet&);

class AnalysisObject {
    public:
        AnalysisObject(const std::string&, TTree*);

        void ClearVectors();
        template<typename T> void Fill(const T&);

    protected:
        std::vector<LorentzVector> _p;
};

class AnalysisJets {
    public:
        AnalysisJets(TTree*);

        void ClearVectors();
        void Fill(const BNjetCollection&, BEANhelper*, const BNmcparticleCollection&);

    protected:
        vector<int> _NumJets;
        vector<vector<float>> _MomentumRank;
        vector<vector<LorentzVector>> _p;
        vector<vector<float>> _JetCharge;
        vector<vector<int>> _JetPartonId;
        vector<vector<int>> _JetPartonParentId;
        vector<vector<int>> _JetPartonMother0Id;
        vector<vector<int>> _JetPartonMother1Id;
        vector<vector<int>> _JetPartonGrandParentId;
        vector<vector<int>> _JetPartonGrandmother00Id;
        vector<vector<int>> _JetPartonGrandmother01Id;
        vector<vector<int>> _JetPartonGrandmother10Id;
        vector<vector<int>> _JetPartonGrandmother11Id;
        vector<vector<int>> _JetPartonStatus;
        vector<vector<int>> _JetPartonMother0Status;
        vector<vector<int>> _JetPartonMother1Status;
        vector<vector<int>> _JetPartonGrandmother00Status;
        vector<vector<int>> _JetPartonGrandmother01Status;
        vector<vector<int>> _JetPartonGrandmother10Status;
        vector<vector<int>> _JetPartonGrandmother11Status;
        vector<vector<float>> _combSecVtxBTag;
        vector<vector<bool>> _combSecVtxLooseBTag;
        vector<vector<bool>> _combSecVtxMediumBTag;
        vector<vector<bool>> _combSecVtxTightBTag;
};

class AnalysisLepton : AnalysisObject {
    public:
        AnalysisLepton(const std::string&, TTree*);

        void ClearVectors();
        void Fill(const BNlepton*, BEANhelper*, const BNmcparticleCollection&);

    protected:
        vector<float> _IsMuon;
        vector<float> _IsElectron;
        vector<float> _Charge;
        vector<float> _RelIso;
        vector<float> _CorrectedD0;
        vector<float> _CorrectedDZ;
        vector<float> _ImpactParameter;
        vector<bool> _IsLoose;
        vector<bool> _IsTight;
        vector<int> _GenMatchDaughter0Id;
        vector<int> _GenMatchDaughter1Id;
        vector<int> _GenMatchId;
        vector<int> _GenMatchMother0Id;
        vector<int> _GenMatchMother1Id;
        vector<int> _GenMatchGrandmother00Id;
        vector<int> _GenMatchGrandmother01Id;
        vector<int> _GenMatchGrandmother10Id;
        vector<int> _GenMatchGrandmother11Id;
        vector<int> _GenMatchDaughter0Status;
        vector<int> _GenMatchDaughter1Status;
        vector<int> _GenMatchStatus;
        vector<int> _GenMatchMother0Status;
        vector<int> _GenMatchMother1Status;
        vector<int> _GenMatchGrandmother00Status;
        vector<int> _GenMatchGrandmother01Status;
        vector<int> _GenMatchGrandmother10Status;
        vector<int> _GenMatchGrandmother11Status;
        vector<float> _EventWeight;
};

class AnalysisTau : AnalysisObject{
    public:
        AnalysisTau(const std::string&, TTree*);

        void ClearVectors();
        void Fill(const BNtau&, const BEANhelper*, const BNjetCollection&, const BNmcparticleCollection&);

    protected:
        std::vector<int> _MomentumRank;
        std::vector<unsigned int> _NProngs;
        std::vector<unsigned int> _NSignalGammas;
        std::vector<unsigned int> _NSignalNeutrals;
        std::vector<unsigned int> _DecayMode;
        std::vector<float> _EmFraction;
        std::vector<bool> _IsInTheCracks;

        std::vector<float> _jet_csv;

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

template<typename T>
LorentzVector
p4(const T& obj)
{
    return LorentzVector(obj.px, obj.py, obj.pz, obj.energy);
}

template<typename T>
void
AnalysisObject::Fill(const T& obj)
{
    _p.push_back(p4(obj));
}

#endif
