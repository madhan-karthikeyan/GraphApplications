#ifndef GRAPH_H
#define GRAPH_H

// Node structure in adjacency list
typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

// Graph structure with an adjacency list
typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* visited;
} Graph;

// Queue for BFS
typedef struct Queue {
    int* items;
    int front, rear, size, capacity;
} Queue;

// Function prototypes
Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest, int weight);
void bfs(Graph* graph, int startVertex);
void dfs(Graph* graph, int startVertex);
void dijkstra(Graph* graph, int startVertex);
int hasCycle(Graph* graph);
void resetVisited(Graph* graph);

#endif
