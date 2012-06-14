// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _ElectronFiller_h
#define _ElectronFiller_h

#include "HighMassAnalysis/Analysis/interface/NtupleFiller.h"

using namespace std;

class ElectronFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit ElectronFiller(const ParameterSet&);
		explicit ElectronFiller(const ParameterSet&, TTree*);
		~ElectronFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void analyze(const Event&, const EventSetup&);
		void SetupBranches();
		void ClearVectors();

	// ----- Variables ----- //
	private:
		int					_NumElectrons;
		vector<float>		_ElectronNumber;
		vector<float>		_ElectronPt;
		vector<float>		_ElectronEta;
		vector<float>		_ElectronPhi;
		
};

#endif
