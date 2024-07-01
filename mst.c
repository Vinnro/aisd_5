#include "mst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Subset {
    Vertex* parent;
    int rank;
} Subset;

int get_vertex_index(Vertex* vertices[], int size, char* id) {
    for (int i = 0; i < size; i++) {
        if (strcmp(vertices[i]->id, id) == 0) {
            return i;
        }
    }
    return -1;
}

Vertex* find(Subset subsets[], Vertex* vertex, Vertex* vertices[], int size) {
    int idx = get_vertex_index(vertices, size, vertex->id);
    if (idx == -1) {
        printf("find: Вершина %s не найдена в подмножествах.\n", vertex->id);
        return NULL;
    }
    if (subsets[idx].parent != vertex) {
        subsets[idx].parent = find(subsets, subsets[idx].parent, vertices, size);
    }
    return subsets[idx].parent;
}


void union_subsets(Subset subsets[], Vertex* v1, Vertex* v2, Vertex* vertices[], int size) {
    Vertex* root1 = find(subsets, v1, vertices, size);
    Vertex* root2 = find(subsets, v2, vertices, size);

    if (root1 == NULL || root2 == NULL) {
        printf("union_subsets: Корневая вершина не найдена.\n");
        return;
    }

    int root1Index = get_vertex_index(vertices, size, root1->id);
    int root2Index = get_vertex_index(vertices, size, root2->id);

    if (root1Index == -1 || root2Index == -1) {
        printf("union_subsets: Индекс корневой вершины не найден.\n");
        return;
    }

    if (subsets[root1Index].rank < subsets[root2Index].rank) {
        subsets[root1Index].parent = root2;
    } else if (subsets[root1Index].rank > subsets[root2Index].rank) {
        subsets[root2Index].parent = root1;
    } else {
        subsets[root2Index].parent = root1;
        subsets[root1Index].rank++;
    }
}


void mst(Graph* graph) {
    int vertex_count = 0;
    Vertex* vertex = graph->vertices;
    while (vertex) {
        vertex_count++;
        vertex = vertex->next;
    }

    int edge_count = 0;
    Edge* edge = graph->edges;
    while (edge) {
        edge_count++;
        edge = edge->next;
    }

    printf("Количество вершин: %d\n", vertex_count);
    printf("Количество рёбер: %d\n", edge_count);

    Edge** result = (Edge**)malloc(vertex_count * sizeof(Edge*)); // было edge_count, исправлено на vertex_count
    int e = 0;
    int i = 0;

    Edge** edges = (Edge**)malloc(edge_count * sizeof(Edge*));
    Edge* currentEdge = graph->edges;
    while (currentEdge != NULL) {
        edges[i++] = currentEdge;
        currentEdge = currentEdge->next;
    }


    for (int i = 0; i < edge_count - 1; ++i) {
        for (int j = 0; j < edge_count - i - 1; ++j) {
            if (edges[j]->weight > edges[j + 1]->weight) {
                Edge* temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    Subset* subsets = (Subset*)malloc(vertex_count * sizeof(Subset));
    Vertex** vertices = (Vertex**)malloc(vertex_count * sizeof(Vertex*));
    i = 0;
    vertex = graph->vertices;
    while (vertex) {
        subsets[i].parent = vertex;
        subsets[i].rank = 0;
        vertices[i] = vertex;
        printf("Инициализация подмножества: %s\n", vertex->id);
        i++;
        vertex = vertex->next;
    }

    i = 0;
    while (e < vertex_count - 1 && i < edge_count) {
        Edge* next_edge = edges[i++];
        Vertex* x = find(subsets, next_edge->vertex1, vertices, vertex_count);
        Vertex* y = find(subsets, next_edge->vertex2, vertices, vertex_count);

        if (x == NULL || y == NULL) {
            printf("Ошибка: не удалось найти вершину %s или %s.\n", next_edge->vertex1->id, next_edge->vertex2->id);
            continue;
        }

        if (x != y) {
            result[e++] = next_edge;
            union_subsets(subsets, x, y, vertices, vertex_count);
        }
    }

    printf("Рёбра минимального остовного дерева:\n");
    for (i = 0; i < e; ++i) {
        printf("%s -- %s (вес: %d)\n", result[i]->vertex1->id, result[i]->vertex2->id, result[i]->weight);
    }

    free(subsets);
    free(vertices);
    free(result);
    free(edges);
}
