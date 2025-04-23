#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_highlighted(const char *line, const char *pattern) {
    const char *start = line;
    const char *match;

    while ((match = strstr(start, pattern)) != NULL) {
        printf("%.*s", (int)(match - start), start);
        printf("\033[1;31m%s\033[0m", pattern);

        start = match + strlen(pattern);
    }
    printf("%s", start);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pattern> <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *pattern = argv[1];
    const char *filename = argv[2];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[1000];
    int line_number = 1;
    printf("Searching for pattern '%s' in file '%s'...\n", pattern, filename);

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, pattern)) {
            printf("Line %d: ", line_number);
            print_highlighted(line, pattern);
        }
        line_number++;
    }

    fclose(file);
    return 0;
}