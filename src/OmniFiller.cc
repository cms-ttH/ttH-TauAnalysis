// vim: sta:et:sw=4:ts=4

#include <cmath>

#include "../interface/OmniFiller.h"

using namespace edm;
using namespace reco;

inline std::string
suffix(unsigned int idx, unsigned int max)
{
    return (max <= 1) ? "" : std::to_string(idx);
}

std::vector<BNtauCollection>
build_permutations(const BNtauCollection& taus, const unsigned int num)
{
    if (num == 0 or num > taus.size())
        return {BNtauCollection()};

    std::vector<BNtauCollection> res;
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < num; ++i)
        indices.push_back(i);

    do {
        BNtauCollection perm;
        for (const auto& i: indices)
            perm.push_back(taus[i]);
        res.push_back(perm);

        for (int i = indices.size() - 1; i >= 0; --i) {
            // increase indices, starting with the back
            indices[i] += 1;
            if (indices[i] <= taus.size() - indices.size() + i) {
                // if an index is smaller than the # of taus (minus room
                // for the other indices), we need to reset the
                // remaining ones and stop increasing lower indices.
                for (unsigned int j = 1; i + j < indices.size(); ++j)
                    indices[i + j] = indices[i] + j;
                break;
            }
        }
    } while (indices.front() < taus.size() && indices.back() < taus.size());

    return res;
}

std::pair<int, int>
count_leptons(const BNleptonCollection& leps)
{
    auto counts = std::make_pair<int, int>(0, 0);
    for (const auto& lep: leps) {
        if (lep->isElectron)
            ++counts.first;
        else if (lep->isMuon)
            ++counts.second;
    }
    return counts;
}

OmniFiller::OmniFiller(const ParameterSet& iConfig, TTree* t, BEANhelper* iBEANhelper) :
    NtupleFiller(iConfig, iBEANhelper),
    required_leptons(iConfig.getParameter<unsigned int>("requiredLeptons")),
    required_taus(iConfig.getParameter<unsigned int>("requiredTaus")),
    tree_jets(t),
    tree_met("MET_", t)
{
    _FillerName = __FILE__;
    _Tree = t;

    SetupBranches();

    for (unsigned int i = 0; i < required_leptons; ++i)
        tree_leptons.push_back(new AnalysisLepton("L" + suffix(i + 1, required_leptons) + "_", _Tree));
    for (unsigned int i = 0; i < required_taus; ++i)
        tree_taus.push_back(new AnalysisTau("T" + suffix(i + 1, required_taus) + "_", _Tree));

    required_triggers[0][2] = {"HLT_Mu17_Mu8", "HLT_Mu17_TkMu8"};
    required_triggers[0][1] = {"HLT_IsoMu24_eta2p1"};
    required_triggers[1][1] = {"HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL", "HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"};
    required_triggers[1][0] = {"HLT_Ele27_WP80"};
    required_triggers[2][0] = {"HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"};
}

OmniFiller::~OmniFiller()
{
    for (auto& l: tree_leptons)
        delete l;
    for (auto& t: tree_taus)
        delete t;
}

