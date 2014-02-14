// vim: sta:et:sw=4:ts=4
// Authors: Nil Valls, Matthias Wolf

#ifndef _TauLeptonFiller_h
#define _TauLeptonFiller_h

#include "AnalysisLepton.h"
#include "AnalysisTau.h"
#include "NtupleFiller.h"

using namespace std;

class TauLeptonFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit TauLeptonFiller(const ParameterSet&);
		explicit TauLeptonFiller(const ParameterSet&, TTree*, BEANhelper*);
		~TauLeptonFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void analyze(const Event&, const EventSetup&);
		void SetupBranches();
		void ClearVectors();

	// ----- Variables ----- //
	private:
        AnalysisLepton* lep;
        AnalysisTau* tau;

		unsigned int			_NumTaus;
		unsigned int			_NumCombos;
		vector<int>				_MomentumRank;

        vector<int> _TauMomentumRank;

		// === Lepton === //
		vector<unsigned int>	_NumLooseMuons;
		vector<unsigned int>	_NumExLooseMuons;
		vector<unsigned int>	_NumTightMuons;
		vector<unsigned int>	_NumLooseElectrons;
		vector<unsigned int>	_NumExLooseElectrons;
		vector<unsigned int>	_NumTightElectrons;

        // === Combo === //
        vector<float> _TriggerEventWeight;

        vector<vector<float>> _jet_deltaR_tau;
        vector<vector<float>> _jet_deltaR_lepton;

        vector<float> _TauLeptonVisibleMass;
        vector<float> _TauLeptonMETMass;
        vector<float> _TauLeptonCosDeltaPhi;
        vector<float> _TauLeptonDeltaR;
        vector<float> _HT;
        vector<float> _MHT;
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
