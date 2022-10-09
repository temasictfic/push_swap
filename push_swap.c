/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 22:15:32 by sciftci           #+#    #+#             */
/*   Updated: 2022/10/09 22:15:32 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exit_error(t_stack **stack_a, t_stack **stack_b)
{
	free_stack(stack_a);
	free_stack(stack_b);
	write(2, "Error\n", 6);
	exit (1);
}

static void	push_swap(t_stack **stack_a, t_stack **stack_b, int stack_size)
{
	if (stack_size == 2 && !is_sorted(*stack_a))
		swap(stack_a, NULL, "sa", 0);
	else if (stack_size == 3)
		sort_three(stack_a);
	else if (stack_size > 3 && !is_sorted(*stack_a))
		sort(stack_a, stack_b);
}

int main(int ac, char **av)
{
    t_stack *stack_a;
    t_stack *stack_b;
    int stack_size;

    if (ac<2)
        return(0);
    if(!is_valid_input(av))
        exit_error(NULL,NULL);
    
    stack_a = fill_stack_a(ac, av);
    stack_b = NULL;
    stack_size = get_stack_size(stack_a);
    assign_order(stack_a, stack_size + 1);
    push_swap(&stack_a, &stack_b, stack_size);
    free_stack(&stack_a);
    free_stack(&stack_b);
    return(0);
}