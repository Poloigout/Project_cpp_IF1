#include "BlackScholesPricer.h"
#include <iostream>
#include <cmath>
#include <algorithm>
BlackScholesPricer::BlackScholesPricer(EuropeanVanillaOption* option, double price,
	double interest, double vol):_option(option), asset_price(price), interest_rate(interest), volatility(vol) { }

double normal_cdf(double x) {
	return 0.5 * std::erfc(-x / std::sqrt(2.0));
}
double BlackScholesPricer::operator()() const{

	double d1 = (std::log(asset_price / _option->GetStrike()) + (interest_rate + (volatility * volatility) / 2) * (_option->getExpiry()))/(volatility*std::sqrt(_option->getExpiry()));
	double d2 = d1 - volatility * std::sqrt(_option->getExpiry());
	double price = 0.0;
	if (_option->GetOptionType() == optionType::Call) {
		price = normal_cdf(d1)*asset_price-normal_cdf(d2)* _option->GetStrike()*std::exp(-interest_rate* _option->getExpiry());
	}
	else {
		price = normal_cdf(-d2)* _option->GetStrike()* std::exp(-interest_rate * _option->getExpiry())-normal_cdf(-d1)*asset_price;
	}
	
	return price;
}

double BlackScholesPricer::delta()const {
	double d1=(std::log(asset_price / _option->GetStrike()) + (interest_rate + volatility * volatility / 2.0) * (_option->getExpiry())) / (volatility * std::sqrt(_option->getExpiry()));
	if (_option->GetOptionType() == optionType::Call) {
		return normal_cdf(d1);
	}
	return normal_cdf(d1) - 1.0;
}