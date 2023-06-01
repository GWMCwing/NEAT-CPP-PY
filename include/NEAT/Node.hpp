#ifndef __NEAT_NODE_HPP__
#define __NEAT_NODE_HPP__

#include <vector>

#include "Activation.hpp"
#include "Genome.hpp"
#include "Edge.hpp"

namespace NEAT {

    // forward declaration
    template <typename dType, typename T2>
    class Genome;
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
         * @param id id of the node
         * @param nodeType type of the node
         * @param layer layer of the node
         * @param activationFunction activation function of the node
         */
        Node(T2 id, NodeType nodeType, int layer, dType bias, ActivationFunction<dType>* activationFunction);

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
         * @brief reset the value of the node
         *
         */
        void reset();

        /**
         * @brief Get the value of the node
         *
         * @return const dType&
         */
        const dType& getValue() const;

        /**
         * @brief Set the value of the node
         *
         * @param value
         */
        void setValue(dType value);

        /**
         * @brief get the value of the node
         *
         * @return dType& bias of the node
         */
        const dType& getBias() const;

        /**
         * @brief set the bias of the node
         *
         * @param value value of the bias node
         */
        void setBias(dType value);

        /**
         * @brief Get the Activation Function object pointer
         *
         * @return ActivationFunction<dType>*
         */
        ActivationFunction<dType>* getActivationFunction() const;

        /**
         * @brief get if node has been visited in a feed forward
         *
         * @return true node has been visited
         * @return false node has not been visited
         */
        const bool& isVisited() const;

        /**
         * @brief set if node has been visited in a feed forward
         *
         * @param visited node has been visited
         */
        void setVisited(bool visited);

        /**
         * @brief feed forward the node
         *
         */
        void forwardPropagate(const Genome<dType, T2>* genome);

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

        /**
         * @brief print the node
         *
         */
        void print(int tabSize = 0) const;

        // NEAT::Genome will handle all the memory management
    private:
        /**
         * @brief value of the node
         *
         */
        dType value;
        /**
         * @brief bias of the node
         *
         */
        dType bias;
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
        /**
         * @brief visited flag for feed forward
         *
         */
        bool visited = false;
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
