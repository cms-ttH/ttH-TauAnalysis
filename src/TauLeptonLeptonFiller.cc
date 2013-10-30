// vim: sta:et:sw=4:ts=4
// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/TauLeptonLeptonFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
TauLeptonLeptonFiller::TauLeptonLeptonFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

TauLeptonLeptonFiller::TauLeptonLeptonFiller(const ParameterSet& iConfig, TTree* iTree, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper) {
	_FillerName	= __FILE__;
	_Tree = iTree;
	SetupBranches();

    lep1 = new AnalysisLepton("TLL_Lepton1", _Tree);
    lep2 = new AnalysisLepton("TLL_Lepton2", _Tree);
    tau = new AnalysisTau("TLL_Tau", _Tree);
}

// === Destructor === //
TauLeptonLeptonFiller::~TauLeptonLeptonFiller()
{
    delete lep1;
    delete lep2;
    delete tau;
}

// ------------ method called to for each event  ------------
void TauLeptonLeptonFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void TauLeptonLeptonFiller::SetupBranches()
{
	// Set up tree branches
	_Tree->Branch("TLL_NumTaus",&_NumTaus);
	_Tree->Branch("TLL_NumLooseMuons",&_NumLooseMuons);
	_Tree->Branch("TLL_NumExLooseMuons",&_NumExLooseMuons);
	_Tree->Branch("TLL_NumTightMuons",&_NumTightMuons);
	_Tree->Branch("TLL_NumLooseElectrons",&_NumLooseElectrons);
	_Tree->Branch("TLL_NumExLooseElectrons",&_NumExLooseElectrons);
	_Tree->Branch("TLL_NumTightElectrons",&_NumTightElectrons);
	_Tree->Branch("TLL_NumCombos",&_NumCombos);
	_Tree->Branch("TLL_MomentumRank",&_MomentumRank);

    _Tree->Branch("TLL_TauMomentumRank", &_TauMomentumRank);

    // === Combo === //
    _Tree->Branch("TLL_TriggerEventWeight", &_TriggerEventWeight);

    _Tree->Branch("TLL_TauLepton1VisibleMass", &_TauLepton1VisibleMass);
    _Tree->Branch("TLL_TauLepton2VisibleMass", &_TauLepton2VisibleMass);
    _Tree->Branch("TLL_TauLepton1METMass", &_TauLepton1METMass);
    _Tree->Branch("TLL_TauLepton2METMass", &_TauLepton2METMass);
    _Tree->Branch("TLL_Lepton1Lepton2VisibleMass", &_Lepton1Lepton2VisibleMass);
    _Tree->Branch("TLL_TauLepton1CosDeltaPhi", &_TauLepton1CosDeltaPhi);
    _Tree->Branch("TLL_TauLepton2CosDeltaPhi", &_TauLepton2CosDeltaPhi);
    _Tree->Branch("TLL_Lepton1Lepton2CosDeltaPhi", &_Lepton1Lepton2CosDeltaPhi);
    _Tree->Branch("TLL_TauLepton1DeltaR", &_TauLepton1DeltaR);
    _Tree->Branch("TLL_TauLepton2DeltaR", &_TauLepton2DeltaR);
    _Tree->Branch("TLL_Lepton1Lepton2DeltaR", &_Lepton1Lepton2DeltaR);
    _Tree->Branch("TLL_HT", &_HT);
    _Tree->Branch("TLL_NumCSVLbtagJets", &_NumCSVLbtagJets);
    _Tree->Branch("TLL_NumCSVMbtagJets", &_NumCSVMbtagJets);
    _Tree->Branch("TLL_NumCSVTbtagJets", &_NumCSVTbtagJets);
    _Tree->Branch("TLL_NumNonCSVLbtagJets", &_NumNonCSVLbtagJets);
    _Tree->Branch("TLL_NumNonCSVMbtagJets", &_NumNonCSVMbtagJets);
    _Tree->Branch("TLL_NumNonCSVTbtagJets", &_NumNonCSVTbtagJets);
    _Tree->Branch("TLL_NumCleanCSVLbtagJets", &_NumCleanCSVLbtagJets);
    _Tree->Branch("TLL_NumCleanCSVMbtagJets", &_NumCleanCSVMbtagJets);
    _Tree->Branch("TLL_NumCleanCSVTbtagJets", &_NumCleanCSVTbtagJets);
    _Tree->Branch("TLL_NumCleanNonCSVLbtagJets", &_NumCleanNonCSVLbtagJets);
    _Tree->Branch("TLL_NumCleanNonCSVMbtagJets", &_NumCleanNonCSVMbtagJets);
    _Tree->Branch("TLL_NumCleanNonCSVTbtagJets", &_NumCleanNonCSVTbtagJets);
    _Tree->Branch("TLL_CleanJetIndices", &_CleanJetIndices);
    _Tree->Branch("TLL_CleanJetIndices", &_CleanJetIndices);
    _Tree->Branch("TLL_CleanJetCSVMIndices", &_CleanJetCSVMIndices);
    _Tree->Branch("TLL_CleanJetNonCSVMIndices", &_CleanJetNonCSVMIndices);

    // === Weights === //
    _Tree->Branch("TLL_CSVeventWeight", &_CSVeventWeight);
    _Tree->Branch("TLL_CSVeventWeightHFdown", &_CSVeventWeightHFdown);
    _Tree->Branch("TLL_CSVeventWeightHFup", &_CSVeventWeightHFup);
    _Tree->Branch("TLL_CSVeventWeightLFdown", &_CSVeventWeightLFdown);
    _Tree->Branch("TLL_CSVeventWeightLFup", &_CSVeventWeightLFup);
    _Tree->Branch("TLL_CSVeventWeightHFStats1down", &_CSVeventWeightHFStats1down);
    _Tree->Branch("TLL_CSVeventWeightHFStats1up", &_CSVeventWeightHFStats1up);
    _Tree->Branch("TLL_CSVeventWeightLFStats1down", &_CSVeventWeightLFStats1down);
    _Tree->Branch("TLL_CSVeventWeightLFStats1up", &_CSVeventWeightLFStats1up);
    _Tree->Branch("TLL_CSVeventWeightHFStats2down", &_CSVeventWeightHFStats2down);
    _Tree->Branch("TLL_CSVeventWeightHFStats2up", &_CSVeventWeightHFStats2up);
    _Tree->Branch("TLL_CSVeventWeightLFStats2down", &_CSVeventWeightLFStats2down);
    _Tree->Branch("TLL_CSVeventWeightLFStats2up", &_CSVeventWeightLFStats2up);
    _Tree->Branch("TLL_CSVeventWeightCErr1up", &_CSVeventWeightCErr1up);
    _Tree->Branch("TLL_CSVeventWeightCErr1down", &_CSVeventWeightCErr1down);
    _Tree->Branch("TLL_CSVeventWeightCErr2up", &_CSVeventWeightCErr2up);
    _Tree->Branch("TLL_CSVeventWeightCErr2down", &_CSVeventWeightCErr2down);
}

