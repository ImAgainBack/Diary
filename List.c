#include "List.h"
#include "cell.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

t_sk_list *create_list(int max_level) {
    t_sk_list *list = (t_sk_list *)malloc(sizeof(t_sk_list));
    list->max_level = max_level;
    list->heads = (t_sk_cell **)malloc(max_level * sizeof(t_sk_cell *));

    for (int i = 0; i < max_level; i++) {
        list->heads[i] = NULL;
    }

    return list;
}

void destroy_list(t_sk_list *list) {
    free(list->heads);
    free(list);
}

void add_head(t_sk_list *list, t_sk_cell *cell) {
    cell->next[cell->level] = list->heads[cell->level];
    list->heads[cell->level] = cell;
}

void display_level(t_sk_list *list, int level) {
    printf("[List head %d @-]-->", level);
    t_sk_cell *current = list->heads[level];

    while (current != NULL) {
        printf(" [%d⎪@] -->", current->value);
        current = current->next[level];
    }

    printf(" NULL\n");
}

void display_list(t_sk_list *list) {
    for (int i = 0; i < list->max_level; i++) {
        display_level(list, i);
    }
}

void display_aligned_list(t_sk_list *list) {
    int max_level = list->max_level;

    for (int i = 0; i < max_level; ++i) {
        t_sk_cell *current = list->heads[i];
        printf("[List head %d @-]", i);

        t_sk_cell *ref = list->heads[0]; // Reference for the comparaison 

        while (ref != NULL) {

            if (current == NULL || current->value != ref->value) {
                printf("---------");
            } else {
                printf("--->[%d⎪@]", current->value);
                current = current->next[i];
            }
            ref = ref->next[0]; // Goes to the next cell of the first level
        }

        printf("---> NULL\n");
    }
}

void insert_tri(t_sk_list *mylist, t_sk_cell *newcell) {
    for (int i = 0; i <= newcell->level; ++i) {
        t_sk_cell* t1_cell = mylist->heads[i];
        t_sk_cell* t2_cell = NULL;

        while ((t1_cell != NULL) && (newcell->value > t1_cell->value)) {
            t2_cell = t1_cell;
            t1_cell = t1_cell->next[i];
        }

        newcell->next[i] = t1_cell;
        if (t2_cell != NULL) {
            t2_cell->next[i] = newcell;
        } else {
            mylist->heads[i] = newcell;
        }
    }
}


t_sk_list *Createlist2(int n) {
    t_sk_list *mylist = create_list(n);
    int max_val = (1 << n) - 1; 

    for (int level = n; level >= 0; level--) {
        int val = (1 << level); // starts with the highest level

        while (val <= max_val) {
            insert_tri(mylist, create_cell(val, level));
            val += (1 << (level + 1)); // goes to the next cell of the level
        }
    }

    display_aligned_list(mylist);
    return mylist;
}


t_sk_cell* search_level0(t_sk_list* mylist, int chiffre) {
    t_sk_cell* current = mylist->heads[0];

    while (current != NULL && current->value < chiffre) {
        current = current->next[0];
    }

    if (current != NULL && current->value == chiffre) {
        printf("%d found at level 0\n", current->value);
        return current;
    } else {
        printf("%d not found at level 0\n", chiffre);
        return NULL;
    }
}

t_sk_cell* search_all_levels(t_sk_list* mylist, int target) {
  int max_level = mylist->max_level;

  for (int i = max_level - 1; i >= 0; --i) {
    t_sk_cell* current = mylist->heads[i];

    while (current != NULL && current->value < target) {
      current = current->next[i];
    }

    if (current != NULL && current->value == target) {
      printf("%d found at level %d\n", current->value, i);
      return current;
    }
  }

  printf("%d not found in any level\n", target);
  return NULL;
}

