#ifndef __NEAT_EDGE_HPP__
#define __NEAT_EDGE_HPP__

#include <vector>
#include "./Node.hpp"


namespace NEAT {

    // forward declaration
    template <typename dType, typename T2>
    class Node;

    /**
     * @brief Enum for edge state
     *
     */
    enum class EdgeState {
        ID_ENABLED,
        POINTER_ENABLED,
        BOTH_ENABLED,
        DISABLED
    };

    /**
     * @brief Edge class for NEAT
     *
     * @tparam dType The type of the value of the node, the python interface only allows float and double
     * @tparam T2 The type of the innovation number, the python interface only allows int and long
     */
    template <typename dType = float, typename T2 = int>
    class Edge final {
    public:
        /**
         * @brief Construct a new Edge object
         *
         * @param from pointer to the from node
         * @param to pointer to the to node
         * @param weight weight of the edge
         * @param innovationNumber innovation number of the edge
         */
        Edge(Node<dType, T2>* from, Node<dType, T2>* to, dType weight, T2 innovationNumber);
        /**
         * @brief Construct a new Edge object
         *
         * @param from_id id of the from node
         * @param to_id id of the to node
         * @param weight weight of the edge
         * @param innovationNumber innovation number of the edge
         */
        Edge(T2 from_id, T2 to_id, dType weight, T2 innovationNumber);
        /**
         * @brief Disable the edge
         *
         */
        void disable();
        /**
         * @brief Enable the edge
         *
         */
        void enable();
        /**
         * @brief toggle the edge
         *
         */
        void toggle();

        /**
         * @brief Get the Weight of the edge
         *
         * @return dType weight of the edge
         */
        dType getWeight() const;

        /**
         * @brief Update the from and to node of the edge by pointer
         *
         * @param from pointer to the from node
         * @param to pointer to the to node
         */
        void updateFromTo(Node<dType, T2>* from, Node<dType, T2>* to);
        /**
         * @brief Update the from and to node of the edge by id
         *
         * @param from_id id of the from node
         * @param to_id id of the to node
         */
        void updateFromTo(T2 from_id, T2 to_id);
        /**
         * @brief Get the State object
         *
         * @return const EdgeState& state of the edge
         */
        const EdgeState& getState() const;
        /**
         * @brief Get the Innovation Number object
         *
         * @return const T2& innovation number of the edge
         */
        const T2& getInnovationNumber() const;

    private:
        /**
         * @brief innovation number of the edge
         *
         */
        const T2 INNOVATION_NUMBER;
        /**
         * @brief pointer to the from node
         *
         */
        Node<dType, T2>* from;
        /**
         * @brief id of the from node
         *
         */
        T2 from_id;
        /**
         * @brief pointer to the to node
         *
         */
        Node<dType, T2>* to;
        /**
         * @brief id of the to node
         *
         */
        T2 to_id;
        /**
         * @brief weight of the edge
         *
         */
        dType weight;
        /**
         * @brief is the edge disabled
         *
         */
        bool disabled = false;
        /**
         * @brief state of the edge
         *
         */
        EdgeState state = EdgeState::DISABLED;

        // prevent copy and assignment
        Edge(const Edge<dType, T2>& edge) = delete;
        Edge<dType, T2>& operator=(const Edge<dType, T2>& edge) = delete;
    };
}

#endif // __NEAT_EDGE_HPP__
