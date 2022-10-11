#include "push_swap.h"
#include "stdio.h"
int main()
{
    t_stack *stack_a;
    t_stack *stack_b;
    stack_a = stack_new(2);
    stack_add_bottom(&stack_a, stack_new(1));
    stack_add_bottom(&stack_a, stack_new(0));

    stack_b = stack_new(4);
    stack_add_bottom(&stack_b, stack_new(3));
    stack_add_bottom(&stack_b, stack_new(5));

    //rev_rotate(&stack_b, &stack_a, "rrb", 0);
    //swap(&stack_b, &stack_a, "sb", 0);
    //push(&stack_b, &stack_a, "pa");
    printf("%d  %d\n", stack_a->value, stack_b->value);
    printf("%d  %d\n", stack_a->next->value, stack_b->next->value);
    //printf("%d  %d\n", stack_a->next->next->value, stack_b->next->next->value);

}