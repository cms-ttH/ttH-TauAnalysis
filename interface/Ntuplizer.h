// vim: et:sta:sw=4:ts=4
// Authors: Nil Valls

#ifndef _Ntuplizer_h
#define _Ntuplizer_h

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Event.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "BEAN/BEANmaker/interface/BEANhelper.h"

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
#include "TauLeptonFiller.h"
#include "TauLeptonLeptonFiller.h"
#include "VertexFiller.h"

#include "Parameters.h"

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
        Parameters params_;
        std::string _filename;
		// === Misc variables === //
		unsigned int _DebugLevel;
		vector<NtupleFiller*> ntupleFillers;
		vector<string> _enabledFillers;
		ParameterSet* jobConfig;
		string _EraRelease;
		bool _FromBEAN;
        TFile* _file;
		TTree* _Tree;
        bool _UsePfLeptons;
		BEANhelper beanHelper;
		map<string,BEANhelper*> beanHelpers;
        sysType::sysType _sysType;
        string _DataRange;
        bool _RunExtraBEANhelpers;
        bool _use_event_veto;
        int _num_leptons;
        analysisType::analysisType _an_type;

        // required for TTL-event check
        InputTag _RecoJetSource;
        InputTag _RecoTauSource;
        InputTag _RecoMuonSource;
        InputTag _RecoElectronSource;
        int _numFailedTauEventCheck;

		// === Trigger Inputs === //
		bool _ApplySkimTriggerRequirements;
		InputTag _SkimTriggerSource;
		vector<std::string> _SkimTriggerRequirements;

		// === Histogram to keep track of events read === //
		TH1I* _EventsRead;
};


#endif
