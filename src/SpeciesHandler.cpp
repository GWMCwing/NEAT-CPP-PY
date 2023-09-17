#include <vector>
#include <iostream>
#include <algorithm>
// TODO: iostream should also output to python console

#include "../include/NEAT/SpeciesHandler.hpp"
#include "../include/NEAT/Species.hpp"
#include "../include/NEAT/Genome.hpp"
#include "../include/NEAT/Edge.hpp"
#include "../include/NEAT/GeneHistory.hpp"

namespace NEAT {

    // forward declaration
    template <typename dType, typename T2>
    class Genome;
    template <typename dType, typename T2>
    class Edge;
    template <typename dType, typename T2>
    class GeneHistory;
    template <typename dType, typename T2>
    class Species;

    template <typename dType, typename T2>
    SpeciesHandler<dType, T2>::SpeciesHandler(Genome<dType, T2>* genome, dType c1, dType c2, dType c3, dType threshold) :
        c1(c1), c2(c2), c3(c3), threshold(threshold) {
        this->addGenome(genome);
    }
    template <typename dType, typename T2>
    SpeciesHandler<dType, T2>::SpeciesHandler(std::vector<Genome<dType, T2>*>& genome, dType c1, dType c2, dType c3, dType threshold) :
        c1(c1), c2(c2), c3(c3), threshold(threshold) {
        this->addGenome(genome);
    }
    template <typename dType, typename T2>
    SpeciesHandler<dType, T2>::SpeciesHandler(Genome<dType, T2>* genome, SpeciesConfig<dType> speciesConfig) :
        c1(speciesConfig.c1), c2(speciesConfig.c2), c3(speciesConfig.c3), threshold(speciesConfig.threshold) {
        this->addGenome(genome);
    }

    template <typename dType, typename T2>
    SpeciesHandler<dType, T2>::SpeciesHandler(std::vector<Genome<dType, T2>*>& genome, SpeciesConfig<dType> speciesConfig) :
        c1(speciesConfig.c1), c2(speciesConfig.c2), c3(speciesConfig.c3), threshold(speciesConfig.threshold) {
        this->addGenome(genome);
    }

    template <typename dType, typename T2>
    SpeciesHandler<dType, T2>::~SpeciesHandler() {
        for (Species<dType, T2>* s : species) {
            delete s;
        }
    }


    template <typename dType, typename T2>
    void SpeciesHandler<dType, T2>::addGenome(Genome<dType, T2>* genome) {
        dType distance = -1;
        Species<dType, T2>* closest = nullptr;
        for (Species<dType, T2>* s : species) {
            dType temp_distance = s->getDistance(genome, c1, c2, c3);
            if (distance == -1 || temp_distance < distance) {
                distance = temp_distance;
                closest = s;
            }
        }
        if (closest == nullptr || distance > threshold) {
            species.push_back(new Species<dType, T2>(genome));
        } else {
            closest->addGenome(genome);
        }
    }

    template <typename dType, typename T2>
    void SpeciesHandler<dType, T2>::addGenome(std::vector<Genome<dType, T2>*>& genomes) {
        for (Genome<dType, T2>* genome : genomes) {
            this->addGenome(genome);
        }
    }

    template <typename dType, typename T2>
    std::vector<Genome<dType, T2>*> SpeciesHandler<dType, T2>::reproduce(T2 n, const MutationConfig<dType>& mutationConfig) const {
        GeneHistory<dType, T2> geneHistory = GeneHistory<dType, T2>();
        //TODO: threading
        if (n <= 0) {
            n = 200;
            std::cout << "Warning: n <= 0, setting n to 200" << std::endl;
        }
        std::vector<Genome<dType, T2>*> nextGeneration = std::vector<Genome<dType, T2>*>();
        // fitness sharing
        for (Species<dType, T2>* s : species) {
            s->fitnessShare();
        }
        // reproduce
        const dType averageFitness = this->getAverageFitnessSum();
        const int speciesSize = species.size();
        int produced = 0;
        for (int i = 0; i < speciesSize; i++) {
            Species<dType, T2>* s = species[i];
            T2 numberToReproduce = static_cast<T2>(s->getAverageFitness() / (averageFitness * n + 0.00000000001));
            if (speciesSize == i + 1) {
                numberToReproduce = n - produced;
            }
            std::vector<Genome<dType, T2>*> tempGeneration = s->generateNextGeneration(geneHistory, numberToReproduce, mutationConfig);
            nextGeneration.insert(nextGeneration.end(), tempGeneration.begin(), tempGeneration.end());
            produced += numberToReproduce;
        }
        return nextGeneration;
    }

    template <typename dType, typename T2>
    dType SpeciesHandler<dType, T2>::getAverageFitnessSum() const {
        dType sum = 0;
        for (Species<dType, T2>* s : species) {
            sum += s->getAverageFitness();
        }
        return sum;
    }


    template <typename dType, typename T2>
    void SpeciesHandler<dType, T2>::print(int tabSize) const {
        coutTab(tabSize);
        std::cout << "SpeciesHandler: " << std::endl;
        for (int i = 0; i < species.size(); i++) {
            species[i]->print(tabSize + 1);
        }
    }

    // Explicit instantiation
    template class SpeciesHandler<double, int>;
    template class SpeciesHandler<double, long>;
}
