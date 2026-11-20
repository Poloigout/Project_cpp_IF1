#include "EuropeanVanillaOption.h"
#include "CallOption.h"
CallOption::CallOption(double e,double s):EuropeanVanillaOption(e,s){}

optionType CallOption::GetOptionType() const{
	return optionType::Call;
}

double CallOption::payoff(double z) const {
	if (z >= _strike) {
		return z - _strike;
	}
	return 0.0;
}