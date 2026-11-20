#include "CRRPricer.h"
#include <cmath>
#include <stdexcept>

CRRPricer::CRRPricer(Option* option, int depth, double asset_price,
	double up, double down, double interest_rate)
	:_option(option), _depth(depth), _asset_price(asset_price),
	_up(up), _down(down), _interest_rate(interest_rate), _computed(false) {

	if (depth <= 0) {
		throw std::invalid_argument("CRRPricer: the depth must be positive");
	}
	if (asset_price <= 0.0) {
		throw std::invalid_argument("CRRPricer: the asset price must be positive");
	}
	if (!(up > down && down > -1.0)) {
		throw std::invalid_argument("CRRPricer: we need U > D > -1");
	}
	if (!(down < interest_rate && interest_rate < up)) {
		throw std::invalid_argument("CRRPricer: arbitrage opportunity (we need D < R < U)");
	}
	if (option->isAsianOption()) {
		throw std::invalid_argument("CRRPricer: option is an AsianOption");
	}
	_tree.setDepth(depth);
}

void CRRPricer::compute() {
	double q = (_interest_rate - _down) / (_up - _down);
	double ratio = (1.0 + _up) / (1.0 + _down);

	
	double S = _asset_price;
	for (int k = 0; k < _depth; k++) {
		S *= (1.0 + _down);
	}

	
	for (int i = 0; i <= _depth; i++) {
		_tree.setNode(_depth, i, _option->payoff(S));
		S *= ratio;
	}

	for (int n = _depth - 1; n >= 0; n--) {
		for (int i = 0; i <= n; i++) {
			double value = (q * _tree.getNode(n + 1, i + 1) + (1.0 - q) * _tree.getNode(n + 1, i))
				/ (1.0 + _interest_rate);
			_tree.setNode(n, i, value);
		}
	}
	_computed = true;
}

double CRRPricer::get(int n, int i) {
	if (!_computed) {
		compute();
	}
	return _tree.getNode(n, i);
}

double CRRPricer::operator()(bool closed_form) {
	if (closed_form) {
		double q = (_interest_rate - _down) / (_up - _down);
		double ratio = (1.0 + _up) / (1.0 + _down);
		double sum = 0.0;

		
		double S = _asset_price;
		for (int k = 0; k < _depth; k++) {
			S *= (1.0 + _down);
		}

		for (int i = 0; i <= _depth; i++) {
			
			double log_coeff = std::lgamma(_depth + 1.0) - std::lgamma(i + 1.0) - std::lgamma(_depth - i + 1.0);
			double proba = std::exp(log_coeff + i * std::log(q) + (_depth - i) * std::log(1.0 - q));
			sum += proba * _option->payoff(S);
			S *= ratio;
		}

	
		for (int k = 0; k < _depth; k++) {
			sum /= (1.0 + _interest_rate);
		}
		return sum;
	}
	if (!_computed) {
		compute();
	}
	return _tree.getNode(0, 0);
}