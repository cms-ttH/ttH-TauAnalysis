// vim: sta:et:sw=4:ts=4
// Authors: Matthias Wolf <matthias.wolf@cern.ch>

// use the same lorentz vector everywhere
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "../interface/AnalysisObjects.h"

template<>
LorentzVector
p4(const BNmet& obj)
{
    return LorentzVector(obj.px, obj.py, 0., 0.);
}

AnalysisObject::AnalysisObject(const std::string& p, TTree* t)
{
    t->Branch((p + "P").c_str(), &_p);
}

void
AnalysisObject::ClearVectors()
{
    _p.clear();
}

AnalysisJets::AnalysisJets(TTree *t)
{
    t->Branch("J_NumJets", &_NumJets);
    t->Branch("J_MomentumRank", &_MomentumRank);
    t->Branch("J_P", &_p);
    t->Branch("J_Charge", &_JetCharge);
    t->Branch("J_PartonId", &_JetPartonId);
    t->Branch("J_PartonParentId", &_JetPartonParentId);
    t->Branch("J_PartonMother0Id", &_JetPartonMother0Id);
    t->Branch("J_PartonMother1Id", &_JetPartonMother1Id);
    t->Branch("J_PartonGrandParentId", &_JetPartonGrandParentId);
    t->Branch("J_PartonGrandmother00Id", &_JetPartonGrandmother00Id);
    t->Branch("J_PartonGrandmother01Id", &_JetPartonGrandmother01Id);
    t->Branch("J_PartonGrandmother10Id", &_JetPartonGrandmother10Id);
    t->Branch("J_PartonGrandmother11Id", &_JetPartonGrandmother11Id);
    t->Branch("J_PartonStatus", &_JetPartonStatus);
    t->Branch("J_PartonMother0Status", &_JetPartonMother0Status);
    t->Branch("J_PartonMother1Status", &_JetPartonMother1Status);
    t->Branch("J_PartonGrandmother00Status", &_JetPartonGrandmother00Status);
    t->Branch("J_PartonGrandmother01Status", &_JetPartonGrandmother01Status);
    t->Branch("J_PartonGrandmother10Status", &_JetPartonGrandmother10Status);
    t->Branch("J_PartonGrandmother11Status", &_JetPartonGrandmother11Status);
    t->Branch("J_combSecVtxBTag", &_combSecVtxBTag);
    t->Branch("J_combSecVtxLooseBTag", &_combSecVtxLooseBTag);
    t->Branch("J_combSecVtxMediumBTag", &_combSecVtxMediumBTag);
    t->Branch("J_combSecVtxTightBTag", &_combSecVtxTightBTag);
}

void
AnalysisJets::ClearVectors()
{
    _NumJets.clear();
    _MomentumRank.clear();
    _p.clear();
    _JetCharge.clear();
    _JetPartonId.clear();
    _JetPartonParentId.clear();
    _JetPartonMother0Id.clear();
    _JetPartonMother1Id.clear();
    _JetPartonGrandParentId.clear();
    _JetPartonGrandmother00Id.clear();
    _JetPartonGrandmother01Id.clear();
    _JetPartonGrandmother10Id.clear();
    _JetPartonGrandmother11Id.clear();
    _JetPartonStatus.clear();
    _JetPartonMother0Status.clear();
    _JetPartonMother1Status.clear();
    _JetPartonGrandmother00Status.clear();
    _JetPartonGrandmother01Status.clear();
    _JetPartonGrandmother10Status.clear();
    _JetPartonGrandmother11Status.clear();
    _combSecVtxBTag.clear();
    _combSecVtxLooseBTag.clear();
    _combSecVtxMediumBTag.clear();
    _combSecVtxTightBTag.clear();
}

