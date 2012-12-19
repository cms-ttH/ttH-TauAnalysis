// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _ElectronFiller_h
#define _ElectronFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class ElectronFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit ElectronFiller(const ParameterSet&);
		explicit ElectronFiller(const ParameterSet&, TTree*, BEANhelper*);
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
		vector<int>			_ElectronGenMatchDaughter0Id;
		vector<int>			_ElectronGenMatchDaughter1Id;
		vector<int>			_ElectronGenMatchId;
		vector<int>			_ElectronGenMatchMother0Id;
		vector<int>			_ElectronGenMatchMother1Id;
		vector<int>			_ElectronGenMatchGrandmother00Id;
		vector<int>			_ElectronGenMatchGrandmother01Id;
		vector<int>			_ElectronGenMatchGrandmother10Id;
		vector<int>			_ElectronGenMatchGrandmother11Id;
		vector<int>			_ElectronGenMatchDaughter0Status;
		vector<int>			_ElectronGenMatchDaughter1Status;
		vector<int>			_ElectronGenMatchStatus;
		vector<int>			_ElectronGenMatchMother0Status;
		vector<int>			_ElectronGenMatchMother1Status;
		vector<int>			_ElectronGenMatchGrandmother00Status;
		vector<int>			_ElectronGenMatchGrandmother01Status;
		vector<int>			_ElectronGenMatchGrandmother10Status;
		vector<int>			_ElectronGenMatchGrandmother11Status;
		
};

#endif
