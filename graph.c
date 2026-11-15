#include<stdio.h>
#include<stdlib.h>

#define MAX_LOCATIONS 200

struct node{
    int vertex;
    float weight;
    float distance;
    int road_id;
    struct node *next;
};

struct Graph{
    int n;
    struct node *adj[MAX_LOCATIONS];
};

float calculateRoadWeight(float distance, int traffic, int flood, int landslide, int damage){
    if(distance <= 0) return 0.0;

    if(traffic < 0) traffic = 0;
    if(traffic > 100) traffic = 100;
    if(flood < 0) flood = 0;
    if(flood > 100) flood = 100;
    if(landslide < 0) landslide = 0;
    if(landslide > 100) landslide = 100;
    if(damage < 0) damage = 0;
    if(damage > 100) damage = 100;

    float T = (float)traffic / 100.0;
    float F = (float)flood / 100.0;
    float L = (float)landslide / 100.0;
    float R = (float)damage / 100.0;

    float penalty = 1.0 + (0.5 * T) + (0.8 * F) + (0.6 * L) + (0.5 * R);
    return distance * penalty;
}

void initGraph(struct Graph *g, int totalLocations){
    if(g == NULL) return;
    g->n = totalLocations;
    for(int i = 0; i < MAX_LOCATIONS; i++){
        g->adj[i] = NULL;
    }
}

static void insertEdgeNode(struct Graph *g, int from, int to, float weight, float distance, int road_id){
    if(from < 0 || from >= MAX_LOCATIONS) return;

    struct node *temp = (struct node*)malloc(sizeof(struct node));
    if(temp == NULL) return;

    temp->vertex = to;
    temp->weight = weight;
    temp->distance = distance;
    temp->road_id = road_id;
    temp->next = g->adj[from];
    g->adj[from] = temp;
}

void addEdge(struct Graph *g, int u, int v, float weight, float distance, int road_id, int is_one_way){
    if(g == NULL || u <= 0 || v <= 0 || u >= MAX_LOCATIONS || v >= MAX_LOCATIONS) return;

    insertEdgeNode(g, u, v, weight, distance, road_id);
    if(is_one_way == 0){
        insertEdgeNode(g, v, u, weight, distance, road_id);
    }
}

void freeGraph(struct Graph *g){
    if(g == NULL) return;
    for(int i = 0; i < MAX_LOCATIONS; i++){
        struct node *curr = g->adj[i];
        while(curr != NULL){
            struct node *temp = curr;
            curr = curr->next;
            free(temp);
        }
        g->adj[i] = NULL;
    }
    g->n = 0;
}
