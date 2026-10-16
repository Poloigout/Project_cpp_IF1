#include "EuropeanVanillaOption.h"

#include <stdexcept>

EuropeanVanillaOption::EuropeanVanillaOption(double _expiry, double _s) :Option(_expiry),_strike(_s) {
	if (_s <= 0.0)
		throw std::invalid_argument("EuropeanVanillaOption: the strike must be positive");
}
double EuropeanVanillaOption::GetStrike()const {
	return _strike;
}