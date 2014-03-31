// vim: sta:et:sw=4:ts=4
// Author: Nil Valls <nvallsve@nd.edu>, Matthias Wolf <matthias.wolf@cern.ch>

#include "../interface/TauLeptonFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
TauLeptonFiller::TauLeptonFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

TauLeptonFiller::TauLeptonFiller(const ParameterSet& iConfig, TTree* iTree, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper) {
	_FillerName	= __FILE__;
	_Tree = iTree;
	SetupBranches();

    lep = new AnalysisLepton("TL_Lepton", _Tree);
    tau = new AnalysisTau("TL_Tau", _Tree);
}

// === Destructor === //
TauLeptonFiller::~TauLeptonFiller()
{
    delete lep;
    delete tau;
}

// ------------ method called to for each event  ------------
void TauLeptonFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void TauLeptonFiller::SetupBranches()
{
	// Set up tree branches
	_Tree->Branch("TL_NumTaus",&_NumTaus);
	_Tree->Branch("TL_NumLooseMuons",&_NumLooseMuons);
	_Tree->Branch("TL_NumExLooseMuons",&_NumExLooseMuons);
	_Tree->Branch("TL_NumTightMuons",&_NumTightMuons);
	_Tree->Branch("TL_NumLooseElectrons",&_NumLooseElectrons);
	_Tree->Branch("TL_NumExLooseElectrons",&_NumExLooseElectrons);
	_Tree->Branch("TL_NumTightElectrons",&_NumTightElectrons);
	_Tree->Branch("TL_NumCombos",&_NumCombos);
	_Tree->Branch("TL_MomentumRank",&_MomentumRank);

    _Tree->Branch("TL_TauMomentumRank", &_TauMomentumRank);

    // === Combo === //
    _Tree->Branch("TL_TriggerEventWeight", &_TriggerEventWeight);

    _Tree->Branch("J_TauDeltaR", &_jet_deltaR_tau);
    _Tree->Branch("J_LeptonDeltaR", &_jet_deltaR_lepton);

    _Tree->Branch("TL_TauLeptonVisibleMass", &_TauLeptonVisibleMass);
    _Tree->Branch("TL_TauLeptonMETMass", &_TauLeptonMETMass);
    _Tree->Branch("TL_TauLeptonCosDeltaPhi", &_TauLeptonCosDeltaPhi);
    _Tree->Branch("TL_TauLeptonDeltaR", &_TauLeptonDeltaR);
    _Tree->Branch("TL_HT", &_HT);
    _Tree->Branch("TL_MHT", &_MHT);
    _Tree->Branch("TL_NumCSVLbtagJets", &_NumCSVLbtagJets);
    _Tree->Branch("TL_NumCSVMbtagJets", &_NumCSVMbtagJets);
    _Tree->Branch("TL_NumCSVTbtagJets", &_NumCSVTbtagJets);
    _Tree->Branch("TL_NumNonCSVLbtagJets", &_NumNonCSVLbtagJets);
    _Tree->Branch("TL_NumNonCSVMbtagJets", &_NumNonCSVMbtagJets);
    _Tree->Branch("TL_NumNonCSVTbtagJets", &_NumNonCSVTbtagJets);
    _Tree->Branch("TL_NumCleanCSVLbtagJets", &_NumCleanCSVLbtagJets);
    _Tree->Branch("TL_NumCleanCSVMbtagJets", &_NumCleanCSVMbtagJets);
    _Tree->Branch("TL_NumCleanCSVTbtagJets", &_NumCleanCSVTbtagJets);
    _Tree->Branch("TL_NumCleanNonCSVLbtagJets", &_NumCleanNonCSVLbtagJets);
    _Tree->Branch("TL_NumCleanNonCSVMbtagJets", &_NumCleanNonCSVMbtagJets);
    _Tree->Branch("TL_NumCleanNonCSVTbtagJets", &_NumCleanNonCSVTbtagJets);
    _Tree->Branch("TL_CleanJetIndices", &_CleanJetIndices);
    _Tree->Branch("TL_CleanJetCSVMIndices", &_CleanJetCSVMIndices);
    _Tree->Branch("TL_CleanJetNonCSVMIndices", &_CleanJetNonCSVMIndices);

    // === Weights === //
    _Tree->Branch("TL_CSVeventWeight", &_CSVeventWeight);
    _Tree->Branch("TL_CSVeventWeightHFdown", &_CSVeventWeightHFdown);
    _Tree->Branch("TL_CSVeventWeightHFup", &_CSVeventWeightHFup);
    _Tree->Branch("TL_CSVeventWeightLFdown", &_CSVeventWeightLFdown);
    _Tree->Branch("TL_CSVeventWeightLFup", &_CSVeventWeightLFup);
    _Tree->Branch("TL_CSVeventWeightHFStats1down", &_CSVeventWeightHFStats1down);
    _Tree->Branch("TL_CSVeventWeightHFStats1up", &_CSVeventWeightHFStats1up);
    _Tree->Branch("TL_CSVeventWeightLFStats1down", &_CSVeventWeightLFStats1down);
    _Tree->Branch("TL_CSVeventWeightLFStats1up", &_CSVeventWeightLFStats1up);
    _Tree->Branch("TL_CSVeventWeightHFStats2down", &_CSVeventWeightHFStats2down);
    _Tree->Branch("TL_CSVeventWeightHFStats2up", &_CSVeventWeightHFStats2up);
    _Tree->Branch("TL_CSVeventWeightLFStats2down", &_CSVeventWeightLFStats2down);
    _Tree->Branch("TL_CSVeventWeightLFStats2up", &_CSVeventWeightLFStats2up);
    _Tree->Branch("TL_CSVeventWeightCErr1up", &_CSVeventWeightCErr1up);
    _Tree->Branch("TL_CSVeventWeightCErr1down", &_CSVeventWeightCErr1down);
    _Tree->Branch("TL_CSVeventWeightCErr2up", &_CSVeventWeightCErr2up);
    _Tree->Branch("TL_CSVeventWeightCErr2down", &_CSVeventWeightCErr2down);
}

