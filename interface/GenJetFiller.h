// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _GenJetFiller_h
#define _GenJetFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class GenJetFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit GenJetFiller(const ParameterSet&);
		explicit GenJetFiller(const ParameterSet&, TTree*, BEANhelper*);
		~GenJetFiller();
		virtual bool FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void analyze(const Event&, const EventSetup&);
		void SetupBranches();
		void ClearVectors();

	// ----- Variables ----- //
	private:
		int					_NumGenJets;
		vector<float>		_MomentumRank;
		vector<float>		_Pt;
		vector<float>		_Eta;
		vector<float>		_Phi;
		vector<bool>		_IsBjet;
		
};

#endif
