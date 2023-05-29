#ifndef __NEAT_GENOME_HPP__
#define __NEAT_GENOME_HPP__

// Inherit this class to create player

#include <map>
#include "Node.hpp"

namespace NEAT {
    /**
     * @brief Class for Genome storage, prediction and handling
     *
     * @tparam dType type of data
     * @tparam T2 type of innovation number
     */
    template <typename dType = float, typename T2 = int>
    class Genome final {
    public:
        Genome();
        virtual ~Genome();
        /**
         * @brief Get the Nodes object
         *
         * @return const std::map< T2, Node<dType, T2>* >&
         */
        const std::map< T2, Node<dType, T2>* >& getNodes() const;
        /**
         * @brief Get the Edges object
         *
         * @return const std::map< T2, Edge<dType, T2>* >&
         */
        const std::map< T2, Edge<dType, T2>* >& getEdges() const;
        /**
         * @brief Get pointer to edge by innovation number
         *
         * @param innovationNumber innovation number of edge
         * @return Edge<dType, T2>* Edge pointer if found, nullptr otherwise
         */
        Edge<dType, T2>* getEdge(T2 innovationNumber) const;
        /**
         * @brief Get pointer to node by id
         *
         * @param id node id
         * @return Node<dType, T2>* Node pointer if found, nullptr otherwise
         */
        Node<dType, T2>* getNode(T2 id) const;
        // 
        /**
         * @brief Add a node to the genome
         *
         * @param node node to add
         */
        void addNode(Node<dType, T2>* node);
        /**
         * @brief Add an edge to the genome
         *
         * @param edge edge to add
         */
        void addEdge(Edge<dType, T2>* edge);
        /**
         * @brief Disable an edge from the genome
         *
         * @param innovationNumber innovation number of edge to disable
         */
        void disableEdge(T2 innovationNumber);
        /**
         * @brief Enable an edge from the genome
         *
         * @param innovationNumber innovation number of edge to enable
         */
        void enableEdge(T2 innovationNumber);
        /**
         * @brief Toggle an edge from the genome
         *
         * @param innovationNumber innovation number of edge to toggle
         */
        void toggleEdge(T2 innovationNumber);
        // 
    private:
        /**
         * @brief Map of nodes, key is node id
         *
         */
        std::map<T2, Node<dType, T2>*> nodes;
        /**
         * @brief Map of edges, key is innovation number
         *
         */
        std::map<T2, Edge<dType, T2>*> edges;
        /**
         * @brief Fitness of genome
         *
         */
        dType fitness = 0;
    };
}


#endif // __NEAT_GENOME_HPP__
