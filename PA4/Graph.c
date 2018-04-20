/*
- Ryan Shee
- CruzID: rshee
- Programming Assignment 5
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

#define NIL (int) 0
#define UNDEF (int) -1
#define WHITE (int) 0
#define GRAY (int) 1
#define BLACK (int) -1

// structs
typedef struct GraphObj {
    List *neighbors;
    int *color;
    int *parent;
    int *discover;
    int *finish;

    int order; // number of vertices
    int size; // number of edges
} GraphObj;

// constructors-deconstructors
Graph newGraph(int n) {
    Graph graph = malloc(sizeof(struct GraphObj));
    graph->neighbors = calloc(n + 1, sizeof(List));
    graph->color = calloc(n + 1, sizeof(int));
    graph->parent = calloc(n + 1, sizeof(int));
    graph->discover = calloc(n + 1, sizeof(int));
    graph->finish = calloc(n + 1, sizeof(int));

    graph->order = n;
    graph->size = 0;
    for(int i = 1; i < n + 1; i++) {
        graph->neighbors[i] = newList();
        graph->color[i] = WHITE;
        graph->parent[i] = NIL;
        graph->discover[i] = UNDEF;
        graph->finish[i] = UNDEF;
    }
    return graph;
}

void freeGraph(Graph* pG) {
    Graph tmp = *pG;
    for(int i = 1; i <= getOrder(tmp); i++)
        freeList(&(tmp->neighbors[i]));
    free(tmp->neighbors);
    free(tmp->color);
    free(tmp->parent);
    free(tmp->discover);
    free(tmp->finish);
    free(*pG);
    *pG = NULL;
}

/*
-   Access functions
*/
int getOrder(Graph G) {
    if(G == NULL) {
        fprintf(stderr, "Graph error: getOrder() called on null Graph reference\n");
        exit(1);
    }
    return G->order;
}

int getSize(Graph G) {
    if(G == NULL) {
        fprintf(stderr, "Graph error: getSize() called on null Graph reference\n");
        exit(1);
    }
    return G->size;
}

int getParent(Graph G, int u) {
    if(G == NULL) {
        fprintf(stderr, "Graph error: getParent() called on null Graph reference\n");
        exit(1);
    }
    return G->parent[u];
}

int getDiscover(Graph G, int u) {
    if(G == NULL) {
        fprintf(stderr, "Graph error: getDiscover() called on null Graph reference\n");
        exit(1);
    }
    return G->discover[u];
}

int getFinish(Graph G, int u) {
    if(G == NULL) {
        fprintf(stderr, "Graph error: getFinish() called on null Graph reference\n");
        exit(1);
    }
    return G->finish[u];
}

/*
-   Manipulation procedures
*/
void addEdgeHelper(List L, int vertex) {
    if(length(L) == 0) {
        append(L, vertex);
        return;
    }
    for(moveFront(L); index(L) != -1; moveNext(L)) {
        if(vertex < get(L)) {
            insertBefore(L, vertex);
            break;
        }
    }
    if(index(L) == -1) append(L, vertex);
}

void addEdge(Graph G, int u, int v) {
    if(G == NULL) {
        fprintf(stderr, "Graph error: addEdge() called on null Graph reference\n");
        exit(1);
    }
    addEdgeHelper(G->neighbors[u], v);
    addEdgeHelper(G->neighbors[v], u);
    G->size++;
}

void addArc(Graph G, int u, int v) {
    if(G == NULL) {
        fprintf(stderr, "Graph error: addArc() called on null Graph reference\n");
        exit(1);
    }
    addEdgeHelper(G->neighbors[u], v);
    G->size++;
}

void visit(Graph G, List S, int u, int *time) {
    G->discover[u] = ++*time;
    G->color[u] = GRAY;
    moveFront(G->neighbors[u]);
    for(moveFront(G->neighbors[u]); index(G->neighbors[u]) != -1; moveNext(G->neighbors[u])) {
        int y = get(G->neighbors[u]);
        if(G->color[y] == WHITE) {
            G->parent[y] = u;
            visit(G, S, y, time);
        }
    }
    G->color[u] = BLACK;
    G->finish[u] = ++*time;
    prepend(S, u);
}

void DFS(Graph G, List S) {
    if(length(S) != getOrder(G)) {
        fprintf(stderr, "Graph error: DFS() cannot be called if length of S is not equal to order of G\n");
        exit(1);
    }
    for(int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }
    int time = 0;
    moveFront(S);
    while(index(S) >= 0) {
        int u = get(S);
        if(G->color[u] == WHITE) visit(G, S, u, &time);
        moveNext(S);
    }
    for (int i = 0; i < getOrder(G); i++) deleteBack(S);
}

/*
-   Other operations
*/
Graph transpose(Graph G) {
    Graph transposed = newGraph(getOrder(G));
    for(int i = 1; i <= getOrder(G); i++) {
        moveFront(G->neighbors[i]);
        if(length(G->neighbors[i]) == 0) continue;
        else {
            while(index(G->neighbors[i]) != -1) {
                addArc(transposed, get(G->neighbors[i]), i);
                moveNext(G->neighbors[i]);
            }
        }
    }
    return transposed;
}

Graph copyGraph(Graph G) {
    Graph copiedGraph = newGraph(getOrder(G));
    for(int i = 1; i <= getOrder(G); i++) {
        moveFront(G->neighbors[i]);
        while(index(G->neighbors[i]) >= 0) {
            addArc(copiedGraph, i, get(G->neighbors[i]));
            moveNext(G->neighbors[i]);
        }
    }
    return copiedGraph;
}

void printGraph(FILE* out, Graph G){
   for (int i = 1; i <= getOrder(G); i++){
      fprintf(out, "%d:", i);
      for (moveFront(G->neighbors[i]); index(G->neighbors[i]) != -1; moveNext(G->neighbors[i]))
         fprintf(out, " %d", get(G->neighbors[i]));
      fprintf(out, "\n");
   }
}
