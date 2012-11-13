// Authors: Nil Valls, Jeff Kolb

#ifndef _MuTauMuonFiller_h
#define _MuTauMuonFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class MuTauMuonFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit MuTauMuonFiller(const ParameterSet&);
		explicit MuTauMuonFiller(const ParameterSet&, TTree*, BEANhelper*);
		~MuTauMuonFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void analyze(const Event&, const EventSetup&);
		void SetupBranches();
		void ClearVectors();

		// === Helper functions === //

	// ----- Variables ----- //
	private:
		unsigned int			_NumTaus;
		unsigned int			_NumMuons;
		unsigned int			_NumCombos;
		vector<unsigned int>	_MomentumRank;

		// === Tau === //
		vector<unsigned int>	_TauMomentumRank;
		vector<float>			_TauPt;
		vector<float>			_TauEta;
		vector<float>			_TauPhi;
		vector<unsigned int>	_TauNProngs;
		vector<unsigned int>	_TauNSignalGammas;
		vector<unsigned int>	_TauNSignalNeutrals;
		vector<unsigned int>	_TauNSignalPiZeros;
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


		// === Muon1 === //
		vector<unsigned int>	_Muon1MomentumRank;
		vector<float>			_Muon1Pt;
		vector<float>			_Muon1Eta;
		vector<float>			_Muon1Phi;
		vector<float>			_Muon1PfIso;
		vector<int> 			_Muon1IsLooseMuon;
		vector<int> 			_Muon1IsTightMuon;

		// === Muon2 === //
		vector<unsigned int>	_Muon2MomentumRank;
		vector<float>			_Muon2Pt;
		vector<float>			_Muon2Eta;
		vector<float>			_Muon2Phi;
		vector<float>			_Muon2PfIso;
		vector<int> 			_Muon2IsLooseMuon;
		vector<int> 			_Muon2IsTightMuon;

		// === Combo === //
		vector<float>			_MuTauVisibleMass;
		vector<float>			_MuTauMETMass;
		vector<float>			_MuTauCosDeltaPhi;
		vector<float>			_MuTauDeltaR;
		vector<float>			_TauMuon1DeltaR;
		vector<float>			_TauMuon2DeltaR;
		vector<float>			_HT;
		vector<unsigned int>	_NumCSVLbtags;
		vector<unsigned int>	_NumCSVMbtags;
		vector<unsigned int>	_NumCSVTbtags;
		vector<unsigned int>	_NumCSVLextraJets;
		vector<unsigned int>	_NumCSVMextraJets;
		vector<unsigned int>	_NumCSVTextraJets;
		
};

#endif
