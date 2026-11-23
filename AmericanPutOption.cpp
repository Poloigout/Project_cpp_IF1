#include "AmericanPutOption.h"

AmericanPutOption::AmericanPutOption(double expiry,double strike):AmericanOption(expiry,strike){}

double AmericanPutOption::payoff(double z) const {
	if (z <= _strike) {
		return _strike - z;
	}
	return 0.0;
}