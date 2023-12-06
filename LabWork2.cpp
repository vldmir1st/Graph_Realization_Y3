#include "Graph.h"

int main() {
    Graph graph;
    graph.addNode(15);
    graph.addNode(-15);
    graph.addNode(100);
    graph.addNode(100);
    graph.addNode(0);
    graph.addNode(-15);
    graph.print();

    graph.addEdge(15, -15);
    graph.addEdge(-15, 15);
    graph.addEdge(1, 32);
    graph.addEdge(0, 100);
    graph.addEdge(15, 100);
    graph.addEdge(15, 0);
    graph.print();
}