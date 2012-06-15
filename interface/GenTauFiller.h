// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _GenTauFiller_h
#define _GenTauFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class GenTauFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit GenTauFiller(const ParameterSet&);
		explicit GenTauFiller(const ParameterSet&, TTree*);
		~GenTauFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void analyze(const Event&, const EventSetup&);
		void SetupBranches();
		void ClearVectors();

	// ----- Variables ----- //
	private:
		int					_NumGenTaus;
		vector<float>		_MomentumRank;
		vector<float>		_Pt;
		vector<float>		_Eta;
		vector<float>		_Phi;
		vector<float>		_VisPt;
		vector<float>		_VisEta;
		vector<float>		_VisPhi;
		vector<int>			_ParentId;
		vector<bool>		_ToElectron;
		vector<bool>		_ToMuon;
		vector<bool>		_ToHadrons;
		
};

#endif
