#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 20

int graph[MAX_N][MAX_N];
int path[MAX_N];
int n, e;

bool isSafe(int v, int pos) {
    // Check if this vertex is connected to the previous vertex
    if (graph[path[pos - 1]][v] == 0)
        return false;

    // Check if vertex has already been included
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

bool hamiltonianCycleUtil(int pos) {
    // Base case: all vertices are in the path
    if (pos == n) {
        // Check if there is an edge from the last vertex to the first
        if (graph[path[pos - 1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    // Try different vertices as the next candidate
    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;

            if (hamiltonianCycleUtil(pos + 1))
                return true;

            // Backtrack
            path[pos] = -1;
        }
    }

    return false;
}

bool hamiltonianCycle() {
    // Initialize path
    for (int i = 0; i < n; i++)
        path[i] = -1;

    // Start at vertex 0
    path[0] = 0;

    if (hamiltonianCycleUtil(1) == false) {
        return false;
    }

    return true;
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

    // Initialize graph
    memset(graph, 0, sizeof(graph));

    printf("Enter %d edges (u v), 0-based index:\n", e);
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

    if (hamiltonianCycle()) {
        printf("Graph contains a Hamiltonian Cycle.\n");
        printf("One such cycle: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", path[i]);
        }
        printf("%d\n", path[0]); // close the cycle
    } else {
        printf("Graph does NOT contain a Hamiltonian Cycle.\n");
    }

    return 0;
}
