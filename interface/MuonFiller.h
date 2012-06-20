// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _MuonFiller_h
#define _MuonFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class MuonFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit MuonFiller(const ParameterSet&);
		explicit MuonFiller(const ParameterSet&, TTree*);
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
        vector<float>       _pfRelIso;
        vector<int>         _isLooseMuon;
        vector<int>         _isTightMuon;
		
};

#endif