void
AnalysisJets::Fill(const BNjetCollection& jets, BEANhelper* helper, const BNmcparticleCollection& mc)
{
    _NumJets.push_back(jets.size());
    _MomentumRank.push_back({});
    _p.push_back({});
    _JetCharge.push_back({});
    _JetPartonId.push_back({});
    _JetPartonParentId.push_back({});
    _JetPartonMother0Id.push_back({});
    _JetPartonMother1Id.push_back({});
    _JetPartonGrandParentId.push_back({});
    _JetPartonGrandmother00Id.push_back({});
    _JetPartonGrandmother01Id.push_back({});
    _JetPartonGrandmother10Id.push_back({});
    _JetPartonGrandmother11Id.push_back({});
    _JetPartonStatus.push_back({});
    _JetPartonMother0Status.push_back({});
    _JetPartonMother1Status.push_back({});
    _JetPartonGrandmother00Status.push_back({});
    _JetPartonGrandmother01Status.push_back({});
    _JetPartonGrandmother10Status.push_back({});
    _JetPartonGrandmother11Status.push_back({});
    _combSecVtxBTag.push_back({});
    _combSecVtxLooseBTag.push_back({});
    _combSecVtxMediumBTag.push_back({});
    _combSecVtxTightBTag.push_back({});

    for (const auto& jet: jets) {
        _MomentumRank.back().push_back(_MomentumRank.size());
        _p.back().push_back(LorentzVector(jet.px, jet.py, jet.pz, jet.energy));
        _JetCharge.back().push_back(jet.charge);

        _combSecVtxBTag.back().push_back(jet.btagCombinedSecVertex);
        _combSecVtxLooseBTag.back().push_back(helper->PassesCSV(jet, 'L'));
        _combSecVtxMediumBTag.back().push_back(helper->PassesCSV(jet, 'M'));
        _combSecVtxTightBTag.back().push_back(helper->PassesCSV(jet, 'T'));

        auto gen_match = helper->GetMatchedMCparticle(mc, jet, 0.25);
        _JetPartonId.back().push_back(gen_match.id);
        _JetPartonMother0Id.back().push_back(gen_match.mother0Id);
        _JetPartonMother1Id.back().push_back(gen_match.mother1Id);
        _JetPartonGrandmother00Id.back().push_back(gen_match.grandMother00Id);
        _JetPartonGrandmother01Id.back().push_back(gen_match.grandMother01Id);
        _JetPartonGrandmother10Id.back().push_back(gen_match.grandMother10Id);
        _JetPartonGrandmother11Id.back().push_back(gen_match.grandMother11Id);
        _JetPartonStatus.back().push_back(gen_match.status);
        _JetPartonMother0Status.back().push_back(gen_match.mother0Status);
        _JetPartonMother1Status.back().push_back(gen_match.mother1Status);
        _JetPartonGrandmother00Status.back().push_back(gen_match.grandMother00Status);
        _JetPartonGrandmother01Status.back().push_back(gen_match.grandMother01Status);
        _JetPartonGrandmother10Status.back().push_back(gen_match.grandMother10Status);
        _JetPartonGrandmother11Status.back().push_back(gen_match.grandMother11Status);

        auto parent = gen_match.mother0Id;
        if (parent == -99)
            parent = gen_match.mother1Id;
        _JetPartonParentId.back().push_back(parent);

        auto grandparent = gen_match.grandMother00Id;
        if (grandparent == -99)
            grandparent = gen_match.grandMother01Id;
        if (grandparent == -99)
            grandparent = gen_match.grandMother10Id;
        if (grandparent == -99)
            grandparent = gen_match.grandMother11Id;
        _JetPartonGrandParentId.back().push_back(grandparent);
    }
}

AnalysisLepton::AnalysisLepton(const std::string& p, TTree* t) :
    AnalysisObject(p, t)
{
    t->Branch((p + "IsMuon").c_str(), &_IsMuon);
    t->Branch((p + "IsElectron").c_str(), &_IsElectron);
    t->Branch((p + "Charge").c_str(), &_Charge);
    t->Branch((p + "RelIso").c_str(), &_RelIso);
    t->Branch((p + "CorrectedD0").c_str(), &_CorrectedD0);
    t->Branch((p + "CorrectedDZ").c_str(), &_CorrectedDZ);
    t->Branch((p + "ImpactParameter").c_str(), &_ImpactParameter);
    t->Branch((p + "IsLoose").c_str(), &_IsLoose);
    t->Branch((p + "IsTight").c_str(), &_IsTight);
    t->Branch((p + "GenMatchDaughter0Id").c_str(), &_GenMatchDaughter0Id);
    t->Branch((p + "GenMatchDaughter1Id").c_str(), &_GenMatchDaughter1Id);
    t->Branch((p + "GenMatchId").c_str(), &_GenMatchId);
    t->Branch((p + "GenMatchMother0Id").c_str(), &_GenMatchMother0Id);
    t->Branch((p + "GenMatchMother1Id").c_str(), &_GenMatchMother1Id);
    t->Branch((p + "GenMatchGrandmother00Id").c_str(), &_GenMatchGrandmother00Id);
    t->Branch((p + "GenMatchGrandmother01Id").c_str(), &_GenMatchGrandmother01Id);
    t->Branch((p + "GenMatchGrandmother10Id").c_str(), &_GenMatchGrandmother10Id);
    t->Branch((p + "GenMatchGrandmother11Id").c_str(), &_GenMatchGrandmother11Id);
    t->Branch((p + "GenMatchDaughter0Status").c_str(), &_GenMatchDaughter0Status);
    t->Branch((p + "GenMatchDaughter1Status").c_str(), &_GenMatchDaughter1Status);
    t->Branch((p + "GenMatchStatus").c_str(), &_GenMatchStatus);
    t->Branch((p + "GenMatchMother0Status").c_str(), &_GenMatchMother0Status);
    t->Branch((p + "GenMatchMother1Status").c_str(), &_GenMatchMother1Status);
    t->Branch((p + "GenMatchGrandmother00Status").c_str(), &_GenMatchGrandmother00Status);
    t->Branch((p + "GenMatchGrandmother01Status").c_str(), &_GenMatchGrandmother01Status);
    t->Branch((p + "GenMatchGrandmother10Status").c_str(), &_GenMatchGrandmother10Status);
    t->Branch((p + "GenMatchGrandmother11Status").c_str(), &_GenMatchGrandmother11Status);
    t->Branch((p + "EventWeight").c_str(), &_EventWeight);
}

