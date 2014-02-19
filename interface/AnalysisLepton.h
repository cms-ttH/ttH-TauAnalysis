// vim: sta:et:sw=4:ts=4
// Authors: Matthias Wolf <matthias.wolf@cern.ch>

#ifndef __AnalysisLepton_h
#define __AnalysisLepton_h

#include <string>
#include <vector>

#include "Math/LorentzVector.h"
#include "TTree.h"

#include "BEAN/BEANmaker/interface/BEANhelper.h"
#include "BEAN/Collections/interface/BNmcparticle.h"
#include "BEAN/Collections/interface/BNlepton.h"

class AnalysisLepton {
    public:
        typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector;

        AnalysisLepton(const std::string&, TTree*);

        void ClearVectors();
        void Fill(const BNlepton*, BEANhelper*, const BNmcparticleCollection&, const BNmet&, const TLorentzVector&);

    protected:
        vector<float> _IsMuon;
        vector<float> _IsElectron;
        vector<float> _Charge;
        std::vector<LorentzVector> _p;
        vector<float> _Pt;
        vector<float> _Eta;
        vector<float> _Phi;
        vector<float> _mt;
        vector<float> _mt2;
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

#endif
