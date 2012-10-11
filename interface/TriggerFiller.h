// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _TriggerFiller_h
#define _TriggerFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class TriggerFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit TriggerFiller(const ParameterSet&);
		explicit TriggerFiller(const ParameterSet&, TTree*);
		~TriggerFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void analyze(const Event&, const EventSetup&);
		void SetupBranches();
		void ClearVectors();

	// ----- Variables ----- //
	private:
		int				_HLT_IsoMu24;
        int             _HLT_IsoMu24_eta2p1;
        int             _HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30;
        int             _HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30;
        int             _HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30;
};

#endif
