#include <iostream>
#include <algorithm>
#include "../include/NEAT/Genome.hpp"
#include "../include/NEAT/Activation.hpp"
#include "../include/NEAT/Helper.hpp"
namespace NEAT {
    template <typename dType, typename T2>
    Genome<dType, T2>::Genome() :inputSize(0), outputSize(0) {
        this->nodes = std::map< T2, Node<dType, T2>* >();
        this->edges = std::map< T2, Edge<dType, T2>* >();
    }

    template <typename dType, typename T2>
    Genome<dType, T2>::Genome(T2 inputSize, T2 outputSize, bool init) :inputSize(inputSize), outputSize(outputSize) {
        if (!init) return;
        // 1. create input nodes
        for (T2 i = 0; i < inputSize; i++) {
            Node<dType, T2>* node = new Node<dType, T2>(i, NodeType::INPUT, 0, 0, getActivationFunction_Factory<dType>()->identity);
            addNode(node);
        }
        // 2. create output nodes
        for (T2 i = 0; i < outputSize; i++) {
            Node<dType, T2>* node = new Node<dType, T2>(i + inputSize, NodeType::OUTPUT, 1, gaussianDistribution<dType>(0, 1), getActivationFunction_Factory<dType>()->identity);
            addNode(node);
        }
        // 3. create edges
        for (T2 i = 0; i < inputSize; i++) {
            for (T2 j = 0; j < outputSize; j++) {
                Node<dType, T2>* fromNode = nodes[i];
                Node<dType, T2>* toNode = nodes[j + inputSize];
                Edge<dType, T2>* edge = new Edge<dType, T2>(fromNode, toNode, gaussianDistribution<dType>(0, 1), i * outputSize + j);
                addEdge(edge);
                fromNode->addOutgoingEdge(edge);
                toNode->addIncomingEdge(edge);
            }
        }
    }

    template <typename dType, typename T2>
    Genome<dType, T2>::~Genome() {
        for (std::pair<const T2, NEAT::Node<dType, T2>*> pair : nodes) {
            delete pair.second;
        }
        for (std::pair<const T2, Edge<dType, T2>*> pair : edges) {
            delete pair.second;
        }
    }

    template <typename dType, typename T2>
    const T2& Genome<dType, T2>::getInputSize() const {
        return inputSize;
    }

    template <typename dType, typename T2>
    const T2& Genome<dType, T2>::getOutputSize() const {
        return outputSize;
    }

    template <typename dType, typename T2>
    const std::map< T2, Node<dType, T2>* >& Genome<dType, T2>::getNodes() const {
        return nodes;
    }

    template <typename dType, typename T2>
    const std::map< T2, Edge<dType, T2>* >& Genome<dType, T2>::getEdges() const {
        return edges;
    }

    template <typename dType, typename T2>
    Edge<dType, T2>* Genome<dType, T2>::getEdge(T2 innovationNumber) const {
        Edge<dType, T2>* edge;
        try {
            edge = edges.at(innovationNumber);
        }
        catch (const std::out_of_range& oor) {
            // std::cerr << "Edge Access Out of Range error: " << oor.what() << '\n';
            return nullptr;
        }
        return edge;
    }

    template <typename dType, typename T2>
    Node<dType, T2>* Genome<dType, T2>::getNode(T2 id) const {
        Node<dType, T2>* node;
        try {
            node = nodes.at(id);
        }
        catch (const std::out_of_range& oor) {
            // std::cerr << "Node Access Out of Range error: " << oor.what() << '\n';
            return nullptr;
        }
        return node;
    }

    template <typename dType, typename T2>
    bool Genome<dType, T2>::addCloneEdge(const Edge<dType, T2>* edge) {
        if (edge == nullptr) {
            return false;
        }
        Edge<dType, T2>* cloneEdge = edge->clone();
        bool success = addEdge(cloneEdge);
        if (!success) {
            delete cloneEdge;
        }
        return success;
    }

    template <typename dType, typename T2>
    bool Genome<dType, T2>::addCloneNode(const Node<dType, T2>* node) {
        if (node == nullptr) {
            return false;
        }
        Node<dType, T2>* cloneNode = node->clone();
        bool success = addNode(cloneNode);
        if (!success) {
            delete cloneNode;
        }
        return success;
    }

    template <typename dType, typename T2>
    bool Genome<dType, T2>::addNode_noClone(Node<dType, T2>* node) {
        if (node == nullptr) {
            return false;
        }
        bool success = addNode(node);
        return success;
    }

    template <typename dType, typename T2>
    void Genome<dType, T2>::disableEdge(T2 innovationNumber) {
        Edge<dType, T2>* edge = getEdge(innovationNumber);
        if (edge != nullptr) {
            edge->disable();
        }
    }