void
AnalysisLepton::ClearVectors()
{
    AnalysisObject::ClearVectors();

    _Charge.clear();
    _RelIso.clear();

    _CorrectedD0.clear();
    _CorrectedDZ.clear();
    _ImpactParameter.clear();

    _IsTight.clear();
    _IsLoose.clear();
    _IsMuon.clear();
    _IsElectron.clear();
    _GenMatchDaughter0Id.clear();
    _GenMatchDaughter1Id.clear();
    _GenMatchId.clear();
    _GenMatchMother0Id.clear();
    _GenMatchMother1Id.clear();
    _GenMatchGrandmother00Id.clear();
    _GenMatchGrandmother01Id.clear();
    _GenMatchGrandmother10Id.clear();
    _GenMatchGrandmother11Id.clear();
    _GenMatchDaughter0Status.clear();
    _GenMatchDaughter1Status.clear();
    _GenMatchStatus.clear();
    _GenMatchMother0Status.clear();
    _GenMatchMother1Status.clear();
    _GenMatchGrandmother00Status.clear();
    _GenMatchGrandmother01Status.clear();
    _GenMatchGrandmother10Status.clear();
    _GenMatchGrandmother11Status.clear();
    _EventWeight.clear();
}

void
AnalysisLepton::Fill(const BNlepton* l, BEANhelper *helper, const BNmcparticleCollection& mc_particles)
{
    AnalysisObject::Fill(*l);

    if (l->isMuon) {
        const BNmuon *m = (const BNmuon*) l;
        _IsMuon.push_back(true);
        _IsElectron.push_back(false);
        _RelIso.push_back(helper->GetMuonRelIso(*m));
        _IsLoose.push_back(helper->IsLooseMuon(*m));
        _IsTight.push_back(helper->IsTightMuon(*m));
        _Charge.push_back(m->tkCharge);

        auto id = helper->IsTightMuon(*m) ? muonID::muonTight : muonID::muonLoose;
        _EventWeight.push_back(helper->GetMuonSF(*m, id));
    } else {
        const BNelectron *e = (const BNelectron*) l;
        _IsMuon.push_back(false);
        _IsElectron.push_back(true);
        _RelIso.push_back(helper->GetElectronRelIso(*e));
        _IsLoose.push_back(helper->IsLooseElectron(*e));
        _IsTight.push_back(helper->IsTightElectron(*e));
        _Charge.push_back(e->tkCharge);

        auto id = helper->IsTightElectron(*e) ? electronID::electronTight : electronID::electronLoose;
        _EventWeight.push_back(helper->GetElectronSF(*e, id));
    }

    // this follows as in http://arxiv.org/pdf/hep-ex/9712029v1.pdf
    // float mt = sqrt(2 * l->pt * mht.Pt() * (1 - cos(l->phi - mht.Phi())));
    // reco::Candidate::LorentzVector v(l->px + met.px, l->py + met.py, 0, l->pt + met.pt);
    // _mt.push_back(mt);

    // this follows as in http://arxiv.org/pdf/hep-ex/9712029v1.pdf
    // float mt2 = sqrt(2 * l->pt * met.pt * (1 - cos(l->phi - met.phi)));
    // reco::Candidate::LorentzVector v(l->px + met.px, l->py + met.py, 0, l->pt + met.pt);
    // _mt2.push_back(mt2);

    _CorrectedD0.push_back(l->correctedD0);
    _CorrectedDZ.push_back(l->correctedDZ);
    _ImpactParameter.push_back(l->IP);

    // Provenance
    std::vector<int> undesiredIDs = {6, -6, 12, -12, 14, -14, 16, -16, 25};

    BNmcparticleCollection status3MCparticles = helper->GetSelectedMCparticlesByStatus(mc_particles, false, false, true);
    BNmcparticleCollection selectedMCparticles = helper->GetUnrejectedMCparticlesByPDGid(status3MCparticles, undesiredIDs);
    BNmcparticle gen_match = helper->GetMatchedMCparticle(selectedMCparticles, *l, 0.25);
    _GenMatchDaughter0Id.push_back(gen_match.daughter0Id);
    _GenMatchDaughter1Id.push_back(gen_match.daughter1Id);
    _GenMatchId.push_back(gen_match.id);
    _GenMatchMother0Id.push_back(gen_match.mother0Id);
    _GenMatchMother1Id.push_back(gen_match.mother1Id);
    _GenMatchGrandmother00Id.push_back(gen_match.grandMother00Id);
    _GenMatchGrandmother01Id.push_back(gen_match.grandMother01Id);
    _GenMatchGrandmother10Id.push_back(gen_match.grandMother10Id);
    _GenMatchGrandmother11Id.push_back(gen_match.grandMother11Id);
    _GenMatchDaughter0Status.push_back(gen_match.daughter0Status);
    _GenMatchDaughter1Status.push_back(gen_match.daughter1Status);
    _GenMatchStatus.push_back(gen_match.status);
    _GenMatchMother0Status.push_back(gen_match.mother0Status);
    _GenMatchMother1Status.push_back(gen_match.mother1Status);
    _GenMatchGrandmother00Status.push_back(gen_match.grandMother00Status);
    _GenMatchGrandmother01Status.push_back(gen_match.grandMother01Status);
    _GenMatchGrandmother10Status.push_back(gen_match.grandMother10Status);
    _GenMatchGrandmother11Status.push_back(gen_match.grandMother11Status);
}

