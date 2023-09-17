// #include <pybind11/pybind11.h>
// #include <pybind11/stl.h>
// #include <pybind11/functional.h>
#include "../lib/pybind11/include/pybind11/pybind11.h"
#include "../lib/pybind11/include/pybind11/stl.h"
#include "../lib/pybind11/include/pybind11/functional.h"
// 
#include "../include/NEAT/Genome.hpp"
#include "../include/NEAT/Population.hpp"
#include "../include/NEAT/SpeciesHandler.hpp"
// 

namespace py = pybind11;

int add(int i, int j) {
  return i + j;
}

PYBIND11_MODULE(_neatcpy, m) {
  m.doc() = "NEATCPP Python Bindings";

  m.def("add", &add, "A function which adds two numbers");

  auto pyMutationConfig = py::class_ <NEAT::MutationConfig<double>>(m, "MutationConfig");
  auto pySpeciesConfig = py::class_ <NEAT::SpeciesConfig<double>>(m, "SpeciesConfig");
  auto pyPopulation = py::class_<NEAT::Population<double, int>>(m, "Population");
  auto pyGenome = py::class_<NEAT::Genome<double, int>>(m, "Genome");
  auto pyEdge = py::class_<NEAT::Edge<double, int>>(m, "Edge");
  auto pyNode = py::class_<NEAT::Node<double, int>>(m, "Node");
  auto pyGeneHistory = py::class_<NEAT::GeneHistory<double, int>>(m, "GeneHistory");


  pyMutationConfig.def(py::init<double, double, double, double, double, double>(),
    py::arg("nodeMutationChance") = 0.03,
    py::arg("edgeMutationChance") = 0.05,
    py::arg("toggleEdgeMutationChance") = 0.05,
    py::arg("weightMutationChance") = 0.8,
    py::arg("activationMutationChance") = 0.1,
    py::arg("biasMutationChance") = 0.1
  )
    .def_readwrite("nodeMutationChance", &NEAT::MutationConfig<double>::mutateAddNodeProbability)
    .def_readwrite("edgeMutationChance", &NEAT::MutationConfig<double>::mutateAddEdgeProbability)
    .def_readwrite("toggleEdgeMutationChance", &NEAT::MutationConfig<double>::mutateToggleEdgeProbability)
    .def_readwrite("weightMutationChance", &NEAT::MutationConfig<double>::mutateWeightProbability)
    .def_readwrite("activationMutationChance", &NEAT::MutationConfig<double>::mutateActivationFunctionProbability)
    .def_readwrite("biasMutationChance", &NEAT::MutationConfig<double>::mutateBiasProbability);

  pySpeciesConfig.def(py::init<double, double, double, double>(),
    py::arg("c1") = 1,
    py::arg("c2") = 1,
    py::arg("c3") = 0.4,
    py::arg("threshold") = 3
  )
    .def_readwrite("c1", &NEAT::SpeciesConfig<double>::c1)
    .def_readwrite("c2", &NEAT::SpeciesConfig<double>::c2)
    .def_readwrite("c3", &NEAT::SpeciesConfig<double>::c3)
    .def_readwrite("threshold", &NEAT::SpeciesConfig<double>::threshold);
  // 

  pyPopulation.def(py::init<int, int, int, NEAT::MutationConfig<double>, NEAT::SpeciesConfig<double>>())
    .def("startNextGeneration",
      py::overload_cast<>(&NEAT::Population<double, int>::startNextGeneration), py::return_value_policy::reference_internal
    )
    .def("startNextGeneration",
      py::overload_cast<int>(&NEAT::Population<double, int>::startNextGeneration), py::arg("populationSize"), py::return_value_policy::reference_internal
    )
    .def("startNextGeneration",
      py::overload_cast<std::vector<double>>(&NEAT::Population<double, int>::startNextGeneration), py::arg("fitnesses"), py::return_value_policy::reference_internal
    )
    .def("startNextGeneration",
      py::overload_cast<int, std::vector<double>>(&NEAT::Population<double, int>::startNextGeneration), py::arg("populationSize"), py::arg("fitnesses"), py::return_value_policy::reference_internal
    )
    // 
    .def("getGenomes", &NEAT::Population<double, int>::getGenomes, py::return_value_policy::reference_internal)
    .def("getGenome", &NEAT::Population<double, int>::getGenome, py::arg("index"), py::return_value_policy::reference_internal)
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
    .def("setMutationConfig", &NEAT::Population<double, int>::setMutationConfig, py::arg("mutationConfig"))
    .def("setSpeciesConfig", &NEAT::Population<double, int>::setSpeciesConfig, py::arg("speciesConfig"))
    // 
    .def("print", &NEAT::Population<double, int>::print, py::arg("tabSize") = 0);
  // 
  // 
  pyGenome.def(py::init<int, int, bool>(), py::arg("inputSize"), py::arg("outputSize"), py::arg("init") = true)
    .def("getInputSize", &NEAT::Genome<double, int>::getInputSize, py::return_value_policy::reference_internal)
    .def("getOutputSize", &NEAT::Genome<double, int>::getOutputSize, py::return_value_policy::reference_internal)
    // 
    .def("getNodes", &NEAT::Genome<double, int>::getNodes, py::return_value_policy::reference_internal)
    .def("getEdges", &NEAT::Genome<double, int>::getEdges, py::return_value_policy::reference_internal)
    .def("getEdge", &NEAT::Genome<double, int>::getEdge,
      py::arg("innovationNumber"),
      py::return_value_policy::reference_internal)
    .def("getNode", &NEAT::Genome<double, int>::getNode,
      py::arg("id"),
      py::return_value_policy::reference_internal)
    // 
    .def("addCloneEdge", &NEAT::Genome<double, int>::addCloneEdge,
      py::arg("edge"),
      py::return_value_policy::reference_internal)
    .def("addCloneNode", &NEAT::Genome<double, int>::addCloneNode,
      py::arg("node"), py::return_value_policy::reference_internal)
    .def("addNode_noClone", &NEAT::Genome<double, int>::addNode_noClone,
      py::arg("node"), py::return_value_policy::reference_internal)
    .def("disableEdge", &NEAT::Genome<double, int>::disableEdge,
      py::arg("innovationNumber"))
    .def("enableEdge", &NEAT::Genome<double, int>::enableEdge,
      py::arg("innovationNumber"))
    .def("toggleEdge", &NEAT::Genome<double, int>::toggleEdge,
      py::arg("innovationNumber"))
    // 
    .def("getMaxInnovationNumber", &NEAT::Genome<double, int>::getMaxInnovationNumber)
    .def("getNumberOfGenes", &NEAT::Genome<double, int>::getNumberOfGenes)
    // 
    .def("setFitness", &NEAT::Genome<double, int>::setFitness, py::arg("fitness"))
    .def("getFitness", &NEAT::Genome<double, int>::getFitness, py::return_value_policy::reference_internal)
    // 
    .def("mutate", &NEAT::Genome<double, int>::mutate,
      py::arg("geneHistory"),
      py::arg("mutationConfig") = NEAT::MutationConfig<double>()
    )
    .def("feedForward", py::overload_cast<const std::vector<double>&>(&NEAT::Genome<double, int>::feedForward),
      py::arg("inputs")
    )
    .def("predict", &NEAT::Genome<double, int>::predict,
      py::arg("inputs")
    )
    .def("clone", &NEAT::Genome<double, int>::clone)
    .def("print", &NEAT::Genome<double, int>::print, py::arg("tabSize") = 0);
}