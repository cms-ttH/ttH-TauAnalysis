// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _EventFiller_h
#define _EventFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class EventFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit EventFiller(const ParameterSet&);
		explicit EventFiller(const ParameterSet&, TTree*);
		~EventFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void analyze(const Event&, const EventSetup&);
		void SetupBranches();
		void ClearVectors();

	// ----- Variables ----- //
	private:
		double				_runNumber;
		double				_eventNumber;
		double				_lumiBlock;
		int					_numInteractionsBXm1;
		int					_numInteractionsBX0;
		int					_numInteractionsBXp1;
		
		double				_MET;
		double				_METphi;
};

#endif