// === Clear vectors that will be used to fill ntuple === //
void TauLeptonLeptonFiller::ClearVectors()
{
    lep1->ClearVectors();
    lep2->ClearVectors();
    tau->ClearVectors();

	_NumTaus										= 0;
	_NumCombos										= 0;	
	_MomentumRank									.clear();
	_TauMomentumRank								.clear();

	// === Lepton === //
	_NumLooseMuons									.clear();
	_NumExLooseMuons								.clear();
	_NumTightMuons									.clear();
	_NumLooseElectrons								.clear();
	_NumExLooseElectrons							.clear();
	_NumTightElectrons								.clear();

    // === Combo === //
    _TriggerEventWeight.clear();

    _TauLepton1VisibleMass.clear();
    _TauLepton2VisibleMass.clear();
    _TauLepton1METMass.clear();
    _TauLepton2METMass.clear();
    _Lepton1Lepton2VisibleMass.clear();
    _TauLepton1CosDeltaPhi.clear();
    _TauLepton2CosDeltaPhi.clear();
    _Lepton1Lepton2CosDeltaPhi.clear();
    _TauLepton1DeltaR.clear();
    _TauLepton2DeltaR.clear();
    _Lepton1Lepton2DeltaR.clear();
    _HT.clear();
    _NumCSVLbtagJets.clear();
    _NumCSVMbtagJets.clear();
    _NumCSVTbtagJets.clear();
    _NumNonCSVLbtagJets.clear();
    _NumNonCSVMbtagJets.clear();
    _NumNonCSVTbtagJets.clear();
    _NumCleanCSVLbtagJets.clear();
    _NumCleanCSVMbtagJets.clear();
    _NumCleanCSVTbtagJets.clear();
    _NumCleanNonCSVLbtagJets.clear();
    _NumCleanNonCSVMbtagJets.clear();
    _NumCleanNonCSVTbtagJets.clear();
    // swap these vectors with empty ones to really release memory
    _CleanJetIndices.clear();
    std::vector< std::vector<unsigned int> >().swap(_CleanJetIndices);
    _CleanJetCSVMIndices.clear();
    std::vector< std::vector<unsigned int> >().swap(_CleanJetCSVMIndices);
    _CleanJetNonCSVMIndices.clear();
    std::vector< std::vector<unsigned int> >().swap(_CleanJetNonCSVMIndices);

    // === Event weights === //
    _CSVeventWeight.clear();
    _CSVeventWeightLFup.clear();
    _CSVeventWeightLFdown.clear();
    _CSVeventWeightHFup.clear();
    _CSVeventWeightHFdown.clear();

    _CSVeventWeightLFStats1up.clear();
    _CSVeventWeightLFStats1down.clear();
    _CSVeventWeightHFStats1up.clear();
    _CSVeventWeightHFStats1down.clear();

    _CSVeventWeightLFStats2up.clear();
    _CSVeventWeightLFStats2down.clear();
    _CSVeventWeightHFStats2up.clear();
    _CSVeventWeightHFStats2down.clear();

    _CSVeventWeightCErr1up.clear();
    _CSVeventWeightCErr1down.clear();
    _CSVeventWeightCErr2up.clear();
    _CSVeventWeightCErr2down.clear();
}

