#ifndef __NEAT_TEST_HANDLER_HPP__
#define __NEAT_TEST_HANDLER_HPP__

#include <vector>

#include "../../include/NEAT/Genome.hpp"
#include "../../include/NEAT/config.hpp"

namespace NEAT {

    // forward declaration
    template <typename dType>
    struct SpeciesConfig;
    template <typename dType>
    struct MutationConfig;

    template <typename dType, typename T2>
    class TestHandler final {
    public:
        TestHandler(T2 inputSize, T2 outputSize, SpeciesConfig<dType> speciesConfig, MutationConfig<dType> mutationConfig);

        std::vector<Genome<dType, T2>*> produceGenome(T2 n, T2 inputSize = -1, T2 outputSize = -1, bool sameForAll = false) const;
        std::vector<T2> generateRandomIntVector(T2 size, T2 lowerBound, T2 upperBound) const;
        std::vector<dType> generateRandomDoubleVector(T2 size, dType lowerBound, dType upperBound) const;

        std::vector<std::vector<dType>> massFeedForward(const std::vector<Genome<dType, T2>*>& genomes, std::vector<std::vector<dType>>& inputs) const;
        std::vector<std::vector<dType>> massFeedForward(const std::vector<Genome<dType, T2>*>& genomes, std::vector<dType>& inputs) const;

        void massAssignFitness(const std::vector<Genome<dType, T2>*>& genomes, const std::vector<dType>& fitnesses) const;
        void massAssignFitness(const std::vector<Genome<dType, T2>*>& genomes, dType fitness) const;
        void massAssignFitness(const std::vector<Genome<dType, T2>*>& genomes, dType(*fitnessCB)(dType)) const;

        void massMutate(const std::vector<Genome<dType, T2>*>& genomes, int count = 1, MutationConfig<dType> mutationConfig = MutationConfig<dType>()) const;
        void massMutate(Genome<dType, T2>* genomes, int count = 1, MutationConfig<dType> mutationConfig = MutationConfig<dType>()) const;

    private:
        T2 inputSize;
        T2 outputSize;
        // 
        SpeciesConfig<dType> speciesConfig;
        MutationConfig<dType> mutationConfig;
    };
}

#endif // __NEAT_TEST_HANDLER_HPP__
