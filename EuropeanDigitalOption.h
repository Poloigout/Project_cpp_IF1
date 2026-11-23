#pragma once
#include "Option.h"
#include "OptionType.h" 

class EuropeanDigitalOption :
    public Option // option digitale "est une" option qui  recupere getExpiry  et doit obligatoirement definri un payoff
{
    protected : 
        double _strike;
    public:
        EuropeanDigitalOption(double, double); //coonstructeur (expiry, strike)
            virtual optionType GetOptionType() const = 0; //constructeur virtuelle
            friend class BlackScholesPricer;


};

