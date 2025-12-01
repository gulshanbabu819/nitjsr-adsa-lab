#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POINTS 1000

typedef struct Point {
    int x, y;
} Point;

Point p0; // Reference point for sorting

// Function to swap two points
void swap(Point* a, Point* b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

// Function to return the square of distance between p1 and p2
int distSq(Point p1, Point p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) +
           (p1.y - p2.y)*(p1.y - p2.y);
}

// To find orientation of ordered triplet (p, q, r)
// Returns 0 -> colinear, 1 -> clockwise, 2 -> counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;           // colinear
    return (val > 0) ? 1 : 2;         // 1 -> clockwise, 2 -> counterclockwise
}

// Compare function for qsort
int compare(const void* vp1, const void* vp2) {
    Point* p1 = (Point*)vp1;
    Point* p2 = (Point*)vp2;

    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return distSq(p0, *p2) >= distSq(p0, *p1) ? -1 : 1;

    return (o == 2) ? -1 : 1;
}

// Prints convex hull of a set of n points
void convexHull(Point points[], int n) {
    // Find the bottom-most point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;

        // Pick the bottom-most or left-most if tie
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) {
            ymin = points[i].y;
            min = i;
        }
    }

    // Place the bottom-most point at first position
    swap(&points[0], &points[min]);
    p0 = points[0];

    // Sort the remaining points based on polar angle with p0
    qsort(&points[1], n - 1, sizeof(Point), compare);

    // If two or more points make same angle with p0, keep only farthest
    int m = 1; // Initialize size of modified array
    for (int i = 1; i < n; i++) {
        // Keep removing i while angle of i and i+1 is same
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;
        points[m++] = points[i];
    }

    if (m < 3) {
        printf("Convex hull not possible\n");
        return;
    }

    // Create a stack and push first three points
    Point stack[MAX_POINTS];
    int top = 0;
    stack[top++] = points[0];
    stack[top++] = points[1];
    stack[top++] = points[2];

    // Process remaining points
    for (int i = 3; i < m; i++) {
        // Keep removing top while the angle formed by
        // points next-to-top, top, and points[i] makes
        // a non-left turn (i.e., not counterclockwise)
        while (top >= 2 && orientation(stack[top - 2], stack[top - 1], points[i]) != 2)
            top--;
        stack[top++] = points[i];
    }

    // Print the convex hull
    printf("Convex Hull:\n");
    for (int i = 0; i < top; i++)
        printf("(%d, %d)\n", stack[i].x, stack[i].y);
}

// Driver code
int main() {
    int n;
    Point points[MAX_POINTS];

    printf("Enter number of points: ");
    scanf("%d", &n);

    if (n < 3) {
        printf("Convex hull not possible with less than 3 points.\n");
        return 0;
    }

    printf("Enter the coordinates (x y) of %d points:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &points[i].x, &points[i].y);
    }

    convexHull(points, n);
    return 0;
}
