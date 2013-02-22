// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _TauFiller_h
#define _TauFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class TauFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit TauFiller(const ParameterSet&);
		explicit TauFiller(const ParameterSet&, TTree*, BEANhelper*);
		~TauFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void SetupBranches();
		void ClearVectors();

	// ----- Variables ----- //
	private:
		int                  _NumTaus;
		vector<float>        _MomentumRank;
		vector<float>        _TauPt;
		vector<float>        _TauEta;
		vector<float>        _TauPhi;
		vector<unsigned int> _TauNProngs;
		vector<unsigned int> _TauNSignalGammas;
		vector<unsigned int> _TauNSignalNeutrals;
		vector<unsigned int> _TauDecayMode;
		vector<float>        _TauEmFraction;
		vector<bool>         _TauIsInTheCracks;
		vector<bool>         _TauHPSagainstElectronDeadECAL;
		vector<bool>         _TauHPSagainstElectronLoose;
		vector<bool>         _TauHPSagainstElectronLooseMVA2;
		vector<bool>         _TauHPSagainstElectronLooseMVA3;
		vector<bool>         _TauHPSagainstElectronMVA;
		vector<bool>         _TauHPSagainstElectronMVA2category;
		vector<float>        _TauHPSagainstElectronMVA2raw;
		vector<bool>         _TauHPSagainstElectronMVA3category;
		vector<float>        _TauHPSagainstElectronMVA3raw;
		vector<bool>         _TauHPSagainstElectronMedium;
		vector<bool>         _TauHPSagainstElectronMediumMVA2;
		vector<bool>         _TauHPSagainstElectronMediumMVA3;
		vector<bool>         _TauHPSagainstElectronTight;
		vector<bool>         _TauHPSagainstElectronTightMVA2;
		vector<bool>         _TauHPSagainstElectronTightMVA3;
		vector<bool>         _TauHPSagainstElectronVLooseMVA2;
		vector<bool>         _TauHPSagainstElectronVTightMVA3;
		vector<bool>         _TauHPSagainstMuonLoose;
		vector<bool>         _TauHPSagainstMuonLoose2;
		vector<bool>         _TauHPSagainstMuonMedium;
		vector<bool>         _TauHPSagainstMuonMedium2;
		vector<bool>         _TauHPSagainstMuonTight;
		vector<bool>         _TauHPSagainstMuonTight2;
		vector<float>        _TauHPSbyCombinedIsolationDeltaBetaCorrRaw;
		vector<float>        _TauHPSbyCombinedIsolationDeltaBetaCorrRaw3Hits;
		vector<float>        _TauHPSbyIsolationMVA2raw;
		vector<bool>         _TauHPSbyLooseCombinedIsolationDeltaBetaCorr;
		vector<bool>         _TauHPSbyLooseCombinedIsolationDeltaBetaCorr3Hits;
		vector<bool>         _TauHPSbyLooseIsolationMVA;
		vector<bool>         _TauHPSbyLooseIsolationMVA2;
		vector<bool>         _TauHPSbyMediumCombinedIsolationDeltaBetaCorr;
		vector<bool>         _TauHPSbyMediumCombinedIsolationDeltaBetaCorr3Hits;
		vector<bool>         _TauHPSbyMediumIsolationMVA;
		vector<bool>         _TauHPSbyMediumIsolationMVA2;
		vector<bool>         _TauHPSbyTightCombinedIsolationDeltaBetaCorr;
		vector<bool>         _TauHPSbyTightCombinedIsolationDeltaBetaCorr3Hits;
		vector<bool>         _TauHPSbyTightIsolationMVA;
		vector<bool>         _TauHPSbyTightIsolationMVA2;
		vector<bool>         _TauHPSbyVLooseCombinedIsolationDeltaBetaCorr;
		vector<bool>         _TauHPSdecayModeFinding;
		vector<float>        _TauHPSbyIsolationMVAraw;
		vector<float>        _TauLTPt;
		vector<float>        _TauCharge;
		vector<bool>         _TauLTvalid;
		vector<float>        _TauLTIpVtdxy;
		vector<float>        _TauLTIpVtdz;
		vector<float>        _TauLTIpVtdxyError;
		vector<float>        _TauLTIpVtdzError;
		vector<float>        _TauLTvx;
		vector<float>        _TauLTvy;
		vector<float>        _TauLTvz;
		vector<unsigned int> _TauLTValidHits;
		vector<float>        _TauLTNormChiSqrd;
		vector<bool>         _TauMatchesGenHadTauFromH1;
		vector<bool>         _TauMatchesGenHadTauFromH2;
		vector<bool>         _TauMatchesGenHadTauFromW1;
		vector<bool>         _TauMatchesGenHadTauFromW2;
		vector<int>          _TauGenMatchDaughter0Id;
		vector<int>          _TauGenMatchDaughter1Id;
		vector<int>          _TauGenMatchId;
		vector<int>          _TauGenMatchMother0Id;
		vector<int>          _TauGenMatchMother1Id;
		vector<int>          _TauGenMatchGrandmother00Id;
		vector<int>          _TauGenMatchGrandmother01Id;
		vector<int>          _TauGenMatchGrandmother10Id;
		vector<int>          _TauGenMatchGrandmother11Id;
		vector<int>          _TauGenMatchDaughter0Status;
		vector<int>          _TauGenMatchDaughter1Status;
		vector<int>          _TauGenMatchStatus;
		vector<int>          _TauGenMatchMother0Status;
		vector<int>          _TauGenMatchMother1Status;
		vector<int>          _TauGenMatchGrandmother00Status;
		vector<int>          _TauGenMatchGrandmother01Status;
		vector<int>          _TauGenMatchGrandmother10Status;
		vector<int>          _TauGenMatchGrandmother11Status;
		
};

#endif
