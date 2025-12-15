#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

typedef struct {
    int numVertices;
    Node **adjLists;
} Graph;

Node *createNode(int v) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph *createGraph(int vertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node **)malloc(vertices * sizeof(Node *));
    int ndx;
    for (ndx = 0; ndx < vertices; ndx++) {
        graph->adjLists[ndx] = NULL;
    }
    return graph;
}

void addEdge(Graph *graph, int src, int dest) {
    Node *newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printGraph(Graph *graph) {
    int ndx;
    for (ndx = 0; ndx < graph->numVertices; ndx++) {
        Node *temp = graph->adjLists[ndx];
        printf("Vertex %d:", ndx);
        while (temp != NULL) {
            printf(" %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void freeGraph(Graph *graph) {
    int ndx;
    for (ndx = 0; ndx < graph->numVertices; ndx++) {
        Node *temp = graph->adjLists[ndx];
        while (temp != NULL) {
            Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->adjLists);
    free(graph);
}

int main() {
    int vertices = 5;
    Graph *graph = createGraph(vertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printGraph(graph);

    freeGraph(graph);
    return 0;
}
