#include "AsianPutOption.h"
#include <algorithm>
AsianPutOption::AsianPutOption(const std::vector<double> timeSteps, double _strike) : AsianOption(timeSteps), _strike(_strike) {};

double AsianPutOption::payoff(double s) const
{
	return std::max(_strike - s, 0.0);
}