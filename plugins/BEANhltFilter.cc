// -*- C++ -*-
//
// Package:    BEANhltFilter
// Class:      BEANhltFilter
// 

// user include files
#include "TTHTauTau/Analysis/plugins/BEANhltFilter.h"

//
// constructors and destructor
//
BEANhltFilter::BEANhltFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
  if( iConfig.exists("HLTacceptPath") ) 
    hltAcceptPath_ = iConfig.getParameter<std::string>("HLTacceptPath");
  else
    edm::LogError ("BEANhltFilter::BEANhltFilter") << " parameter 'HLTacceptPath' must be configured! Exiting...";
}


BEANhltFilter::~BEANhltFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
BEANhltFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<BNtriggerCollection> triggerHandle;
  iEvent.getByLabel("BNproducer","HLT", triggerHandle);
  BNtriggerCollection const &hlt = *triggerHandle;

  bool triggerFound = false;
  bool triggerPassed = false;
  for( BNtriggerCollection::const_iterator trgIt = hlt.begin(); trgIt != hlt.end(); trgIt++ ){
    std::string hlt_name = trgIt->name;
    if( (hlt_name.find(hltAcceptPath_)!=std::string::npos) ){
      if( trgIt->prescale!=1 ) continue;
      triggerFound = true;
      triggerPassed = ( trgIt->pass==1 );
    }
    if( triggerPassed ) break; 
  }
  if( !triggerFound) {
    edm::LogError ("BEANhltFilter::filter") << "HLT path " << hltAcceptPath_ << " not found in event!"; 
  }
  return triggerPassed;
}

// ------------ method called once each job just before starting event loop  ------------
void 
BEANhltFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
BEANhltFilter::endJob() {
}

// ------------ method called when starting to processes a run  ------------
bool 
BEANhltFilter::beginRun(edm::Run&, edm::EventSetup const&)
{ 
  return true;
}

// ------------ method called when ending the processing of a run  ------------
bool 
BEANhltFilter::endRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
bool 
BEANhltFilter::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
bool 
BEANhltFilter::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
BEANhltFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(BEANhltFilter);
