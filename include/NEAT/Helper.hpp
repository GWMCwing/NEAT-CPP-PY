#ifndef __NEAT_HELPER_HPP__
#define __NEAT_HELPER_HPP__

#include <random>

namespace NEAT {

    template<typename dType = float>
    dType gaussianDistribution(dType mean, dType stdDeviation) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<dType> d(mean, stdDeviation);
        return d(gen);
    }

}

#endif // __NEAT_HELPER_HPP__
