/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:16:27 by sciftci           #+#    #+#             */
/*   Updated: 2022/10/18 11:34:27 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line_bonus.h"
#include "push_swap.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

static size_t	count_digit(long num)
{
	size_t	many;

	many = 0;
	if (num < 0)
	{
		many = 1;
		num *= -1;
	}
	while (1)
	{
		num /= 10;
		many++;
		if (num == 0)
			break ;
	}
	return (many);
}

char	*ft_itoa(int n)
{
	long	number;
	char	*array;
	size_t	size;

	number = n;
	size = count_digit(n);
	array = malloc((size + 1) * sizeof(char));
	if (!array)
		return (NULL);
	if (number < 0)
	{
		array[0] = '-';
		number *= -1;
	}
	array[size] = '\0';
	while (1)
	{
		array[size - 1] = (number % 10) + '0';
		number /= 10;
		size--;
		if (number == 0)
			break ;
	}
	return (array);
}

char	*fields(t_stack *stack, int field_num)
{
	char *empty;
	if (stack)
	{
		if (field_num == 0)
			return (ft_itoa(stack->value));
		else if (field_num == 1)
			return (ft_itoa(stack->order));
		else if (field_num == 2)
			return (ft_itoa(stack->index));
		else if (field_num == 3)
			return (ft_itoa(stack->target_index));
		else if (field_num == 4)
			return (ft_itoa(stack->cost_a));
		else if (field_num == 5)
			return (ft_itoa(stack->cost_b));
		else if (field_num == 6)
			return (ft_itoa(ft_abs(stack->cost_b) + ft_abs(stack->cost_a)));
	}
	empty = malloc(1);
	empty[0] = '\0';
	return (empty);
}

static void	execute_cmd(t_stack **stack_a, t_stack **stack_b, char *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd[2] == 'r')
		rev_rotate(stack_a, stack_b, NULL, 1);
	else if (cmd[2] == 'a')
		rev_rotate(stack_a, NULL, NULL, 0);
	else if (cmd[2] == 'b')
		rev_rotate(stack_b, NULL, NULL, 0);
	else if (cmd[1] == 'r')
		rotate(stack_a, stack_b, NULL, 1);
	else if (cmd[0] == 'r' && cmd[1] == 'a')
		rotate(stack_a, NULL, NULL, 0);
	else if (cmd[0] == 'r' && cmd[1] == 'b')
		rotate(stack_b, NULL, NULL, 0);
	else if (cmd[1] == 's')
		swap(stack_a, stack_b, NULL, 1);
	else if (cmd[0] == 's' && cmd[1] == 'a')
		swap(stack_a, NULL, NULL, 0);
	else if (cmd[0] == 's' && cmd[1] == 'b')
		swap(stack_b, NULL, NULL, 0);
	else if (cmd[1] == 'a')
		push(stack_b, stack_a, NULL);
	else if (cmd[1] == 'b')
		push(stack_a, stack_b, NULL);
}

int	main(int ac, char **av)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	t_stack	*tmp_a;
	t_stack	*tmp_b;
	int		stack_size;
	char	*cmd;
	char	*new_line;
	char	*value_a;
	char	*order_a;
	char	*index_a;
	char	*value_b;
	char	*order_b;
	char	*index_b;
	char	*target_index;
	char	*cost_a;
	char	*cost_b;
	char	*total_cost;
	int		fd;
	int		flag;
	int 	i;

	i = 0;
	flag = 0;
	new_line = NULL;
	cmd = NULL;
	if (ac < 2)
		return (0);
	if (!is_valid_input(av))
		exit_error(NULL, NULL);
	stack_a = fill_stack_a(ac, av);
	stack_b = NULL;
	stack_size = get_stack_size(stack_a);
	assign_order(stack_a, stack_size + 1);
	fd = open("ps.txt", O_RDONLY | O_CREAT);
	do
	{
		execute_cmd(&stack_a, &stack_b, cmd);
		if (get_stack_size(stack_a) == 3 && is_sorted(stack_a))
			flag = 1;
		if (flag && get_stack_size(stack_b) > 0)
		{
			assign_target_index(&stack_a, &stack_b);
			get_cost(&stack_a, &stack_b);
		}
		if (flag && get_stack_size(stack_b) == 0)
			get_index(&stack_a);
		tmp_a = stack_a;
		tmp_b = stack_b;
		if (cmd)
			printf("#%d %35s\n", ++i, cmd);
		printf("\nvalue          order     index             value          order     index    target_index    cost_a    cost_b    total_cost");
		printf("\n-----------    -----     -----             -----------    -----     -----    ------------    ------    ------    ----------\n\n");
		while (tmp_a || tmp_b)
		{
			value_a = fields(tmp_a, 0);
			order_a = fields(tmp_a, 1);
			index_a = fields(tmp_a, 2);
			value_b = fields(tmp_b, 0);
			order_b = fields(tmp_b, 1);
			index_b = fields(tmp_b, 2);
			target_index = fields(tmp_b, 3);
			cost_a = fields(tmp_b, 4);
			cost_b = fields(tmp_b, 5);
			total_cost = fields(tmp_b, 6);
			printf("%-11s    <%4s>    [%4s]            ", value_a,
				order_a, index_a );
			printf("%-11s    <%4s>    [%4s]    [> %4s <]     $%4s     $%4s     $%4s\n\n", value_b,
					order_b, index_b, target_index, cost_a, cost_b, total_cost);
			if (tmp_a)
				tmp_a = tmp_a->next;
			if (tmp_b)
				tmp_b = tmp_b->next;
			free(value_a);
			free(order_a);
			free(index_a);
			free(value_b);
			free(order_b);
			free(index_b);
			free(target_index);
			free(cost_a);
			free(cost_b);
			free(total_cost);
		}
		printf("_______________________________            __________________________________________________________________________________\n");
		printf("stack_a                                                                                                               stack_b\n");
		free(cmd);
		cmd = get_next_line(fd);
		free(new_line);
		new_line = get_next_line(0);
	} while (new_line[0] == '\n' && !(is_sorted(stack_a) && get_stack_size(stack_b) == 0));
	close(fd);
	free_stack(&stack_a);
	free_stack(&stack_b);
}
