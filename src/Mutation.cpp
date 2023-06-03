#include "../include/NEAT/Genome.hpp"
#include "../include/NEAT/Activation.hpp"
#include "../include/NEAT/GeneHistory.hpp"
#include "../include/NEAT/Helper.hpp"


namespace NEAT {


    template <typename dType, typename T2>
    void Genome<dType, T2>::mutate(GeneHistory<dType, T2>& GeneHistory, const MutationConfig<dType>& mutationConfig) {
        // TODO: Extract probabilities to a config file
        const dType mutateAddNodeProbability = mutationConfig.mutateAddNodeProbability;
        const dType mutateAddEdgeProbability = mutationConfig.mutateAddEdgeProbability;
        const dType mutateToggleEdgeProbability = mutationConfig.mutateToggleEdgeProbability;
        const dType mutateWeightProbability = mutationConfig.mutateWeightProbability;
        const dType mutateActivationFunctionProbability = mutationConfig.mutateActivationFunctionProbability;
        const dType mutateBiasProbability = mutationConfig.mutateBiasProbability;

        if (uniformDistribution<dType>(0, 1) < mutateAddNodeProbability) {
            mutateAddNode(GeneHistory);
        }
        if (uniformDistribution<dType>(0, 1) < mutateAddEdgeProbability) {
            mutateAddEdge(GeneHistory);
        }
        if (uniformDistribution<dType>(0, 1) < mutateToggleEdgeProbability) {
            mutateToggleEdge();
        }
        if (uniformDistribution<dType>(0, 1) < mutateWeightProbability) {
            mutateWeight();
        }
        if (uniformDistribution<dType>(0, 1) < mutateActivationFunctionProbability) {
            mutateActivationFunction();
        }
        if (uniformDistribution<dType>(0, 1) < mutateBiasProbability) {
            mutateBias();
        }
    }

    template <typename dType, typename T2>
    void Genome<dType, T2>::mutateAddNode(GeneHistory<dType, T2>& GeneHistory) {
        // 1. select a random edge
        Edge<dType, T2>* edge = getRandomEdge();
        if (edge == nullptr)
            return;
        // 2. disable the edge
        edge->disable();
        // 3. create a new node, layer of the new node is 1 + min layer of the two nodes
        Node<dType, T2>* fromNode = edge->getFrom(this);
        Node<dType, T2>* toNode = edge->getTo(this);
        const T2 newNodeId = GeneHistory.addNode(fromNode->getId(), toNode->getId(), edge->getInnovationNumber());
        const int newLayer = std::min(fromNode->getLayer(), toNode->getLayer()) + 1;
        const dType bias = gaussianDistribution<dType>(0, 1);
        // TODO: Check if the default activation function is random or deterministic
        Node<dType, T2>* newNode = new Node<dType, T2>(newNodeId, NodeType::HIDDEN, newLayer, bias, getActivationFunction_Factory()->sigmoid);
        // 4. create two new edges, 
        //   one from the first node to the new node with weight 1
        //   one from the new node to the second node with the same weight as the disabled edge
        const T2 innovationNumber1 = GeneHistory.addEdge(fromNode->getId(), newNodeId);
        const T2 innovationNumber2 = GeneHistory.addEdge(newNodeId, toNode->getId());
        // std::cout << "innovationNumber1: " << innovationNumber1 << std::endl;
        // std::cout << "innovationNumber2: " << innovationNumber2 << std::endl;
        Edge<dType, T2>* newEdge1 = new Edge<dType, T2>(fromNode, newNode, 1, innovationNumber1);
        Edge<dType, T2>* newEdge2 = new Edge<dType, T2>(newNode, toNode, edge->getWeight(), innovationNumber2);
        // 5. update the layer of the nodes, all nodes with layer > new node layer
        for (std::pair<const T2, Node<dType, T2>*>& nodePair : nodes) {
            Node<dType, T2>* node = nodePair.second;
            if (node->getLayer() >= newLayer) {
                node->setLayer(node->getLayer() + 1);
            }
        }
        // 6. add the new node and edges to the genome
        // nodes.insert(std::make_pair(newNodeId, newNode));
        // edges.insert(std::make_pair(innovationNumber1, newEdge1));
        // edges.insert(std::make_pair(innovationNumber2, newEdge2));
        this->addNode(newNode);
        this->addEdge(newEdge1);
        this->addEdge(newEdge2);
        fromNode->addOutgoingEdge(newEdge1);
        newNode->addIncomingEdge(newEdge1);
        newNode->addOutgoingEdge(newEdge2);
        toNode->addIncomingEdge(newEdge2);
    }

