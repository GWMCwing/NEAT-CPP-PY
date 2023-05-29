#ifndef __NEAT_NODE_HPP__
#define __NEAT_NODE_HPP__

#include <vector>

#include "Activation.hpp"
#include "Edge.hpp"

namespace NEAT {

    // forward declaration
    template <typename dType, typename T2>
    class Edge;

    enum class NodeType {
        INPUT,
        OUTPUT,
        HIDDEN,
        BIAS,
        UNKNOWN
    };

    /**
     * @brief Node class for NEAT
     *
     * @tparam T The type of the value of the node, the python interface only allows float and double
     */
    template <typename dType = float, typename T2 = int>
    class Node final {
    public:
        Node();
        Node(dType value, T2 id, NodeType nodeType, int layer, ActivationFunction<dType>* activationFunction);
        Node<dType, T2>* cloneEmptyEdge() const;
        const T2& getId() const;

        // NEAT::Genome will handle all the memory management
    private:
        dType value;
        T2 id;
        const NodeType nodeType;
        std::vector<Edge<dType, T2>*> incoming_edges;
        std::vector<Edge<dType, T2>*> outgoing_edges;
        int layer;
        // NodeState state = NodeState::UNINITIALIZED;
        ActivationFunction<dType>* activationFunction;
        // 
        Node(const Node<dType, T2>& node) = delete;
        Node<dType, T2>& operator=(const Node<dType, T2>& node) = delete;
    };
}

#endif // __NEAT_NODE_HPP__
