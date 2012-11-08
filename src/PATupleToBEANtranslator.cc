// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/PATupleToBEANtranslator.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
PATupleToBEANtranslator::PATupleToBEANtranslator(){
    minJetPt_ = 10;
    minNDOF_ = 4;
    maxAbsZ_ = 15;
    maxd0_ = 2;
}

// === Destructor === //
PATupleToBEANtranslator::~PATupleToBEANtranslator(){}

BNeventCollection PATupleToBEANtranslator::EDMtoBN(Event const* iEvent){
	BNeventCollection result;
	return result;
}

BNmcparticleCollection	PATupleToBEANtranslator::RECOtoBN(reco::GenParticleCollection const* iCollection){
    BNmcparticleCollection result;

    for( size_t k = 0; k < iCollection->size(); k++ ){
        const reco::Candidate & mcParticle = (*iCollection)[k];

        int status = mcParticle.status();
        int pdgId  = mcParticle.pdgId();
        int numdgt = mcParticle.numberOfDaughters();

        int aId = abs(pdgId);
        bool keep = false;
        if( (status==3) ||
                (aId==23 || aId==24 || aId==25 || aId==6 || aId==5 || aId==4 || aId==11 || aId==13 || aId==15) ) keep = true;

        if( !keep ) continue;


        BNmcparticle MyMCparticle;

        MyMCparticle.energy = mcParticle.energy();
        MyMCparticle.et = mcParticle.et();
        MyMCparticle.pt = mcParticle.pt();
        MyMCparticle.px = mcParticle.px();
        MyMCparticle.py = mcParticle.py();
        MyMCparticle.pz = mcParticle.pz();
        MyMCparticle.phi = mcParticle.phi();
        MyMCparticle.eta = mcParticle.eta();
        MyMCparticle.theta = mcParticle.theta();
        MyMCparticle.mass = mcParticle.mass();
        MyMCparticle.vx = mcParticle.vx();
        MyMCparticle.vy = mcParticle.vy();
        MyMCparticle.vz = mcParticle.vz();
        MyMCparticle.charge = mcParticle.charge();
        MyMCparticle.id = mcParticle.pdgId();
        MyMCparticle.status = mcParticle.status();



        if( (mcParticle.numberOfMothers()==1) ){
            MyMCparticle.motherId = mcParticle.mother()->pdgId();
            MyMCparticle.motherCharge = mcParticle.mother()->charge();
            MyMCparticle.motherET = mcParticle.mother()->et();
            MyMCparticle.motherPT = mcParticle.mother()->pt();
            MyMCparticle.motherPhi = mcParticle.mother()->phi();
            MyMCparticle.motherEta = mcParticle.mother()->eta();

            if( (mcParticle.mother()->numberOfMothers()==1) ){
                MyMCparticle.grandMotherId = mcParticle.mother()->mother()->pdgId();
                MyMCparticle.grandMotherCharge = mcParticle.mother()->mother()->charge();
                MyMCparticle.grandMotherET = mcParticle.mother()->mother()->et();
                MyMCparticle.grandMotherPT = mcParticle.mother()->mother()->pt();
                MyMCparticle.grandMotherPhi = mcParticle.mother()->mother()->phi();
                MyMCparticle.grandMotherEta = mcParticle.mother()->mother()->eta();
            }
        }
        if( (mcParticle.numberOfMothers()>=1) ){
            const reco::Candidate *Mother0 = mcParticle.mother(0);
            const reco::Candidate *Mother1 = 0;

            if( (mcParticle.numberOfMothers()>=2) ) Mother1 = mcParticle.mother(1);

            int mother0id = Mother0->pdgId();
            int mother1id = ( Mother1!=0 ) ? Mother1->pdgId() : -99;

            bool staytrapped = true;
            while( (mother0id==pdgId || mother1id==pdgId) && staytrapped ){
                if( mother0id==pdgId && (Mother0!=0) ){
                    if( Mother0->numberOfMothers()>=1 ){
                        Mother0 = Mother0->mother(0);
                        mother0id = Mother0->pdgId();
                        mother1id = -99;
                        if( Mother0->numberOfMothers()>=2 ){
                            Mother1 = Mother0->mother(1);
                            mother1id = Mother1->pdgId();
                        }
                    }
                    else staytrapped = false;
                }
                else if( mother1id==pdgId && (Mother1!=0) ){
                    if( Mother1->numberOfMothers()>=1 ){
                        Mother1 = Mother1->mother(0);
                        mother1id = Mother1->pdgId();
                        mother0id = -99;
                        if( Mother1->numberOfMothers()>=2 ){
                            Mother0 = Mother1->mother(1);
                            mother0id = Mother0->pdgId();
                        }
                    }
                    else staytrapped = false;
                }
                else staytrapped = false;
            }

            if( mother0id!=-99 ){
                MyMCparticle.mother0Id = Mother0->pdgId();
                MyMCparticle.mother0Status = Mother0->status();
                MyMCparticle.mother0Charge = Mother0->charge();
                MyMCparticle.mother0ET = Mother0->et();
                MyMCparticle.mother0PT = Mother0->pt();
                MyMCparticle.mother0Phi = Mother0->phi();
                MyMCparticle.mother0Eta = Mother0->eta();

                if( (Mother0->numberOfMothers()>=1) ){
                    const reco::Candidate *GrandMother0 = Mother0->mother(0);
                    const reco::Candidate *GrandMother1 = 0;

                    if( (Mother0->numberOfMothers()>=2) ) GrandMother1 = Mother0->mother(1);

                    int gmother0id = GrandMother0->pdgId();
                    int gmother1id = ( GrandMother1!=0 ) ? GrandMother1->pdgId() : -99;

                    bool staytrapped = true;
                    while( (gmother0id==mother0id || gmother1id==mother0id) && staytrapped ){
                        if( gmother0id==mother0id && (GrandMother0!=0) ){
                            if( GrandMother0->numberOfMothers()>=1 ){
                                GrandMother0 = GrandMother0->mother(0);
                                gmother0id = GrandMother0->pdgId();
                                gmother1id = -99;
                                if( GrandMother0->numberOfMothers()>=2 ){
                                    GrandMother1 = GrandMother0->mother(1);
                                    gmother1id = GrandMother1->pdgId();
                                }
                            }
                            else staytrapped = false;
                        }
                        else if( gmother1id==mother0id && (GrandMother1!=0) ){
                            if( GrandMother1->numberOfMothers()>=1 ){
                                GrandMother1 = GrandMother1->mother(0);
                                gmother1id = GrandMother1->pdgId();
                                gmother0id = -99;
                                if( GrandMother1->numberOfMothers()>=2 ){
                                    GrandMother0 = GrandMother1->mother(1);
                                    gmother0id = GrandMother0->pdgId();
                                }
                            }
                            else staytrapped = false;
                        }
                        else staytrapped = false;
                    }

                    if( gmother0id!=-99 ){
                        MyMCparticle.grandMother00Id = GrandMother0->pdgId();
                        MyMCparticle.grandMother00Status = GrandMother0->status();
                        MyMCparticle.grandMother00Charge = GrandMother0->charge();
                        MyMCparticle.grandMother00ET = GrandMother0->et();
                        MyMCparticle.grandMother00PT = GrandMother0->pt();
                        MyMCparticle.grandMother00Phi = GrandMother0->phi();
                        MyMCparticle.grandMother00Eta = GrandMother0->eta();
                    }
                    if( gmother1id!=-99 ){
                        MyMCparticle.grandMother01Id = GrandMother1->pdgId();
                        MyMCparticle.grandMother01Status = GrandMother1->status();
                        MyMCparticle.grandMother01Charge = GrandMother1->charge();
                        MyMCparticle.grandMother01ET = GrandMother1->et();
                        MyMCparticle.grandMother01PT = GrandMother1->pt();
                        MyMCparticle.grandMother01Phi = GrandMother1->phi();
                        MyMCparticle.grandMother01Eta = GrandMother1->eta();
                    }
                }
            }
            if( mother1id!=-99 ){
                MyMCparticle.mother1Id = Mother1->pdgId();
                MyMCparticle.mother1Status = Mother1->status();
                MyMCparticle.mother1Charge = Mother1->charge();
                MyMCparticle.mother1ET = Mother1->et();
                MyMCparticle.mother1PT = Mother1->pt();
                MyMCparticle.mother1Phi = Mother1->phi();
                MyMCparticle.mother1Eta = Mother1->eta();

                if( (Mother1->numberOfMothers()>=1) ){
                    const reco::Candidate *GrandMother0 = Mother1->mother(0);
                    const reco::Candidate *GrandMother1 = 0;

                    if( (Mother0->numberOfMothers()>=2) ) GrandMother1 = Mother1->mother(1);

                    int gmother0id = GrandMother0->pdgId();
                    int gmother1id = ( GrandMother1!=0 ) ? GrandMother1->pdgId() : -99;

                    bool staytrapped = true;
                    while( (gmother0id==mother1id || gmother1id==mother1id) && staytrapped ){
                        if( gmother0id==mother1id && (GrandMother0!=0) ){
                            if( GrandMother0->numberOfMothers()>=1 ){
                                GrandMother0 = GrandMother0->mother(0);
                                gmother0id = GrandMother0->pdgId();
                                gmother1id = -99;
                                if( GrandMother0->numberOfMothers()>=2 ){
                                    GrandMother1 = GrandMother0->mother(1);
                                    gmother1id = GrandMother1->pdgId();
                                }
                            }
                            else staytrapped = false;
                        }
                        else if( gmother1id==mother1id && (GrandMother1!=0) ){
                            if( GrandMother1->numberOfMothers()>=1 ){
                                GrandMother1 = GrandMother1->mother(0);
                                gmother1id = GrandMother1->pdgId();
                                gmother0id = -99;
                                if( GrandMother1->numberOfMothers()>=2 ){
                                    GrandMother0 = GrandMother1->mother(1);
                                    gmother0id = GrandMother0->pdgId();
                                }
                            }
                            else staytrapped = false;
                        }
                        else staytrapped = false;
                    }

                    if( gmother0id!=-99 ){
                        MyMCparticle.grandMother10Id = GrandMother0->pdgId();
                        MyMCparticle.grandMother10Status = GrandMother0->status();
                        MyMCparticle.grandMother10Charge = GrandMother0->charge();
                        MyMCparticle.grandMother10ET = GrandMother0->et();
                        MyMCparticle.grandMother10PT = GrandMother0->pt();
                        MyMCparticle.grandMother10Phi = GrandMother0->phi();
                        MyMCparticle.grandMother10Eta = GrandMother0->eta();
                    }
                    if( gmother1id!=-99 ){
                        MyMCparticle.grandMother11Id = GrandMother1->pdgId();
                        MyMCparticle.grandMother11Status = GrandMother1->status();
                        MyMCparticle.grandMother11Charge = GrandMother1->charge();
                        MyMCparticle.grandMother11ET = GrandMother1->et();
                        MyMCparticle.grandMother11PT = GrandMother1->pt();
                        MyMCparticle.grandMother11Phi = GrandMother1->phi();
                        MyMCparticle.grandMother11Eta = GrandMother1->eta();
                    }
                }
            }
        }


        if( (mcParticle.numberOfDaughters()>=1) ){
            MyMCparticle.daughter0Id = mcParticle.daughter(0)->pdgId();
            MyMCparticle.daughter0Status = mcParticle.daughter(0)->status();
            MyMCparticle.daughter0Charge = mcParticle.daughter(0)->charge();
            MyMCparticle.daughter0ET = mcParticle.daughter(0)->et();
            MyMCparticle.daughter0PT = mcParticle.daughter(0)->pt();
            MyMCparticle.daughter0Phi = mcParticle.daughter(0)->phi();
            MyMCparticle.daughter0Eta = mcParticle.daughter(0)->eta();

            if( (mcParticle.numberOfDaughters()>=2) ){
                MyMCparticle.daughter1Id = mcParticle.daughter(1)->pdgId();
                MyMCparticle.daughter1Status = mcParticle.daughter(1)->status();
                MyMCparticle.daughter1Charge = mcParticle.daughter(1)->charge();
                MyMCparticle.daughter1ET = mcParticle.daughter(1)->et();
                MyMCparticle.daughter1PT = mcParticle.daughter(1)->pt();
                MyMCparticle.daughter1Phi = mcParticle.daughter(1)->phi();
                MyMCparticle.daughter1Eta = mcParticle.daughter(1)->eta();
            }
        }
        result.push_back(MyMCparticle);
    }
    return result;
}


