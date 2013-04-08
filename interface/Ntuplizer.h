// Authors: Nil Valls

#ifndef _Ntuplizer_h
#define _Ntuplizer_h

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Event.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "NtupleMaker/BEANmaker/interface/BEANhelper.h"

#include "NtupleFiller.h"
#include "EventFiller.h"
#include "GenLevelFiller.h"
#include "GenTauFiller.h"
#include "GenJetFiller.h"
#include "TauFiller.h"
#include "ElectronFiller.h"
#include "MuonFiller.h"
#include "JetFiller.h"
#include "DitauFiller.h"
#include "DitauLeptonFiller.h"
#include "DitauMuonFiller.h"
#include "DitauElectronFiller.h"
#include "TriggerFiller.h"
#include "QuickFiller.h"
#include "VertexFiller.h"

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
		string GetAnalysisTypeParameter(unsigned int);
		unsigned int GetEra();
		const char GetSubera();
		string GetSampleType();
		string GetLeptonFlavor();
		bool EraIs(unsigned int);
		bool SuberaIs(const char);
		bool SampleTypeIs(const string);
		bool SampleTypeContains(const string);
		bool LeptonFlavorIs(const string);

	// ----- Variables ----- //
	private:
		// === Misc variables === //
		unsigned int _DebugLevel;
		vector<NtupleFiller*> ntupleFillers;
		vector<string> _enabledFillers;
		ParameterSet* jobConfig;
		string _AnalysisType;
		string _EraRelease;
		vector<string> _AnalysisTypeVector;
		bool _FromBEAN;
		TTree* _Tree;
		string _TreeName;
        bool _UsePfLeptons;
		BEANhelper beanHelper;
        sysType::sysType _sysType;

        // required for TTL-event check
        InputTag _RecoJetSource;
        InputTag _RecoTauSource;
        InputTag _RecoMuonSource;
        InputTag _RecoElectronSource;

		// === Trigger Inputs === //
		bool _ApplySkimTriggerRequirements;
		InputTag _SkimTriggerSource;
		vector<std::string> _SkimTriggerRequirements;

		// === Histogram to keep track of events read === //
		TH1I* _EventsRead;
};


#endif