    template <typename dType, typename T2>
    void Genome<dType, T2>::mutateAddEdge(GeneHistory<dType, T2>& GeneHistory) {
        // 1. select two random distinct nodes 
        Node<dType, T2>* node1, * node2;
        node1 = getRandomNode(true, true);
        if (node1 == nullptr)
            return;
        while (true) {
            node2 = getRandomNode(true, true);
            if (node2 == nullptr)
                return;
            if (node1 != node2 && node1->getLayer() != node2->getLayer()) break;
        }
        // make sure node1 is the node with the smaller layer
        if (node1->getLayer() > node2->getLayer()) {
            Node<dType, T2>* temp = node1;
            node1 = node2;
            node2 = temp;
        }
        // 2. check if the edge already exists, if exists return
        for (const Edge<dType, T2>* edge : node1->getOutgoingEdges()) {
            if (edge->getTo(this) == node2) {
                return;
            }
        }
        // 3. add the edge to the genome
        const T2 innovationNumber = GeneHistory.addEdge(node1->getId(), node2->getId());
        const dType weight = gaussianDistribution<dType>(0, 1);
        Edge<dType, T2>* newEdge = new Edge<dType, T2>(node1, node2, weight, innovationNumber);
        node1->addOutgoingEdge(newEdge);
        node2->addIncomingEdge(newEdge);
        this->addEdge(newEdge);
    }

    template <typename dType, typename T2>
    void Genome<dType, T2>::mutateToggleEdge() {
        Edge<dType, T2>* edge = getRandomEdge();
        if (edge == nullptr) {
            return;
        }
        edge->toggle();
    }

    template <typename dType, typename T2>
    void Genome<dType, T2>::mutateWeight() {
        // TODO: extract sd to a configurable constant
        // TODO: allow small probability of assigning a random weight
        const dType sd = 0.001;
        Edge<dType, T2>* edge = getRandomEdge();
        if (edge == nullptr) {
            return;
        }
        edge->setWeight(edge->getWeight() + gaussianDistribution<dType>(0, sd));
    }

    template <typename dType, typename T2>
    void Genome<dType, T2>::mutateActivationFunction() {
        Node<dType, T2>* node = getRandomNode(false, false);
        if (node == nullptr) {
            return;
        }
        node->setActivationFunction(getActivationFunction_Factory<dType>()->getRandomActivationFunction_single());
    }

    template <typename dType, typename T2>
    void Genome<dType, T2>::mutateBias() {
        Node<dType, T2>* node = getRandomNode(false, true);
        if (node == nullptr) {
            return;
        }
        node->setBias(node->getBias() + gaussianDistribution<dType>(0, 0.001));
    }

    template <typename dType, typename T2>
    Edge<dType, T2>* Genome<dType, T2>::getRandomEdge() {
        T2 i = uniformIntDistribution<T2>(0, static_cast<T2>(edges.size() - 1));
        Edge<dType, T2>* edge = nullptr;
        for (auto const& [key, val] : edges) {
            if (i-- == 0)
                edge = val;
        }
        return edge;
    }

    template <typename dType, typename T2>
    Node<dType, T2>* Genome<dType, T2>::getRandomNode(bool allowInput, bool allowOutput) {
        if (!allowInput && !allowOutput && static_cast<T2>(nodes.size()) == inputSize + outputSize) {
            return nullptr;
        }

        while (true) {
            T2 i = uniformIntDistribution<T2>(0, static_cast<T2>(nodes.size() - 1));
            Node<dType, T2>* node = nullptr;
            for (auto const& [key, val] : nodes) {
                if (i-- == 0)
                    node = val;
            }
            if (allowInput && node->getType() == NodeType::INPUT) {
                return node;
            }
            if (allowOutput && node->getType() == NodeType::OUTPUT) {
                return node;
            }
            if (node->getType() == NodeType::HIDDEN) {
                return node;
            }
        }
    }

    // Explicit instantiation
    template class Genome<double, int>;
    template class Genome<double, long>;
}