BNgenjetCollection		PATupleToBEANtranslator::RECOtoBN(reco::GenJetCollection const* iCollection){
    BNgenjetCollection result;
    for(reco::GenJetCollection::const_iterator genjet = iCollection->begin(); genjet!=iCollection->end(); ++genjet ){

        if( !(genjet->pt()>10. && fabs(genjet->eta())<3.5) ) continue;

        BNgenjet MyGenjet;

        MyGenjet.pt = genjet->pt();
        MyGenjet.px = genjet->px();
        MyGenjet.py = genjet->py();
        MyGenjet.pz = genjet->pz();
        MyGenjet.phi = genjet->phi();
        MyGenjet.eta = genjet->eta();
        MyGenjet.et = genjet->et();
        MyGenjet.energy = genjet->energy();
        MyGenjet.mass = genjet->mass();
        MyGenjet.emEnergy = genjet->emEnergy();
        MyGenjet.hadEnergy = genjet->hadEnergy();
        MyGenjet.invisibleEnergy = genjet->invisibleEnergy();
        MyGenjet.auxiliaryEnergy = genjet->auxiliaryEnergy();
        MyGenjet.charge = genjet->charge();

        result.push_back(MyGenjet);
    }
    return result;
}


BNtauCollection			PATupleToBEANtranslator::PATtoBN(
        pat::TauCollection	const* iCollection, 
        reco::Vertex const* primaryVertex
){
    BNtauCollection result;
    math::XYZPoint vertexPosition = primaryVertex->position();
    for( pat::TauCollection::const_iterator tau = iCollection->begin(); tau!=iCollection->end(); ++tau ){

        BNtau MyTau;

        MyTau.px											= tau->px();
        MyTau.py											= tau->py();
        MyTau.pz											= tau->pz();
        MyTau.pt											= tau->pt();
        MyTau.energy										= tau->energy();
        MyTau.et											= tau->et();
        MyTau.eta											= tau->eta();
        MyTau.phi											= tau->phi();
        MyTau.numProngs										= tau->signalPFChargedHadrCands().size();
        MyTau.numSignalGammas								= tau->signalPFGammaCands().size();
        MyTau.numSignalNeutrals								= tau->signalPFNeutrHadrCands().size();
        //MyTau.numSignalPiZeros								= tau->signalPiZeroCandidates().size();
        MyTau.decayMode										= tau->decayMode();
        MyTau.emFraction									= tau->emFraction();
        MyTau.inTheCracks									= tauIsInTheCracks(tau->eta());
        MyTau.HPSagainstElectronLoose						= tau->tauID("againstElectronLoose");
        MyTau.HPSagainstElectronMVA							= tau->tauID("againstElectronMVA");
        MyTau.HPSagainstElectronMedium						= tau->tauID("againstElectronMedium");
        MyTau.HPSagainstElectronTight						= tau->tauID("againstElectronTight");
        MyTau.HPSagainstMuonLoose							= tau->tauID("againstMuonLoose");
        MyTau.HPSagainstMuonMedium							= tau->tauID("againstMuonMedium");
        MyTau.HPSagainstMuonTight							= tau->tauID("againstMuonTight");
        MyTau.HPSbyLooseCombinedIsolationDeltaBetaCorr		= tau->tauID("byLooseCombinedIsolationDeltaBetaCorr");
        MyTau.HPSbyMediumCombinedIsolationDeltaBetaCorr		= tau->tauID("byMediumCombinedIsolationDeltaBetaCorr");
        MyTau.HPSbyTightCombinedIsolationDeltaBetaCorr		= tau->tauID("byTightCombinedIsolationDeltaBetaCorr");
        MyTau.HPSbyVLooseCombinedIsolationDeltaBetaCorr		= tau->tauID("byVLooseCombinedIsolationDeltaBetaCorr");
        MyTau.HPSdecayModeFinding							= tau->tauID("decayModeFinding");

        if(tau->leadPFChargedHadrCand().isNonnull()){
            MyTau.leadingTrackPt				= tau->leadPFChargedHadrCand()->pt();
            MyTau.charge						= tau->leadPFChargedHadrCand()->charge();

            if(tau->leadPFChargedHadrCand()->trackRef().isNonnull()){
                MyTau.leadingTrackValid				= 1;
                MyTau.leadingTrackIpVtdxy			= tau->leadPFChargedHadrCand()->trackRef()->dxy(vertexPosition);
                MyTau.leadingTrackIpVtdz			= tau->leadPFChargedHadrCand()->trackRef()->dz(vertexPosition);
                MyTau.leadingTrackIpVtdxyError		= tau->leadPFChargedHadrCand()->trackRef()->dxyError();
                MyTau.leadingTrackIpVtdzError		= tau->leadPFChargedHadrCand()->trackRef()->dzError();
                MyTau.leadingTrackVx				= tau->leadPFChargedHadrCand()->trackRef()->vx();
                MyTau.leadingTrackVy				= tau->leadPFChargedHadrCand()->trackRef()->vy();
                MyTau.leadingTrackVz				= tau->leadPFChargedHadrCand()->trackRef()->vz();
                MyTau.leadingTrackValidHits			= tau->leadPFChargedHadrCand()->trackRef()->numberOfValidHits();
                MyTau.leadingTrackNormChiSqrd		= tau->leadPFChargedHadrCand()->trackRef()->normalizedChi2();
            }else{
                MyTau.leadingTrackValid				= 0;
                MyTau.leadingTrackIpVtdxy			= -99;
                MyTau.leadingTrackIpVtdz			= -99;
                MyTau.leadingTrackIpVtdxyError		= -99;
                MyTau.leadingTrackIpVtdzError		= -99;
                MyTau.leadingTrackVx				= -99;
                MyTau.leadingTrackVy				= -99;
                MyTau.leadingTrackVz				= -99;
                MyTau.leadingTrackValidHits			= -99;
                MyTau.leadingTrackNormChiSqrd		= -99;
            }
        }else{
            MyTau.leadingTrackValid				= 0;
            MyTau.leadingTrackPt				= -99;
            MyTau.charge						= -99;
            MyTau.leadingTrackIpVtdxy			= -99;
            MyTau.leadingTrackIpVtdz			= -99;
            MyTau.leadingTrackIpVtdxyError		= -99;
            MyTau.leadingTrackIpVtdzError		= -99;
            MyTau.leadingTrackVx				= -99;
            MyTau.leadingTrackVy				= -99;
            MyTau.leadingTrackVz				= -99;
            MyTau.leadingTrackValidHits			= -99;
            MyTau.leadingTrackNormChiSqrd		= -99;
        }
        result.push_back(MyTau);
    }
    return result;
}

