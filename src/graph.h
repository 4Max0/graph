#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

extern struct Node** node_list;
extern int node_count;

extern struct Node*** follow_node_list;
extern int follow_node_count;

extern struct Edge** edge_list;
extern int edge_count;

struct Node {

    char* label;

};

struct Edge {

    struct Node* node;
    struct Node** follow_nodes;
    int follow_nodes_len;

};

struct Graph {
    
    struct Edge** edges;
    int edge_count;

};

struct Traversal {

    struct Node** traversal;
    int length;

};

struct Queue {

    struct Node*** taken_paths;
    int head;
    int tail;
    int size;

};

// Add a type
struct Node* create_node(char* label);
struct Node** create_follow_nodes(int num, ...);
struct Edge* create_edge(struct Node* node, struct Node** follow_nodes, int follow_nodes_len);
struct Graph* create_graph(int num, ...);

// traversal
struct Traversal* dfs_search(struct Graph* graph, struct Node* start_node, struct Node* target_node);
bool dfs_traversal(struct Graph* graph, struct Node*** traversal_ptr, int* length, struct Node* current_node, struct Node* target_node);
struct Traversal* bfs_search(struct Graph* graph, struct Node* start_node, struct Node* target_node);
void show_traversal(struct Traversal* traversal);

// Queue
struct Queue* init_queue();
void enqueue(struct Node** path);
void dequeue();
void free_queue();

// frees
void free_nodes();
void free_follow_nodes();
void free_edges();
void free_graph(struct Graph* graph);
void free_traversal(struct Traversal* traversal);

#endif // GRAPH_H