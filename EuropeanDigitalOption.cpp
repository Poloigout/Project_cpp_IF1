#include "EuropeanDigitalOption.h"


#include <stdexcept>

EuropeanDigitalOption::EuropeanDigitalOption(double expiry, double strike) :Option(expiry), _strike(strike)

// - Option(expiry) appelle le constructeur de la classe mère et range  léchéance dans _expiry
   
    // - _strike(strike) initialise le membre avec l'arg reçu
{
	if (strike< 0.0) //etant donné que le sujet exige des arguments nonnegative >=0
		throw std::invalid_argument("EuropeanDigitalOption: the strike must be nonnegative");


}
