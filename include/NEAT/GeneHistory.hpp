#ifndef __NEAT_GENE_HISTORY_HPP__
#define __NEAT_GENE_HISTORY_HPP__

#include <map>

#include "./Node.hpp"
#include "./Edge.hpp"


namespace NEAT {

    // forward declaration
    template <typename dType, typename T2>
    class Node;
    template <typename dType, typename T2>
    class Edge;

    /**
     * @brief Class for mutation history, innovation number of the current generation
     *
     * @tparam dType
     * @tparam T2
     */
    template <typename dType, typename T2>
    class GeneHistory final {
    public:
        GeneHistory() { };
        void init(T2 inputSize, T2 outputSize) {
            // add input nodes
            for (T2 i = 0; i < inputSize; i++) {
                nodes[i] = { i };
            }
            // add output nodes
            for (T2 i = 0; i < outputSize; i++) {
                nodes[i + inputSize] = { i + inputSize };
            }
            // add edges
            for (T2 i = 0; i < inputSize; i++) {
                for (T2 j = 0; j < outputSize; j++) {
                    edges[{ i, j + inputSize }] = { i * outputSize + j };
                }
            }
            // set innovation number
            edgeInnovationNumber = inputSize * outputSize;
            nodeInnovationNumber = inputSize + outputSize;
        }
        T2 addNode(const T2 fromId, const T2 toId, const T2 edgeInnovationNumber) {
            // find if the node already exists
            typename std::map<T2, NodeHistory>::iterator it = nodes.find(edgeInnovationNumber);
            if (it != nodes.end()) {
                // if the node already exists, return the node id
                return it->second.nodeId;
            }
            // if the node does not exist, create a new node
            T2 nodeId = getNextNodeInnovationNumber();
            nodes[edgeInnovationNumber] = { nodeId };
            return nodeId;
        }
        T2 addEdge(const T2 fromId, const T2 toId) {
            // find if the edge already exists
            typename std::map<std::pair<T2, T2>, EdgeHistory>::iterator it = edges.find({ fromId, toId });
            if (it != edges.end()) {
                // if the edge already exists, return the edge id
                return it->second.edgeInnovationNumber;
            }
            // if the edge does not exist, create a new edge
            T2 edgeId = getNextEdgeInnovationNumber();
            edges[{ fromId, toId }] = { edgeId };
            return edgeId;
        }

    private:

        struct EdgeHistory {
            T2 edgeInnovationNumber;
        };

        struct NodeHistory {
            T2 nodeId;
        };

        T2 getNextEdgeInnovationNumber() const {
            return edgeInnovationNumber++;
        }
        T2 getNextNodeInnovationNumber() const {
            return nodeInnovationNumber++;
        }
        static T2 edgeInnovationNumber;
        static T2 nodeInnovationNumber;
        // edgeInnovationNumber, NodeHistory
        std::map< T2, NodeHistory > nodes;
        // fromId, toId, EdgeHistory
        std::map< std::pair<T2, T2>, EdgeHistory > edges;
    };

    // Explicit instantiation
    template <typename dType, typename T2>
    T2 GeneHistory<dType, T2>::edgeInnovationNumber = 0;
    template <typename dType, typename T2>
    T2 GeneHistory<dType, T2>::nodeInnovationNumber = 0;

}

#endif // __NEAT_GENE_HISTORY_HPP__
