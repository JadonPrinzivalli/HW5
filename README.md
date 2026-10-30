# CPS-222 Assignment 5

This project implements a directed weighted Graph, BetterPriorityQueue, and Dijkstra's shortest-path algorithm. It uses C++11 and the standard library only.

## Compile and run

Open this folder in VS Code and use its terminal:

```sh
make
make test
```

`make` builds three separate programs. Run them individually with:

```sh
./graph-tests
./bpq-tests
./dijkstra
```

Use `make clean` to remove the programs. The Makefile uses g++ with -Wall, -Wextra, and -g.

## Files

- Graph.h / Graph.cpp: graph interface and implementation.
- BetterPriorityQueue.h / BetterPriorityQueue.cpp: instructor's BPQNode struct and an extended standard min-priority queue.
- Dijkstra.h / Dijkstra.cpp: shortest-path cost function.
- GraphTests.cpp / BPQTests.cpp / DijkstraTests.cpp: supplied starter tests plus additional tests.
- Makefile: builds and runs the three test programs.

## Choices and assumptions

Graph stores node keys and edge pointers in vectors. Debug strings keep insertion order. GetNodes returns a set of key values; order is not important and keys must be unique. GetOutwardEdgesFrom returns pointers to graph-owned edges leaving the requested node. Callers must not delete those edges. The destructor deletes them; copying a graph creates separate edges to avoid double deletion.

Duplicate keys, INVALID_NODE_KEY, missing edge endpoints, and duplicate directed endpoint pairs throw invalid_argument. Node 0 is valid and is AddNode's default. Reverse edges and self-loops are allowed. An existing node with no outgoing edges returns an empty set; requesting outgoing edges for a missing node throws.

Contains matches graph keys. Update accepts only strictly smaller priorities and moves the changed item up the heap until each parent has a priority no larger than its children. ToString shows heap storage order, which need not be fully sorted.

Dijkstra returns the shortest total cost, not a path listing. Edge weights are unsigned and must represent nonnegative costs; negative weights are not supported. INT_MAX represents an unreachable destination. Because both the result and BPQ priority are int, costs at least INT_MAX also use that sentinel. The code checks before adding to avoid overflow. Missing endpoints or a null graph throw invalid_argument. An existing start equal to end returns 0.

The visited field is preserved from the supplied struct but is not needed: popped nodes leave the queue and cannot be updated. This implementation uses simple linear searches, so its Dijkstra bound is O(V*V + V*E), as explained above the function, rather than the faster indexed-heap/adjacency-list bound.

Additional tests cover node/edge counts, invalid inputs, direction, self-loops, copying, empty queues, rejected priority increases, repeated decreases, disconnected paths, zero-weight edges, large weights, and the assignment's six-node example (cost 20).

## Sources and assistance

Interfaces, BPQNode, starter tests, and requirements come from the instructor's supplied Assignment 5 materials. Implementation and additional tests were prepared with OpenAI Codex assistance, acknowledged in source comments. Follow the course's assistance policy and understand the code you submit.

## Verification performed

All three full test programs and the retained starter-test sections passed. Builds used -Wall and -Wextra with no warnings. AddressSanitizer and UndefinedBehaviorSanitizer reported no errors in these runs. Separate verification compared 6,400 path queries against an independent all-pairs algorithm and checked heap validity through 2,000 queue updates; these also passed. The temporary verification programs are not part of this submission. This is not a guarantee about unseen instructor tests or a separate Valgrind leak check.

The simple raw-pointer implementation assumes memory allocations succeed; it does not attempt recovery if memory runs out while inserting or copying edges.
