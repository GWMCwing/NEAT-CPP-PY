#include <iostream>

#include "../include/NEAT/Population.hpp"
#include "../include/NEAT/SpeciesHandler.hpp"
#include "../include/NEAT/Species.hpp"
#include "../include/NEAT/GeneHistory.hpp"
#include "../include/NEAT/Helper.hpp"

namespace NEAT {
    template <typename dType, typename T2>
    Population<dType, T2>::Population(T2 inputSize, T2 outputSize, T2 populationSize, MutationConfig<dType> mutationConfig, SpeciesConfig<dType> speciesConfig) :
        inputSize(inputSize), outputSize(outputSize), populationSize(populationSize), mutationConfig(mutationConfig), speciesConfig(speciesConfig) {
        genomes.reserve(populationSize);
        for (T2 i = 0; i < populationSize; i++) {
            genomes.push_back(new Genome<dType, T2>(inputSize, outputSize, true));
        }
        generation = 0;
        GeneHistory<dType, T2> geneHistory = GeneHistory<dType, T2>();
        geneHistory.init(inputSize, outputSize);
    }

    template <typename dType, typename T2>
    Population<dType, T2>::~Population() {
        for (Genome<dType, T2>* genome : genomes) {
            delete genome;
        }
        for (Genome<dType, T2>* genome : bestGenomeHistory) {
            delete genome;
        }
    }

    template <typename dType, typename T2>
    const std::vector<Genome<dType, T2>*>& Population<dType, T2>::getGenomes() const {
        return genomes;
    }

    template <typename dType, typename T2>
    const Genome<dType, T2>* Population<dType, T2>::getGenome(T2 index) const {
        return genomes[index];
    }

    template <typename dType, typename T2>
    const std::vector<Genome<dType, T2>*>& Population<dType, T2>::startNextGeneration() {
        return startNextGeneration(populationSize);
    }

    template <typename dType, typename T2>
    const std::vector<Genome<dType, T2>*>& Population<dType, T2>::startNextGeneration(T2 populationSize) {
        if (populationSize < 1)
            throw std::invalid_argument("Population<dType, T2>::startNextGeneration(T2 populationSize) - populationSize < 1");
        // start next generation
        SpeciesHandler<dType, T2>* speciesHandler = new SpeciesHandler<dType, T2>(genomes, speciesConfig);
        // get next generation
        std::vector<Genome<dType, T2>*> nextGeneration = speciesHandler->reproduce(populationSize, mutationConfig);
        // get best fitness, worst fitness and average fitness
        const Genome<dType, T2>* bestGenome = genomes[0];
        dType bestFitness = genomes[0]->getFitness();
        dType worstFitness = genomes[0]->getFitness();
        dType averageFitness = 0;
        for (Genome<dType, T2>* genome : genomes) {
            if (genome->getFitness() > bestFitness) {
                bestFitness = genome->getFitness();
                bestGenome = genome;
            }
            if (genome->getFitness() < worstFitness) {
                worstFitness = genome->getFitness();
            }
            averageFitness += genome->getFitness();
        }
        averageFitness /= genomes.size();
        // clone best genome
        Genome<dType, T2>* bestGenomeClone = bestGenome->clone();
        // push back
        bestFitnessHistory.push_back(bestFitness);
        worstFitnessHistory.push_back(worstFitness);
        averageFitnessHistory.push_back(averageFitness);
        bestGenomeHistory.push_back(bestGenomeClone);
        // delete old genomes
        for (Genome<dType, T2>* genome : genomes) {
            delete genome;
        }
        genomes.clear();
        // set new genomes
        genomes = nextGeneration;
        // delete species handler
        delete speciesHandler;
        // update generation
        generation++;
        // return genomes
        return genomes;
    }

    template <typename dType, typename T2>
    const std::vector<Genome<dType, T2>*>& Population<dType, T2>::startNextGeneration(std::vector<dType> fitnesses) {
        return startNextGeneration(populationSize, fitnesses);
    }

