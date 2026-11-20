#pragma once
class Option {
protected:
	double _expiry;
	
public:
	double getExpiry() const;
	virtual double payoff(double) const= 0;
	Option(double);
	virtual ~Option() = default;
};