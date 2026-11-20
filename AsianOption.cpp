#include "AsianOption.h"
#include <numeric>

AsianOption::AsianOption(const std::vector<double>& timeSteps)
    : Option(timeSteps.back()), timeSteps(timeSteps)
{
}

const std::vector<double>& AsianOption::getTimeSteps() const
{
    return timeSteps;
}
double AsianOption::payoffPath(const std::vector<double>& path) const
{
    if (path.empty())
        return 0.0;

    double mean = std::accumulate(path.begin(), path.end(), 0.0) / path.size();
    return payoff(mean);
}
bool AsianOption::isAsianOption() const
{
    return true;
}