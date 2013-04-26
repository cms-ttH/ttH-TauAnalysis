// Authors: Nil Valls

#ifndef _DitauLeptonFiller_h
#define _DitauLeptonFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class DitauLeptonFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit DitauLeptonFiller(const ParameterSet&);
		explicit DitauLeptonFiller(const ParameterSet&, TTree*, BEANhelper*);
		~DitauLeptonFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void analyze(const Event&, const EventSetup&);
		void SetupBranches();
		void ClearVectors();

		// === Helper functions === //
		void FillTau1(const BNtau&);
		void FillTau2(const BNtau&);
		void FillMuon(const BNmuon&);
		void FillElectron(const BNelectron&);
		void FillDitauLepton(const BNtau&, const BNtau&, const BNmuon&);
		void FillDitauLepton(const BNtau&, const BNtau&, const BNelectron&);

	// ----- Variables ----- //
	private:
		unsigned int			_NumTaus;
		unsigned int			_NumLeptons;
		unsigned int			_NumMuons;
		unsigned int			_NumElectrons;
		unsigned int			_NumCombos;
		vector<int>				_MomentumRank;

		// === Tau1 === //
		vector<int>				_Tau1MomentumRank;
		vector<float>			_Tau1Pt;
		vector<float>			_Tau1Eta;
		vector<float>			_Tau1Phi;
		vector<unsigned int>	_Tau1NProngs;
		vector<unsigned int>	_Tau1NSignalGammas;
		vector<unsigned int>	_Tau1NSignalNeutrals;
		vector<unsigned int>	_Tau1DecayMode;
		vector<float>			_Tau1EmFraction;
		vector<bool>			_Tau1IsInTheCracks;
		vector<bool>                _Tau1HPSagainstElectronDeadECAL;
		vector<bool>                _Tau1HPSagainstElectronLoose;
		vector<bool>                _Tau1HPSagainstElectronLooseMVA2;
		vector<bool>                _Tau1HPSagainstElectronLooseMVA3;
		vector<bool>                _Tau1HPSagainstElectronMVA;
		vector<bool>                _Tau1HPSagainstElectronMVA2category;
		vector<float>               _Tau1HPSagainstElectronMVA2raw;
		vector<bool>                _Tau1HPSagainstElectronMVA3category;
		vector<float>               _Tau1HPSagainstElectronMVA3raw;
		vector<bool>                _Tau1HPSagainstElectronMedium;
		vector<bool>                _Tau1HPSagainstElectronMediumMVA2;
		vector<bool>                _Tau1HPSagainstElectronMediumMVA3;
		vector<bool>                _Tau1HPSagainstElectronTight;
		vector<bool>                _Tau1HPSagainstElectronTightMVA2;
		vector<bool>                _Tau1HPSagainstElectronTightMVA3;
		vector<bool>                _Tau1HPSagainstElectronVLooseMVA2;
		vector<bool>                _Tau1HPSagainstElectronVTightMVA3;
		vector<bool>                _Tau1HPSagainstMuonLoose;
		vector<bool>                _Tau1HPSagainstMuonLoose2;
		vector<bool>                _Tau1HPSagainstMuonMedium;
		vector<bool>                _Tau1HPSagainstMuonMedium2;
		vector<bool>                _Tau1HPSagainstMuonTight;
		vector<bool>                _Tau1HPSagainstMuonTight2;
		vector<float>               _Tau1HPSbyCombinedIsolationDeltaBetaCorrRaw;
		vector<float>               _Tau1HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits;
		vector<float>               _Tau1HPSbyIsolationMVA2raw;
		vector<bool>                _Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr;
		vector<bool>                _Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits;
		vector<bool>                _Tau1HPSbyLooseIsolationMVA;
		vector<bool>                _Tau1HPSbyLooseIsolationMVA2;
		vector<bool>                _Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr;
		vector<bool>                _Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits;
		vector<bool>                _Tau1HPSbyMediumIsolationMVA;
		vector<bool>                _Tau1HPSbyMediumIsolationMVA2;
		vector<bool>                _Tau1HPSbyTightCombinedIsolationDeltaBetaCorr;
		vector<bool>                _Tau1HPSbyTightCombinedIsolationDeltaBetaCorr3Hits;
		vector<bool>                _Tau1HPSbyTightIsolationMVA;
		vector<bool>                _Tau1HPSbyTightIsolationMVA2;
		vector<bool>                _Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr;
		vector<bool>                _Tau1HPSdecayModeFinding;
		vector<float>               _Tau1HPSbyIsolationMVAraw;
		vector<float>			_Tau1LTPt;
		vector<float>			_Tau1Charge;
		vector<bool>			_Tau1LTvalid;
		vector<float>			_Tau1LTIpVtdxy;
		vector<float>			_Tau1LTIpVtdz;
		vector<float>			_Tau1LTIpVtdxyError;
		vector<float>			_Tau1LTIpVtdzError;
		vector<float>			_Tau1LTvx;
		vector<float>			_Tau1LTvy;
		vector<float>			_Tau1LTvz;
		vector<unsigned int>	_Tau1LTValidHits;
		vector<float>			_Tau1LTNormChiSqrd;
		vector<int>				_Tau1GenMatchDaughter0Id;
		vector<int>				_Tau1GenMatchDaughter1Id;
		vector<int>				_Tau1GenMatchId;
		vector<int>				_Tau1GenMatchMother0Id;
		vector<int>				_Tau1GenMatchMother1Id;
		vector<int>				_Tau1GenMatchGrandmother00Id;
		vector<int>				_Tau1GenMatchGrandmother01Id;
		vector<int>				_Tau1GenMatchGrandmother10Id;
		vector<int>				_Tau1GenMatchGrandmother11Id;
		vector<int>				_Tau1GenMatchDaughter0Status;
		vector<int>				_Tau1GenMatchDaughter1Status;
		vector<int>				_Tau1GenMatchStatus;
		vector<int>				_Tau1GenMatchMother0Status;
		vector<int>				_Tau1GenMatchMother1Status;
		vector<int>				_Tau1GenMatchGrandmother00Status;
		vector<int>				_Tau1GenMatchGrandmother01Status;
		vector<int>				_Tau1GenMatchGrandmother10Status;
		vector<int>				_Tau1GenMatchGrandmother11Status;

		// === Tau2 === //
		vector<int>				_Tau2MomentumRank;
		vector<float>			_Tau2Pt;
		vector<float>			_Tau2Eta;
		vector<float>			_Tau2Phi;
		vector<unsigned int>	_Tau2NProngs;
		vector<unsigned int>	_Tau2NSignalGammas;
		vector<unsigned int>	_Tau2NSignalNeutrals;
		vector<unsigned int>	_Tau2DecayMode;
		vector<float>			_Tau2EmFraction;
		vector<bool>			_Tau2IsInTheCracks;
		vector<bool>                _Tau2HPSagainstElectronDeadECAL;
		vector<bool>                _Tau2HPSagainstElectronLoose;
		vector<bool>                _Tau2HPSagainstElectronLooseMVA2;
		vector<bool>                _Tau2HPSagainstElectronLooseMVA3;
		vector<bool>                _Tau2HPSagainstElectronMVA;
		vector<bool>                _Tau2HPSagainstElectronMVA2category;
		vector<float>               _Tau2HPSagainstElectronMVA2raw;
		vector<bool>                _Tau2HPSagainstElectronMVA3category;
		vector<float>               _Tau2HPSagainstElectronMVA3raw;
		vector<bool>                _Tau2HPSagainstElectronMedium;
		vector<bool>                _Tau2HPSagainstElectronMediumMVA2;
		vector<bool>                _Tau2HPSagainstElectronMediumMVA3;
		vector<bool>                _Tau2HPSagainstElectronTight;
		vector<bool>                _Tau2HPSagainstElectronTightMVA2;
		vector<bool>                _Tau2HPSagainstElectronTightMVA3;
		vector<bool>                _Tau2HPSagainstElectronVLooseMVA2;
		vector<bool>                _Tau2HPSagainstElectronVTightMVA3;
		vector<bool>                _Tau2HPSagainstMuonLoose;
		vector<bool>                _Tau2HPSagainstMuonLoose2;
		vector<bool>                _Tau2HPSagainstMuonMedium;
		vector<bool>                _Tau2HPSagainstMuonMedium2;
		vector<bool>                _Tau2HPSagainstMuonTight;
		vector<bool>                _Tau2HPSagainstMuonTight2;
		vector<float>               _Tau2HPSbyCombinedIsolationDeltaBetaCorrRaw;
		vector<float>               _Tau2HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits;
		vector<float>               _Tau2HPSbyIsolationMVA2raw;
		vector<bool>                _Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr;
		vector<bool>                _Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits;
		vector<bool>                _Tau2HPSbyLooseIsolationMVA;
		vector<bool>                _Tau2HPSbyLooseIsolationMVA2;
		vector<bool>                _Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr;
		vector<bool>                _Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits;
		vector<bool>                _Tau2HPSbyMediumIsolationMVA;
		vector<bool>                _Tau2HPSbyMediumIsolationMVA2;
		vector<bool>                _Tau2HPSbyTightCombinedIsolationDeltaBetaCorr;
		vector<bool>                _Tau2HPSbyTightCombinedIsolationDeltaBetaCorr3Hits;
		vector<bool>                _Tau2HPSbyTightIsolationMVA;
		vector<bool>                _Tau2HPSbyTightIsolationMVA2;
		vector<bool>                _Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr;
		vector<bool>                _Tau2HPSdecayModeFinding;
		vector<float>               _Tau2HPSbyIsolationMVAraw;
		vector<float>			_Tau2LTPt;
		vector<float>			_Tau2Charge;
		vector<bool>			_Tau2LTvalid;
		vector<float>			_Tau2LTIpVtdxy;
		vector<float>			_Tau2LTIpVtdz;
		vector<float>			_Tau2LTIpVtdxyError;
		vector<float>			_Tau2LTIpVtdzError;
		vector<float>			_Tau2LTvx;
		vector<float>			_Tau2LTvy;
		vector<float>			_Tau2LTvz;
		vector<unsigned int>	_Tau2LTValidHits;
		vector<float>			_Tau2LTNormChiSqrd;
		vector<int>				_Tau2GenMatchDaughter0Id;
		vector<int>				_Tau2GenMatchDaughter1Id;
		vector<int>				_Tau2GenMatchId;
		vector<int>				_Tau2GenMatchMother0Id;
		vector<int>				_Tau2GenMatchMother1Id;
		vector<int>				_Tau2GenMatchGrandmother00Id;
		vector<int>				_Tau2GenMatchGrandmother01Id;
		vector<int>				_Tau2GenMatchGrandmother10Id;
		vector<int>				_Tau2GenMatchGrandmother11Id;
		vector<int>				_Tau2GenMatchDaughter0Status;
		vector<int>				_Tau2GenMatchDaughter1Status;
		vector<int>				_Tau2GenMatchStatus;
		vector<int>				_Tau2GenMatchMother0Status;
		vector<int>				_Tau2GenMatchMother1Status;
		vector<int>				_Tau2GenMatchGrandmother00Status;
		vector<int>				_Tau2GenMatchGrandmother01Status;
		vector<int>				_Tau2GenMatchGrandmother10Status;
		vector<int>				_Tau2GenMatchGrandmother11Status;

		// === Lepton === //
		vector<unsigned int>	_NumLooseMuons;
		vector<unsigned int>	_NumExLooseMuons;
		vector<unsigned int>	_NumTightMuons;
		vector<unsigned int>	_NumLooseElectrons;
		vector<unsigned int>	_NumExLooseElectrons;
		vector<unsigned int>	_NumTightElectrons;
		vector<int>				_LeptonMomentumRank;
		vector<int>				_MuonMomentumRank;
		vector<int>				_ElectronMomentumRank;
		vector<float>			_LeptonIsMuon;
		vector<float>			_LeptonIsElectron;
		vector<float>			_LeptonPt;
		vector<float>			_LeptonEta;
		vector<float>			_LeptonPhi;
		vector<float>			_LeptonRelIso;
		vector<bool> 			_LeptonIsLoose;
		vector<bool> 			_LeptonIsTight;
		vector<float>			_LeptonEventWeight;
		vector<int>				_LeptonGenMatchDaughter0Id;
		vector<int>				_LeptonGenMatchDaughter1Id;
		vector<int>				_LeptonGenMatchId;
		vector<int>				_LeptonGenMatchMother0Id;
		vector<int>				_LeptonGenMatchMother1Id;
		vector<int>				_LeptonGenMatchGrandmother00Id;
		vector<int>				_LeptonGenMatchGrandmother01Id;
		vector<int>				_LeptonGenMatchGrandmother10Id;
		vector<int>				_LeptonGenMatchGrandmother11Id;
		vector<int>				_LeptonGenMatchDaughter0Status;
		vector<int>				_LeptonGenMatchDaughter1Status;
		vector<int>				_LeptonGenMatchStatus;
		vector<int>				_LeptonGenMatchMother0Status;
		vector<int>				_LeptonGenMatchMother1Status;
		vector<int>				_LeptonGenMatchGrandmother00Status;
		vector<int>				_LeptonGenMatchGrandmother01Status;
		vector<int>				_LeptonGenMatchGrandmother10Status;
		vector<int>				_LeptonGenMatchGrandmother11Status;

		// === Combo === //
		vector<float>			_DitauVisibleMass;
		vector<float>			_DitauMETMass;
		vector<float>			_DitauCosDeltaPhi;
		vector<float>			_DitauDeltaR;
		vector<float>			_Tau1LeptonDeltaR;
		vector<float>			_Tau2LeptonDeltaR;
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
		vector<float>	_TotalJetWeight;
		
};

#endif
