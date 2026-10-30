This project includes a Graph class, BetterPriorityQueue, and Dijkstra's algorithm for finding the shortest-path cost between two nodes.

Compile and run

Build and run all three test programs:

make test

Or compile with make and run them separately:

./graph-tests
./bpq-tests
./dijkstra

Remove the compiled programs with:

make clean

Notes

The graph uses directed edges with nonnegative weights. Dijkstra returns INT_MAX when the destination cannot be reached.

The tests include the provided starter tests and additional cases for invalid inputs, priority updates, disconnected nodes, and zero-weight edges.

Sources

The interfaces and starter tests were provided by the instructor. I used OpenAI Codex to help with implementation and additional tests.