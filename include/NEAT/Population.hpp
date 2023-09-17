#ifndef __NEAT_POPULATION_HPP__
#define __NEAT_POPULATION_HPP__

#include "./Genome.hpp"
#include "./config.hpp"

namespace NEAT {

    // forward declaration
    template <typename dType, typename T2>
    class Genome;
    template <typename dType>
    struct MutationConfig;

    template <typename dType>
    struct SpeciesConfig;

    /**
     * @brief Class for Genome storage, handling, and interaction from environment
     *
     * @tparam dType type of data
     * @tparam T2 type of innovation number
     */
    template <typename dType = double, typename T2 = int>
    class Population final {
    public:
        Population(T2 inputSize, T2 outputSize, T2 populationSize, MutationConfig<dType> mutationConfig, SpeciesConfig<dType> speciesConfig);
        ~Population();

        const std::vector<Genome<dType, T2>*>& startNextGeneration();
        const std::vector<Genome<dType, T2>*>& startNextGeneration(T2 populationSize);
        const std::vector<Genome<dType, T2>*>& startNextGeneration(std::vector<dType> fitnesses);
        const std::vector<Genome<dType, T2>*>& startNextGeneration(T2 populationSize, std::vector<dType> fitnesses);
        // 
        const std::vector<Genome<dType, T2>*>& getGenomes() const;
        const Genome<dType, T2>* getGenome(T2 index) const;
        const T2& getPopulationSize() const;
        const T2& getInputSize() const;
        const T2& getOutputSize() const;
        const T2& getGeneration() const;
        const MutationConfig<dType>& getMutationConfig() const;
        const SpeciesConfig<dType>& getSpeciesConfig() const;
        // 
        const std::vector<dType>& getBestFitnessHistory() const;
        const std::vector<dType>& getAverageFitnessHistory() const;
        const std::vector<dType>& getWorstFitnessHistory() const;
        const std::vector<Genome<dType, T2>*>& getBestGenomeHistory() const;

        void setMutationConfig(MutationConfig<dType> mutationConfig);
        void setSpeciesConfig(SpeciesConfig<dType> speciesConfig);

        void print(int tabSize) const;

    private:
        std::vector<Genome<dType, T2>*> genomes;
        T2 inputSize;
        T2 outputSize;
        T2 populationSize;
        T2 generation = -1;
        MutationConfig<dType> mutationConfig;
        SpeciesConfig<dType> speciesConfig;
        std::vector<dType> bestFitnessHistory;
        std::vector<dType> averageFitnessHistory;
        std::vector<dType> worstFitnessHistory;
        std::vector<Genome<dType, T2>*> bestGenomeHistory;
        // prevent copy and assignment
        Population(const Population<dType, T2>&) = delete;
        Population<dType, T2>& operator=(const Population<dType, T2>&) = delete;
    };
}

#endif // __NEAT_POPULATION_HPP__
