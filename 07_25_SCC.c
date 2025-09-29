#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// --------- Strongly Connected Components (Tarjan's Algorithm) -----------

int timeSCC;
int discSCC[MAX], lowSCC[MAX];
int stackSCC[MAX], stackTopSCC;
int inStackSCC[MAX];
int V; // Number of vertices
int adjSCC[MAX][MAX]; // adjacency matrix or adjacency list (we'll assume adjacency matrix for simplicity)
int adjSizeSCC[MAX];  // number of neighbors for each vertex

void SCCUtil(int u) {
    discSCC[u] = lowSCC[u] = ++timeSCC;
    stackSCC[stackTopSCC++] = u;
    inStackSCC[u] = 1;

    // Explore neighbors
    for (int v = 0; v < V; v++) {
        if (adjSCC[u][v]) { // edge exists u -> v
            if (discSCC[v] == -1) {
                SCCUtil(v);
                if (lowSCC[v] < lowSCC[u])
                    lowSCC[u] = lowSCC[v];
            }
            else if (inStackSCC[v]) {
                if (discSCC[v] < lowSCC[u])
                    lowSCC[u] = discSCC[v];
            }
        }
    }

    // Head node of SCC found
    if (lowSCC[u] == discSCC[u]) {
        printf("SCC: ");
        while (1) {
            int w = stackSCC[--stackTopSCC];
            inStackSCC[w] = 0;
            printf("%d ", w);
            if (w == u)
                break;
        }
        printf("\n");
    }
}

void findSCCs() {
    for (int i = 0; i < V; i++) {
        discSCC[i] = -1;
        lowSCC[i] = -1;
        inStackSCC[i] = 0;
    }
    timeSCC = 0;
    stackTopSCC = 0;

    for (int i = 0; i < V; i++) {
        if (discSCC[i] == -1)
            SCCUtil(i);
    }
}

// --------- Biconnected Components, Articulation Points, Bridges -----------

int timeBCC;
int discBCC[MAX], lowBCC[MAX], parentBCC[MAX];
int apBCC[MAX]; // articulation point marker
int V_undirected;
int adjBCC[MAX][MAX];
int visitedBCC[MAX];

typedef struct StackNode {
    int u;
    int v;
} StackNode;

StackNode edgeStack[MAX * MAX];
int edgeTop;

void pushEdge(int u, int v) {
    edgeStack[edgeTop].u = u;
    edgeStack[edgeTop].v = v;
    edgeTop++;
}

StackNode popEdge() {
    return edgeStack[--edgeTop];
}

void BCCUtil(int u) {
    discBCC[u] = lowBCC[u] = ++timeBCC;
    visitedBCC[u] = 1;
    int children = 0;

    for (int v = 0; v < V_undirected; v++) {
        if (adjBCC[u][v]) {
            if (discBCC[v] == -1) {
                children++;
                parentBCC[v] = u;
                pushEdge(u, v);
                BCCUtil(v);

                if (lowBCC[v] >= discBCC[u]) {
                    apBCC[u] = 1;  // articulation point
                    printf("Biconnected Component: ");
                    StackNode e;
                    do {
                        e = popEdge();
                        printf("(%d,%d) ", e.u, e.v);
                    } while (!(e.u == u && e.v == v));
                    printf("\n");
                }

                if (lowBCC[v] < lowBCC[u])
                    lowBCC[u] = lowBCC[v];
            }
            else if (v != parentBCC[u] && discBCC[v] < discBCC[u]) {
                if (discBCC[v] < lowBCC[u])
                    lowBCC[u] = discBCC[v];
                pushEdge(u, v);
            }
        }
    }
}

void findBCCs() {
    for (int i = 0; i < V_undirected; i++) {
        discBCC[i] = -1;
        lowBCC[i] = -1;
        parentBCC[i] = -1;
        apBCC[i] = 0;
        visitedBCC[i] = 0;
    }
    edgeTop = 0;
    timeBCC = 0;

    for (int i = 0; i < V_undirected; i++) {
        if (discBCC[i] == -1) {
            BCCUtil(i);
            // If edges remain on stack, they form a BCC
            if (edgeTop > 0) {
                printf("Biconnected Component: ");
                while (edgeTop > 0) {
                    StackNode e = popEdge();
                    printf("(%d,%d) ", e.u, e.v);
                }
                printf("\n");
            }
        }
    }

    printf("Articulation Points: ");
    for (int i = 0; i < V_undirected; i++) {
        if (apBCC[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

    printf("Bridges: ");
    // Bridges are edges u-v where low[v] > disc[u] in undirected graph
    for (int u = 0; u < V_undirected; u++) {
        for (int v = u+1; v < V_undirected; v++) {
            if (adjBCC[u][v]) {
                // Check if edge u-v is bridge
                if ((discBCC[u] < lowBCC[v] && parentBCC[v] == u) || (discBCC[v] < lowBCC[u] && parentBCC[u] == v)) {
                    printf("(%d,%d) ", u, v);
                }
            }
        }
    }
    printf("\n");
}

// ------------------ Main -------------------

int main() {
    // Example usage

    // --- Directed graph for SCC ---
    printf("Enter number of vertices for directed graph (SCC): ");
    scanf("%d", &V);

    printf("Enter adjacency matrix (directed graph):\n");
    for (int i = 0; i < V; i++) 
        for (int j = 0; j < V; j++)
            scanf("%d", &adjSCC[i][j]);

    printf("\nStrongly Connected Components:\n");
    findSCCs();

    // --- Undirected graph for BCC, AP, Bridges ---
    printf("\nEnter number of vertices for undirected graph (BCC, AP, Bridges): ");
    scanf("%d", &V_undirected);

    printf("Enter adjacency matrix (undirected graph):\n");
    for (int i = 0; i < V_undirected; i++) 
        for (int j = 0; j < V_undirected; j++)
            scanf("%d", &adjBCC[i][j]);

    printf("\nBiconnected Components, Articulation Points, Bridges:\n");
    findBCCs();

    return 0;
}
