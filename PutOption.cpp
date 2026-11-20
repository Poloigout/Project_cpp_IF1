#include "PutOption.h"


PutOption::PutOption(double e, double s) :EuropeanVanillaOption(e, s) {}

optionType PutOption::GetOptionType() const {
	return optionType::Put;
}

double PutOption::payoff(double z) const {
	if (z <= _strike) {
		return _strike - z;
	}
	return 0.0;
}