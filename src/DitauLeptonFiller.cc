// vim: sta:et:sw=4:ts=4
// Author: Nil Valls <nvallsve@nd.edu>

#include "../interface/DitauLeptonFiller.h"

using namespace std;
using namespace edm;
using namespace reco;

// constructors and destructor
DitauLeptonFiller::DitauLeptonFiller(const ParameterSet& iConfig) : NtupleFiller(){
	cerr << "Must not use default constructor of " << __FILE__ << endl; exit(1); 
}

DitauLeptonFiller::DitauLeptonFiller(const ParameterSet& iConfig, TTree* iTree, BEANhelper* iBEANhelper) : NtupleFiller(iConfig, iBEANhelper) {
	_FillerName	= __FILE__;
	_Tree = iTree;
	SetupBranches();

    lep = new AnalysisLepton("TTL_Lepton", _Tree);
    tau1 = new AnalysisTau("TTL_Tau1", _Tree);
    tau2 = new AnalysisTau("TTL_Tau2", _Tree);
}

// === Destructor === //
DitauLeptonFiller::~DitauLeptonFiller()
{
    delete lep;
    delete tau1;
    delete tau2;
}

// ------------ method called to for each event  ------------
void DitauLeptonFiller::analyze(const Event& iEvent, const EventSetup& iSetup){}

