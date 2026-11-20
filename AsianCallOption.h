#pragma once
#pragma once
#include "AsianOption.h"
#include <vector>
class AsianCallOption :public AsianOption
{
private:
	double _strike;

public:
	AsianCallOption(const std::vector<double> timeSteps, double _strike);
	double payoff(double s) const override;
};
