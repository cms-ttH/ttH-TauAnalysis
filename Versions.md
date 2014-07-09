# Ntuple Versions

## v1

* initial skimming, muon track is not embedded in pat muons

## v2

* PF2PAT, still testing

## v3

* fixed muon track embedding

## v4

* same as v3, but processed on ND T3

## v5

* only signal MC, just filter for H->tautau, no lepton or B-tag skim requirements

## v6

* H->bb skim
* >=2 b tags, good e/mu

## v7

* genTauTest
* PAT, gen tau collections, save all event content

## v8

* skim with new (5,5) tau pt cuts

## v9

* v8 skim + 53X

## v10

* 7TeV v8 skim + corrections

## v11

* 7TeV - v8 skim
* 8TeV - run on BEANs - fixes w.r.t v10

## v12

* 8TeV
* run on BEANs + fixes missing fillers in v11

## v13

* 8TeV
* run on BEANs + fix to parentage + skim for 1 loose CSV (0.244)

## v14

* 8TeV
* require 2 loose (0.244) CVS tags

## v15

* 8TeV
* require 1 loose (0.244) CVS tag

## v16

* 8TeV
* require 3 total jets, 2 loose CSV tags, and one base tau

## v17

* 8TeV
* require 3 total jets, 1 loose CSV tags, and one base tau

## v18

* 8TeV
* require 4 total jets, 2 medium CVS tags and one base tau

## v20

* 8TeV
* require 4 total jets, 2 medium CVS tags and one base tau
* run with JES-hfSF-lfSF-TES systematics

## v21

* 8TeV
* require 4 total jets, 1 medium CVS tags and one base tau
* run with JES-hfSF-lfSF-TES systematics

## v22

* 8TeV
* no skim
* no systematics

## v23

* 8TeV
* skim 42201
* no systematics, update CSV reshaping

## v24

* 8TeV
* skim 31101
* no systematics, update CSV reshaping

## v25

* 8TeV
* require 4 total jets, 2 medium CVS tags and one new base tau add top pt
* reweighting run with JES-hfSF-lfSF-TES systematics

## v26

* 8TeV require 3 total jets, 1 medium CVS tag and one new base tau add top
* pt reweighting run with JES-hfSF-lfSF-TES systematics

## v27

* 8TeV require 3 pt>30 jets, 2 medium CVS tags, and one or two loose and
* one iso taus (322021) run with JES-hfSF-lfSF-TES systematics

## v28

* 8TeV require 3 pt>30 jets, 1 medium CVS tag, and two loose and one iso
* taus (311021) run with JES-hfSF-lfSF-TES systematics

## v29

* 8TeV-Fall12BEANs same as v27, tau pt>10, events in NUTs must pass TTL
* check add Q^2 and PU sys branches

## v30

* 8TeV-Fall12BEANs same as v28, tau pt>10, events in NUTs must pass TTL
* check add Q^2 and PU sys branches

## v31

* 8TeV-Spring13BEANs otherwise same as v30

## v32

* 8TeV-Spring13BEANs require >=2 pt>30 jets, >=1 medium CVS tag, and >=2
* loose and >=1 iso taus (211021) added vertex branches q^2 correct in NUT

## v33

* 8TeV-Spring13BEANs require >=2 pt>30 jets, >=2 medium CVS tag, and >=2
* loose and >=1 iso taus (222021) added vertex branches q^2 correct in NUT

## v34

* 8TeV-Spring13BEANs same as v32 only 2012AB, for PU studies

## v35

* 8TeV-Spring13BEANs same as v32 only 2012CPR, for PU studies

## v36

* 8TeV-Fall12BEANs loose skim (211021) bugfix in jet cleaning Q^2 weight
* set in NUT (replaces v30)

## v37

* 8TeV-Fall12BEANs loose skim (222021) bugfix in jet cleaning Q^2 weight
* set in NUT (replaces v29)

## v38

* 8TeV-Spring13BEANs 211021 switch to CSV reweighting

## v39

* 8TeV-Spring13BEANs 222021 switch to CSV reweighting

## v40

* 8TeV-Fall12BEANs 111021 switch to CSV reweighting

## v41

* 8TeV-Spring13BEANs run on s1 - tighten skim to 111021

## v42

* 8TeV-Spring13BEANs s1, 111021 add extra PU weights

## v43

* 8TeV-Spring13BEANs s1, 111021 add extra PU weights test different tau
* filters allow > 1 lepton for Z-peak calibrations

## v44

* 8TeV-Fall12BEANs s2, 211011 add extra PU weights added TT filler

## v45

* 8TeV-Spring13BEANs s1 - 111021 added TT, TLL fillers

## v46

* 8TeV-Spring13BEANs s1 - 111021 added extra CSV weights for charm

## v46

* 8TeV-Spring13BEANs s1 - 111021 increased CSV weight uncertainty for charm

## v47

* 8TeV-Spring13BEANs s1 - 111021 increased CSV weight uncertainty for charm

## v48

* 8TeV-Spring13BEANs s1 - 111021 add double lepton datasets add sample
* splitting bits add clean jet indices

## v49

* 8TeV-Spring13BEANS s1 - 111021 TLL only improve TLL event selection add
* charge branches and missing CSV event weight for TLL

## v50

* 8TeV-Spring13BEANS s1 - 111021 TLL only add impact parameter and delta(z)
* for leptons

## v51

* 8TeV-Spring13BEANS s1 - 111021 TLL only fix DeltaR(lepton, tau) now with
* μ + eγ dataset

## v52

* 8TeV-Spring13BEANS s1 - 111021 TLL only Include trigger scale factors
* Match electron and muon combinations to triggers

## v53

* 8TeV-Spring13BEANS s1 - 111021 TLL and TTL Include Mt for leptons

## v54

* 8TeV-Spring13BEANS s1 - 111021 TLL and TTL include jet parentage

## v54.1

* Bugfix of previous

## v55

* Reproduction of dilepton channel with loose tau requirements

## v56

* Reproduction of dilepton channel with tighter tau requirements

## v57

* Reproduction of dilepton channel with very loose tau Tigther jet
* requirements

## v58

* Reproduction of dilepton channel with non-existant tau

### v58.1

* Fixed skimmer to correct jets

### v58.2

* Introduce Z-peak mask based on MET and dilepton visible mass

### v58.3

* Add Z-peak mask with MET derived from all components used in the analysis
* Also add pt of the vector sum of all components used in the analysis

### v58.4

* Use track charge

### v59.4

* Fix scale factors for leptons

## v59

* Apply changes from dilepton sync to taus Fix skimming of events Introduce
* Z-peak mask based on MET/MHT Add MHT Add Mt of leptons based on MHT in
* addition to MET

## v59.1

* Fix analysis type flags to get correct scale factors

## v59.2

* Add jet, lepton/tau ΔR variables

## v59.3

* Add true vertex count

## v60

* Add new TL channel

## v60.1

* Add Lorentz vectors to leptons, taus

## v60.2

* Add...?

## v61

* Add Δφ between MET and leptons, taus, and jets
* Add the mass of jets, jets + same-sign lepton to tll

## v62

* Add...?

## v63

* Test of Charlie's new projection to clean jets w.r.t. leptons

## v64

* Full run with new ntuple structure and lobster

## v64.1

* Save the CSV value of jets matched to Taus

# Skim Versions

## s1

* 8TeV-Spring13BEANs
* 111011

## s2
* 8TeV-Fall12/Fall12BEANs-BEANS
* 111011
