// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/QuickFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
QuickFiller::QuickFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

QuickFiller::QuickFiller(const ParameterSet& iConfig, TTree* iTree, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper) {
	_FillerName	= __FILE__;
	_Tree = iTree;
	_FileService = NULL;
	SetupBranches();
}

QuickFiller::QuickFiller(const ParameterSet& iConfig, TTree* iTree, Service<TFileService>* iFS, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper){
	_FillerName	= __FILE__;
	_Tree = iTree;
	_FileService = iFS;
	SetupBranches();

	tauMatch					= (*_FileService)->make<TH1D>("TauMatch",			"Tau Match",			20, -10, 10);
	tauMatch_pu					= (*_FileService)->make<TH1D>("TauMatch_PURW",		"Tau Match PURW",		20, -10, 10);
	tauMatchParentVsTauMatch	= (*_FileService)->make<TH2D>("ParentVsMatch",		"Parent Vs Match",		20, -10, 10, 20, -10, 10);
	tauMatchParentVsTauMatch_pu	= (*_FileService)->make<TH2D>("ParentVsMatch_PURW", "Parent Vs Match PURW",	20, -10, 10, 20, -10, 10);

	tau1Match						= (*_FileService)->make<TH1D>("Tau1Match",				"Tau1 Match",					20, -10, 10);
	tau1Match_pu					= (*_FileService)->make<TH1D>("Tau1Match_PURW",			"Tau1 Match PURW",				20, -10, 10);
	tau1MatchParentVsTauMatch		= (*_FileService)->make<TH2D>("ParentVsTau1Match",		"Parent Vs Tau1 Match",			20, -10, 10, 20, -10, 10);
	tau1MatchParentVsTauMatch_pu	= (*_FileService)->make<TH2D>("ParentVsTau1Match_PURW", "Parent Vs Tau1 Match PURW",	20, -10, 10, 20, -10, 10);

	tau2Match						= (*_FileService)->make<TH1D>("Tau2Match",				"Tau2 Match",					20, -10, 10);
	tau2Match_pu					= (*_FileService)->make<TH1D>("Tau2Match_PURW",			"Tau2 Match PURW",				20, -10, 10);
	tau2MatchParentVsTauMatch		= (*_FileService)->make<TH2D>("ParentVsTau2Match",		"Parent Vs Tau2 Match",			20, -10, 10, 20, -10, 10);
	tau2MatchParentVsTauMatch_pu	= (*_FileService)->make<TH2D>("ParentVsTau2Match_PURW", "Parent Vs Tau2 Match PURW",	20, -10, 10, 20, -10, 10);

	tau2MPvsTau1MP					= (*_FileService)->make<TH2F>("tau2MPvsTau1MP", "tau2MPvsTau1MP",    45, -10, 35, 45, -10, 35);


	tau1_fromH_pt						= (*_FileService)->make<TH1F>("tau1_fromH_pt",						"tau1_fromH_pt",					50, 0, 100);
	tau1_fromH_eta						= (*_FileService)->make<TH1F>("tau1_fromH_eta",						"tau1_fromH_eta",					50, -3, -3);
	tau1_fromH_nProngs					= (*_FileService)->make<TH1F>("tau1_fromH_nProngs",					"tau1_fromH_nProngs",				5, 0, 5);
	tau1_fromH_dm						= (*_FileService)->make<TH1F>("tau1_fromH_dm",						"tau1_fromH_dm",					20, 0, 20);
	tau1_fromH_nSignalGammas			= (*_FileService)->make<TH1F>("tau1_fromH_nSignalGammas",			"tau1_fromH_nSignalGammas",			10, 0, 10);
	tau1_fromH_nSignalNeutrals			= (*_FileService)->make<TH1F>("tau1_fromH_nSignalNeutrals",			"tau1_fromH_nSignalNeutrals",		10, 0, 10);
	tau1_fromH_antiElectronIndex		= (*_FileService)->make<TH1F>("tau1_fromH_antiElectronIndex",		"tau1_fromH_antiElectronIndex",		5, 0, 5);
	tau1_fromH_antiMuonIndex			= (*_FileService)->make<TH1F>("tau1_fromH_antiMuonIndex",			"tau1_fromH_antiMuonIndex",			5, 0, 5);
	tau1_fromH_isoIndex					= (*_FileService)->make<TH1F>("tau1_fromH_isoIndex",				"tau1_fromH_isoIndex",				5, 0, 5);
	tau1_fromH_ltPt						= (*_FileService)->make<TH1F>("tau1_fromH_ltPt",					"tau1_fromH_ltPt",					30, 0, 60);
	tau1_fromW_pt						= (*_FileService)->make<TH1F>("tau1_fromW_pt",						"tau1_fromW_pt",					50, 0, 100);
	tau1_fromW_eta						= (*_FileService)->make<TH1F>("tau1_fromW_eta",						"tau1_fromW_eta",					50, -3, -3);
	tau1_fromW_nProngs					= (*_FileService)->make<TH1F>("tau1_fromW_nProngs",					"tau1_fromW_nProngs",				5, 0, 5);
	tau1_fromW_dm						= (*_FileService)->make<TH1F>("tau1_fromW_dm",						"tau1_fromW_dm",					20, 0, 20);
	tau1_fromW_nSignalGammas			= (*_FileService)->make<TH1F>("tau1_fromW_nSignalGammas",			"tau1_fromW_nSignalGammas",			10, 0, 10);
	tau1_fromW_nSignalNeutrals			= (*_FileService)->make<TH1F>("tau1_fromW_nSignalNeutrals",			"tau1_fromW_nSignalNeutrals",		10, 0, 10);
	tau1_fromW_antiElectronIndex		= (*_FileService)->make<TH1F>("tau1_fromW_antiElectronIndex",		"tau1_fromW_antiElectronIndex",		5, 0, 5);
	tau1_fromW_antiMuonIndex			= (*_FileService)->make<TH1F>("tau1_fromW_antiMuonIndex",			"tau1_fromW_antiMuonIndex",			5, 0, 5);
	tau1_fromW_isoIndex					= (*_FileService)->make<TH1F>("tau1_fromW_isoIndex",				"tau1_fromW_isoIndex",				5, 0, 5);
	tau1_fromW_ltPt						= (*_FileService)->make<TH1F>("tau1_fromW_ltPt",					"tau1_fromW_ltPt",					30, 0, 60);
	tau1_fromOther_pt					= (*_FileService)->make<TH1F>("tau1_fromOther_pt",					"tau1_fromOther_pt",				50, 0, 100);
	tau1_fromOther_eta					= (*_FileService)->make<TH1F>("tau1_fromOther_eta",					"tau1_fromOther_eta",				50, -3, -3);
	tau1_fromOther_nProngs				= (*_FileService)->make<TH1F>("tau1_fromOther_nProngs",				"tau1_fromOther_nProngs",			5, 0, 5);
	tau1_fromOther_dm					= (*_FileService)->make<TH1F>("tau1_fromOther_dm",					"tau1_fromOther_dm",				20, 0, 20);
	tau1_fromOther_nSignalGammas		= (*_FileService)->make<TH1F>("tau1_fromOther_nSignalGammas",		"tau1_fromOther_nSignalGammas",		10, 0, 10);
	tau1_fromOther_nSignalNeutrals		= (*_FileService)->make<TH1F>("tau1_fromOther_nSignalNeutrals",		"tau1_fromOther_nSignalNeutrals",	10, 0, 10);
	tau1_fromOther_antiElectronIndex	= (*_FileService)->make<TH1F>("tau1_fromOther_antiElectronIndex",	"tau1_fromOther_antiElectronIndex",	5, 0, 5);
	tau1_fromOther_antiMuonIndex		= (*_FileService)->make<TH1F>("tau1_fromOther_antiMuonIndex",		"tau1_fromOther_antiMuonIndex",		5, 0, 5);
	tau1_fromOther_isoIndex				= (*_FileService)->make<TH1F>("tau1_fromOther_isoIndex",			"tau1_fromOther_isoIndex",			5, 0, 5);
	tau1_fromOther_ltPt					= (*_FileService)->make<TH1F>("tau1_fromOther_ltPt",				"tau1_fromOther_ltPt",				30, 0, 60);
	tau2_fromH_pt						= (*_FileService)->make<TH1F>("tau2_fromH_pt",						"tau2_fromH_pt",					50, 0, 100);
	tau2_fromH_eta						= (*_FileService)->make<TH1F>("tau2_fromH_eta",						"tau2_fromH_eta",					50, -3, -3);
	tau2_fromH_nProngs					= (*_FileService)->make<TH1F>("tau2_fromH_nProngs",					"tau2_fromH_nProngs",				5, 0, 5);
	tau2_fromH_dm						= (*_FileService)->make<TH1F>("tau2_fromH_dm",						"tau2_fromH_dm",					20, 0, 20);
	tau2_fromH_nSignalGammas			= (*_FileService)->make<TH1F>("tau2_fromH_nSignalGammas",			"tau2_fromH_nSignalGammas",			10, 0, 10);
	tau2_fromH_nSignalNeutrals			= (*_FileService)->make<TH1F>("tau2_fromH_nSignalNeutrals",			"tau2_fromH_nSignalNeutrals",		10, 0, 10);
	tau2_fromH_antiElectronIndex		= (*_FileService)->make<TH1F>("tau2_fromH_antiElectronIndex",		"tau2_fromH_antiElectronIndex",		5, 0, 5);
	tau2_fromH_antiMuonIndex			= (*_FileService)->make<TH1F>("tau2_fromH_antiMuonIndex",			"tau2_fromH_antiMuonIndex",			5, 0, 5);
	tau2_fromH_isoIndex					= (*_FileService)->make<TH1F>("tau2_fromH_isoIndex",				"tau2_fromH_isoIndex",				5, 0, 5);
	tau2_fromH_ltPt						= (*_FileService)->make<TH1F>("tau2_fromH_ltPt",					"tau2_fromH_ltPt",					30, 0, 60);
	tau2_fromW_pt						= (*_FileService)->make<TH1F>("tau2_fromW_pt",						"tau2_fromW_pt",					50, 0, 100);
	tau2_fromW_eta						= (*_FileService)->make<TH1F>("tau2_fromW_eta",						"tau2_fromW_eta",					50, -3, -3);
	tau2_fromW_nProngs					= (*_FileService)->make<TH1F>("tau2_fromW_nProngs",					"tau2_fromW_nProngs",				5, 0, 5);
	tau2_fromW_dm						= (*_FileService)->make<TH1F>("tau2_fromW_dm",						"tau2_fromW_dm",					20, 0, 20);
	tau2_fromW_nSignalGammas			= (*_FileService)->make<TH1F>("tau2_fromW_nSignalGammas",			"tau2_fromW_nSignalGammas",			10, 0, 10);
	tau2_fromW_nSignalNeutrals			= (*_FileService)->make<TH1F>("tau2_fromW_nSignalNeutrals",			"tau2_fromW_nSignalNeutrals",		10, 0, 10);
	tau2_fromW_antiElectronIndex		= (*_FileService)->make<TH1F>("tau2_fromW_antiElectronIndex",		"tau2_fromW_antiElectronIndex",		5, 0, 5);
	tau2_fromW_antiMuonIndex			= (*_FileService)->make<TH1F>("tau2_fromW_antiMuonIndex",			"tau2_fromW_antiMuonIndex",			5, 0, 5);
	tau2_fromW_isoIndex					= (*_FileService)->make<TH1F>("tau2_fromW_isoIndex",				"tau2_fromW_isoIndex",				5, 0, 5);
	tau2_fromW_ltPt						= (*_FileService)->make<TH1F>("tau2_fromW_ltPt",					"tau2_fromW_ltPt",					30, 0, 60);
	tau2_fromOther_pt					= (*_FileService)->make<TH1F>("tau2_fromOther_pt",					"tau2_fromOther_pt",				50, 0, 100);
	tau2_fromOther_eta					= (*_FileService)->make<TH1F>("tau2_fromOther_eta",					"tau2_fromOther_eta",				50, -3, -3);
	tau2_fromOther_nProngs				= (*_FileService)->make<TH1F>("tau2_fromOther_nProngs",				"tau2_fromOther_nProngs",			5, 0, 5);
	tau2_fromOther_dm					= (*_FileService)->make<TH1F>("tau2_fromOther_dm",					"tau2_fromOther_dm",				20, 0, 20);
	tau2_fromOther_nSignalGammas		= (*_FileService)->make<TH1F>("tau2_fromOther_nSignalGammas",		"tau2_fromOther_nSignalGammas",		10, 0, 10);
	tau2_fromOther_nSignalNeutrals		= (*_FileService)->make<TH1F>("tau2_fromOther_nSignalNeutrals",		"tau2_fromOther_nSignalNeutrals",	10, 0, 10);
	tau2_fromOther_antiElectronIndex	= (*_FileService)->make<TH1F>("tau2_fromOther_antiElectronIndex",	"tau2_fromOther_antiElectronIndex",	5, 0, 5);
	tau2_fromOther_antiMuonIndex		= (*_FileService)->make<TH1F>("tau2_fromOther_antiMuonIndex",		"tau2_fromOther_antiMuonIndex",		5, 0, 5);
	tau2_fromOther_isoIndex				= (*_FileService)->make<TH1F>("tau2_fromOther_isoIndex",			"tau2_fromOther_isoIndex",			5, 0, 5);
	tau2_fromOther_ltPt					= (*_FileService)->make<TH1F>("tau2_fromOther_ltPt",				"tau2_fromOther_ltPt",				30, 0, 60);
	tau12_fromH_pt						= (*_FileService)->make<TH1F>("tau12_fromH_pt",						"tau12_fromH_pt",					50, 0, 100);
	tau12_fromH_eta						= (*_FileService)->make<TH1F>("tau12_fromH_eta",					"tau12_fromH_eta",					50, -3, -3);
	tau12_fromH_nProngs					= (*_FileService)->make<TH1F>("tau12_fromH_nProngs",				"tau12_fromH_nProngs",				5, 0, 5);
	tau12_fromH_dm						= (*_FileService)->make<TH1F>("tau12_fromH_dm",						"tau12_fromH_dm",					20, 0, 20);
	tau12_fromH_nSignalGammas			= (*_FileService)->make<TH1F>("tau12_fromH_nSignalGammas",			"tau12_fromH_nSignalGammas",		10, 0, 10);
	tau12_fromH_nSignalNeutrals			= (*_FileService)->make<TH1F>("tau12_fromH_nSignalNeutrals",		"tau12_fromH_nSignalNeutrals",		10, 0, 10);
	tau12_fromH_antiElectronIndex		= (*_FileService)->make<TH1F>("tau12_fromH_antiElectronIndex",		"tau12_fromH_antiElectronIndex",	5, 0, 5);
	tau12_fromH_antiMuonIndex			= (*_FileService)->make<TH1F>("tau12_fromH_antiMuonIndex",			"tau12_fromH_antiMuonIndex",		5, 0, 5);
	tau12_fromH_isoIndex				= (*_FileService)->make<TH1F>("tau12_fromH_isoIndex",				"tau12_fromH_isoIndex",				5, 0, 5);
	tau12_fromH_ltPt					= (*_FileService)->make<TH1F>("tau12_fromH_ltPt",					"tau12_fromH_ltPt",					30, 0, 60);
	tau12_fromW_pt						= (*_FileService)->make<TH1F>("tau12_fromW_pt",						"tau12_fromW_pt",					50, 0, 100);
	tau12_fromW_eta						= (*_FileService)->make<TH1F>("tau12_fromW_eta",					"tau12_fromW_eta",					50, -3, -3);
	tau12_fromW_nProngs					= (*_FileService)->make<TH1F>("tau12_fromW_nProngs",				"tau12_fromW_nProngs",				5, 0, 5);
	tau12_fromW_dm						= (*_FileService)->make<TH1F>("tau12_fromW_dm",						"tau12_fromW_dm",					20, 0, 20);
	tau12_fromW_nSignalGammas			= (*_FileService)->make<TH1F>("tau12_fromW_nSignalGammas",			"tau12_fromW_nSignalGammas",		10, 0, 10);
	tau12_fromW_nSignalNeutrals			= (*_FileService)->make<TH1F>("tau12_fromW_nSignalNeutrals",		"tau12_fromW_nSignalNeutrals",		10, 0, 10);
	tau12_fromW_antiElectronIndex		= (*_FileService)->make<TH1F>("tau12_fromW_antiElectronIndex",		"tau12_fromW_antiElectronIndex",	5, 0, 5);
	tau12_fromW_antiMuonIndex			= (*_FileService)->make<TH1F>("tau12_fromW_antiMuonIndex",			"tau12_fromW_antiMuonIndex",		5, 0, 5);
	tau12_fromW_isoIndex				= (*_FileService)->make<TH1F>("tau12_fromW_isoIndex",				"tau12_fromW_isoIndex",				5, 0, 5);
	tau12_fromW_ltPt					= (*_FileService)->make<TH1F>("tau12_fromW_ltPt",					"tau12_fromW_ltPt",					30, 0, 60);
	tau12_fromOther_pt					= (*_FileService)->make<TH1F>("tau12_fromOther_pt",					"tau12_fromOther_pt",				50, 0, 100);
	tau12_fromOther_eta					= (*_FileService)->make<TH1F>("tau12_fromOther_eta",				"tau12_fromOther_eta",				50, -3, -3);
	tau12_fromOther_nProngs				= (*_FileService)->make<TH1F>("tau12_fromOther_nProngs",			"tau12_fromOther_nProngs",			5, 0, 5);
	tau12_fromOther_dm					= (*_FileService)->make<TH1F>("tau12_fromOther_dm",					"tau12_fromOther_dm",				20, 0, 20);
	tau12_fromOther_nSignalGammas		= (*_FileService)->make<TH1F>("tau12_fromOther_nSignalGammas",		"tau12_fromOther_nSignalGammas",	10, 0, 10);
	tau12_fromOther_nSignalNeutrals		= (*_FileService)->make<TH1F>("tau12_fromOther_nSignalNeutrals",	"tau12_fromOther_nSignalNeutrals",	10, 0, 10);
	tau12_fromOther_antiElectronIndex	= (*_FileService)->make<TH1F>("tau12_fromOther_antiElectronIndex",	"tau12_fromOther_antiElectronIndex",5, 0, 5);
	tau12_fromOther_antiMuonIndex		= (*_FileService)->make<TH1F>("tau12_fromOther_antiMuonIndex",		"tau12_fromOther_antiMuonIndex",	5, 0, 5);
	tau12_fromOther_isoIndex			= (*_FileService)->make<TH1F>("tau12_fromOther_isoIndex",			"tau12_fromOther_isoIndex",			5, 0, 5);
	tau12_fromOther_ltPt				= (*_FileService)->make<TH1F>("tau12_fromOther_ltPt",				"tau12_fromOther_ltPt",				30, 0, 60);


}

