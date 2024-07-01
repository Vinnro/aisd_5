#include "dijkstra.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 100
#define INF INT_MAX

void initialize_single_source(Graph* graph, DijkstraVertex vertices[], const char* startId) {
    Vertex* current = graph->vertices;
    int i = 0;
    while (current != NULL) {
        strcpy(vertices[i].id, current->id);
        vertices[i].distance = INF;
        vertices[i].visited = 0;
        if (strcmp(current->id, startId) == 0) {
            vertices[i].distance = 0;
        }
        current = current->next;
        i++;
    }
}

int get_vertex_index1(DijkstraVertex vertices[], int size, const char* id) {
    for (int i = 0; i < size; i++) {
        if (strcmp(vertices[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

DijkstraVertex* extract_min(DijkstraVertex vertices[], int size) {
    int minDistance = INF;
    DijkstraVertex* minVertex = NULL;
    for (int i = 0; i < size; i++) {
        if (!vertices[i].visited && vertices[i].distance < minDistance) {
            minDistance = vertices[i].distance;
            minVertex = &vertices[i];
        }
    }
    return minVertex;
}

void relax(DijkstraVertex vertices[], int uIndex, int vIndex, int weight) {
    if (vertices[vIndex].distance > vertices[uIndex].distance + weight) {
        vertices[vIndex].distance = vertices[uIndex].distance + weight;
    }
}

void dijkstra(Graph* graph, const char* startId, const char* endId) {
    DijkstraVertex vertices[MAX_VERTICES];
    initialize_single_source(graph, vertices, startId);

    Vertex* current = graph->vertices;
    int size = 0;
    while (current != NULL) {
        size++;
        current = current->next;
    }

    while (1) {
        DijkstraVertex* u = extract_min(vertices, size);
        if (u == NULL) {
            break;
        }
        u->visited = 1;
        if (strcmp(u->id, endId) == 0) {
            printf("Кратчайший путь от %s до %s: %d\n", startId, endId, u->distance);
            return;
        }

        Edge* currentEdge = graph->edges;
        while (currentEdge != NULL) {
            if (strcmp(currentEdge->vertex1->id, u->id) == 0 || strcmp(currentEdge->vertex2->id, u->id) == 0) {
                Vertex* v = (strcmp(currentEdge->vertex1->id, u->id) == 0) ? currentEdge->vertex2 : currentEdge->vertex1;
                int vIndex = get_vertex_index1(vertices, size, v->id);
                relax(vertices, get_vertex_index1(vertices, size, u->id), vIndex, currentEdge->weight);
            }
            currentEdge = currentEdge->next;
        }
    }

    printf("Путь от %s до %s не существует.\n", startId, endId);
}
