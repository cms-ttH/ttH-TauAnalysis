#include <vector>

#include "Math/LorentzVector.h"

#ifdef __MAKECINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all structs;
#pragma link off all functions;

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector;

#pragma link C++ class std::vector<std::vector<bool> >+;
#pragma link C++ class std::vector<std::vector<LorentzVector> >+;

#endif
