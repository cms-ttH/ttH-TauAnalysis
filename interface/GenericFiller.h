// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _GenericFiller_h
#define _GenericFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class GenericFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit GenericFiller(const ParameterSet&);
		explicit GenericFiller(const ParameterSet&, TTree*);
		~GenericFiller();
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
