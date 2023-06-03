#include <iostream>
#include <chrono>
#include <vector>

#include "./handler/testHandler.hpp"
#include "../include/NEAT/Population.hpp"
#include "../include/NEAT/SpeciesHandler.hpp"
#include "../include/NEAT/Species.hpp"
#include "../include/NEAT/Genome.hpp"
#include "../include/NEAT/Activation.hpp"
#include "../include/NEAT/GeneHistory.hpp"
#include "../include/NEAT/Helper.hpp"
#include "../include/NEAT/config.hpp"

// forward declaration
void testForGenome();
void crossOverTest();
void populationTest();
template <typename dType, typename T2>
void forceSkipGeneration(NEAT::TestHandler<dType, T2>* testHandler, NEAT::Population<dType, T2>* population, int n);
template <typename dType, typename T2>
void forceMutate(NEAT::Genome<dType, T2>* genome);

int main() {
    NEAT::ActivationFunction_Factory<>* AfFactory = NEAT::getActivationFunction_Factory<>();
    const int inputSize = 2;
    const int outputSize = 1;
    const int populationSize = 100;
    const NEAT::MutationConfig<double> mutationConfig = {
        0.8, // mutateAddNodeProbability
        0.2, // mutateAddEdgeProbability
        0.2, // mutateToggleEdgeProbability
        0.2, // mutateWeightProbability
        0.2, // mutateActivationFunctionProbability
        0.2, // mutateBiasProbability
    };

    const NEAT::SpeciesConfig<double> speciesConfig = {
        1, // c1 (excess genes)
        1, // c2 (disjoint genes)
        0.2, // c3 (weight difference)
        3, // threshold
    };
    NEAT::TestHandler<double, int>* testHandler = new NEAT::TestHandler(inputSize, outputSize, speciesConfig, mutationConfig);
    NEAT::Population<double, int>* population = new NEAT::Population<double, int>(inputSize, outputSize, populationSize, mutationConfig, speciesConfig);

    delete population;
    delete testHandler;
}

template <typename dType, typename T2>
void forceMutate(NEAT::Genome<dType, T2>* genome) {
    NEAT::GeneHistory<dType, T2> geneHistory;
    genome->mutate(geneHistory);
};

template <typename dType, typename T2>
void forceSkipGeneration(NEAT::TestHandler<dType, T2>* testHandler, NEAT::Population<dType, T2>* population, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "Generation " << population->getGeneration() + 1 << ", ";
        auto t1 = std::chrono::high_resolution_clock::now();
        population->startNextGeneration(testHandler->generateRandomDoubleVector(population->getPopulationSize(), 0, 100));
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> ms_double = t2 - t1;
        std::cout << "Time taken: " << ms_double.count() << " ms" << std::endl;
    }
    std::cout << "Generation " << population->getGeneration() << " Done." << std::endl;
};

void populationTest() {
    const int inputSize = 2;
    const int outputSize = 1;
    const int populationSize = 100;
    const NEAT::MutationConfig<double> mutationConfig = {
        0.8, // mutateAddNodeProbability
        0.2, // mutateAddEdgeProbability
        0.2, // mutateToggleEdgeProbability
        0.2, // mutateWeightProbability
        0.2, // mutateActivationFunctionProbability
        0.2, // mutateBiasProbability
    };

    const NEAT::SpeciesConfig<double> speciesConfig = {
        1, // c1 (excess genes)
        1, // c2 (disjoint genes)
        0.2, // c3 (weight difference)
        3, // threshold
    };
    NEAT::TestHandler<double, int>* testHandler = new NEAT::TestHandler(inputSize, outputSize, speciesConfig, mutationConfig);
    NEAT::Population<double, int>* population = new NEAT::Population<double, int>(inputSize, outputSize, populationSize, mutationConfig, speciesConfig);
    forceSkipGeneration<double, int>(testHandler, population, 100);
    // population->print();

    delete population;
    delete testHandler;
}

void crossOverTest() {
    const int inputSize = 2;
    const int outputSize = 1;
    NEAT::Genome<double, int>* genome1 = new NEAT::Genome(inputSize, outputSize, true);
    NEAT::Genome<double, int>* genome2 = new NEAT::Genome(inputSize, outputSize, true);
    NEAT::Species<double, int>* species = new NEAT::Species(genome1);
    NEAT::Genome<double, int>* genome3 = species->crossover(genome1, genome2);
    delete species;
    delete genome1;
    delete genome2;
    delete genome3;
}

void testForGenome() {
    const int inputSize = 2;
    const int outputSize = 1;
    NEAT::Genome<double, int> genome(inputSize, outputSize, true);
    std::cout << genome.getNodes().size() << std::endl;
    std::cout << genome.getEdges().size() << std::endl;
    std::cout << genome.getNodes().at(0)->getIncomingEdges().size() << std::endl;
    // 
    std::vector<double> input = {};
    for (int i = 0; i < inputSize; i++) {
        input.push_back(NEAT::gaussianDistribution<double>(0, 0.2));
    }
    std::vector<double> output;
    // print all edges weight
    for (std::pair<const int, NEAT::Edge<double, int>*> pair : genome.getEdges()) {
        std::cout << pair.second->getFrom(&genome)->getId() << " -> " << pair.second->getTo(&genome)->getId() << " : ";
        std::cout << pair.second->getWeight() << std::endl;
    }
    genome.getNodes().at(inputSize + 0)->setBias(0);
    genome.feedForward(input, output);
    for (double d : output) {
        std::cout << d << std::endl;
    }
    NEAT::Genome<double, int>* dynamicGenome = genome.clone();
    // std::cout << "genome" << std::endl;
    // genome.print();
    std::cout << "dynamicGenome" << std::endl;
    dynamicGenome->print();
    NEAT::GeneHistory<double, int> geneHistory;
    geneHistory.init(inputSize, outputSize);
    for (int i = 0; i < 1000; i++) {
        forceMutate(dynamicGenome);
    }
    std::cout << "mutated genome" << std::endl;
    dynamicGenome->print();
    output.clear();
    dynamicGenome->feedForward(input, output);
    for (double d : output) {
        std::cout << d << std::endl;
    }
    delete dynamicGenome;
}

