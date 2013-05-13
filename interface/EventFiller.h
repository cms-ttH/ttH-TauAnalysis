// Authors: Andres Florez, Alfredo Gurrola, Eduardo Luiggi, Chi Nhan Nguyen, Nitish Dhingra, Nil Valls

#ifndef _EventFiller_h
#define _EventFiller_h

#include "../interface/NtupleFiller.h"

using namespace std;

class EventFiller : public NtupleFiller {

	// ----- Functions ----- //
	public:
		explicit EventFiller(const ParameterSet&);
		explicit EventFiller(const ParameterSet&, TTree*, map<string,BEANhelper*>);
		~EventFiller();
		virtual void FillNtuple(const Event&, const EventSetup&);

	private:
		// === Core functions === //
		void analyze(const Event&, const EventSetup&);
		void SetupBranches();
		void ClearVectors();

	// ----- Variables ----- //
	private:
		double                  _runNumber;
		double                  _eventNumber;
		double                  _lumiBlock;

		double                  _MET;
		double                  _METphi;

		double                  _PUweight;
		double                  _PUweightUp;
		double                  _PUweightDown;
		double                  _PUweight2012A;
		double                  _PUweight2012B;
		double                  _PUweight2012C;
		double                  _PUweight2012D;
		double                  _PUweight2012AB;
		double                  _PUweight2012BC;
		double                  _PUweight2012CD;
		double                  _PUweight2012ABC;
		map<string,BEANhelper*> _beanHelpers;
        
		double                  _topPtWeight;
		double                  _topPtWeightUp;
		double                  _topPtWeightDown;

		bool                    _isTauEvent;

		double                  _q2WeightUp;
		double                  _q2WeightDown;
};

#endif
