/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:25:52 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/27 15:01:51 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	fill_stack_a(t_stack **stack, char **args)
{
	t_node	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (args[i])
	{
		if (!(*stack)->a)
			(*stack)->a = lst_new_2(ft_atoi(args[i]));
		else
		{
			tmp = lst_new_2(ft_atoi(args[i]));
			ft_lstadd_back_bis(stack, tmp);
		}
		i++;
	}
}

char	**split_args(char **args)
{
	int		nb_words;
	char	**result;
	int		i;

	i = 0;
	nb_words = count_words(args);
	result = malloc((nb_words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i <= nb_words)
	{
		result[i] = NULL;
		i++;
	}
	if (!fill_result(args, result))
	{
		free_map(result);
		return (NULL);
	}
	return (result);
}

int	check_error(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if ((args[i][j] == '-' || args[i][j] == '+')
				&& (!ft_isdigit(args[i][j + 1]) || (j > 0
						&& ft_isdigit(args[i][j - 1]))))
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

int	check_duplicate_nb(char **args)
{
	int	i;
	int	k;

	i = 0;
	while (args[i])
	{
		k = i + 1;
		while (args[k])
		{
			if (ft_atoi(args[i]) == ft_atoi(args[k]))
				return ((ft_putendl_fd("Error\nThere is duplicate numbers.", 2),
						0));
			k++;
		}
		i++;
	}
	return (1);
}
