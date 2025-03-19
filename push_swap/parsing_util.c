/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:43:58 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/03/19 15:52:10 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*remove_extra_spaces(char *str)
{
	int	i;
	int	j;
	int	in_space;

	i = 0;
	j = 0;
	in_space = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' && in_space == 0)
		{
			str[j++] = ' ';
			in_space = 1;
		}
		else
		{
			str[j++] = str[i];
			in_space = 0;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

int	convert_to_int(t_data *data)
{
	int	i;

	i = 0;
	while (data->dest[i])
	{
		if (is_valid_int(data->dest[i]) == 1)
			return (1);
		data->nb[i] = ft_atoi(data->dest[i]);
		i++;
	}
	return (0);
}

int	is_valid_int(char *str)
{
	int	len_nb;
	int	i;

	i = 0;
	len_nb = ft_strlen(str);
	if (len_nb > 11)
	{
		if (str[0] == '-')
		{
			write(2, "Error\nThe following digit : ", 29);
			write(2, str, len_nb);
			write(2, " is too small.\n", 16);
			return (1);
		}
		write(2, "Error\nThe following digit  : ", 30);
		write(2, str, len_nb);
		write(2, " is too long\n", 14);
		return (1);
	}
	if (len_nb == 11 && ft_strcmp(str, "-2147483648") != 0)
		return (1);
	if (len_nb == 10 && ft_strcmp(str, "2147483647") != 0)
		return (1);
	return (0);
}

int	check_if_digit(char **av, int i, int j)
{
	if (!ft_isdigit(av[i][j]) && (av[i][j] != '-' && av[i][j] != '+'))
	{
		write(2, "Error\nIl ne doit y avoir que des numero ou signe '-' '+'.\n",
			59);
		return (1);
	}
	return (0);
}

int	check_sign(char **av, int i, int j)
{
	if (av[i][j] == '-' || av[i][j] == '+')
	{
		if ((!ft_isdigit(av[i][j + 1])))
		{
			write(2, "Error.\nPut digit after the sign.\n", 34);
			return (1);
		}
	}
	return (0);
}
