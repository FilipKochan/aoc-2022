#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define LETTERS_COUNT 52

ssize_t getPriority(char c) {
    assert(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));

    if (c <= 'Z') {
        return c - 'A' + 27;
    }

    return c - 'a' + 1;
}

ssize_t getIndex(char c) {
    return getPriority(c) - 1;
}

int main() {
    char *line = NULL;
    size_t cap = 0;
    ssize_t size = 0;
    ssize_t res = 0;
    ssize_t res2 = 0;
    ssize_t count = 0;
    short groups[3][LETTERS_COUNT] = { {0}, {0}, {0} };
    while ((size = getline(&line, &cap, stdin)) > 0) {
        size--; // for newline
        ssize_t compartment_size = size / 2;

        assert(size % 2 == 0);

        // part 1
        short appearancesFst[LETTERS_COUNT] = { 0 };
        short appearancesSnd[LETTERS_COUNT] = { 0 };

        for (ssize_t i = 0; i < compartment_size; i++) {
            char c1 = line[i];
            char c2 = line[i + compartment_size];
            ssize_t i1 = getIndex(c1);
            ssize_t i2 = getIndex(c2);
            appearancesFst[i1] = 1;
            appearancesSnd[i2] = 1;
        }

        for (ssize_t i = 0; i < LETTERS_COUNT; i++) {
            if (appearancesFst[i] && appearancesSnd[i]) {
                res += (i + 1);
                break;
            }
        }

        // part 2
        for (ssize_t i = 0; i < size; i++) {
            groups[count % 3][getIndex(line[i])] = 1;
        }

        count++;

        if (count > 0 && (count % 3 == 0)) {
            for (ssize_t i = 0; i < LETTERS_COUNT; i++) {
                if (groups[0][i] && groups[1][i] && groups[2][i]) {
                    res2 += (i + 1);
                    break;
                }
            }

            for (ssize_t i = 0; i < 3; i++) {
                for (ssize_t j = 0; j < LETTERS_COUNT; j++) {
                    groups[i][j] = 0;
                }
            }
        }

    }

    assert(count % 3 == 0);
    for (ssize_t i = 0; i < LETTERS_COUNT; i++) {
        if (groups[0][i] &&groups[1][i] && groups[2][i]) {
            res2 += (i + 1);
            break;
        }
    }

    free(line);
    printf("part 1: %zu\npart 2: %zu\n", res, res2);
    return 0;
}
