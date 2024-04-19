#include <stdio.h>
#include <string.h>

void getZarr(char *string, int *z) {
    int n = strlen(string);
    int l = 0, r = 0, k = 0;
    for (int i = 1; i < n; i++) {
        if (i > r) {
            l = r = i;
            while (r < n && string[r - l] == string[r]) {
                r++;
            }
            z[i] = r - l;
            r--;
        } else {
            k = i - l;
            if (z[k] < r - i + 1) {
                z[i] = z[k];
            } else {
                l = i;
                while (r < n && string[r - l] == string[r]) {
                    r++;
                }
                z[i] = r - l;
                r--;
            }
        }
    }
}

void search(char *text, char *pattern) {
    int text_len = strlen(text);
    int pattern_len = strlen(pattern);
    char concat[text_len + pattern_len + 2];
    strcpy(concat, pattern);
    strcat(concat, "$");
    strcat(concat, text);
    int l = strlen(concat);

    int z[l];
    getZarr(concat, z);

    for (int i = 0; i < l; i++) {
        if (z[i] == pattern_len) {
            printf("Pattern found at index %d\n", i - pattern_len - 1);
        }
    }
}

int main() {
    char file_path[100];
    printf("Enter the path to the file containing both text and pattern: ");
    scanf("%s", file_path);

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("File not found. Please check the file path.\n");
        return 1;
    }

    char text[1000], pattern[1000];
    fscanf(file, "%s", text);
    fscanf(file, "%s", pattern);
    fclose(file);

    search(text, pattern);

    return 0;
}
