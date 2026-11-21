#pragma once
#include <vector>
class Option {
protected:
	double _expiry;
	
public:
	double getExpiry() const;
	virtual double payoff(double) const= 0;
	Option(double);
	virtual ~Option() = default;
	double payoffPath(const std::vector<double>& path) const;
	virtual bool isAsianOption() const;
	virtual bool isAmericanOption() const;
};