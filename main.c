#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "dijkstra.h"
#include "dfs.h"
#include "mst.h"

void send_command_menu() {
    printf("\033[0;33m____________________________________\n");
    printf("__________Вот ваше меню_____________\n");
    printf("____Выберите один из вариантов ниже___\n");
    printf("[1] Добавить комнату\n");
    printf("[2] Добавить соединение\n");
    printf("[3] Проверить достижимость выхода\n");
    printf("[4] Найти кратчайший путь\n");
    printf("[5] Модифицировать лабиринт (MST)\n");
    printf("[6] Вывести состояние графа\n");
    printf("[0] Выход\n");
    printf("____________________________________\033[0m\n");
}

void add_room(Graph *graph) {
    char id[256];
    int type;
    printf("Введите идентификатор комнаты: ");
    scanf("%s", id);
    printf("Введите тип комнаты (0 - вход, 1 - выход, 2 - переход): ");
    scanf("%d", &type);
    addVertex(graph, id, type);
}

void add_connection(Graph *graph) {
    char id1[256], id2[256];
    int weight;
    printf("Введите идентификаторы двух комнат для соединения: ");
    scanf("%s %s", id1, id2);
    printf("Введите вес соединения: ");
    scanf("%d", &weight);
    addEdge(graph, id1, id2, weight);
}

void check_reachability(Graph *graph) {
    char startId[256];
    printf("Введите идентификатор стартовой комнаты: ");
    scanf("%s", startId);
    if (dfs(graph, startId)) {
        printf("Достижимость выхода подтверждена.\n");
    } else {
        printf("Выход недостижим.\n");
    }
}

void find_shortest_path(Graph *graph) {
    char startId[256], endId[256];
    printf("Введите идентификатор начальной комнаты: ");
    scanf("%s", startId);
    printf("Введите идентификатор конечной комнаты: ");
    scanf("%s", endId);
    dijkstra(graph, startId, endId);
}

void modify_labyrinth(Graph *graph) {
    mst(graph);
}

void print_graph_state(Graph *graph) {
    printGraph(graph);
}

void visualize_graph(Graph *graph) {
    visualizeGraph(graph);
}

void menu(Graph *graph) {
    void (*func[7])(Graph *) = {add_room, add_connection, check_reachability, find_shortest_path, modify_labyrinth, print_graph_state, visualize_graph};
    printf("\033[H\033[J");
    send_command_menu();

    while (1) {
        printf("\033[1;90mВведите команду (номер [0-7]):\033[0;0m\n");
        int command = 0;
        int x = scanf("%d", &command);
        if (x == EOF) {
            scanf("%*[^\n]*c");
            deleteGraph(graph);
            return;
        }
        if (command == 0) {
            deleteGraph(graph);
            return;
        } else if (command > 0 && command < 8) {
            func[command - 1](graph);
        } else {
            printf("Неверная команда. Попробуйте снова.\n");
        }
    }
}

int main() {
    Graph* labyrinth = createGraph();
    menu(labyrinth);
    return 0;
}
