/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:31:18 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/28 16:34:03 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	index_sort_nb_cpy(t_stack *stack)
{
	t_node	*current;
	int		i;

	current = stack->cpy_stack_a;
	while (current && current->next)
	{
		if (current->value > current->next->value)
		{
			swap(&current->value, &current->next->value);
			current = stack->cpy_stack_a;
		}
		else
			current = current->next;
	}
	current = stack->cpy_stack_a;
	i = 0;
	while (current)
	{
		current->index = i;
		current = current->next;
		i++;
	}
}

void	assign_sorted_index(t_stack *stack)
{
	t_node	*cpy_start;
	t_node	*current;

	cpy_start = stack->cpy_stack_a;
	current = stack->a;
	while (current)
	{
		while (stack->cpy_stack_a)
		{
			if (current->value == stack->cpy_stack_a->value)
			{
				current->value = stack->cpy_stack_a->index;
				stack->cpy_stack_a = cpy_start;
				break ;
			}
			else
				stack->cpy_stack_a = stack->cpy_stack_a->next;
		}
		current = current->next;
	}
}

void	index_stack(t_stack *stack)
{
	t_node	*tmp;
	t_node	*new;

	tmp = stack->a;
	stack->cpy_stack_a = NULL;
	while (tmp)
	{
		new = lst_new_2(tmp->value);
		ft_lstadd_back_cpy(stack, new);
		tmp = tmp->next;
	}
}

void	radix_sort(t_stack *stack)
{
	t_node	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = stack->a;
	while (i < stack->max_bits)
	{
		j = 0;
		while (j < stack->nb_in_stack)
		{
			tmp = stack->a;
			if (((tmp->value >> i) & 1) == 1)
				ra(&stack->a);
			else
				pb(&stack->b, &stack->a);
			j++;
		}
		while (stack->b)
			pa(&stack->a, &stack->b);
		i++;
	}
}

void	sort_big_stack(t_stack *stack)
{
	int	max_nb;

	max_nb = 0;
	index_stack(stack);
	index_sort_nb_cpy(stack);
	assign_sorted_index(stack);
	max_nb = find_max_nb(stack);
	calculate_max_bit(stack, max_nb);
	radix_sort(stack);
	while(stack->a)
	{
		ft_printf("%d\n", stack->a->value);
		stack->a = stack->a->next;
	}
}
