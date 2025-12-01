#include <stdio.h>
#include <string.h>
#define NO_OF_CHARS 256

// Function to create the bad character heuristic table
void badCharHeuristic(char *pattern, int size, int badchar[NO_OF_CHARS]) {
    int i;

    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    // Fill the actual value of last occurrence
    for (i = 0; i < size; i++)
        badchar[(unsigned char) pattern[i]] = i;
}

// Boyer-Moore search function using Bad Character Heuristic
void boyerMooreSearch(char *text, char *pattern) {
    int m = strlen(pattern);
    int n = strlen(text);

    int badchar[NO_OF_CHARS];

    // Fill the bad character array by calling preprocessing function
    badCharHeuristic(pattern, m, badchar);

    int s = 0; // s is the shift of the pattern with respect to text
    while (s <= (n - m)) {
        int j = m - 1;

        // Keep reducing index j while characters of pattern and text are matching
        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        // If pattern is present at current shift
        if (j < 0) {
            printf("Pattern found at index %d\n", s);

            // Shift pattern so that the next character in text aligns with the last occurrence in pattern
            s += (s + m < n) ? m - badchar[(unsigned char)text[s + m]] : 1;
        } else {
            // Shift pattern so that the bad character in text aligns with the last occurrence in pattern
            int shift = j - badchar[(unsigned char)text[s + j]];
            s += (shift > 1) ? shift : 1;
        }
    }
}

// Driver code
int main() {
    char text[] = "ABAAABCDABC";
    char pattern[] = "ABC";
    boyerMooreSearch(text, pattern);
    return 0;
}
