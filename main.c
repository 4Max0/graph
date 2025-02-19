#include "src/graph.h"

#include <stdio.h>


int main() {

    // create Nodes
    struct Node* node1 = create_node("Frankfurt\0"); 
    struct Node* node2 = create_node("Mannheim\0"); 
    struct Node* node3 = create_node("Wuerzburg\0"); 
    struct Node* node4 = create_node("Kassel\0");
    struct Node* node5 = create_node("Karlsruhe\0");
    struct Node* node6 = create_node("Augsburg\0");
    struct Node* node7 = create_node("Erfurt\0");
    struct Node* node8 = create_node("Nuernberg\0");
    struct Node* node9 = create_node("Stuttgart\0");
    struct Node* node10 = create_node("Muenchen\0");

    // create an array of nodes we connect to
    struct Node** follow_nodes1 = create_follow_nodes(3, node2, node3, node4);
    struct Node** follow_nodes2 = create_follow_nodes(2, node1, node5);
    struct Node** follow_nodes3 = create_follow_nodes(3, node1, node7, node8);
    struct Node** follow_nodes4 = create_follow_nodes(2, node1, node10);
    struct Node** follow_nodes5 = create_follow_nodes(2, node2, node6);
    struct Node** follow_nodes6 = create_follow_nodes(2, node5, node10);
    struct Node** follow_nodes7 = create_follow_nodes(1, node3);
    struct Node** follow_nodes8 = create_follow_nodes(3, node3, node9, node10);
    struct Node** follow_nodes9 = create_follow_nodes(1, node8);
    struct Node** follow_nodes10 = create_follow_nodes(3, node6, node4, node8);

    // create "edges"
    // edges are a node and it's connections to other nodes 
    struct Edge* edge1 = create_edge(node1, follow_nodes1, 3);
    struct Edge* edge2 = create_edge(node2, follow_nodes2, 2);
    struct Edge* edge3 = create_edge(node3, follow_nodes3,3);
    struct Edge* edge4 = create_edge(node4, follow_nodes4,2);
    struct Edge* edge5 = create_edge(node5, follow_nodes5, 2);
    struct Edge* edge6 = create_edge(node6, follow_nodes6, 2);
    struct Edge* edge7 = create_edge(node7, follow_nodes7, 1);
    struct Edge* edge8 = create_edge(node8, follow_nodes8, 3);
    struct Edge* edge9 = create_edge(node9, follow_nodes9, 1);
    struct Edge* edge10 = create_edge(node10, follow_nodes10, 3);

    // create graph
    // A graph is a collection of edges
    struct Graph* graph1 = create_graph(10, edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9, edge10);

    // traversal is the implementation of a traversal path (depth first search as a implemented function)
    struct Traversal* traversal1 = dfs_search(graph1, node3, node10);
    struct Traversal* traversal2 = dfs_search(graph1, node7, node5);

    // Function to show the traversal
    show_traversal(traversal1);
    show_traversal(traversal2);

    // free the used memory
    free_traversal(traversal1);
    free_traversal(traversal2);
    free_graph(graph1);
    free_nodes();
    free_follow_nodes();
    free_edges();

    return 0;
}
