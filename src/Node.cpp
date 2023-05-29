#include "../include/NEAT/Node.hpp"

namespace NEAT {

    template <typename dType, typename T2>
    Node<dType, T2>::Node() { }

    template <typename dType, typename T2>
    Node<dType, T2>::Node(dType value, T2 id, NodeType type, int layer, ActivationFunction<dType>* activationFunction) :
        value(value), id(id), nodeType(type), layer(layer), activationFunction(activationFunction)
        // , state(NodeState::FULLY_INITIALIZED) 
    { }

    template <typename dType, typename T2>
    Node<dType, T2>* Node<dType, T2>::cloneEmptyEdge() const {
        return new Node<dType, T2>(value, id, nodeType, layer, activationFunction);
    }

    // Explicitly instantiate
    template class Node<float, int>;
    template class Node<double, int>;
    template class Node<float, long>;
    template class Node<double, long>;
}