// === Destructor === //
QuickFiller::~QuickFiller(){}

// ------------ method called to for each event  ------------
void QuickFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void QuickFiller::SetupBranches(){
	ClearVectors();

	// Set up tree branches
	_Tree->Branch("Q_PUweight", &_PUweight);

}

// === Clear vectors that will be used to fill ntuple === //
void QuickFiller::ClearVectors(){

	_PUweight = 1.0;

}

// === Fill ntuple === //
void QuickFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){
	GetCollections(iEvent, iSetup);
	ClearVectors();

	_PUweight               = beanHelper->GetPUweight(_BNevents.begin()->numTruePV);

	// Select muons (tight)
	BNmuonCollection selectedMuons = beanHelper->GetSelectedMuons(_BNmuons, muonID::muonTight);

	// Tau loops: Tau1 is always leads in pT
	unsigned int theNumberOfTaus1 = 0;
	unsigned int theNumberOfTaus2 = 0;
	unsigned int theNumberOfMuons = 0;
	unsigned int theNumberOfCombos = 0;

	// Start loop over Taus so select two (if applicable) that form a good (and heaviest) pair
	_NumTaus = _BNtaus.size();
	theNumberOfTaus1 = 0;
	for ( BNtauCollection::const_iterator Tau1 = _BNtaus.begin(); Tau1 != _BNtaus.end(); ++Tau1 ) {
		if(theNumberOfCombos > 0){ break; }
		theNumberOfTaus1++;

		theNumberOfTaus2 = theNumberOfTaus1 + 1;
		for ( BNtauCollection::const_iterator Tau2 = (Tau1 + 1); Tau2 != _BNtaus.end(); ++Tau2 ) {
			if(theNumberOfCombos > 0){ break; }
			theNumberOfTaus2++;

			if( theNumberOfTaus2 <= theNumberOfTaus1 ){ continue; }// Make sure we don't double-count: only compare pairs in which the tau2 iterator is larger than the tau 1 iterator, else skip combo


			// BNtauCollection should be sorted by pT in descending order, but let's make sure, and if not, flip them so Tau1 has the largest pT
			if (Tau1->pt < Tau2->pt){
				BNtauCollection::const_iterator TauTemp = Tau1;
				Tau1 = Tau2;
				Tau2 = TauTemp;
			}

			if(Tau1->pt < 20){ continue; }
			if(Tau2->pt < 5){ continue; }
			if(fabs(Tau1->eta) > 2.1){ continue; }
			if(fabs(Tau2->eta) > 2.1){ continue; }
			if(!(Tau1->HPSdecayModeFinding)){ continue; }
			if(!(Tau2->HPSdecayModeFinding)){ continue; }
			if(!(Tau1->HPSagainstMuonLoose)){ continue; }
			if(!(Tau2->HPSagainstMuonLoose)){ continue; }

			_NumMuons = selectedMuons.size();
			theNumberOfMuons = 0;
			for ( BNmuonCollection::const_iterator Muon = selectedMuons.begin(); Muon != selectedMuons.end(); ++Muon ) {
				theNumberOfMuons++;


				// =========   NO VECTOR FILLING BEFORE THIS POINT   ========= //

				// Jets and MET and related quantities
				// Correct for jet pT
				BNjetCollection correctedJets                           = beanHelper->GetCorrectedJets(_BNjets, _sysType);

				// Apply kinematic requirements on corrected jets
				BNjetCollection selCorrJets                             = beanHelper->GetSelectedJets(correctedJets, 30, 2.4, jetID::jetLoose, '-');

				// Clean jets from taus and muon
				vector<TLorentzVector> tausAndMuon;
				tausAndMuon.push_back(TLorentzVector(Tau1->px, Tau1->py, Tau1->pz, Tau1->energy));
				tausAndMuon.push_back(TLorentzVector(Tau2->px, Tau2->py, Tau2->pz, Tau2->energy));
				tausAndMuon.push_back(TLorentzVector(Muon->px, Muon->py, Muon->pz, Muon->energy));
				BNjetCollection cleanSelCorrJets						= beanHelper->GetCleanJets(selCorrJets, tausAndMuon, 0.25);

				_NumCSVMbtagJets	.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'M'));
				_NumNonCSVMbtagJets .push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'M'));


				if(_NumCSVMbtagJets.back() != 2){ continue; }
				//if(_NumNonCSVMbtagJets.back() < 1 || _NumNonCSVMbtagJets.back() > 3){ continue; }
				if(_NumNonCSVMbtagJets.back() !=2){ continue; }

				if(theNumberOfCombos > 0){ break; }
				theNumberOfCombos++;


				// ===== DONE WITH SELECTION ==== //
				vector<int> undesiredIDs;
				undesiredIDs.push_back(6);	undesiredIDs.push_back(-6);		// No tops
				undesiredIDs.push_back(12);	undesiredIDs.push_back(-12);	// No e neutrinos
				undesiredIDs.push_back(14);	undesiredIDs.push_back(-14);	// No mu neutrinos
				undesiredIDs.push_back(16);	undesiredIDs.push_back(-16);	// No tau neutrinos
				//undesiredIDs.push_back(24);	undesiredIDs.push_back(-24);	// No W
				undesiredIDs.push_back(25);									// No H
				//undesiredIDs.push_back(21);									// No g

				BNmcparticleCollection status3MCparticles	= beanHelper->GetSelectedMCparticlesByStatus(_BNmcparticles, false, false, true); 
				BNmcparticleCollection selectedMCparticles	= beanHelper->GetUnrejectedMCparticlesByPDGid(status3MCparticles, undesiredIDs);
				//BNmcparticleCollection status2MCparticles	= beanHelper->GetSelectedMCparticlesByStatus(_BNmcparticles, false, true, false); 
				//BNmcparticleCollection selectedMCparticles	= beanHelper->GetUnrejectedMCparticlesByPDGid(status2MCparticles, undesiredIDs);
				BNmcparticle tau1GenMatch = beanHelper->GetMatchedMCparticle(selectedMCparticles, *Tau1, 0.25);
				BNmcparticle tau2GenMatch = beanHelper->GetMatchedMCparticle(selectedMCparticles, *Tau2, 0.25);

				int tau1MatchId = GetMatchId(&tau1GenMatch);
				int tau2MatchId = GetMatchId(&tau2GenMatch);

				tauMatch		->Fill(tau1MatchId);
				tauMatch		->Fill(tau2MatchId);
				tauMatch_pu		->Fill(tau1MatchId, _PUweight);
				tauMatch_pu		->Fill(tau2MatchId, _PUweight);
				tau1Match		->Fill(tau1MatchId);
				tau2Match		->Fill(tau2MatchId);
				tau1Match_pu	->Fill(tau1MatchId, _PUweight);
				tau2Match_pu	->Fill(tau2MatchId, _PUweight);

				int tau1MatchParentId = GetMatchParentId(&tau1GenMatch);
				int tau2MatchParentId = GetMatchParentId(&tau2GenMatch);

				if( tau1GenMatch.mother0Id == tau2GenMatch.mother0Id && abs(tau1GenMatch.mother0Id)==24){ cout << "SAME W! gparents: " << tau1GenMatch.grandMother00Id << "," << tau2GenMatch.grandMother00Id << " DeltaR(tau1,tau2): " << deltaR(Tau1->eta, Tau1->phi, Tau2->eta, Tau2->phi) << " mass: " << GetComboMassBN(*Tau1, *Tau2) << endl; }
				else if( tau1GenMatch.mother0Id == -1*tau2GenMatch.mother0Id && abs(tau1GenMatch.mother0Id)==24){ cout << "DIFF W! gparents: "<< tau1GenMatch.grandMother00Id << "," << tau2GenMatch.grandMother00Id << " DeltaR(tau1,tau2): " << deltaR(Tau1->eta, Tau1->phi, Tau2->eta, Tau2->phi) << " mass: " << GetComboMassBN(*Tau1, *Tau2) << endl; }
				else if( tau1GenMatch.mother0Id == tau2GenMatch.mother0Id && abs(tau1GenMatch.mother0Id)==25){ cout << "SAME H! gparents: " << tau1GenMatch.grandMother00Id << "," << tau2GenMatch.grandMother00Id << " DeltaR(tau1,tau2): " << deltaR(Tau1->eta, Tau1->phi, Tau2->eta, Tau2->phi) << " mass: " << GetComboMassBN(*Tau1, *Tau2) << endl; }


				if(tau1MatchParentId == 0){ beanHelper->DrawFeynman(tau1GenMatch); }
				if(tau2MatchParentId == 0){ beanHelper->DrawFeynman(tau2GenMatch); }

				tauMatchParentVsTauMatch		->Fill(tau1MatchId, tau1MatchParentId); 
				tauMatchParentVsTauMatch		->Fill(tau2MatchId, tau2MatchParentId); 
				tauMatchParentVsTauMatch_pu		->Fill(tau1MatchId, tau1MatchParentId, _PUweight); //*/
				tauMatchParentVsTauMatch_pu		->Fill(tau2MatchId, tau2MatchParentId, _PUweight); //*/
				tau1MatchParentVsTauMatch		->Fill(tau1MatchId, tau1MatchParentId); 
				tau2MatchParentVsTauMatch		->Fill(tau2MatchId, tau2MatchParentId); 
				tau1MatchParentVsTauMatch_pu	->Fill(tau1MatchId, tau1MatchParentId, _PUweight); //*/
				tau2MatchParentVsTauMatch_pu	->Fill(tau2MatchId, tau2MatchParentId, _PUweight); //*/	

				tau2MPvsTau1MP->Fill(tau1MatchId + tau1MatchParentId*9, tau2MatchId + tau2MatchParentId*9);

				if(tau1MatchParentId==1){
					tau1_fromH_pt					->Fill(Tau1->pt,						_PUweight);
					tau1_fromH_eta					->Fill(Tau1->eta,						_PUweight);
					tau1_fromH_nProngs				->Fill(Tau1->numProngs,					_PUweight);
					tau1_fromH_dm					->Fill(Tau1->decayMode,					_PUweight);
					tau1_fromH_nSignalGammas		->Fill(Tau1->numSignalGammas,			_PUweight);
					tau1_fromH_nSignalNeutrals		->Fill(Tau1->numSignalNeutrals,			_PUweight);
					tau1_fromH_antiElectronIndex	->Fill(GetAntiElectronIndex(&(*Tau1)),	_PUweight);
					tau1_fromH_antiMuonIndex		->Fill(GetAntiMuonIndex(&(*Tau1)),		_PUweight);
					tau1_fromH_isoIndex				->Fill(GetIsolationIndex(&(*Tau1)),		_PUweight);
					tau1_fromH_ltPt					->Fill(Tau1->leadingTrackPt,			_PUweight);

					tau12_fromH_pt					->Fill(Tau1->pt,						_PUweight);
					tau12_fromH_eta					->Fill(Tau1->eta,						_PUweight);
					tau12_fromH_nProngs				->Fill(Tau1->numProngs,					_PUweight);
					tau12_fromH_dm					->Fill(Tau1->decayMode,					_PUweight);
					tau12_fromH_nSignalGammas		->Fill(Tau1->numSignalGammas,			_PUweight);
					tau12_fromH_nSignalNeutrals		->Fill(Tau1->numSignalNeutrals,			_PUweight);
					tau12_fromH_antiElectronIndex	->Fill(GetAntiElectronIndex(&(*Tau1)),	_PUweight);
					tau12_fromH_antiMuonIndex		->Fill(GetAntiMuonIndex(&(*Tau1)),		_PUweight);
					tau12_fromH_isoIndex			->Fill(GetIsolationIndex(&(*Tau1)),		_PUweight);
					tau12_fromH_ltPt				->Fill(Tau1->leadingTrackPt,			_PUweight);
				}else if(tau1MatchParentId==2){
					tau1_fromW_pt					->Fill(Tau1->pt,						_PUweight);
					tau1_fromW_eta					->Fill(Tau1->eta,						_PUweight);
					tau1_fromW_nProngs				->Fill(Tau1->numProngs,					_PUweight);
					tau1_fromW_dm					->Fill(Tau1->decayMode,					_PUweight);
					tau1_fromW_nSignalGammas		->Fill(Tau1->numSignalGammas,			_PUweight);
					tau1_fromW_nSignalNeutrals		->Fill(Tau1->numSignalNeutrals,			_PUweight);
					tau1_fromW_antiElectronIndex	->Fill(GetAntiElectronIndex(&(*Tau1)),	_PUweight);
					tau1_fromW_antiMuonIndex		->Fill(GetAntiMuonIndex(&(*Tau1)),		_PUweight);
					tau1_fromW_isoIndex				->Fill(GetIsolationIndex(&(*Tau1)),		_PUweight);
					tau1_fromW_ltPt					->Fill(Tau1->leadingTrackPt,			_PUweight);

					tau12_fromW_pt					->Fill(Tau1->pt,						_PUweight);
					tau12_fromW_eta					->Fill(Tau1->eta,						_PUweight);
					tau12_fromW_nProngs				->Fill(Tau1->numProngs,					_PUweight);
					tau12_fromW_dm					->Fill(Tau1->decayMode,					_PUweight);
					tau12_fromW_nSignalGammas		->Fill(Tau1->numSignalGammas,			_PUweight);
					tau12_fromW_nSignalNeutrals		->Fill(Tau1->numSignalNeutrals,			_PUweight);
					tau12_fromW_antiElectronIndex	->Fill(GetAntiElectronIndex(&(*Tau1)),	_PUweight);
					tau12_fromW_antiMuonIndex		->Fill(GetAntiMuonIndex(&(*Tau1)),		_PUweight);
					tau12_fromW_isoIndex			->Fill(GetIsolationIndex(&(*Tau1)),		_PUweight);
					tau12_fromW_ltPt				->Fill(Tau1->leadingTrackPt,			_PUweight);
				}else if(tau1MatchParentId>0){
					tau1_fromOther_pt					->Fill(Tau1->pt,						_PUweight);
					tau1_fromOther_eta					->Fill(Tau1->eta,						_PUweight);
					tau1_fromOther_nProngs				->Fill(Tau1->numProngs,					_PUweight);
					tau1_fromOther_dm					->Fill(Tau1->decayMode,					_PUweight);
					tau1_fromOther_nSignalGammas		->Fill(Tau1->numSignalGammas,			_PUweight);
					tau1_fromOther_nSignalNeutrals		->Fill(Tau1->numSignalNeutrals,			_PUweight);
					tau1_fromOther_antiElectronIndex	->Fill(GetAntiElectronIndex(&(*Tau1)),	_PUweight);
					tau1_fromOther_antiMuonIndex		->Fill(GetAntiMuonIndex(&(*Tau1)),		_PUweight);
					tau1_fromOther_isoIndex				->Fill(GetIsolationIndex(&(*Tau1)),		_PUweight);
					tau1_fromOther_ltPt					->Fill(Tau1->leadingTrackPt,			_PUweight);

					tau12_fromOther_pt					->Fill(Tau1->pt,						_PUweight);
					tau12_fromOther_eta					->Fill(Tau1->eta,						_PUweight);
					tau12_fromOther_nProngs				->Fill(Tau1->numProngs,					_PUweight);
					tau12_fromOther_dm					->Fill(Tau1->decayMode,					_PUweight);
					tau12_fromOther_nSignalGammas		->Fill(Tau1->numSignalGammas,			_PUweight);
					tau12_fromOther_nSignalNeutrals		->Fill(Tau1->numSignalNeutrals,			_PUweight);
					tau12_fromOther_antiElectronIndex	->Fill(GetAntiElectronIndex(&(*Tau1)),	_PUweight);
					tau12_fromOther_antiMuonIndex		->Fill(GetAntiMuonIndex(&(*Tau1)),		_PUweight);
					tau12_fromOther_isoIndex			->Fill(GetIsolationIndex(&(*Tau1)),		_PUweight);
					tau12_fromOther_ltPt				->Fill(Tau1->leadingTrackPt,			_PUweight);
				}

				if(tau2MatchParentId==1){
					tau2_fromH_pt					->Fill(Tau2->pt,						_PUweight);
					tau2_fromH_eta					->Fill(Tau2->eta,						_PUweight);
					tau2_fromH_nProngs				->Fill(Tau2->numProngs,					_PUweight);
					tau2_fromH_dm					->Fill(Tau2->decayMode,					_PUweight);
					tau2_fromH_nSignalGammas		->Fill(Tau2->numSignalGammas,			_PUweight);
					tau2_fromH_nSignalNeutrals		->Fill(Tau2->numSignalNeutrals,			_PUweight);
					tau2_fromH_antiElectronIndex	->Fill(GetAntiElectronIndex(&(*Tau2)),	_PUweight);
					tau2_fromH_antiMuonIndex		->Fill(GetAntiMuonIndex(&(*Tau2)),		_PUweight);
					tau2_fromH_isoIndex				->Fill(GetIsolationIndex(&(*Tau2)),		_PUweight);
					tau2_fromH_ltPt					->Fill(Tau2->leadingTrackPt,			_PUweight);

					tau12_fromH_pt					->Fill(Tau2->pt,						_PUweight);
					tau12_fromH_eta					->Fill(Tau2->eta,						_PUweight);
					tau12_fromH_nProngs				->Fill(Tau2->numProngs,					_PUweight);
					tau12_fromH_dm					->Fill(Tau2->decayMode,					_PUweight);
					tau12_fromH_nSignalGammas		->Fill(Tau2->numSignalGammas,			_PUweight);
					tau12_fromH_nSignalNeutrals		->Fill(Tau2->numSignalNeutrals,			_PUweight);
					tau12_fromH_antiElectronIndex	->Fill(GetAntiElectronIndex(&(*Tau2)),	_PUweight);
					tau12_fromH_antiMuonIndex		->Fill(GetAntiMuonIndex(&(*Tau2)),		_PUweight);
					tau12_fromH_isoIndex			->Fill(GetIsolationIndex(&(*Tau2)),		_PUweight);
					tau12_fromH_ltPt				->Fill(Tau2->leadingTrackPt,			_PUweight);
				}else if(tau2MatchParentId==2){
					tau2_fromW_pt					->Fill(Tau2->pt,						_PUweight);
					tau2_fromW_eta					->Fill(Tau2->eta,						_PUweight);
					tau2_fromW_nProngs				->Fill(Tau2->numProngs,					_PUweight);
					tau2_fromW_dm					->Fill(Tau2->decayMode,					_PUweight);
					tau2_fromW_nSignalGammas		->Fill(Tau2->numSignalGammas,			_PUweight);
					tau2_fromW_nSignalNeutrals		->Fill(Tau2->numSignalNeutrals,			_PUweight);
					tau2_fromW_antiElectronIndex	->Fill(GetAntiElectronIndex(&(*Tau2)),	_PUweight);
					tau2_fromW_antiMuonIndex		->Fill(GetAntiMuonIndex(&(*Tau2)),		_PUweight);
					tau2_fromW_isoIndex				->Fill(GetIsolationIndex(&(*Tau2)),		_PUweight);
					tau2_fromW_ltPt					->Fill(Tau2->leadingTrackPt,			_PUweight);

					tau12_fromW_pt					->Fill(Tau2->pt,						_PUweight);
					tau12_fromW_eta					->Fill(Tau2->eta,						_PUweight);
					tau12_fromW_nProngs				->Fill(Tau2->numProngs,					_PUweight);
					tau12_fromW_dm					->Fill(Tau2->decayMode,					_PUweight);
					tau12_fromW_nSignalGammas		->Fill(Tau2->numSignalGammas,			_PUweight);
					tau12_fromW_nSignalNeutrals		->Fill(Tau2->numSignalNeutrals,			_PUweight);
					tau12_fromW_antiElectronIndex	->Fill(GetAntiElectronIndex(&(*Tau2)),	_PUweight);
					tau12_fromW_antiMuonIndex		->Fill(GetAntiMuonIndex(&(*Tau2)),		_PUweight);
					tau12_fromW_isoIndex			->Fill(GetIsolationIndex(&(*Tau2)),		_PUweight);
					tau12_fromW_ltPt				->Fill(Tau2->leadingTrackPt,			_PUweight);
				}else if(tau2MatchParentId>0){
					tau2_fromOther_pt					->Fill(Tau2->pt,						_PUweight);
					tau2_fromOther_eta					->Fill(Tau2->eta,						_PUweight);
					tau2_fromOther_nProngs				->Fill(Tau2->numProngs,					_PUweight);
					tau2_fromOther_dm					->Fill(Tau2->decayMode,					_PUweight);
					tau2_fromOther_nSignalGammas		->Fill(Tau2->numSignalGammas,			_PUweight);
					tau2_fromOther_nSignalNeutrals		->Fill(Tau2->numSignalNeutrals,			_PUweight);
					tau2_fromOther_antiElectronIndex	->Fill(GetAntiElectronIndex(&(*Tau2)),	_PUweight);
					tau2_fromOther_antiMuonIndex		->Fill(GetAntiMuonIndex(&(*Tau2)),		_PUweight);
					tau2_fromOther_isoIndex				->Fill(GetIsolationIndex(&(*Tau2)),		_PUweight);
					tau2_fromOther_ltPt					->Fill(Tau2->leadingTrackPt,			_PUweight);

					tau12_fromOther_pt					->Fill(Tau2->pt,						_PUweight);
					tau12_fromOther_eta					->Fill(Tau2->eta,						_PUweight);
					tau12_fromOther_nProngs				->Fill(Tau2->numProngs,					_PUweight);
					tau12_fromOther_dm					->Fill(Tau2->decayMode,					_PUweight);
					tau12_fromOther_nSignalGammas		->Fill(Tau2->numSignalGammas,			_PUweight);
					tau12_fromOther_nSignalNeutrals		->Fill(Tau2->numSignalNeutrals,			_PUweight);
					tau12_fromOther_antiElectronIndex	->Fill(GetAntiElectronIndex(&(*Tau2)),	_PUweight);
					tau12_fromOther_antiMuonIndex		->Fill(GetAntiMuonIndex(&(*Tau2)),		_PUweight);
					tau12_fromOther_isoIndex			->Fill(GetIsolationIndex(&(*Tau2)),		_PUweight);
					tau12_fromOther_ltPt				->Fill(Tau2->leadingTrackPt,			_PUweight);
				}


			}
		}
	}

}