AnalysisTau::AnalysisTau(const std::string& p, TTree* t) :
    AnalysisObject(p, t)
{
    t->Branch((p + "MomentumRank").c_str(), &_MomentumRank);
    t->Branch((p + "NProngs").c_str(), &_NProngs);
    t->Branch((p + "NSignalGammas").c_str(), &_NSignalGammas);
    t->Branch((p + "NSignalNeutrals").c_str(), &_NSignalNeutrals);
    t->Branch((p + "DecayMode").c_str(), &_DecayMode);
    t->Branch((p + "EmFraction").c_str(), &_EmFraction);
    t->Branch((p + "IsInTheCracks").c_str(), &_IsInTheCracks);

    t->Branch((p + "HPSagainstElectronDeadECAL").c_str(), &_HPSagainstElectronDeadECAL);
    t->Branch((p + "HPSagainstElectronLoose").c_str(), &_HPSagainstElectronLoose);
    t->Branch((p + "HPSagainstElectronLooseMVA2").c_str(), &_HPSagainstElectronLooseMVA2);
    t->Branch((p + "HPSagainstElectronLooseMVA3").c_str(), &_HPSagainstElectronLooseMVA3);
    t->Branch((p + "HPSagainstElectronMVA").c_str(), &_HPSagainstElectronMVA);
    t->Branch((p + "HPSagainstElectronMVA2category").c_str(), &_HPSagainstElectronMVA2category);
    t->Branch((p + "HPSagainstElectronMVA2raw").c_str(), &_HPSagainstElectronMVA2raw);
    t->Branch((p + "HPSagainstElectronMVA3category").c_str(), &_HPSagainstElectronMVA3category);
    t->Branch((p + "HPSagainstElectronMVA3raw").c_str(), &_HPSagainstElectronMVA3raw);
    t->Branch((p + "HPSagainstElectronMedium").c_str(), &_HPSagainstElectronMedium);
    t->Branch((p + "HPSagainstElectronMediumMVA2").c_str(), &_HPSagainstElectronMediumMVA2);
    t->Branch((p + "HPSagainstElectronMediumMVA3").c_str(), &_HPSagainstElectronMediumMVA3);
    t->Branch((p + "HPSagainstElectronTight").c_str(), &_HPSagainstElectronTight);
    t->Branch((p + "HPSagainstElectronTightMVA2").c_str(), &_HPSagainstElectronTightMVA2);
    t->Branch((p + "HPSagainstElectronTightMVA3").c_str(), &_HPSagainstElectronTightMVA3);
    t->Branch((p + "HPSagainstElectronVLooseMVA2").c_str(), &_HPSagainstElectronVLooseMVA2);
    t->Branch((p + "HPSagainstElectronVTightMVA3").c_str(), &_HPSagainstElectronVTightMVA3);
    t->Branch((p + "HPSagainstMuonLoose").c_str(), &_HPSagainstMuonLoose);
    t->Branch((p + "HPSagainstMuonLoose2").c_str(), &_HPSagainstMuonLoose2);
    t->Branch((p + "HPSagainstMuonMedium").c_str(), &_HPSagainstMuonMedium);
    t->Branch((p + "HPSagainstMuonMedium2").c_str(), &_HPSagainstMuonMedium2);
    t->Branch((p + "HPSagainstMuonTight").c_str(), &_HPSagainstMuonTight);
    t->Branch((p + "HPSagainstMuonTight2").c_str(), &_HPSagainstMuonTight2);
    t->Branch((p + "HPSbyCombinedIsolationDeltaBetaCorrRaw").c_str(), &_HPSbyCombinedIsolationDeltaBetaCorrRaw);
    t->Branch((p + "HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits").c_str(), &_HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits);
    t->Branch((p + "HPSbyIsolationMVA2raw").c_str(), &_HPSbyIsolationMVA2raw);
    t->Branch((p + "HPSbyLooseCombinedIsolationDeltaBetaCorr").c_str(), &_HPSbyLooseCombinedIsolationDeltaBetaCorr);
    t->Branch((p + "HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits").c_str(), &_HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits);
    t->Branch((p + "HPSbyLooseIsolationMVA").c_str(), &_HPSbyLooseIsolationMVA);
    t->Branch((p + "HPSbyLooseIsolationMVA2").c_str(), &_HPSbyLooseIsolationMVA2);
    t->Branch((p + "HPSbyMediumCombinedIsolationDeltaBetaCorr").c_str(), &_HPSbyMediumCombinedIsolationDeltaBetaCorr);
    t->Branch((p + "HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits").c_str(), &_HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits);
    t->Branch((p + "HPSbyMediumIsolationMVA").c_str(), &_HPSbyMediumIsolationMVA);
    t->Branch((p + "HPSbyMediumIsolationMVA2").c_str(), &_HPSbyMediumIsolationMVA2);
    t->Branch((p + "HPSbyTightCombinedIsolationDeltaBetaCorr").c_str(), &_HPSbyTightCombinedIsolationDeltaBetaCorr);
    t->Branch((p + "HPSbyTightCombinedIsolationDeltaBetaCorr3Hits").c_str(), &_HPSbyTightCombinedIsolationDeltaBetaCorr3Hits);
    t->Branch((p + "HPSbyTightIsolationMVA").c_str(), &_HPSbyTightIsolationMVA);
    t->Branch((p + "HPSbyTightIsolationMVA2").c_str(), &_HPSbyTightIsolationMVA2);
    t->Branch((p + "HPSbyVLooseCombinedIsolationDeltaBetaCorr").c_str(), &_HPSbyVLooseCombinedIsolationDeltaBetaCorr);
    t->Branch((p + "HPSdecayModeFinding").c_str(), &_HPSdecayModeFinding);
    t->Branch((p + "HPSbyIsolationMVAraw").c_str(), &_HPSbyIsolationMVAraw);

    t->Branch((p + "LTPt").c_str(), &_LTPt);
    t->Branch((p + "Charge").c_str(), &_Charge);
    t->Branch((p + "LTvalid").c_str(), &_LTvalid);
    t->Branch((p + "LTIpVtdxy").c_str(), &_LTIpVtdxy);
    t->Branch((p + "LTIpVtdz").c_str(), &_LTIpVtdz);
    t->Branch((p + "LTIpVtdxyError").c_str(), &_LTIpVtdxyError);
    t->Branch((p + "LTIpVtdzError").c_str(), &_LTIpVtdzError);
    t->Branch((p + "LTvx").c_str(), &_LTvx);
    t->Branch((p + "LTvy").c_str(), &_LTvy);
    t->Branch((p + "LTvz").c_str(), &_LTvz);
    t->Branch((p + "LTValidHits").c_str(), &_LTValidHits);
    t->Branch((p + "LTNormChiSqrd").c_str(), &_LTNormChiSqrd);

    t->Branch((p + "GenMatchDaughter0Id").c_str(), &_GenMatchDaughter0Id);
    t->Branch((p + "GenMatchDaughter1Id").c_str(), &_GenMatchDaughter1Id);
    t->Branch((p + "GenMatchId").c_str(), &_GenMatchId);
    t->Branch((p + "GenMatchMother0Id").c_str(), &_GenMatchMother0Id);
    t->Branch((p + "GenMatchMother1Id").c_str(), &_GenMatchMother1Id);
    t->Branch((p + "GenMatchGrandmother00Id").c_str(), &_GenMatchGrandmother00Id);
    t->Branch((p + "GenMatchGrandmother01Id").c_str(), &_GenMatchGrandmother01Id);
    t->Branch((p + "GenMatchGrandmother10Id").c_str(), &_GenMatchGrandmother10Id);
    t->Branch((p + "GenMatchGrandmother11Id").c_str(), &_GenMatchGrandmother11Id);
    t->Branch((p + "GenMatchDaughter0Status").c_str(), &_GenMatchDaughter0Status);
    t->Branch((p + "GenMatchDaughter1Status").c_str(), &_GenMatchDaughter1Status);
    t->Branch((p + "GenMatchStatus").c_str(), &_GenMatchStatus);
    t->Branch((p + "GenMatchMother0Status").c_str(), &_GenMatchMother0Status);
    t->Branch((p + "GenMatchMother1Status").c_str(), &_GenMatchMother1Status);
    t->Branch((p + "GenMatchGrandmother00Status").c_str(), &_GenMatchGrandmother00Status);
    t->Branch((p + "GenMatchGrandmother01Status").c_str(), &_GenMatchGrandmother01Status);
    t->Branch((p + "GenMatchGrandmother10Status").c_str(), &_GenMatchGrandmother10Status);
    t->Branch((p + "GenMatchGrandmother11Status").c_str(), &_GenMatchGrandmother11Status);
}

