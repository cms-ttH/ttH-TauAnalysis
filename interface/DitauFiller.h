// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _DitauFiller_h
#define _DitauFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class DitauFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit DitauFiller(const ParameterSet&);
		explicit DitauFiller(const ParameterSet&, TTree*, BEANhelper*);
		~DitauFiller();
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
		vector<unsigned int>	_Tau1NSignalPiZeros;
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
		vector<float>			_Tau1METCosDeltaPhi;
		vector<float>			_Tau1METMt;

		// === Tau2 === //
		vector<unsigned int>	_Tau2MomentumRank;
		vector<float>			_Tau2Pt;
		vector<float>			_Tau2Eta;
		vector<float>			_Tau2Phi;
		vector<unsigned int>	_Tau2NProngs;
		vector<unsigned int>	_Tau2NSignalGammas;
		vector<unsigned int>	_Tau2NSignalNeutrals;
		vector<unsigned int>	_Tau2NSignalPiZeros;
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
		vector<float>			_Tau2METCosDeltaPhi;
		vector<float>			_Tau2METMt;

		// === Combo === //
		vector<float>			_DitauVisibleMass;
		vector<float>			_DitauMETMass;
		vector<float>			_DitauCosDeltaPhi;
		vector<float>			_DitauDeltaR;
		vector<float>			_HT;
		vector<unsigned int>	_NumCSVLbtags;
		vector<unsigned int>	_NumCSVMbtags;
		vector<unsigned int>	_NumCSVTbtags;
		vector<unsigned int>	_NumCSVLextraJets;
		vector<unsigned int>	_NumCSVMextraJets;
		vector<unsigned int>	_NumCSVTextraJets;
		vector<float>			_DitauMETpZeta;
		vector<float>			_DitauMETpZetaVis;
		
};

#endif
