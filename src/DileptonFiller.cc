// vim: sta:et:sw=4:ts=4
// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/DileptonFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
DileptonFiller::DileptonFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

DileptonFiller::DileptonFiller(const ParameterSet& iConfig, TTree* iTree, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper) {
	_FillerName	= __FILE__;
	_Tree = iTree;
	SetupBranches();

    lep1 = new AnalysisLepton("LL_Lepton1", _Tree);
    lep2 = new AnalysisLepton("LL_Lepton2", _Tree);
    tau = new AnalysisTau("LL_Tau", _Tree);
}

// === Destructor === //
DileptonFiller::~DileptonFiller()
{
    delete lep1;
    delete lep2;
    delete tau;
}

// ------------ method called to for each event  ------------
void DileptonFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void DileptonFiller::SetupBranches()
{
	// Set up tree branches
	_Tree->Branch("LL_NumTaus",&_NumTaus);
	_Tree->Branch("LL_NumLooseMuons",&_NumLooseMuons);
	_Tree->Branch("LL_NumExLooseMuons",&_NumExLooseMuons);
	_Tree->Branch("LL_NumTightMuons",&_NumTightMuons);
	_Tree->Branch("LL_NumLooseElectrons",&_NumLooseElectrons);
	_Tree->Branch("LL_NumExLooseElectrons",&_NumExLooseElectrons);
	_Tree->Branch("LL_NumTightElectrons",&_NumTightElectrons);
	_Tree->Branch("LL_NumCombos",&_NumCombos);
	_Tree->Branch("LL_MomentumRank",&_MomentumRank);

    _Tree->Branch("LL_TauMomentumRank", &_TauMomentumRank);
    _Tree->Branch("LL_PassZMask", &_zmask);
    _Tree->Branch("LL_PassZMask2", &_zmask2);

    // === Combo === //
    _Tree->Branch("LL_TriggerEventWeight", &_TriggerEventWeight);

    _Tree->Branch("J_Lepton1DeltaR", &_jet_deltaR_lepton1);
    _Tree->Branch("J_Lepton2DeltaR", &_jet_deltaR_lepton2);

    _Tree->Branch("LL_TauLepton1VisibleMass", &_TauLepton1VisibleMass);
    _Tree->Branch("LL_TauLepton2VisibleMass", &_TauLepton2VisibleMass);
    _Tree->Branch("LL_TauLepton1METMass", &_TauLepton1METMass);
    _Tree->Branch("LL_TauLepton2METMass", &_TauLepton2METMass);
    _Tree->Branch("LL_Lepton1Lepton2VisibleMass", &_Lepton1Lepton2VisibleMass);
    _Tree->Branch("LL_TauLepton1CosDeltaPhi", &_TauLepton1CosDeltaPhi);
    _Tree->Branch("LL_TauLepton2CosDeltaPhi", &_TauLepton2CosDeltaPhi);
    _Tree->Branch("LL_Lepton1Lepton2CosDeltaPhi", &_Lepton1Lepton2CosDeltaPhi);
    _Tree->Branch("LL_TauLepton1DeltaR", &_TauLepton1DeltaR);
    _Tree->Branch("LL_TauLepton2DeltaR", &_TauLepton2DeltaR);
    _Tree->Branch("LL_Lepton1Lepton2DeltaR", &_Lepton1Lepton2DeltaR);
    _Tree->Branch("LL_HT", &_HT);
    _Tree->Branch("LL_MHT", &_MHT);
    _Tree->Branch("LL_NumCSVLbtagJets", &_NumCSVLbtagJets);
    _Tree->Branch("LL_NumCSVMbtagJets", &_NumCSVMbtagJets);
    _Tree->Branch("LL_NumCSVTbtagJets", &_NumCSVTbtagJets);
    _Tree->Branch("LL_NumNonCSVLbtagJets", &_NumNonCSVLbtagJets);
    _Tree->Branch("LL_NumNonCSVMbtagJets", &_NumNonCSVMbtagJets);
    _Tree->Branch("LL_NumNonCSVTbtagJets", &_NumNonCSVTbtagJets);
    _Tree->Branch("LL_NumCleanCSVLbtagJets", &_NumCleanCSVLbtagJets);
    _Tree->Branch("LL_NumCleanCSVMbtagJets", &_NumCleanCSVMbtagJets);
    _Tree->Branch("LL_NumCleanCSVTbtagJets", &_NumCleanCSVTbtagJets);
    _Tree->Branch("LL_NumCleanNonCSVLbtagJets", &_NumCleanNonCSVLbtagJets);
    _Tree->Branch("LL_NumCleanNonCSVMbtagJets", &_NumCleanNonCSVMbtagJets);
    _Tree->Branch("LL_NumCleanNonCSVTbtagJets", &_NumCleanNonCSVTbtagJets);
    _Tree->Branch("LL_CleanJetIndices", &_CleanJetIndices);
    _Tree->Branch("LL_CleanJetIndices", &_CleanJetIndices);
    _Tree->Branch("LL_CleanJetCSVMIndices", &_CleanJetCSVMIndices);
    _Tree->Branch("LL_CleanJetNonCSVMIndices", &_CleanJetNonCSVMIndices);

    // === Weights === //
    _Tree->Branch("LL_CSVeventWeight", &_CSVeventWeight);
    _Tree->Branch("LL_CSVeventWeightHFdown", &_CSVeventWeightHFdown);
    _Tree->Branch("LL_CSVeventWeightHFup", &_CSVeventWeightHFup);
    _Tree->Branch("LL_CSVeventWeightLFdown", &_CSVeventWeightLFdown);
    _Tree->Branch("LL_CSVeventWeightLFup", &_CSVeventWeightLFup);
    _Tree->Branch("LL_CSVeventWeightHFStats1down", &_CSVeventWeightHFStats1down);
    _Tree->Branch("LL_CSVeventWeightHFStats1up", &_CSVeventWeightHFStats1up);
    _Tree->Branch("LL_CSVeventWeightLFStats1down", &_CSVeventWeightLFStats1down);
    _Tree->Branch("LL_CSVeventWeightLFStats1up", &_CSVeventWeightLFStats1up);
    _Tree->Branch("LL_CSVeventWeightHFStats2down", &_CSVeventWeightHFStats2down);
    _Tree->Branch("LL_CSVeventWeightHFStats2up", &_CSVeventWeightHFStats2up);
    _Tree->Branch("LL_CSVeventWeightLFStats2down", &_CSVeventWeightLFStats2down);
    _Tree->Branch("LL_CSVeventWeightLFStats2up", &_CSVeventWeightLFStats2up);
    _Tree->Branch("LL_CSVeventWeightCErr1up", &_CSVeventWeightCErr1up);
    _Tree->Branch("LL_CSVeventWeightCErr1down", &_CSVeventWeightCErr1down);
    _Tree->Branch("LL_CSVeventWeightCErr2up", &_CSVeventWeightCErr2up);
    _Tree->Branch("LL_CSVeventWeightCErr2down", &_CSVeventWeightCErr2down);
}

