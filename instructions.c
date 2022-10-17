/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 03:30:10 by sciftci           #+#    #+#             */
/*   Updated: 2022/10/14 01:05:44 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rev_rotate(t_stack **stack_a, t_stack **stack_b, char *cmd, int flag)
{
	t_stack	*tmp;
	t_stack	*tail;
	t_stack	*before_tail;

	if (get_stack_size(*stack_a) < 2)
		return ;
	tail = get_stack_bottom(*stack_a);
	before_tail = get_stack_before_bottom(*stack_a);
	tmp = *stack_a;
	*stack_a = tail;
	(*stack_a)->next = tmp;
	before_tail->next = NULL;
	if (flag)
		return (rev_rotate(stack_b, NULL, cmd, 0));
	if (cmd)
	{
		ft_putstr(cmd);
		ft_putstr("\n");
	}
}

void	rotate(t_stack **stack_a, t_stack **stack_b, char *cmd, int flag)
{
	t_stack	*tmp;
	t_stack	*tail;

	if (get_stack_size(*stack_a) < 2)
		return ;
	tmp = *stack_a;
	*stack_a = (*stack_a)->next;
	tail = get_stack_bottom(*stack_a);
	tmp->next = NULL;
	tail->next = tmp;
	if (flag)
		return (rotate(stack_b, NULL, cmd, 0));
	if (cmd)
	{
		ft_putstr(cmd);
		ft_putstr("\n");
	}
}

void	swap(t_stack **stack_a, t_stack **stack_b, char *cmd, int flag)
{
	t_stack	*tmp;

	if (*stack_a == NULL || (*stack_a)->next == NULL)
		return ;
	tmp = (*stack_a)->next;
	(*stack_a)->next = tmp->next;
	tmp->next = *stack_a;
	*stack_a = tmp;
	if (flag)
		return (swap(stack_b, NULL, cmd, 0));
	if (cmd)
	{
		ft_putstr(cmd);
		ft_putstr("\n");
	}
}

void	push(t_stack **src, t_stack **dest, char *cmd)
{
	t_stack	*tmp;

	if (*src == NULL)
		return ;
	tmp = (*src)->next;
	(*src)->next = *dest;
	*dest = *src;
	*src = tmp;
	if (cmd)
	{
		ft_putstr(cmd);
		ft_putstr("\n");
	}
}
