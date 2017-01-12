#ifndef DEQUE_H
#define DEQUE_H
#include <stdlib.h>

struct deque_s {
    long order_num;        /* 8 bytes */
    long customer_number;  /* 8 bytes */

    struct deque_s *prev; /* 8 bytes */
    struct deque_s *next; /* 8 bytes */
    /* 32 bytes */

    char customer_name[95];
    char not_empty;

    /* 128 bytes == 1/32 mempage size */
};

typedef struct deque_s deque;

deque** active_nodes;
int     active_count;

/*
 * Makes new deque contains n nodes
 * returns pointer to the front node of new deque
 */
extern deque* interactive_input(int n);

/* makes new node */
extern deque* init(int order_num, int customer_number, char* customer_name);

/* Common double ended list functions */
extern void push_back(deque *node, deque *new_node);
extern void push_front(deque *node, deque *new_node);
extern deque* pop_back(deque *node);
extern deque* pop_front(deque *node);
extern int  is_empty(deque *node);
extern int  size(deque *node);

/* Prints contents of all nodes */
extern void print(deque *node);

/* print contents of one node */
extern void print_node(deque *node);

extern int orders_per_name(deque *node, char* name);

/* Returns pointers to approptiate nodes */
extern deque* front(deque *node);
extern deque* back(deque *node);

extern void clean();

#endif // DEQUE_H
