#ifndef __NEAT_GENOME_HPP__
#define __NEAT_GENOME_HPP__

// Inherit this class to create player

#include <map>
#include "Node.hpp"

namespace NEAT {
    template <typename dType = float, typename T2 = int>
    class Genome final {
    public:
        virtual Genome();
        virtual ~Genome();
        // 
        const std::map<const T2, const Node<dType, T2>* const> getNodes() const;
        const std::map<const T2, const Edge<dType, T2>* const> getEdges() const;
        Edge<dType, T2>* getEdge(T2 innovationNumber) const;
        Node<dType, T2>* getNode(T2 id) const;
        // 
        void addNode(Node<dType, T2>* node);
        void addEdge(Edge<dType, T2>* edge);
        void disableEdge(T2 innovationNumber);
        void enableEdge(T2 innovationNumber);
        void toggleEdge(T2 innovationNumber);
        // 
    private:
        std::map<T2, Node<dType, T2>*> nodes;
        std::map<T2, Edge<dType, T2>*> edges;
        dType fitness = 0;
    };
}


#endif // __NEAT_GENOME_HPP__
