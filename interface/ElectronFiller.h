// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _ElectronFiller_h
#define _ElectronFiller_h

#include "../interface/NtupleFiller.h"

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
		vector<float>		_MomentumRank;
		vector<float>		_ElectronPt;
		vector<float>		_ElectronEta;
		vector<float>		_ElectronPhi;
        vector<float>       _ElectronRelIso;
        vector<bool>        _IsLooseElectron;
        vector<bool>        _IsTightElectron;
		
};

#endif
