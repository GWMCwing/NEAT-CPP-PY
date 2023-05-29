#ifndef __NEAT_EDGE_HPP__
#define __NEAT_EDGE_HPP__

#include <vector>
#include "./Node.hpp"


namespace NEAT {

    // forward declaration
    template <typename dType, typename T2>
    class Node;

    enum class EdgeState {
        ID_ENABLED,
        POINTER_ENABLED,
        BOTH_ENABLED,
        DISABLED
    };

    template <typename dType = float, typename T2 = int>
    class Edge final {
    public:
        // 
        Edge(Node<dType, T2>* from, Node<dType, T2>* to, dType weight, T2 innovationNumber);
        Edge(T2 from_id, T2 to_id, dType weight, T2 innovationNumber);
        void disable();
        void enable();
        void toggle();

        void updateFromTo(Node<dType, T2>* from, Node<dType, T2>* to);
        void updateFromTo(T2 from_id, T2 to_id);
        const EdgeState& getState() const;
        const T2& getInnovationNumber() const;

    private:
        const T2 INNOVATION_NUMBER;
        Node<dType, T2>* from;
        T2 from_id;
        Node<dType, T2>* to;
        T2 to_id;
        dType weight;
        bool disabled = false;
        EdgeState state = EdgeState::DISABLED;

        Edge(const Edge<dType, T2>& edge) = delete;
        Edge<dType, T2>& operator=(const Edge<dType, T2>& edge) = delete;

    };
}

#endif // __NEAT_EDGE_HPP__
