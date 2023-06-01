#include <vector>
#include <iostream>
#include <algorithm>
// TODO: iostream should also output to python console

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
    SpeciesHandler<dType, T2>::SpeciesHandler(dType c1, dType c2, dType c3, dType threshold) :
        c1(c1), c2(c2), c3(c3), threshold(threshold) {
        this->species = std::vector<Species<dType, T2>*>();
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
    void SpeciesHandler<dType, T2>::addGenome(std::vector<Genome<dType, T2>*> genomes) {
        for (Genome<dType, T2>* genome : genomes) {
            this->addGenome(genome);
        }
    }

    template <typename dType, typename T2>
    std::vector<Genome<dType, T2>*> SpeciesHandler<dType, T2>::reproduce(dType c1, dType c2, dType c3, T2 n) const {
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
        const T2 averageFitness = this->getAverageFitnessSum();
        for (Species<dType, T2>* s : species) {
            T2 numberToReproduce = s->getAverageFitness() / averageFitness * n;
            std::vector<Genome<dType, T2>*> tempGeneration = s->generateNextGeneration(geneHistory, c1, c2, c3, numberToReproduce);
            nextGeneration.insert(nextGeneration.end(), tempGeneration.begin(), tempGeneration.end());
        }
        // sort
        // std::sort(nextGeneration.begin(), nextGeneration.end(), [](const Genome<dType, T2>* a, const Genome<dType, T2>* b) {
        //     return a->getFitness() > b->getFitness();
        //     });
        // keep only n best
        // if (static_cast<T2>(nextGeneration.size()) > n) {
        //     nextGeneration.erase(nextGeneration.begin() + n, nextGeneration.end());
        // }
        return nextGeneration;
    }

    template <typename dType, typename T2>
    std::vector<Genome<dType, T2>*> SpeciesHandler<dType, T2>::reproduce(T2 n) const {
        return this->reproduce(this->c1, this->c2, this->c3, n);
    }

    template <typename dType, typename T2>
    dType SpeciesHandler<dType, T2>::getAverageFitnessSum() const {
        dType sum = 0;
        for (Species<dType, T2>* s : species) {
            sum += s->getAverageFitness();
        }
        return sum;
    }

    // Explicit instantiation
    template class SpeciesHandler<double, int>;
    template class SpeciesHandler<double, long>;
}
