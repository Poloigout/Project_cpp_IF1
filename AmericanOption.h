#pragma once
#include "Option.h"
class AmericanOption: public Option {
protected:
	double _strike;
public:
	AmericanOption(double expiry, double strike);
	bool isAmericanOption() const override;
};