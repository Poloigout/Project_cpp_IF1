#pragma once
class Option {
private:
	double _expiry;
	
public:
	double getExpiry();
	virtual double payoff(double) const= 0;
	Option(double _expiry);
};