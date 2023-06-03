#ifndef __NEAT_SPECIES_HPP__
#define __NEAT_SPECIES_HPP__

#include <vector>

#include "./Genome.hpp"

namespace NEAT {
    //forward declaration
    template <typename dType, typename T2>
    class Genome;

    /**
     * @brief Struct for edge difference
     *
     * @tparam dType type of data
     * @tparam T2 type of innovation number
     */
    template <typename dType = double, typename T2 = int>
    struct EdgeDifference final {
        std::vector<const Edge<dType, T2>*> disjoint;
        std::vector<const Edge<dType, T2>*> excess;
        std::vector<const Edge<dType, T2>*> matching;
    };

    /**
     * @brief Species class for SpeciesHandler
     *
     * @tparam dType type of data
     * @tparam T2 type of innovation number
     */
    template <typename dType, typename T2>
    class Species final {
    public:
        Species(Genome <dType, T2>* representative);

        /**
         * @brief Add genome to species
         *
         * @param genome
         */
        void addGenome(Genome<dType, T2>* genome);

        /**
         * @brief Get the Representative object
         *
         * @return const Genome<dType, T2>*
         */
        const Genome<dType, T2>* getRepresentative() const;

        /**
         * @brief Get the distance between the genome and the representative of the species
         *
         * @param genome genome to compare
         * @param c1 excess coefficient of distance formula
         * @param c2 disjoint coefficient of distance formula
         * @param c3 weight coefficient of distance formula
         * @return dType distance between the genome and the representative of the species
         */
        dType getDistance(const Genome<dType, T2>* genome, dType c1, dType c2, dType c3) const;

        /**
         * @brief Get the Edge Difference of 2 genomes
         *
         * @param genome1 reference genome
         * @param genome2 target genome
         * @return EdgeDifference
         */
        EdgeDifference<dType, T2> getEdgeDifference(const Genome<dType, T2>* genome1, const Genome<dType, T2>* genome2) const;

        // /**
        //  * @brief Get the Excess Difference of the genome and the representative of the species
        //  *
        //  * @param incompatibleEdge incompatible edges of the genome to compare
        //  * @param maxId_representative max innovation number of the representative of the species
        //  * @param maxId_target max innovation number of the genome
        //  * @return T2 excess difference
        //  * merged with getDisjointDifference
        //  */
        // T2 getExcessDifference(const std::vector<T2>& incompatibleEdge, const T2& maxId_representative, const T2& maxId_target) const;

        // /**
        //  * @brief Get the Disjoint Difference of the genome and the representative of the species
        //  *
        //  * @param incompatibleEdge incompatible edges of the genome to compare
        //  * @param maxId_representative max innovation number of the representative of the species
        //  * @param maxId_target max innovation number of the genome
        //  * @return T2 disjoint difference
        //  * merged with getExcessDifference
        //  */
        // T2 getDisjointDifference(const std::vector<T2>& incompatibleEdge, const T2& maxId_representative, const T2& maxId_target) const;

        /**
         * @brief Get the Average Weight Difference of the genome and the representative of the species
         *
         * @param genome genome to compare
         * @return dType average weight difference
         */
        dType getAverageWeightDifference(const Genome<dType, T2>* genome) const;

        // std::vector<Edge<dType, T2>*> getIncompatibleEdge(const Genome<dType, T2>* genome) const;

        /**
         * @brief Calculate if the genome is in the same species, return distance if within threshold, else return -1
         *
         * @param genome genome to compare
         * @param c1 excess coefficient of distance formula
         * @param c2 disjoint coefficient of distance formula
         * @param c3 weight coefficient of distance formula
         * @return dType distance if within threshold, else return -1
         */
        dType isSameSpecies(const Genome<dType, T2>* genome, dType c1, dType c2, dType c3, dType threshold) const;

        /**
         * @brief fitness sharing of the species, divide fitness by number of genomes in the species
         *
         */
        void fitnessShare();

        /**
         * @brief Sort genomes in the species by fitness
         *
         * @return const std::vector<Genome<dType, T2>*>&
         */
        const std::vector<Genome<dType, T2>*>& sortGenomes();

        Genome<dType, T2>* crossover(const Genome<dType, T2>* genome1, const Genome<dType, T2>* genome2) const;

        /**
         * @brief Generate next generation of genomes
         *
         * @param geneHistory gene history
         * @param n number of genomes to reproduce
         * @return std::vector<Genome<dType, T2>*> next generation of genomes
         */
        std::vector<Genome<dType, T2>*> generateNextGeneration(GeneHistory<dType, T2>& geneHistory, T2 n, const MutationConfig<dType>& mutationConfig);

        /**
         * @brief Get the Average Fitness of the species, assume fitness sharing has been done and total fitness is calculated
         *
         * @return dType average fitness
         */
        dType getAverageFitness() const;

    private:

        const Genome<dType, T2>* getRandomGenome() const;

        /**
         * @brief Genomes in the species
         *
         */
        std::vector<Genome<dType, T2>*> genomes;
        /**
         * @brief Representative of the species
         *
         */
        Genome<dType, T2>* representative;
        dType totalFitness = 0;
        // prevent copying
        Species(const Species<dType, T2>& species) = delete;
        Species<dType, T2>& operator=(const Species<dType, T2>& species) = delete;
    };
}

#endif // __NEAT_SPECIES_HPP__
