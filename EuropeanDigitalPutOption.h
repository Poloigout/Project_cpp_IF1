#pragma once
#include "EuropeanDigitalOption.h"
class EuropeanDigitalPutOption :
    public EuropeanDigitalOption
{
public:
    EuropeanDigitalPutOption(double, double);
    virtual optionType GetOptionType() const override;
    double payoff(double z) const override;

};

