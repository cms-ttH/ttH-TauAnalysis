// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _DitauElectronFiller_h
#define _DitauElectronFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class DitauElectronFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit DitauElectronFiller(const ParameterSet&);
		explicit DitauElectronFiller(const ParameterSet&, TTree*);
		~DitauElectronFiller();
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
