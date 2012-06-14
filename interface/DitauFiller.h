// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _DitauFiller_h
#define _DitauFiller_h

#include "HighMassAnalysis/Analysis/interface/NtupleFiller.h"

using namespace std;

class DitauFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit DitauFiller(const ParameterSet&);
		explicit DitauFiller(const ParameterSet&, TTree*);
		~DitauFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void analyze(const Event&, const EventSetup&);
		void SetupBranches();
		void ClearVectors();

	// ----- Variables ----- //
	private:
		int					_NumCombos;
		vector<float>		_ComboNumber;
		
};

#endif