BNelectronCollection	PATupleToBEANtranslator::PATtoBN(
        pat::ElectronCollection const* iCollection, 
        reco::Vertex const* primaryVertex,
        reco::BeamSpot const* beamSpot
) {

    math::XYZPoint beamSpotPosition = beamSpot->position();
    float BSx = beamSpot->x0();
    float BSy = beamSpot->y0();
    float BSz = beamSpot->z0();
    
    math::XYZPoint vertexPosition = primaryVertex->position();
    
    BNelectronCollection result;
    for( pat::ElectronCollection::const_iterator ele = iCollection->begin(); ele!=iCollection->end(); ++ele ){

        double elePin = ele->trackMomentumAtVtx().R();
        double elePout = ele->trackMomentumOut().R();

        BNelectron MyElectron;

        // general kinematic variables
        MyElectron.energy = ele->energy();
        MyElectron.gsfEt = ele->et();
        MyElectron.pt = ele->pt();
        MyElectron.px = ele->px();
        MyElectron.py = ele->py();
        MyElectron.pz = ele->pz();
        MyElectron.phi = ele->phi();
        MyElectron.eta = ele->eta();
        MyElectron.theta = ele->theta();

        MyElectron.charge = ele->charge();
        MyElectron.classification = ele->classification();
        MyElectron.vx = ele->vx();
        MyElectron.vy = ele->vy();
        MyElectron.vz = ele->vz();

        MyElectron.pIn = elePin;
        MyElectron.pOut = elePout;
        MyElectron.EscOverPin = ele->eSuperClusterOverP();
        MyElectron.EseedOverPout = ele->eSeedClusterOverPout();
        MyElectron.hadOverEm = ele->hadronicOverEm();
        MyElectron.fbrem = fabs(elePin-elePout)/elePin;
        MyElectron.absInvEMinusInvPin = fabs( 1/ele->ecalEnergy()-(ele->eSuperClusterOverP()/ele->ecalEnergy()) );
        MyElectron.delPhiIn = ele->deltaPhiSuperClusterTrackAtVtx();
        MyElectron.delEtaIn = ele->deltaEtaSuperClusterTrackAtVtx();

        MyElectron.trackIso = ele->trackIso();
        MyElectron.ecalIso = ele->ecalIso();
        MyElectron.hcalIso = ele->hcalIso();
        MyElectron.caloIso = ele->caloIso();

        MyElectron.trackIsoDR03 = ele->dr03TkSumPt();
        MyElectron.ecalIsoDR03 = ele->dr03EcalRecHitSumEt();
        MyElectron.hcalIsoDR03 = ele->dr03HcalTowerSumEt();
        MyElectron.hcalIsoDR03depth1 = ele->dr03HcalDepth1TowerSumEt();
        MyElectron.hcalIsoDR03depth2 = ele->dr03HcalDepth2TowerSumEt();
        MyElectron.caloIsoDR03 = ele->dr03EcalRecHitSumEt()+ele->dr03HcalTowerSumEt();

        MyElectron.trackIsoDR04 = ele->dr04TkSumPt();
        MyElectron.ecalIsoDR04 = ele->dr04EcalRecHitSumEt();
        MyElectron.hcalIsoDR04 = ele->dr04HcalTowerSumEt();
        MyElectron.hcalIsoDR04depth1 = ele->dr04HcalDepth1TowerSumEt();
        MyElectron.hcalIsoDR04depth2 = ele->dr04HcalDepth2TowerSumEt();
        MyElectron.caloIsoDR04 = ele->dr04EcalRecHitSumEt()+ele->dr04HcalTowerSumEt();

        MyElectron.mva = ele->mva();
        MyElectron.mvaTrigV0 = ele->electronID("mvaTrigV0");
        MyElectron.mvaNonTrigV0 = ele->electronID("mvaNonTrigV0");
        MyElectron.numberOfLostHits = ele->gsfTrack()->trackerExpectedHitsInner().numberOfLostHits();
        MyElectron.numberOfExpectedInnerHits = ele->gsfTrack()->trackerExpectedHitsInner().numberOfHits();
        MyElectron.numberOfValidPixelHits = ele->gsfTrack()->trackerExpectedHitsInner().numberOfValidPixelHits();
        MyElectron.numberOfValidPixelBarrelHits = ele->gsfTrack()->trackerExpectedHitsInner().numberOfValidPixelBarrelHits();
        MyElectron.numberOfValidPixelEndcapHits = ele->gsfTrack()->trackerExpectedHitsInner().numberOfValidPixelEndcapHits();

        MyElectron.scEnergy = ele->caloEnergy();
        MyElectron.scSigmaEtaEta = ele->scSigmaEtaEta();
        MyElectron.scSigmaIEtaIEta = ele->scSigmaIEtaIEta();
        MyElectron.scE1x5 = ele->scE1x5();
        MyElectron.scE2x5Max = ele->scE2x5Max();
        MyElectron.scE5x5 = ele->scE5x5();
        MyElectron.numClusters = ele->numberOfBrems();

        MyElectron.IP = ele->dB(pat::Electron::PV3D);
        MyElectron.IPError = ele->edB(pat::Electron::PV3D);

        double caloenergy = -1;

        if( (ele->superCluster().isAvailable()) ){
            /* don't have easy access to Event 
            double eMax    = lazyTools.eMax(    *(ele->superCluster()) );
            double eLeft   = lazyTools.eLeft(   *(ele->superCluster()) );
            double eRight  = lazyTools.eRight(  *(ele->superCluster()) );
            double eTop    = lazyTools.eTop(    *(ele->superCluster()) );
            double eBottom = lazyTools.eBottom( *(ele->superCluster()) );
            double e3x3    = lazyTools.e3x3(    *(ele->superCluster()) );
            double swissCross = -99;

            if( eMax>0.000001 ) swissCross = 1 - (eLeft+eRight+eTop+eBottom)/eMax;

            MyElectron.eMax = eMax;
            MyElectron.eLeft = eLeft;
            MyElectron.eRight = eRight;
            MyElectron.eTop = eTop;
            MyElectron.eBottom = eBottom;
            MyElectron.e3x3 = e3x3;
            MyElectron.swissCross = swissCross;
            */
            caloenergy = ele->caloEnergy();

            MyElectron.scEt = ele->caloEnergy() * sin( ele->superCluster()->position().theta() );
            MyElectron.scRawEnergy = ele->superCluster()->rawEnergy();
            MyElectron.scEta = ele->superCluster()->position().eta();
            MyElectron.scPhi = ele->superCluster()->position().phi();
            MyElectron.scZ = ele->superCluster()->position().Z();

            double seedE = -999, seedTime = -999;
            int seedRecoFlag = -999;
            /* don't have the neccesary collections
            if( (ele->isEB()) ){
                DetId idEB = EcalClusterTools::getMaximum( ele->superCluster()->hitsAndFractions(), &(*barrelRecHits) ).first;
                EcalRecHitCollection::const_iterator thisHitEB = barrelRecHits->find(idEB);

                seedE = thisHitEB->energy();
                seedTime = thisHitEB->time();
                seedRecoFlag = thisHitEB->recoFlag();
            }
            else if( (ele->isEE()) ){
                DetId idEE = EcalClusterTools::getMaximum( ele->superCluster()->hitsAndFractions(), &(*endcapRecHits) ).first;
                EcalRecHitCollection::const_iterator thisHitEE = endcapRecHits->find(idEE);

                seedE = thisHitEE->energy();
                seedTime = thisHitEE->time();
                seedRecoFlag = thisHitEE->recoFlag();
            }
            */
            MyElectron.seedEnergy   = seedE;
            MyElectron.seedTime     = seedTime;
            MyElectron.seedRecoFlag = seedRecoFlag;
        }

        double heepEt = ( caloenergy<0 || ele->energy()==0. ) ? 0 : ele->et()/ele->energy()*caloenergy;
        MyElectron.et = heepEt;

        if( (ele->closestCtfTrackRef().isAvailable()) ) MyElectron.tkCharge = ele->closestCtfTrackRef()->charge();
        if( (ele->gsfTrack().isAvailable()) ){
            double tkvx = ele->gsfTrack()->vx();
            double tkvy = ele->gsfTrack()->vy();
            double tkpx = ele->gsfTrack()->px();
            double tkpy = ele->gsfTrack()->py();
            double tkpt = ele->gsfTrack()->pt();

            double ndof = ele->gsfTrack()->ndof();
            if( (ndof!=0) ) MyElectron.tkNormChi2 = ele->gsfTrack()->chi2()/ndof;
            MyElectron.tkPT = ele->gsfTrack()->pt();
            MyElectron.tkEta = ele->gsfTrack()->eta();
            MyElectron.tkPhi = ele->gsfTrack()->phi();
            MyElectron.tkDZ = ele->gsfTrack()->dz();
            MyElectron.tkD0 = ele->gsfTrack()->d0();
            MyElectron.tkD0bs = (tkvx-BSx)*tkpy/tkpt-(tkvy-BSy)*tkpx/tkpt;
            MyElectron.tkD0err = ele->gsfTrack()->d0Error();
            MyElectron.tkNumValidHits = ele->gsfTrack()->numberOfValidHits();
            MyElectron.gsfCharge = ele->gsfTrack()->charge();

            MyElectron.correctedD0 = ele->gsfTrack()->dxy(beamSpotPosition);
            MyElectron.correctedD0Vertex = ele->gsfTrack()->dxy(vertexPosition);
            MyElectron.correctedDZ = ele->gsfTrack()->dz(vertexPosition);
        }

        MyElectron.isEB = ele->isEB();
        MyElectron.isEE = ele->isEE();
        MyElectron.isGap = ele->isGap();
        MyElectron.isEBEEGap = ele->isEBEEGap();
        MyElectron.isEBGap = ele->isEBGap();
        MyElectron.isEEGap = ele->isEEGap();
        MyElectron.isEcalDriven = ele->ecalDrivenSeed();
        MyElectron.isTrackerDriven = ele->trackerDrivenSeed();

        if( (ele->genLepton()) ){
            int genId = ele->genLepton()->pdgId();

            MyElectron.genId = ele->genLepton()->pdgId();
            MyElectron.genET = ele->genLepton()->et();
            MyElectron.genPT = ele->genLepton()->pt();
            MyElectron.genPhi = ele->genLepton()->phi();
            MyElectron.genEta = ele->genLepton()->eta();
            MyElectron.genCharge = ele->genLepton()->charge();

            MyElectron.genNumberOfMothers = ele->genLepton()->numberOfMothers();

            if( (ele->genLepton()->numberOfMothers()>0) ){
                const reco::Candidate *ElectronMother = ele->genLepton()->mother();
                bool staytrapped = true;
                while( (ElectronMother->pdgId()==genId && staytrapped) ){
                    if( ElectronMother->numberOfMothers()>=1 ) ElectronMother = ElectronMother->mother();
                    else staytrapped = false;
                }

                MyElectron.genMotherId = ElectronMother->pdgId();
                MyElectron.genMotherET = ElectronMother->et();
                MyElectron.genMotherPT = ElectronMother->pt();
                MyElectron.genMotherPhi = ElectronMother->phi();
                MyElectron.genMotherEta = ElectronMother->eta();
                MyElectron.genMotherCharge = ElectronMother->charge();
            }

            if( (ele->genLepton()->numberOfMothers()>=1) ){
                const reco::Candidate *ElectronMother0 = ele->genLepton()->mother(0);
                const reco::Candidate *ElectronMother1 = 0;

                if( (ele->genLepton()->numberOfMothers()>=2) ) ElectronMother1 = ele->genLepton()->mother(1);

                int mother0id = ElectronMother0->pdgId();
                int mother1id = ( ElectronMother1!=0 ) ? ElectronMother1->pdgId() : -99;

                bool staytrapped = true;
                while( (mother0id==genId || mother1id==genId) && staytrapped ){
                    if( mother0id==genId && (ElectronMother0!=0) ){
                        if( ElectronMother0->numberOfMothers()>=1 ){
                            ElectronMother0 = ElectronMother0->mother(0);
                            mother0id = ElectronMother0->pdgId();
                            mother1id = -99;
                            if( ElectronMother0->numberOfMothers()>=2 ){
                                ElectronMother1 = ElectronMother0->mother(1);
                                mother1id = ElectronMother1->pdgId();
                            }
                        }
                        else staytrapped = false;
                    }
                    else if( mother1id==genId && (ElectronMother1!=0) ){
                        if( ElectronMother1->numberOfMothers()>=1 ){
                            ElectronMother1 = ElectronMother1->mother(0);
                            mother1id = ElectronMother1->pdgId();
                            mother0id = -99;
                            if( ElectronMother1->numberOfMothers()>=2 ){
                                ElectronMother0 = ElectronMother1->mother(1);
                                mother0id = ElectronMother0->pdgId();
                            }
                        }
                        else staytrapped = false;
                    }
                    else staytrapped = false;
                }

                if( mother0id!=-99 ){
                    MyElectron.genMother0Id = ElectronMother0->pdgId();

                    if( (ElectronMother0->numberOfMothers()>=1) ){
                        const reco::Candidate *ElectronGrandMother0 = ElectronMother0->mother(0);
                        const reco::Candidate *ElectronGrandMother1 = 0;

                        if( (ElectronMother0->numberOfMothers()>=2) ) ElectronGrandMother1 = ElectronMother0->mother(1);

                        int gmother0id = ElectronGrandMother0->pdgId();
                        int gmother1id = ( ElectronGrandMother1!=0 ) ? ElectronGrandMother1->pdgId() : -99;

                        bool staytrapped = true;
                        while( (gmother0id==mother0id || gmother1id==mother0id) && staytrapped ){
                            if( gmother0id==mother0id && (ElectronGrandMother0!=0) ){
                                if( ElectronGrandMother0->numberOfMothers()>=1 ){
                                    ElectronGrandMother0 = ElectronGrandMother0->mother(0);
                                    gmother0id = ElectronGrandMother0->pdgId();
                                    gmother1id = -99;
                                    if( ElectronGrandMother0->numberOfMothers()>=2 ){
                                        ElectronGrandMother1 = ElectronGrandMother0->mother(1);
                                        gmother1id = ElectronGrandMother1->pdgId();
                                    }
                                }
                                else staytrapped = false;
                            }
                            else if( gmother1id==mother0id && (ElectronGrandMother1!=0) ){
                                if( ElectronGrandMother1->numberOfMothers()>=1 ){
                                    ElectronGrandMother1 = ElectronGrandMother1->mother(0);
                                    gmother1id = ElectronGrandMother1->pdgId();
                                    gmother0id = -99;
                                    if( ElectronGrandMother1->numberOfMothers()>=2 ){
                                        ElectronGrandMother0 = ElectronGrandMother1->mother(1);
                                        gmother0id = ElectronGrandMother0->pdgId();
                                    }
                                }
                                else staytrapped = false;
                            }
                            else staytrapped = false;
                        }

                        MyElectron.genGrandMother00Id = gmother0id;
                        MyElectron.genGrandMother01Id = gmother1id;
                    }
                }
                if( mother1id!=-99 ){
                    MyElectron.genMother1Id = ElectronMother1->pdgId();

                    if( (ElectronMother1->numberOfMothers()>=1) ){
                        const reco::Candidate *ElectronGrandMother0 = ElectronMother1->mother(0);
                        const reco::Candidate *ElectronGrandMother1 = 0;

                        if( (ElectronMother0->numberOfMothers()>=2) ) ElectronGrandMother1 = ElectronMother1->mother(1);

                        int gmother0id = ElectronGrandMother0->pdgId();
                        int gmother1id = ( ElectronGrandMother1!=0 ) ? ElectronGrandMother1->pdgId() : -99;

                        bool staytrapped = true;
                        while( (gmother0id==mother1id || gmother1id==mother1id) && staytrapped ){
                            if( gmother0id==mother1id && (ElectronGrandMother0!=0) ){
                                if( ElectronGrandMother0->numberOfMothers()>=1 ){
                                    ElectronGrandMother0 = ElectronGrandMother0->mother(0);
                                    gmother0id = ElectronGrandMother0->pdgId();
                                    gmother1id = -99;
                                    if( ElectronGrandMother0->numberOfMothers()>=2 ){
                                        ElectronGrandMother1 = ElectronGrandMother0->mother(1);
                                        gmother1id = ElectronGrandMother1->pdgId();
                                    }
                                }
                                else staytrapped = false;
                            }
                            else if( gmother1id==mother1id && (ElectronGrandMother1!=0) ){
                                if( ElectronGrandMother1->numberOfMothers()>=1 ){
                                    ElectronGrandMother1 = ElectronGrandMother1->mother(0);
                                    gmother1id = ElectronGrandMother1->pdgId();
                                    gmother0id = -99;
                                    if( ElectronGrandMother1->numberOfMothers()>=2 ){
                                        ElectronGrandMother0 = ElectronGrandMother1->mother(1);
                                        gmother0id = ElectronGrandMother0->pdgId();
                                    }
                                }
                                else staytrapped = false;
                            }
                            else staytrapped = false;
                        }

                        MyElectron.genGrandMother10Id = gmother0id;
                        MyElectron.genGrandMother11Id = gmother1id;
                    }
                }
            }

        }// end check if genLepton

        /*
           ConversionFinder convFinder;
           ConversionInfo convInfo = convFinder.getConversionInfo(*ele, trackHandle, evt_bField);

           double dist = convInfo.dist();
           double dcot = convInfo.dcot();
           double convradius = convInfo.radiusOfConversion();
           math::XYZPoint convPoint = convInfo.pointOfConversion();

           MyElectron.dist = dist;
           MyElectron.dcot = dcot;
           MyElectron.convradius = convradius;
           MyElectron.convPointX = convPoint.x();
           MyElectron.convPointY = convPoint.y();
           MyElectron.convPointZ = convPoint.z();
           MyElectron.passConvVeto = ele->passConversionVeto();
         */

        bool cutDelEta=false, cutDelPhi=false, cutSigIeta=false, cutE2x5=false, cutEMhad1=false, cutHad2=false, cutTrackIso=false;

        double absEta = fabs(ele->superCluster()->position().eta());
        double EMhad1 = ele->dr03EcalRecHitSumEt() + ele->dr03HcalDepth1TowerSumEt();
        bool EB = ( absEta < 1.442 );
        bool EE = ( absEta > 1.560 && absEta < 2.5 );

        bool isECAL = ele->ecalDrivenSeed();

        bool cutET = ( heepEt > 25. );
        bool cutEta = ( EB || EE );
        bool cutHoverE = ( ele->hadronicOverEm() < 0.05 );

        if( EB ){
            cutDelEta = ( fabs(ele->deltaEtaSuperClusterTrackAtVtx())<0.005 );
            cutDelPhi = ( fabs(ele->deltaPhiSuperClusterTrackAtVtx())<0.09 );
            cutSigIeta = true;
            cutE2x5 = ( (ele->scE2x5Max()/ele->scE5x5())>0.94 || (ele->scE1x5()/ele->scE5x5())>0.83 );
            cutEMhad1 = ( EMhad1 < (2 + 0.03*heepEt) );
            cutHad2 = true;
            cutTrackIso = ( ele->dr03TkSumPt()<7.5 );
        }
        else if( EE ){
            cutDelEta = ( fabs(ele->deltaEtaSuperClusterTrackAtVtx())<0.007 );
            cutDelPhi = ( fabs(ele->deltaPhiSuperClusterTrackAtVtx())<0.09 );
            cutSigIeta = ( ele->scSigmaIEtaIEta()<0.03 );
            cutE2x5 = true;
            if( heepEt<50 ) cutEMhad1 = ( EMhad1 < 2.5 );
            else cutEMhad1 = ( EMhad1 < (2.5 + 0.03*(heepEt-50)) );
            cutHad2 = ( ele->dr03HcalDepth2TowerSumEt()<0.5 );
            cutTrackIso = ( ele->dr03TkSumPt()<15. );
        }

        bool isHEEPnoEt = ( isECAL && cutEta && cutDelEta && cutDelPhi && cutHoverE &&  
                cutSigIeta && cutE2x5 && cutEMhad1 && cutHad2 && cutTrackIso );
        bool isHEEP = ( isHEEPnoEt && cutET );


        MyElectron.isHEEP = ( isHEEP ) ? 1 : 0;
        MyElectron.isHEEPnoEt = ( isHEEPnoEt ) ? 1 : 0;

        result.push_back(MyElectron);

    }
    return result;
}


