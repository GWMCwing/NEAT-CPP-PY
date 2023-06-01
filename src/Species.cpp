#include <map>
#include <vector>
#include <math.h>
#include <set>
#include <algorithm>

#include "../include/NEAT/Species.hpp"
#include "../include/NEAT/Genome.hpp"
#include "../include/NEAT/Helper.hpp"

namespace NEAT {

    // forward declaration
    template <typename dType, typename T2>
    class Genome;
    template <typename dType, typename T2>
    class Edge;

    template <typename dType, typename T2>
    template <typename dType2, typename T3>
    SpeciesHandler<dType, T2>::Species<dType2, T3>::Species(Genome<dType2, T3>* representative) {
        this->genomes = std::vector<Genome<dType, T2>*>();
        this->genomes.push_back(representative);
        this->representative = representative;
        this->totalFitness = representative->getFitness();
    }

    template <typename dType, typename T2>
    template <typename dType2, typename T3>
    void SpeciesHandler<dType, T2>::Species<dType2, T3>::addGenome(Genome<dType2, T3>* genome) {
        if (genome->getFitness() > this->representative->getFitness()) {
            this->representative = genome;
        }
        this->genomes.push_back(genome);
        this->totalFitness += genome->getFitness();
    }

    template <typename dType, typename T2>
    template <typename dType2, typename T3>
    const Genome<dType2, T3>* SpeciesHandler<dType, T2>::Species<dType2, T3>::getRepresentative() const {
        return this->representative;
    }

    template <typename dType, typename T2>
    template <typename dType2, typename T3>
    dType2 SpeciesHandler<dType, T2>::Species<dType2, T3>::getDistance(const Genome<dType2, T3>* genome, dType2 c1, dType2 c2, dType2 c3) const {
        // T3 maxId_representative = this->representative->getMaxInnovationNumber();
        // T3 maxId_target = genome->getMaxInnovationNumber();
        // std::set<T3> innovationNumbers_representative, innovationNumbers_target;
        // get incompatible edges innovation numbers
        // TODO: use getEdgeDifference function
        // for (const std::pair<T3, Edge<dType2, T3>*>& edgePair : this->representative->getEdges()) {
        //     innovationNumbers_representative.insert(edgePair.first);
        // }
        // for (const std::pair<T3, Edge<dType2, T3>*>& edgePair : genome->getEdges()) {
        //     innovationNumbers_target.insert(edgePair.first);
        // }
        // std::vector<T3> incompatibleEdges;
        // std::set_symmetric_difference(innovationNumbers_representative.begin(), innovationNumbers_representative.end(), innovationNumbers_target.begin()
        //     , innovationNumbers_target.end(), std::back_inserter(incompatibleEdges));
        // // 
        // dType2 excessDifference = this->getExcessDifference(incompatibleEdges, maxId_representative, maxId_target);
        // dType2 disjointDifference = this->getDisjointDifference(incompatibleEdges, maxId_representative, maxId_target);
        EdgeDifference<dType2, T3> edgeDifference = this->getEdgeDifference(this->representative, genome);
        dType2 excessDifference = edgeDifference.excess.size();
        dType2 disjointDifference = edgeDifference.disjoint.size();
        dType2 averageWeightDifference = this->getAverageWeightDifference(genome);
        // 
        T3 genes_representative = this->representative->getNumberOfGenes();
        T3 genes_target = genome->getNumberOfGenes();
        T3 N = (genes_representative > genes_target) ? genes_representative : genes_target;
        if (N < 20) N = 1;
        // 
        return (excessDifference * c1 / N) + (disjointDifference * c2 / N) + (averageWeightDifference * c3);
    }

    template <typename dType, typename T2>
    template <typename dType2, typename T3>
    dType2 SpeciesHandler<dType, T2>::Species<dType2, T3>::isSameSpecies(const Genome<dType2, T3>* genome, dType2 c1, dType2 c2, dType2 c3, dType2 threshold) const {
        dType2 distance = this->getDistance(genome, c1, c2, c3);
        return (distance < threshold) ? distance : -1;
    }

    template <typename dType, typename T2>
    template <typename dType2, typename T3>
    EdgeDifference<dType2, T3> SpeciesHandler<dType, T2>::Species<dType2, T3>::getEdgeDifference(const Genome<dType2, T3>* genome1, const Genome<dType2, T3>* genome2) const {
        T3 maxIdTarget = genome2->getMaxInnovationNumber();
        EdgeDifference<dType2, T3> edgeDifference;
        for (const std::pair<T3, Edge<dType2, T3>*>& edgePair : genome1->getEdges()) {
            bool foundMatching = false;
            const Edge<dType2, T3>* edge1 = edgePair.second;
            for (const std::pair<T3, Edge<dType2, T3>*>& edgePair2 : genome2->getEdges()) {
                const Edge<dType2, T3>* edge2 = edgePair2.second;
                if (edge1->getInnovationNumber() == edge2->getInnovationNumber()) {
                    foundMatching = true;
                    edgeDifference.matching.push_back(edge1);
                    break;
                }
            }
            if (!foundMatching) {
                if (edge1->getInnovationNumber() > maxIdTarget) {
                    edgeDifference.excess.push_back(edge1);
                } else {
                    edgeDifference.disjoint.push_back(edge1);
                }
            }
        }
        return edgeDifference;
    }

