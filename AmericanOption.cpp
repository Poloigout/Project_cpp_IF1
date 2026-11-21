#include "AmericanOption.h"
#include <stdexcept>
AmericanOption::AmericanOption(double expiry, double strike) :Option(expiry), _strike(strike) {
	if (strike <= 0.0) {
		throw std::invalid_argument("The strike must be positive");
	}
}
bool AmericanOption::isAmericanOption()const {
	return true;
}