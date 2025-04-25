/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:13:20 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/25 20:24:33 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	calculate_max_bit(t_stack *stack, int max_nb)
{
	stack->max_bits = 0;
	while (max_nb >> stack->max_bits != 0)
		stack->max_bits++;
}

int	find_max_nb(t_stack *stack)
{
	t_node	*current;
	t_node	*max_value;

	current = stack->a;
	max_value = current->next;
	while (current && current->next)
	{
		if (current->value > max_value->value)
			max_value = current;
		current = current->next;
	}
	return (max_value->value);
}

void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	count_element(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	free_all(t_stack *stack, char **args)
{
	free_map(args);
	if (stack)
		free(stack);
	return (0);
}
