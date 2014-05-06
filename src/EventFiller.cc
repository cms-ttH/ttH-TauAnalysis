// vim: et:sta:sw=4:ts=4
// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/EventFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
EventFiller::EventFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

EventFiller::EventFiller(const ParameterSet& iConfig, TTree* iTree, map<string,BEANhelper*> iBEANhelper) : NtupleFiller(iConfig, iBEANhelper[string("2012ABCD")]) {
    _helpers = iBEANhelper;
	_FillerName	= __FILE__;
	_Tree = iTree;
	SetupBranches();
}

// === Destructor === //
EventFiller::~EventFiller(){}

// ------------ method called to for each event  ------------
void EventFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void EventFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("run", &_runNumber);
	_Tree->Branch("event", &_eventNumber);
	_Tree->Branch("lumi", &_lumiBlock);

    _Tree->Branch("NTruePV", &_numTruePV);

    _Tree->Branch("higgsDecayMode", &_higgsDecayMode);
    _Tree->Branch("bQuarkCount", &_bQuarkCount);
    _Tree->Branch("cQuarkCount", &_cQuarkCount);

	_Tree->Branch("puWeight", &_PUweight);
	_Tree->Branch("puWeightUp", &_PUweightUp);
	_Tree->Branch("puWeightDown", &_PUweightDown);
    _Tree->Branch("topPtWeight", &_topPtWeight);
	_Tree->Branch("topPtWeightUp", &_topPtWeightUp);
	_Tree->Branch("topPtWeightDown", &_topPtWeightDown);
	_Tree->Branch("q2WeightUp", &_q2WeightUp);
	_Tree->Branch("q2WeightDown", &_q2WeightDown);
        // _Tree->Branch("MET", &_MET);
        // _Tree->Branch("METphi", &_METphi);
        // _Tree->Branch("METcov", &_METcov);
	_Tree->Branch("IsTauEvent", &_isTauEvent);

    if(_helpers.size() > 1) {
        _Tree->Branch("puWeight2012A", &_PUweight2012A);
        _Tree->Branch("puWeight2012B", &_PUweight2012B);
        _Tree->Branch("puWeight2012C", &_PUweight2012C);
        _Tree->Branch("puWeight2012D", &_PUweight2012D);
        _Tree->Branch("puWeight2012AB", &_PUweight2012AB);
        _Tree->Branch("puWeight2012BC", &_PUweight2012BC);
        _Tree->Branch("puWeight2012CD", &_PUweight2012CD);
        _Tree->Branch("puWeight2012ABC", &_PUweight2012ABC);
    }

}

// === Clear vectors that will be used to fill ntuple === //
void EventFiller::ClearVectors(){

	_runNumber					= 0;
	_eventNumber				= 0;
	_lumiBlock					= 0;

    _higgsDecayMode = 0;
    _bQuarkCount = 0;
    _cQuarkCount = 0;

    _numTruePV = 0;

	_PUweight					= 1.0;
	_PUweightUp					= 1.0;
	_PUweightDown   			= 1.0;
    _topPtWeight                = 1.0;
    _topPtWeightUp              = 1.0;
    _topPtWeightDown            = 1.0;
    _q2WeightUp                 = 1.0;
    _q2WeightDown               = 1.0;
    _isTauEvent                 = false;
	_MET						= 0;
	_METphi						= 0;
    _METcov.clear();
    
    if(_helpers.size() > 1) {
        _PUweight2012A   = 1.0;
        _PUweight2012B   = 1.0;
        _PUweight2012C   = 1.0;
        _PUweight2012D   = 1.0;
        _PUweight2012AB  = 1.0;
        _PUweight2012BC  = 1.0;
        _PUweight2012CD  = 1.0;
        _PUweight2012ABC = 1.0;
    }

}

