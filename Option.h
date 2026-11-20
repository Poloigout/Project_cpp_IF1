#pragma once
#include<vector>
class Option {
private:
	double _expiry;
	
public:
	double getExpiry() const;
	virtual double payoff(double) const= 0;
	Option(double _expiry);
	double payoffPath(const std::vector<double>& path) const;
	virtual bool isAsianOption() const;
};