void
AnalysisTau::ClearVectors()
{
    AnalysisObject::ClearVectors();

    _MomentumRank.clear();
    _NProngs.clear();
    _NSignalGammas.clear();
    _NSignalNeutrals.clear();
    _DecayMode.clear();
    _EmFraction.clear();
    _IsInTheCracks.clear();
    _HPSagainstElectronDeadECAL.clear();
    _HPSagainstElectronLoose.clear();
    _HPSagainstElectronLooseMVA2.clear();
    _HPSagainstElectronLooseMVA3.clear();
    _HPSagainstElectronMVA.clear();
    _HPSagainstElectronMVA2category.clear();
    _HPSagainstElectronMVA2raw.clear();
    _HPSagainstElectronMVA3category.clear();
    _HPSagainstElectronMVA3raw.clear();
    _HPSagainstElectronMedium.clear();
    _HPSagainstElectronMediumMVA2.clear();
    _HPSagainstElectronMediumMVA3.clear();
    _HPSagainstElectronTight.clear();
    _HPSagainstElectronTightMVA2.clear();
    _HPSagainstElectronTightMVA3.clear();
    _HPSagainstElectronVLooseMVA2.clear();
    _HPSagainstElectronVTightMVA3.clear();
    _HPSagainstMuonLoose.clear();
    _HPSagainstMuonLoose2.clear();
    _HPSagainstMuonMedium.clear();
    _HPSagainstMuonMedium2.clear();
    _HPSagainstMuonTight.clear();
    _HPSagainstMuonTight2.clear();
    _HPSbyCombinedIsolationDeltaBetaCorrRaw.clear();
    _HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits.clear();
    _HPSbyIsolationMVA2raw.clear();
    _HPSbyLooseCombinedIsolationDeltaBetaCorr.clear();
    _HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits.clear();
    _HPSbyLooseIsolationMVA.clear();
    _HPSbyLooseIsolationMVA2.clear();
    _HPSbyMediumCombinedIsolationDeltaBetaCorr.clear();
    _HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits.clear();
    _HPSbyMediumIsolationMVA.clear();
    _HPSbyMediumIsolationMVA2.clear();
    _HPSbyTightCombinedIsolationDeltaBetaCorr.clear();
    _HPSbyTightCombinedIsolationDeltaBetaCorr3Hits.clear();
    _HPSbyTightIsolationMVA.clear();
    _HPSbyTightIsolationMVA2.clear();
    _HPSbyVLooseCombinedIsolationDeltaBetaCorr.clear();
    _HPSdecayModeFinding.clear();
    _HPSbyIsolationMVAraw.clear();
    _LTPt.clear();
    _Charge.clear();
    _LTvalid.clear();
    _LTIpVtdxy.clear();
    _LTIpVtdz.clear();
    _LTIpVtdxyError.clear();
    _LTIpVtdzError.clear();
    _LTvx.clear();
    _LTvy.clear();
    _LTvz.clear();
    _LTValidHits.clear();
    _LTNormChiSqrd.clear();
    _GenMatchDaughter0Id.clear();
    _GenMatchDaughter1Id.clear();
    _GenMatchId.clear();
    _GenMatchMother0Id.clear();
    _GenMatchMother1Id.clear();
    _GenMatchGrandmother00Id.clear();
    _GenMatchGrandmother01Id.clear();
    _GenMatchGrandmother10Id.clear();
    _GenMatchGrandmother11Id.clear();
    _GenMatchDaughter0Status.clear();
    _GenMatchDaughter1Status.clear();
    _GenMatchStatus.clear();
    _GenMatchMother0Status.clear();
    _GenMatchMother1Status.clear();
    _GenMatchGrandmother00Status.clear();
    _GenMatchGrandmother01Status.clear();
    _GenMatchGrandmother10Status.clear();
    _GenMatchGrandmother11Status.clear();
}

