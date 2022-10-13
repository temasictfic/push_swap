#include "push_swap.h"
#include "gnl/gnl.h"

void	exit_error(t_stack **stack_a, t_stack **stack_b)
{
	free_stack(stack_a);
	free_stack(stack_b);
	write(2, "Error\n", 6);
	exit(1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	cursor;

	if (n == 0)
		return (0);
	cursor = 0;
	while (cursor < (n - 1) && s1[cursor] && s2[cursor])
	{
		if (s1[cursor] != s2[cursor])
			break ;
		cursor++;
	}
	return (((unsigned char *)s1)[cursor] - ((unsigned char *)s2)[cursor]);
}

int is_valid_cmd(char *cmd)
{
    int i;
    char *three[] = {"rrr", "rra", "rrb"};
    char *two[] = {"rr", "ra", "rb", "ss", "sa", "sb", "pa", "pb"};

    i = 0;
    while (i < 3)
    {
        if (ft_strncmp(three[i], cmd, 3) == 0)
            return(1);
        i++;
    }
    i = 0;
    while (i < 8)
    {
        if (ft_strncmp(two[i], cmd, 2) == 0)
            return(1);
        i++;
    }
    return (0);
}

void execute_cmd(t_stack **stack_a, t_stack **stack_b, char *cmd)
{
        if (cmd == NULL)
            return;
        if (cmd[2] == 'r')
            rev_rotate(stack_a, stack_b, "rrr", 1);
        else if (cmd[2] == 'a')
            rev_rotate(stack_a, NULL, "rra", 0);
        else if (cmd[2] == 'b')
            rev_rotate(stack_b, NULL, "rrb", 0);
        else if (cmd[1] == 'r')
            rotate(stack_a, stack_b, "rr", 1);
        else if (cmd[0] == 'r' && cmd[1] == 'a')
            rotate(stack_a, NULL, "ra", 0);
        else if (cmd[0] == 'r' && cmd[1] == 'b')
            rotate(stack_b, NULL, "rb", 0);
        else if (cmd[1] == 's')
            swap(stack_a, stack_b, "ss", 1);
        else if (cmd[0] == 's' && cmd[1] == 'a')
            swap(stack_a, NULL, "sa", 0);
        else if (cmd[0] == 's' && cmd[1] == 'b')
            swap(stack_b, NULL, "sb", 0);
        else if (cmd[1] == 'a')
            push(stack_b, stack_a, "pa");
        else if (cmd[1] == 'b')
            push(stack_a, stack_b, "pb"); 
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
    while (1)
    {
        inst = get_next_line(STDIN_FILENO);
        if (inst == NULL)
        {
            ft_putstr("KO\n");
            break;
        }
        else if (!is_valid_cmd(inst))
            exit_error(&stack_a, &stack_b);
        execute_cmd(stack_a, stack_b, inst);
        if (is_sorted(stack_a) && get_stack_size(stack_b) == 0)
        {
            ft_putstr("OK\n");
            break;
        }
    }
    free_stack(&stack_a);
    free_stack(&stack_b);
    return (0);
}
