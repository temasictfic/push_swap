/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 00:45:27 by sciftci           #+#    #+#             */
/*   Updated: 2022/10/13 15:07:45 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_num(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '+' || str[i] == '-') && str[i + 1] != '\0')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (str[i] != '\0' && !(str[i] >= '0' && str[i] <= '9'))
		return (0);
	return (1);
}

static int	num_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s1[i] == '+')
	{
		if (s2[j] != '+')
			i++;
	}
	else
	{
		if (s2[j] == '+')
			j++;
	}
	while (s1[i] != '\0' && s2[j] != '\0' && s1[i] == s2[j])
	{
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

static int	has_duplicate(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 1;
		while (str[j])
		{
			if (i != j && num_strcmp(str[i], str[j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	is_zero(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] == '0')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	is_valid_input(char **str)
{
	int	i;
	int	zeroes;

	zeroes = 0;
	i = 1;
	while (str[i])
	{
		if (!is_num(str[i]))
			return (0);
		zeroes += is_zero(str[i]);
		i++;
	}
	if (zeroes > 1 || has_duplicate(str))
		return (0);
	return (1);
}
