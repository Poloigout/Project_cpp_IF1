#pragma once
#include <random>
class MT {
private:
    std::mt19937_64 generator;
    std::uniform_real_distribution<double> unif;
    std::normal_distribution<double> norm;
    MT() : generator(std::random_device{}()), unif(0.0, 1.0), norm(0.0, 1.0) {}
    MT(const MT&) = delete;
    MT& operator=(const MT&) = delete;
    static MT& getInstance() {
        static MT instance;
        return instance;
    }
public:
    static double rand_unif() {
        MT& m = getInstance();
        return m.unif(m.generator);
    }

    static double rand_norm() {
        MT& m = getInstance();
        return m.norm(m.generator);
    }
};