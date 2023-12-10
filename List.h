#ifndef LIST_H
#define LIST_H

#include "cell.h"


typedef struct s_sk_list{
    t_sk_cell ** heads;
    int max_level;
}t_sk_list;


t_sk_list *create_list(int max_level);
void destroy_list(t_sk_list *list);
void add_head(t_sk_list *list, t_sk_cell *cell);
void display_level(t_sk_list *list, int level);
void display_list(t_sk_list *list);
void display_aligned_list(t_sk_list *list);
void insert_tri(t_sk_list *list, t_sk_cell *mycell);



t_sk_cell *search_level0(t_sk_list *, int);

t_sk_list *Createlist2(int);

t_sk_cell *search_all_levels(t_sk_list *mylist, int target);

#endif // LIST_H
