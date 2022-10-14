/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:44:50 by sciftci           #+#    #+#             */
/*   Updated: 2022/10/14 12:00:29 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*  leftmost is top (value 3)
**		value:			3	 0	 9	 1
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

/*
**	Picks the best target_index in stack_a for the given order of
**	an element in stack_b. First checks if the order of stack_b element can
**	be placed somewhere in between elements in stack_a, by checking whether
**	there is an element in stack_a with a bigger order. If not, it finds the
**	element with the smallest order in stack_a and assigns that 
**	as the target_index.
**	--- Example:
**		target_index starts at INT_MAX
**		B order: 3
**		A contains orders: 9 4 2 1 0
**		9 > 3 && 9 < INT_MAX 	: target_index updated to 9
**		4 > 3 && 4 < 9 			: target_index updated to 4
**		2 < 3 && 2 < 4			: no update!
**	So target_index needs to be the index of order 4, since it is
**	the closest order.
**	--- Example:
**		target_index starts at INT_MAX
**		B order: 20
**		A contains orders: 16 4 3
**		16 < 20					: no update! target_index = INT_MAX
**		4  < 20					: no update! target_index = INT_MAX
**		3  < 20					: no update! target_index = INT_MAX
**	... target_index stays at INT MAX, need to switch strategies.
**		16 < 20					: target_index updated to 20
**		4  < 20					: target_index updated to 4
**		3  < 20					: target_index updated to 3
**	So target_index needs to be the index of order 3, since that is
**	the "end" of the stack.
*/
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

/*
** Assigns a target position in stack_a to each element of stack_a
*/
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
