#pragma once
#include <random>
class MT
{
	public: 
		static double rand_unif();
		static double rand_norm();
		MT(const MT&) = delete;
		MT& operator=(const MT&) = delete;
	private:
		MT();
		~MT()=default;
		static MT& instance();
		std::mt19937 _gen;
		std::uniform_real_distribution<double> _unif;
		std::normal_distribution<double>_norm;
};

