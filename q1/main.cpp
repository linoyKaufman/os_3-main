#include <iostream>
#include "Graph.hpp"
int main() {
    int n, m;
    std::cin >> n >> m;
    std::cout << "Number of vertices: " << n << ", Number of edges: " << m << std::endl;

    Graph g(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        std::cout << "Adding edge: " << u << " -> " << v << std::endl;
        g.addEdge(u, v);
    }

    g.printSCCs();

    return 0;
}