// ------------ method called to for each event  ------------
void OmniFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void OmniFiller::SetupBranches()
{
    // Set up tree branches
    _Tree->Branch("NumTaus",&_NumTaus);
    _Tree->Branch("NumLooseMuons",&_NumLooseMuons);
    _Tree->Branch("NumExLooseMuons",&_NumExLooseMuons);
    _Tree->Branch("NumTightMuons",&_NumTightMuons);
    _Tree->Branch("NumLooseElectrons",&_NumLooseElectrons);
    _Tree->Branch("NumExLooseElectrons",&_NumExLooseElectrons);
    _Tree->Branch("NumTightElectrons",&_NumTightElectrons);
    _Tree->Branch("NumCombos",&_NumCombos);
    _Tree->Branch("MomentumRank",&_MomentumRank);

    // === Combo === //
    _Tree->Branch("TriggerEventWeight", &_TriggerEventWeight);

    _Tree->Branch("HT", &_HT);
    _Tree->Branch("MHT", &_MHT);
    _Tree->Branch("NumCSVLbtagJets", &_NumCSVLbtagJets);
    _Tree->Branch("NumCSVMbtagJets", &_NumCSVMbtagJets);
    _Tree->Branch("NumCSVTbtagJets", &_NumCSVTbtagJets);
    _Tree->Branch("NumNonCSVLbtagJets", &_NumNonCSVLbtagJets);
    _Tree->Branch("NumNonCSVMbtagJets", &_NumNonCSVMbtagJets);
    _Tree->Branch("NumNonCSVTbtagJets", &_NumNonCSVTbtagJets);
    _Tree->Branch("NumCleanCSVLbtagJets", &_NumCleanCSVLbtagJets);
    _Tree->Branch("NumCleanCSVMbtagJets", &_NumCleanCSVMbtagJets);
    _Tree->Branch("NumCleanCSVTbtagJets", &_NumCleanCSVTbtagJets);
    _Tree->Branch("NumCleanNonCSVLbtagJets", &_NumCleanNonCSVLbtagJets);
    _Tree->Branch("NumCleanNonCSVMbtagJets", &_NumCleanNonCSVMbtagJets);
    _Tree->Branch("NumCleanNonCSVTbtagJets", &_NumCleanNonCSVTbtagJets);

    // === Weights === //
    _Tree->Branch("CSVeventWeight", &_CSVeventWeight);
    _Tree->Branch("CSVeventWeightHFdown", &_CSVeventWeightHFdown);
    _Tree->Branch("CSVeventWeightHFup", &_CSVeventWeightHFup);
    _Tree->Branch("CSVeventWeightLFdown", &_CSVeventWeightLFdown);
    _Tree->Branch("CSVeventWeightLFup", &_CSVeventWeightLFup);
    _Tree->Branch("CSVeventWeightHFStats1down", &_CSVeventWeightHFStats1down);
    _Tree->Branch("CSVeventWeightHFStats1up", &_CSVeventWeightHFStats1up);
    _Tree->Branch("CSVeventWeightLFStats1down", &_CSVeventWeightLFStats1down);
    _Tree->Branch("CSVeventWeightLFStats1up", &_CSVeventWeightLFStats1up);
    _Tree->Branch("CSVeventWeightHFStats2down", &_CSVeventWeightHFStats2down);
    _Tree->Branch("CSVeventWeightHFStats2up", &_CSVeventWeightHFStats2up);
    _Tree->Branch("CSVeventWeightLFStats2down", &_CSVeventWeightLFStats2down);
    _Tree->Branch("CSVeventWeightLFStats2up", &_CSVeventWeightLFStats2up);
    _Tree->Branch("CSVeventWeightCErr1up", &_CSVeventWeightCErr1up);
    _Tree->Branch("CSVeventWeightCErr1down", &_CSVeventWeightCErr1down);
    _Tree->Branch("CSVeventWeightCErr2up", &_CSVeventWeightCErr2up);
    _Tree->Branch("CSVeventWeightCErr2down", &_CSVeventWeightCErr2down);
}

