/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 05:13:40 by sciftci           #+#    #+#             */
/*   Updated: 2022/10/14 11:47:49 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Returns highest order in stack.
*/
static int	find_highest_order(t_stack *stack)
{
	int	order;

	order = stack->order;
	while (stack)
	{
		if (stack->order > order)
			order = stack->order;
		stack = stack->next;
	}
	return (order);
}

/*
** Sorts a stack of 3 numbers in 2 or fewer moves. 
** Sorting is done by index rather than value.
*/
void	sort_three(t_stack **stack)
{
	int	highest;

	if (is_sorted(*stack))
		return ;
	highest = find_highest_order(*stack);
	if ((*stack)->order == highest)
		rotate(stack, NULL, "ra", 0);
	else if ((*stack)->next->order == highest)
		rev_rotate(stack, NULL, "rra", 0);
	if ((*stack)->order > (*stack)->next->order)
		swap(stack, NULL, "sa", 0);
}

/*
** Pushes all elements of stack_a into stack_b, except three last ones.
** Pushes smaller values first and then larger values.
*/
static void	push_all_but_three(t_stack **stack_a, t_stack **stack_b)
{
	int	stack_size;
	int	pushed;
	int	i;

	stack_size = get_stack_size(*stack_a);
	pushed = 0;
	i = 0;
	while (stack_size > 6 && i < stack_size && pushed < stack_size / 2)
	{
		if ((*stack_a)->order <= stack_size / 2)
		{
			push(stack_a, stack_b, "pb");
			pushed++;
		}
		else
			rotate(stack_a, NULL, "ra", 0);
		i++;
	}
	while (stack_size - pushed > 3)
	{
		push(stack_a, stack_b, "pb");
		pushed++;
	}
}

/*
** After the bulk of the stacj is sorted, shifts stack_a until
** lowest value is at the top. If it is int the bottom half of
** stack, rev_rotate otherwise rotate.
*/
static void	rotate_sort(t_stack **stack_a)
{
	int	lowest_index;
	int	stack_size;

	stack_size = get_stack_size(*stack_a);
	lowest_index = get_lowest_order_index(stack_a);
	if (lowest_index > stack_size / 2)
	{
		while (lowest_index++ < stack_size)
			rev_rotate(stack_a, NULL, "rra", 0);
	}
	else
	{
		while (lowest_index-- > 0)
			rotate(stack_a, NULL, "ra", 0);
	}
}

/*
**	Sorting algorithm for a stack larger than 3.
**	Push everything but 3 numbers to stack_b.
**	Sort the 3 numbers left in stack_a.
**	Calculate and do the most cheapest move.
**	Shift elements until stack_a is in order.
*/
void	sort(t_stack **stack_a, t_stack **stack_b)
{
	push_all_but_three(stack_a, stack_b);
	sort_three(stack_a);
	while (*stack_b)
	{
		assign_target_index(stack_a, stack_b);
		get_cost(stack_a, stack_b);
		move_cheapest(stack_a, stack_b);
	}
	if (!is_sorted(*stack_a))
		rotate_sort(stack_a);
}
