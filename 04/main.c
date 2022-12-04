#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t res1 = 0, res2 = 0;
    char *line = NULL;
    int s1,e1,s2,e2;
    while (scanf("%d-%d,%d-%d", &s1,&e1,&s2,&e2) > 0) {
        if (((s1 <= s2) && (e2 <= e1)) || ((s1 >= s2) && (e2 >= e1))) {
            res1++;
        }

        if ((s2 <= e1 && e1 <= e2) || (s1 <= e2 && e2 <= e1)) {
            res2++;
        }
    }
    free(line);
    printf("part 1: %zu\npart 2: %zu\n", res1, res2);
    return 0;
}
