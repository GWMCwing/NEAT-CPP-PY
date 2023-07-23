#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
// 
#include "../include/NEAT/Genome.hpp"
#include "../include/NEAT/Population.hpp"
#include "../include/NEAT/SpeciesHandler.hpp"
// 

namespace py = pybind11;

PYBIND11_MODULE(NEATCPP, m) {
  m.doc() = "NEATCPP Python Bindings";

  py::class_ <NEAT::MutationConfig<double>>(m, "MutationConfig")
    .def(py::init<>())
    .def_readwrite("activationMutationChance", &NEAT::MutationConfig<double>::mutateActivationFunctionProbability)
    .def_readwrite("biasMutationChance", &NEAT::MutationConfig<double>::mutateBiasProbability)
    .def_readwrite("edgeMutationChance", &NEAT::MutationConfig<double>::mutateAddEdgeProbability)
    .def_readwrite("nodeMutationChance", &NEAT::MutationConfig<double>::mutateAddNodeProbability)
    .def_readwrite("weightMutationChance", &NEAT::MutationConfig<double>::mutateWeightProbability)
    .def_readwrite("toggleEdgeMutationChance", &NEAT::MutationConfig<double>::mutateToggleEdgeProbability);

  py::class_ <NEAT::SpeciesConfig<double>>(m, "SpeciesConfig")
    .def(py::init<>())
    .def_readwrite("c1", &NEAT::SpeciesConfig<double>::c1)
    .def_readwrite("c2", &NEAT::SpeciesConfig<double>::c2)
    .def_readwrite("c3", &NEAT::SpeciesConfig<double>::c3)
    .def_readwrite("threshold", &NEAT::SpeciesConfig<double>::threshold);
  // 

  py::class_<NEAT::Population<double, int>>(m, "Population")
    .def(py::init<int, int, int, NEAT::MutationConfig<double>, NEAT::SpeciesConfig<double>>())
    .def("startNextGeneration", (const std::vector<NEAT::Genome<double, int>*>&(NEAT::Population<double, int>::*)()) & NEAT::Population<double, int>::startNextGeneration, py::return_value_policy::reference_internal)
    .def("startNextGeneration", (const std::vector<NEAT::Genome<double, int>*>&(NEAT::Population<double, int>::*)(int)) & NEAT::Population<double, int>::startNextGeneration, py::return_value_policy::reference_internal)
    .def("startNextGeneration", (const std::vector<NEAT::Genome<double, int>*>&(NEAT::Population<double, int>::*)(std::vector<double>)) & NEAT::Population<double, int>::startNextGeneration, py::return_value_policy::reference_internal)
    .def("startNextGeneration", (const std::vector<NEAT::Genome<double, int>*>&(NEAT::Population<double, int>::*)(int, std::vector<double>)) & NEAT::Population<double, int>::startNextGeneration, py::return_value_policy::reference_internal)
    // 
    .def("getGenomes", &NEAT::Population<double, int>::getGenomes, py::return_value_policy::reference_internal)
    .def("getGenome", &NEAT::Population<double, int>::getGenome, py::return_value_policy::reference_internal)
    // 
    .def("getPopulationSize", &NEAT::Population<double, int>::getPopulationSize, py::return_value_policy::reference_internal)
    .def("getInputSize", &NEAT::Population<double, int>::getInputSize, py::return_value_policy::reference_internal)
    .def("getOutputSize", &NEAT::Population<double, int>::getOutputSize, py::return_value_policy::reference_internal)
    .def("getGeneration", &NEAT::Population<double, int>::getGeneration, py::return_value_policy::reference_internal)
    .def("getMutationConfig", &NEAT::Population<double, int>::getMutationConfig, py::return_value_policy::reference_internal)
    .def("getSpeciesConfig", &NEAT::Population<double, int>::getSpeciesConfig, py::return_value_policy::reference_internal)
    // 
    .def("getBestFitnessHistory", &NEAT::Population<double, int>::getBestFitnessHistory, py::return_value_policy::reference_internal)
    .def("getAverageFitnessHistory", &NEAT::Population<double, int>::getAverageFitnessHistory, py::return_value_policy::reference_internal)
    .def("getWorstFitnessHistory", &NEAT::Population<double, int>::getWorstFitnessHistory, py::return_value_policy::reference_internal)
    .def("getBestGenomeHistory", &NEAT::Population<double, int>::getBestGenomeHistory, py::return_value_policy::reference_internal)
    // 
    .def("setMutationConfig", &NEAT::Population<double, int>::setMutationConfig)
    .def("setSpeciesConfig", &NEAT::Population<double, int>::setSpeciesConfig)
    // 
    .def("print", &NEAT::Population<double, int>::print);
  // 
  // 
  py::class_<NEAT::Genome<double, int>>(m, "Genome")
    .def(py::init<int, int, bool>())
    .def("getInputSize", &NEAT::Genome<double, int>::getInputSize, py::return_value_policy::reference_internal)
    .def("getOutputSize", &NEAT::Genome<double, int>::getOutputSize, py::return_value_policy::reference_internal)
    // 
    .def("getNodes", &NEAT::Genome<double, int>::getNodes, py::return_value_policy::reference_internal)
    .def("getEdges", &NEAT::Genome<double, int>::getEdges, py::return_value_policy::reference_internal)
    .def("getEdge", &NEAT::Genome<double, int>::getEdge, py::return_value_policy::reference_internal)
    .def("getNode", &NEAT::Genome<double, int>::getNode, py::return_value_policy::reference_internal)
    // 
    .def("addCloneEdge", &NEAT::Genome<double, int>::addCloneEdge, py::return_value_policy::reference_internal)
    .def("addCloneNode", &NEAT::Genome<double, int>::addCloneNode, py::return_value_policy::reference_internal)
    .def("addNode_noClone", &NEAT::Genome<double, int>::addNode_noClone, py::return_value_policy::reference_internal)
    .def("disableEdge", &NEAT::Genome<double, int>::disableEdge, py::return_value_policy::reference_internal)
    .def("enableEdge", &NEAT::Genome<double, int>::enableEdge, py::return_value_policy::reference_internal)
    .def("toggleEdge", &NEAT::Genome<double, int>::toggleEdge, py::return_value_policy::reference_internal)
    // 
    .def("getMaxInnovationNumber", &NEAT::Genome<double, int>::getMaxInnovationNumber, py::return_value_policy::reference_internal)
    .def("getNumberOfGenes", &NEAT::Genome<double, int>::getNumberOfGenes, py::return_value_policy::reference_internal)
    // 
    .def("setFitness", &NEAT::Genome<double, int>::setFitness)
    .def("getFitness", &NEAT::Genome<double, int>::getFitness, py::return_value_policy::reference_internal)
    // 
    .def("mutate", &NEAT::Genome<double, int>::mutate, py::return_value_policy::reference_internal)
    .def("feedForward", &NEAT::Genome<double, int>::feedForward, py::return_value_policy::reference_internal)
    .def("predict", &NEAT::Genome<double, int>::predict, py::return_value_policy::reference_internal)
    .def("clone", &NEAT::Genome<double, int>::clone, py::return_value_policy::reference_internal)
    .def("print", &NEAT::Genome<double, int>::print);
}