// === Clear vectors that will be used to fill ntuple === //
void OmniFiller::ClearVectors()
{
    for (auto& lep: tree_leptons)
        lep->ClearVectors();
    for (auto& tau: tree_taus)
        tau->ClearVectors();

    tree_jets.ClearVectors();
    tree_met.ClearVectors();

    _NumTaus = 0;
    _NumCombos = 0;
    _MomentumRank.clear();

    // === Lepton === //
    _NumLooseMuons.clear();
    _NumExLooseMuons.clear();
    _NumTightMuons.clear();
    _NumLooseElectrons.clear();
    _NumExLooseElectrons.clear();
    _NumTightElectrons.clear();

    // === Combo === //
    _TriggerEventWeight.clear();

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
bool OmniFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){

    // Get the object collections from the event
    GetCollections(iEvent, iSetup);

    // Clear vectors
    ClearVectors();

    // Leptons
    BNelectronCollection tightElectrons = helper->GetSelectedElectrons(_BNelectrons, electronID::electronTight);
    BNmuonCollection tightMuons = helper->GetSelectedMuons(_BNmuons, muonID::muonTight);
    BNleptonCollection tightLeptons;
    tightLeptons.push_back(tightElectrons);
    tightLeptons.push_back(tightMuons);
    tightLeptons.sort();

    BNelectronCollection looseElectrons = helper->GetSelectedElectrons(_BNelectrons, electronID::electronLoose);
    BNmuonCollection looseMuons = helper->GetSelectedMuons(_BNmuons, muonID::muonLoose);
    BNleptonCollection looseLeptons;
    looseLeptons.push_back(looseElectrons);
    looseLeptons.push_back(looseMuons);
    looseLeptons.sort();

    BNelectronCollection exLooseElectrons = helper->GetDifference(looseElectrons, tightElectrons);
    BNmuonCollection exLooseMuons = helper->GetDifference(looseMuons, tightMuons);
    BNleptonCollection exLooseLeptons;
    exLooseLeptons.push_back(exLooseElectrons);
    exLooseLeptons.push_back(exLooseMuons);
    exLooseLeptons.sort();

    // Make sure we can at least make one combo
    if (looseLeptons.size() != required_leptons ||
            tightLeptons.size() < min(required_leptons, (unsigned int) 1))
        return false;

    // Taus  (corrected taus currently just account for systematic shifts)
    BNtauCollection correctedTaus =  helper->GetCorrectedTaus(_BNtaus, _sysType);
    BNtauCollection selectedTaus = helper->GetSelectedTaus(correctedTaus, tauID::tauNonIso);

    // Make sure we can at least make one combo
    if (correctedTaus.size() < required_taus)
        return false;

    _NumTaus = selectedTaus.size();
    unsigned int theNumberOfTaus = 0;
    unsigned int filled = 0;

    for (const auto& taus: build_permutations(selectedTaus, required_taus)) {
        theNumberOfTaus++;

        // Clean leptons
        BNleptonCollection cleanLooseLeptons = helper->GetDifference(looseLeptons, taus, 0.15);
        BNleptonCollection cleanExLooseLeptons = helper->GetDifference(exLooseLeptons, taus, 0.15);
        BNleptonCollection cleanTightLeptons = helper->GetDifference(tightLeptons, taus, 0.15);

        // Make sure we can at least make one TLL combo
        if (cleanLooseLeptons.size() != required_leptons)
            continue; // Exactly two tight or loose leptons
        if (cleanTightLeptons.size() < min(required_leptons, (unsigned int) 1))
            continue; // At least one tight lepton

        // Count loose leptons
        auto counts = count_leptons(cleanLooseLeptons);
        unsigned int numLooseElectrons = counts.first;
        unsigned int numLooseMuons = counts.second;

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

        if (required_triggers.find(numLooseElectrons) == required_triggers.end() ||
                required_triggers[numLooseElectrons].find(numLooseMuons) == required_triggers[numLooseElectrons].end()) {
            edm::LogWarning("OmniFiller")
                << "No trigger requirement found for " << numLooseElectrons
                << " e and " << numLooseMuons << " mu" << std::endl;
            continue;
        }

        bool matched = false;
        for (const auto& trig: required_triggers[numLooseElectrons][numLooseMuons]) {
            if (triggers.find(trig) != triggers.end()) {
                matched = true;
            }
        }

        if (!matched) {
            edm::LogWarning("OmniFiller")
                << "No matching trigger requirement found for " << numLooseElectrons
                << " e and " << numLooseMuons << " mu" << std::endl;
            continue;
        }

        _NumLooseElectrons.push_back(numLooseElectrons);
        _NumLooseMuons.push_back(numLooseMuons);

        // Count exLoose leptons
        counts = count_leptons(cleanExLooseLeptons);
        _NumExLooseElectrons.push_back(counts.first);
        _NumExLooseMuons.push_back(counts.second);

        // Count tight leptons
        counts = count_leptons(cleanTightLeptons);
        _NumTightElectrons.push_back(counts.first);
        _NumTightMuons.push_back(counts.second);

        // Jets and MET and related quantities
        // Correct for jet pT
        BNjetCollection corrected_jets = helper->GetCorrectedJets(_BNjets, _sysType);

        // Clean jets of leptons
        std::vector<unsigned int> tmp_indices;
        BNjetCollection tmp_jets = helper->GetCleanJets(corrected_jets, cleanLooseLeptons, 0.25, &tmp_indices);

        // Re-cut jets and clean of taus
        std::vector<unsigned int> jet_indices;
        BNjetCollection clean_jets;
        BNjetCollection unclean_jets;
        for (unsigned int i = 0; i < tmp_jets.size(); ++i) {
            if (!helper->IsGoodJet(tmp_jets[i], 30, 2.4, jetID::jetLoose, '-'))
                continue;

            unclean_jets.push_back(tmp_jets[i]);

            bool tau_overlap = false;
            for (const auto& tau: taus) {
                if (deltaR(tmp_jets[i].eta, tmp_jets[i].phi, tau.eta, tau.phi) < 0.25) {
                    tau_overlap = true;
                    break;
                }
            }

            if (tau_overlap)
                continue;

            clean_jets.push_back(tmp_jets[i]);
            jet_indices.push_back(tmp_indices[i]);
        }

        tree_jets.Fill(clean_jets, helper, _BNmcparticles);

        BNjetCollection cleanSelUncorrJets;
        for (const auto& j: jet_indices)
            cleanSelUncorrJets.push_back(_BNjets[j]);

        // Derive quantities based on the corrected MET based on the clean, corrected, kinematically-selected jets
        BNmet met = helper->GetCorrectedMET(*(_BNmets.begin()), cleanSelUncorrJets, _sysType);
        tree_met.Fill(met);

        // _HT.push_back(Tau->pt + Lepton1->pt + Lepton2->pt + correctedMET.pt + helper->GetHT(clean_jets));

        // TLorentzVector vlep1(Lepton1->px, Lepton1->py, Lepton1->pz, Lepton1->energy);
        // TLorentzVector vlep2(Lepton2->px, Lepton2->py, Lepton2->pz, Lepton2->energy);
        // TLorentzVector vtau(Tau->px, Tau->py, Tau->pz, Tau->energy);
        // TLorentzVector vsum = vlep1 + vlep2 + vtau;

        // TLorentzVector jsum;
        // TLorentzVector jlsum;

        // if (Tau->charge * Lepton1->charge > 0)
            // jlsum += vlep1;
        // else
            // jlsum += vlep2;

        // for (const auto& j: clean_jets) {
            // vsum += TLorentzVector(j.px, j.py, j.pz, j.energy);
            // jsum += TLorentzVector(j.px, j.py, j.pz, j.energy);
            // jlsum += TLorentzVector(j.px, j.py, j.pz, j.energy);
        // }

        // auto mht = -vsum;
        // _MHT.push_back(vsum.Pt());

        _NumCSVLbtagJets.push_back(helper->GetNumCSVbtags(unclean_jets, 'L'));
        _NumCSVMbtagJets.push_back(helper->GetNumCSVbtags(unclean_jets, 'M'));
        _NumCSVTbtagJets.push_back(helper->GetNumCSVbtags(unclean_jets, 'T'));
        _NumNonCSVLbtagJets.push_back(helper->GetNumNonCSVbtags(unclean_jets, 'L'));
        _NumNonCSVMbtagJets.push_back(helper->GetNumNonCSVbtags(unclean_jets, 'M'));
        _NumNonCSVTbtagJets.push_back(helper->GetNumNonCSVbtags(unclean_jets, 'T'));

        _NumCleanCSVLbtagJets.push_back(helper->GetNumCSVbtags(clean_jets, 'L'));
        _NumCleanCSVMbtagJets.push_back(helper->GetNumCSVbtags(clean_jets, 'M'));
        _NumCleanCSVTbtagJets.push_back(helper->GetNumCSVbtags(clean_jets, 'T'));
        _NumCleanNonCSVLbtagJets.push_back(helper->GetNumNonCSVbtags(clean_jets, 'L'));
        _NumCleanNonCSVMbtagJets.push_back(helper->GetNumNonCSVbtags(clean_jets, 'M'));
        _NumCleanNonCSVTbtagJets.push_back(helper->GetNumNonCSVbtags(clean_jets, 'T'));

        // for (auto& idx: tag_indices)
            // idx = jet_indices[idx];
        // for (auto& idx: notag_indices)
            // idx = jet_indices[idx];

        // fill total jet weight with clean jets
        _CSVeventWeight.push_back(helper->GetCSVweight(clean_jets, _sysType));

        // CSV weights for systematics
        if (_sysType == sysType::NA) {
            _CSVeventWeightLFup.push_back(helper->GetCSVweight(clean_jets, sysType::CSVLFup));
            _CSVeventWeightLFdown.push_back(helper->GetCSVweight(clean_jets, sysType::CSVLFdown));
            _CSVeventWeightHFup.push_back(helper->GetCSVweight(clean_jets, sysType::CSVHFup));
            _CSVeventWeightHFdown.push_back(helper->GetCSVweight(clean_jets, sysType::CSVHFdown));

            _CSVeventWeightLFStats1up.push_back(helper->GetCSVweight(clean_jets, sysType::CSVLFStats1up));
            _CSVeventWeightLFStats1down.push_back(helper->GetCSVweight(clean_jets, sysType::CSVLFStats1down));
            _CSVeventWeightHFStats1up.push_back(helper->GetCSVweight(clean_jets, sysType::CSVHFStats1up));
            _CSVeventWeightHFStats1down.push_back(helper->GetCSVweight(clean_jets, sysType::CSVHFStats1down));

            _CSVeventWeightLFStats2up.push_back(helper->GetCSVweight(clean_jets, sysType::CSVLFStats2up));
            _CSVeventWeightLFStats2down.push_back(helper->GetCSVweight(clean_jets, sysType::CSVLFStats2down));
            _CSVeventWeightHFStats2up.push_back(helper->GetCSVweight(clean_jets, sysType::CSVHFStats2up));
            _CSVeventWeightHFStats2down.push_back(helper->GetCSVweight(clean_jets, sysType::CSVHFStats2down));

            _CSVeventWeightCErr1up.push_back(helper->GetCSVweight(clean_jets, sysType::CSVCErr1up));
            _CSVeventWeightCErr1down.push_back(helper->GetCSVweight(clean_jets, sysType::CSVCErr1down));
            _CSVeventWeightCErr2up.push_back(helper->GetCSVweight(clean_jets, sysType::CSVCErr2up));
            _CSVeventWeightCErr2down.push_back(helper->GetCSVweight(clean_jets, sysType::CSVCErr2down));
        }


        // TLL stuff
        _MomentumRank.push_back(_MomentumRank.size());
        _NumCombos++;

        for (unsigned int i = 0; i < required_leptons; ++i)
            tree_leptons[i]->Fill(cleanLooseLeptons[i], helper, _BNmcparticles);
        for (unsigned int i = 0; i < required_taus; ++i)
            tree_taus[i]->Fill(taus[i], helper, _BNmcparticles);

        if (cleanLooseLeptons.size() == 2) {
            auto lepton1 = cleanLooseLeptons[0];
            auto lepton2 = cleanLooseLeptons[1];

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
        }

        // double dil_vismass = GetComboMassBN(*lepton1, *lepton2);
        // bool pass_zmask =
                          // (dil_vismass < (65.5 + 3 * mht.Pt() / 8)) ||
                          // (dil_vismass > (108 - mht.Pt() / 4)) ||
                          // (dil_vismass < (79 - 3 * mht.Pt() / 4)) ||
                          // (dil_vismass > (99 + mht.Pt() / 2));
        // _zmask.push_back(pass_zmask);

        // bool pass_zmask2 =
                           // (dil_vismass < (65.5 + 3 * met.pt / 8)) ||
                           // (dil_vismass > (108 - met.pt / 4)) ||
                           // (dil_vismass < (79 - 3 * met.pt / 4)) ||
                           // (dil_vismass > (99 + met.pt / 2));
        // _zmask2.push_back(pass_zmask2);
        ++filled;
    } // End of tau loop

    return (filled > 0);
}
