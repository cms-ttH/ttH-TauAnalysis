// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _GenLevelFiller_h
#define _GenLevelFiller_h

#include "HighMassAnalysis/Analysis/interface/NtupleFiller.h"

using namespace std;

class GenLevelFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit GenLevelFiller(const ParameterSet&);
		explicit GenLevelFiller(const ParameterSet&, TTree*);
		~GenLevelFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void analyze(const Event&, const EventSetup&);
		void SetupBranches();
		void ClearVectors();

	// ----- Variables ----- //
	private:
		
};

#endif
