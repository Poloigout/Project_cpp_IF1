#pragma once
#include "Option.h"
#include "OptionType.h"
class EuropeanVanillaOption : public Option{
protected:
	double _strike;
public:
	EuropeanVanillaOption(double, double);
	virtual optionType GetOptionType() const = 0;
	friend class BlackScholesPricer;
	
};

