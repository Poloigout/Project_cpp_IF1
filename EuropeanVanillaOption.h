#pragma once // évite que le fichier soit inclus deux fois
#include "Option.h" // la classe mère doit être connue
#include "OptionType.h" // pour pouvoir utiliser l'enum optionType
class EuropeanVanillaOption : public Option{ // hérite d'Option
protected:
	double _strike;
public:
	EuropeanVanillaOption(double, double);
	virtual optionType GetOptionType() const = 0;
	friend class BlackScholesPricer;
	
};