BNmuonCollection		PATupleToBEANtranslator::PATtoBN(
        pat::MuonCollection const* iCollection, 
        reco::Vertex const* primaryVertex,
        reco::BeamSpot const* beamSpot
){
    math::XYZPoint beamSpotPosition = beamSpot->position();
    double BSx = beamSpot->x0();
    double BSy = beamSpot->y0();
    double BSz = beamSpot->z0();
    
    math::XYZPoint vertexPosition = primaryVertex->position();
    double PVx = primaryVertex->x();
    double PVy = primaryVertex->y();
    double PVz = primaryVertex->z();
    
    BNmuonCollection result;
    for( pat::MuonCollection::const_iterator muon = iCollection->begin(); muon!=iCollection->end(); ++muon ){

        BNmuon MyMuon;

        // general kinematic variables
        MyMuon.energy = muon->energy();
        MyMuon.et = muon->et();
        MyMuon.pt = muon->pt();
        MyMuon.px = muon->px();
        MyMuon.py = muon->py();
        MyMuon.pz = muon->pz();
        MyMuon.phi = muon->phi();
        MyMuon.eta = muon->eta();
        MyMuon.theta = muon->theta();


        MyMuon.charge = muon->charge();
        MyMuon.vx = muon->vx();
        MyMuon.vy = muon->vy();
        MyMuon.vz = muon->vz();

        MyMuon.trackIso = muon->trackIso();
        MyMuon.ecalIso = muon->ecalIso();
        MyMuon.hcalIso = muon->hcalIso();
        MyMuon.caloIso = muon->caloIso();

        MyMuon.trackIsoDR03 = muon->isolationR03().sumPt;
        MyMuon.ecalIsoDR03 = muon->isolationR03().emEt;
        MyMuon.hcalIsoDR03 = muon->isolationR03().hadEt;
        MyMuon.caloIsoDR03 = muon->isolationR03().emEt + muon->isolationR03().hadEt;

        MyMuon.trackVetoIsoDR03 = muon->isolationR03().trackerVetoPt;
        MyMuon.ecalVetoIsoDR03 = muon->isolationR03().emVetoEt;
        MyMuon.hcalVetoIsoDR03 = muon->isolationR03().hadVetoEt;
        MyMuon.caloVetoIsoDR03 = muon->isolationR03().emVetoEt + muon->isolationR03().hadVetoEt;

        MyMuon.trackIsoDR05 = muon->isolationR05().sumPt;
        MyMuon.ecalIsoDR05 = muon->isolationR05().emEt;
        MyMuon.hcalIsoDR05 = muon->isolationR05().hadEt;
        MyMuon.caloIsoDR05 = muon->isolationR05().emEt + muon->isolationR05().hadEt;

        MyMuon.trackVetoIsoDR05 = muon->isolationR05().trackerVetoPt;
        MyMuon.ecalVetoIsoDR05 = muon->isolationR05().emVetoEt;
        MyMuon.hcalVetoIsoDR05 = muon->isolationR05().hadVetoEt;
        MyMuon.caloVetoIsoDR05 = muon->isolationR05().emVetoEt + muon->isolationR05().hadVetoEt;

        MyMuon.timeAtIpInOut = muon->time().timeAtIpInOut;
        MyMuon.timeAtIpInOutErr = muon->time().timeAtIpInOutErr;
        MyMuon.timeAtIpOutIn = muon->time().timeAtIpOutIn;
        MyMuon.timeAtIpOutInErr = muon->time().timeAtIpOutInErr;
        MyMuon.time_ndof = muon->time().nDof;

        if( muon->isEnergyValid() ){
            MyMuon.ecal_time = muon->calEnergy().ecal_time;
            MyMuon.hcal_time = muon->calEnergy().hcal_time;
            MyMuon.ecal_timeError = muon->calEnergy().ecal_timeError;
            MyMuon.hcal_timeError = muon->calEnergy().hcal_timeError;
            MyMuon.energy_ecal = muon->calEnergy().em;
            MyMuon.energy_hcal = muon->calEnergy().had;
            MyMuon.e3x3_ecal = muon->calEnergy().emS9;
            MyMuon.e3x3_hcal = muon->calEnergy().hadS9;
            MyMuon.energyMax_ecal = muon->calEnergy().emMax;
            MyMuon.energyMax_hcal = muon->calEnergy().hadMax;
        }



        MyMuon.IDGMPTight = ( muon->isGood("GlobalMuonPromptTight") ) ? 1 : 0;

        MyMuon.isGlobalMuon = ( muon->isGlobalMuon() ) ? 1 : 0;
        MyMuon.isTrackerMuon = ( muon->isTrackerMuon() ) ? 1 : 0;
        MyMuon.isStandAloneMuon = ( muon->isStandAloneMuon() ) ? 1 : 0;
        MyMuon.isGlobalMuonPromptTight = ( muon->isGood("GlobalMuonPromptTight") ) ? 1 : 0;

        MyMuon.numberOfMatches = muon->numberOfMatches();
        MyMuon.numberOfMatchedStations = muon->numberOfMatchedStations();
    
        MyMuon.dVzPVz = muon->vz() - PVz;
        MyMuon.dB = muon->dB();

        MyMuon.IP = muon->dB(pat::Muon::PV3D);
        MyMuon.IPError = muon->edB(pat::Muon::PV3D);


        if( (muon->globalTrack().isAvailable()) ){
            MyMuon.normalizedChi2 = muon->globalTrack()->normalizedChi2();
            MyMuon.numberOfValidMuonHits = muon->globalTrack()->hitPattern().numberOfValidMuonHits();
            MyMuon.numberOfValidTrackerHits = muon->globalTrack()->hitPattern().numberOfValidTrackerHits();
            MyMuon.numberOfLayersWithMeasurement = muon->track()->hitPattern().trackerLayersWithMeasurement();
            MyMuon.ptErr = muon->globalTrack()->ptError();
        }
        if( (muon->innerTrack().isAvailable()) ){
            MyMuon.numberOfValidTrackerHitsInnerTrack = muon->innerTrack()->numberOfValidHits();
            MyMuon.pixelLayersWithMeasurement = muon->innerTrack()->hitPattern().pixelLayersWithMeasurement();
            MyMuon.numberOfValidPixelHits = muon->innerTrack()->hitPattern().numberOfValidPixelHits();

            MyMuon.correctedD0 = muon->innerTrack()->dxy(beamSpotPosition);
            MyMuon.correctedD0Vertex = muon->innerTrack()->dxy(vertexPosition);
            MyMuon.correctedDZ = muon->innerTrack()->dz(vertexPosition);
        }

        // Get track muon info
        if( (muon->track().isAvailable()) ){
            double tkvx = muon->track()->vx();
            double tkvy = muon->track()->vy();
            double tkpx = muon->track()->px();
            double tkpy = muon->track()->py();
            double tkpt = muon->track()->pt();

            double ndof = muon->track()->ndof();
            if( (ndof!=0) ) MyMuon.tkNormChi2 = muon->track()->chi2()/ndof;
            MyMuon.tkPT = muon->track()->pt();
            MyMuon.tkEta = muon->track()->eta();
            MyMuon.tkPhi = muon->track()->phi();
            MyMuon.tkDZ = muon->track()->dz();
            MyMuon.tkD0 = muon->track()->d0();
            MyMuon.tkD0bs = (tkvx-BSx)*tkpy/tkpt-(tkvy-BSy)*tkpx/tkpt;
            MyMuon.tkD0err = muon->track()->d0Error();
            MyMuon.tkNumValidHits = muon->track()->numberOfValidHits();
            MyMuon.tkCharge = muon->track()->charge();
        }
        // Get standalone muon info
        if( (muon->standAloneMuon().isAvailable()) ){
            double samvx = muon->standAloneMuon()->vx();
            double samvy = muon->standAloneMuon()->vy();
            double sampx = muon->standAloneMuon()->px();
            double sampy = muon->standAloneMuon()->py();
            double sampt = muon->standAloneMuon()->pt();

            double ndof = muon->standAloneMuon()->ndof();
            if( (ndof!=0) ) MyMuon.samNormChi2 = muon->standAloneMuon()->chi2()/ndof;
            MyMuon.samPT = muon->standAloneMuon()->pt();
            MyMuon.samEta = muon->standAloneMuon()->eta();
            MyMuon.samPhi = muon->standAloneMuon()->phi();
            MyMuon.samDZ = muon->standAloneMuon()->dz();
            MyMuon.samD0 = muon->standAloneMuon()->d0();
            MyMuon.samD0bs = (samvx-BSx)*sampy/sampt-(samvy-BSy)*sampx/sampt;
            MyMuon.samD0err = muon->standAloneMuon()->d0Error();
            MyMuon.samNumValidHits = muon->standAloneMuon()->numberOfValidHits();
            MyMuon.samCharge = muon->standAloneMuon()->charge();
        }
        // Get global muon info
        if( (muon->combinedMuon().isAvailable()) ){
            double comvx = muon->combinedMuon()->vx();
            double comvy = muon->combinedMuon()->vy();
            double compx = muon->combinedMuon()->px();
            double compy = muon->combinedMuon()->py();
            double compt = muon->combinedMuon()->pt();

            double ndof = muon->combinedMuon()->ndof();
            if( (ndof!=0) ) MyMuon.comNormChi2 = muon->combinedMuon()->chi2()/ndof;
            MyMuon.comPT = muon->combinedMuon()->pt();
            MyMuon.comEta = muon->combinedMuon()->eta();
            MyMuon.comPhi = muon->combinedMuon()->phi();
            MyMuon.comDZ = muon->combinedMuon()->dz();
            MyMuon.comD0 = muon->combinedMuon()->d0();
            MyMuon.comD0bs = (comvx-BSx)*compy/compt-(comvy-BSy)*compx/compt;
            MyMuon.comD0err = muon->combinedMuon()->d0Error();
            MyMuon.comNumValidHits = muon->combinedMuon()->numberOfValidHits();
            MyMuon.comCharge = muon->combinedMuon()->charge();
        }

        if( (muon->genLepton()) ){
            int genId = muon->genLepton()->pdgId();

            MyMuon.genId = muon->genLepton()->pdgId();
            MyMuon.genET = muon->genLepton()->et();
            MyMuon.genPT = muon->genLepton()->pt();
            MyMuon.genPhi = muon->genLepton()->phi();
            MyMuon.genEta = muon->genLepton()->eta();
            MyMuon.genCharge = muon->genLepton()->charge();

            MyMuon.genNumberOfMothers = muon->genLepton()->numberOfMothers();

            if( (muon->genLepton()->numberOfMothers()>0) ){
                const reco::Candidate *MuonMother = muon->genLepton()->mother();
                bool staytrapped = true;
                while( (MuonMother->pdgId()==genId && staytrapped) ){
                    if( MuonMother->numberOfMothers()>=1 ) MuonMother = MuonMother->mother();
                    else staytrapped = false;
                }

                MyMuon.genMotherId = MuonMother->pdgId();
                MyMuon.genMotherET = MuonMother->et();
                MyMuon.genMotherPT = MuonMother->pt();
                MyMuon.genMotherPhi = MuonMother->phi();
                MyMuon.genMotherEta = MuonMother->eta();
                MyMuon.genMotherCharge = MuonMother->charge();
            }

            if( (muon->genLepton()->numberOfMothers()>=1) ){
                const reco::Candidate *MuonMother0 = muon->genLepton()->mother(0);
                const reco::Candidate *MuonMother1 = 0;

                if( (muon->genLepton()->numberOfMothers()>=2) ) MuonMother1 = muon->genLepton()->mother(1);

                int mother0id = MuonMother0->pdgId();
                int mother1id = ( MuonMother1!=0 ) ? MuonMother1->pdgId() : -99;

                bool staytrapped = true;
                while( (mother0id==genId || mother1id==genId) && staytrapped ){
                    if( mother0id==genId && (MuonMother0!=0) ){
                        if( MuonMother0->numberOfMothers()>=1 ){
                            MuonMother0 = MuonMother0->mother(0);
                            mother0id = MuonMother0->pdgId();
                            mother1id = -99;
                            if( MuonMother0->numberOfMothers()>=2 ){
                                MuonMother1 = MuonMother0->mother(1);
                                mother1id = MuonMother1->pdgId();
                            }
                        }
                        else staytrapped = false;
                    }
                    else if( mother1id==genId && (MuonMother1!=0) ){
                        if( MuonMother1->numberOfMothers()>=1 ){
                            MuonMother1 = MuonMother1->mother(0);
                            mother1id = MuonMother1->pdgId();
                            mother0id = -99;
                            if( MuonMother1->numberOfMothers()>=2 ){
                                MuonMother0 = MuonMother1->mother(1);
                                mother0id = MuonMother0->pdgId();
                            }
                        }
                        else staytrapped = false;
                    }
                    else staytrapped = false;
                }

                if( mother0id!=-99 ){
                    MyMuon.genMother0Id = MuonMother0->pdgId();

                    if( (MuonMother0->numberOfMothers()>=1) ){
                        const reco::Candidate *MuonGrandMother0 = MuonMother0->mother(0);
                        const reco::Candidate *MuonGrandMother1 = 0;

                        if( (MuonMother0->numberOfMothers()>=2) ) MuonGrandMother1 = MuonMother0->mother(1);

                        int gmother0id = MuonGrandMother0->pdgId();
                        int gmother1id = ( MuonGrandMother1!=0 ) ? MuonGrandMother1->pdgId() : -99;

                        bool staytrapped = true;
                        while( (gmother0id==mother0id || gmother1id==mother0id) && staytrapped ){
                            if( gmother0id==mother0id && (MuonGrandMother0!=0) ){
                                if( MuonGrandMother0->numberOfMothers()>=1 ){
                                    MuonGrandMother0 = MuonGrandMother0->mother(0);
                                    gmother0id = MuonGrandMother0->pdgId();
                                    gmother1id = -99;
                                    if( MuonGrandMother0->numberOfMothers()>=2 ){
                                        MuonGrandMother1 = MuonGrandMother0->mother(1);
                                        gmother1id = MuonGrandMother1->pdgId();
                                    }
                                }
                                else staytrapped = false;
                            }
                            else if( gmother1id==mother0id && (MuonGrandMother1!=0) ){
                                if( MuonGrandMother1->numberOfMothers()>=1 ){
                                    MuonGrandMother1 = MuonGrandMother1->mother(0);
                                    gmother1id = MuonGrandMother1->pdgId();
                                    gmother0id = -99;
                                    if( MuonGrandMother1->numberOfMothers()>=2 ){
                                        MuonGrandMother0 = MuonGrandMother1->mother(1);
                                        gmother0id = MuonGrandMother0->pdgId();
                                    }
                                }
                                else staytrapped = false;
                            }
                            else staytrapped = false;
                        }

                        MyMuon.genGrandMother00Id = gmother0id;
                        MyMuon.genGrandMother01Id = gmother1id;
                    }
                }
                if( mother1id!=-99 ){
                    MyMuon.genMother1Id = MuonMother1->pdgId();

                    if( (MuonMother1->numberOfMothers()>=1) ){
                        const reco::Candidate *MuonGrandMother0 = MuonMother1->mother(0);
                        const reco::Candidate *MuonGrandMother1 = 0;

                        if( (MuonMother0->numberOfMothers()>=2) ) MuonGrandMother1 = MuonMother1->mother(1);

                        int gmother0id = MuonGrandMother0->pdgId();
                        int gmother1id = ( MuonGrandMother1!=0 ) ? MuonGrandMother1->pdgId() : -99;

                        bool staytrapped = true;
                        while( (gmother0id==mother1id || gmother1id==mother1id) && staytrapped ){
                            if( gmother0id==mother1id && (MuonGrandMother0!=0) ){
                                if( MuonGrandMother0->numberOfMothers()>=1 ){
                                    MuonGrandMother0 = MuonGrandMother0->mother(0);
                                    gmother0id = MuonGrandMother0->pdgId();
                                    gmother1id = -99;
                                    if( MuonGrandMother0->numberOfMothers()>=2 ){
                                        MuonGrandMother1 = MuonGrandMother0->mother(1);
                                        gmother1id = MuonGrandMother1->pdgId();
                                    }
                                }
                                else staytrapped = false;
                            }
                            else if( gmother1id==mother1id && (MuonGrandMother1!=0) ){
                                if( MuonGrandMother1->numberOfMothers()>=1 ){
                                    MuonGrandMother1 = MuonGrandMother1->mother(0);
                                    gmother1id = MuonGrandMother1->pdgId();
                                    gmother0id = -99;
                                    if( MuonGrandMother1->numberOfMothers()>=2 ){
                                        MuonGrandMother0 = MuonGrandMother1->mother(1);
                                        gmother0id = MuonGrandMother0->pdgId();
                                    }
                                }
                                else staytrapped = false;
                            }
                            else staytrapped = false;
                        }

                        MyMuon.genGrandMother10Id = gmother0id;
                        MyMuon.genGrandMother11Id = gmother1id;
                    }
                }
            }

        }// end check if genLepton

        result.push_back(MyMuon);
    }
    return result;
}


