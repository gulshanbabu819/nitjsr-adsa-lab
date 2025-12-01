#include <stdio.h>
#include <string.h>
#define d 256  // Number of characters in the input alphabet (ASCII)

// Rabin-Karp function to search for a pattern in a text
void rabinKarp(char text[], char pattern[], int q) {
    int M = strlen(pattern);
    int N = strlen(text);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for text
    int h = 1;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and first window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++) {
        // Check the hash values of current window of text and pattern
        if (p == t) {
            // If hash values match, check characters one by one
            for (j = 0; j < M; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }

            // If pattern is found
            if (j == M)
                printf("Pattern found at index %d\n", i);
        }

        // Calculate hash value for next window of text
        if (i < N - M) {
            t = (d * (t - text[i] * h) + text[i + M]) % q;

            // We might get negative value of t, converting it to positive
            if (t < 0)
                t = (t + q);
        }
    }
}

int main() {
    char text[] = "ABCCDDAEFG";
    char pattern[] = "CDD";
    
    // A prime number for modulo
    int q = 101;

    rabinKarp(text, pattern, q);

    return 0;
}