int QuickFiller::GetMatchId(BNmcparticle* iMCparticle){
	int tauMatchId = -1;
	if(abs(iMCparticle->id) == 99){ tauMatchId = -1; } // unmatched
	else if(abs(iMCparticle->id) == 11){ tauMatchId = 1; } // electron
	else if(abs(iMCparticle->id) == 13){ tauMatchId = 2; } // muon
	else if(abs(iMCparticle->id) == 15){ tauMatchId = 3; } // tau
	else if(abs(iMCparticle->id) == 24){ tauMatchId = 4; } // W
	else if(abs(iMCparticle->id) ==  5){ tauMatchId = 5; } // b
	else if(abs(iMCparticle->id) ==  4){ tauMatchId = 6; } // c
	else if(abs(iMCparticle->id) ==  21 || abs(iMCparticle->id) <= 3){ tauMatchId = 7; } // u,d,s,g
	else{ tauMatchId = 0;
		cout << "=== Something else ===" << endl;
		cout << "id................" << iMCparticle->id				<< "\t (" << iMCparticle->status					<< ")"	<< endl; 
		cout << "daughter0Id......." << iMCparticle->daughter0Id		<< "\t (" << iMCparticle->daughter0Status		<< ")"	<< endl; 
		cout << "daughter1Id......." << iMCparticle->daughter1Id		<< "\t (" << iMCparticle->daughter1Status		<< ")"	<< endl; 
		cout << "mother0Id........." << iMCparticle->mother0Id		<< "\t (" << iMCparticle->mother0Status			<< ")"	<< endl; 
		cout << "mother1Id........." << iMCparticle->mother1Id		<< "\t (" << iMCparticle->mother0Status			<< ")"	<< endl; 
		cout << "grandMother00Id..." << iMCparticle->grandMother00Id	<< "\t (" << iMCparticle->grandMother00Status	<< ")"	<< endl; 
		cout << "grandMother01Id..." << iMCparticle->grandMother01Id	<< "\t (" << iMCparticle->grandMother01Status	<< ")"	<< endl; 
		cout << "grandMother10Id..." << iMCparticle->grandMother10Id	<< "\t (" << iMCparticle->grandMother10Status	<< ")"	<< endl; 
		cout << "grandMother11Id..." << iMCparticle->grandMother11Id	<< "\t (" << iMCparticle->grandMother11Status	<< ")"	<< endl; 
	} // Something else
	return tauMatchId;
}

