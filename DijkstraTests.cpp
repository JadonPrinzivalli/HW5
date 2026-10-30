
#include "Graph.h"
#include "BetterPriorityQueue.h"
#include "Dijkstra.h"

#include <iostream>
#include <cassert>

using namespace std;


int DijkstraTest(){
	cout << "Testing Dijkstra Algorithm..." << endl;
	
	// Test 1: graph from assignment
	Graph *g = new Graph();
	
	g->AddNode(1);
	g->AddNode(2);
	g->AddNode(3);
	
	g->AddEdge(1, 2, 7);
	g->AddEdge(2, 1, 7);
	g->AddEdge(1, 3, 9);
	g->AddEdge(3, 1, 9);

	
	cout <<  "---Graph---" << endl;
	cout << "\tnodes: " << g->NodesToString() << endl;
	cout << "\tedges: " << g->EdgesToString() << endl;
	cout << "---Graph---" << endl << endl;

	nodekey_t start = 1;
	nodekey_t end = 3;

	cout << "start: " << to_string(start) << "  goal: " << to_string(end) << endl;
	
	int ans = dijkstra(start, end, g);
	cout << "Output from Dijkstra(" << to_string(start) << ", " << to_string(end) << ") => " << ans << endl;
	assert(ans == 9);

	delete g;
	
	cout << "DONE with basic testing of Dijkstra algorithm" << endl;
	
	return ans;
}



// Additional tests written with ChatGPT assistance.
void ExtraDijkstraTests() {
    Graph g;
    for (nodekey_t i = 1; i <= 7; ++i) g.AddNode(i);
    // Full six-node example from the assignment; node 7 is disconnected.
    const unsigned int links[][3] = {
        {1,2,7}, {1,3,9}, {1,6,14}, {2,3,10}, {2,4,15},
        {3,4,11}, {3,6,2}, {4,5,6}, {5,6,9}
    };
    for (const auto &link : links) {
        g.AddEdge(link[0], link[1], link[2]);
        g.AddEdge(link[1], link[0], link[2]);
    }
    assert(dijkstra(1, 5, &g) == 20);
    assert(dijkstra(5, 1, &g) == 20);
    assert(dijkstra(1, 7, &g) == INT_MAX);
    assert(dijkstra(7, 7, &g) == 0);
    Graph directed;
    for (nodekey_t i = 0; i < 4; ++i) directed.AddNode(i);
    directed.AddEdge(0, 1, 9); directed.AddEdge(0, 2, 0);
    directed.AddEdge(2, 1, 2); directed.AddEdge(1, 3, 0);
    directed.AddEdge(1, 1, 0);
    assert(dijkstra(0, 3, &directed) == 2);
    assert(dijkstra(3, 0, &directed) == INT_MAX);
    try { dijkstra(0, 3, nullptr); assert(false); } catch (const invalid_argument&) {}
    try { dijkstra(8, 3, &directed); assert(false); } catch (const invalid_argument&) {}
    try { dijkstra(0, 8, &directed); assert(false); } catch (const invalid_argument&) {}
    Graph big;
    for (nodekey_t i = 0; i < 4; ++i) big.AddNode(i);
    big.AddEdge(0, 1, INT_MAX - 1); big.AddEdge(1, 2, 10);
    big.AddEdge(0, 2, 20); big.AddEdge(0, 3, UINT_MAX);
    assert(dijkstra(0, 1, &big) == INT_MAX - 1);
    assert(dijkstra(0, 2, &big) == 20);
    assert(dijkstra(0, 3, &big) == INT_MAX);
    Graph empty;
    try { dijkstra(0, 0, &empty); assert(false); } catch (const invalid_argument&) {}
}

int main(){
    ExtraDijkstraTests();
	
	DijkstraTest(); // this one by itself tests the graph on the assignment
	cout << endl;
	cout << "ALL TESTS PASSED!" << endl;

	return 0;
}
