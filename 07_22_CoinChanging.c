#include <stdio.h>

// Function to implement the greedy algorithm
void coinChangeGreedy(int coins[], int n, int amount) {
    printf("Coins used to make change for %d:\n", amount);
    
    for (int i = 0; i < n; i++) {
        while (amount >= coins[i]) {
            amount -= coins[i];
            printf("%d ", coins[i]);
        }
    }

    if (amount != 0) {
        printf("\nCannot make exact change with the given coin denominations.");
    }

    printf("\n");
}

int main() {
    // Example coin denominations (descending order for greedy)
    int coins[] = {25, 10, 5, 1};  // US coins
    int n = sizeof(coins) / sizeof(coins[0]);

    int amount;

    printf("Enter the amount to change: ");
    scanf("%d", &amount);

    coinChangeGreedy(coins, n, amount);

    return 0;
}
