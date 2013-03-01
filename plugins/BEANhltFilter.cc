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
    hltAcceptPaths_ = iConfig.getParameter<std::vector<std::string> >("HLTacceptPaths");
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
  BNtriggerCollection const &hltBeanList = *triggerHandle;

  int triggersFound = 0;
  bool triggerPassed = false;
  for( BNtriggerCollection::const_iterator hltBeanIt = hltBeanList.begin(); hltBeanIt != hltBeanList.end(); hltBeanIt++ ){
    std::string hltBeanName = hltBeanIt->name;
    for( std::vector<std::string>::const_iterator hltAcceptTrg = hltAcceptPaths_.begin();
        hltAcceptTrg != hltAcceptPaths_.end(); hltAcceptTrg++ ) {
      if( (hltBeanName.find(*hltAcceptTrg)!=std::string::npos) ){
        if( hltBeanIt->prescale!=1 ) continue;
        triggersFound++;
        triggerPassed = ( hltBeanIt->pass==1 );
        if( triggerPassed ) break; 
      }
    }
    if( triggerPassed ) break; 
  }
  if( triggersFound == 0) {
    edm::LogError ("BEANhltFilter::filter") << "None of the requested HLT paths were found in the event!"; 
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
