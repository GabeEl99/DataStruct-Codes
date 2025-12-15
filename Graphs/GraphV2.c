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

void bfs(Graph *graph, int startVertex) {
    int *visited = (int *)calloc(graph->numVertices, sizeof(int));
    int *queue = (int *)malloc(graph->numVertices * sizeof(int));
    int front = 0;
    int rear = -1;

    visited[startVertex] = 1;
    queue[++rear] = startVertex;

    while (front <= rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        Node *temp = graph->adjLists[currentVertex];
        while (temp != NULL) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[++rear] = adjVertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");

    free(visited);
    free(queue);
}

void dfsUtil(Graph *graph, int vertex, int *visited) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    Node *temp = graph->adjLists[vertex];
    while (temp != NULL) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            dfsUtil(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

void dfs(Graph *graph, int startVertex) {
    int *visited = (int *)calloc(graph->numVertices, sizeof(int));
    dfsUtil(graph, startVertex, visited);
    printf("\n");
    free(visited);
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
    int vertices = 6;
    Graph *graph = createGraph(vertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    bfs(graph, 0);
    dfs(graph, 0);

    freeGraph(graph);
    return 0;
}
