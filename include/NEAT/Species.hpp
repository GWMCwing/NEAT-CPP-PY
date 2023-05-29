#ifndef __NEAT_SpeciesHandler_HPP__
#define __NEAT_SpeciesHandler_HPP__

#include <vector>

#include "./Genome.hpp"

namespace NEAT {
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
        void addGenome(Genome<dType, T2>* genome);
        void addGenome(std::vector<Genome<dType, T2>*> genomes);
        void removeGenome(Genome<dType, T2>* genome);
        void removeGenome(std::vector<Genome<dType, T2>*> genomes);
        std::vector<Genome<dType, T2>*> reproduce(T2 n, dType c1, dType c2, dType c3);

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
            void addGenome(Genome<dType, T2>* genome);
            const Genome<dType, T2>* getRepresentative() const;
        private:
            std::vector<Genome<dType, T2>*> genomes;
            Genome<dType, T2>* representative;
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
