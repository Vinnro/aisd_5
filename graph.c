#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = NULL;
    graph->edges = NULL;
    return graph;
}

void visualizeGraph(Graph* graph) {
    printf("Визуализация графа:\n");

    // Перебираем все вершины и выводим их соединения
    Vertex* vertex = graph->vertices;
    while (vertex) {
        printf("%s", vertex->id);

        Edge* edge = graph->edges;
        int isFirstEdge = 1;

        while (edge) {
            if (edge->vertex1 == vertex) {
                if (isFirstEdge) {
                    printf(" -> ");
                    isFirstEdge = 0;
                } else {
                    printf(", ");
                }
                printf("%s(%d)", edge->vertex2->id, edge->weight);
            } else if (edge->vertex2 == vertex) {
                if (isFirstEdge) {
                    printf(" <- ");
                    isFirstEdge = 0;
                } else {
                    printf(", ");
                }
                printf("%s(%d)", edge->vertex1->id, edge->weight);
            }
            edge = edge->next;
        }
        printf("\n");
        vertex = vertex->next;
    }
}

void printGraph(Graph* graph) {
    Vertex* vertex = graph->vertices;
    printf("Вершины:\n");
    while (vertex) {
        printf("Комната: %s, Тип: %d\n", vertex->id, vertex->type);
        vertex = vertex->next;
    }

    Edge* edge = graph->edges;
    printf("Рёбра:\n");
    while (edge) {
        printf("Соединение: %s - %s, Вес: %d\n",
               edge->vertex1->id, edge->vertex2->id, edge->weight);
        edge = edge->next;
    }
}

void deleteGraph(Graph* graph) {
    Vertex* currentVertex = graph->vertices;
    while (currentVertex != NULL) {
        Vertex* tmpVertex = currentVertex;
        currentVertex = currentVertex->next;
        free(tmpVertex);
    }

    Edge* currentEdge = graph->edges;
    while (currentEdge != NULL) {
        Edge* tmpEdge = currentEdge;
        currentEdge = currentEdge->next;
        free(tmpEdge);
    }

    free(graph);
}

void addVertex(Graph* graph, const char* id, int type) {
    Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
    strcpy(vertex->id, id);
    vertex->type = type;
    vertex->next = graph->vertices;
    graph->vertices = vertex;
}

void addEdge(Graph* graph, const char* id1, const char* id2, int weight) {
    Vertex* vertex1 = NULL;
    Vertex* vertex2 = NULL;

    Vertex* currentVertex = graph->vertices;
    while (currentVertex != NULL) {
        if (strcmp(currentVertex->id, id1) == 0) {
            vertex1 = currentVertex;
        }
        if (strcmp(currentVertex->id, id2) == 0) {
            vertex2 = currentVertex;
        }
        currentVertex = currentVertex->next;
    }

    if (vertex1 && vertex2) {
        Edge* edge = (Edge*)malloc(sizeof(Edge));
        edge->vertex1 = vertex1;
        edge->vertex2 = vertex2;
        edge->weight = weight;
        edge->next = graph->edges;
        graph->edges = edge;
    }
}

