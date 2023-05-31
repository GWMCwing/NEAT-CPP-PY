#ifndef __NEAT_NODE_HPP__
#define __NEAT_NODE_HPP__

#include <vector>

#include "Activation.hpp"
#include "Edge.hpp"

namespace NEAT {

    // forward declaration
    template <typename dType, typename T2>
    class Edge;

    /**
     * @brief Enum for node type
     *
     */
    enum class NodeType {
        INPUT,
        OUTPUT,
        HIDDEN,
        BIAS,
        UNKNOWN // Used for placeholder
    };

    /**
     * @brief Node class for NEAT
     *
     * @tparam dType The type of the value of the node, the python interface only allows double
     * @tparam T2 The type of the innovation number, the python interface only allows int and long
     */
    template <typename dType = double, typename T2 = int>
    class Node final {
    public:
        /**
         * @brief Construct a new Node object
         *
         */
        Node();
        /**
         * @brief Construct a new Node object with initial value
         *
         * @param value value of the node
         * @param id id of the node
         * @param nodeType type of the node
         * @param layer layer of the node
         * @param activationFunction activation function of the node
         */
        Node(T2 id, NodeType nodeType, int layer, ActivationFunction<dType>* activationFunction);

        /**
         * @brief Get the Id of the node
         *
         * @return const T2&
         */
        const T2& getId() const;

        /**
         * @brief Get the type of the node
         *
         */
        const NodeType& getType() const;

        /**
         * @brief Get the Layer of the node
         *
         * @return const int&
         */
        const int& getLayer() const;

        /**
         * @brief Set the Layer of the node
         *
         * @param layer
         */
        void setLayer(int layer);

        /**
         * @brief Clone this node (deep copy)
         *
         * @return Node<dType, T2>* a pointer to the cloned node
         */
        Node<dType, T2>* clone() const;

        /**
         * @brief sort the edges of the node according to the innovation number
         *
         */
        void sortEdges();

        void addIncomingEdge(Edge<dType, T2>* edge);
        void addIncomingEdge(std::vector<Edge<dType, T2>*> edges);
        void addOutgoingEdge(Edge<dType, T2>* edge);
        void addOutgoingEdge(std::vector<Edge<dType, T2>*> edges);
        void setActivationFunction(ActivationFunction<dType>* activationFunction);

        const std::vector<Edge<dType, T2>*>& getIncomingEdges() const;
        const std::vector<Edge<dType, T2>*>& getOutgoingEdges() const;

        // NEAT::Genome will handle all the memory management
    private:
        /**
         * @brief value of the node
         *
         */
        dType value;
        /**
         * @brief id of the node
         *
         */
        T2 id;
        /**
         * @brief type of the node
         *
         */
        const NodeType nodeType;
        /**
         * @brief incoming edges of the node
         *
         */
        std::vector<Edge<dType, T2>*> incoming_edges;
        /**
         * @brief outgoing edges of the node
         *
         */
        std::vector<Edge<dType, T2>*> outgoing_edges;
        /**
         * @brief layer of the node
         *
         */
        int layer;
        // NodeState state = NodeState::UNINITIALIZED;
        /**
         * @brief activation function of the node
         *
         */
        ActivationFunction<dType>* activationFunction;
        // prevent copy and assignment
        Node(const Node<dType, T2>& node) = delete;
        Node<dType, T2>& operator=(const Node<dType, T2>& node) = delete;
    };
}

#endif // __NEAT_NODE_HPP__
