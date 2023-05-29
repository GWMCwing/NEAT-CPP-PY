#include "../include/NEAT/Edge.hpp"


namespace NEAT {
    template <typename dType, typename T2>
    Edge<dType, T2>::Edge(Node<dType, T2>* from, Node<dType, T2>* to, dType weight, T2 innovationNumber) :
        from(from), to(to), weight(weight), INNOVATION_NUMBER(innovationNumber), state(EdgeState::POINTER_ENABLED) { }

    template <typename dType, typename T2>
    Edge<dType, T2>::Edge(T2 from_id, T2 to_id, dType weight, T2 innovationNumber) :
        from_id(from_id), to_id(to_id), weight(weight), INNOVATION_NUMBER(innovationNumber), state(EdgeState::ID_ENABLED) { }


    template <typename dType, typename T2>
    void Edge<dType, T2>::disable() {
        this->disabled = true;
    }

    template <typename dType, typename T2>
    void Edge<dType, T2>::enable() {
        this->disabled = false;
    }

    template <typename dType, typename T2>
    void Edge<dType, T2>::toggle() {
        this->disabled = !this->disabled;
    }

    template <typename dType, typename T2>
    void Edge<dType, T2>::updateFromTo(Node<dType, T2>* from, Node<dType, T2>* to) {
        this->from = from;
        this->to = to;
        this->state = (this->state == EdgeState::ID_ENABLED) ? EdgeState::BOTH_ENABLED : EdgeState::POINTER_ENABLED;
    }

    template <typename dType, typename T2>
    void Edge<dType, T2>::updateFromTo(T2 from_id, T2 to_id) {
        this->from_id = from_id;
        this->to_id = to_id;
        this->state = (this->state == EdgeState::POINTER_ENABLED) ? EdgeState::BOTH_ENABLED : EdgeState::ID_ENABLED;
    }

    template <typename dType, typename T2>
    const EdgeState& Edge<dType, T2>::getState() const {
        return this->state;
    }

    // Explicitly instantiate
    template class Edge<float, int>;
    template class Edge<double, int>;
    template class Edge<float, long>;
    template class Edge<double, long>;
}
