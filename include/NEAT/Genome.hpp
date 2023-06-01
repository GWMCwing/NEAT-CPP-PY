#ifndef __NEAT_GENOME_HPP__
#define __NEAT_GENOME_HPP__

// Inherit this class to create player

#include <map>
#include "./Node.hpp"
#include "./Edge.hpp"
#include "./GeneHistory.hpp"

namespace NEAT {
    // Forward declaration
    template <typename dType, typename T2>
    class Node;
    template <typename dType, typename T2>
    class Edge;
    template <typename dType, typename T2>
    class GeneHistory;

    /**
     * @brief Class for Genome storage, prediction and handling
     *
     * @tparam dType type of data
     * @tparam T2 type of innovation number
     */
    template <typename dType = double, typename T2 = int>
    class Genome final {
    public:
        /**
         * @brief Construct a new empty Genome object
         *
         */
        Genome();
        /**
         * @brief Construct a new Genome object base on input and output size, ONLY for initialisation of the first population
         *
         * @param inputSize input size of genome
         * @param outputSize output size of genome
         * @param geneHistory gene history of genome
         * @param init initialise genome with edges and nodes
         */
        Genome(T2 inputSize, T2 outputSize, bool init = true);
        virtual ~Genome();

        /**
         * @brief Get the Input Size object
         *
         * @return T2 input size
         */
        const T2& getInputSize() const;

        /**
         * @brief Get the Output Size object
         *
         * @return T2 output size
         */
        const T2& getOutputSize() const;

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

        /**
         * @brief Add a edge to the genome by cloning
         *
         * @param edge edge to add node
         * @return true add success
         * @return false add fail
         */
        bool addCloneEdge(const Edge<dType, T2>* edge);
        /**
         * @brief Add a node to the genome by cloning
         *
         * @param node node to add node
         * @return true add success
         * @return false add fail
         */
        bool addCloneNode(const Node<dType, T2>* node);

        /**
         * @brief add a node to the genome without cloning
         *
         * @param node node to add node
         * @return true add success
         */
        bool addNode_noClone(Node<dType, T2>* node);

        // 
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

        /**
         * @brief Get the Max Innovation Number of edges
         *
         * @return T2 max innovation number
         */
        T2 getMaxInnovationNumber() const;

        /**
         * @brief Get the Number Of Genes of genome
         *
         * @return T2 number of genes
         */
        T2 getNumberOfGenes() const;

        /**
         * @brief set the Fitness of genome
         *
         */
        void setFitness(dType fitness);

        /**
         * @brief Get the Fitness of genome
         *
         * @return dType fitness
         */
        const dType& getFitness() const;

        /**
         * @brief Mutate the genome
         *
         */
        void mutate(GeneHistory<dType, T2>& geneHistory);

        /**
         * @brief get the prediction from the genome
         *
         * @param inputs input vector
         * @param outputs output vector
         */
        void feedForward(const std::vector<dType>& inputs, std::vector<dType>& outputs);

        /**
         * @brief get the prediction from the genome
         *
         * @param inputs input vector
         * @return T2 prediction class
         */
        T2 predict(const std::vector<dType>& inputs);

        /**
         * @brief clone a genome with the same nodes, edges, and fitness
         *
         * @return Genome<dType, T2>* cloned genome
         */
        Genome<dType, T2>* clone() const;

        /**
         * @brief print the genome
         *
         */
        void print(int tabSize = 0) const;
        // 
    private:

        /**
         * @brief Mutate the genome by adding a node
         *
         * @param geneHistory gene history of current population
         */
        void mutateAddNode(GeneHistory<dType, T2>& geneHistory);

        /**
         * @brief Mutate the genome by adding an edge
         *
         * @param geneHistory gene history of current population
         */
        void mutateAddEdge(GeneHistory<dType, T2>& geneHistory);

        /**
         * @brief Mutate the genome by toggling an edge
         *
         */
        void mutateToggleEdge();

        /**
         * @brief Mutate the genome by changing the weight of an edge
         *
         */
        void mutateWeight();

        /**
         * @brief Mutate the genome by changing the activation function of a node
         *
         */
        void mutateActivationFunction();

        /**
         * @brief Mutate the genome by changing the bias of a node
         *
         */
        void mutateBias();

        /**
         * @brief Mutate the genome by changing the bias of a node
         *
         */
        Edge<dType, T2>* getRandomEdge();

        /**
         * @brief Get a random node from the genome
         *
         * @return Node<dType, T2>* random node pointer, nullptr unable to satisfy condition
         */
        Node<dType, T2>* getRandomNode(bool allowInput = false, bool allowOutput = false);

        /**
         * @brief Add a node to the genome
         *
         * @param node node to add
         * @return true if node is added, false otherwise
         */
        bool addNode(Node<dType, T2>* node);
        /**
         * @brief Add an edge to the genome
         *
         * @param edge edge to add
         * @return true if edge is added, false otherwise
         */
        bool addEdge(Edge<dType, T2>* edge);
        /**
         * @brief Add a vector of nodes to the genome
         *
         * @param edges
         * @return std::vector<bool> vector of bools indicating if the node is added
         */
        std::vector<bool> addEdge(std::vector<Edge<dType, T2>* > edges);
        // input size
        T2 inputSize;
        // output size
        T2 outputSize;
        // Map of nodes, key is node id
        std::map<T2, Node<dType, T2>*> nodes;
        // Map of edges, key is innovation number
        std::map<T2, Edge<dType, T2>*> edges;
        // Fitness of genome
        dType fitness = 0;
    };
}


#endif // __NEAT_GENOME_HPP__
