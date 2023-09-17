#ifndef __NEAT_SpeciesHandler_HPP__
#define __NEAT_SpeciesHandler_HPP__

#include <vector>

#include "./Genome.hpp"
#include "./Edge.hpp"
#include "./GeneHistory.hpp"
#include "./Species.hpp"
#include "./config.hpp"

namespace NEAT {
    // forward declaration
    template <typename dType, typename T2>
    class Genome;
    template <typename dType, typename T2>
    class Edge;
    template <typename dType>
    struct MutationConfig;
    template <typename dType>
    struct SpeciesConfig;

    /**
     * @brief Class for Species storage, reproduction and handling, all genomes has to be calculated fitness before adding
     *
     * @tparam dType type of data
     * @tparam T2 type of innovation number
     */
    template <typename dType = double, typename T2 = int>
    class SpeciesHandler final {
    public:
        SpeciesHandler(Genome<dType, T2>* genome, dType c1, dType c2, dType c3, dType threshold);
        SpeciesHandler(std::vector<Genome<dType, T2>*>& genome, dType c1, dType c2, dType c3, dType threshold);
        SpeciesHandler(Genome<dType, T2>* genome, SpeciesConfig<dType> speciesConfig);
        SpeciesHandler(std::vector<Genome<dType, T2>*>& genome, SpeciesConfig<dType> speciesConfig);
        ~SpeciesHandler();
        /**
         * @brief Add genome(s) to species
         *
         * @param genome genome(s) to add
         */
        void addGenome(Genome<dType, T2>* genome);
        void addGenome(std::vector<Genome<dType, T2>*>& genomes);

        /**
         * @brief Get next generation of genomes
         *
         * @param c1 excess coefficient of distance formula
         * @param c2 disjoint coefficient of distance formula
         * @param c3 weight coefficient of distance formula
         * @param n number of genomes to reproduce
         * @return std::vector<Genome<dType, T2>*> next generation of genomes
         */
        std::vector<Genome<dType, T2>*> reproduce(T2 n, const MutationConfig<dType>& mutationConfig) const;
        // std::vector<Genome<dType, T2>*> reproduce(T2 n) const;

        /**
         * @brief Get the sum of average fitness of all species
         *
         * @return dType average fitness
         */
        dType getAverageFitnessSum() const;
        void print(int tabSize) const;

    private:
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