BNjetCollection			PATupleToBEANtranslator::PATtoBN(
        pat::JetCollection const* iCollection,
        reco::Vertex const* primaryVertex,
        const edm::Event& event,
        const edm::EventSetup& eventSetup
){
    math::XYZPoint vertexPosition = primaryVertex->position();
    double PVx = primaryVertex->x();
    double PVy = primaryVertex->y();
    double PVz = primaryVertex->z();
    
    BNjetCollection result;

    edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl_PF;
    eventSetup.get<JetCorrectionsRecord>().get("AK5PF",JetCorParColl_PF); 
    JetCorrectorParameters const & JetCorPar_PF = (*JetCorParColl_PF)["Uncertainty"];
    JetCorrectionUncertainty *jecUnc_PF = new JetCorrectionUncertainty(JetCorPar_PF);

    // don't have these collections 
    //std::vector<PFCandidatePtr> PFJetPart;

    /*  these collections aren't in our PAT-tuple 
    //full
    Handle<ValueMap<float> > puJetIdMVA_full;
    iEvent.getByLabel("puJetMvaChs","fullDiscriminant",puJetIdMVA_full);
    Handle<ValueMap<int> > puJetIdFlag_full;
    iEvent.getByLabel("puJetMvaChs","fullId",puJetIdFlag_full);

    //simple
    Handle<ValueMap<float> > puJetIdMVA_simple;
    iEvent.getByLabel("puJetMvaChs","simpleDiscriminant",puJetIdMVA_simple);
    Handle<ValueMap<int> > puJetIdFlag_simple;
    iEvent.getByLabel("puJetMvaChs","simpleId",puJetIdFlag_simple);

    //cutbased
    Handle<ValueMap<float> > puJetIdMVA_cutbased;
    iEvent.getByLabel("puJetMvaChs","cutbasedDiscriminant",puJetIdMVA_cutbased);
    Handle<ValueMap<int> > puJetIdFlag_cutbased;
    iEvent.getByLabel("puJetMvaChs","cutbasedId",puJetIdFlag_cutbased);

    //puJet ID  MVA inputs
    Handle<ValueMap<StoredPileupJetIdentifier> > vmap;
    iEvent.getByLabel("puJetIdChs", vmap);


    PileupJetIdentifier puIdentifier;
     */
    for( pat::JetCollection::const_iterator pfjet = iCollection->begin(); pfjet != iCollection->end(); ++ pfjet ) {

        if( !(pfjet->pt()>minJetPt_) ) continue;

        BNjet MyPfjet;

        unsigned int idx = pfjet-iCollection->begin();

        /*
           float mva_full  = (*puJetIdMVA_full)[pfjets.refAt(idx)];
           int idflag_full = (*puJetIdFlag_full)[pfjets.refAt(idx)];

           float mva_simple  = (*puJetIdMVA_simple)[pfjets.refAt(idx)];
           int idflag_simple = (*puJetIdFlag_simple)[pfjets.refAt(idx)];

           float mva_cutbased  = (*puJetIdMVA_cutbased)[pfjets.refAt(idx)];
           int idflag_cutbased = (*puJetIdFlag_cutbased)[pfjets.refAt(idx)];

           puIdentifier = (*vmap)[pfjets.refAt(idx)];

           bool passTight_full=false, passMedium_full=false, passLoose_full=false;
           if( ( ( idflag_full & (1 << 0) ) != 0 ) ) passTight_full  = true;
           if( ( ( idflag_full & (1 << 1) ) != 0 ) ) passMedium_full = true;
           if( ( ( idflag_full & (1 << 2) ) != 0 ) ) passLoose_full = true;

           bool passTight_simple=false, passMedium_simple=false, passLoose_simple=false;
           if( ( ( idflag_simple & (1 << 0) ) != 0 ) ) passTight_simple  = true;
           if( ( ( idflag_simple & (1 << 1) ) != 0 ) ) passMedium_simple = true;
           if( ( ( idflag_simple & (1 << 2) ) != 0 ) ) passLoose_simple = true;

           bool passTight_cutbased=false, passMedium_cutbased=false, passLoose_cutbased=false;
           if( ( ( idflag_cutbased & (1 << 0) ) != 0 ) ) passTight_cutbased  = true;
           if( ( ( idflag_cutbased & (1 << 1) ) != 0 ) ) passMedium_cutbased = true;
           if( ( ( idflag_cutbased & (1 << 2) ) != 0 ) ) passLoose_cutbased = true;

        // printf("  ===> jet %d,\t pt = %4.1f,\t eta = %4.2f \n", idx, pfjet->pt(), pfjet->eta() );
        // printf("\t\t\t mva_full = %4.3f,\t idflag_full = %d,\t passTight_full = %d,\t passMedium_full = %d,\t passLoose_full = %d \n",
        // 	      mva_full, idflag_full, (passTight_full)?1:0, (passMedium_full)?1:0, (passLoose_full)?1:0 );
        // printf("\t\t\t mva_simp = %4.3f,\t idflag_simp = %d,\t passTight_simp = %d,\t passMedium_simp = %d,\t passLoose_simp = %d \n",
        // 	      mva_simple, idflag_simple, (passTight_simple)?1:0, (passMedium_simple)?1:0, (passLoose_simple)?1:0 );
        // printf("\t\t\t mva_cutb = %4.3f,\t idflag_cutb = %d,\t passTight_cutb = %d,\t passMedium_cutb = %d,\t passLoose_cutb = %d \n",
        // 	      mva_cutbased, idflag_cutbased, (passTight_cutbased)?1:0, (passMedium_cutbased)?1:0, (passLoose_cutbased)?1:0 );

        MyPfjet.puJetMVA_full     = mva_full;
        MyPfjet.puJetMVA_simple   = mva_simple;
        MyPfjet.puJetMVA_cutbased = mva_cutbased;

        MyPfjet.puJetId_full     = idflag_full;
        MyPfjet.puJetId_simple   = idflag_simple;
        MyPfjet.puJetId_cutbased = idflag_cutbased;

        MyPfjet.puJetId_tight_full     = (passTight_full)?1:0;
        MyPfjet.puJetId_tight_simple   = (passTight_simple)?1:0;
        MyPfjet.puJetId_tight_cutbased = (passTight_cutbased)?1:0;

        MyPfjet.puJetId_medium_full     = (passMedium_full)?1:0;
        MyPfjet.puJetId_medium_simple   = (passMedium_simple)?1:0;
        MyPfjet.puJetId_medium_cutbased = (passMedium_cutbased)?1:0;

        MyPfjet.puJetId_loose_full     = (passLoose_full)?1:0;
        MyPfjet.puJetId_loose_simple   = (passLoose_simple)?1:0;
        MyPfjet.puJetId_loose_cutbased = (passLoose_cutbased)?1:0;

         */

        double rawpt = pfjet->correctedJet(0).pt();

        std::vector<PFCandidatePtr> PFJetPart = pfjet->getPFConstituents();

        double maxCandPt=0;
        double leadCandVx=-99,leadCandVy=-99,leadCandVz=-99;
        for(UInt_t j=0;j<PFJetPart.size();j++){
            double pTcand = PFJetPart[j]->pt();
            if( pTcand>maxCandPt ){
                maxCandPt = pTcand;
                leadCandVx = PFJetPart[j]->vx();
                leadCandVy = PFJetPart[j]->vy();
                leadCandVz = PFJetPart[j]->vz();
            }
        }

        double leadCandDistFromPV = sqrt( (leadCandVx-PVx)*(leadCandVx-PVx) + (leadCandVy-PVy)*(leadCandVy-PVy) + (leadCandVz-PVz)*(leadCandVz-PVz) );

        MyPfjet.leadCandPt = maxCandPt;

        MyPfjet.leadCandVx = leadCandVx;
        MyPfjet.leadCandVy = leadCandVy;
        MyPfjet.leadCandVz = leadCandVz;
        //MyPfjet.leadCandDistFromPV = leadCandDistFromPV;

        /*
           MyPfjet.dZ = puIdentifier.dZ();
           MyPfjet.dR2Mean = puIdentifier.dR2Mean();
           MyPfjet.dRMean = puIdentifier.dRMean();
           MyPfjet.frac01 = puIdentifier.frac01();
           MyPfjet.frac02 = puIdentifier.frac02();
           MyPfjet.frac03 = puIdentifier.frac03();
           MyPfjet.frac04 = puIdentifier.frac04();
           MyPfjet.frac05 = puIdentifier.frac05();
           MyPfjet.frac06 = puIdentifier.frac06();
           MyPfjet.frac07 = puIdentifier.frac07(); //Always 0
           MyPfjet.beta = puIdentifier.beta();
           MyPfjet.betaStar = puIdentifier.betaStar();
           MyPfjet.betaClassic = puIdentifier.betaClassic();
           MyPfjet.betaStarClassic = puIdentifier.betaStarClassic();
           MyPfjet.ptD = puIdentifier.ptD();
           MyPfjet.nvtx = puIdentifier.nvtx();
           MyPfjet.d0 = puIdentifier.d0(); //Not declared in class StoredPileupJetIdentifier (PileupJetIdentifier.h) 
         */
        MyPfjet.Upt = rawpt;

        double unc = 1., JECuncUp = 1., JECuncDown = 1.; // JEC uncertainties only defined for jets with |eta| < 5.5 and pt > 9 GeV (2011 data)
        
        if( pfjet->pt()>9. && fabs(pfjet->eta())<5.0 ){
            jecUnc_PF->setJetEta(pfjet->eta());
            jecUnc_PF->setJetPt(pfjet->pt());// the uncertainty is a function of the corrected pt
            JECuncUp = jecUnc_PF->getUncertainty(true); //up variation
            unc = JECuncUp;
            jecUnc_PF->setJetEta(pfjet->eta());
            jecUnc_PF->setJetPt(pfjet->pt());// the uncertainty is a function of the corrected pt
            JECuncDown = jecUnc_PF->getUncertainty(false); //up variation
        }
        
        // general kinematic variables
        MyPfjet.energy = pfjet->energy();
        MyPfjet.et = pfjet->et();
        MyPfjet.pt = pfjet->pt();
        MyPfjet.px = pfjet->px();
        MyPfjet.py = pfjet->py();
        MyPfjet.pz = pfjet->pz();
        MyPfjet.phi = pfjet->phi();
        MyPfjet.eta = pfjet->eta();
        MyPfjet.theta = pfjet->theta();

        //MyPfjet.EMfrac = pfjet->emEnergyFraction();
        //MyPfjet.Hadfrac = pfjet->energyFractionHadronic();
        MyPfjet.charge = pfjet->jetCharge();
        MyPfjet.mass = pfjet->mass();
        //MyPfjet.area = pfjet->towersArea();
        MyPfjet.fHPD = pfjet->jetID().fHPD;
        MyPfjet.flavour = pfjet->partonFlavour();
        MyPfjet.Nconst = pfjet->nConstituents();
        MyPfjet.n90Hits = pfjet->jetID().n90Hits;
        MyPfjet.approximatefHPD = pfjet->jetID().approximatefHPD;
        MyPfjet.hitsInN90 = pfjet->jetID().hitsInN90;


        // btag variables
        MyPfjet.btagTChighPur = pfjet->bDiscriminator("trackCountingHighPurBJetTags");
        MyPfjet.btagTChighEff = pfjet->bDiscriminator("trackCountingHighEffBJetTags");
        MyPfjet.btagJetProb = pfjet->bDiscriminator("jetProbabilityBJetTags");
        MyPfjet.btagJetBProb = pfjet->bDiscriminator("jetBProbabilityBJetTags");
        MyPfjet.btagSoftEle = pfjet->bDiscriminator("softElectronBJetTags");
        MyPfjet.btagSoftMuon = pfjet->bDiscriminator("softMuonBJetTags");
        MyPfjet.btagSoftMuonNoIP = pfjet->bDiscriminator("softMuonNoIPBJetTags");
        MyPfjet.btagSecVertex = pfjet->bDiscriminator("simpleSecondaryVertexBJetTags");
        MyPfjet.btagSecVertexHighEff = pfjet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags");
        MyPfjet.btagSecVertexHighPur = pfjet->bDiscriminator("simpleSecondaryVertexHighPurBJetTags");
        MyPfjet.btagCombinedSecVertex = pfjet->bDiscriminator("combinedSecondaryVertexBJetTags");
        MyPfjet.btagCombinedSecVertexMVA = pfjet->bDiscriminator("combinedSecondaryVertexMVABJetTags");
        MyPfjet.btagSoftMuonByPt = pfjet->bDiscriminator("softMuonByPtBJetTags");
        MyPfjet.btagSoftMuonByIP3 = pfjet->bDiscriminator("softMuonByIP3dBJetTags");
        MyPfjet.btagSoftElectronByPt = pfjet->bDiscriminator("softElectronByPtBJetTags");
        MyPfjet.btagSoftElectronByIP3 = pfjet->bDiscriminator("softElectronByIP3dBJetTags");

        MyPfjet.JESunc = unc;
        MyPfjet.JECuncUp = JECuncUp;
        MyPfjet.JECuncDown = JECuncDown;

        if( (pfjet->genJet()) ){ // if there is a matched genjet, fill variables
            MyPfjet.genJetET = pfjet->genJet()->et();
            MyPfjet.genJetPT = pfjet->genJet()->pt();
            MyPfjet.genJetEta = pfjet->genJet()->eta();
            MyPfjet.genJetPhi = pfjet->genJet()->phi();
        }
        if( (pfjet->genParton()) ){ // if there is a matched parton, fill variables
            MyPfjet.genPartonET = pfjet->genParton()->et();
            MyPfjet.genPartonPT = pfjet->genParton()->pt();
            MyPfjet.genPartonEta = pfjet->genParton()->eta();
            MyPfjet.genPartonPhi = pfjet->genParton()->phi();
            MyPfjet.genPartonId = pfjet->genParton()->pdgId();

            int numberOfMothers = pfjet->genParton()->numberOfMothers();
            if( numberOfMothers==1 ){
                MyPfjet.genPartonMotherId  = pfjet->genParton()->mother()->pdgId();
                MyPfjet.genPartonMother0Id = pfjet->genParton()->mother()->pdgId();
                int numberOfGrandMothers = pfjet->genParton()->mother()->numberOfMothers();
                if( numberOfGrandMothers==1 ) MyPfjet.genPartonGrandMotherId = pfjet->genParton()->mother()->mother()->pdgId();
                else if( numberOfGrandMothers>=2 ){
                    MyPfjet.genPartonGrandMother00Id = pfjet->genParton()->mother()->mother(0)->pdgId();
                    MyPfjet.genPartonGrandMother01Id = pfjet->genParton()->mother()->mother(1)->pdgId();
                }

                int pdgId = pfjet->genParton()->pdgId();
                int motherId = pfjet->genParton()->mother()->pdgId();

                int last_motherID = -99;
                int last_grandMotherID = -99;
                if( pdgId==motherId ){
                    const reco::Candidate* new_mother = pfjet->genParton()->mother();

                    bool keepGoing = true;
                    while( keepGoing ){
                        int new_motherID = new_mother->pdgId();
                        last_motherID = new_motherID;
                        if( new_mother->numberOfMothers()>0 ){
                            new_mother = new_mother->mother();
                            last_grandMotherID = new_mother->pdgId();
                            if( new_motherID!=pdgId ) keepGoing = false;
                        }
                        else keepGoing = false;
                    }
                }

                if( last_motherID!=-99 ){
                    MyPfjet.genPartonMother0Id = last_motherID;
                    if( last_grandMotherID!=-99 ) MyPfjet.genPartonGrandMotherId = last_grandMotherID;
                }
            }
            else if( numberOfMothers>=2 ){
                MyPfjet.genPartonMother0Id = pfjet->genParton()->mother(0)->pdgId();
                MyPfjet.genPartonMother1Id = pfjet->genParton()->mother(1)->pdgId();

                if( pfjet->genParton()->mother(0)->numberOfMothers()==1 ) MyPfjet.genPartonGrandMother00Id = pfjet->genParton()->mother(0)->mother()->pdgId();
                else if( pfjet->genParton()->mother(0)->numberOfMothers()>=2 ){
                    MyPfjet.genPartonGrandMother00Id = pfjet->genParton()->mother(0)->mother(0)->pdgId();
                    MyPfjet.genPartonGrandMother01Id = pfjet->genParton()->mother(0)->mother(1)->pdgId();
                }

                if( pfjet->genParton()->mother(1)->numberOfMothers()==1 ) MyPfjet.genPartonGrandMother00Id = pfjet->genParton()->mother(1)->mother()->pdgId();
                else if( pfjet->genParton()->mother(1)->numberOfMothers()>=2 ){
                    MyPfjet.genPartonGrandMother10Id = pfjet->genParton()->mother(1)->mother(0)->pdgId();
                    MyPfjet.genPartonGrandMother11Id = pfjet->genParton()->mother(1)->mother(1)->pdgId();
                }
            }

        }

        // DataFormats/JetReco/interface/PFJet.h
        // http://indico.cern.ch/getFile.py/access?contribId=8&resId=0&materialId=slides&confId=92249
        MyPfjet.chargedHadronEnergyFraction = pfjet->chargedHadronEnergyFraction();
        MyPfjet.neutralHadronEnergyFraction = pfjet->neutralHadronEnergyFraction();
        MyPfjet.chargedEmEnergyFraction = pfjet->chargedEmEnergyFraction();
        MyPfjet.neutralEmEnergyFraction = pfjet->neutralEmEnergyFraction();
        MyPfjet.chargedMultiplicity = pfjet->chargedMultiplicity();
        MyPfjet.neutralMultiplicity = pfjet->neutralMultiplicity();
        MyPfjet.nconstituents = pfjet->numberOfDaughters();


        bool loose = (
                pfjet->neutralHadronEnergyFraction() < 0.99 &&
                pfjet->chargedEmEnergyFraction() < 0.99 &&
                pfjet->neutralEmEnergyFraction() < 0.99 &&
                pfjet->numberOfDaughters() > 1
                );

        if( fabs(pfjet->eta())<2.4 ){
            loose = ( loose &&
                    pfjet->chargedHadronEnergyFraction() > 0.0 &&
                    pfjet->chargedMultiplicity() > 0
                    );
        }

        MyPfjet.jetIDLoose = (loose) ? 1 : 0;

        result.push_back(MyPfjet);
    }
    return result;
}


