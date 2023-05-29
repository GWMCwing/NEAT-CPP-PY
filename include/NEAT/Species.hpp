#ifndef __NEAT_SpeciesHandler_HPP__
#define __NEAT_SpeciesHandler_HPP__

#include <vector>

#include "./Genome.hpp"

namespace NEAT {
    // forward declaration
    template <typename dType, typename T2>
    class Genome;

    /**
     * @brief Class for Species storage, reproduction and handling, all genomes has to be calculated fitness before adding
     *
     * @tparam dType type of data
     * @tparam T2 type of innovation number
     */
    template <typename dType = float, typename T2 = int>
    class SpeciesHandler final {
    public:
        SpeciesHandler();
        /**
         * @brief Add genome(s) to species
         *
         * @param genome genome(s) to add
         */
        void addGenome(Genome<dType, T2>* genome);
        void addGenome(std::vector<Genome<dType, T2>*> genomes);
        /**
         * @brief Remove genome(s) from species
         *
         * @param genome genome(s) to remove
         */
        void removeGenome(Genome<dType, T2>* genome);
        void removeGenome(std::vector<Genome<dType, T2>*> genomes);
        /**
         * @brief Get next generation of genomes
         *
         * @param c1 excess coefficient of distance formula
         * @param c2 disjoint coefficient of distance formula
         * @param c3 weight coefficient of distance formula
         * @param n number of genomes to reproduce
         * @return std::vector<Genome<dType, T2>*> next generation of genomes
         */
        std::vector<Genome<dType, T2>*> reproduce(dType c1, dType c2, dType c3, T2 n = -1);

    private:
        /**
         * @brief Species class for SpeciesHandler
         *
         * @tparam dType type of data
         * @tparam T2 type of innovation number
         */
        template <typename dType = float, typename T2 = int>
        class Species {
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
             * @brief Calculate if the genome is in the same species, return distance if within threshold, else return -1
             *
             * @param genome genome to compare
             * @param c1 excess coefficient of distance formula
             * @param c2 disjoint coefficient of distance formula
             * @param c3 weight coefficient of distance formula
             * @return dType distance if within threshold, else return -1
             */
            dType isSameSpecies(const Genome<dType, T2>* genome, dType c1, dType c2, dType c3) const;
        private:
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
            // prevent copying
            Species(const Species<dType, T2>& species) = delete;
            Species<dType, T2>& operator=(const Species<dType, T2>& species) = delete;
        };
        // 
        /**
         * @brief Species vector
         *
         */
        std::vector<Species<dType, T2>*> species;
        // prevent copying
        SpeciesHandler(const SpeciesHandler<dType, T2>& speciesHandler) = delete;
        SpeciesHandler<dType, T2>& operator=(const SpeciesHandler<dType, T2>& speciesHandler) = delete;
    };
}

#endif // __NEAT_SpeciesHandler_HPP__
