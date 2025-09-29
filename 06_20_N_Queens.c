#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 20

int board[MAX];
int N;

// Function to print the board
void printSolution() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j)
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

// Function to check if a queen can be placed at (row, col)
bool isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        // Check same column and diagonals
        if (board[i] == col || 
            abs(board[i] - col) == abs(i - row))
            return false;
    }
    return true;
}

// Recursive function to solve N-Queens
void solve(int row) {
    if (row == N) {
        printSolution();  // Found a valid configuration
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row] = col;     // Place queen
            solve(row + 1);       // Recur to next row
            // No need to undo board[row] due to overwrite on next loop
        }
    }
}

int main() {
    printf("Enter the value of N (max %d): ", MAX);
    scanf("%d", &N);

    if (N <= 0 || N > MAX) {
        printf("Invalid board size.\n");
        return 1;
    }

    printf("\nSolutions to the %d-Queens problem:\n\n", N);
    solve(0);

    return 0;
}
