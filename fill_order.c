/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_order.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:23:39 by sciftci           #+#    #+#             */
/*   Updated: 2022/10/13 18:52:50 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exit_error(t_stack **stack_a, t_stack **stack_b)
{
	free_stack(stack_a);
	free_stack(stack_b);
	write(2, "Error\n", 6);
	exit(1);
}

/*
** Fill stack_a with arg values
** Values should be int
*/
t_stack	*fill_stack_a(int ac, char **av)
{
	t_stack		*stack_a;
	long int	num;
	int			i;

	stack_a = NULL;
	num = 0;
	i = 1;
	while (i < ac)
	{
		num = ft_atoi(av[i]);
		if (num > INT_MAX || num < INT_MIN)
			exit_error(&stack_a, NULL);
		if (i == 1)
			stack_a = stack_new((int)num);
		else
			stack_add_bottom(&stack_a, stack_new((int)num));
		i++;
	}
	return (stack_a);
}

/*
** Assign an number to each value in stack_a
** Lowast gets 1 and highest gets stack_size
**		values:		-3		0		9	 2
**		order:		[1]	[2]	[4]	[3]
*/
void	assign_order(t_stack *stack_a, int stack_size)
{
	t_stack	*ptr;
	t_stack	*highest;
	int		value;

	while (--stack_size > 0)
	{
		ptr = stack_a;
		value = INT_MIN;
		highest = NULL;
		while (ptr)
		{
			if (ptr->value == INT_MIN && ptr->order == 0)
				ptr->order = 1;
			if (ptr->value > value && ptr->order == 0)
			{
				value = ptr->value;
				highest = ptr;
				ptr = stack_a;
			}
			else
				ptr = ptr->next;
		}
		if (highest != NULL)
			highest->order = stack_size;
	}
}