// === Setup branches going into the ntuple === //
void DitauLeptonFiller::SetupBranches()
{
	// Set up tree branches
	_Tree->Branch("TTL_NumTaus",&_NumTaus);
	_Tree->Branch("TTL_NumMuons",&_NumMuons);
	_Tree->Branch("TTL_NumElectrons",&_NumElectrons);
	_Tree->Branch("TTL_NumLeptons",&_NumLeptons);
	_Tree->Branch("TTL_NumCombos",&_NumCombos);
	_Tree->Branch("TTL_MomentumRank",&_MomentumRank);

	// === Tau1 === //
	_Tree->Branch("TTL_Tau1MomentumRank", &_Tau1MomentumRank);

	// === Tau2 === //
	_Tree->Branch("TTL_Tau2MomentumRank", &_Tau2MomentumRank);

	// === Lepton === //
	_Tree->Branch("TTL_MuonMomentumRank", &_MuonMomentumRank);
	_Tree->Branch("TTL_ElectronMomentumRank", &_ElectronMomentumRank);
	_Tree->Branch("TTL_LeptonMomentumRank", &_LeptonMomentumRank);
    _Tree->Branch("TTL_NumLooseMuons",&_NumLooseMuons);
    _Tree->Branch("TTL_NumExLooseMuons",&_NumExLooseMuons);
    _Tree->Branch("TTL_NumTightMuons",&_NumTightMuons);
    _Tree->Branch("TTL_NumLooseElectrons",&_NumLooseElectrons);
    _Tree->Branch("TTL_NumExLooseElectrons",&_NumExLooseElectrons);
    _Tree->Branch("TTL_NumTightElectrons",&_NumTightElectrons);

    // === Combo === //
    _Tree->Branch("TTL_DitauVisibleMass", &_DitauVisibleMass);
    _Tree->Branch("TTL_DitauMETMass", &_DitauMETMass);
    _Tree->Branch("TTL_DitauCosDeltaPhi", &_DitauCosDeltaPhi);
    _Tree->Branch("TTL_DitauDeltaR", &_DitauDeltaR);
    _Tree->Branch("TTL_Tau1LeptonDeltaR", &_Tau1LeptonDeltaR);
    _Tree->Branch("TTL_Tau2LeptonDeltaR", &_Tau2LeptonDeltaR);
    _Tree->Branch("TTL_HT", &_HT);
    _Tree->Branch("TTL_NumCSVLbtagJets", &_NumCSVLbtagJets);
    _Tree->Branch("TTL_NumCSVMbtagJets", &_NumCSVMbtagJets);
    _Tree->Branch("TTL_NumCSVTbtagJets", &_NumCSVTbtagJets);
    _Tree->Branch("TTL_NumNonCSVLbtagJets", &_NumNonCSVLbtagJets);
    _Tree->Branch("TTL_NumNonCSVMbtagJets", &_NumNonCSVMbtagJets);
    _Tree->Branch("TTL_NumNonCSVTbtagJets", &_NumNonCSVTbtagJets);
    _Tree->Branch("TTL_NumCleanCSVLbtagJets", &_NumCleanCSVLbtagJets);
    _Tree->Branch("TTL_NumCleanCSVMbtagJets", &_NumCleanCSVMbtagJets);
    _Tree->Branch("TTL_NumCleanCSVTbtagJets", &_NumCleanCSVTbtagJets);
    _Tree->Branch("TTL_NumCleanNonCSVLbtagJets", &_NumCleanNonCSVLbtagJets);
    _Tree->Branch("TTL_NumCleanNonCSVMbtagJets", &_NumCleanNonCSVMbtagJets);
    _Tree->Branch("TTL_NumCleanNonCSVTbtagJets", &_NumCleanNonCSVTbtagJets);
    _Tree->Branch("TTL_CleanJetIndices", &_CleanJetIndices);

    // === Combo weights === //
    _Tree->Branch("TTL_CSVeventWeight", &_CSVeventWeight);
    _Tree->Branch("TTL_CSVeventWeightHFdown", &_CSVeventWeightHFdown);
    _Tree->Branch("TTL_CSVeventWeightHFup", &_CSVeventWeightHFup);
    _Tree->Branch("TTL_CSVeventWeightLFdown", &_CSVeventWeightLFdown);
    _Tree->Branch("TTL_CSVeventWeightLFup", &_CSVeventWeightLFup);
    _Tree->Branch("TTL_CSVeventWeightHFStats1down", &_CSVeventWeightHFStats1down);
    _Tree->Branch("TTL_CSVeventWeightHFStats1up", &_CSVeventWeightHFStats1up);
    _Tree->Branch("TTL_CSVeventWeightLFStats1down", &_CSVeventWeightLFStats1down);
    _Tree->Branch("TTL_CSVeventWeightLFStats1up", &_CSVeventWeightLFStats1up);
    _Tree->Branch("TTL_CSVeventWeightHFStats2down", &_CSVeventWeightHFStats2down);
    _Tree->Branch("TTL_CSVeventWeightHFStats2up", &_CSVeventWeightHFStats2up);
    _Tree->Branch("TTL_CSVeventWeightLFStats2down", &_CSVeventWeightLFStats2down);
    _Tree->Branch("TTL_CSVeventWeightLFStats2up", &_CSVeventWeightLFStats2up);
    _Tree->Branch("TTL_CSVeventWeightCErr1up", &_CSVeventWeightCErr1up);
    _Tree->Branch("TTL_CSVeventWeightCErr1down", &_CSVeventWeightCErr1down);
    _Tree->Branch("TTL_CSVeventWeightCErr2up", &_CSVeventWeightCErr2up);
    _Tree->Branch("TTL_CSVeventWeightCErr2down", &_CSVeventWeightCErr2down);
}