    template <typename dType, typename T2>
    void Genome<dType, T2>::enableEdge(T2 innovationNumber) {
        Edge<dType, T2>* edge = getEdge(innovationNumber);
        if (edge != nullptr) {
            edge->enable();
        }
    }

    template <typename dType, typename T2>
    void Genome<dType, T2>::toggleEdge(T2 innovationNumber) {
        Edge<dType, T2>* edge = getEdge(innovationNumber);
        if (edge != nullptr) {
            edge->toggle();
        }
    }

    template <typename dType, typename T2>
    T2 Genome<dType, T2>::getMaxInnovationNumber() const {
        T2 maxInnovationNumber = 0;
        for (std::pair<const T2, Edge<dType, T2>*> pair : edges) {
            if (pair.first > maxInnovationNumber) {
                maxInnovationNumber = pair.first;
            }
        }
        return maxInnovationNumber;
    }

    template <typename dType, typename T2>
    T2 Genome<dType, T2>::getNumberOfGenes() const {
        return edges.size() + nodes.size();
    }

    template <typename dType, typename T2>
    void Genome<dType, T2>::setFitness(dType fitness) {
        this->fitness = fitness;
    }

    template <typename dType, typename T2>
    const dType& Genome<dType, T2>::getFitness() const {
        return fitness;
    }

    template <typename dType, typename T2>
    void Genome<dType, T2>::feedForward(const std::vector<dType>& inputs, std::vector<dType>& outputs) {
        std::vector<Node<dType, T2>*> allNodes;

        if (static_cast<T2>(inputs.size()) != inputSize) {
            std::cerr << "Input size does not match genome input size" << std::endl;
            outputs.assign(outputSize, 0);
            return;
        }
        // 1. reset all nodes
        for (std::pair<const T2, Node<dType, T2>*> pair : nodes) {
            pair.second->reset();
        }
        // 2. set input nodes
        for (T2 i = 0; i < inputSize; i++) {
            Node<dType, T2>* node = nodes.at(i);
            node->setValue(inputs.at(i));
        }
        // 3. sort nodes according to layer
        for (std::pair<const T2, Node<dType, T2>*> pair : nodes) {
            allNodes.push_back(pair.second);
        }
        std::sort(allNodes.begin(), allNodes.end(), [](Node<dType, T2>* a, Node<dType, T2>* b) {
            return a->getLayer() < b->getLayer();
            });
        // 4. forward propagate
        for (Node<dType, T2>* node : allNodes) {
            node->forwardPropagate(this);
        }
        // 5. get output nodes
        for (T2 i = inputSize; i < inputSize + outputSize; i++) {
            Node<dType, T2>* node = nodes.at(i);
            outputs.push_back(node->getValue());
        }
    }

    template <typename dType, typename T2>
    T2 Genome<dType, T2>::predict(const std::vector<dType>& inputs) {
        std::vector<dType> outputs{};
        feedForward(inputs, outputs);
        T2 maxIndex = 0;
        for (T2 i = 0; i < outputSize; i++) {
            if (outputs[i] > outputs[maxIndex]) {
                maxIndex = i;
            }
        }
        return maxIndex;
    }

    template <typename dType, typename T2>
    Genome<dType, T2>* Genome<dType, T2>::clone() const {
        // TODO: Check all clone mem leak or ref leak
        Genome<dType, T2>* newGenome = new Genome<dType, T2>();
        newGenome->inputSize = inputSize;
        newGenome->outputSize = outputSize;
        for (std::pair<const T2, Node<dType, T2>*> pair : nodes) {
            Node<dType, T2>* newNode = pair.second->clone();
            newGenome->addEdge(newNode->getIncomingEdges());
            newGenome->addEdge(newNode->getOutgoingEdges());
            newGenome->addNode(newNode);
        }
        return newGenome;
    }

    // private

    template <typename dType, typename T2>
    bool Genome<dType, T2>::addNode(Node<dType, T2>* node) {
        // check if node already exists
        if (getNode(node->getId()) != nullptr) {
            return false;
        }
        nodes.insert(std::pair<T2, Node<dType, T2>*>(node->getId(), node));
        return true;
    }

    template <typename dType, typename T2>
    bool Genome<dType, T2>::addEdge(Edge<dType, T2>* edge) {
        // check if edge already exists
        if (getEdge(edge->getInnovationNumber()) != nullptr) {
            return false;
        }
        edges.insert(std::pair<T2, Edge<dType, T2>*>(edge->getInnovationNumber(), edge));
        return true;
    }

    template <typename dType, typename T2>
    std::vector<bool> Genome<dType, T2>::addEdge(std::vector<Edge<dType, T2>*> edges) {
        std::vector<bool> addedEdges;
        for (Edge<dType, T2>* edge : edges) {
            addedEdges.push_back(addEdge(edge));
        }
        return addedEdges;
    }

    // Explicit Instantiation
    template class Genome<double, int>;
    template class Genome<double, long>;
}
