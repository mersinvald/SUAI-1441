#include "deque.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

deque* interactive_input(int n){
    deque* root;

    int order_num;
    int customer_number;
    char customer_name[95];

    deque* prev_node = NULL;

    int i = 0;

    do {
        printf("Enter order number:\t");
        scanf("%i", &order_num);

        printf("Enter customer number:\t");
        scanf("%i", &customer_number);

        printf("Enter customer name:\t");

        do {
            fgets(customer_name, 95, stdin);
        } while(customer_name[0] == '\n');

        int len = strlen(customer_name);
        customer_name[len-1] = '\0';

        root = init(order_num, customer_number, customer_name);
        root->prev = prev_node;

        if(prev_node != NULL) prev_node->next = root;

        prev_node = root;
        root = root->next;

        i++;
    } while(i < n);

    return front(prev_node);
}

deque* init(int order_num, int customer_number, char *customer_name){
    deque* node = malloc(sizeof (deque));
    node->order_num = order_num;
    node->customer_number = customer_number;
    strcpy(node->customer_name, customer_name);

    if(strlen(node->customer_name) >= 1)
        node->not_empty = 1;
    else
        node->not_empty = 0;

    if(active_nodes == NULL) active_count = 0;

    deque** temp = realloc(active_nodes, ++active_count * sizeof(deque*));
    assert(temp != NULL);
    active_nodes = temp;

    active_nodes[active_count - 1] = node;


    return node;
}

void push_back(deque *node, deque *new_node){
    deque* back_node = back(node);
    new_node->prev = back_node;
    back_node->next = new_node;
}

void push_front(deque *node, deque *new_node){
    deque* front_node = front(node);
    new_node->next = front_node;
    front_node->prev = new_node;
}

deque* pop_back(deque *node){
    if(size(node) <= 1) return NULL;
    deque* back_node = back(node);
    deque* not_very_back_node = back_node->prev;

    if(node == back_node) node = not_very_back_node;

    back_node->prev = NULL;
    not_very_back_node->next = NULL;

    return back_node;
}

deque* pop_front(deque *node){
    if(size(node) <= 1) return NULL;
    deque* front_node = front(node);
    deque* not_very_front_node = front_node->next;

    if(node == front_node) node = not_very_front_node;

    front_node->next = NULL;
    not_very_front_node->prev = NULL;

    return front_node;
}

int is_empty(deque *node){
    if(node == NULL) return 1;

    node = front(node);
    do {
        if(node->not_empty) return 0;
        node = node->next;
    } while(node != NULL);

    return 1;
}

int size(deque *node){
    int size = 0;

    node = front(node);
    do {
        if(node->not_empty){
            size++;
        }
        node = node->next;
    } while(node != NULL);
    return size;
}

void print(deque *node){
    node = front(node);
    do {
        if(node->not_empty){
            print_node(node);
            printf("\n");
        }
        node = node->next;
    } while(node != NULL);
}

void print_node(deque *node){
    printf("Order number:\t%li\n", node->order_num);
    printf("Customer name:\t%s\n", node->customer_name);
    printf("Customer number: %li\n", node->customer_number);
}

deque* front(deque *node) {
    while(node->prev != NULL){
        node = node->prev;
    }
    return node;
}

//"Съешь еще этих мягких французских булок   ";

deque* back(deque *node){
    while(node->next != NULL){
        node = node->next;
    }
    return node;
}

void clean() {
    deque* n;
    int i;
    for(i = 0; i < active_count; i++){
        n = active_nodes[i];
        n->next = NULL;
        n->prev = NULL;
        n->not_empty = 0;
        free(n);

        n = NULL;
    }

    free(active_nodes);
    active_nodes = NULL;
    active_count = 0;
}

int orders_per_name(deque *node, char *name){
    int count = 0;

    node = front(node);
    do {
        if(node->not_empty && !strcmp(node->customer_name, name)){
            count++;
        }
        node = node->next;
    } while(node != NULL);
    return count;
}
