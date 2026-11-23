#pragma once

#include "EuropeanDigitalOption.h"
#include "EuropeanVanillaOption.h"
class BlackScholesPricer {
private:
	EuropeanVanillaOption* _option;
	EuropeanDigitalOption* _digitalOption;
	double asset_price;
	double interest_rate;
	double volatility;
public:
	BlackScholesPricer(EuropeanVanillaOption* option, double asset_price,double interest_rate, double volatility);
	BlackScholesPricer(EuropeanDigitalOption* option, double asset_price,double interest_rate, double volatility);      // constructeur 2 : digitale
	
	// 1 constructeurs pour chaque pointeur afin de garantir que le compilateur choisisse le bon constructeur après le type de l'argument 
	double operator()()const;
	double delta() const;
	
};