int QuickFiller::GetMatchParentId(BNmcparticle* iMCparticle){
	int tauMatchParentId = -1;
	if( abs(iMCparticle->mother0Id) == 99 ){	tauMatchParentId = -1;	} // No mother...
	else if( abs(iMCparticle->mother0Id) == 25 ){	tauMatchParentId = 1;	} // H
	else if( abs(iMCparticle->mother0Id) == 24 ){	tauMatchParentId = 2;	} // W
	else if( abs(iMCparticle->mother0Id) ==  6 ){	tauMatchParentId = 3;	} // t
	else{											tauMatchParentId = 0;	} // Other

	return tauMatchParentId;

}

unsigned int QuickFiller::GetAntiElectronIndex(const BNtau* iTau){
	unsigned int result = 0;

		 if(iTau->HPSagainstElectronTight){		result = 3; }
	else if(iTau->HPSagainstElectronMedium){	result = 2; }
	else if(iTau->HPSagainstElectronLoose){		result = 1; }

	return result;
}

unsigned int QuickFiller::GetAntiMuonIndex(const BNtau* iTau){
	unsigned int result = 0;

		 if(iTau->HPSagainstMuonTight){		result = 3; }
	else if(iTau->HPSagainstMuonMedium){	result = 2; }
	else if(iTau->HPSagainstMuonLoose){		result = 1; }

	return result;

}

unsigned int QuickFiller::GetIsolationIndex(const BNtau* iTau){
	unsigned int result = 0;

		 if(iTau->HPSbyTightCombinedIsolationDeltaBetaCorr){	result = 4; }
	else if(iTau->HPSbyMediumCombinedIsolationDeltaBetaCorr){	result = 3; }
	else if(iTau->HPSbyLooseCombinedIsolationDeltaBetaCorr){	result = 2; }
	else if(iTau->HPSbyVLooseCombinedIsolationDeltaBetaCorr){	result = 1; }

	return result;

}

