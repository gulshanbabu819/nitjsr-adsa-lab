#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Recursive backtracking for 0/1 knapsack
int knapsack(int W, int wt[], int val[], int n, int i) {
    // Base case: no items left or no capacity left
    if (i == n || W == 0)
        return 0;

    // If weight of current item > remaining capacity, skip it
    if (wt[i] > W)
        return knapsack(W, wt, val, n, i + 1);

    // Choice 1: include the item
    int include = val[i] + knapsack(W - wt[i], wt, val, n, i + 1);

    // Choice 2: exclude the item
    int exclude = knapsack(W, wt, val, n, i + 1);

    // Return the better of two choices
    return max(include, exclude);
}

int main() {
    int val[] = {60, 100, 120};   // Values of items
    int wt[]  = {10, 20, 30};     // Weights of items
    int W = 50;                   // Capacity of knapsack
    int n = sizeof(val)/sizeof(val[0]);

    int maxValue = knapsack(W, wt, val, n, 0);
    printf("Maximum value in Knapsack = %d\n", maxValue);
    return 0;
}
