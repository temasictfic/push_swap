/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:44:50 by sciftci           #+#    #+#             */
/*   Updated: 2022/10/11 03:55:11 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**		value:		 3	 0	 9	 1
**		order:		[3]	[1]	[4]	[2]
**		index:		<0>	<1>	<2>	<3>
*/
static void	get_index(t_stack **stack)
{
	t_stack	*tmp;
	int		i;

	tmp = *stack;
	i = 0;
	while (tmp)
	{
		tmp->index = i;
		tmp = tmp->next;
		i++;
	}
}

/*
** gets index of lowest order element
*/
int	get_lowest_order_index(t_stack **stack)
{
	t_stack	*tmp;
	int		lowest_order;
	int		lowest_index;

	tmp = *stack;
	lowest_order = INT_MAX;
	get_index(stack);
	lowest_index = tmp->index;
	while (tmp)
	{
		if (tmp->order < lowest_order)
		{
			lowest_order = tmp->order;
			lowest_index = tmp->index;
		}
		tmp = tmp->next;
	}
	return (lowest_index);
}

static int	get_target_index(t_stack **stack_a, int b_order, int target_order,
		int target_index)
{
	t_stack	*tmp_a;

	tmp_a = *stack_a;
	while (tmp_a)
	{
		if (tmp_a->order > b_order && tmp_a->order < target_order)
		{
			target_order = tmp_a->order;
			target_index = tmp_a->index;
		}
		tmp_a = tmp_a->next;
	}
	if (target_order != INT_MAX)
		return (target_index);
	tmp_a = *stack_a;
	while (tmp_a)
	{
		if (tmp_a->order < target_order)
		{
			target_order = tmp_a->order;
			target_index = tmp_a->index;
		}
		tmp_a = tmp_a->next;
	}
	return (target_index);
}

void	assign_target_index(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp_b;
	int		target_index;

	tmp_b = *stack_b;
	get_index(stack_a);
	get_index(stack_b);
	target_index = 0;
	while (tmp_b)
	{
		target_index = get_target_index(stack_a, tmp_b->order, INT_MAX,
				target_index);
		tmp_b->target_index = target_index;
		tmp_b = tmp_b->next;
	}
}
