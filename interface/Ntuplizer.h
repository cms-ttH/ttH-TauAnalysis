// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _Ntuplizer_h
#define _Ntuplizer_h

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Math/interface/LorentzVectorFwd.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/normalizedPhi.h"
#include "DataFormats/TauReco/interface/PFTau.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/Common/interface/RefVector.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "CLHEP/Random/RandGauss.h"
#include "CommonTools/CandUtils/interface/Booster.h"
#include <Math/VectorUtil.h>

#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include <TMath.h>
#include <iostream>
#include <iomanip>
#include "HighMassAnalysis/Analysis/interface/NtupleFiller.h"
#include "HighMassAnalysis/Analysis/interface/EventFiller.h"
#include "HighMassAnalysis/Analysis/interface/GenLevelFiller.h"
#include "HighMassAnalysis/Analysis/interface/TauFiller.h"
#include "HighMassAnalysis/Analysis/interface/ElectronFiller.h"
#include "HighMassAnalysis/Analysis/interface/MuonFiller.h"
#include "HighMassAnalysis/Analysis/interface/JetFiller.h"
#include "HighMassAnalysis/Analysis/interface/DitauFiller.h"
#include "HighMassAnalysis/Analysis/interface/DitauMuonFiller.h"
#include "HighMassAnalysis/Analysis/interface/DitauElectronFiller.h"

#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TTree.h>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <TRandom3.h>

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