// === Fill ntuple === //
bool
EventFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup)
{
	GetCollections(iEvent, iSetup);
	ClearVectors();

	// Event info
	_runNumber			= iEvent.id().run();
	_eventNumber		= iEvent.id().event();
	_lumiBlock			= iEvent.id().luminosityBlock();

    // Flavor and Higgs decay mode splitting info
    // To be used with the inclusive ttH sample and/or ttbar samples
    int sample = params_.get_sample_number();

    // The inclusive ttH sample numbers are 9000 + mass in GeV
    if (sample >= 9000) {
        hdecayType::hdecayType t = helper->GetHdecayType(_BNmcparticles);
        if (t == hdecayType::hbb) {
            _higgsDecayMode = 0;
        } else if (t == hdecayType::hcc) {
            _higgsDecayMode = 1;
        } else if (t == hdecayType::hww) {
            _higgsDecayMode = 2;
        } else if (t == hdecayType::hzz) {
            _higgsDecayMode = 3;
        } else if (t == hdecayType::htt) {
            _higgsDecayMode = 4;
        } else if (t == hdecayType::hgg) {
            _higgsDecayMode = 5;
        } else if (t == hdecayType::hjj) {
            _higgsDecayMode = 6;
        } else if (t == hdecayType::hzg) {
            _higgsDecayMode = 7;
        } else {
            _higgsDecayMode = -1;
        }
    } else {
        _higgsDecayMode = -1;
    }

    // The ttbar samples are 2533, 2563, 2566
    if (sample == 2533 || sample == 2563 || sample == 2566) {
        int bs = helper->ttPlusBBClassifyEvent(_BNmcparticles, _BNjets);
        if (bs == 1 || bs == 2) {
            _bQuarkCount = 1;
        } else if (bs > 2) {
            _bQuarkCount = 2;
        } else {
            _bQuarkCount = 0;
        }
    } else {
        _bQuarkCount = 0;
        _cQuarkCount = 0;
    }

    _numTruePV = _BNevents.begin()->numTruePV;

	// Pileup weights
	_PUweight				= helper->GetPUweight(_BNevents.begin()->numTruePV);
	_PUweightUp				= helper->GetPUweightUp(_BNevents.begin()->numTruePV);
	_PUweightDown			= helper->GetPUweightDown(_BNevents.begin()->numTruePV);

    if(_helpers.size() > 1) {
        _PUweight2012A   = _helpers["2012A"]->GetPUweight(_BNevents.begin()->numTruePV);
        _PUweight2012B   = _helpers["2012B"]->GetPUweight(_BNevents.begin()->numTruePV);
        _PUweight2012C   = _helpers["2012C"]->GetPUweight(_BNevents.begin()->numTruePV);
        _PUweight2012D   = _helpers["2012D"]->GetPUweight(_BNevents.begin()->numTruePV);
        _PUweight2012AB  = _helpers["2012AB"]->GetPUweight(_BNevents.begin()->numTruePV);
        _PUweight2012BC  = _helpers["2012BC"]->GetPUweight(_BNevents.begin()->numTruePV);
        _PUweight2012CD  = _helpers["2012CD"]->GetPUweight(_BNevents.begin()->numTruePV);
        _PUweight2012ABC = _helpers["2012ABC"]->GetPUweight(_BNevents.begin()->numTruePV);
    }

	// MET
	BNjetCollection correctedJets							= helper->GetCorrectedJets(_BNjets, _sysType);
	BNjetCollection selCorrJets								= helper->GetSelectedJets(correctedJets, 30, 2.4, jetID::jetLoose, '-');
    BNjetCollection selUncorrJets;
    // for (const auto& j: selCorrJets)
        // selUncorrJets.push_back(*j.uncorrected);
	BNmet correctedMET	= helper->GetCorrectedMET(*(_BNmets.begin()), selUncorrJets, _sysType);
	_MET				= correctedMET.pt;
	_METphi				= correctedMET.phi;
    _METcov = {correctedMET.sigmaX2, correctedMET.sigmaXY, correctedMET.sigmaYX, correctedMET.sigmaY2};

    // top PT
    _topPtWeight = helper->GetTopPtweight(_BNmcparticles);
    _topPtWeightUp = helper->GetTopPtweightUp(_BNmcparticles);
    _topPtWeightDown = helper->GetTopPtweightDown(_BNmcparticles);
    
    // tau
    _isTauEvent         = helper->IsTauEvent(_BNtaus, _BNjets, _BNelectrons, _BNmuons, _sysType);

    // Q^2 weights
    _q2WeightUp = helper->GetQ2ScaleUp(*(_BNevents.begin()));
    _q2WeightDown = helper->GetQ2ScaleDown(*(_BNevents.begin()));

    return true;
}
