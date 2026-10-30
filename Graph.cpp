// Assistance: ChatGPT
#include "Graph.h"

Graph::Graph() {
    // The vectors start empty automatically.
}

Graph::Graph(const Graph &other) {
    nodes = other.nodes;

    // Each graph needs its own edges, otherwise both destructors would delete them.
    for (size_t i = 0; i < other.edges.size(); i++) {
        AddEdge(other.edges[i]->from, other.edges[i]->to, other.edges[i]->weight);
    }
}

Graph &Graph::operator=(const Graph &other) {
    // Assigning a graph to itself should leave it alone.
    if (this == &other) {
        return *this;
    }

    // Delete the old edges before replacing the graph's contents.
    for (size_t i = 0; i < edges.size(); i++) {
        delete edges[i];
    }
    edges.clear();
    nodes = other.nodes;

    for (size_t i = 0; i < other.edges.size(); i++) {
        AddEdge(other.edges[i]->from, other.edges[i]->to, other.edges[i]->weight);
    }
    return *this;
}

Graph::~Graph() {
    // A vector of pointers does not delete the objects those pointers point to.
    for (size_t i = 0; i < edges.size(); i++) {
        delete edges[i];
    }
}

void Graph::AddNode(nodekey_t key) {
    if (key == INVALID_NODE_KEY || IsPresent(key)) {
        throw invalid_argument("Invalid or duplicate node key");
    }
    nodes.push_back(key);
}
const GraphEdge* Graph::AddEdge(nodekey_t fromNodeKey, nodekey_t toNodeKey, unsigned int weight) {
    if (!IsPresent(fromNodeKey) || !IsPresent(toNodeKey)) {
        throw invalid_argument("Both endpoints must exist");
    }
    for (size_t i = 0; i < edges.size(); i++) {
        if (edges[i]->from == fromNodeKey && edges[i]->to == toNodeKey) {
            throw invalid_argument("Duplicate directed edge");
        }
    }

    // Allocate on the heap so the edge still exists after AddEdge returns.
    GraphEdge *edge = new GraphEdge;
    edge->from = fromNodeKey;
    edge->to = toNodeKey;
    edge->weight = weight;
    edges.push_back(edge);
    return edge;
}
bool Graph::IsPresent(nodekey_t key) const {
    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i] == key) {
            return true;
        }
    }
    return false;
}
string Graph::NodesToString() const {
    string result = "[";
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (i != 0) {
            result += ", ";
        }
        result += "(" + to_string(nodes[i]) + ")";
    }
    return result + "]";
}
string Graph::EdgesToString() const {
    string result = "[";
    for (size_t i = 0; i < edges.size(); ++i) {
        if (i != 0) {
            result += ", ";
        }
        const GraphEdge *edge = edges[i];
        result += "((" + to_string(edge->from) + ")->(" + to_string(edge->to)
                  + ") w:" + to_string(edge->weight) + ")";
    }
    return result + "]";
}
set<const GraphEdge*> Graph::GetOutwardEdgesFrom(nodekey_t nodeKey) const {
    if (!IsPresent(nodeKey)) {
        throw invalid_argument("Node does not exist");
    }
    set<const GraphEdge*> result;
    // Only include edges leaving this node, not edges arriving at it.
    for (size_t i = 0; i < edges.size(); i++) {
        if (edges[i]->from == nodeKey) {
            result.insert(edges[i]);
        }
    }
    return result;
}
set<nodekey_t> Graph::GetNodes() const {
    set<nodekey_t> result;
    for (size_t i = 0; i < nodes.size(); i++) {
        result.insert(nodes[i]);
    }
    return result;
}
size_t Graph::Size() const {
    return edges.size();
}
size_t Graph::Order() const {
    return nodes.size();
}
