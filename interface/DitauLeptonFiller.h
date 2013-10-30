// vim: sta:et:sw=4:ts=4
// Authors: Nil Valls

#ifndef _DitauLeptonFiller_h
#define _DitauLeptonFiller_h

#include "AnalysisLepton.h"
#include "AnalysisTau.h"
#include "NtupleFiller.h"

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
        AnalysisLepton *lep;
        AnalysisTau *tau1;
        AnalysisTau *tau2;
		unsigned int			_NumTaus;
		unsigned int			_NumLeptons;
		unsigned int			_NumMuons;
		unsigned int			_NumElectrons;
		unsigned int			_NumCombos;
		vector<int>				_MomentumRank;

		// === Tau1 === //
		vector<int>				_Tau1MomentumRank;

		// === Tau2 === //
		vector<int>				_Tau2MomentumRank;

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

        // === Combo === //
        vector<float> _DitauVisibleMass;
        vector<float> _DitauMETMass;
        vector<float> _DitauCosDeltaPhi;
        vector<float> _DitauDeltaR;
        vector<float> _Tau1LeptonDeltaR;
        vector<float> _Tau2LeptonDeltaR;
        vector<float> _HT;
        vector<unsigned int> _NumCSVLbtagJets;
        vector<unsigned int> _NumCSVMbtagJets;
        vector<unsigned int> _NumCSVTbtagJets;
        vector<unsigned int> _NumNonCSVLbtagJets;
        vector<unsigned int> _NumNonCSVMbtagJets;
        vector<unsigned int> _NumNonCSVTbtagJets;
        vector<unsigned int> _NumCleanCSVLbtagJets;
        vector<unsigned int> _NumCleanCSVMbtagJets;
        vector<unsigned int> _NumCleanCSVTbtagJets;
        vector<unsigned int> _NumCleanNonCSVLbtagJets;
        vector<unsigned int> _NumCleanNonCSVMbtagJets;
        vector<unsigned int> _NumCleanNonCSVTbtagJets;
        vector< vector<unsigned int> > _CleanJetIndices;
        vector< vector<unsigned int> > _CleanJetCSVMIndices;
        vector< vector<unsigned int> > _CleanJetNonCSVMIndices;

        vector<float> _CSVeventWeight;
        vector<float> _CSVeventWeightLFup;
        vector<float> _CSVeventWeightLFdown;
        vector<float> _CSVeventWeightHFup;
        vector<float> _CSVeventWeightHFdown;
        vector<float> _CSVeventWeightLFStats1up;
        vector<float> _CSVeventWeightLFStats1down;
        vector<float> _CSVeventWeightHFStats1up;
        vector<float> _CSVeventWeightHFStats1down;
        vector<float> _CSVeventWeightLFStats2up;
        vector<float> _CSVeventWeightLFStats2down;
        vector<float> _CSVeventWeightHFStats2up;
        vector<float> _CSVeventWeightHFStats2down;
        vector<float> _CSVeventWeightCErr1up;
        vector<float> _CSVeventWeightCErr1down;
        vector<float> _CSVeventWeightCErr2up;
        vector<float> _CSVeventWeightCErr2down;
};

#endif
