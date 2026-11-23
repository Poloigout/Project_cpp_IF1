#include "BlackScholesPricer.h"
#include "EuropeanDigitalOption.h"

#include <iostream>
#include <cmath>
#include <algorithm>
BlackScholesPricer::BlackScholesPricer(EuropeanVanillaOption* option, double price,
	double interest, double vol):_option(option), _digitalOption(nullptr), asset_price(price), interest_rate(interest), volatility(vol) { }

BlackScholesPricer::BlackScholesPricer(EuropeanDigitalOption* option, double price,double interest, double vol): _option(nullptr), _digitalOption(option),
	asset_price(price), interest_rate(interest), volatility(vol) {}



static double normal_cdf(double x) {
	return 0.5 * std::erfc(-x / std::sqrt(2.0));
}

/*
double BlackScholesPricer::operator()() const{




	// calculs communs aux deux familles 
	double d1 = (std::log(asset_price / _option->_strike) + (interest_rate + (volatility * volatility) / 2) * (_option->getExpiry()))/(volatility*std::sqrt(_option->getExpiry()));
	double d2 = d1 - volatility * std::sqrt(_option->getExpiry());
	double price = 0.0;
	if (_option->GetOptionType() == optionType::Call) {
		price = normal_cdf(d1)*asset_price-normal_cdf(d2)* _option->_strike*std::exp(-interest_rate* _option->getExpiry());
	}
	else {
		price = normal_cdf(-d2)* _option->_strike * std::exp(-interest_rate * _option->getExpiry())-normal_cdf(-d1)*asset_price;
	}
	
	return price;
}
*/


double BlackScholesPricer::operator()() const {
    // 1. Récupérer K et T dans l'option qui est remplie
    double K, T;
    if (_option != nullptr) {
        K = _option->_strike;  // le strike de la vanille
        T = _option->getExpiry();  // l'échéance de la vanille 
           
    }
    else {
        K = _digitalOption->_strike;     // le strike de la digitale
        T = _digitalOption->getExpiry();     // l'échéance de la digitale
    }

    // 2. Calculs communs aux deux familles
    double d1 = (std::log(asset_price / K) + (interest_rate + volatility * volatility / 2) * T)
        / (volatility * std::sqrt(T));
    double d2 = d1 - volatility * std::sqrt(T);
    double disc = std::exp(-interest_rate * T);   // facteur d'actualisation e^(-rT)

    // 3. Appliquer la bonne formule
    if (_option != nullptr) {
        // VANILLE
        if (_option->GetOptionType() == optionType::Call)
            return asset_price * normal_cdf(d1) - K * disc * normal_cdf(d2);   // call : S·N(d1) − K·disc·N(d2)
        return K * disc * normal_cdf(-d2) - asset_price * normal_cdf(-d1);       // put  : K·disc·N(−d2) − S·N(−d1)
    }
    else {
        // DIGITALE
        if (_digitalOption->GetOptionType() == optionType::Call)
            return disc * normal_cdf(d2);   // digital call : disc·N(d2)
        return disc * normal_cdf(-d2);       // digital put  : disc·N(−d2)
    }
}


//delta mesure de combien el pricx de l'option bouge quand S bouge de 1. Elle fait donc intervenir la densité de la loi normale et sa fonction de repartition 


static double normal_pdf(double x) {
    // densité de la loi normale centrée réduite : φ(x) = e^(-x²/2) / √(2π)
    return std::exp(-0.5 * x * x) / std::sqrt(2.0 * 3.14159265358979323846);
}

/*
double BlackScholesPricer::delta()const {
	double d1=(std::log(asset_price / _option->_strike) + (interest_rate + volatility * volatility / 2.0) * (_option->getExpiry())) / (volatility * std::sqrt(_option->getExpiry()));
	if (_option->GetOptionType() == optionType::Call) {
		return normal_cdf(d1);
	}
	return normal_cdf(d1) - 1.0;
}
*/


double BlackScholesPricer::delta() const {
    // 1. Récupérer K et T  (identique à operator())
    double K, T;
    if (_option != nullptr) {
        K = _option->_strike;  // le strike de la vanille
        T = _option->getExpiry();  // l'échéance de la vanille 

    }
    else {
        K = _digitalOption->_strike;
        T = _digitalOption->getExpiry();
    }

    // 2. Calculs communs
    double d1 = (std::log(asset_price / K) + (interest_rate + volatility * volatility / 2) * T)/ (volatility * std::sqrt(T));
    double d2 = d1 - volatility * std::sqrt(T);
    double disc = std::exp(-interest_rate * T);   // facteur d'actualisation e^(-rT)    

    // 3. La bonne formule
    if (_option != nullptr) {
        // VANILLE : call → N(d1)     put → N(d1) − 1
        if (_option->GetOptionType() == optionType::Call)
            return normal_cdf(d1); //Call
        return normal_cdf(d1) - 1;
    }
    else {
        
         if (_digitalOption->GetOptionType() == optionType::Call)
            return disc * normal_pdf(d2)/(asset_price*volatility*std::sqrt(T));// DIGITALE : call → disc · φ(d2) / (S · σ · √T)
                        
         return -disc * normal_pdf(d2) / (asset_price * volatility * std::sqrt(T));//digitale: put  → − disc · φ(d2) / (S · σ · √T)
        
    }
}