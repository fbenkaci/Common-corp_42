/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:43:58 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/03/20 14:56:26 by fbenkaci         ###   ########.fr       */
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
		data->nb[data->j] = ft_atoi(data->dest[i]);
		ft_printf("%d\n", data->nb[data->j]);
		data->j++;
		i++;
	}
	return (0);
}

int	is_valid_int(char *str)
{
	long	nbr;
	char	*error;

	error = "Error\nAll numbers must be between -2147483648 and 2147483647.\n";
	if (ft_strlen(str) > 11)
	{
		ft_putstr_fd(error, 2);
		return (1);
	}
	nbr = ft_atol(str);
	if (nbr > INT_MAX || nbr < INT_MIN)
	{
		ft_putstr_fd(error, 2);
		return (1);
	}
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