// === Fill ntuple === //
void TauLeptonLeptonFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){

	// Get the object collections from the event
	GetCollections(iEvent, iSetup);

	// Clear vectors
	ClearVectors();

	// Leptons
	BNelectronCollection tightElectrons		= beanHelper->GetSelectedElectrons(_BNelectrons, electronID::electronTight);
	BNmuonCollection tightMuons				= beanHelper->GetSelectedMuons(_BNmuons, muonID::muonTight);
	BNleptonCollection tightLeptons;
	tightLeptons.push_back(tightElectrons);
	tightLeptons.push_back(tightMuons);
	tightLeptons.sort();

	BNelectronCollection looseElectrons		= beanHelper->GetSelectedElectrons(_BNelectrons, electronID::electronLoose);
	BNmuonCollection looseMuons				= beanHelper->GetSelectedMuons(_BNmuons, muonID::muonLoose);
	BNleptonCollection looseLeptons;
	looseLeptons.push_back(looseElectrons);
	looseLeptons.push_back(looseMuons);
	looseLeptons.sort();

	BNelectronCollection exLooseElectrons	= beanHelper->GetDifference(looseElectrons, tightElectrons);
	BNmuonCollection exLooseMuons			= beanHelper->GetDifference(looseMuons, tightMuons);
	BNleptonCollection exLooseLeptons;
	exLooseLeptons.push_back(exLooseElectrons);
	exLooseLeptons.push_back(exLooseMuons);
	exLooseLeptons.sort();

	// Make sure we can at least make one TLL combo
	if(looseLeptons.size() < 2){ return; } // At least two tight or loose leptons
	if(tightLeptons.size() < 1){ return; } // At least one tight lepton

    // Taus  (corrected taus currently just account for systematic shifts)
    BNtauCollection correctedTaus =  beanHelper->GetCorrectedTaus(_BNtaus, _sysType);
	BNtauCollection selectedTaus = beanHelper->GetSelectedTaus(correctedTaus, tauID::tauNonIso);

	// Make sure we can at least make one TLL combo
	if(correctedTaus.size() < 1){ return; } // At least one tau

	// Tau loops: Tau1 is always leads in pT
	unsigned int theNumberOfTaus		= 0;

	// Start loop over Taus so select two (if applicable) that form a good combo
	_NumTaus = selectedTaus.size();
	theNumberOfTaus = 0;
	for ( BNtauCollection::const_iterator Tau = selectedTaus.begin(); Tau != selectedTaus.end(); ++Tau ) {
        theNumberOfTaus++;

        // Clean leptons
        BNleptonCollection cleanLooseLeptons	= GetUnmatchedLeptons(*Tau, looseLeptons,	0.15);
        BNleptonCollection cleanExLooseLeptons	= GetUnmatchedLeptons(*Tau, exLooseLeptons,	0.15);
        BNleptonCollection cleanTightLeptons	= GetUnmatchedLeptons(*Tau, tightLeptons,	0.15);

        // Make sure we can at least make one TLL combo
        if (cleanLooseLeptons.size() != 2)
            continue; // Exactly two tight or loose leptons
        if (cleanTightLeptons.size() < 1)
            continue; // At least one tight lepton

        // Count loose leptons
        unsigned int numLooseElectrons = 0;
        unsigned int numLooseMuons = 0;
        for(BNleptonCollection::const_iterator it = cleanLooseLeptons.begin(); it != cleanLooseLeptons.end(); ++it){
            if ((*it)->isElectron)
                numLooseElectrons++;
            else if ((*it)->isMuon)
                numLooseMuons++;
        }

        // Check if HLT path matches leptons found => for scale factor
        // correctness
        std::set<std::string> triggers;
        for (const auto& trig: _BNtrigger) {
            if (trig.pass) {
                // skip version number, e.g., _v17
                auto pos = trig.name.rfind("_");
                triggers.insert(trig.name.substr(0, pos));
            }
        }

        bool dielectron_triggered = \
                                    triggers.find("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL") != triggers.end();
        bool dimuon_triggered = \
                                triggers.find("HLT_Mu17_Mu8") != triggers.end()
                                || triggers.find("HLT_Mu17_TkMu8") != triggers.end();
        bool mixed_triggered = \
                               triggers.find("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL") != triggers.end()
                               || triggers.find("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL") != triggers.end();
        if (numLooseMuons == 2 && numLooseElectrons == 0) {
            if (!dimuon_triggered) {
                edm::LogWarning("TauLeptonLeptonFiller")
                    << "Two muons but no corresponding trigger path found!" << std::endl
                    << "  HLT Paths: dimuon " << dimuon_triggered
                    << "; dielectron " << dielectron_triggered
                    << "; mixed " << mixed_triggered << std::endl;
                continue;
            }
        } else if (numLooseMuons == 1 && numLooseElectrons == 1) {
            if (!mixed_triggered) {
                edm::LogWarning("TauLeptonLeptonFiller")
                    << "One muon and one electron but no corresponding trigger path found!"
                    << std::endl
                    << "  HLT Paths: dimuon " << dimuon_triggered
                    << "; dielectron " << dielectron_triggered
                    << "; mixed " << mixed_triggered << std::endl;
                continue;
            }
        } else {
            if (!dielectron_triggered) {
                edm::LogWarning("TauLeptonLeptonFiller")
                    << "Two electrons but no corresponding trigger path found!" << std::endl
                    << "  HLT Paths: dimuon " << dimuon_triggered
                    << "; dielectron " << dielectron_triggered
                    << "; mixed " << mixed_triggered << std::endl;
                continue;
            }
        }

        _NumLooseElectrons		.push_back(numLooseElectrons);
        _NumLooseMuons			.push_back(numLooseMuons);

        // Count exLoose leptons
        unsigned int numExLooseElectrons = 0;
        unsigned int numExLooseMuons = 0;
        for(BNleptonCollection::const_iterator it = cleanExLooseLeptons.begin(); it != cleanExLooseLeptons.end(); ++it){
            if((*it)->isElectron){ numExLooseElectrons++; }
            else if((*it)->isMuon){ numExLooseMuons++; }
        }
        _NumExLooseElectrons	.push_back(numExLooseElectrons);
        _NumExLooseMuons		.push_back(numExLooseMuons);

        // Count tight leptons
        unsigned int numTightElectrons = 0;
        unsigned int numTightMuons = 0;
        for(BNleptonCollection::const_iterator it = cleanTightLeptons.begin(); it != cleanTightLeptons.end(); ++it){
            if((*it)->isElectron){ numTightElectrons++; }
            else if((*it)->isMuon){ numTightMuons++; }
        }
        _NumTightElectrons		.push_back(numTightElectrons);//*/
        _NumTightMuons			.push_back(numTightMuons);


        // Get the two leptons in question
        BNlepton* Lepton1 = cleanLooseLeptons.at(0);
        BNlepton* Lepton2 = cleanLooseLeptons.at(1);


        // Jets and MET and related quantities
        // Correct for jet pT
        BNjetCollection correctedJets                           = beanHelper->GetCorrectedJets(_BNjets, _sysType);
        // Apply kinematic requirements on corrected jets
        BNjetCollection selCorrJets                             = beanHelper->GetSelectedJets(correctedJets, 30, 2.4, jetID::jetLoose, '-');
        vector<TLorentzVector> tauAndLeptons; // Clean jets from taus and leptons
        tauAndLeptons.push_back(TLorentzVector(Tau->px, Tau->py, Tau->pz, Tau->energy));
        tauAndLeptons.push_back(TLorentzVector(Lepton1->px, Lepton1->py, Lepton1->pz, Lepton1->energy));
        tauAndLeptons.push_back(TLorentzVector(Lepton2->px, Lepton2->py, Lepton2->pz, Lepton2->energy));

        // Clean jets
        std::vector<unsigned int> jet_indices;
        BNjetCollection cleanSelCorrJets						= beanHelper->GetCleanJets(selCorrJets, tauAndLeptons, 0.25, &jet_indices);
        _CleanJetIndices.push_back(jet_indices);

        // Derive quantities based on the corrected MET based on the clean, corrected, kinematically-selected jets
        BNmet correctedMET  = beanHelper->GetCorrectedMET(*(_BNmets.begin()), beanHelper->GetUncorrectedJets(cleanSelCorrJets, _BNjets), _sysType);

        _HT.push_back(Tau->pt + Lepton1->pt + Lepton2->pt + correctedMET.pt + beanHelper->GetHT(cleanSelCorrJets));

        std::vector<unsigned int> tag_indices;
        std::vector<unsigned int> notag_indices;

        _NumCSVLbtagJets.push_back(beanHelper->GetNumCSVbtags(selCorrJets, 'L'));
        _NumCSVMbtagJets.push_back(beanHelper->GetNumCSVbtags(selCorrJets, 'M'));
        _NumCSVTbtagJets.push_back(beanHelper->GetNumCSVbtags(selCorrJets, 'T'));
        _NumNonCSVLbtagJets.push_back(beanHelper->GetNumNonCSVbtags(selCorrJets, 'L'));
        _NumNonCSVMbtagJets.push_back(beanHelper->GetNumNonCSVbtags(selCorrJets, 'M'));
        _NumNonCSVTbtagJets.push_back(beanHelper->GetNumNonCSVbtags(selCorrJets, 'T'));

        _NumCleanCSVLbtagJets.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'L'));
        _NumCleanCSVMbtagJets.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'M', &tag_indices));
        _NumCleanCSVTbtagJets.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'T'));
        _NumCleanNonCSVLbtagJets.push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'L'));
        _NumCleanNonCSVMbtagJets.push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'M', &notag_indices));
        _NumCleanNonCSVTbtagJets.push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'T'));

        for (auto& idx: tag_indices)
            idx = jet_indices[idx];
        for (auto& idx: notag_indices)
            idx = jet_indices[idx];

        _CleanJetCSVMIndices.push_back(tag_indices);
        _CleanJetNonCSVMIndices.push_back(notag_indices);

        // fill total jet weight with clean jets
        _CSVeventWeight.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, _sysType));

        // CSV weights for systematics
        if (_sysType == sysType::NA) {
            _CSVeventWeightLFup.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVLFup));
            _CSVeventWeightLFdown.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVLFdown));
            _CSVeventWeightHFup.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVHFup));
            _CSVeventWeightHFdown.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVHFdown));

            _CSVeventWeightLFStats1up.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVLFStats1up));
            _CSVeventWeightLFStats1down.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVLFStats1down));
            _CSVeventWeightHFStats1up.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVHFStats1up));
            _CSVeventWeightHFStats1down.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVHFStats1down));

            _CSVeventWeightLFStats2up.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVLFStats2up));
            _CSVeventWeightLFStats2down.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVLFStats2down));
            _CSVeventWeightHFStats2up.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVHFStats2up));
            _CSVeventWeightHFStats2down.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVHFStats2down));

            _CSVeventWeightCErr1up.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVCErr1up));
            _CSVeventWeightCErr1down.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVCErr1down));
            _CSVeventWeightCErr2up.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVCErr2up));
            _CSVeventWeightCErr2down.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVCErr2down));
        }


        // TLL stuff
        _MomentumRank.push_back(_MomentumRank.size());
        _NumCombos++;

        _TauMomentumRank.push_back(theNumberOfTaus-1);

        tau->Fill(*Tau, beanHelper, _BNmcparticles);
        lep1->Fill(Lepton1, beanHelper, _BNmcparticles, correctedMET);
        lep2->Fill(Lepton2, beanHelper, _BNmcparticles, correctedMET);
        FillTauLeptonLepton(beanHelper, *Tau, Lepton1, Lepton2, correctedMET);

	} // End of tau loop

}

