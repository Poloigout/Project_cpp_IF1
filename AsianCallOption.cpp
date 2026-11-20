#include "AsianCallOption.h"

AsianCallOption::AsianCallOption(const std::vector<double> timeSteps, double strike)
	: AsianOption(timeSteps), _strike(strike) {
}

double AsianCallOption::payoff(double s) const
{
	return std::max(s - _strike, 0.0);
}