// vim: sta:et:sw=4:ts=4
// Authors: Matthias Wolf <matthias.wolf@cern.ch>

// use the same lorentz vector everywhere
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "../interface/AnalysisLepton.h"

AnalysisLepton::AnalysisLepton(const std::string& p, TTree* t)
{
    t->Branch((p + "IsMuon").c_str(), &_IsMuon);
    t->Branch((p + "IsElectron").c_str(), &_IsElectron);
    t->Branch((p + "Charge").c_str(), &_Charge);
    t->Branch((p + "P").c_str(), &_p);
    t->Branch((p + "Pt").c_str(), &_Pt);
    t->Branch((p + "Eta").c_str(), &_Eta);
    t->Branch((p + "Phi").c_str(), &_Phi);
    t->Branch((p + "Mt").c_str(), &_mt);
    t->Branch((p + "Mt2").c_str(), &_mt2);
    t->Branch((p + "RelIso").c_str(), &_RelIso);
    t->Branch((p + "CorrectedD0").c_str(), &_CorrectedD0);
    t->Branch((p + "CorrectedDZ").c_str(), &_CorrectedDZ);
    t->Branch((p + "ImpactParameter").c_str(), &_ImpactParameter);
    t->Branch((p + "METCosDeltaPhi").c_str(), &_METCosDeltaPhi);
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
    _Charge.clear();
    _p.clear();
    _Pt.clear();
    _Eta.clear();
    _Phi.clear();
    _mt.clear();
    _mt2.clear();
    _RelIso.clear();

    _CorrectedD0.clear();
    _CorrectedDZ.clear();
    _ImpactParameter.clear();
    _METCosDeltaPhi.clear();

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
AnalysisLepton::Fill(const BNlepton* l, BEANhelper *helper, const BNmcparticleCollection& mc_particles, const BNmet& met, const TLorentzVector& mht)
{
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

    _p.push_back(LorentzVector(l->px, l->py, l->pz, l->energy));
    _Pt.push_back(l->pt);
    _Eta.push_back(l->eta);
    _Phi.push_back(l->phi);

    // this follows as in http://arxiv.org/pdf/hep-ex/9712029v1.pdf
    float mt = sqrt(2 * l->pt * mht.Pt() * (1 - cos(l->phi - mht.Phi())));
    // reco::Candidate::LorentzVector v(l->px + met.px, l->py + met.py, 0, l->pt + met.pt);
    _mt.push_back(mt);

    // this follows as in http://arxiv.org/pdf/hep-ex/9712029v1.pdf
    float mt2 = sqrt(2 * l->pt * met.pt * (1 - cos(l->phi - met.phi)));
    // reco::Candidate::LorentzVector v(l->px + met.px, l->py + met.py, 0, l->pt + met.pt);
    _mt2.push_back(mt2);

    _CorrectedD0.push_back(l->correctedD0);
    _CorrectedDZ.push_back(l->correctedDZ);
    _ImpactParameter.push_back(l->IP);
    _METCosDeltaPhi.push_back(cos(l->phi - met.phi));

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
