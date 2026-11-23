#include <iostream>
#include <vector>
#include "CallOption.h"
#include "PutOption.h"
#include "BlackScholesPricer.h"
#include "BlackScholesMCPricer.h"
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"
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

    // === Tests options digitales ===
    std::cout << "\n=== Digitales ===\n";
    EuropeanDigitalCallOption dCall(1.0, 100.0);   // T = 1 an, K = 100
    EuropeanDigitalPutOption  dPut(1.0, 100.0);

    BlackScholesPricer bsDCall(&dCall, 100.0, 0.05, 0.2);   // S = 100, r = 5 %, sigma = 20 %
    BlackScholesPricer bsDPut(&dPut, 100.0, 0.05, 0.2);

    std::cout << "Digital call BS : " << bsDCall() << "   (attendu ~0.5323)\n";
    std::cout << "Digital put  BS : " << bsDPut() << "   (attendu ~0.4189)\n";
    std::cout << "Somme           : " << bsDCall() + bsDPut() << "   (attendu e^-rT ~0.9512)\n";

    std::cout << "Delta digital call : " << bsDCall.delta() << "   (attendu ~0.01876)\n";
    std::cout << "Delta digital put  : " << bsDPut.delta() << "   (attendu ~-0.01876)\n";

    return 0;
}