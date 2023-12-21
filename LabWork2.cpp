#include "Graph.h"

int main() {
    Graph graph;
    /*
    for (int i = 1; i < 6; i++)
        graph.addNode(6-i);
    //graph.print();
    
    for (int i = 1; i < 6; i++)
        for (int j = 0; j < 8; j++)
            graph.addEdge(i,8-j);
    graph.print();
    
    for (int i = 8; i > 0; i--) {
        graph.delNode(i);   
       
    }
    graph.print();

    for (int i = 1; i < 6; i++)
        graph.addNode(6 - i);
    //graph.print();

    for (int i = 1; i < 6; i++)
        for (int j = 0; j < 8; j++)
            graph.addEdge(i, 8 - j);
    graph.print();
    if (graph.searchEdge(5, 5) == true) cout << "true\n";
    else cout << "false\n";
    if (graph.searchEdge(5, 8) == true) cout << "true\n";
    else cout << "false\n";
    */   

    for (int i = 1; i <= 9; i++)
        graph.addNode(i);

    /*
    for (int i = 1; i < 9; i++)
        graph.addEdge(i,i+i );
    */

    graph.addEdge(1, 3);
    graph.addEdge(1, 6);
    graph.addEdge(3, 6);

    graph.addEdge(4, 9);
    graph.addEdge(4, 7);
    graph.addEdge(7, 9);

    graph.addEdge(2, 5);
    graph.addEdge(2, 8);
    graph.addEdge(8, 5);

    graph.addEdge(2, 7);
    graph.addEdge(3, 8);

    graph.print();
    graph.printAllMaxIndependentSets();
    graph.traverse();
    
}