BNmetCollection			PATupleToBEANtranslator::PATtoBN(pat::METCollection const* iCollection){
	BNmetCollection result;


    BNmet MyPfmet;

    MyPfmet.pt = iCollection->front().pt();
    MyPfmet.px = iCollection->front().px();
    MyPfmet.py = iCollection->front().py();
    MyPfmet.phi = iCollection->front().phi();
    MyPfmet.sumET = iCollection->front().sumEt();
    MyPfmet.corSumET = iCollection->front().corSumEt();
    MyPfmet.Upt = iCollection->front().uncorrectedPt();
    MyPfmet.Uphi = iCollection->front().uncorrectedPhi();
    if (iCollection->front().isPFMET()) { //Appears to always return false
        MyPfmet.NeutralEMFraction = iCollection->front().NeutralEMFraction();
        MyPfmet.NeutralHadEtFraction = iCollection->front().NeutralHadEtFraction();
        MyPfmet.ChargedEMEtFraction = iCollection->front().ChargedEMEtFraction();
        MyPfmet.ChargedHadEtFraction = iCollection->front().ChargedHadEtFraction();
        MyPfmet.MuonEtFraction = iCollection->front().MuonEtFraction();
        MyPfmet.Type6EtFraction = iCollection->front().Type6EtFraction();
        MyPfmet.Type7EtFraction = iCollection->front().Type7EtFraction();
    }

    double sigmaX2_pf = (iCollection->front()).getSignificanceMatrix()(0,0);
    double sigmaY2_pf = (iCollection->front()).getSignificanceMatrix()(1,1);
    double sigmaXY_pf = (iCollection->front()).getSignificanceMatrix()(0,1);
    double sigmaYX_pf = (iCollection->front()).getSignificanceMatrix()(1,0);

    double significance_pf = 99;
    if(sigmaX2_pf<1.e10 && sigmaY2_pf<1.e10) significance_pf = (iCollection->front()).significance();

    MyPfmet.significance = significance_pf;
    MyPfmet.sigmaX2 = sigmaX2_pf;
    MyPfmet.sigmaY2 = sigmaY2_pf;
    MyPfmet.sigmaXY = sigmaXY_pf;
    MyPfmet.sigmaYX = sigmaYX_pf;

    if( (iCollection->front().genMET()) ){
        MyPfmet.genPT = iCollection->front().genMET()->pt();
        MyPfmet.genPhi = iCollection->front().genMET()->phi();
    }

    result.push_back(MyPfmet);
	return result;
}


