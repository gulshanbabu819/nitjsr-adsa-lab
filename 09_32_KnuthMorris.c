#include <stdio.h>
#include <string.h>

// Function to compute the Longest Prefix Suffix (LPS) array
void computeLPSArray(char* pattern, int M, int* lps) {
    int len = 0;  // length of the previous longest prefix suffix
    lps[0] = 0;   // lps[0] is always 0

    int i = 1;
    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
                // Don't increment i here
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP search function
void KMPSearch(char* pattern, char* text) {
    int M = strlen(pattern);
    int N = strlen(text);

    // Create lps[] that will hold the longest prefix suffix values
    int lps[M];

    // Preprocess the pattern
    computeLPSArray(pattern, M, lps);

    int i = 0; // index for text[]
    int j = 0; // index for pattern[]

    while (i < N) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == M) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1]; // Continue searching for next matches
        } else if (i < N && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

// Driver code
int main() {
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABABCABAB";
    KMPSearch(pattern, text);
    return 0;
}
