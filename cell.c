#ifndef CELL_C
#define CELL_C
#include "cell.h"
#include <stdlib.h>

t_sk_cell *create_cell(int val, int level) {
    t_sk_cell *cell = (t_sk_cell *)malloc(sizeof(t_sk_cell));
    cell->value = val;
    cell->level = level;
    cell->next = (t_sk_cell **)malloc((level + 1) * sizeof(t_sk_cell *));

    for (int i = 0; i <= level; i++) {
        cell->next[i] = NULL;
    }

    return cell;
}

void destroy_cell(t_sk_cell *cell) {
    free(cell->next);
    free(cell);
}

#endif
