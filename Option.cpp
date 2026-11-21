#include "Option.h"
#include <stdexcept>
Option::Option(double e):_expiry(e){
	if (e <= 0.0) {
		throw std::invalid_argument("Option: the expiry must be positive");
	}
	
}
double Option::getExpiry() const {
	return _expiry;
}
double Option::payoffPath(const std::vector<double>& path) const
{
	if (path.empty() == true)
	{
		return 0.0;
	}
	return(payoff(path.back()));
}
bool Option::isAsianOption() const
{
	return false;
}
bool Option::isAmericanOption() const {
	return false;
}