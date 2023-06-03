#include <iostream>
#include <algorithm>
#include <vector>

#include "../include/NEAT/Node.hpp"
#include "../include/NEAT/Helper.hpp"

namespace NEAT {

    template <typename dType, typename T2>
    Node<dType, T2>::Node() : value(0), bias(0), nodeType(NodeType::UNKNOWN), layer(-1), visited(false) {
        this->activationFunction = nullptr;
        this->incoming_edges = std::vector<Edge<dType, T2>*>();
        this->outgoing_edges = std::vector<Edge<dType, T2>*>();
    }

    template <typename dType, typename T2>
    Node<dType, T2>::Node(T2 id, NodeType type, int layer, dType bias, ActivationFunction<dType>* activationFunction) :
        value(0), bias(bias), id(id), nodeType(type), layer(layer), activationFunction(activationFunction)
        // , state(NodeState::FULLY_INITIALIZED) 
    {
        this->incoming_edges = std::vector<Edge<dType, T2>*>();
        this->outgoing_edges = std::vector<Edge<dType, T2>*>();
    }

    template <typename dType, typename T2>
    const T2& Node<dType, T2>::getId() const {
        return id;
    }

    template <typename dType, typename T2>
    const NodeType& Node<dType, T2>::getType() const {
        return nodeType;
    }

    template <typename dType, typename T2>
    const int& Node<dType, T2>::getLayer() const {
        return layer;
    }

    template <typename dType, typename T2>
    void Node<dType, T2>::setLayer(int layer) {
        this->layer = layer;
    }

    template <typename dType, typename T2>
    void Node<dType, T2>::reset() {
        this->value = 0;
        this->visited = false;
    }

    template <typename dType, typename T2>
    void Node<dType, T2>::setVisited(bool visited) {
        this->visited = visited;
    }

    template <typename dType, typename T2>
    const bool& Node<dType, T2>::isVisited() const {
        return visited;
    }

    template <typename dType, typename T2>
    const dType& Node<dType, T2>::getValue() const {
        return value;
    }

    template <typename dType, typename T2>
    void Node<dType, T2>::setValue(dType value) {
        this->value = value;
    }

    template <typename dType, typename T2>
    const dType& Node<dType, T2>::getBias() const {
        return bias;
    }

    template <typename dType, typename T2>
    void Node<dType, T2>::setBias(dType value) {
        this->bias = value;
    }

    template <typename dType, typename T2>
    ActivationFunction<dType>* Node<dType, T2>::getActivationFunction() const {
        return activationFunction;
    }

    template <typename dType, typename T2>
    void Node<dType, T2>::forwardPropagate(const Genome<dType, T2>* genome) {
        if (dynamic_cast<ActivationFunction_Single<dType>*>(this->activationFunction) != nullptr) {
            this->value = (*(
                dynamic_cast<ActivationFunction_Single<dType>*>(this->activationFunction)
                ))(this->value + this->bias);
        }
        if (this->nodeType == NodeType::OUTPUT) {
            return;
        }
        for (Edge<dType, T2>* edge : outgoing_edges) {
            edge->getTo(genome)->value += edge->getWeight() * this->value;
        }
    }

    template <typename dType, typename T2>
    Node<dType, T2>* Node<dType, T2>::clone() const {
        Node<dType, T2>* newNode = new Node<dType, T2>(id, nodeType, layer, bias, activationFunction);
        newNode->value = value;
        // TODO: clone edges without duplicating them, possible get from a genome as a parameter input
        // for (const Edge<dType, T2>* edge : incoming_edges) {
        //     newNode->incoming_edges.push_back(edge->clone());
        // }
        // for (const Edge<dType, T2>* edge : outgoing_edges) {
        //     newNode->outgoing_edges.push_back(edge->clone());
        // }
        // newNode->sortEdges();
        return newNode;
    }

    template <typename dType, typename T2>
    void Node<dType, T2>::sortEdges() {
        std::sort(incoming_edges.begin(), incoming_edges.end(), [](const Edge<dType, T2>* a, const Edge<dType, T2>* b) {
            return a->getInnovationNumber() < b->getInnovationNumber();
            });
        std::sort(outgoing_edges.begin(), outgoing_edges.end(), [](const Edge<dType, T2>* a, const Edge<dType, T2>* b) {
            return a->getInnovationNumber() < b->getInnovationNumber();
            });
    }

    template <typename dType, typename T2>
    void Node<dType, T2>::addIncomingEdge(Edge<dType, T2>* edge) {
        incoming_edges.push_back(edge);
    }

    template <typename dType, typename T2>
    void Node<dType, T2>::addIncomingEdge(std::vector<Edge<dType, T2>*> edges) {
        incoming_edges.insert(incoming_edges.end(), edges.begin(), edges.end());
    }

    template <typename dType, typename T2>
    void Node<dType, T2>::addOutgoingEdge(Edge<dType, T2>* edge) {
        outgoing_edges.push_back(edge);
    }

    template <typename dType, typename T2>
    void Node<dType, T2>::addOutgoingEdge(std::vector<Edge<dType, T2>*> edges) {
        outgoing_edges.insert(outgoing_edges.end(), edges.begin(), edges.end());
    }

    template <typename dType, typename T2>
    void Node<dType, T2>::setActivationFunction(ActivationFunction<dType>* activationFunction) {
        this->activationFunction = activationFunction;
    }

    template <typename dType, typename T2>
    const std::vector<Edge<dType, T2>*>& Node<dType, T2>::getIncomingEdges() const {
        return incoming_edges;
    }

    template <typename dType, typename T2>
    const std::vector<Edge<dType, T2>*>& Node<dType, T2>::getOutgoingEdges() const {
        return outgoing_edges;
    }

    template <typename dType, typename T2>
    void Node<dType, T2>::print(int tabSize) const {
        coutTab(tabSize);
        std::cout << "Node: " << id << " type: ";
        if (nodeType == NodeType::INPUT) {
            std::cout << "INPUT";
        } else if (nodeType == NodeType::OUTPUT) {
            std::cout << "OUTPUT";
        } else if (nodeType == NodeType::HIDDEN) {
            std::cout << "HIDDEN";
        } else if (nodeType == NodeType::BIAS) {
            std::cout << "BIAS";
        } else {
            std::cout << "UNKNOWN";
        }
        std::cout << " layer: " << layer << " bias: " << bias << " value: " << value << std::endl;
        coutTab(tabSize);
        std::cout << "  Incoming edges: " << incoming_edges.size() << std::endl;
        if (incoming_edges.size() == 0) {
            coutTab(tabSize + 1);
            std::cout << "None" << std::endl;
        } else {
            for (Edge<dType, T2>* edge : incoming_edges) {
                edge->print(tabSize + 1);
            }
        }
        coutTab(tabSize);
        std::cout << "  Outgoing edges: " << outgoing_edges.size() << std::endl;
        if (outgoing_edges.size() == 0) {
            coutTab(tabSize + 1);
            std::cout << "None" << std::endl;
        } else {
            for (Edge<dType, T2>* edge : outgoing_edges) {
                edge->print(tabSize + 1);
            }
        }
    }

    // Explicitly instantiate
    template class Node<double, int>;
    template class Node<double, long>;
}
