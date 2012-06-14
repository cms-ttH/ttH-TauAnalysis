// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _Ntuplizer_h
#define _Ntuplizer_h

// system include files
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <TMath.h>
#include <iostream>
#include <iomanip>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>

// user include files
#include "FWCore/Framework/interface/EDAnalyzer.h"
//#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
//#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "../interface/NtupleFiller.h"
#include "../interface/EventFiller.h"
#include "../interface/GenLevelFiller.h"
#include "../interface/GenTauFiller.h"
#include "../interface/TauFiller.h"
#include "../interface/ElectronFiller.h"
#include "../interface/MuonFiller.h"
#include "../interface/JetFiller.h"
#include "../interface/DitauFiller.h"
#include "../interface/DitauMuonFiller.h"
#include "../interface/DitauElectronFiller.h"

using namespace std;
using namespace edm;

typedef reco::Candidate::LorentzVector LorentzVector;
typedef std::vector< reco::Candidate::LorentzVector > LVCollection;

class Ntuplizer : public EDAnalyzer {

	// ----- Functions ----- //
	public:
		explicit Ntuplizer(const ParameterSet&);
		~Ntuplizer();

	protected:
		// === Core functions === //
		virtual void beginJob();
		virtual void analyze(const Event&, const EventSetup&);
		virtual void endJob();

	private:
		bool MeetsTriggerRequirements(const Event&, InputTag, vector<string>);
		bool IsFillerEnabled(const string);

	// ----- Variables ----- //
	private:
		// === Misc variables === //
		vector<NtupleFiller*> ntupleFillers;
		vector<string> _enabledFillers;
		ParameterSet* jobConfig;
		string _AnalysisType;
		TTree* _Tree;
		string _TreeName;

		// === Trigger Inputs === //
		bool _ApplyTriggerRequirements;
		InputTag _TriggerSource;
		vector<std::string> _TriggerRequirements;

		// === Trigger Inputs === //
		bool _ApplySkimTriggerRequirements;
		InputTag _SkimTriggerSource;
		vector<std::string> _SkimTriggerRequirements;

		// === Histogram to keep track of events read === //
		TH1I* _EventsRead;
};


#endif
