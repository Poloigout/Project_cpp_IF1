#include "EuropeanVanillaOption.h"
#include "CallOption.h"
CallOption::CallOption(double e,double s):EuropeanVanillaOption(e,s){}

optionType CallOption::GetOptionType() const{
	return optionType::Call;
}

double CallOption::payoff(double z) const {
	if (z >= GetStrike()) {
		return z - GetStrike();
	}
	return 0.0;
}