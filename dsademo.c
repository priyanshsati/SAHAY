#include <stdio.h>
#include <limits.h>

#define MAX 10

// Structure for graph edge
struct Edge {
    int destination;
    int distance;
    int blocked;
};

// Graph
struct Edge graph[MAX][MAX];
int edgeCount[MAX];


// Add road
void addRoad(int source, int destination, int distance, int blocked) {

    graph[source][edgeCount[source]].destination = destination;
    graph[source][edgeCount[source]].distance = distance;
    graph[source][edgeCount[source]].blocked = blocked;

    edgeCount[source]++;

    // Undirected graph
    graph[destination][edgeCount[destination]].destination = source;
    graph[destination][edgeCount[destination]].distance = distance;
    graph[destination][edgeCount[destination]].blocked = blocked;

    edgeCount[destination]++;
}


// Find minimum-distance unvisited vertex
int findMinVertex(int distance[], int visited[], int vertices) {

    int minDistance = INT_MAX;
    int minVertex = -1;

    for (int i = 0; i < vertices; i++) {

        if (!visited[i] && distance[i] < minDistance) {
            minDistance = distance[i];
            minVertex = i;
        }
    }

    return minVertex;
}


// Dijkstra's Algorithm
void dijkstra(int source, int destination, int vertices) {

    int distance[MAX];
    int visited[MAX];
    int parent[MAX];

    // Initialization
    for (int i = 0; i < vertices; i++) {
        distance[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    distance[source] = 0;


    // Dijkstra
    for (int count = 0; count < vertices; count++) {

        int current =
            findMinVertex(distance, visited, vertices);

        if (current == -1)
            break;

        visited[current] = 1;


        // Check all connected roads
        for (int i = 0; i < edgeCount[current]; i++) {

            int next =
                graph[current][i].destination;

            int roadDistance =
                graph[current][i].distance;

            int blocked =
                graph[current][i].blocked;


            // Ignore blocked roads
            if (blocked)
                continue;


            if (distance[current] != INT_MAX &&
                distance[current] + roadDistance
                < distance[next]) {

                distance[next] =
                    distance[current] + roadDistance;

                parent[next] = current;
            }
        }
    }


    // No route
    if (distance[destination] == INT_MAX) {

        printf("\nNo available route found!\n");
        return;
    }


    // Construct path
    int path[MAX];
    int pathSize = 0;

    int current = destination;

    while (current != -1) {

        path[pathSize] = current;
        pathSize++;

        current = parent[current];
    }


    // Display result
    printf("\n===== SAHAY ROUTE RESULT =====\n");

    printf("Route: ");

    for (int i = pathSize - 1; i >= 0; i--) {

        printf("Location %d", path[i]);

        if (i != 0)
            printf(" -> ");
    }

    printf("\nTotal Distance: %d km\n",
           distance[destination]);
}


// Display graph
void displayGraph(int vertices) {

    printf("\n===== ROAD NETWORK =====\n");

    for (int i = 0; i < vertices; i++) {

        printf("Location %d: ", i);

        for (int j = 0; j < edgeCount[i]; j++) {

            printf("-> %d (%d km",
                   graph[i][j].destination,
                   graph[i][j].distance);

            if (graph[i][j].blocked)
                printf(", BLOCKED");

            printf(") ");
        }

        printf("\n");
    }
}


// Main
int main() {

    int vertices = 6;

    // Add roads
    addRoad(0, 1, 5, 0);
    addRoad(0, 2, 2, 0);
    addRoad(1, 3, 3, 0);
    addRoad(2, 3, 4, 0);

    addRoad(1, 4, 2, 0);
    addRoad(3, 5, 2, 0);
    addRoad(4, 5, 3, 0);


    displayGraph(vertices);


    int source;
    int destination;

    printf("\nEnter source location (0-5): ");
    scanf("%d", &source);

    printf("Enter destination location (0-5): ");
    scanf("%d", &destination);


    dijkstra(source, destination, vertices);


    return 0;
}