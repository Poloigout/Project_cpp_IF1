#include "AmericanCallOption.h"
#include <stdexcept>

AmericanCallOption::AmericanCallOption(double expiry, double strike) :AmericanOption(expiry,strike){}

double AmericanCallOption::payoff(double z) const {
	if (z >= _strike) {
		return z - _strike;
	}
	return 0.0;
}
