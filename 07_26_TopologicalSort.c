#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int graph[MAX][MAX];  // adjacency matrix
int visited[MAX];
int stack[MAX];
int top = -1;
int V;  // Number of vertices

// Push onto stack
void push(int v) {
    stack[++top] = v;
}

// Pop from stack
int pop() {
    return stack[top--];
}

// DFS function to visit nodes
void dfs(int v) {
    visited[v] = 1;
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && !visited[i]) {
            dfs(i);
        }
    }
    // All descendants processed, push this vertex
    push(v);
}

// Topological sort function
void topologicalSort() {
    for (int i = 0; i < V; i++)
        visited[i] = 0;

    for (int i = 0; i < V; i++) {
        if (!visited[i])
            dfs(i);
    }

    printf("Topological order:\n");
    while (top != -1) {
        printf("%d ", pop());
    }
    printf("\n");
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &graph[i][j]);

    topologicalSort();

    return 0;
}
