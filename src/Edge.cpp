#include <iostream>
#include "../include/NEAT/Edge.hpp"
#include "../include/NEAT/Genome.hpp"
#include "../include/NEAT/Node.hpp"
#include "../include/NEAT/Helper.hpp"

namespace NEAT {
    // forward declaration
    template <typename dType, typename T2>
    class Genome;
    template <typename dType, typename T2>
    class Node;

    template <typename dType, typename T2>
    Edge<dType, T2>::Edge(Node<dType, T2>* from, Node<dType, T2>* to, dType weight, T2 innovationNumber, bool disabled) :INNOVATION_NUMBER(innovationNumber),
        from(from), to(to), weight(weight), disabled(disabled), state(EdgeState::BOTH_ENABLED) {
        this->from_id = from->getId();
        this->to_id = to->getId();
    }

    template <typename dType, typename T2>
    Edge<dType, T2>::Edge(T2 from_id, T2 to_id, dType weight, T2 innovationNumber, bool disabled) : INNOVATION_NUMBER(innovationNumber),
        from_id(from_id), to_id(to_id), weight(weight), disabled(disabled), state(EdgeState::ID_ENABLED) { }

    template <typename dType, typename T2>
    Edge<dType, T2>::~Edge() {
        // std::cout << "Edge destructor called: " << INNOVATION_NUMBER << std::endl;
    }

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
    const dType& Edge<dType, T2>::getWeight() const {
        return this->weight;
    }

    template <typename dType, typename T2>
    void Edge<dType, T2>::setWeight(dType weight) {
        this->weight = weight;
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

    template <typename dType, typename T2>
    const T2& Edge<dType, T2>::getInnovationNumber() const {
        return this->INNOVATION_NUMBER;
    }

    template <typename dType, typename T2>
    Node<dType, T2>* Edge<dType, T2>::getFrom(const Genome<dType, T2>* genome) const {
        if (this->state == EdgeState::ID_ENABLED || genome != nullptr) {
            if (genome == nullptr) {
                std::cout << "Genome is nullptr" << std::endl;
                return nullptr;
            }
            return genome->getNode(this->from_id);
        }
        return this->from;
    }

    template <typename dType, typename T2>
    Node<dType, T2>* Edge<dType, T2>::getTo(const Genome<dType, T2>* genome) const {
        if (this->state == EdgeState::ID_ENABLED || genome != nullptr) {
            if (genome == nullptr) {
                std::cout << "Genome is nullptr" << std::endl;
                return nullptr;
            }
            return genome->getNode(this->to_id);
        }
        return this->to;
    }

    template <typename dType, typename T2>
    Edge<dType, T2>* Edge<dType, T2>::clone() const {
        return new Edge<dType, T2>(this->from_id, this->to_id, this->weight, INNOVATION_NUMBER, this->disabled);
    }

    template <typename dType, typename T2>
    void Edge<dType, T2>::print(int tabSize) const {
        coutTab(tabSize);
        std::cout << "Edge: " << this->INNOVATION_NUMBER << " from: " << this->from_id << " to: " << this->to_id << " weight: " << this->weight << " disabled: " << (this->disabled ? "True" : "False") << std::endl;
    }

    // Explicitly instantiate
    template class Edge<double, int>;
    template class Edge<double, long>;
}
