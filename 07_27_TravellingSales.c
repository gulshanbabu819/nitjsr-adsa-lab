#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX 20  // max size supported by DP TSP

int dp[1 << MAX][MAX];
int dist[MAX][MAX];
int n;

// TSP using DP + Bitmask
int tsp(int mask, int pos) {
    if (mask == (1 << n) - 1) {
        return dist[pos][0];  // return to start
    }
    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int ans = INT_MAX;
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) {
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city);
            if (newAns < ans)
                ans = newAns;
        }
    }
    return dp[mask][pos] = ans;
}

// Generate random distance matrix with values 1 to 100
void generateRandomGraph(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = rand() % 100 + 1;
        }
    }
}

// Measure time taken to solve TSP for given graph size
double measureTSPTime(int size) {
    n = size;
    generateRandomGraph(n);

    // Initialize DP table
    int limit = 1 << n;
    for (int i = 0; i < limit; i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = -1;

    clock_t start = clock();
    int ans = tsp(1, 0);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Size: %d, TSP cost: %d, Time: %f seconds\n", size, ans, time_spent);

    return time_spent;
}

int main() {
    srand(time(NULL));

    int sizes[] = {10, 20, 40, 60, 100};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("TSP Running Time Table (problem size vs execution time):\n");
    printf("Size\tTime(s)\n");

    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];

        if (size <= MAX) {
            // Exact DP TSP run
            double t = measureTSPTime(size);
            printf("%d\t%f\n", size, t);
        } else {
            // For large sizes, skip exact and estimate
            // Estimate time assuming O(n^2 * 2^n), just to illustrate growth
            // We'll use time for size=20 as base and extrapolate
            double base_time = 1.0; // placeholder seconds for size=20

            // Calculate scale factor: (size^2 * 2^size) / (20^2 * 2^20)
            double scale = ((double)(size * size) * (1LL << size)) / ((20.0 * 20.0) * (1LL << 20));

            // Print estimated time
            printf("%d\t%f (estimated, skipped exact computation)\n", size, base_time * scale);
        }
    }

    return 0;
}