    template <typename dType, typename T2>
    const std::vector<Genome<dType, T2>*>& Population<dType, T2>::startNextGeneration(T2 populationSize, std::vector<dType> fitnesses) {
        if (static_cast<T2>(fitnesses.size()) < populationSize) {
            throw std::invalid_argument("Population<dType, T2>::startNextGeneration(std::vector<dType> fitnesses) - fitnesses.size() < populationSize");
        }
        if (static_cast<T2>(fitnesses.size()) > populationSize) {
            std::cout << "WARN: Population<dType, T2>::startNextGeneration(std::vector<dType> fitnesses) - fitnesses.size() > populationSize" << std::endl;
        }
        for (T2 i = 0; i < populationSize; i++) {
            genomes[i]->setFitness(fitnesses[i]);
        }
        return startNextGeneration(populationSize);
    }

    template <typename dType, typename T2>
    void Population<dType, T2>::setMutationConfig(MutationConfig<dType> mutationConfig) {
        this->mutationConfig = mutationConfig;
    }

    template <typename dType, typename T2>
    void Population<dType, T2>::setSpeciesConfig(SpeciesConfig<dType> speciesConfig) {
        this->speciesConfig = speciesConfig;
    }

    template <typename dType, typename T2>
    const T2& Population<dType, T2>::getPopulationSize() const {
        return populationSize;
    }

    template <typename dType, typename T2>
    const T2& Population<dType, T2>::getInputSize() const {
        return inputSize;
    }

    template <typename dType, typename T2>
    const T2& Population<dType, T2>::getOutputSize() const {
        return outputSize;
    }

    template <typename dType, typename T2>
    const T2& Population<dType, T2>::getGeneration() const {
        return generation;
    }

    template <typename dType, typename T2>
    const MutationConfig<dType>& Population<dType, T2>::getMutationConfig() const {
        return mutationConfig;
    }

    template <typename dType, typename T2>
    const SpeciesConfig<dType>& Population<dType, T2>::getSpeciesConfig() const {
        return speciesConfig;
    }

    template <typename dType, typename T2>
    const std::vector<dType>& Population<dType, T2>::getBestFitnessHistory() const {
        return bestFitnessHistory;
    }

    template <typename dType, typename T2>
    const std::vector<dType>& Population<dType, T2>::getAverageFitnessHistory() const {
        return averageFitnessHistory;
    }

    template <typename dType, typename T2>
    const std::vector<dType>& Population<dType, T2>::getWorstFitnessHistory() const {
        return worstFitnessHistory;
    }

    template <typename dType, typename T2>
    const std::vector<Genome<dType, T2>*>& Population<dType, T2>::getBestGenomeHistory() const {
        return bestGenomeHistory;
    }

    template <typename dType, typename T2>
    void Population<dType, T2>::print(int tabSize) const {
        coutTab(tabSize);
        std::cout << "Population" << std::endl;
        coutTab(tabSize);
        std::cout << "{" << std::endl;
        coutTab(tabSize + 1);
        std::cout << "populationSize: " << populationSize << std::endl;
        coutTab(tabSize + 1);
        std::cout << "inputSize: " << inputSize << std::endl;
        coutTab(tabSize + 1);
        std::cout << "outputSize: " << outputSize << std::endl;
        coutTab(tabSize + 1);
        std::cout << "generation: " << generation << std::endl;
        coutTab(tabSize + 1);
        //TODO: std::cout << "mutationConfig: " << std::endl;
        std::cout << "Genomes: " << std::endl;
        for (Genome<dType, T2>* genome : genomes) {
            genome->print(tabSize + 1);
        }
        coutTab(tabSize);
        std::cout << "}" << std::endl;
    }

    // Explicit instantiation
    template class Population<double, int>;
    template class Population<double, long>;

}
