#include "EuropeanDigitalCallOption.h"

#include "EuropeanDigitalOption.h"
EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike) :EuropeanDigitalOption(expiry, strike) {}

optionType EuropeanDigitalCallOption::GetOptionType() const {
	return optionType::Call;
}

double EuropeanDigitalCallOption::payoff(double z) const {
	if (z >= _strike) {
		return 1.0; //le prix finit au dessus de k->l'option paie 1
	}
	return 0.0;
}