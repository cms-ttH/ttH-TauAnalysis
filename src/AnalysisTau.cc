// vim: sta:et:sw=4:ts=4
// Authors: Matthias Wolf <matthias.wolf@cern.ch>

#include "../interface/AnalysisTau.h"

AnalysisTau::AnalysisTau(const std::string& p, TTree* t)
{
    t->Branch((p + "MomentumRank").c_str(), &_MomentumRank);
    t->Branch((p + "Pt").c_str(), &_Pt);
    t->Branch((p + "Eta").c_str(), &_Eta);
    t->Branch((p + "Phi").c_str(), &_Phi);
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
    _MomentumRank.clear();
    _Pt.clear();
    _Eta.clear();
    _Phi.clear();
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
    _Pt.push_back(t.pt);
    _Eta.push_back(t.eta);
    _Phi.push_back(t.phi);
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
