// -*- C++ -*-
//
// Package:    BEANskimmer
// Class:      BEANskimmer
// 

#include <string>

// user include files
#include "BEAN/Collections/interface/BNmcparticle.h"

#include "ttH/TauAnalysis/plugins/BEANskimmer.h"

//
// constructors and destructor
//
BEANskimmer::BEANskimmer(const edm::ParameterSet& config) :
   numPartons_(config.getUntrackedParameter<int>("partons", -1)),
   genSrc_(config.getUntrackedParameter<edm::InputTag>("genSrc"))
{
    //now do what ever initialization is needed
    std::vector<std::string> jet_cfg = config.getUntrackedParameter<std::vector<std::string>>("jetConfig");
    std::string lep_cfg = config.getUntrackedParameter<std::string>("lepConfig");

    for (const auto& s: jet_cfg)
        jet_reqs_.push_back({std::stoi(s.substr(0, 1)), std::stoi(s.substr(1, 1)), std::stoi(s.substr(2, 1)), std::stoi(s.substr(3, 1))});

    tauSrc_ = config.exists("tauSrc") ? config.getParameter<edm::InputTag>("tauSrc") : edm::InputTag("BNproducer::selectedPatTaus");
    jetSrc_ = config.exists("jetSrc") ? config.getParameter<edm::InputTag>("jetSrc") : edm::InputTag("BNproducer::selectedPatJets");

    CSV_WP_L_ = 0.244;
    CSV_WP_M_ = 0.679;
    CSV_WP_T_ = 0.898;
    minNumBaseTaus_ = 0;
    minNumIsoTaus_ = 0;

    int sample = config.getUntrackedParameter<int>("sample");
    auto type = config.getUntrackedParameter<bool>("dilepton") ? analysisType::TauDIL : analysisType::TauLJ;
    helper_.SetUp("2012_53x", sample, type, (sample < 0), "SingleMu", false, true, "All");

    if( lep_cfg.size() > 0 ) minNumBaseTaus_ = std::stoi(lep_cfg.substr(0, 1));
    if( lep_cfg.size() > 1 ) minNumIsoTaus_ = std::stoi(lep_cfg.substr(1, 1));

    //std::cout << "Configuration: " << std::endl
    //  << "minNumJets_ = " << minNumJets_ << std::endl
    //  << "minNumLooseBtags_ = " << minNumLooseBtags_ << std::endl
    //  << "minNumMediumBtags_ = " << minNumMediumBtags_ << std::endl
    //  << "minNumTightBtags_ = " << minNumTightBtags_ << std::endl
    //  << "minNumBaseTaus_ = " << minNumBaseTaus_ << std::endl
    //  << "minNumIsoTaus_ = " << minNumIsoTaus_ << std::endl;

}


BEANskimmer::~BEANskimmer()
{

    // do anything here that needs to be done at destruction time
    // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
    bool
BEANskimmer::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace std;
    using namespace edm;

    if (numPartons_ > -1) {
       unsigned int test = numPartons_;

       edm::Handle<BNmcparticleCollection> gen;
       iEvent.getByLabel(genSrc_, gen);

       if (helper_.GetNumExtraPartons(*gen) != test)
          return false;
    }

    edm::Handle<BNjetCollection> jetsHandle;
    iEvent.getByLabel(jetSrc_, jetsHandle);
    const BNjetCollection &raw_pfjets = *jetsHandle;
    BNjetCollection pfjets = helper_.GetCorrectedJets(raw_pfjets, sysType::NA);

    int numLooseTags = 0;
    int numMediumTags = 0;
    int numTightTags = 0;
    int numJets = 0;

    for( int i=0; i<int(pfjets.size()); i++ ){
        if( pfjets.at(i).pt < 30 ) continue;
        numJets++;
        double csv = pfjets.at(i).btagCombinedSecVertex;
        if( csv > CSV_WP_T_ ) numTightTags++; 
        if( csv > CSV_WP_M_ ) numMediumTags++; 
        if( csv > CSV_WP_L_ ) numLooseTags++;
    }

    bool res = false;
    for (const auto& req: jet_reqs_) {
        if (numJets >= req[0] &&
                numLooseTags >= req[1] &&
                numMediumTags >= req[2] &&
                numTightTags >= req[3]) {
            res = true;
            break;
        }
    }
    if (!res)
        return false;

    int numBaseTaus = 0;
    int numIsoTaus = 0;
    edm::Handle<BNtauCollection> tausHandle;
    iEvent.getByLabel(tauSrc_, tausHandle);
    BNtauCollection const &taus = *tausHandle;

    for( int i=0; i<int(taus.size()); i++ ) {
        BNtau tau = taus.at(i);
        if( tau.pt > 20 &&
                tau.HPSdecayModeFinding > 0 &&
                tau.leadingTrackPt > 5 &&
                tau.leadingTrackValid > 0 &&
                tau.HPSagainstElectronLoose > 0 &&
                tau.HPSagainstMuonLoose > 0 &&
                tau.HPSbyVLooseCombinedIsolationDeltaBetaCorr > 0) numIsoTaus++;
        if( tau.pt > 20 &&
                tau.HPSdecayModeFinding > 0 &&
                tau.leadingTrackPt > 5 &&
                tau.leadingTrackValid > 0 &&
                tau.HPSagainstElectronLoose > 0 &&
                tau.HPSagainstMuonLoose > 0 ) numBaseTaus++;
    }
    if( numBaseTaus < minNumBaseTaus_ )
        return false;
    if( numIsoTaus < minNumIsoTaus_ )
        return false;

    return true;
}

// ------------ method called once each job just before starting event loop  ------------
    void 
BEANskimmer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
BEANskimmer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
    bool 
BEANskimmer::beginRun(edm::Run&, edm::EventSetup const&)
{ 
    return true;
}

// ------------ method called when ending the processing of a run  ------------
    bool 
BEANskimmer::endRun(edm::Run&, edm::EventSetup const&)
{
    return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
    bool 
BEANskimmer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
    return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
    bool 
BEANskimmer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
    return true;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
BEANskimmer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(BEANskimmer);
