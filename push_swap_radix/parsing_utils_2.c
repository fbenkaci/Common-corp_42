/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:38:55 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/27 15:40:35 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	count_words(char **args)
{
	int		i;
	int		j;
	int		count;
	char	**tmp;

	i = 1;
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

int	is_valid_int(char **args)
{
	long	nbr;
	char	*error;
	int		i;

	i = 0;
	error = "Error\nAll numbers must be between -2147483648 and 2147483647.\n";
	while (args[i])
	{
		nbr = ft_atol(args[i]);
		ft_printf("%d\n", nbr);
		if (nbr > INT_MAX || nbr < INT_MIN)
		{
			ft_putstr_fd(error, 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	copy_split_words(char **tmp, char **result, int *k)
{
	int	j;

	j = 0;
	while (tmp[j])
	{
		result[*k] = ft_strdup(tmp[j]);
		if (!result[*k])
		{
			free_map(result);
			free_map(tmp);
			return (0);
		}
		(*k)++;
		j++;
	}
	return (1);
}

int	fill_result(char **args, char **result)
{
	char	**tmp;
	int		i;
	int		k;

	i = 1;
	k = 0;
	while (args[i])
	{
		tmp = ft_split(args[i], ' ');
		if (!tmp || !copy_split_words(tmp, result, &k))
			return (0);
		free_map(tmp);
		i++;
	}
	result[k] = NULL;
	return (1);
}

void	ft_lstadd_back_bis(t_stack **lst, t_node *new)
{
	t_node	*tmp;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		(*lst)->a = new;
		return ;
	}
	tmp = (*lst)->a;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}
