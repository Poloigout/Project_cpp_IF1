#include "EuropeanDigitalPutOption.h"


#include "EuropeanDigitalOption.h"
EuropeanDigitalPutOption::EuropeanDigitalPutOption(double expiry, double strike) :EuropeanDigitalOption(expiry, strike) {}

optionType EuropeanDigitalPutOption::GetOptionType() const {
	return optionType::Put;
}

double EuropeanDigitalPutOption::payoff(double z) const {
	if (z <= _strike) {
		return 1.0;   // le prix finit en dessous de K → l'option paie 1
	}
	return 0.0;
}