#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getZarr(char *str, int Z[]);

// prints all occurrences of pattern in text using Z algo
void search(char *text, char *pattern) {
    // Create concatenated string "P$T"
    int textLen = strlen(text);
    int patternLen = strlen(pattern);
    int concatLen = textLen + patternLen + 1;
    char *concat = (char *)malloc(concatLen * sizeof(char));
    strcpy(concat, pattern);
    strcat(concat, "$");
    strcat(concat, text);

    // Construct Z array
    int *Z = (int *)malloc(concatLen * sizeof(int));
    getZarr(concat, Z);

    // now looping through Z array for matching condition
    for (int i = 0; i < concatLen; ++i) {
        // if Z[i] (matched region) is equal to pattern
        // length we got the pattern
        if (Z[i] == patternLen)
            printf("Pattern found at index %d\n", i - patternLen - 1);
    }

    free(concat);
    free(Z);
}

// Fills Z array for given string str[]
void getZarr(char *str, int Z[]) {
    int n = strlen(str);
    int L, R, k;

    // [L,R] make a window which matches with prefix of s
    L = R = 0;
    for (int i = 1; i < n; ++i) {
        // if i>R nothing matches so we will calculate.
        // Z[i] using naive way.
        if (i > R) {
            L = R = i;

            // R-L = 0 in starting, so it will start
            // checking from 0'th index. For example,
            // for "ababab" and i = 1, the value of R
            // remains 0 and Z[i] becomes 0. For string
            // "aaaaaa" and i = 1, Z[i] and R become 5
            while (R < n && str[R - L] == str[R])
                R++;
            Z[i] = R - L;
            R--;
        } else {
            // k = i-L so k corresponds to number which
            // matches in [L,R] interval.
            k = i - L;

            // if Z[k] is less than remaining interval
            // then Z[i] will be equal to Z[k].
            // For example, str = "ababab", i = 3, R = 5
            // and L = 2
            if (Z[k] < R - i + 1)
                Z[i] = Z[k];

            // For example str = "aaaaaa" and i = 2, R is 5,
            // L is 0
            else {
                // else start from R and check manually
                L = i;
                while (R < n && str[R - L] == str[R])
                    R++;
                Z[i] = R - L;
                R--;
            }
        }
    }
}

// Driver program
int main() {
    FILE *textFile = fopen("text.txt", "r");
    FILE *patternFile = fopen("pattern.txt", "r");

    if (!textFile || !patternFile) {
        printf("Error opening files.\n");
        return 1;
    }

    char text[1000], pattern[100];
    fgets(text, 1000, textFile);
    fgets(pattern, 100, patternFile);

    fclose(textFile);
    fclose(patternFile);

    // Remove newline characters
    text[strcspn(text, "\n")] = '\0';
    pattern[strcspn(pattern, "\n")] = '\0';

    search(text, pattern);
    return 0;
}

