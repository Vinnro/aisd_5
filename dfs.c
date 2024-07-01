#include "dfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
    Vertex* vertex;
    struct Stack* next;
} Stack;

void push(Stack** stack, Vertex* vertex) {
    Stack* newNode = (Stack*)malloc(sizeof(Stack));
    newNode->vertex = vertex;
    newNode->next = *stack;
    *stack = newNode;
}

Vertex* pop(Stack** stack) {
    if (*stack == NULL) {
        return NULL;
    }
    Stack* top = *stack;
    Vertex* vertex = top->vertex;
    *stack = top->next;
    free(top);
    return vertex;
}

int is_empty(Stack* stack) {
    return stack == NULL;
}

int dfs(Graph* graph, const char* startId) {
    Vertex* startVertex = NULL;
    Vertex* currentVertex = graph->vertices;
    while (currentVertex != NULL) {
        if (strcmp(currentVertex->id, startId) == 0) {
            startVertex = currentVertex;
            break;
        }
        currentVertex = currentVertex->next;
    }

    if (startVertex == NULL) {
        printf("Комната с идентификатором %s не найдена.\n", startId);
        return 0;
    }

    // Инициализация массива посещенных вершин
    int numVertices = 0;
    currentVertex = graph->vertices;
    while (currentVertex != NULL) {
        numVertices++;
        currentVertex = currentVertex->next;
    }
    int* visited = (int*)malloc(numVertices * sizeof(int));
    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;
    }

    Stack* stack = NULL;
    push(&stack, startVertex);

    while (!is_empty(stack)) {
        Vertex* vertex = pop(&stack);
        int vertexIndex = atoi(vertex->id); // Преобразование id в индекс
        if (!visited[vertexIndex]) {
            visited[vertexIndex] = 1;
            if (vertex->type == EXIT) {
                free(visited);
                return 1;
            }

            Edge* currentEdge = graph->edges;
            while (currentEdge != NULL) {
                if (strcmp(currentEdge->vertex1->id, vertex->id) == 0 && !visited[atoi(currentEdge->vertex2->id)]) {
                    push(&stack, currentEdge->vertex2);
                } else if (strcmp(currentEdge->vertex2->id, vertex->id) == 0 && !visited[atoi(currentEdge->vertex1->id)]) {
                    push(&stack, currentEdge->vertex1);
                }
                currentEdge = currentEdge->next;
            }
        }
    }

    free(visited);
    return 0;
}