// === Clear vectors that will be used to fill ntuple === //
void TauLeptonFiller::ClearVectors()
{
    lep->ClearVectors();
    tau->ClearVectors();

    _jet_deltaR_tau.clear();
    _jet_deltaR_lepton.clear();

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

    _TauLeptonVisibleMass.clear();
    _TauLeptonMETMass.clear();
    _TauLeptonCosDeltaPhi.clear();
    _TauLeptonDeltaR.clear();
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
void TauLeptonFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){

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

	// Make sure we can at least make one TL combo
	if(tightLeptons.size() < 1){ return; } // At least one tight lepton

    // Taus  (corrected taus currently just account for systematic shifts)
    BNtauCollection correctedTaus =  beanHelper->GetCorrectedTaus(_BNtaus, _sysType);
	BNtauCollection selectedTaus = beanHelper->GetSelectedTaus(correctedTaus, tauID::tauNonIso);

	// Make sure we can at least make one TL combo
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

        // Make sure we can at least make one TL combo
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

        // Count exLoose leptons
        unsigned int numExLooseElectrons = 0;
        unsigned int numExLooseMuons = 0;
        for(BNleptonCollection::const_iterator it = cleanExLooseLeptons.begin(); it != cleanExLooseLeptons.end(); ++it){
            if((*it)->isElectron){ numExLooseElectrons++; }
            else if((*it)->isMuon){ numExLooseMuons++; }
        }

        // Count tight leptons
        unsigned int numTightElectrons = 0;
        unsigned int numTightMuons = 0;
        for(BNleptonCollection::const_iterator it = cleanTightLeptons.begin(); it != cleanTightLeptons.end(); ++it){
            if((*it)->isElectron){ numTightElectrons++; }
            else if((*it)->isMuon){ numTightMuons++; }
        }

        if (numTightMuons + numTightElectrons != 1)
            continue;

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

        bool e_triggered = triggers.find("HLT_Ele27_WP80") != triggers.end();
        bool m_triggered = triggers.find("HLT_IsoMu24_eta2p1") != triggers.end();

        if ((numTightMuons == 1 && !m_triggered) ||
                (numTightElectrons == 1 && !e_triggered)) {
            edm::LogWarning("TauLeptonFiller")
                << "Found inconsistent lepton <-> trigger configuration: HLT e "
                << e_triggered << " vs e count " << numTightElectrons
                << "; HLT mu " << m_triggered << " vs mu count "
                << numTightMuons << std::endl;
            continue;
        }

        _NumLooseElectrons		.push_back(numLooseElectrons);
        _NumLooseMuons			.push_back(numLooseMuons);
        _NumExLooseElectrons	.push_back(numExLooseElectrons);
        _NumExLooseMuons		.push_back(numExLooseMuons);
        _NumTightElectrons		.push_back(numTightElectrons);
        _NumTightMuons			.push_back(numTightMuons);

        // Get the two leptons in question
        BNlepton* Lepton = cleanLooseLeptons.at(0);


        // Jets and MET and related quantities
        // Correct for jet pT
        BNjetCollection correctedJets                           = beanHelper->GetCorrectedJets(_BNjets, _sysType);
        // Apply kinematic requirements on corrected jets
        BNjetCollection selCorrJets                             = beanHelper->GetSelectedJets(correctedJets, 30, 2.4, jetID::jetLoose, '-');
        vector<TLorentzVector> tauAndLeptons; // Clean jets from taus and leptons
        tauAndLeptons.push_back(TLorentzVector(Tau->px, Tau->py, Tau->pz, Tau->energy));
        tauAndLeptons.push_back(TLorentzVector(Lepton->px, Lepton->py, Lepton->pz, Lepton->energy));

        // Clean jets
        std::vector<unsigned int> jet_indices;
        BNjetCollection cleanSelCorrJets						= beanHelper->GetCleanJets(selCorrJets, tauAndLeptons, 0.25, &jet_indices);
        _CleanJetIndices.push_back(jet_indices);

        _jet_deltaR_tau.push_back({});
        _jet_deltaR_lepton.push_back({});

        // Derive quantities based on the corrected MET based on the clean, corrected, kinematically-selected jets
        BNmet correctedMET  = beanHelper->GetCorrectedMET(*(_BNmets.begin()), beanHelper->GetUncorrectedJets(cleanSelCorrJets, _BNjets), _sysType);

        _HT.push_back(Tau->pt + Lepton->pt + correctedMET.pt + beanHelper->GetHT(cleanSelCorrJets));

        TLorentzVector vlep(Lepton->px, Lepton->py, Lepton->pz, Lepton->energy);
        TLorentzVector vtau(Tau->px, Tau->py, Tau->pz, Tau->energy);
        TLorentzVector vsum = vlep + vtau;

        for (const auto& j: cleanSelCorrJets)
            vsum += TLorentzVector(j.px, j.py, j.pz, j.energy);

        auto mht = -vsum;
        _MHT.push_back(vsum.Pt());

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


        // TL stuff
        _MomentumRank.push_back(_MomentumRank.size());
        _NumCombos++;

        _TauMomentumRank.push_back(theNumberOfTaus-1);

        tau->Fill(*Tau, beanHelper, _BNmcparticles, correctedMET);
        lep->Fill(Lepton, beanHelper, _BNmcparticles, correctedMET, -vsum);

        auto lepton = Lepton;
        auto helper = beanHelper;
        auto met = correctedMET;

        _TauLeptonVisibleMass.push_back(GetComboMassBN(*Tau, *lepton));
        _TauLeptonMETMass.push_back(GetComboMassBN(*Tau, *lepton, met));
        _TauLeptonCosDeltaPhi.push_back(cos(TMath::Abs(normalizedPhi(Tau->phi - lepton->phi))));
        _TauLeptonDeltaR.push_back(deltaR(Tau->eta, Tau->phi, lepton->eta, lepton->phi));
        for (const auto& jet: selCorrJets) {
            _jet_deltaR_tau.back().push_back(deltaR(jet.eta, jet.phi, Tau->eta, Tau->phi));
            _jet_deltaR_lepton.back().push_back(deltaR(jet.eta, jet.phi, lepton->eta, lepton->phi));
        }
    } // End of tau loop
}
