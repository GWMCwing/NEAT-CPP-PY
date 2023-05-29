#include <iostream>
#include "../include/NEAT/Genome.hpp"

namespace NEAT {

    template <typename dType, typename T2>
    Genome<dType, T2>::Genome() { }

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
            std::cerr << "Edge Access Out of Range error: " << oor.what() << '\n';
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
            std::cerr << "Node Access Out of Range error: " << oor.what() << '\n';
            return nullptr;
        }
        return node;
    }

    template <typename dType, typename T2>
    void Genome<dType, T2>::addNode(Node<dType, T2>* node) {
        nodes.insert(std::pair<T2, Node<dType, T2>*>(node->getId(), node));
    }

    template <typename dType, typename T2>
    void Genome<dType, T2>::addEdge(Edge<dType, T2>* edge) {
        edges.insert(std::pair<T2, Edge<dType, T2>*>(edge->getInnovationNumber(), edge));
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

    // Explicit Instantiation
    template class Genome<float, int>;
    template class Genome<double, int>;
    template class Genome<float, long>;
    template class Genome<double, long>;
}
