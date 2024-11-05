#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Create a node in the adjacency list
Node* createNode(int vertex, int weight) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Initialize the graph with a given number of vertices
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Add edge between source and destination with a given weight
void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Since it's an undirected graph, add an edge from dest to src
    newNode = createNode(src, weight);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Create a queue for BFS
Queue* createQueue(int capacity) {
    Queue* queue = malloc(sizeof(Queue));
    queue->items = malloc(capacity * sizeof(int));
    queue->front = queue->rear = queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

// Queue utility functions
int isQueueEmpty(Queue* queue) {
    return queue->size == 0;
}

void enqueue(Queue* queue, int value) {
    queue->items[queue->rear++] = value;
    queue->size++;
}

int dequeue(Queue* queue) {
    queue->size--;
    return queue->items[queue->front++];
}

// Reset the visited array
void resetVisited(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
}

// BFS traversal from a starting vertex
void bfs(Graph* graph, int startVertex) {
    Queue* queue = createQueue(graph->numVertices);
    graph->visited[startVertex] = 1;
    enqueue(queue, startVertex);

    printf("BFS Traversal starting from vertex %d:\n", startVertex);
    while (!isQueueEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = 1;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// DFS traversal from a starting vertex
void dfs(Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!graph->visited[adjVertex]) {
            dfs(graph, adjVertex);
        }
        temp = temp->next;
    }
}

// Dijkstra's shortest path algorithm
void dijkstra(Graph* graph, int startVertex) {
    int distances[graph->numVertices];
    int visited[graph->numVertices];

    // Initialize distances and visited arrays
    for (int i = 0; i < graph->numVertices; i++) {
        distances[i] = INT_MAX;
        visited[i] = 0;
    }
    distances[startVertex] = 0;

    for (int i = 0; i < graph->numVertices - 1; i++) {
        int minDistance = INT_MAX, minVertex = -1;

        // Find the vertex with the minimum distance that hasn't been visited
        for (int j = 0; j < graph->numVertices; j++) {
            if (!visited[j] && distances[j] < minDistance) {
                minDistance = distances[j];
                minVertex = j;
            }
        }

        visited[minVertex] = 1;

        // Update the distances of the adjacent vertices of minVertex
        Node* temp = graph->adjLists[minVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            int weight = temp->weight;
            if (!visited[adjVertex] && distances[minVertex] != INT_MAX &&
                distances[minVertex] + weight < distances[adjVertex]) {
                distances[adjVertex] = distances[minVertex] + weight;
            }
            temp = temp->next;
        }
    }

    printf("Vertex\tDistance from %d\n", startVertex);
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d\t%d\n", i, distances[i]);
    }
}

// Helper function for cycle detection using DFS
int detectCycleDFS(Graph* graph, int vertex, int parent) {
    graph->visited[vertex] = 1;

    Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!graph->visited[adjVertex]) {
            if (detectCycleDFS(graph, adjVertex, vertex)) {
                return 1;
            }
        } else if (adjVertex != parent) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

// Detect if the graph contains a cycle
int hasCycle(Graph* graph) {
    resetVisited(graph);
    for (int i = 0; i < graph->numVertices; i++) {
        if (!graph->visited[i]) {
            if (detectCycleDFS(graph, i, -1)) {
                return 1;
            }
        }
    }
    return 0;
}
