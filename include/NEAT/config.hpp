#ifndef __NEAT_CONFIG_HPP__
#define __NEAT_CONFIG_HPP__

namespace NEAT {

    template <typename dType = double>
    struct SpeciesConfig final {
        dType c1 = 1;
        dType c2 = 1;
        dType c3 = 0.4;
        dType threshold = 3;
    };

    template <typename dType>
    struct MutationConfig final {
        dType mutateAddNodeProbability = 0.03;
        dType mutateAddEdgeProbability = 0.05;
        dType mutateToggleEdgeProbability = 0.05;
        dType mutateWeightProbability = 0.8;
        dType mutateActivationFunctionProbability = 0.1;
        dType mutateBiasProbability = 0.1;
    };

}

#endif // __NEAT_CONFIG_HPP__
