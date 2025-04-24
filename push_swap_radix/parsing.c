/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:25:52 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/24 13:14:09 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	fill_stack_AA(t_stack **stack, char **args)
{
	t_node	*tmp;
	int		i;

	// t_node	*current;
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
		// current = stack->a;
		// while (current)
		// {
		// 	ft_printf("%d\n", current->value);
		// 	current = current->next;
		// }
		i++;
	}
	// ft_printf("%d\n", current->value);
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
	if (!fill_result(args, result, tmp))
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
	return (1);
}

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
	t_stack	*stack;
	char	**args;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (1);
	stack->a = NULL;
	stack->b = NULL;
	args = split_args(av);
	if (ac > 1)
	{
		if (check_error(args) == 0 || check_duplicate_nb(args) == 0)
		{
			free_map(args);
			free(stack);
			return (0);
		}
		fill_stack_AA(&stack, args);
		if (A_is_sorted(stack))
		{
			free_stack(stack->a);
			free(stack);
			free_map(args);
			return (0);
		}
		stack->nb_in_stack = count_element(args);
		if (stack->nb_in_stack <= 5)
		{
			sort_small_stack(stack);
			free_stack(stack->a);
			free(stack);
			free_map(args);
			return (0);
		}
		else
		{
			sort_big_stack(stack);
			free_stack(stack->cpy_stack_a);
			free_stack(stack->a);
			free(stack);
			free_map(args);
		}
		
	}
	return (0);
}
