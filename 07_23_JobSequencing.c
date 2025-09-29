#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a job
typedef struct Job {
    char id[10];
    int deadline;
    int profit;
} Job;

// Comparator function to sort jobs by descending profit
int compare(const void *a, const void *b) {
    Job *job1 = (Job *)a;
    Job *job2 = (Job *)b;
    return job2->profit - job1->profit;
}

// Function to find maximum deadline
int findMaxDeadline(Job jobs[], int n) {
    int max = jobs[0].deadline;
    for (int i = 1; i < n; i++) {
        if (jobs[i].deadline > max)
            max = jobs[i].deadline;
    }
    return max;
}

// Function to schedule jobs to maximize profit
void jobSequencing(Job jobs[], int n) {
    // Sort jobs by profit in descending order
    qsort(jobs, n, sizeof(Job), compare);

    int maxDeadline = findMaxDeadline(jobs, n);
    
    // Create time slots (0 means free)
    char schedule[maxDeadline + 1][10];
    int occupied[maxDeadline + 1];
    memset(occupied, 0, sizeof(occupied));

    int totalProfit = 0;

    printf("Scheduled Jobs: ");
    
    for (int i = 0; i < n; i++) {
        // Try to schedule job before or on its deadline
        for (int j = jobs[i].deadline; j > 0; j--) {
            if (!occupied[j]) {
                occupied[j] = 1;
                strcpy(schedule[j], jobs[i].id);
                totalProfit += jobs[i].profit;
                printf("%s ", jobs[i].id);
                break;
            }
        }
    }

    printf("\nTotal Profit: %d\n", totalProfit);
}

// Main function to test the algorithm
int main() {
    // Sample Jobs: {id, deadline, profit}
    Job jobs[] = {
        {"J1", 2, 100},
        {"J2", 1, 19},
        {"J3", 2, 27},
        {"J4", 1, 25},
        {"J5", 3, 15}
    };

    int n = sizeof(jobs) / sizeof(jobs[0]);

    jobSequencing(jobs, n);

    return 0;
}
