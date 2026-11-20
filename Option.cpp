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