void
AnalysisTau::Fill(const BNtau& t, const BEANhelper *helper, const BNmcparticleCollection& mc_particles)
{
    AnalysisObject::Fill(t);

    _NProngs.push_back(t.numProngs);
    _NSignalGammas.push_back(t.numSignalGammas);
    _NSignalNeutrals.push_back(t.numSignalNeutrals);
    _DecayMode.push_back(t.decayMode);
    _EmFraction.push_back(t.emFraction);
    _IsInTheCracks.push_back(t.inTheCracks);

    // HPS discriminants
    _HPSagainstElectronDeadECAL.push_back(t.HPSagainstElectronDeadECAL);
    _HPSagainstElectronLoose.push_back(t.HPSagainstElectronLoose);
    _HPSagainstElectronLooseMVA2.push_back(t.HPSagainstElectronLooseMVA2);
    _HPSagainstElectronLooseMVA3.push_back(t.HPSagainstElectronLooseMVA3);
    _HPSagainstElectronMVA.push_back(t.HPSagainstElectronMVA);
    _HPSagainstElectronMVA2category.push_back(t.HPSagainstElectronMVA2category);
    _HPSagainstElectronMVA2raw.push_back(t.HPSagainstElectronMVA2raw);
    _HPSagainstElectronMVA3category.push_back(t.HPSagainstElectronMVA3category);
    _HPSagainstElectronMVA3raw.push_back(t.HPSagainstElectronMVA3raw);
    _HPSagainstElectronMedium.push_back(t.HPSagainstElectronMedium);
    _HPSagainstElectronMediumMVA2.push_back(t.HPSagainstElectronMediumMVA2);
    _HPSagainstElectronMediumMVA3.push_back(t.HPSagainstElectronMediumMVA3);
    _HPSagainstElectronTight.push_back(t.HPSagainstElectronTight);
    _HPSagainstElectronTightMVA2.push_back(t.HPSagainstElectronTightMVA2);
    _HPSagainstElectronTightMVA3.push_back(t.HPSagainstElectronTightMVA3);
    _HPSagainstElectronVLooseMVA2.push_back(t.HPSagainstElectronVLooseMVA2);
    _HPSagainstElectronVTightMVA3.push_back(t.HPSagainstElectronVTightMVA3);
    _HPSagainstMuonLoose.push_back(t.HPSagainstMuonLoose);
    _HPSagainstMuonLoose2.push_back(t.HPSagainstMuonLoose2);
    _HPSagainstMuonMedium.push_back(t.HPSagainstMuonMedium);
    _HPSagainstMuonMedium2.push_back(t.HPSagainstMuonMedium2);
    _HPSagainstMuonTight.push_back(t.HPSagainstMuonTight);
    _HPSagainstMuonTight2.push_back(t.HPSagainstMuonTight2);
    _HPSbyCombinedIsolationDeltaBetaCorrRaw.push_back(t.HPSbyCombinedIsolationDeltaBetaCorrRaw);
    _HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits.push_back(t.HPSbyCombinedIsolationDeltaBetaCorrRaw3Hits);
    _HPSbyIsolationMVA2raw.push_back(t.HPSbyIsolationMVA2raw);
    _HPSbyLooseCombinedIsolationDeltaBetaCorr.push_back(t.HPSbyLooseCombinedIsolationDeltaBetaCorr);
    _HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits.push_back(t.HPSbyLooseCombinedIsolationDeltaBetaCorr3Hits);
    _HPSbyLooseIsolationMVA.push_back(t.HPSbyLooseIsolationMVA);
    _HPSbyLooseIsolationMVA2.push_back(t.HPSbyLooseIsolationMVA2);
    _HPSbyMediumCombinedIsolationDeltaBetaCorr.push_back(t.HPSbyMediumCombinedIsolationDeltaBetaCorr);
    _HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits.push_back(t.HPSbyMediumCombinedIsolationDeltaBetaCorr3Hits);
    _HPSbyMediumIsolationMVA.push_back(t.HPSbyMediumIsolationMVA);
    _HPSbyMediumIsolationMVA2.push_back(t.HPSbyMediumIsolationMVA2);
    _HPSbyTightCombinedIsolationDeltaBetaCorr.push_back(t.HPSbyTightCombinedIsolationDeltaBetaCorr);
    _HPSbyTightCombinedIsolationDeltaBetaCorr3Hits.push_back(t.HPSbyTightCombinedIsolationDeltaBetaCorr3Hits);
    _HPSbyTightIsolationMVA.push_back(t.HPSbyTightIsolationMVA);
    _HPSbyTightIsolationMVA2.push_back(t.HPSbyTightIsolationMVA2);
    _HPSbyVLooseCombinedIsolationDeltaBetaCorr.push_back(t.HPSbyVLooseCombinedIsolationDeltaBetaCorr);
    _HPSdecayModeFinding.push_back(t.HPSdecayModeFinding);
    _HPSbyIsolationMVAraw.push_back(t.HPSbyIsolationMVAraw);

    // Leading track variables
    _LTPt.push_back(t.leadingTrackPt);
    _Charge.push_back(t.charge);
    _LTvalid.push_back(t.leadingTrackValid);
    _LTIpVtdxy.push_back(t.leadingTrackIpVtdxy);
    _LTIpVtdz.push_back(t.leadingTrackIpVtdz);
    _LTIpVtdxyError.push_back(t.leadingTrackIpVtdxyError);
    _LTIpVtdzError.push_back(t.leadingTrackIpVtdzError);
    _LTvx.push_back(t.leadingTrackVx);
    _LTvy.push_back(t.leadingTrackVy);
    _LTvz.push_back(t.leadingTrackVz);
    _LTValidHits.push_back(t.leadingTrackValidHits);
    _LTNormChiSqrd.push_back(t.leadingTrackNormChiSqrd);

    // Provenance
    std::vector<int> undesiredIDs = {6, -6, 12, -12, 14, -14, 16, -16, 25};
    // undesiredIDs.push_back(6);
    // undesiredIDs.push_back(-6);		// No tops
    // undesiredIDs.push_back(12);	undesiredIDs.push_back(-12);	// No e neutrinos
    // undesiredIDs.push_back(14);	undesiredIDs.push_back(-14);	// No mu neutrinos
    // undesiredIDs.push_back(16);	undesiredIDs.push_back(-16);	// No tau neutrinos
    //undesiredIDs.push_back(24);	undesiredIDs.push_back(-24);	// No W
    // undesiredIDs.push_back(25);									// No H
    //undesiredIDs.push_back(21);									// No g

    BNmcparticleCollection status3MCparticles = helper->GetSelectedMCparticlesByStatus(mc_particles, false, false, true);
    BNmcparticleCollection selectedMCparticles = helper->GetUnrejectedMCparticlesByPDGid(status3MCparticles, undesiredIDs);

    BNmcparticle tauGenMatch = helper->GetMatchedMCparticle(selectedMCparticles, t, 0.25);
    _GenMatchDaughter0Id.push_back(tauGenMatch.daughter0Id);
    _GenMatchDaughter1Id.push_back(tauGenMatch.daughter1Id);
    _GenMatchId.push_back(tauGenMatch.id);
    _GenMatchMother0Id.push_back(tauGenMatch.mother0Id);
    _GenMatchMother1Id.push_back(tauGenMatch.mother1Id);
    _GenMatchGrandmother00Id.push_back(tauGenMatch.grandMother00Id);
    _GenMatchGrandmother01Id.push_back(tauGenMatch.grandMother01Id);
    _GenMatchGrandmother10Id.push_back(tauGenMatch.grandMother10Id);
    _GenMatchGrandmother11Id.push_back(tauGenMatch.grandMother11Id);
    _GenMatchDaughter0Status.push_back(tauGenMatch.daughter0Status);
    _GenMatchDaughter1Status.push_back(tauGenMatch.daughter1Status);
    _GenMatchStatus.push_back(tauGenMatch.status);
    _GenMatchMother0Status.push_back(tauGenMatch.mother0Status);
    _GenMatchMother1Status.push_back(tauGenMatch.mother1Status);
    _GenMatchGrandmother00Status.push_back(tauGenMatch.grandMother00Status);
    _GenMatchGrandmother01Status.push_back(tauGenMatch.grandMother01Status);
    _GenMatchGrandmother10Status.push_back(tauGenMatch.grandMother10Status);
    _GenMatchGrandmother11Status.push_back(tauGenMatch.grandMother11Status);
}
