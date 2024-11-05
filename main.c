#include <stdio.h>
#include "graph.h"

// Function to display menu
void displayMenu() {
    printf("\nGraph Operations Menu:\n");
    printf("1. Add Edge\n");
    printf("2. BFS Traversal\n");
    printf("3. DFS Traversal\n");
    printf("4. Shortest Path (Dijkstra's Algorithm)\n");
    printf("5. Cycle Detection\n");
    printf("6. Exit\n");
    printf("Choose an option: ");
}

int main() {
    int vertices, choice, src, dest, weight, startVertex;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    Graph* graph = createGraph(vertices);

    while (1) {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter source, destination, and weight: ");
                scanf("%d %d %d", &src, &dest, &weight);
                addEdge(graph, src, dest, weight);
                printf("Edge added successfully!\n");
                break;

            case 2:
                printf("Enter starting vertex for BFS: ");
                scanf("%d", &startVertex);
                resetVisited(graph);
                bfs(graph, startVertex);
                break;

            case 3:
                printf("Enter starting vertex for DFS: ");
                scanf("%d", &startVertex);
                resetVisited(graph);
                dfs(graph, startVertex);
                break;

            case 4:
                printf("Enter starting vertex for Dijkstra's algorithm: ");
                scanf("%d", &startVertex);
                dijkstra(graph, startVertex);
                break;

            case 5:
                resetVisited(graph);
                if (hasCycle(graph))
                    printf("Graph contains a cycle.\n");
                else
                    printf("Graph does not contain a cycle.\n");
                break;

            case 6:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
