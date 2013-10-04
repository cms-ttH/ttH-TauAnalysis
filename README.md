# Ntuplizer for the ttH, H→ττ Analysis

## Setup

In your CMSSW area, use

    cd $CMSSW_BASE/src
    mkdir -p ttH
    git clone https://github.com/matz-e/TTHTauTau-Analysis.git ttH/TauAnalysis

## Producing ntuples

See the `test` directory for `crab` configurations.

## Postproduction

To pre-process files prior to moving them to, e.g., hadoop, do

    split_trees /some/path/vXX /some/other/path/vXX
    rsync -a /some/other/path/vXX /hadoop/path/

## Ntuple storage

The most current ntuples are found in

    /store/user/matze/ttH/
