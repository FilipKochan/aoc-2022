#include <stdio.h>
#include <stdlib.h>

void append_crate(char **crates_row, char elem, size_t *sz, size_t *cap)
{
    if ((*sz) + 1 > (*cap)) {
        (*cap) *= 2;
        char *tmp = realloc(*crates_row, *cap);
        if (tmp == NULL) {
            exit(1);
        }
        (*crates_row) = tmp;
    }
    (*crates_row)[(*sz)++] = elem;
}

int main()
{
    char **crates = NULL;
    char **crates_pt2 = NULL;
    size_t *crates_sz_pt2 = NULL;
    size_t *crates_cap_pt2 = NULL;
    size_t *crates_sz = NULL;
    size_t *crates_cap = NULL;
    size_t crates_size = 0;

    char *line = NULL;
    size_t cap;

    ssize_t size;
    while ((size = getline(&line, &cap, stdin)) > 1) {
        size--;
        if (crates == NULL) {
            crates_size = (size + 1) / 4,

            crates = calloc(crates_size, sizeof(void *));
            crates_pt2 = calloc(crates_size, sizeof(void *));

            crates_cap = calloc(crates_size, sizeof(void *));
            crates_cap_pt2 = calloc(crates_size, sizeof(void *));

            crates_sz = calloc(crates_size, sizeof(void *));
            crates_sz_pt2 = calloc(crates_size, sizeof(void *));

            for (size_t i = 0; i < crates_size; i++) {
                crates[i] = calloc(1, sizeof(void *));
                crates_pt2[i] = calloc(1, sizeof(void *));

                crates_sz[i] = 0;
                crates_sz_pt2[i] = 0;

                crates_cap[i] = 1;
                crates_cap_pt2[i] = 1;
            }
        }

        for (size_t i = 0; i < crates_size; i++) {
            char c = line[1 + i * 4];
            if ('1' <= c && c <= '9') {
                break;
            }
            if (c == ' ') {
                continue;
            }

            append_crate(crates + i, c, crates_sz + i, crates_cap + i);
            append_crate(crates_pt2 + i, c, crates_sz_pt2 + i, crates_cap_pt2 + i);
        }
    }

    for (size_t i = 0; i < crates_size; i++) {
        for (size_t j = 0; j < (crates_sz[i]) / 2; j++) {
            char tmp = crates[i][j];
            crates[i][j] = crates[i][crates_sz[i] - j - 1];
            crates[i][crates_sz[i] - j - 1] = tmp;
        }
        for (size_t j = 0; j < crates_sz_pt2[i]; j++) {
            crates_pt2[i][j] = crates[i][j];
        }
    }

    size_t amount, from, to;
    while (scanf("move %zu from %zu to %zu\n", &amount, &from, &to) == 3) {
        from--; to--;
        char chunk[amount + 1];
        chunk[amount] = 0;
        while (amount--) {
            char c = crates[from][crates_sz[from]-- - 1];
            crates[from][crates_sz[from]] = '\0';

            char c2 = crates_pt2[from][crates_sz_pt2[from]-- - 1];
            crates_pt2[from][crates_sz_pt2[from]] = '\0';

            chunk[amount] = c2;
            append_crate(crates + to, c, crates_sz + to, crates_cap + to);
        }

        while (chunk[++amount]) {
            append_crate(crates_pt2 + to, chunk[amount], crates_sz_pt2 + to, crates_cap_pt2 + to);
        }
    }


    printf("part 1: ");
    for (size_t i = 0; i < crates_size; i++) {
        printf("%c", crates[i][crates_sz[i] - 1]);
    }
    printf("\npart 2: ");
    for (size_t i = 0; i < crates_size; i++) {
        printf("%c", crates_pt2[i][crates_sz_pt2[i] - 1]);
    }
    printf("\n");
    for (size_t i = 0; i < crates_size; i++) {
        free(crates[i]);
        free(crates_pt2[i]);
    }

    free(crates);
    free(crates_pt2);
    free(crates_sz);
    free(crates_sz_pt2);
    free(crates_cap);
    free(crates_cap_pt2);
    free(line);

    return 0;
}
