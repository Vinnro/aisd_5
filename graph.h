#ifndef GRAPH_H
#define GRAPH_H

typedef struct Vertex {
    char id[50];
    enum { ENTRY, EXIT, TRANSITION } type;
    struct Vertex* next;
} Vertex;

typedef struct Edge {
    Vertex* vertex1;
    Vertex* vertex2;
    int weight;
    struct Edge* next;
} Edge;


typedef struct Graph {
    Vertex* vertices;
    Edge* edges;
} Graph;




Graph* createGraph();
void visualizeGraph(Graph* graph);
void printGraph(Graph* graph);
void deleteGraph(Graph* graph);
void addVertex(Graph* graph, const char* id, int type);
void addEdge(Graph* graph, const char* id1, const char* id2, int weight);

#endif // GRAPH_H
