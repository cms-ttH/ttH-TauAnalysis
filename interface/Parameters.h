// vim: et:sta:sw=4:ts=4
// Authors: Matthias Wolf <matthias.wolf@cern.ch>

#ifndef _Parameters_h
#define _Parameters_h

#include "FWCore/ParameterSet/interface/ParameterSet.h"

class Parameters {
   public:
      explicit Parameters() {};
      explicit Parameters(const edm::ParameterSet& p);

      inline bool is_data() const { return data_; };
      inline std::string get_era() const { return era_; };
      inline int get_lepton_count() const { return leptons_; };
      inline int get_sample_number() const { return sample_; };

   private:
      bool data_;
      std::string era_;
      int leptons_;
      int sample_;
};

#endif
