#include <stdio.h>
#include "deque.h"

int main(void) {
    /* make_deque test */
    printf("Make empty deque with 2 nodes\n");
    deque *orders = interactive_input(2);

    printf("\nCurrent state:\n");
    print(orders);

    printf("This deque is %s", (is_empty(orders)) ? "empty\n" : "not empty\n");

    printf("Customer %s ordered %i items\n", orders->customer_name, orders_per_name(orders, orders->customer_name));

    printf("\n");

    /* push_back test */
    printf("Pushing node to back\n");
    push_back(orders, init(3, 2097149, "Mike Lubinets"));

    printf("\nCurrent state:\n");
    print(orders);

    /* push_front test */
    printf("Pushing node to front\n");
    push_front(orders, init(1, 9125270, "Marina Shamis"));

    printf("\nCurrent state:\n");
    print(orders);


    deque* poped;
    /* pop_back test */
    printf("Poping node from back\n");
    poped = pop_back(orders);

    printf("Poped one:\n");
    print_node(poped);

    printf("\nCurrent state:\n");
    print(orders);

    /* pop_front test */
    printf("Poping node from front\n");
    poped = pop_front(orders);
    printf("Poped one:\n");
    print_node(poped);

    printf("\nCurrent state:\n");
    print(orders);

    /* clean test */
    clean();
    printf("Clean deque\n");

    printf("\nCurrent state:\n");
    print(orders);
    printf("This deque is %s", (is_empty(orders)) ? "empty\n" : "not empty\n");

    return 0;
}

