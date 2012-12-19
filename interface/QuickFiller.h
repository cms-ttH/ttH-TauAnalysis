// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _QuickFiller_h
#define _QuickFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class QuickFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit QuickFiller(const ParameterSet&);
		explicit QuickFiller(const ParameterSet&, TTree*, BEANhelper*);
		~QuickFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void analyze(const Event&, const EventSetup&);
		void SetupBranches();
		void ClearVectors();

	// ----- Variables ----- //
	private:

		double _PUweight;
		
};

#endif
