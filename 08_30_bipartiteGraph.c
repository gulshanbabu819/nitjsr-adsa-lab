#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 100

int graph[MAX_N][MAX_N];
int color[MAX_N];
int n, e;

bool isBipartite(int start) {
    int queue[MAX_N];
    int front = 0, rear = 0;

    color[start] = 0; // Start coloring with 0
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];

        for (int v = 0; v < n; v++) {
            if (graph[u][v]) {
                if (color[v] == -1) {
                    // Assign alternate color to neighbor
                    color[v] = 1 - color[u];
                    queue[rear++] = v;
                } else if (color[v] == color[u]) {
                    // Same color on both sides => not bipartite
                    return false;
                }
            }
        }
    }

    return true;
}

int main() {
    printf("Enter number of vertices (n): ");
    scanf("%d", &n);

    printf("Enter number of edges (e): ");
    scanf("%d", &e);

    // Initialize graph and colors
    memset(graph, 0, sizeof(graph));
    for (int i = 0; i < n; i++) color[i] = -1;

    printf("Enter %d edges (u v), 0-based indexing:\n", e);
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= n || v >= n || u == v) {
            printf("Invalid edge (%d, %d)\n", u, v);
            return 1;
        }
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    // Handle disconnected graphs
    bool is_bipartite = true;
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            if (!isBipartite(i)) {
                is_bipartite = false;
                break;
            }
        }
    }

    if (is_bipartite) {
        printf("Graph is Bipartite.\n");
    } else {
        printf("Graph is NOT Bipartite.\n");
    }

    return 0;
}