    // template <typename dType, typename T2>
    // template <typename dType2, typename T3>
    // T3 SpeciesHandler<dType, T2>::Species<dType2, T3>::getExcessDifference(const std::vector<T3>& incompatibleEdge, const T3& maxId_representative, const T3& maxId_target) const {
    //     // TODO: optimize
    //     T3 excessDifference = 0;
    //     if (maxId_target <= maxId_representative) return excessDifference;
    //     for (const T3& edge_IN : incompatibleEdge) {
    //         if (edge_IN > maxId_representative) {
    //             excessDifference++;
    //         }
    //     }
    //     return excessDifference;
    // }

    // template <typename dType, typename T2>
    // template <typename dType2, typename T3>
    // T3 SpeciesHandler<dType, T2>::Species<dType2, T3>::getDisjointDifference(const std::vector<T3>& incompatibleEdge, const T3& maxId_representative, const T3& maxId_target) const {
    //     // TODO: optimize
    //     T3 disjointDifference = 0;
    //     for (const T3& edge_IN : incompatibleEdge) {
    //         if (edge_IN < maxId_representative) {
    //             disjointDifference++;
    //         }
    //     }
    //     return disjointDifference;
    // }

    template <typename dType, typename T2>
    template <typename dType2, typename T3>
    dType2 SpeciesHandler<dType, T2>::Species<dType2, T3>::getAverageWeightDifference(const Genome<dType2, T3>* genome) const {
        dType2 averageWeight_target = 0;
        dType2 averageWeight_representative = 0;
        T3 genes_target = genome->getNumberOfGenes();
        T3 genes_representative = this->representative->getNumberOfGenes();
        // 
        for (std::pair<T3, Edge<dType2, T3>*> edgePair : genome->getEdges()) {
            averageWeight_target += edgePair.second->getWeight();
        }
        for (std::pair<T3, Edge<dType2, T3>*> edgePair : this->representative->getEdges()) {
            averageWeight_representative += edgePair.second->getWeight();
        }
        // prevent division by zero
        const dType2 epsilon = 0.0000001;
        averageWeight_target /= genes_target + epsilon;
        averageWeight_representative /= genes_representative + epsilon;
        //
        return std::abs(averageWeight_target - averageWeight_representative);
    }

    template <typename dType, typename T2>
    template <typename dType2, typename T3>
    void SpeciesHandler<dType, T2>::Species<dType2, T3>::fitnessShare() {
        const T3 N = this->genomes.size();
        for (Genome<dType2, T3>* genome : this->genomes) {
            genome->setFitness(genome->getFitness() / N);
        }
        totalFitness /= N;
    }

    template <typename dType, typename T2>
    template <typename dType2, typename T3>
    const std::vector<Genome<dType2, T3>*>& SpeciesHandler<dType, T2>::Species<dType2, T3>::sortGenomes() {
        std::sort(this->genomes.begin(), this->genomes.end(), [](const Genome<dType2, T3>* genome1, const Genome<dType2, T3>* genome2) {
            return genome1->getFitness() > genome2->getFitness();
            });
        return this->genomes;
    }

    template <typename dType, typename T2>
    template <typename dType2, typename T3>
    std::vector<Genome<dType2, T3>*> SpeciesHandler<dType, T2>::Species<dType2, T3>::generateNextGeneration(GeneHistory<dType2, T3>& geneHistory, dType2 c1, dType2 c2, dType2 c3, T3 n) const {
        std::vector<Genome<dType2, T3>*> nextGeneration;
        for (T3 i = 0; i < n; i++) {
            Genome<dType2, T3>* newGenome = nullptr;
            if (uniformDistribution<dType2>(0, 1) < 0.25 || genomes.size() == 1) { // 25% chance to get the same genome instead of getting one from crossover
                newGenome = this->getRandomGenome()->clone();
            } else {
                const Genome<dType2, T3>* genome1, * genome2;
                genome1 = this->getRandomGenome();
                while (true) {
                    genome2 = this->getRandomGenome();
                    if (genome1 != genome2) break;
                }
                newGenome = this->crossover(genome1, genome2);
            }
            newGenome->mutate(geneHistory);
            nextGeneration.push_back(newGenome);
        }
        return nextGeneration;
    }

