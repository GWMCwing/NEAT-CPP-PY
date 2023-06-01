#ifndef __NEAT_SpeciesHandler_HPP__
#define __NEAT_SpeciesHandler_HPP__

#include <vector>

#include "./Genome.hpp"
#include "./Edge.hpp"
#include "./GeneHistory.hpp"

namespace NEAT {
    // forward declaration
    template <typename dType, typename T2>
    class Genome;
    template <typename dType, typename T2>
    class Edge;

    /**
     * @brief Struct for edge difference
     *
     * @tparam dType type of data
     * @tparam T2 type of innovation number
     */
    template <typename dType = double, typename T2 = int>
    struct EdgeDifference {
        std::vector<const Edge<dType, T2>*> disjoint;
        std::vector<const Edge<dType, T2>*> excess;
        std::vector<const Edge<dType, T2>*> matching;
    };

    /**
     * @brief Class for Species storage, reproduction and handling, all genomes has to be calculated fitness before adding
     *
     * @tparam dType type of data
     * @tparam T2 type of innovation number
     */
    template <typename dType = double, typename T2 = int>
    class SpeciesHandler final {
    public:
        SpeciesHandler(dType c1, dType c2, dType c3, dType threshold);
        /**
         * @brief Add genome(s) to species
         *
         * @param genome genome(s) to add
         */
        void addGenome(Genome<dType, T2>* genome);
        void addGenome(std::vector<Genome<dType, T2>*> genomes);

        /**
         * @brief Get next generation of genomes
         *
         * @param c1 excess coefficient of distance formula
         * @param c2 disjoint coefficient of distance formula
         * @param c3 weight coefficient of distance formula
         * @param n number of genomes to reproduce
         * @return std::vector<Genome<dType, T2>*> next generation of genomes
         */
        std::vector<Genome<dType, T2>*> reproduce(dType c1, dType c2, dType c3, T2 n) const;
        std::vector<Genome<dType, T2>*> reproduce(T2 n) const;

        /**
         * @brief Get the sum of average fitness of all species
         *
         * @return dType average fitness
         */
        dType getAverageFitnessSum() const;

    private:
        // -------------- Species --------------
        /**
         * @brief Species class for SpeciesHandler
         *
         * @tparam dType type of data
         * @tparam T2 type of innovation number
         */
        template <typename dType2 = dType, typename T3 = T2>
        class Species final {
        public:
            Species(Genome <dType2, T3>* representative);

            /**
             * @brief Add genome to species
             *
             * @param genome
             */
            void addGenome(Genome<dType2, T3>* genome);

            /**
             * @brief Get the Representative object
             *
             * @return const Genome<dType, T2>*
             */
            const Genome<dType2, T3>* getRepresentative() const;

            /**
             * @brief Get the distance between the genome and the representative of the species
             *
             * @param genome genome to compare
             * @param c1 excess coefficient of distance formula
             * @param c2 disjoint coefficient of distance formula
             * @param c3 weight coefficient of distance formula
             * @return dType distance between the genome and the representative of the species
             */
            dType2 getDistance(const Genome<dType2, T3>* genome, dType2 c1, dType2 c2, dType2 c3) const;

            /**
             * @brief Get the Edge Difference of 2 genomes
             *
             * @param genome1 reference genome
             * @param genome2 target genome
             * @return EdgeDifference
             */
            EdgeDifference<dType2, T3> getEdgeDifference(const Genome<dType2, T3>* genome1, const Genome<dType2, T3>* genome2) const;

            // /**
            //  * @brief Get the Excess Difference of the genome and the representative of the species
            //  *
            //  * @param incompatibleEdge incompatible edges of the genome to compare
            //  * @param maxId_representative max innovation number of the representative of the species
            //  * @param maxId_target max innovation number of the genome
            //  * @return T3 excess difference
            //  * merged with getDisjointDifference
            //  */
            // T3 getExcessDifference(const std::vector<T3>& incompatibleEdge, const T3& maxId_representative, const T3& maxId_target) const;

