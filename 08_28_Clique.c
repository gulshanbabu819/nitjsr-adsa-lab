#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_N 30  // Max number of vertices supported

int graph[MAX_N][MAX_N];  // Adjacency matrix
int n, e, m;

// Function to check if the selected vertices form a clique
bool isClique(int* subset, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (!graph[subset[i]][subset[j]]) {
                return false;
            }
        }
    }
    return true;
}

// Recursive function to generate all combinations of vertices
bool findClique(int* subset, int idx, int start, int k) {
    if (idx == k) {
        return isClique(subset, k);
    }

    for (int i = start; i <= n - (k - idx); ++i) {
        subset[idx] = i;
        if (findClique(subset, idx + 1, i + 1, k)) {
            return true;
        }
    }

    return false;
}

int main() {
    printf("Enter number of vertices (n): ");
    scanf("%d", &n);

    if (n > MAX_N) {
        printf("Maximum supported vertices is %d.\n", MAX_N);
        return 1;
    }

    printf("Enter number of edges (e): ");
    scanf("%d", &e);

    printf("Enter desired clique size (m): ");
    scanf("%d", &m);

    // Initialize the graph
    memset(graph, 0, sizeof(graph));

    printf("Enter %d edges (u v) pairs, 0-based indexing:\n", e);
    for (int i = 0; i < e; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= n || v >= n || u == v) {
            printf("Invalid edge: (%d, %d)\n", u, v);
            return 1;
        }
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    int subset[MAX_N];
    if (findClique(subset, 0, 0, m)) {
        printf("Graph contains a clique of size %d.\n", m);
    } else {
        printf("Graph does NOT contain a clique of size %d.\n", m);
    }

    return 0;
}
