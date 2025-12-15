#include <stdio.h>
#include <stdlib.h>

typedef struct WNode {
    int vertex;
    int weight;
    struct WNode *next;
} WNode;

typedef struct {
    int numVertices;
    WNode **adjLists;
} WGraph;

WNode *createWNode(int v, int w) {
    WNode *newNode = (WNode *)malloc(sizeof(WNode));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = NULL;
    return newNode;
}

WGraph *createWGraph(int vertices) {
    WGraph *graph = (WGraph *)malloc(sizeof(WGraph));
    graph->numVertices = vertices;
    graph->adjLists = (WNode **)malloc(vertices * sizeof(WNode *));
    int ndx;
    for (ndx = 0; ndx < vertices; ndx++) {
        graph->adjLists[ndx] = NULL;
    }
    return graph;
}

void addWEdge(WGraph *graph, int src, int dest, int weight) {
    WNode *newNode = createWNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createWNode(src, weight);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printWGraph(WGraph *graph) {
    int ndx;
    for (ndx = 0; ndx < graph->numVertices; ndx++) {
        WNode *temp = graph->adjLists[ndx];
        printf("Vertex %d:", ndx);
        while (temp != NULL) {
            printf(" (%d, w=%d)", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

void freeWGraph(WGraph *graph) {
    int ndx;
    for (ndx = 0; ndx < graph->numVertices; ndx++) {
        WNode *temp = graph->adjLists[ndx];
        while (temp != NULL) {
            WNode *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->adjLists);
    free(graph);
}

int main() {
    int vertices = 5;
    WGraph *graph = createWGraph(vertices);

    addWEdge(graph, 0, 1, 4);
    addWEdge(graph, 0, 2, 2);
    addWEdge(graph, 1, 2, 5);
    addWEdge(graph, 1, 3, 10);
    addWEdge(graph, 2, 3, 3);
    addWEdge(graph, 3, 4, 1);

    printWGraph(graph);

    freeWGraph(graph);
    return 0;
}
