// Assistance: ChatGPT
#include "Dijkstra.h"
#include "BetterPriorityQueue.h"

// With V nodes and E directed edges, time is O(V*V + V*E).
// Graph's outward-edge queries check V nodes and scan E edges, up to V times.
// Each of up to E distance updates searches a queue of up to V items.
// Heap operations and inserting outgoing edges into sets are absorbed in this
// bound for a graph without parallel edges. Auxiliary space is O(V + E).
int dijkstra(nodekey_t start, nodekey_t end, const Graph *g) {
    if (g == nullptr || !g->IsPresent(start) || !g->IsPresent(end)) {
        throw invalid_argument("Dijkstra needs a graph and existing endpoints");
    }

    BetterPriorityQueue queue;
    set<nodekey_t> nodes = g->GetNodes();
    for (nodekey_t key : nodes) {
        BPQNode node;
        node.gnode = key;
        // INT_MAX represents infinity until a route to this node is found.
        node.pri = INT_MAX;
        if (key == start) {
            node.pri = 0;
        }
        queue.push(node);
    }

    while (!queue.empty()) {
        BPQNode current = queue.top();
        queue.pop();

        // If the smallest distance is infinity, the remaining nodes are unreachable.
        if (current.pri == INT_MAX) {
            return INT_MAX;
        }
        if (current.gnode == end) {
            return current.pri;
        }

        set<const GraphEdge*> outgoing = g->GetOutwardEdgesFrom(current.gnode);
        for (const GraphEdge *edge : outgoing) {
            // The supplied priority and return types are int. Avoid overflow,
            // and reserve INT_MAX for infinity rather than a finite distance.
            if (edge->weight >= static_cast<unsigned int>(INT_MAX - current.pri)) {
                continue;
            }

            BPQNode neighbor;
            neighbor.gnode = edge->to;
            neighbor.pri = current.pri + static_cast<int>(edge->weight);
            // Update ignores worse distances and nodes already popped.
            queue.Update(neighbor);
        }
    }
    return INT_MAX;
}