// === Clear vectors that will be used to fill ntuple === //
void DitauLeptonFiller::ClearVectors(){
    lep->ClearVectors();
    tau1->ClearVectors();
    tau2->ClearVectors();

	_NumTaus										= 0;
	_NumLeptons										= 0;
	_NumMuons										= 0;
	_NumElectrons									= 0;
	_NumCombos										= 0;	
	_MomentumRank									.clear();

	// === Tau1 === //
	_Tau1MomentumRank                                   .clear();

	// === Tau2 === //
	_Tau2MomentumRank                                   .clear();

	// === Lepton === //
	_MuonMomentumRank                                   .clear();
	_ElectronMomentumRank                               .clear();
	_LeptonMomentumRank                                 .clear();
	_NumLooseMuons                                      .clear();
	_NumExLooseMuons                                    .clear();
	_NumTightMuons                                      .clear();
	_NumLooseElectrons                                  .clear();
	_NumExLooseElectrons                                .clear();
	_NumTightElectrons                                  .clear();

    // === Combo === //
    _DitauVisibleMass.clear();
    _DitauMETMass.clear();
    _DitauCosDeltaPhi.clear();
    _DitauDeltaR.clear();
    _Tau1LeptonDeltaR.clear();
    _Tau2LeptonDeltaR.clear();
    _HT.clear();
    _NumCSVLbtagJets.clear();
    _NumCSVMbtagJets.clear();
    _NumCSVTbtagJets.clear();
    _NumNonCSVLbtagJets.clear();
    _NumNonCSVMbtagJets.clear();
    _NumNonCSVTbtagJets.clear();
    _NumCleanCSVLbtagJets.clear();
    _NumCleanCSVMbtagJets.clear();
    _NumCleanCSVTbtagJets.clear();
    _NumCleanNonCSVLbtagJets.clear();
    _NumCleanNonCSVMbtagJets.clear();
    _NumCleanNonCSVTbtagJets.clear();
    for (auto& v: _CleanJetIndices)
        v.clear();
    _CleanJetIndices.clear();

    // === Combo weights === //
    _CSVeventWeight.clear();
    _CSVeventWeightLFup.clear();
    _CSVeventWeightLFdown.clear();
    _CSVeventWeightHFup.clear();
    _CSVeventWeightHFdown.clear();

    _CSVeventWeightLFStats1up.clear();
    _CSVeventWeightLFStats1down.clear();
    _CSVeventWeightHFStats1up.clear();
    _CSVeventWeightHFStats1down.clear();

    _CSVeventWeightLFStats2up.clear();
    _CSVeventWeightLFStats2down.clear();
    _CSVeventWeightHFStats2up.clear();
    _CSVeventWeightHFStats2down.clear();

    _CSVeventWeightCErr1up.clear();
    _CSVeventWeightCErr1down.clear();
    _CSVeventWeightCErr2up.clear();
    _CSVeventWeightCErr2down.clear();
}

