#include <iostream>
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
    Species<dType, T2>::Species(Genome<dType, T2>* representative) {
        this->genomes = std::vector<Genome<dType, T2>*>();
        this->genomes.push_back(representative);
        this->representative = representative;
        this->totalFitness = representative->getFitness();
    }

    template <typename dType, typename T2>
    void Species<dType, T2>::addGenome(Genome<dType, T2>* genome) {
        if (genome->getFitness() > this->representative->getFitness()) {
            this->representative = genome;
        }
        this->genomes.push_back(genome);
        this->totalFitness += genome->getFitness();
    }

    template <typename dType, typename T2>
    const Genome<dType, T2>* Species<dType, T2>::getRepresentative() const {
        return this->representative;
    }

    template <typename dType, typename T2>
    dType Species<dType, T2>::getDistance(const Genome<dType, T2>* genome, dType c1, dType c2, dType c3) const {
        // T2 maxId_representative = this->representative->getMaxInnovationNumber();
        // T2 maxId_target = genome->getMaxInnovationNumber();
        // std::set<T2> innovationNumbers_representative, innovationNumbers_target;
        // get incompatible edges innovation numbers
        // TODO: use getEdgeDifference function
        // for (const std::pair<T2, Edge<dType, T2>*>& edgePair : this->representative->getEdges()) {
        //     innovationNumbers_representative.insert(edgePair.first);
        // }
        // for (const std::pair<T2, Edge<dType, T2>*>& edgePair : genome->getEdges()) {
        //     innovationNumbers_target.insert(edgePair.first);
        // }
        // std::vector<T2> incompatibleEdges;
        // std::set_symmetric_difference(innovationNumbers_representative.begin(), innovationNumbers_representative.end(), innovationNumbers_target.begin()
        //     , innovationNumbers_target.end(), std::back_inserter(incompatibleEdges));
        // // 
        // dType excessDifference = this->getExcessDifference(incompatibleEdges, maxId_representative, maxId_target);
        // dType disjointDifference = this->getDisjointDifference(incompatibleEdges, maxId_representative, maxId_target);
        EdgeDifference<dType, T2> edgeDifference = this->getEdgeDifference(this->representative, genome);
        dType excessDifference = edgeDifference.excess.size();
        dType disjointDifference = edgeDifference.disjoint.size();
        dType averageWeightDifference = this->getAverageWeightDifference(genome);
        // 
        T2 genes_representative = this->representative->getNumberOfGenes();
        T2 genes_target = genome->getNumberOfGenes();
        T2 N = (genes_representative > genes_target) ? genes_representative : genes_target;
        if (N < 20) N = 1;
        // 
        return (excessDifference * c1 / N) + (disjointDifference * c2 / N) + (averageWeightDifference * c3);
    }

    template <typename dType, typename T2>
    dType Species<dType, T2>::isSameSpecies(const Genome<dType, T2>* genome, dType c1, dType c2, dType c3, dType threshold) const {
        dType distance = this->getDistance(genome, c1, c2, c3);
        return (distance < threshold) ? distance : -1;
    }

    template <typename dType, typename T2>
    EdgeDifference<dType, T2> Species<dType, T2>::getEdgeDifference(const Genome<dType, T2>* genome1, const Genome<dType, T2>* genome2) const {
        if (genome1 == nullptr) {
            std::cout << "genome1 is null" << std::endl;
        }
        if (genome2 == nullptr) {
            std::cout << "genome2 is null" << std::endl;
        }
        T2 maxIdTarget = genome2->getMaxInnovationNumber();
        EdgeDifference<dType, T2> edgeDifference;
        const std::map<T2, NEAT::Edge<dType, T2>*>& genome1Edge = genome1->getEdges();
        const std::map<T2, NEAT::Edge<dType, T2>*>& genome2Edge = genome2->getEdges();
        for (const std::pair<const T2, Edge<dType, T2>*>& edgePair1 : genome1Edge) {
            bool foundMatching = false;
            const Edge<dType, T2>* edge1 = edgePair1.second;
            if (edge1 == nullptr) {
                std::cout << "edge1 is null" << std::endl;
            }
            for (const std::pair<const T2, Edge<dType, T2>*>& edgePair2 : genome2Edge) {
                const Edge<dType, T2>* edge2 = edgePair2.second;
                if (edge2 == nullptr) {
                    std::cout << "edge2 is null" << std::endl;
                }
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
    // template <typename dType, typename T2>
    // T2 Species<dType, T2>::getExcessDifference(const std::vector<T2>& incompatibleEdge, const T2& maxId_representative, const T2& maxId_target) const {
    //     // TODO: optimize
    //     T2 excessDifference = 0;
    //     if (maxId_target <= maxId_representative) return excessDifference;
    //     for (const T2& edge_IN : incompatibleEdge) {
    //         if (edge_IN > maxId_representative) {
    //             excessDifference++;
    //         }
    //     }
    //     return excessDifference;
    // }

    // template <typename dType, typename T2>
    // template <typename dType, typename T2>
    // T2 Species<dType, T2>::getDisjointDifference(const std::vector<T2>& incompatibleEdge, const T2& maxId_representative, const T2& maxId_target) const {
    //     // TODO: optimize
    //     T2 disjointDifference = 0;
    //     for (const T2& edge_IN : incompatibleEdge) {
    //         if (edge_IN < maxId_representative) {
    //             disjointDifference++;
    //         }
    //     }
    //     return disjointDifference;
    // }

    template <typename dType, typename T2>
    dType Species<dType, T2>::getAverageWeightDifference(const Genome<dType, T2>* genome) const {
        dType averageWeight_target = 0;
        dType averageWeight_representative = 0;
        T2 genes_target = genome->getNumberOfGenes();
        T2 genes_representative = this->representative->getNumberOfGenes();
        // 
        for (std::pair<T2, Edge<dType, T2>*> edgePair : genome->getEdges()) {
            averageWeight_target += edgePair.second->getWeight();
        }
        for (std::pair<T2, Edge<dType, T2>*> edgePair : this->representative->getEdges()) {
            averageWeight_representative += edgePair.second->getWeight();
        }
        // prevent division by zero
        const dType epsilon = 0.0000001;
        averageWeight_target /= genes_target + epsilon;
        averageWeight_representative /= genes_representative + epsilon;
        //
        return std::abs(averageWeight_target - averageWeight_representative);
    }

    template <typename dType, typename T2>
    void Species<dType, T2>::fitnessShare() {
        const T2 N = this->genomes.size();
        for (Genome<dType, T2>* genome : this->genomes) {
            genome->setFitness(genome->getFitness() / N);
        }
        // totalFitness /= N;
    }

    template <typename dType, typename T2>
    const std::vector<Genome<dType, T2>*>& Species<dType, T2>::sortGenomes() {
        std::sort(this->genomes.begin(), this->genomes.end(), [](const Genome<dType, T2>* genome1, const Genome<dType, T2>* genome2) {
            return genome1->getFitness() > genome2->getFitness();
            });
        return genomes;
    }

    template <typename dType, typename T2>
    std::vector<Genome<dType, T2>*> Species<dType, T2>::generateNextGeneration(GeneHistory<dType, T2>& geneHistory, T2 n, const MutationConfig<dType>& mutationConfig) {
        std::vector<Genome<dType, T2>*> nextGeneration;
        if (n == 1 || genomes.size() == 1) {
            nextGeneration.push_back(this->getRandomGenome()->clone());
            return nextGeneration;
        }
        if (n == 2 || genomes.size() == 2) {
            nextGeneration.push_back(this->getRandomGenome()->clone());
            nextGeneration.push_back(this->getRandomGenome()->clone());
            return nextGeneration;
        }
        nextGeneration.reserve(n);
        sortGenomes();
        for (T2 i = 0; i < n; i++) {
            std::vector<Genome<dType, T2>*> genomeList = this->genomes;
            Genome<dType, T2>* newGenome = nullptr;
            // TODO: break out of inf loop selecting the same genome
            // TODO: vector of genome pointer to prevent while true loop
            // std::cout << "Generating genome " << i << " of " << n << std::endl;
            if (uniformDistribution<dType>(0, 1) < 0.25) { // 25% chance to get the same genome instead of getting one from crossover
                newGenome = this->getRandomGenome()->clone();
            } else {
                const Genome<dType, T2>* genome1, * genome2;
                genome1 = this->getRandomGenome();
                genomeList.erase(std::find(genomeList.begin(), genomeList.end(), genome1));
                genome2 = this->getRandomGenome(&genomeList);
                newGenome = this->crossover(genome1, genome2);
            }
            newGenome->mutate(geneHistory, mutationConfig);
            nextGeneration.push_back(newGenome);
        }
        return nextGeneration;
    }

    template <typename dType, typename T2>
    Genome<dType, T2>* Species<dType, T2>::crossover(const Genome<dType, T2>* genome1, const Genome<dType, T2>* genome2) const {
        // std::cout << "crossover" << std::endl;
        // TODO: optimize
        // 1. get the genome with the higher fitness
        const Genome<dType, T2>* genome_higherFitness = (genome1->getFitness() > genome2->getFitness()) ? genome1 : genome2;
        const Genome<dType, T2>* genome_lowerFitness = (genome1->getFitness() > genome2->getFitness()) ? genome2 : genome1;
        // 2. get the disjoint and excess genes of the genome with the higher fitness
        const EdgeDifference<dType, T2> edgeDifference = getEdgeDifference(genome_higherFitness, genome_lowerFitness);
        const std::vector<const Edge<dType, T2>*>& disjointGenes = edgeDifference.disjoint;
        const std::vector<const Edge<dType, T2>*>& excessGenes = edgeDifference.excess;
        // 3. get the matching genes of both genomes
        const std::vector<const Edge<dType, T2>*>& matchingGenes = edgeDifference.matching;
        // 4. clone edges of the disjoint and excess genome from the genome with the higher fitness
        Genome<dType, T2>* offspring = new Genome<dType, T2>(genome_higherFitness->getInputSize(), genome_higherFitness->getOutputSize(), false);
        for (const Edge<dType, T2>* edge : disjointGenes) {
            offspring->addCloneEdge(edge);
        }
        for (const Edge<dType, T2>* edge : excessGenes) {
            offspring->addCloneEdge(edge);
        }
        // 5. clone edges of the matching genome from a random genome
        for (const Edge<dType, T2>* edge : matchingGenes) {
            const Genome<dType, T2>* randomGenome = (uniformDistribution<dType>(0, 1) < 0.5) ? genome1 : genome2;
            Edge <dType, T2>* randomEdge = randomGenome->getEdge(edge->getInnovationNumber());
            offspring->addCloneEdge(randomEdge);
        }
        // 6. build nodes from the edges
        for (std::pair<T2, Edge<dType, T2>*> edgePair : offspring->getEdges()) {
            const Edge<dType, T2>* edge = edgePair.second;
            // do not use clone, because the edges will be cloned many times
            // 1. check if the from node is within the offspring
            // const Node<dType, T2>* originalFromNode = edge->getFrom(offspring); // TODO: should get from original genome
            Node<dType, T2>* originalFromNode = edge->getFrom(genome_higherFitness);
            if (originalFromNode == nullptr) {
                originalFromNode = edge->getFrom(genome_lowerFitness);
            }
            Node<dType, T2>* fromNode = offspring->getNode(originalFromNode->getId());
            if (fromNode == nullptr) {
                // 2. if not, re produce the node
                const T2& id = originalFromNode->getId();
                const NodeType nodeType = originalFromNode->getType();
                const dType bias = originalFromNode->getBias();
                const int layer = originalFromNode->getLayer();
                ActivationFunction<dType>* activationFunction = originalFromNode->getActivationFunction();
                fromNode = new Node<dType, T2>(id, nodeType, layer, bias, activationFunction);
                fromNode->addOutgoingEdge(const_cast<Edge<dType, T2>*>(edge));
                offspring->addNode_noClone(fromNode);
            } else {
                fromNode->addOutgoingEdge(const_cast<Edge<dType, T2>*>(edge));
            }
            // 3. check if the to node is within the offspring
            // const Node<dType, T2>* originalToNode = edge->getTo(offspring); // TODO: should get from original genome
            Node<dType, T2>* originalToNode = edge->getTo(genome_higherFitness);
            if (originalToNode == nullptr) {
                originalToNode = edge->getTo(genome_lowerFitness);
            }
            Node<dType, T2>* toNode = offspring->getNode(originalToNode->getId());
            if (toNode == nullptr) {
                // 4. if not, re produce the node
                const T2& id = originalToNode->getId();
                const NodeType nodeType = originalToNode->getType();
                const dType bias = originalToNode->getBias();
                const int layer = originalToNode->getLayer();
                ActivationFunction<dType>* activationFunction = originalToNode->getActivationFunction();
                toNode = new Node<dType, T2>(id, nodeType, layer, bias, activationFunction);
                toNode->addIncomingEdge(const_cast<Edge<dType, T2>*>(edge));
                offspring->addNode_noClone(toNode);
            } else {
                toNode->addIncomingEdge(const_cast<Edge<dType, T2>*>(edge));
            }
        }
        return offspring;
    }

    template <typename dType, typename T2>
    dType Species<dType, T2>::getAverageFitness() const {
        dType averageFitness = 0;
        for (Genome<dType, T2>* genome : this->genomes) {
            averageFitness += genome->getFitness();
        }
        return averageFitness / this->genomes.size();
    }

    template <typename dType, typename T2>
    const Genome<dType, T2>* Species<dType, T2>::getRandomGenome(const std::vector<Genome<dType, T2>*>* genomes) const {
        if (genomes == nullptr) genomes = &(this->genomes);
        dType randomFitness = (uniformDistribution<dType>(0, 1) * totalFitness);
        dType currentFitness = 0;
        for (Genome<dType, T2>* genome : *genomes) {
            currentFitness += genome->getFitness();
            if (currentFitness >= randomFitness) {
                return genome;
            }
        }
        return genomes->front();
    }

    template <typename dType, typename T2>
    void Species<dType, T2>::print(int tabSize) const {
        coutTab(tabSize);
        std::cout << "Species: " << std::endl;
        for (int i = 0; i < genomes.size();i++) {
            genomes[i]->print(tabSize + 1);
        }
    }

    // Explicit instantiation
    template class Species<double, int>;
    template class Species<double, long>;

}
