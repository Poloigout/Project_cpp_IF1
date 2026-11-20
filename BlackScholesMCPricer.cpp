#include "BlackScholesMCPricer.h"
#include "MT.h"
#include <cmath>
#include <stdexcept>

BlackScholesMCPricer::BlackScholesMCPricer(Option* _option, double price,
    double interest, double vol)
    : NbPaths(0), option(_option), asset_price(price),
    interest_rate(interest), volatility(vol),
    sumPayoff(0.0), sumPayoffSq(0.0) {
}

int BlackScholesMCPricer::getNbPaths() const {
    return NbPaths;
}

void BlackScholesMCPricer::generate(int nb_paths) {
    double T = option->getExpiry();
    double disc = std::exp(-interest_rate * T);
    double drift = (interest_rate - 0.5 * volatility * volatility) * T;
    double diff = volatility * std::sqrt(T);

    for (int i = 0; i < nb_paths; ++i) {
        double Z = MT::rand_norm();
        double S = asset_price * std::exp(drift + diff * Z);
        double x = disc * option->payoff(S);
        sumPayoff += x;
        sumPayoffSq += x * x;
        ++NbPaths;
    }
}

double BlackScholesMCPricer::operator()() const {
    if (NbPaths == 0)
        throw std::runtime_error("Estimation indefinie : aucun chemin genere");
    return sumPayoff / NbPaths;
}

std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
    if (NbPaths < 2)
        throw std::runtime_error("Pas assez de chemins pour l'intervalle de confiance");
    double mean = sumPayoff / NbPaths;
    double var = (sumPayoffSq - NbPaths * mean * mean) / (NbPaths - 1);
    double half = 1.96 * std::sqrt(var / NbPaths);
    return { mean - half, mean + half };
}