#include <stdio.h>
#include <stdbool.h>

#define MAX 20  // Max number of vertices

int graph[MAX][MAX];   // Adjacency matrix
int color[MAX];        // Color assigned to each vertex

// Function to check if it's safe to assign color to vertex
bool isSafe(int v, int c, int V) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && color[i] == c) {
            return false;
        }
    }
    return true;
}

// Recursive utility function to solve coloring problem
bool graphColoringUtil(int m, int V, int v) {
    if (v == V) {
        return true;  // All vertices are assigned
    }

    // Try all colors for vertex v
    for (int c = 1; c <= m; c++) {
        if (isSafe(v, c, V)) {
            color[v] = c;

            // Recur to assign colors to rest of the vertices
            if (graphColoringUtil(m, V, v + 1)) {
                return true;
            }

            // Backtrack
            color[v] = 0;
        }
    }

    return false;  // No valid color assignment found
}

// Main function to solve the m-coloring problem
bool graphColoring(int m, int V) {
    for (int i = 0; i < V; i++) {
        color[i] = 0;
    }

    if (!graphColoringUtil(m, V, 0)) {
        printf("Solution does not exist.\n");
        return false;
    }

    printf("Color assignment:\n");
    for (int i = 0; i < V; i++) {
        printf("Vertex %d ---> Color %d\n", i, color[i]);
    }

    return true;
}

// Example usage
int main() {
    int V, E, m;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    // Initialize graph
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v) as 0-based indices:\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;  // Undirected graph
    }

    printf("Enter the number of colors: ");
    scanf("%d", &m);

    graphColoring(m, V);

    return 0;
}
