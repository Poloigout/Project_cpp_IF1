// Project_C++.cpp
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <stdexcept>

#include "CallOption.h"
#include "PutOption.h"
#include "AsianCallOption.h"
#include "AsianPutOption.h"
#include "BlackScholesPricer.h"
#include "CRRPricer.h"
#include "BinaryTree.h"
#include "MT.h"

int main()
{
	std::cout << std::fixed << std::setprecision(6);

	// ---------- Paramètres ----------
	const double S0 = 100.0;
	const double K = 100.0;
	const double T = 1.0;
	const double r = 0.05;
	const double sigma = 0.2;
	const int    N = 200;

	// Paramètres CRR calibrés sur Black-Scholes : h = T/N
	const double h = T / N;
	const double U = std::exp(sigma * std::sqrt(h)) - 1.0;
	const double D = std::exp(-sigma * std::sqrt(h)) - 1.0;
	const double R = std::exp(r * h) - 1.0;

	CallOption call(T, K);
	PutOption  put(T, K);

	// ---------- 1. Payoffs ----------
	std::cout << "=== Payoffs ===\n";
	std::cout << "Call(110) = " << call.payoff(110.0) << " (attendu 10)\n";
	std::cout << "Call(90)  = " << call.payoff(90.0) << " (attendu 0)\n";
	std::cout << "Put(90)   = " << put.payoff(90.0) << " (attendu 10)\n";
	std::cout << "Put(110)  = " << put.payoff(110.0) << " (attendu 0)\n\n";

	// ---------- 2. Black-Scholes ----------
	std::cout << "=== Black-Scholes ===\n";
	BlackScholesPricer bsCall(&call, S0, r, sigma);
	BlackScholesPricer bsPut(&put, S0, r, sigma);
	double c = bsCall();
	double p = bsPut();
	std::cout << "Call prix  = " << c << " (attendu ~10.4506)\n";
	std::cout << "Put prix   = " << p << " (attendu ~5.5735)\n";
	std::cout << "Call delta = " << bsCall.delta() << " (attendu ~0.6368)\n";
	std::cout << "Put delta  = " << bsPut.delta() << " (attendu ~-0.3632)\n";
	// Parité call-put : C - P = S0 - K e^{-rT}
	std::cout << "Parité C-P = " << (c - p) << " vs " << (S0 - K * std::exp(-r * T)) << "\n\n";

	// ---------- 3. CRR : arbre vs formule fermée ----------
	std::cout << "=== CRR (N = " << N << ") ===\n";
	CRRPricer crrCall(&call, N, S0, U, D, R);
	CRRPricer crrPut(&put, N, S0, U, D, R);
	std::cout << "Call arbre   = " << crrCall(false) << "\n";
	std::cout << "Call fermée  = " << crrCall(true) << "\n";
	std::cout << "Call BS      = " << c << "\n";
	std::cout << "Put arbre    = " << crrPut(false) << "\n";
	std::cout << "Put fermée   = " << crrPut(true) << "\n";
	std::cout << "Put BS       = " << p << "\n\n";

	// Petit arbre pour vérifier get(n, i)
	CRRPricer small(&call, 3, S0, 0.1, -0.1, 0.02);
	std::cout << "Petit arbre (N = 3) : prix = " << small(false) << "\n";
	std::cout << "get(0,0) = " << small.get(0, 0) << "\n";
	std::cout << "get(1,0) = " << small.get(1, 0) << ", get(1,1) = " << small.get(1, 1) << "\n\n";

	// ---------- 4. Options asiatiques ----------
	std::cout << "=== Options asiatiques ===\n";
	std::vector<double> times = { 0.25, 0.5, 0.75, 1.0 };
	AsianCallOption asianCall(times, K);
	AsianPutOption  asianPut(times, K);

	std::vector<double> path = { 102.0, 105.0, 98.0, 107.0 };   // moyenne = 103
	std::cout << "AsianCall payoffPath = " << asianCall.payoffPath(path) << " (attendu 3)\n";
	std::cout << "AsianPut  payoffPath = " << asianPut.payoffPath(path) << " (attendu 0)\n";
	std::cout << "Call européen payoffPath = " << call.payoffPath(path)
		<< " (attendu 7, dernier prix)\n";
	std::cout << "isAsianOption : asiatique = " << asianCall.isAsianOption()
		<< ", européen = " << call.isAsianOption() << "\n";

	try {
		CRRPricer bad(&asianCall, N, S0, U, D, R);
		std::cout << "ERREUR : aucune exception levée\n";
	}
	catch (const std::invalid_argument& e) {
		std::cout << "Exception attendue : " << e.what() << "\n";
	}
	std::cout << "\n";

	// ---------- 5. Validation des paramètres CRR ----------
	std::cout << "=== Validation des paramètres ===\n";
	try { CRRPricer bad(&call, 0, S0, U, D, R); }
	catch (const std::invalid_argument& e) { std::cout << "depth = 0 : " << e.what() << "\n"; }
	try { CRRPricer bad(&call, N, S0, 0.01, -0.01, 0.05); }
	catch (const std::invalid_argument& e) { std::cout << "R hors (D,U) : " << e.what() << "\n"; }
	try { CallOption bad(T, -5.0); }
	catch (const std::invalid_argument& e) { std::cout << "strike < 0 : " << e.what() << "\n"; }
	try { CallOption bad(0.0, K); }
	catch (const std::invalid_argument& e) { std::cout << "expiry = 0 : " << e.what() << "\n"; }
	std::cout << "\n";

	// ---------- 6. BinaryTree ----------
	std::cout << "=== BinaryTree ===\n";
	BinaryTree<int> tree;
	tree.setDepth(3);
	int v = 1;
	for (int n = 0; n <= 3; n++)
		for (int i = 0; i <= n; i++)
			tree.setNode(n, i, v++);
	tree.display();
	std::cout << "getNode(2,1) = " << tree.getNode(2, 1) << " (attendu 5)\n";
	try { tree.getNode(4, 0); }
	catch (const std::out_of_range& e) { std::cout << "Exception attendue : " << e.what() << "\n"; }
	std::cout << "\n";

	// ---------- 7. Générateur MT ----------
	std::cout << "=== MT ===\n";
	const int M = 1000000;
	double sumU = 0.0, sumN = 0.0, sumN2 = 0.0;
	for (int k = 0; k < M; k++) {
		sumU += MT::rand_unif();
		double z = MT::rand_norm();
		sumN += z;
		sumN2 += z * z;
	}
	double meanN = sumN / M;
	std::cout << "Moyenne uniforme   = " << sumU / M << " (attendu 0.5)\n";
	std::cout << "Moyenne normale    = " << meanN << " (attendu 0)\n";
	std::cout << "Variance normale   = " << sumN2 / M - meanN * meanN << " (attendu 1)\n";

	return 0;
}