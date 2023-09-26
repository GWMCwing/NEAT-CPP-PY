#ifndef __NEAT_HELPER_HPP__
#define __NEAT_HELPER_HPP__

// TODO: template class for all random distributions

#include <random>
#include <math.h>
#include <iostream>

namespace NEAT {

    class Seed {
    public:
        static unsigned int seed;
        static std::mt19937 gen;
        static unsigned int getSeed();
        static void setSeed(unsigned int newSeed);
        static std::mt19937& getGenerator();
    };

    /**
     * @brief Get a random number from a gaussian distribution
     *
     * @tparam dType type of random number
     * @param mean mean of distribution
     * @param stdDeviation standard deviation of distribution
     * @return dType random number
     */
    template<typename dType = double>
    dType gaussianDistribution(dType mean, dType stdDeviation) {
        std::mt19937& gen = Seed::getGenerator();
        std::normal_distribution<dType> d(mean, stdDeviation);
        return d(gen);
    }

    /**
     * @brief Get a random number from a uniform real distribution
     *
     * @tparam dType type of random number
     * @param min min of distribution inclusive
     * @param max max of distribution inclusive
     * @return dType random number
     */
    template <typename dType = double>
    dType uniformDistribution(dType min, dType max) {
        std::mt19937& gen = Seed::getGenerator();
        std::uniform_real_distribution<dType> d(min, max);
        return d(gen);
    }

    /**
     * @brief Get a random number from a uniform discrete distribution
     *
     * @tparam dType type of random number
     * @param min min of distribution inclusive
     * @param max max of distribution inclusive
     * @return dType random number
     */
    template <typename dType = int>
    dType uniformIntDistribution(dType min, dType max) {
        std::mt19937& gen = Seed::getGenerator();
        std::uniform_int_distribution<dType> d(min, max);
        return d(gen);
    }

    inline void coutTab(int tabSize) {
        for (int i = 0; i < tabSize; i++)
            std::cout << '\t';
    }

    // unused
    template <typename T = int>
    T pairFunction(T a, T b) {
        return (a + b) * (a + b + 1) / 2 + b;
    }

    // unused
    template <typename T = int>
    void unPairFunction(T z, T& a, T& b) {
        T w = std::floor((std::sqrt(8 * z + 1) - 1) / 2);
        b = z - (w * w + w) / 2;
        a = w - b;
    }
}

#endif // __NEAT_HELPER_HPP__
