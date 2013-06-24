// Authors: Nil Valls

#ifndef _TauLeptonLeptonFiller_h
#define _TauLeptonLeptonFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class TauLeptonLeptonFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit TauLeptonLeptonFiller(const ParameterSet&);
		explicit TauLeptonLeptonFiller(const ParameterSet&, TTree*, BEANhelper*);
		~TauLeptonLeptonFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void analyze(const Event&, const EventSetup&);
		void SetupBranches();
		void ClearVectors();

		// === Helper functions === //
		void FillTau(const BNtau&);
		void FillLepton1(const BNlepton*);
		void FillLepton2(const BNlepton*);
		void FillTauLeptonLepton(const BNtau&, const BNlepton*, const BNlepton*, const BNmet&);

	// ----- Variables ----- //
	private:
		unsigned int			_NumTaus;
		unsigned int			_NumCombos;
		vector<int>				_MomentumRank;

		// === Tau1 === //
		vector<int>				_TauMomentumRank;
		vector<float>			_TauPt;
		vector<float>			_TauEta;
		vector<float>			_TauPhi;
		vector<unsigned int>	_TauNProngs;
		vector<unsigned int>	_TauNSignalGammas;
		vector<unsigned int>	_TauNSignalNeutrals;
		vector<unsigned int>	_TauDecayMode;
		vector<float>			_TauEmFraction;
		vector<bool>			_TauIsInTheCracks;
		vector<bool>            _TauHPSagainstElectronDeadECAL;
		vector<bool>            _TauHPSagainstElectronLoose;
		vector<bool>            _TauHPSagainstElectronLooseMVA2;
		vector<bool>            _TauHPSagainstElectronLooseMVA3;
		vector<bool>            _TauHPSagainstElectronMVA;
		vector<bool>            _TauHPSagainstElectronMVA2category;
		vector<float>           _TauHPSagainstElectronMVA2raw;
		vector<bool>            _TauHPSagainstElectronMVA3category;
		vector<float>           _TauHPSagainstElectronMVA3raw;
		vector<bool>            _TauHPSagainstElectronMedium;
		vector<bool>            _TauHPSagainstElectronMediumMVA2;
		vector<bool>            _TauHPSagainstElectronMediumMVA3;
		vector<bool>            _TauHPSagainstElectronTight;
		vector<bool>            _TauHPSagainstElectronTightMVA2;
		vector<bool>            _TauHPSagainstElectronTightMVA3;
		vector<bool>            _TauHPSagainstElectronVLooseMVA2;
		vector<bool>            _TauHPSagainstElectronVTightMVA3;
		vector<bool>            _TauHPSagainstMuonLoose;
		vector<bool>            _TauHPSagainstMuonLoose2;
		vector<bool>            _TauHPSagainstMuonMedium;
		vector<bool>            _TauHPSagainstMuonMedium2;
		vector<bool>            _TauHPSagainstMuonTight;
		vector<bool>            _TauHPSagainstMuonTight2;
		vector<float>           _TauHPSbyCombinedIsolationDeltaBetaCorrRaw;
		vector<float>           _TauHPSbyCombinedIsolationDeltaBetaCorrRaw3Hits;
		vector<float>           _TauHPSbyIsolationMVA2raw;
		vector<bool>            _TauHPSbyLooseCombinedIsolationDeltaBetaCorr;
		vector<bool>            _TauHPSbyLooseCombinedIsolationDeltaBetaCorr3Hits;
		vector<bool>            _TauHPSbyLooseIsolationMVA;
		vector<bool>            _TauHPSbyLooseIsolationMVA2;
		vector<bool>            _TauHPSbyMediumCombinedIsolationDeltaBetaCorr;
		vector<bool>            _TauHPSbyMediumCombinedIsolationDeltaBetaCorr3Hits;
		vector<bool>            _TauHPSbyMediumIsolationMVA;
		vector<bool>            _TauHPSbyMediumIsolationMVA2;
		vector<bool>            _TauHPSbyTightCombinedIsolationDeltaBetaCorr;
		vector<bool>            _TauHPSbyTightCombinedIsolationDeltaBetaCorr3Hits;
		vector<bool>            _TauHPSbyTightIsolationMVA;
		vector<bool>            _TauHPSbyTightIsolationMVA2;
		vector<bool>            _TauHPSbyVLooseCombinedIsolationDeltaBetaCorr;
		vector<bool>            _TauHPSdecayModeFinding;
		vector<float>           _TauHPSbyIsolationMVAraw;
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

		// === Lepton === //
		vector<unsigned int>	_NumLooseMuons;
		vector<unsigned int>	_NumExLooseMuons;
		vector<unsigned int>	_NumTightMuons;
		vector<unsigned int>	_NumLooseElectrons;
		vector<unsigned int>	_NumExLooseElectrons;
		vector<unsigned int>	_NumTightElectrons;
		vector<float>			_Lepton1IsMuon;
		vector<float>			_Lepton1IsElectron;
		vector<float>			_Lepton1Pt;
		vector<float>			_Lepton1Eta;
		vector<float>			_Lepton1Phi;
		vector<float>			_Lepton1RelIso;
		vector<bool> 			_Lepton1IsLoose;
		vector<bool> 			_Lepton1IsTight;
		vector<float>			_Lepton1EventWeight;
		vector<int>				_Lepton1GenMatchDaughter0Id;
		vector<int>				_Lepton1GenMatchDaughter1Id;
		vector<int>				_Lepton1GenMatchId;
		vector<int>				_Lepton1GenMatchMother0Id;
		vector<int>				_Lepton1GenMatchMother1Id;
		vector<int>				_Lepton1GenMatchGrandmother00Id;
		vector<int>				_Lepton1GenMatchGrandmother01Id;
		vector<int>				_Lepton1GenMatchGrandmother10Id;
		vector<int>				_Lepton1GenMatchGrandmother11Id;
		vector<int>				_Lepton1GenMatchDaughter0Status;
		vector<int>				_Lepton1GenMatchDaughter1Status;
		vector<int>				_Lepton1GenMatchStatus;
		vector<int>				_Lepton1GenMatchMother0Status;
		vector<int>				_Lepton1GenMatchMother1Status;
		vector<int>				_Lepton1GenMatchGrandmother00Status;
		vector<int>				_Lepton1GenMatchGrandmother01Status;
		vector<int>				_Lepton1GenMatchGrandmother10Status;
		vector<int>				_Lepton1GenMatchGrandmother11Status;

		vector<float>			_Lepton2IsMuon;
		vector<float>			_Lepton2IsElectron;
		vector<float>			_Lepton2Pt;
		vector<float>			_Lepton2Eta;
		vector<float>			_Lepton2Phi;
		vector<float>			_Lepton2RelIso;
		vector<bool> 			_Lepton2IsLoose;
		vector<bool> 			_Lepton2IsTight;
		vector<float>			_Lepton2EventWeight;
		vector<int>				_Lepton2GenMatchDaughter0Id;
		vector<int>				_Lepton2GenMatchDaughter1Id;
		vector<int>				_Lepton2GenMatchId;
		vector<int>				_Lepton2GenMatchMother0Id;
		vector<int>				_Lepton2GenMatchMother1Id;
		vector<int>				_Lepton2GenMatchGrandmother00Id;
		vector<int>				_Lepton2GenMatchGrandmother01Id;
		vector<int>				_Lepton2GenMatchGrandmother10Id;
		vector<int>				_Lepton2GenMatchGrandmother11Id;
		vector<int>				_Lepton2GenMatchDaughter0Status;
		vector<int>				_Lepton2GenMatchDaughter1Status;
		vector<int>				_Lepton2GenMatchStatus;
		vector<int>				_Lepton2GenMatchMother0Status;
		vector<int>				_Lepton2GenMatchMother1Status;
		vector<int>				_Lepton2GenMatchGrandmother00Status;
		vector<int>				_Lepton2GenMatchGrandmother01Status;
		vector<int>				_Lepton2GenMatchGrandmother10Status;
		vector<int>				_Lepton2GenMatchGrandmother11Status;

		// === Combo === //
		vector<float>			_TauLepton1VisibleMass;
		vector<float>			_TauLepton2VisibleMass;
		vector<float>			_TauLepton1METMass;
		vector<float>			_TauLepton2METMass;
		vector<float>			_Lepton1Lepton2VisibleMass;
		vector<float>			_TauLepton1CosDeltaPhi;
		vector<float>			_TauLepton2CosDeltaPhi;
		vector<float>			_Lepton1Lepton2CosDeltaPhi;
		vector<float>			_TauLepton1DeltaR;
		vector<float>			_TauLepton2DeltaR;
		vector<float>			_Lepton1Lepton2DeltaR;
		vector<float>			_HT;
		vector<unsigned int>	_NumCSVLbtagJets;
		vector<unsigned int>	_NumCSVMbtagJets;
		vector<unsigned int>	_NumCSVTbtagJets;
		vector<unsigned int>	_NumNonCSVLbtagJets;
		vector<unsigned int>	_NumNonCSVMbtagJets;
		vector<unsigned int>	_NumNonCSVTbtagJets;
		vector<unsigned int>	_NumCleanCSVLbtagJets;
		vector<unsigned int>	_NumCleanCSVMbtagJets;
		vector<unsigned int>	_NumCleanCSVTbtagJets;
		vector<unsigned int>	_NumCleanNonCSVLbtagJets;
		vector<unsigned int>	_NumCleanNonCSVMbtagJets;
		vector<unsigned int>	_NumCleanNonCSVTbtagJets;

        vector<float>	        _CSVeventWeight;
        vector<float>	        _CSVeventWeightLFup;
        vector<float>	        _CSVeventWeightLFdown;
        vector<float>	        _CSVeventWeightHFup;
        vector<float>	        _CSVeventWeightHFdown;
        vector<float>	        _CSVeventWeightLFStats1up;
        vector<float>	        _CSVeventWeightLFStats1down;
        vector<float>	        _CSVeventWeightHFStats1up;
        vector<float>	        _CSVeventWeightHFStats1down;
        vector<float>	        _CSVeventWeightLFStats2up;
        vector<float>	        _CSVeventWeightLFStats2down;
        vector<float>	        _CSVeventWeightHFStats2up;
        vector<float>	        _CSVeventWeightHFStats2down;
		
};

#endif