BNprimaryvertexCollection	PATupleToBEANtranslator::RECOtoBN(reco::VertexCollection const* iCollection){
    BNprimaryvertexCollection result;
    bool firstPV = true;
    for( reco::VertexCollection::const_iterator vtx = iCollection->begin(); vtx!=iCollection->end(); ++vtx ){

        BNprimaryvertex MyPV;

        MyPV.x = vtx->x();
        MyPV.xError = vtx->xError();
        MyPV.y = vtx->y();
        MyPV.yError = vtx->yError();
        MyPV.z = vtx->z();
        MyPV.zError = vtx->zError();

        MyPV.normalizedChi2 = vtx->normalizedChi2();
        MyPV.isFake = vtx->isFake();
        MyPV.isValid = vtx->isValid();
        MyPV.tracksSize = vtx->tracksSize();

        MyPV.ndof = vtx->ndof();
        MyPV.rho  = vtx->position().rho();

        bool isGood = false;
        if( vtx->ndof() > minNDOF_ &&
                ( (maxAbsZ_ <= 0) || fabs(vtx->z()) <= maxAbsZ_ ) &&
                ( (maxd0_ <= 0) || fabs(vtx->position().rho()) <= maxd0_ )
          ){
            isGood = true;
        }

        MyPV.isGood = ( isGood ) ? 1 : 0;

        result.push_back(MyPV);
    }
    return result;
}


