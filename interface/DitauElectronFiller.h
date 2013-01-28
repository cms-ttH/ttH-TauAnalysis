// Authors: Nil Valls

#ifndef _DitauElectronFiller_h
#define _DitauElectronFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class DitauElectronFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit DitauElectronFiller(const ParameterSet&);
		explicit DitauElectronFiller(const ParameterSet&, TTree*, BEANhelper*);
		~DitauElectronFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void analyze(const Event&, const EventSetup&);
		void SetupBranches();
		void ClearVectors();

		// === Helper functions === //
		void FillTau1(const BNtau&);
		void FillTau2(const BNtau&);
		void FillElectron(const BNelectron&);
		void FillDitauElectron(const BNtau&, const BNtau&, const BNelectron&);
		void MatchRecoAndGenHadTausFromH();
		void FindGenTausFromHandW();
		//pat::Tau * FindClosestRecoTau(reco::Candidate::LorentzVector *);

	// ----- Variables ----- //
	private:
		TH1F*				_Plot1;
		TH1F*				_Plot2;
		reco::Candidate::LorentzVector genHadTauFromH1;
		reco::Candidate::LorentzVector genHadTauFromH2;
		reco::Candidate::LorentzVector genHadTauFromW1;
		reco::Candidate::LorentzVector genHadTauFromW2;
		/*pat::Tau *				_recoTauMatchedToGenHadTauFromH1;
		pat::Tau *				_recoTauMatchedToGenHadTauFromH2;
		pat::Tau *				_recoTauMatchedToGenHadTauFromW1;
		pat::Tau *				_recoTauMatchedToGenHadTauFromW2;//*/
		unsigned int			_NumTaus;
		unsigned int			_NumElectrons;
		unsigned int			_NumCombos;
		vector<unsigned int>	_MomentumRank;

		// === Tau1 === //
		vector<unsigned int>	_Tau1MomentumRank;
		vector<float>			_Tau1Pt;
		vector<float>			_Tau1Eta;
		vector<float>			_Tau1Phi;
		vector<unsigned int>	_Tau1NProngs;
		vector<unsigned int>	_Tau1NSignalGammas;
		vector<unsigned int>	_Tau1NSignalNeutrals;
		vector<unsigned int>	_Tau1DecayMode;
		vector<float>			_Tau1EmFraction;
		vector<bool>			_Tau1IsInTheCracks;
		vector<bool>			_Tau1HPSagainstElectronLoose;
		vector<bool>			_Tau1HPSagainstElectronMVA;
		vector<bool>			_Tau1HPSagainstElectronMedium;
		vector<bool>			_Tau1HPSagainstElectronTight;
		vector<bool>			_Tau1HPSagainstMuonLoose;
		vector<bool>			_Tau1HPSagainstMuonMedium;
		vector<bool>			_Tau1HPSagainstMuonTight;
		vector<bool>			_Tau1HPSbyLooseCombinedIsolationDeltaBetaCorr;
		vector<bool>			_Tau1HPSbyMediumCombinedIsolationDeltaBetaCorr;
		vector<bool>			_Tau1HPSbyTightCombinedIsolationDeltaBetaCorr;
		vector<bool>			_Tau1HPSbyVLooseCombinedIsolationDeltaBetaCorr;
		vector<bool>			_Tau1HPSdecayModeFinding;
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
		vector<bool>			_Tau1MatchesGenHadTauFromH1;
		vector<bool>			_Tau1MatchesGenHadTauFromH2;
		vector<bool>			_Tau1MatchesGenHadTauFromW1;
		vector<bool>			_Tau1MatchesGenHadTauFromW2;
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
		vector<unsigned int>	_Tau2MomentumRank;
		vector<float>			_Tau2Pt;
		vector<float>			_Tau2Eta;
		vector<float>			_Tau2Phi;
		vector<unsigned int>	_Tau2NProngs;
		vector<unsigned int>	_Tau2NSignalGammas;
		vector<unsigned int>	_Tau2NSignalNeutrals;
		vector<unsigned int>	_Tau2DecayMode;
		vector<float>			_Tau2EmFraction;
		vector<bool>			_Tau2IsInTheCracks;
		vector<bool>			_Tau2HPSagainstElectronLoose;
		vector<bool>			_Tau2HPSagainstElectronMVA;
		vector<bool>			_Tau2HPSagainstElectronMedium;
		vector<bool>			_Tau2HPSagainstElectronTight;
		vector<bool>			_Tau2HPSagainstMuonLoose;
		vector<bool>			_Tau2HPSagainstMuonMedium;
		vector<bool>			_Tau2HPSagainstMuonTight;
		vector<bool>			_Tau2HPSbyLooseCombinedIsolationDeltaBetaCorr;
		vector<bool>			_Tau2HPSbyMediumCombinedIsolationDeltaBetaCorr;
		vector<bool>			_Tau2HPSbyTightCombinedIsolationDeltaBetaCorr;
		vector<bool>			_Tau2HPSbyVLooseCombinedIsolationDeltaBetaCorr;
		vector<bool>			_Tau2HPSdecayModeFinding;
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
		vector<bool>			_Tau2MatchesGenHadTauFromH1;
		vector<bool>			_Tau2MatchesGenHadTauFromH2;
		vector<bool>			_Tau2MatchesGenHadTauFromW1;
		vector<bool>			_Tau2MatchesGenHadTauFromW2;
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

		// === Electron === //
		vector<unsigned int>	_ElectronMomentumRank;
		vector<float>			_ElectronPt;
		vector<float>			_ElectronEta;
		vector<float>			_ElectronPhi;
		vector<float>			_ElectronRelIso;
		vector<int> 			_ElectronIsLooseElectron;
		vector<int> 			_ElectronIsTightElectron;
		unsigned int			_NumOtherLooseMuons;
		unsigned int			_NumOtherTightMuons;
		vector<unsigned int>	_NumOtherLooseElectrons;
		vector<unsigned int>	_NumOtherTightElectrons;
		vector<float>			_LeptonEventWeight;
		vector<int>				_ElectronGenMatchDaughter0Id;
		vector<int>				_ElectronGenMatchDaughter1Id;
		vector<int>				_ElectronGenMatchId;
		vector<int>				_ElectronGenMatchMother0Id;
		vector<int>				_ElectronGenMatchMother1Id;
		vector<int>				_ElectronGenMatchGrandmother00Id;
		vector<int>				_ElectronGenMatchGrandmother01Id;
		vector<int>				_ElectronGenMatchGrandmother10Id;
		vector<int>				_ElectronGenMatchGrandmother11Id;
		vector<int>				_ElectronGenMatchDaughter0Status;
		vector<int>				_ElectronGenMatchDaughter1Status;
		vector<int>				_ElectronGenMatchStatus;
		vector<int>				_ElectronGenMatchMother0Status;
		vector<int>				_ElectronGenMatchMother1Status;
		vector<int>				_ElectronGenMatchGrandmother00Status;
		vector<int>				_ElectronGenMatchGrandmother01Status;
		vector<int>				_ElectronGenMatchGrandmother10Status;
		vector<int>				_ElectronGenMatchGrandmother11Status;

		// === Combo === //
		vector<float>			_DitauVisibleMass;
		vector<float>			_DitauMETMass;
		vector<float>			_DitauCosDeltaPhi;
		vector<float>			_DitauDeltaR;
		vector<float>			_Tau1ElectronDeltaR;
		vector<float>			_Tau2ElectronDeltaR;
		vector<float>			_HT;
		vector<unsigned int>	_NumCSVLbtagJets;
		vector<unsigned int>	_NumCSVMbtagJets;
		vector<unsigned int>	_NumCSVTbtagJets;
		vector<unsigned int>	_NumNonCSVLbtagJets;
		vector<unsigned int>	_NumNonCSVMbtagJets;
		vector<unsigned int>	_NumNonCSVTbtagJets;
		
};

#endif