            // /**
            //  * @brief Get the Disjoint Difference of the genome and the representative of the species
            //  *
            //  * @param incompatibleEdge incompatible edges of the genome to compare
            //  * @param maxId_representative max innovation number of the representative of the species
            //  * @param maxId_target max innovation number of the genome
            //  * @return T3 disjoint difference
            //  * merged with getExcessDifference
            //  */
            // T3 getDisjointDifference(const std::vector<T3>& incompatibleEdge, const T3& maxId_representative, const T3& maxId_target) const;

            /**
             * @brief Get the Average Weight Difference of the genome and the representative of the species
             *
             * @param genome genome to compare
             * @return dType2 average weight difference
             */
            dType2 getAverageWeightDifference(const Genome<dType2, T3>* genome) const;

            // std::vector<Edge<dType2, T3>*> getIncompatibleEdge(const Genome<dType2, T3>* genome) const;

            /**
             * @brief Calculate if the genome is in the same species, return distance if within threshold, else return -1
             *
             * @param genome genome to compare
             * @param c1 excess coefficient of distance formula
             * @param c2 disjoint coefficient of distance formula
             * @param c3 weight coefficient of distance formula
             * @return dType distance if within threshold, else return -1
             */
            dType2 isSameSpecies(const Genome<dType2, T3>* genome, dType2 c1, dType2 c2, dType2 c3, dType2 threshold) const;

            /**
             * @brief fitness sharing of the species, divide fitness by number of genomes in the species
             *
             */
            void fitnessShare();

            /**
             * @brief Sort genomes in the species by fitness
             *
             * @return const std::vector<Genome<dType2, T3>*>&
             */
            const std::vector<Genome<dType2, T3>*>& sortGenomes();

            Genome<dType2, T3>* crossover(const Genome<dType2, T3>* genome1, const Genome<dType2, T3>* genome2) const;

            /**
             * @brief Generate next generation of genomes
             *
             * @param c1 excess coefficient of distance formula
             * @param c2 disjoint coefficient of distance formula
             * @param c3 weight coefficient of distance formula
             * @param n number of genomes to reproduce
             * @return std::vector<Genome<dType2, T3>*> next generation of genomes
             */
            std::vector<Genome<dType2, T3>*> generateNextGeneration(GeneHistory<dType2, T3>& geneHistory, dType2 c1, dType2 c2, dType2 c3, T3 n) const;

            /**
             * @brief Get the Average Fitness of the species, assume fitness sharing has been done and total fitness is calculated
             *
             * @return dType2 average fitness
             */
            dType2 getAverageFitness() const;

        private:

            const Genome<dType2, T3>* getRandomGenome() const;

            /**
             * @brief Genomes in the species
             *
             */
            std::vector<Genome<dType2, T3>*> genomes;
            /**
             * @brief Representative of the species
             *
             */
            Genome<dType2, T3>* representative;
            dType2 totalFitness = 0;
            // prevent copying
            Species(const Species<dType2, T3>& species) = delete;
            Species<dType2, T3>& operator=(const Species<dType2, T3>& species) = delete;
        };
        // 
        // ------------- SpeciesHandler ------------------
        // 
        /**
         * @brief Species vector
         *
         */
        std::vector<Species<dType, T2>*> species;
        /**
         * @brief excess coefficients of distance formula
         *
         */
        dType c1;
        /**
         * @brief disjoint coefficients of distance formula
         *
         */
        dType c2;
        /**
         * @brief weight coefficients of distance formula
         *
         */
        dType c3;
        /**
         * @brief threshold of distance formula
         *
         */
        dType threshold;
        // prevent copying
        SpeciesHandler(const SpeciesHandler<dType, T2>& speciesHandler) = delete;
        SpeciesHandler<dType, T2>& operator=(const SpeciesHandler<dType, T2>& speciesHandler) = delete;
    };
}

#endif // __NEAT_SpeciesHandler_HPP__
