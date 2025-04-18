/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:25:52 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/19 15:14:03 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*fill_stack_AA(char **args)
{
	int		i;
	t_node	*stack;
	t_node	*tmp;

	stack = NULL;
	i = 0;
	tmp = NULL;
	while (args[i])
	{
		if (!stack)
			stack = lst_new_2(ft_atoi(args[i]));
		else
		{
			tmp = lst_new_2(ft_atoi(args[i]));
			ft_lstadd_back_bis(&stack, tmp);
		}
		i++;
	}
	return (stack);
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
				&& (!ft_isdigit(args[i][j + 1]) || ft_isdigit(args[i][j - 1])))
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
			// ft_printf("i == %d, k == %d\n", i, k);
			if (ft_atoi(args[i]) == ft_atoi(args[k]))
				return ((ft_putendl_fd("Error\nThere is duplicate numbers.", 2),
						0));
			k++;
		}
		i++;
	}
	// fill_stack_AA(args);
	return (1);
}

// int  check_list_error(char **args)
// {
//  if (!check_error(args))
//      return (0);
//  if (!check_duplicate_nb(args))
//      return (0);
//  return (1);
// }

int	count_element(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	main(int ac, char **av)
{
	char	**args;
	t_node	*stack;
	int		nb_in_stack;

	args = split_args(av);
	if (ac > 1)
	{
		if (check_error(args) == 0 || check_duplicate_nb(args) == 0)
			return (0);
		stack = fill_stack_AA(args);
		if (A_is_sorted(stack))
			return (0);
		nb_in_stack = count_element(args); 
		if (nb_in_stack <= 5)
		{
			sort_small_stack(stack, nb_in_stack);
			return (0);
		}
	}
	// free_map(args);
	return (0);
}
