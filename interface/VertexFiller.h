
#ifndef _VertexFiller_h
#define _VertexFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class VertexFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit VertexFiller(const ParameterSet&);
		explicit VertexFiller(const ParameterSet&, TTree*, BEANhelper*);
		~VertexFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void analyze(const Event&, const EventSetup&);
		void SetupBranches();
		void ClearVectors();

	// ----- Variables ----- //
	private:
		int					_numVertices;
        double              _numInteractionsBXm1;
        double              _numInteractionsBX0;
        double              _numInteractionsBXp1;
		vector<float>		_xCoord;
		vector<float>		_xCoordErr;
		vector<float>		_yCoord;
		vector<float>		_yCoordErr;
		vector<float>		_zCoord;
		vector<float>		_zCoordErr;

		vector<float>		_rho;
		vector<float>		_normChiSq;
		vector<float>		_ndof;
		
};

#endif
