#include <iostream>
#include "CallOption.h"
#include "PutOption.h"
#include "BlackScholesPricer.h"

int main() {
    double expiry = 1.0;
    double strike = 100.0;
    double S0 = 100.0;
    double r = 0.05;
    double sigma = 0.2;

    CallOption Call(expiry, strike);
    PutOption Put(expiry, strike);

    BlackScholesPricer pricerCall(&Call, S0, r, sigma);
    BlackScholesPricer pricerPut(&Put, S0, r, sigma);

    std::cout << "Call price : " << pricerCall() << "\n";
    std::cout << "Call delta : " << pricerCall.delta() << "\n";
    std::cout << "Put price  : " << pricerPut() << "\n";
    std::cout << "Put delta  : " << pricerPut.delta() << "\n";

    return 0;
}