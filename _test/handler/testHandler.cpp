#include "./testHandler.hpp"
#include "../../include/NEAT/Genome.hpp"
#include "../../include/NEAT/Helper.hpp"

namespace NEAT {
    template <typename dType, typename T2>
    TestHandler<dType, T2>::TestHandler(T2 inputSize, T2 outputSize, SpeciesConfig<dType> speciesConfig, MutationConfig<dType> mutationConfig) :
        inputSize(inputSize), outputSize(outputSize), speciesConfig(speciesConfig), mutationConfig(mutationConfig) { }

    template <typename dType, typename T2>
    std::vector<Genome<dType, T2>*> TestHandler<dType, T2>::produceGenome(T2 n, T2 inputSize, T2 outputSize, bool sameForAll) const {
        std::vector<Genome<dType, T2>*> genomes;
        for (T2 i = 0; i < n; i++) {
            genomes.push_back(new Genome<dType, T2>((inputSize == -1 ? this->inputSize : inputSize), (outputSize == -1 ? this->outputSize : outputSize), true));
        }
        return genomes;
    }

    template <typename dType, typename T2>
    std::vector<T2> TestHandler<dType, T2>::generateRandomIntVector(T2 size, T2 lowerBound, T2 upperBound) const {
        std::vector<T2> vec;
        vec.reserve(size);
        for (T2 i = 0; i < size; i++) {
            vec.push_back(uniformIntDistribution<T2>(lowerBound, upperBound));
        }
        return vec;
    }

    template <typename dType, typename T2>
    std::vector<dType> TestHandler<dType, T2>::generateRandomDoubleVector(T2 size, dType lowerBound, dType upperBound) const {
        std::vector<dType> vec;
        vec.reserve(size);
        for (T2 i = 0; i < size; i++) {
            vec.push_back(uniformDistribution<dType>(lowerBound, upperBound));
        }
        return vec;
    }

    template <typename dType, typename T2>
    std::vector<std::vector<dType>> TestHandler<dType, T2>::massFeedForward(const std::vector<Genome<dType, T2>*>& genomes, std::vector<dType>& input) const {
        std::vector<std::vector<dType>> outputs;
        outputs.reserve(genomes.size());
        for (Genome<dType, T2>* genome : genomes) {
            std::vector<dType> tempOutput;
            genome->feedForward(input, tempOutput);
            outputs.push_back(tempOutput);
        }
        return outputs;
    }

    template <typename dType, typename T2>
    std::vector<std::vector<dType>> TestHandler<dType, T2>::massFeedForward(const std::vector<Genome<dType, T2>*>& genomes, std::vector<std::vector<dType>>& inputs) const {
        if (inputs.size() != genomes.size()) {
            throw std::invalid_argument("The number of inputs must be equal to the number of genomes.");
        }
        std::vector<std::vector<dType>> outputs;
        outputs.reserve(genomes.size());
        for (T2 i = 0; i < static_cast<T2>(genomes.size()); i++) {
            std::vector<dType> tempOutput;
            genomes[i]->feedForward(inputs[i], tempOutput);
            outputs.push_back(tempOutput);
        }
        return outputs;
    }

    template <typename dType, typename T2>
    void TestHandler<dType, T2>::massAssignFitness(const std::vector<Genome<dType, T2>*>& genomes, const std::vector<dType>& fitnesses) const {
        if (genomes.size() != fitnesses.size()) {
            throw std::invalid_argument("The number of genomes must be equal to the number of fitnesses.");
        }
        for (T2 i = 0; i < static_cast<T2>(genomes.size()); i++) {
            genomes[i]->setFitness(fitnesses[i]);
        }
    }

    template <typename dType, typename T2>
    void TestHandler<dType, T2>::massAssignFitness(const std::vector<Genome<dType, T2>*>& genomes, dType fitness) const {
        for (T2 i = 0; i < static_cast<T2>(genomes.size()); i++) {
            genomes[i]->setFitness(fitness);
        }
    }

    // TODO:
    // template <typename dType, typename T2>
    // void TestHandler<dType, T2>::massAssignFitness(const std::vector<Genome<dType, T2>*>& genomes, dType(*fitnessCB)(dType)) const {
    //     for (Genome<dType, T2>* genome : genomes) {
    //         genome->setFitness(fitnessCB(genome->));
    //     }
    // }


    // Explicitly instantiate the template class
    template class TestHandler<double, int>;
    template class TestHandler<double, long>;
}