BNtriggerCollection	PATupleToBEANtranslator::EDMtoBN(
        edm::TriggerResults const* iCollection,
        const edm::Event& event,
        const edm::EventSetup& eventSetup
//        edm::Run& run
){
   
    HLTConfigProvider hltConfig;
    //std::string hlt("HLT");
    //bool changed;
    //hltConfig.init(run,eventSetup,hlt,changed);
    BNtriggerCollection result;
    const edm::TriggerNames & trigNames = event.triggerNames(*iCollection);
    unsigned int numTriggers = trigNames.size();

    for( unsigned int hltIndex=0; hltIndex<numTriggers-1; ++hltIndex ){

        std::string currentTrigName = trigNames.triggerName(hltIndex);
        int accept = iCollection->accept(hltIndex);

        int prescale = hltConfig.prescaleValue(event, eventSetup, currentTrigName);

        BNtrigger MyTrigger;

        MyTrigger.pass = accept;
        MyTrigger.prescale = prescale;
        MyTrigger.name = currentTrigName;

        //std::cout << " =====>  HLT: path name = " << currentTrigName << ",\t prescale = " << prescale << ",\t pass = " << accept << std::endl; 

        result.push_back(MyTrigger);

    }
    return result;
}


const reco::Vertex* PATupleToBEANtranslator::getPrimaryVertex(reco::VertexCollection const* iCollection) {
   
    for( reco::VertexCollection::const_iterator vtx = iCollection->begin(); vtx!=iCollection->end(); ++vtx ){

        bool isGood = false;
        if( vtx->ndof() > minNDOF_ &&
                ( (maxAbsZ_ <= 0) || fabs(vtx->z()) <= maxAbsZ_ ) &&
                ( (maxd0_ <= 0) || fabs(vtx->position().rho()) <= maxd0_ )
          ){
            isGood = true;
        }

        if( isGood ){
            return &*vtx;
        }

    }
    return 0;
}
bool PATupleToBEANtranslator::tauIsInTheCracks(float etaValue){
    return (fabs(etaValue) < 0.018 ||
            (fabs(etaValue)>0.423 && fabs(etaValue)<0.461) ||
            (fabs(etaValue)>0.770 && fabs(etaValue)<0.806) ||
            (fabs(etaValue)>1.127 && fabs(etaValue)<1.163) ||
            (fabs(etaValue)>1.460 && fabs(etaValue)<1.558));
}

