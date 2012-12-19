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
		int						_NumTaus;
		vector<float>			_MomentumRank;
		vector<float>			_TauPt;
		vector<float>			_TauEta;
		vector<float>			_TauPhi;
		vector<unsigned int>	_TauNProngs;
		vector<unsigned int>	_TauNSignalGammas;
		vector<unsigned int>	_TauNSignalNeutrals;
		vector<unsigned int>	_TauDecayMode;
		vector<float>			_TauEmFraction;
		vector<bool>			_TauIsInTheCracks;
		vector<bool>			_TauHPSagainstElectronLoose;
		vector<bool>			_TauHPSagainstElectronMVA;
		vector<bool>			_TauHPSagainstElectronMedium;
		vector<bool>			_TauHPSagainstElectronTight;
		vector<bool>			_TauHPSagainstMuonLoose;
		vector<bool>			_TauHPSagainstMuonMedium;
		vector<bool>			_TauHPSagainstMuonTight;
		vector<bool>			_TauHPSbyLooseCombinedIsolationDeltaBetaCorr;
		vector<bool>			_TauHPSbyMediumCombinedIsolationDeltaBetaCorr;
		vector<bool>			_TauHPSbyTightCombinedIsolationDeltaBetaCorr;
		vector<bool>			_TauHPSbyVLooseCombinedIsolationDeltaBetaCorr;
		vector<bool>			_TauHPSdecayModeFinding;
		vector<float>			_TauLTPt;
		vector<float>			_TauCharge;
		vector<bool>			_TauLTvalid;
		vector<float>			_TauLTIpVtdxy;
		vector<float>			_TauLTIpVtdz;
		vector<float>			_TauLTIpVtdxyError;
		vector<float>			_TauLTIpVtdzError;
		vector<float>			_TauLTvx;
		vector<float>			_TauLTvy;
		vector<float>			_TauLTvz;
		vector<unsigned int>	_TauLTValidHits;
		vector<float>			_TauLTNormChiSqrd;
		vector<bool>			_TauMatchesGenHadTauFromH1;
		vector<bool>			_TauMatchesGenHadTauFromH2;
		vector<bool>			_TauMatchesGenHadTauFromW1;
		vector<bool>			_TauMatchesGenHadTauFromW2;
		vector<int>				_TauGenMatchDaughter0Id;
		vector<int>				_TauGenMatchDaughter1Id;
		vector<int>				_TauGenMatchId;
		vector<int>				_TauGenMatchMother0Id;
		vector<int>				_TauGenMatchMother1Id;
		vector<int>				_TauGenMatchGrandmother00Id;
		vector<int>				_TauGenMatchGrandmother01Id;
		vector<int>				_TauGenMatchGrandmother10Id;
		vector<int>				_TauGenMatchGrandmother11Id;
		vector<int>				_TauGenMatchDaughter0Status;
		vector<int>				_TauGenMatchDaughter1Status;
		vector<int>				_TauGenMatchStatus;
		vector<int>				_TauGenMatchMother0Status;
		vector<int>				_TauGenMatchMother1Status;
		vector<int>				_TauGenMatchGrandmother00Status;
		vector<int>				_TauGenMatchGrandmother01Status;
		vector<int>				_TauGenMatchGrandmother10Status;
		vector<int>				_TauGenMatchGrandmother11Status;
		
};

#endif
