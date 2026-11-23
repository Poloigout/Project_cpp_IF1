#pragma once
#include "EuropeanDigitalOption.h"
class EuropeanDigitalCallOption :
    public EuropeanDigitalOption
{

    
public:
    EuropeanDigitalCallOption(double, double);
    virtual optionType GetOptionType() const override;
    double payoff(double z) const override;


};

