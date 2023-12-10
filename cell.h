#ifndef UNTITLED5_STRUCT_H
#define UNTITLED5_STRUCT_H
#define MAX_NAME_LENGTH 50



typedef struct s_sk_cell {
    int value;
    int level;
    char name[MAX_NAME_LENGTH]; // Adding the name_surname field
    struct s_sk_cell **next;
} t_sk_cell;

t_sk_cell *create_cell(int val, int level);
void destroy_cell(t_sk_cell *cell);

#endif //UNTITLED5_STRUCT_H
