/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:25:52 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/12 19:32:57 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_error(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if ((args[i][j] == '-' || args[i][j] == '+')
				&& (!ft_isdigit(args[i][j + 1]) || (ft_isdigit(args[i][j
							- 1]))))
				return (ft_putendl_fd("Error\nInvalid sign usage.", 2), 0);
			else if (!ft_isdigit(args[i][j]) && args[i][j] != '-'
				&& args[i][j] != '+')
				return (ft_putendl_fd("Error\nOnly digits and signs allowed.",
						2), 0);
			j++;
		}
		i++;
	}
	return (1);
}
int	count_words(char **args)
{
	int		i;
	int		j;
	int		count;
	char	**tmp;

	i = 1;
	j = 0;
	count = 0;
	while (args[i])
	{
		tmp = ft_split(args[i], ' ');
		if (!tmp)
			return (0);
		j = 0;
		while (tmp[j])
		{
			count++;
			j++;
		}
		free_map(tmp);
		i++;
	}
	return (count);
}

int	fill_result(char **args, char **result, char **tmp)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (args[i])
	{
		tmp = ft_split(args[i], ' ');
		if (!tmp)
			return (0);
		j = 0;
		while (tmp[j])
		{
			result[k] = ft_strdup(tmp[j]);
			if (!result[k])
				return (free_map(result), free_map(tmp), 0);
			j++;
			k++;
		}
		free_map(tmp);
		i++;
	}
	result[k] = NULL;
	return (1);
}

char	**split_args(char **args)
{
	int		nb_words;
	char	**result;
	char	**tmp;

	tmp = NULL;
	nb_words = count_words(args);
	result = malloc((nb_words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (fill_result(args, result, tmp) == 0)
		return (NULL);
	return (result);
}
int	is_valid_int(char *str)
{
	long	nbr;
	char	*error;

	error = "Error\nAll numbers must be between -2147483648 and 2147483647.\n";
	nbr = ft_atol(str);
	if (nbr > INT_MAX || nbr < INT_MIN)
	{
		ft_putstr_fd(error, 2);
		return (0);
	}
	return (1);
}

int	convert_to_int(int **tab, char **args, int *j)
{
	int	len;
	int	i;

	*j = 0;
	len = 0;
	i = 1;
	while (args[i++])
		len++;
	*tab = malloc(sizeof(int) * len);
	if (!*tab)
		return (0);
	i = 1;
	while (args[i])
	{
		if (!is_valid_int(args[i]))
			return (0);
		(*tab)[*j] = ft_atoi(args[i]);
		i++;
		(*j)++;
	}
	return (1);
}

void	fill_stack_A(int **tab)
{
	t_list *data;
    
    
}

void	*check_duplicate_nb(char **args)
{
	int	*tab;
	int	i;
	int	k;
	int	j;

	i = 0;
	j = 0;
	convert_to_int(&tab, args, &j);
	ft_printf("%d", tab[0]);
	while (i + 1 < j)
	{
		k = i + 1;
		while (k < j)
		{
			if (tab[i] == tab[k])
				return ((ft_putendl_fd("Error\nThere is duplicate numbers.", 2),
						0));
			k++;
		}
		i++;
	}
    fill_stack_A(tab);
	return (1);
}

int	check_list_error(char **args)
{
	if (!check_error(args))
		return (0);
	if (!check_duplicate_nb(args))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	char	**args;
	int		i;

	i = 0;
	args = split_args(av);
	if (ac > 1)
	{
		if (check_list_error(args) == 0)
			return (0);
	}
	free_map(args);
	return (0);
}
