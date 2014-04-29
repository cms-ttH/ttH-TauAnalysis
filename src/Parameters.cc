#include "../interface/Parameters.h"

Parameters::Parameters(const edm::ParameterSet& p)
{
    std::vector<std::string> params = p.getParameter<std::vector<std::string>>("AnalysisParameters");
    data_ = params[2].find("data") != std::string::npos;
    era_ = params[0];
    leptons_ = std::stoi(params[5].substr(2, 1));
    sample_ = std::stoi(params[3]);
}
