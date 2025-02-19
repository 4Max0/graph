#include "graph.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>

struct Node** node_list = NULL;
int node_count = 0;

struct Node*** follow_node_list = NULL;
int follow_node_count = 0;

struct Edge** edge_list = NULL;
int edge_count = 0;

// Create -------------------------------------------------------------------------------------------------------------------------------------------

struct Node* create_node(char* label) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 

    new_node->label = label;
    node_list = (struct Node**) realloc(node_list, (node_count + 1) * sizeof(struct Node*));
    node_list[node_count] = new_node;
    node_count++;

    return new_node;
}

struct Node** create_follow_nodes(int num, ...) {
    struct Node** node_array = (struct Node**) malloc(num * sizeof(struct Node*));
    va_list args;
    va_start(args, num);

    for (int i = 0; i < num; i++) {
        node_array[i] = va_arg(args, struct Node*);
    }
    va_end(args);

    follow_node_list = (struct Node***) realloc(follow_node_list, (follow_node_count + 1) * sizeof(struct Node**));
    follow_node_list[follow_node_count] = node_array;
    follow_node_count++;

    return node_array;

}

struct Edge* create_edge(struct Node* node, struct Node** follow_nodes, int follow_nodes_len) {

    struct Edge* new_edge = (struct Edge*) malloc(sizeof(struct Edge));

    new_edge->node = node;
    new_edge->follow_nodes = follow_nodes;
    new_edge->follow_nodes_len = follow_nodes_len;

    edge_list = (struct Edge**) realloc(edge_list, (edge_count + 1) * sizeof(struct Edge*));
    edge_list[edge_count] = new_edge;
    edge_count++;

    return new_edge;
}

struct Graph* create_graph(int num, ...) {

    struct Graph* new_graph = (struct Graph*) malloc(sizeof(struct Graph));
    struct Edge** new_graph_edges = (struct Edge**) malloc(num  * sizeof(struct Edge*));

    va_list args;
    va_start(args, num);

    for (int i = 0; i < num; i++) {
        new_graph_edges[i] = va_arg(args, struct Edge*);
    }
    va_end(args);

    new_graph->edges = new_graph_edges;
    new_graph->edge_count = num;
    
    return new_graph;
}

// DFS ----------------------------------------------------------------------------------------------------------------------------------------------

struct Traversal* dfs_search(struct Graph* graph, struct Node* start_node, struct Node* target_node) {
    
    struct Traversal* result = (struct Traversal*) malloc(sizeof(struct Traversal));
    if (result == NULL) {
        perror("Failed to allocate memory for Traversal");
        exit(EXIT_FAILURE);
    }

    result->traversal = (struct Node**) malloc(sizeof(struct Node*));
    if (result->traversal == NULL) {
        perror("Failed to allocate memory for traversal array");
        free(result);
        exit(EXIT_FAILURE);
    }

    result->length = 0;
    result->traversal[result->length] = start_node;
    result->length++;

    if (dfs_traversal(graph, &result->traversal, &result->length, start_node, target_node)) {
        return result;
    } else {
        free(result->traversal);
        free(result);
        return NULL;
    }
}


bool dfs_traversal(struct Graph* graph, struct Node*** traversal_ptr, int* length, struct Node* current_node, struct Node* target_node) {
    struct Node** traversal = *traversal_ptr;

    if (current_node == target_node) {
        *traversal_ptr = traversal;
        return true;
    }

    for (int i = 0; i < graph->edge_count; i++) {
        if (graph->edges[i]->node == current_node) {
            for (int j = 0; j < graph->edges[i]->follow_nodes_len; j++) {
                struct Node* next_node = graph->edges[i]->follow_nodes[j];
                bool already_visited = false;

                for (int k = 0; k < *length; k++) {
                    if (traversal[k] == next_node) {
                        already_visited = true;
                        break;
                    }
                }

                if (!already_visited) {
                    struct Node** new_traversal = (struct Node**) realloc(traversal, (*length + 1) * sizeof(struct Node*));
                    if (new_traversal == NULL) {
                        perror("Failed to reallocate memory for traversal");
                        exit(EXIT_FAILURE);
                    }
                    traversal = new_traversal;
                    traversal[*length] = next_node;
                    (*length)++;

                    if (dfs_traversal(graph, &traversal, length, next_node, target_node)) {
                        *traversal_ptr = traversal;
                        return true;
                    }

                    (*length)--;
                }
            }
        }
    }

    *traversal_ptr = traversal;
    return false;
}

// BFS ----------------------------------------------------------------------------------------------------------------------------------------------

struct Traversal* bfs_search(struct Graph* graph, struct Node* start_node, struct Node* target_node) {
    return NULL;
}

// Traversal ----------------------------------------------------------------------------------------------------------------------------------------

void show_traversal(struct Traversal* traversal) {

    for (int i = 0; i < traversal->length; i++) {
        printf("%s", traversal->traversal[i]->label);

        if (i < traversal->length -1) {
            printf(" -> ");
        }

    }

    printf("\n");

}

// FREE ---------------------------------------------------------------------------------------------------------------------------------------------

void free_nodes() {

    for (int i = 0; i < node_count; i++ ) {
        free(node_list[i]);
        node_list[i] = NULL;

    }
    free(node_list);
    node_list = NULL;
    node_count = 0;

}

void free_follow_nodes() {
    
    for (int i = 0; i < follow_node_count; i++) {
        free(follow_node_list[i]);
        follow_node_list[i] = NULL;
    }

    free(follow_node_list);
    follow_node_list = NULL;
    follow_node_count = 0;
}

void free_edges() {

    for (int i = 0; i < edge_count; i++  ) {

        
        free(edge_list[i]);
        edge_list[i] = NULL;
    }

    free(edge_list);
    edge_list = NULL;
    edge_count = 0;

}

void free_graph(struct Graph* graph) {

    free(graph->edges);
    free(graph);
}

void free_traversal(struct Traversal* traversal) {
    free(traversal->traversal);
    free(traversal);
}