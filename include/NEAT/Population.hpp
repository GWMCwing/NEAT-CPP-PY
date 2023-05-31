#ifndef __NEAT_POPULATION_HPP__
#define __NEAT_POPULATION_HPP__

#include "./Genome.hpp"
namespace NEAT {

    // forward declaration
    template <typename dType, typename T2>
    class Genome;

    /**
     * @brief Class for Genome storage, handling, and interaction from environment
     *
     * @tparam dType type of data
     * @tparam T2 type of innovation number
     */
    template <typename dType = double, typename T2 = int>
    class Population final {
    public:
        Population();
        ~Population();
        // TODO:
    };
}

#endif // __NEAT_POPULATION_HPP__
