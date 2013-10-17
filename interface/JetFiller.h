// vim: et:sta:sw=4:ts=4
// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _JetFiller_h
#define _JetFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class JetFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit JetFiller(const ParameterSet&);
		explicit JetFiller(const ParameterSet&, TTree*, BEANhelper*);
		~JetFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void analyze(const Event&, const EventSetup&);
		void SetupBranches();
		void ClearVectors();

	// ----- Variables ----- //
	private:
		int					_NumJets;
		vector<float>		_MomentumRank;
		vector<float>		_JetPt;
		vector<float>		_JetEta;
		vector<float>		_JetPhi;
        vector<double> _JetCSV;
        vector<float> _JetCharge;
        vector<float> _JetChargePtWeighed;
        vector<int> _JetPartonId;
        vector<int> _JetPartonMother0Id;
        vector<int> _JetPartonMother1Id;
        vector<int> _JetPartonGrandmother00Id;
        vector<int> _JetPartonGrandmother01Id;
        vector<int> _JetPartonGrandmother10Id;
        vector<int> _JetPartonGrandmother11Id;
        vector<int> _JetPartonStatus;
        vector<int> _JetPartonMother0Status;
        vector<int> _JetPartonMother1Status;
        vector<int> _JetPartonGrandmother00Status;
        vector<int> _JetPartonGrandmother01Status;
        vector<int> _JetPartonGrandmother10Status;
        vector<int> _JetPartonGrandmother11Status;
		vector<float>		_combSecVtxBTag;
		vector<bool>		_combSecVtxLooseBTag;
		vector<bool>		_combSecVtxMediumBTag;
		vector<bool>		_combSecVtxTightBTag;
		
};

#endif
