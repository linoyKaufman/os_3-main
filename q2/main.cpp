#include "graph.hpp"
#include <iostream>

#ifdef USE_DEQUE
#include "deque_graph.cpp"
#define SelectedGraph DequeGraph
#elif defined(USE_LIST)
#include "list_graph.cpp"
#define SelectedGraph ListGraph
#endif

int main() {
    int n, m;
    std::cin >> n >> m;

    // עכשיו Graph* graph = new SelectedGraph(n) יעבוד
    Graph* graph = new SelectedGraph(n);  // נבחרה המחלקה המתאימה

    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        graph->addEdge(u, v);
    }

    graph->runKosaraju();
    delete graph;

    return 0;
}