// === Fill ntuple === //
void DitauLeptonFiller::FillNtuple(const Event& iEvent, const EventSetup& iSetup){

	// Get the object collections from the event
	GetCollections(iEvent, iSetup);

	// Clear vectors
	ClearVectors();

	// Leptons
	BNelectronCollection looseElectrons		= beanHelper->GetSelectedElectrons(_BNelectrons, electronID::electronLoose);
	BNelectronCollection tightElectrons		= beanHelper->GetSelectedElectrons(_BNelectrons, electronID::electronTight);
	BNelectronCollection exLooseElectrons	= beanHelper->GetDifference(looseElectrons, tightElectrons);
	BNmuonCollection looseMuons				= beanHelper->GetSelectedMuons(_BNmuons, muonID::muonLoose);
	BNmuonCollection tightMuons				= beanHelper->GetSelectedMuons(_BNmuons, muonID::muonTight);
	BNmuonCollection exLooseMuons			= beanHelper->GetDifference(looseMuons, tightMuons);

	// Select leptons (tight)
	BNmuonCollection selectedMuons			= tightMuons;
	BNelectronCollection selectedElectrons	= tightElectrons;

    // Taus  (corrected taus currently just account for systematic shifts)
    BNtauCollection correctedTaus =  beanHelper->GetCorrectedTaus(_BNtaus, _sysType);

    // Correct for jet pT
    BNjetCollection correctedJets                           = beanHelper->GetCorrectedJets(_BNjets, _sysType);
    // Apply kinematic requirements on corrected jets
    BNjetCollection selCorrJets                             = beanHelper->GetSelectedJets(correctedJets, 30, 2.4, jetID::jetLoose, '-');
	
    // Make sure we can at least make one TTL combo
	if(correctedTaus.size() < 2 || (selectedMuons.size() + selectedElectrons.size()) < 1){ return; }

	// Tau loops: Tau1 is always leads in pT
	unsigned int theNumberOfTaus1		= 0;
	unsigned int theNumberOfTaus2		= 0;
	unsigned int theNumberOfMuons		= 0;
	unsigned int theNumberOfElectrons	= 0;
	unsigned int theNumberOfLeptons		= 0;

	// Start loop over Taus so select two (if applicable) that form a good (and heaviest) pair
	_NumTaus = correctedTaus.size();
	theNumberOfTaus1 = 0;
	for ( BNtauCollection::const_iterator Tau1 = correctedTaus.begin(); Tau1 != correctedTaus.end(); ++Tau1 ) {
		theNumberOfTaus1++;

		theNumberOfTaus2 = theNumberOfTaus1 + 1;
		for ( BNtauCollection::const_iterator Tau2 = (Tau1 + 1); Tau2 != correctedTaus.end(); ++Tau2 ) {
			theNumberOfTaus2++;

			if( theNumberOfTaus2 <= theNumberOfTaus1 ){ continue; }// Make sure we don't double-count: only compare pairs in which the tau2 iterator is larger than the tau 1 iterator, else skip combo


			// BNtauCollection should be sorted by pT in descending order, but let's make sure, and if not, flip them so Tau1 has the largest pT
			if (Tau1->pt < Tau2->pt){
				BNtauCollection::const_iterator TauTemp = Tau1;
				Tau1 = Tau2;
				Tau2 = TauTemp;
			}

			if(Tau1->pt < _RecoTauMinPt){ continue; }
			if(Tau2->pt < _RecoTauMinPt){ continue; }
			if(fabs(Tau1->eta) > _RecoTauMaxAbsEta ){ continue; }
			if(fabs(Tau2->eta) > _RecoTauMaxAbsEta ){ continue; }
			if(_RecoTauRequireDMF && !(Tau1->HPSdecayModeFinding)){ continue; }
			if(_RecoTauRequireDMF && !(Tau2->HPSdecayModeFinding)){ continue; }


			// Count leptons
			unsigned int numLooseMuons			= GetNumberOfUnmatchedLeptons(*Tau1, *Tau2, looseMuons,			0.15);
			unsigned int numExLooseMuons		= GetNumberOfUnmatchedLeptons(*Tau1, *Tau2, exLooseMuons,		0.15);
			unsigned int numTightMuons			= GetNumberOfUnmatchedLeptons(*Tau1, *Tau2, tightMuons,			0.15);
			unsigned int numLooseElectrons		= GetNumberOfUnmatchedLeptons(*Tau1, *Tau2, looseElectrons,		0.15);
			unsigned int numExLooseElectrons	= GetNumberOfUnmatchedLeptons(*Tau1, *Tau2, exLooseElectrons,	0.15);
			unsigned int numTightElectrons		= GetNumberOfUnmatchedLeptons(*Tau1, *Tau2, tightElectrons,		0.15);


			// Initialize lepton iterators
			BNmuonCollection::const_iterator Muon			= selectedMuons.begin();
			BNelectronCollection::const_iterator Electron	= selectedElectrons.begin();

			_NumMuons		= selectedMuons.size();
			_NumElectrons	= selectedElectrons.size();
			_NumLeptons		= _NumMuons + _NumElectrons;

			theNumberOfMuons		= 0;
			theNumberOfElectrons	= 0;
			theNumberOfLeptons		= 0;
			
			// Lepton loop
			while(Muon != selectedMuons.end() || Electron != selectedElectrons.end()){
				bool useMuon; // Is this a muon or electron?
				if(Muon == selectedMuons.end()){ useMuon = false; } // If no muons, don't use muon
				else{
					if(Electron == selectedElectrons.end()){ useMuon = true;	} // If no electrons, use muon
					else{ useMuon = (Muon->pt > Electron->pt);					} // If both, use highest pT object
				}

				// Prevent overlap with taus
				if(useMuon){ // Lepton is a muon: fill for muon
					if(deltaR(Tau1->eta, Tau1->phi, Muon->eta, Muon->phi) < 0.15){ ++Muon; continue; }
					if(deltaR(Tau2->eta, Tau2->phi, Muon->eta, Muon->phi) < 0.15){ ++Muon; continue; }
				}else{	// Lepton is an electron: fill for electron
					if(deltaR(Tau1->eta, Tau1->phi, Electron->eta, Electron->phi) < 0.15){ ++Electron; continue; }
					if(deltaR(Tau2->eta, Tau2->phi, Electron->eta, Electron->phi) < 0.15){ ++Electron; continue; }
				}

                const BNlepton *lepton = useMuon ? static_cast<const BNlepton*>(&*Muon) : static_cast<const BNlepton*>(&*Electron);

                // Jets and MET and related quantities
                vector<TLorentzVector> non_jets;
                non_jets.push_back(TLorentzVector(Tau1->px, Tau1->py, Tau1->pz, Tau1->energy));
                non_jets.push_back(TLorentzVector(Tau2->px, Tau2->py, Tau2->pz, Tau2->energy));
                non_jets.push_back(TLorentzVector(lepton->px, lepton->py, lepton->pz, lepton->energy));

                std::vector<unsigned int> jet_indices;
                BNjetCollection cleanSelCorrJets = beanHelper->GetCleanJets(selCorrJets, non_jets, 0.25, &jet_indices);
                BNmet correctedMET  = beanHelper->GetCorrectedMET(*(_BNmets.begin()), beanHelper->GetUncorrectedJets(cleanSelCorrJets, _BNjets), _sysType);

                _CleanJetIndices.push_back(jet_indices);

				_MomentumRank.push_back(_MomentumRank.size());
				_NumCombos++;
				theNumberOfLeptons++;

				// Count leptons
				_NumLooseMuons			.push_back(numLooseMuons);
				_NumExLooseMuons		.push_back(numExLooseMuons);
				_NumTightMuons			.push_back(numTightMuons);
				_NumLooseElectrons		.push_back(numLooseElectrons);
				_NumExLooseElectrons	.push_back(numExLooseElectrons);
				_NumTightElectrons		.push_back(numTightElectrons);

                _Tau1MomentumRank.push_back(theNumberOfTaus1-1);
                _Tau2MomentumRank.push_back(theNumberOfTaus2-1);

                tau1->Fill(*Tau1, beanHelper, _BNmcparticles);
                tau2->Fill(*Tau2, beanHelper, _BNmcparticles);
                lep->Fill(lepton, beanHelper, _BNmcparticles, correctedMET);

				// Fill lepton
				_LeptonMomentumRank.push_back(theNumberOfLeptons-1);
				if(useMuon){ // Lepton is a muon: fill for muon
					theNumberOfMuons++;	
					_MuonMomentumRank.push_back(theNumberOfMuons-1);
					_ElectronMomentumRank.push_back(-1);
					FillDitauLepton(*Tau1, *Tau2, *Muon);
				}else{	// Lepton is an electron: fill for electron
					theNumberOfElectrons++;
					_MuonMomentumRank.push_back(-1);
					_ElectronMomentumRank.push_back(theNumberOfElectrons-1);
					FillDitauLepton(*Tau1, *Tau2, *Electron);
				} // End of muon/electron if-statement

				if(useMuon){	_HT.push_back(Tau1->pt + Tau2->pt + Muon->pt + correctedMET.pt + beanHelper->GetHT(cleanSelCorrJets)); }
				else{			_HT.push_back(Tau1->pt + Tau2->pt + Electron->pt + correctedMET.pt + beanHelper->GetHT(cleanSelCorrJets)); }

                // fill total jet weight with clean jets
                _CSVeventWeight.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, _sysType));
               
                // CSV weights for systematics
                if (_sysType == sysType::NA) {
                    _CSVeventWeightLFup.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVLFup));
                    _CSVeventWeightLFdown.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVLFdown));
                    _CSVeventWeightHFup.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVHFup));
                    _CSVeventWeightHFdown.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVHFdown));

                    _CSVeventWeightLFStats1up.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVLFStats1up));
                    _CSVeventWeightLFStats1down.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVLFStats1down));
                    _CSVeventWeightHFStats1up.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVHFStats1up));
                    _CSVeventWeightHFStats1down.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVHFStats1down));

                    _CSVeventWeightLFStats2up.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVLFStats2up));
                    _CSVeventWeightLFStats2down.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVLFStats2down));
                    _CSVeventWeightHFStats2up.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVHFStats2up));
                    _CSVeventWeightHFStats2down.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVHFStats2down));

                    _CSVeventWeightCErr1up.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVCErr1up));
                    _CSVeventWeightCErr1down.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVCErr1down));
                    _CSVeventWeightCErr2up.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVCErr2up));
                    _CSVeventWeightCErr2down.push_back(beanHelper->GetCSVweight(cleanSelCorrJets, sysType::CSVCErr2down));
                }
                
				_DitauMETMass		.push_back(GetComboMassBN(*Tau1, *Tau2, correctedMET));

				_NumCSVLbtagJets	.push_back(beanHelper->GetNumCSVbtags(selCorrJets, 'L'));
				_NumCSVMbtagJets	.push_back(beanHelper->GetNumCSVbtags(selCorrJets, 'M'));
				_NumCSVTbtagJets	.push_back(beanHelper->GetNumCSVbtags(selCorrJets, 'T'));
				_NumNonCSVLbtagJets .push_back(beanHelper->GetNumNonCSVbtags(selCorrJets, 'L'));
				_NumNonCSVMbtagJets .push_back(beanHelper->GetNumNonCSVbtags(selCorrJets, 'M'));
				_NumNonCSVTbtagJets .push_back(beanHelper->GetNumNonCSVbtags(selCorrJets, 'T'));

				_NumCleanCSVLbtagJets	.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'L'));
				_NumCleanCSVMbtagJets	.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'M'));
				_NumCleanCSVTbtagJets	.push_back(beanHelper->GetNumCSVbtags(cleanSelCorrJets, 'T'));
				_NumCleanNonCSVLbtagJets .push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'L'));
				_NumCleanNonCSVMbtagJets .push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'M'));
				_NumCleanNonCSVTbtagJets .push_back(beanHelper->GetNumNonCSVbtags(cleanSelCorrJets, 'T'));

				// Move to the next lepton
				if(useMuon){ ++Muon; }
				else{ ++Electron; }
			
			} // End of lepton while-loop

		} // end of tau2 loop
	} // end of tau1 loop
		
}

