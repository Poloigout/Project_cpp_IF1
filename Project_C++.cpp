#include <iostream>
#include <vector>
#include "CallOption.h"
#include "PutOption.h"
#include "BlackScholesPricer.h"
#include "BlackScholesMCPricer.h"

void test(Option* opt, EuropeanVanillaOption* vanilla, const std::string& name,
    double S, double r, double sigma) {
    BlackScholesPricer bs(vanilla, S, r, sigma);
    BlackScholesMCPricer mc(opt, S, r, sigma);

    std::cout << "=== " << name << " ===\n";
    std::cout << "BS prix : " << bs() << "   delta : " << bs.delta() << "\n";

    // Vérifie que generate cumule bien entre deux appels
    mc.generate(1000);
    auto ci = mc.confidenceInterval();
    std::cout << "MC N=" << mc.getNbPaths() << "  prix=" << mc()
        << "  IC=[" << ci[0] << ", " << ci[1] << "]\n";

    mc.generate(999000);
    ci = mc.confidenceInterval();
    std::cout << "MC N=" << mc.getNbPaths() << "  prix=" << mc()
        << "  IC=[" << ci[0] << ", " << ci[1] << "]\n";

    double p = bs();
    std::cout << "Prix BS dans l'IC : "
        << ((p >= ci[0] && p <= ci[1]) ? "OUI" : "NON (peut arriver ~5% du temps)")
        << "\n\n";
}

int main() {
    double S = 100, r = 0.05, sigma = 0.2, T = 1.0, K = 100;

    CallOption call(T, K);
    PutOption put(T, K);

    test(&call, &call, "Call", S, r, sigma);   // BS attendu ~ 10.45
    test(&put, &put, "Put", S, r, sigma);      // BS attendu ~ 5.57

    // Exception si aucun chemin généré
    try {
        BlackScholesMCPricer mc(&call, S, r, sigma);
        mc();
        std::cout << "ERREUR : pas d'exception levee\n";
    }
    catch (const std::exception& e) {
        std::cout << "Exception OK : " << e.what() << "\n";
    }
    return 0;
}