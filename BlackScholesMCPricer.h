#pragma once
#include <vector>
#include "Option.h"

class BlackScholesMCPricer {
private:
    int NbPaths;
    Option* option;
    double asset_price;
    double interest_rate;
    double volatility;
    double sumPayoff;     
    double sumPayoffSq;   
public:
    BlackScholesMCPricer(Option*, double, double, double);
    int getNbPaths() const;
    void generate(int nb_paths);
    double operator()() const;
    std::vector<double> confidenceInterval() const;
};