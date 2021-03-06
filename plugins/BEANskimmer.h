// -*- C++ -*-
//
// Package:    BEANskimmer
// Class:      BEANskimmer
// 


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "BEAN/BEANmaker/interface/BEANhelper.h"
#include "BEAN/Collections/interface/BNjet.h"
#include "BEAN/Collections/interface/BNtau.h"

#include <string>
#include <vector>
//
// class declaration
//

class BEANskimmer : public edm::EDFilter {
   public:
      explicit BEANskimmer(const edm::ParameterSet&);
      ~BEANskimmer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual bool beginRun(edm::Run&, edm::EventSetup const&);
      virtual bool endRun(edm::Run&, edm::EventSetup const&);
      virtual bool beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual bool endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      // ----------member data ---------------------------
    BEANhelper helper_;

    std::vector<std::vector<int>> jet_reqs_;
    int minNumBaseTaus_;
    int minNumIsoTaus_;
    int numPartons_;
    double CSV_WP_L_;
    double CSV_WP_M_;
    double CSV_WP_T_;
    edm::InputTag tauSrc_;
    edm::InputTag jetSrc_;
    edm::InputTag genSrc_;
};

