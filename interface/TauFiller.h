// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _TauFiller_h
#define _TauFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class TauFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit TauFiller(const ParameterSet&);
		explicit TauFiller(const ParameterSet&, TTree*);
		~TauFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void analyze(const Event&, const EventSetup&);
		void SetupBranches();
		void ClearVectors();

	// ----- Variables ----- //
	private:
		int					_NumTaus;
		vector<float>		_TauNumber;
		vector<float>		_TauPt;
		vector<float>		_TauEta;
		vector<float>		_TauPhi;
		
};

#endif
