#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "minheap.c"
#include "graph.c"

#define MAX_PATH 100
#define INF 999999.0

struct RouteResult{
    int found;
    int source;
    int destination;
    int path[MAX_PATH];
    int pathLength;
    int roadCount;
    float totalWeight;
    float totalDistance;
    int warningCount;
    char warnings[10][256];
};

struct RouteResult findShortestRoute(const struct Graph *g, int src, int dest){
    struct RouteResult res;
    res.source = src;
    res.destination = dest;
    res.found = 0;
    res.pathLength = 0;
    res.roadCount = 0;
    res.totalWeight = 0.0;
    res.totalDistance = 0.0;
    res.warningCount = 0;

    if(g == NULL || src <= 0 || dest <= 0 || src >= MAX_LOCATIONS || dest >= MAX_LOCATIONS){
        snprintf(res.warnings[0], 256, "Invalid source or destination ID.");
        res.warningCount = 1;
        return res;
    }

    if(src == dest){
        res.found = 1;
        res.path[0] = src;
        res.pathLength = 1;
        return res;
    }

    float dist[MAX_LOCATIONS];
    int parent[MAX_LOCATIONS];
    int visited[MAX_LOCATIONS];

    for(int i = 0; i < MAX_LOCATIONS; i++){
        dist[i] = INF;
        parent[i] = -1;
        visited[i] = 0;
    }

    dist[src] = 0.0;
    struct MinHeap heap;
    initMinHeap(&heap);
    insert(&heap, src, 0.0);

    while(!isEmpty(&heap)){
        struct HeapNode minNode = deleteMin(&heap);
        int u = minNode.vertex;
        float d = minNode.distance;

        if(d > dist[u]) continue;
        if(visited[u] == 1) continue;
        visited[u] = 1;

        if(u == dest) break;

        struct node *temp = g->adj[u];
        while(temp != NULL){
            int v = temp->vertex;
            float weight = temp->weight;

            if(visited[v] == 0){
                float newDist = dist[u] + weight;
                if(newDist < dist[v]){
                    dist[v] = newDist;
                    parent[v] = u;
                    insert(&heap, v, dist[v]);
                }
            }
            temp = temp->next;
        }
    }

    if(dist[dest] >= INF || parent[dest] == -1){
        res.found = 0;
        snprintf(res.warnings[0], 256, "No usable route exists between Location %d and Location %d.", src, dest);
        res.warningCount = 1;
        return res;
    }

    int tempPath[MAX_PATH];
    int count = 0;
    int curr = dest;

    while(curr != -1 && count < MAX_PATH){
        tempPath[count] = curr;
        count++;
        if(curr == src) break;
        curr = parent[curr];
    }

    res.pathLength = count;
    for(int i = 0; i < count; i++){
        res.path[i] = tempPath[count - 1 - i];
    }

    res.roadCount = res.pathLength - 1;
    res.totalWeight = dist[dest];

    float totalDist = 0.0;
    for(int i = 0; i < res.roadCount; i++){
        int from = res.path[i];
        int to = res.path[i + 1];

        struct node *edge = g->adj[from];
        float edgeDist = 0.0;
        float edgeWeight = 0.0;

        while(edge != NULL){
            if(edge->vertex == to){
                edgeDist = edge->distance;
                edgeWeight = edge->weight;
                break;
            }
            edge = edge->next;
        }

        totalDist += edgeDist;

        if(edgeWeight >= (edgeDist * 1.5) && res.warningCount < 10){
            snprintf(res.warnings[res.warningCount], 256,
                     "Caution between Location %d and %d: Road hazard penalty (Weight %.1f vs Physical %.1f km).",
                     from, to, edgeWeight, edgeDist);
            res.warningCount++;
        }
    }

    res.totalDistance = totalDist;
    res.found = 1;
    return res;
}