// === Clear vectors that will be used to fill ntuple === //
void DileptonFiller::ClearVectors()
{
    lep1->ClearVectors();
    lep2->ClearVectors();
    tau->ClearVectors();

    _jet_deltaR_lepton1.clear();
    _jet_deltaR_lepton2.clear();

	_NumTaus										= 0;
	_NumCombos										= 0;	
	_MomentumRank									.clear();
	_TauMomentumRank								.clear();
    _zmask.clear();
    _zmask2.clear();

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
    _MHT.clear();
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
void DileptonFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){

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

    // Make sure we can at least make one TLL combo
    if (looseLeptons.size() != 2)
        return; // Exactly two tight or loose leptons
    if (tightLeptons.size() < 1)
        return; // At least one tight lepton

    // Count loose leptons
    unsigned int numLooseElectrons = 0;
    unsigned int numLooseMuons = 0;
    for(BNleptonCollection::const_iterator it = looseLeptons.begin(); it != looseLeptons.end(); ++it){
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
            edm::LogWarning("DileptonFiller")
                << "Two muons but no corresponding trigger path found!" << std::endl
                << "  HLT Paths: dimuon " << dimuon_triggered
                << "; dielectron " << dielectron_triggered
                << "; mixed " << mixed_triggered << std::endl;
            return;
        }
    } else if (numLooseMuons == 1 && numLooseElectrons == 1) {
        if (!mixed_triggered) {
            edm::LogWarning("DileptonFiller")
                << "One muon and one electron but no corresponding trigger path found!"
                << std::endl
                << "  HLT Paths: dimuon " << dimuon_triggered
                << "; dielectron " << dielectron_triggered
                << "; mixed " << mixed_triggered << std::endl;
            return;
        }
    } else {
        if (!dielectron_triggered) {
            edm::LogWarning("DileptonFiller")
                << "Two electrons but no corresponding trigger path found!" << std::endl
                << "  HLT Paths: dimuon " << dimuon_triggered
                << "; dielectron " << dielectron_triggered
                << "; mixed " << mixed_triggered << std::endl;
            return;
        }
    }

    _NumCombos = 1;

    _NumLooseElectrons		.push_back(numLooseElectrons);
    _NumLooseMuons			.push_back(numLooseMuons);

    // Count exLoose leptons
    unsigned int numExLooseElectrons = 0;
    unsigned int numExLooseMuons = 0;
    for(BNleptonCollection::const_iterator it = exLooseLeptons.begin(); it != exLooseLeptons.end(); ++it){
        if((*it)->isElectron){ numExLooseElectrons++; }
        else if((*it)->isMuon){ numExLooseMuons++; }
    }
    _NumExLooseElectrons	.push_back(numExLooseElectrons);
    _NumExLooseMuons		.push_back(numExLooseMuons);

    // Count tight leptons
    unsigned int numTightElectrons = 0;
    unsigned int numTightMuons = 0;
    for(BNleptonCollection::const_iterator it = tightLeptons.begin(); it != tightLeptons.end(); ++it){
        if((*it)->isElectron){ numTightElectrons++; }
        else if((*it)->isMuon){ numTightMuons++; }
    }
    _NumTightElectrons		.push_back(numTightElectrons);//*/
    _NumTightMuons			.push_back(numTightMuons);


    // Get the two leptons in question
    BNlepton* Lepton1 = looseLeptons.at(0);
    BNlepton* Lepton2 = looseLeptons.at(1);


    // Jets and MET and related quantities
    // Correct for jet pT
    BNjetCollection correctedJets                           = beanHelper->GetCorrectedJets(_BNjets, _sysType);
    // Apply kinematic requirements on corrected jets
    BNjetCollection selCorrJets                             = beanHelper->GetSelectedJets(correctedJets, 30, 2.4, jetID::jetLoose, '-');
    vector<TLorentzVector> tauAndLeptons; // Clean jets from taus and leptons

    // Clean jets
    std::vector<unsigned int> jet_indices;
    BNjetCollection cleanSelCorrJets = beanHelper->GetCleanJets(selCorrJets, tauAndLeptons, 0.25, &jet_indices);
    _CleanJetIndices.push_back(jet_indices);

    // Derive quantities based on the corrected MET based on the clean, corrected, kinematically-selected jets
    BNmet correctedMET  = beanHelper->GetCorrectedMET(*(_BNmets.begin()), beanHelper->GetUncorrectedJets(cleanSelCorrJets, _BNjets), _sysType);

    _HT.push_back(Lepton1->pt + Lepton2->pt + correctedMET.pt + beanHelper->GetHT(cleanSelCorrJets));

    TLorentzVector vlep1(Lepton1->px, Lepton1->py, Lepton1->pz, Lepton1->energy);
    TLorentzVector vlep2(Lepton2->px, Lepton2->py, Lepton2->pz, Lepton2->energy);
    TLorentzVector vsum = vlep1 + vlep2;

    for (const auto& j: cleanSelCorrJets)
        vsum += TLorentzVector(j.px, j.py, j.pz, j.energy);

    double mht = vsum.Pt();
    _MHT.push_back(mht);

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
    lep1->Fill(Lepton1, beanHelper, _BNmcparticles, correctedMET, -vsum);
    lep2->Fill(Lepton2, beanHelper, _BNmcparticles, correctedMET, -vsum);

    auto lepton1 = Lepton1;
    auto lepton2 = Lepton2;
    auto helper = beanHelper;
    auto met = correctedMET;

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

    for (const auto& jet: selCorrJets) {
        _jet_deltaR_lepton1.push_back(deltaR(jet.eta, jet.phi, lepton1->eta, lepton1->phi));
        _jet_deltaR_lepton2.push_back(deltaR(jet.eta, jet.phi, lepton2->eta, lepton2->phi));
    }

    double dil_vismass = GetComboMassBN(*lepton1, *lepton2);
    bool pass_zmask = \
                      (dil_vismass < (65.5 + 3 * mht / 8)) ||
                      (dil_vismass > (108 - mht / 4)) ||
                      (dil_vismass < (79 - 3 * mht / 4)) ||
                      (dil_vismass > (99 + mht / 2));
    _zmask.push_back(pass_zmask);

    bool pass_zmask2 = \
                      (dil_vismass < (65.5 + 3 * met.pt / 8)) ||
                      (dil_vismass > (108 - met.pt / 4)) ||
                      (dil_vismass < (79 - 3 * met.pt / 4)) ||
                      (dil_vismass > (99 + met.pt / 2));
    _zmask2.push_back(pass_zmask2);

    _Lepton1Lepton2VisibleMass.push_back(dil_vismass);
    _Lepton1Lepton2CosDeltaPhi.push_back(cos(TMath::Abs(normalizedPhi(lepton1->phi - lepton2->phi))));
    _Lepton1Lepton2DeltaR.push_back(deltaR(lepton1->eta, lepton1->phi, lepton2->eta, lepton2->phi));
}
