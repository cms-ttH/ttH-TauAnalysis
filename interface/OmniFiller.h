// vim: sta:et:sw=4:ts=4
// Authors: Nil Valls

#ifndef _OmniFiller_h
#define _OmniFiller_h

#include "AnalysisObjects.h"
#include "NtupleFiller.h"

class OmniFiller : public NtupleFiller {
    // ----- Functions ----- //
    public:
        explicit OmniFiller(const ParameterSet&, TTree*, BEANhelper*);
        ~OmniFiller();
        virtual bool FillNtuple(const Event&, const EventSetup&);

    private:
        // === Core functions === //
        void analyze(const Event&, const EventSetup&);
        void SetupBranches();
        void ClearVectors();

        // ----- Variables ----- //
        unsigned int required_leptons;
        unsigned int required_taus;

        std::vector<AnalysisLepton*> tree_leptons;
        std::vector<AnalysisTau*> tree_taus;
        AnalysisJets tree_jets;
        AnalysisObject tree_met;

        std::map<int, std::map<int, std::vector<std::string>>> required_triggers;

        unsigned int _NumTaus;
        unsigned int _NumCombos;
        vector<int> _MomentumRank;

        // === Lepton === //
        vector<unsigned int> _NumLooseMuons;
        vector<unsigned int> _NumExLooseMuons;
        vector<unsigned int> _NumTightMuons;
        vector<unsigned int> _NumLooseElectrons;
        vector<unsigned int> _NumExLooseElectrons;
        vector<unsigned int> _NumTightElectrons;

        // === Combo === //
        vector<float> _TriggerEventWeight;
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

