/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:30:12 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/19 15:24:40 by fbenkaci         ###   ########.fr       */
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

int	fill_result(char **args, char **result, char **tmp)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = -1;
	while (args[i])
	{
		tmp = ft_split(args[i], ' ');
		if (!tmp)
			return (0);
		j = 0;
		while (tmp[j])
		{
			result[k] = ft_strdup(tmp[j]);
			if (result[k] == NULL)
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

void	ft_lstadd_back_bis(t_node **lst, t_node *new)
{
	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (*lst != NULL)
	{
		lst = &(*lst)->next;
	}
	*lst = new;
}

t_node	*lst_new_2(int a)
{
	t_node *new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->value = a;
	new->next = NULL;

	return (new);
}