#include "push_swap.h"

void	exit_error(t_stack **stack_a, t_stack **stack_b)
{
	free_stack(stack_a);
	free_stack(stack_b);
	write(2, "Error\n", 6);
	exit(1);
}

int main(int ac, char **av)
{
    t_stack		*stack_a;
    t_stack     *stack_b;
    char        *inst;

    if (ac < 2)
		return (0);
	if (!is_valid_input(av))
		exit_error(NULL, NULL);
	stack_a = fill_stack_a(ac, av);
    stack_b = NULL;

    //read instructions \n
    //check instructions valid otherwise give error
    // an instruction doesn’t exist and/or
    //   is incorrectly formatted.

    exit_error(NULL, NULL);

    inst = get_next_line(); 
    // execute instructions if they valid

        


    if (is_sorted(stack_a) && get_stack_size(stack_b) == 0)
        ft_putstr("OK\n");
    else
        ft_putstr("KO\n");
    free_stack(&stack_a);
    free_stack(&stack_b);
    return (0);
}