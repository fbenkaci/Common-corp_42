/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:11:12 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/19 17:21:33 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	A_is_sorted(t_node *stack)
{
	t_node	*current;

	current = stack;
	while (current->next)
	{
		// ft_printf("current->value == %d current->next->value == %d\n",
		// current->value, current->next->value);
		if (current->value > current->next->value)
		{
			// ft_printf("Non trié.\n");
			return (0);
		}
		current = current->next;
	}
	// ft_printf("Trié.\n");
	return (1);
}

void	sort_small_stack(t_node *stack, int nb_elmt)
{
	t_node	*current;
	t_node	*nb_max;
	t_node	*tmp;

	current = stack;
	if (nb_elmt == 2)
	{
		// ft_printf("Avant le swap stack->value == %d stack->next->value ==
		// %d\n",
		// current, current->next);
		if (current->value > current->next->value)
			sa(current);
		// ft_printf("Apres le swap stack->value == %d stack->next->value ==
		// %d\n",
		// stack->value, stack->next->value);
	}
	if (nb_elmt == 3)
	{
		tmp = current;
		while (tmp->next)
		{
			if (current->value > current->next->value)
			{
				nb_max = current;
				current = tmp;
			}
			else
				current = current->next;
			ft_printf("%d %d\n", current->value, current->next->value);
		}
		ft_printf("max == %d\n", nb_max->value);
		// tmp = current;
		// if (tmp->next != NULL)
		// {
		// 	while (tmp->next)
		// 	{
		// 		tmp = tmp->next;
		// 	}
		// }
	}
}