void
TauLeptonLeptonFiller::FillTauLeptonLepton(BEANhelper *helper, const BNtau& tau, const BNlepton* lepton1, const BNlepton* lepton2, const BNmet& met)
{
    if (lepton1->isMuon && lepton2->isMuon) {
        _TriggerEventWeight.push_back(helper->GetDoubleMuonTriggerSF(*static_cast<const BNmuon*>(lepton1), *static_cast<const BNmuon*>(lepton2)));
    } else if (lepton1->isElectron && lepton2->isElectron) {
        _TriggerEventWeight.push_back(helper->GetDoubleElectronTriggerSF(*static_cast<const BNelectron*>(lepton1), *static_cast<const BNelectron*>(lepton2)));
    } else {
        if (lepton1->isMuon)
            _TriggerEventWeight.push_back(helper->GetMuonEleTriggerSF(*static_cast<const BNmuon*>(lepton1), *static_cast<const BNelectron*>(lepton2)));
        else
            _TriggerEventWeight.push_back(helper->GetMuonEleTriggerSF(*static_cast<const BNmuon*>(lepton2), *static_cast<const BNelectron*>(lepton1)));
    }

	_TauLepton1VisibleMass.push_back(GetComboMassBN(tau, *lepton1));
	_TauLepton2VisibleMass.push_back(GetComboMassBN(tau, *lepton2));
	_TauLepton1METMass.push_back(GetComboMassBN(tau, *lepton1, met));
	_TauLepton2METMass.push_back(GetComboMassBN(tau, *lepton2, met));
	_Lepton1Lepton2VisibleMass.push_back(GetComboMassBN(*lepton1, *lepton2));
	_TauLepton1CosDeltaPhi.push_back(cos(TMath::Abs(normalizedPhi(tau.phi - lepton1->phi))));
	_TauLepton2CosDeltaPhi.push_back(cos(TMath::Abs(normalizedPhi(tau.phi - lepton2->phi))));
	_Lepton1Lepton2CosDeltaPhi.push_back(cos(TMath::Abs(normalizedPhi(lepton1->phi - lepton2->phi))));
	_TauLepton1DeltaR.push_back(deltaR(tau.eta, tau.phi, lepton1->eta, lepton1->phi));
	_TauLepton2DeltaR.push_back(deltaR(tau.eta, tau.phi, lepton2->eta, lepton2->phi));
	_Lepton1Lepton2DeltaR.push_back(deltaR(lepton1->eta, lepton1->phi, lepton2->eta, lepton2->phi));

}