void DitauLeptonFiller::FillDitauLepton(const BNtau& Tau1, const BNtau& Tau2, const BNmuon& Muon){
	_DitauVisibleMass	.push_back(GetComboMassBN(Tau1, Tau2));
	_DitauCosDeltaPhi	.push_back(cos(TMath::Abs(normalizedPhi(Tau1.phi - Tau2.phi))));
	_DitauDeltaR		.push_back(reco::deltaR(Tau1.eta, Tau1.phi, Tau2.eta, Tau2.phi));
	_Tau1LeptonDeltaR	.push_back(reco::deltaR(Tau1.eta, Tau1.phi, Muon.eta, Muon.phi));
	_Tau2LeptonDeltaR	.push_back(reco::deltaR(Tau2.eta, Tau2.phi, Muon.eta, Muon.phi));
}

void DitauLeptonFiller::FillDitauLepton(const BNtau& Tau1, const BNtau& Tau2, const BNelectron& Electron){
	_DitauVisibleMass	.push_back(GetComboMassBN(Tau1, Tau2));
	_DitauCosDeltaPhi	.push_back(cos(TMath::Abs(normalizedPhi(Tau1.phi - Tau2.phi))));
	_DitauDeltaR		.push_back(reco::deltaR(Tau1.eta, Tau1.phi, Tau2.eta, Tau2.phi));
	_Tau1LeptonDeltaR	.push_back(reco::deltaR(Tau1.eta, Tau1.phi, Electron.eta, Electron.phi));
	_Tau2LeptonDeltaR	.push_back(reco::deltaR(Tau2.eta, Tau2.phi, Electron.eta, Electron.phi));
}
