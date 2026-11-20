// MT.cpp
#include "MT.h"

MT::MT()
{
	_gen.seed(std::random_device{}());
	_unif = std::uniform_real_distribution<double>(0.0, 1.0);
	_norm = std::normal_distribution<double>(0.0, 1.0);
}

MT& MT::instance()
{
	static MT inst;
	return inst;
}

double MT::rand_unif()
{
	MT& mt = instance();
	return mt._unif(mt._gen);
}

double MT::rand_norm()
{
	MT& mt = instance();
	return mt._norm(mt._gen);
}