    template <typename dType, typename T2>
    template <typename dType2, typename T3>
    Genome<dType2, T3>* SpeciesHandler<dType, T2>::Species<dType2, T3>::crossover(const Genome<dType2, T3>* genome1, const Genome<dType2, T3>* genome2) const {
        // TODO: optimize
        // 1. get the genome with the higher fitness
        const Genome<dType2, T3>* genome_higherFitness = genome1->getFitness() > genome2->getFitness() ? genome1 : genome2;
        const Genome<dType2, T3>* genome_lowerFitness = genome1->getFitness() > genome2->getFitness() ? genome2 : genome1;
        // 2. get the disjoint and excess genes of the genome with the higher fitness
        const EdgeDifference<dType2, T3> edgeDifference = getEdgeDifference(genome_higherFitness, genome_lowerFitness);
        const std::vector<const Edge<dType, T2>*>& disjointGenes = edgeDifference.disjoint;
        const std::vector<const Edge<dType, T2>*>& excessGenes = edgeDifference.excess;
        // 3. get the matching genes of both genomes
        const std::vector<const Edge<dType, T2>*>& matchingGenes = edgeDifference.matching;
        // 4. clone edges of the disjoint and excess genome from the genome with the higher fitness
        Genome<dType2, T3>* offspring = new Genome<dType2, T3>(genome_higherFitness->getInputSize(), genome_higherFitness->getOutputSize(), false);
        for (const Edge<dType, T2>* edge : disjointGenes) {
            bool successCloneEdge = offspring->addCloneEdge(edge);
        }
        for (const Edge<dType, T2>* edge : excessGenes) {
            bool successCloneEdge = offspring->addCloneEdge(edge);
        }
        // 5. clone edges of the matching genome from a random genome
        for (const Edge<dType, T2>* edge : matchingGenes) {
            const Genome<dType2, T3>* randomGenome = uniformDistribution<dType2>(0, 1) < 0.5 ? genome1 : genome2;
            Edge <dType2, T3>* randomEdge = randomGenome->getEdge(edge->getInnovationNumber());
            bool successCloneEdge = offspring->addCloneEdge(randomEdge);
        }
        // 6. build nodes from the edges
        for (std::pair<T2, Edge<dType, T2>*> edgePair : offspring->getEdges()) {
            const Edge<dType, T2>* edge = edgePair.second;
            // do not use clone, because the edges will be cloned many times
            // 1. check if the from node is within the offspring
            const Node<dType2, T3>* originalFromNode = edge->getFrom(offspring);
            Node<dType2, T3>* fromNode = offspring->getNode(originalFromNode->getId());
            if (fromNode == nullptr) {
                // 2. if not, re produce the node
                const T2& id = originalFromNode->getId();
                const NodeType nodeType = originalFromNode->getType();
                const dType2 bias = originalFromNode->getBias();
                const int layer = originalFromNode->getLayer();
                ActivationFunction<dType2>* activationFunction = originalFromNode->getActivationFunction(); // TODO:
                fromNode = new Node<dType2, T3>(id, nodeType, layer, bias, activationFunction);
                fromNode->addOutgoingEdge(const_cast<Edge<dType, T2>*>(edge));
                offspring->addNode_noClone(fromNode);
            } else {
                fromNode->addOutgoingEdge(const_cast<Edge<dType, T2>*>(edge));
            }
            // 3. check if the to node is within the offspring
            const Node<dType2, T3>* originalToNode = edge->getTo(offspring);
            Node<dType2, T3>* toNode = offspring->getNode(originalToNode->getId());
            if (toNode == nullptr) {
                // 4. if not, re produce the node
                const T2& id = originalToNode->getId();
                const NodeType nodeType = originalToNode->getType();
                const dType2 bias = originalToNode->getBias();
                const int layer = originalToNode->getLayer();
                ActivationFunction<dType2>* activationFunction = originalToNode->getActivationFunction(); // TODO:
                toNode = new Node<dType2, T3>(id, nodeType, layer, bias, activationFunction);
                toNode->addIncomingEdge(const_cast<Edge<dType, T2>*>(edge));
                offspring->addNode_noClone(toNode);
            } else {
                toNode->addIncomingEdge(const_cast<Edge<dType, T2>*>(edge));
            }
        }
        return offspring;
    }

    template <typename dType, typename T2>
    template <typename dType2, typename T3>
    dType2 SpeciesHandler<dType, T2>::Species<dType2, T3>::getAverageFitness() const {
        dType2 averageFitness = 0;
        for (Genome<dType2, T3>* genome : this->genomes) {
            averageFitness += genome->getFitness();
        }
        return averageFitness / this->genomes.size();
    }

    template <typename dType, typename T2>
    template <typename dType2, typename T3>
    const Genome<dType2, T3>* SpeciesHandler<dType, T2>::Species<dType2, T3>::getRandomGenome() const {
        dType2 randomFitness = std::abs(gaussianDistribution<dType2>(0, 1) * totalFitness);
        dType2 currentFitness = 0;
        for (Genome<dType2, T3>* genome : this->genomes) {
            currentFitness += genome->getFitness();
            if (currentFitness >= randomFitness) {
                return genome;
            }
        }
        return this->genomes.front();
    }

    // Explicit instantiation
    template class SpeciesHandler<double, int>::Species<double, int>;
    template class SpeciesHandler<double, long>::Species<double, long>;

}
