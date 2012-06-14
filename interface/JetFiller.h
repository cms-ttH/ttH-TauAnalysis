// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _JetFiller_h
#define _JetFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class JetFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit JetFiller(const ParameterSet&);
		explicit JetFiller(const ParameterSet&, TTree*);
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
		vector<float>		_JetNumber;
		vector<float>		_JetPt;
		vector<float>		_JetEta;
		vector<float>		_JetPhi;
		vector<float>		_combSecVtxBTag;
		vector<bool>		_combSecVtxLooseBTag;
		vector<bool>		_combSecVtxMediumBTag;
		vector<bool>		_combSecVtxTightBTag;
		
};

#endif
