#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
typedef struct {
    char id[50];
    int distance;
    int visited;
} DijkstraVertex;

void dijkstra(Graph* graph, const char* startId, const char* endId);

#endif // DIJKSTRA_H
