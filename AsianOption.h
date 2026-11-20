#pragma once
#include "Option.h"

class AsianOption : public Option
{
private:
    std::vector<double> timeSteps;

public:
    AsianOption(const std::vector<double>& timeSteps);
    const std::vector<double>& getTimeSteps() const;
    double payoffPath(const std::vector<double>& path) const;
    bool isAsianOption() const override;
};