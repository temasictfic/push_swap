/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 05:05:22 by sciftci           #+#    #+#             */
/*   Updated: 2022/10/14 11:03:34 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** cost_b and cost_a represent distance to top of stacks
** if element is in bottom half of stack, cost is negative
** otherwise positive
*/
void	get_cost(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp_a;
	t_stack	*tmp_b;
	int		size_a;
	int		size_b;

	tmp_a = *stack_a;
	tmp_b = *stack_b;
	size_a = get_stack_size(tmp_a);
	size_b = get_stack_size(tmp_b);
	while (tmp_b)
	{
		tmp_b->cost_b = tmp_b->index;
		if (tmp_b->index > size_b / 2)
			tmp_b->cost_b = tmp_b->index - size_b;
		tmp_b->cost_a = tmp_b->target_index;
		if (tmp_b->target_index > size_a / 2)
			tmp_b->cost_a = tmp_b->target_index - size_a;
		tmp_b = tmp_b->next;
	}
}

static void	rotate_both(t_stack **stack_a, t_stack **stack_b, int *cost_a,
		int *cost_b)
{
	while (*cost_a < 0 && *cost_b < 0)
	{
		(*cost_a)++;
		(*cost_b)++;
		rev_rotate(stack_a, stack_b, "rrr", 1);
	}
	while (*cost_a > 0 && *cost_b > 0)
	{
		(*cost_a)--;
		(*cost_b)--;
		rotate(stack_a, stack_b, "rr", 1);
	}
}

static void	rotate_one(t_stack **stack, int *cost, char *r, char *rr)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			rotate(stack, NULL, r, 0);
			(*cost)--;
		}
		else if (*cost < 0)
		{
			rev_rotate(stack, NULL, rr, 0);
			(*cost)++;
		}
	}
}

static void	move(t_stack **stack_a, t_stack **stack_b, int cost_a, int cost_b)
{
	rotate_both(stack_a, stack_b, &cost_a, &cost_b);
	rotate_one(stack_a, &cost_a, "ra", "rra");
	rotate_one(stack_b, &cost_b, "rb", "rrb");
	push(stack_b, stack_a, "pa");
}

/*
**  finds the element in stack_b with the cheapest cost to move to stack_a
**	and moves it to the correct position in stack_a
*/
void	move_cheapest(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp;
	int		cheapest;
	int		cost_a;
	int		cost_b;
	int		total_cost;

	tmp = *stack_b;
	cheapest = INT_MAX;
	while (tmp)
	{
		total_cost = ft_abs(tmp->cost_a) + ft_abs(tmp->cost_b);
		if (total_cost < cheapest)
		{
			cheapest = total_cost;
			cost_a = tmp->cost_a;
			cost_b = tmp->cost_b;
		}
		tmp = tmp->next;
	}
	move(stack_a, stack_b, cost_a, cost_b);
}
