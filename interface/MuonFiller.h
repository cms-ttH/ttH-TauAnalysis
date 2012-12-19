// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _MuonFiller_h
#define _MuonFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class MuonFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit MuonFiller(const ParameterSet&);
		explicit MuonFiller(const ParameterSet&, TTree*, BEANhelper*);
		~MuonFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void analyze(const Event&, const EventSetup&);
		void SetupBranches();
		void ClearVectors();

	// ----- Variables ----- //
	private:
		int					_NumMuons;
		vector<float>		_MomentumRank;
		vector<float>		_MuonPt;
		vector<float>		_MuonEta;
		vector<float>		_MuonPhi;
        vector<float>       _MuonRelIso;
        vector<bool>        _IsLooseMuon;
        vector<bool>        _IsTightMuon;
		vector<int>			_MuonGenMatchDaughter0Id;
		vector<int>			_MuonGenMatchDaughter1Id;
		vector<int>			_MuonGenMatchId;
		vector<int>			_MuonGenMatchMother0Id;
		vector<int>			_MuonGenMatchMother1Id;
		vector<int>			_MuonGenMatchGrandmother00Id;
		vector<int>			_MuonGenMatchGrandmother01Id;
		vector<int>			_MuonGenMatchGrandmother10Id;
		vector<int>			_MuonGenMatchGrandmother11Id;
		vector<int>			_MuonGenMatchDaughter0Status;
		vector<int>			_MuonGenMatchDaughter1Status;
		vector<int>			_MuonGenMatchStatus;
		vector<int>			_MuonGenMatchMother0Status;
		vector<int>			_MuonGenMatchMother1Status;
		vector<int>			_MuonGenMatchGrandmother00Status;
		vector<int>			_MuonGenMatchGrandmother01Status;
		vector<int>			_MuonGenMatchGrandmother10Status;
		vector<int>			_MuonGenMatchGrandmother11Status;
		
};

#endif
