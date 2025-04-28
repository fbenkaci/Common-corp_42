/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small_stack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:11:12 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/28 16:04:35 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	a_is_sorted(t_stack *stack)
{
	t_node	*current;

	current = stack->a;
	while (current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}

void	sort_three(t_stack *stack)
{
	int	a;
	int	b;
	int	c;

	a = stack->a->value;
	b = stack->a->next->value;
	c = stack->a->next->next->value;
	if (a > b && a < c)
		sa(stack->a);
	else if (a > b && b < c)
		ra(&stack->a);
	else if (a > b && b > c)
	{
		ra(&stack->a);
		sa(stack->a);
	}
	else if (a < b && a > c)
		rra(&stack->a);
	else if (a < b && b > c)
	{
		rra(&stack->a);
		sa(stack->a);
	}
}

void	sort_small_stack(t_stack *stack)
{
	if (a_is_sorted(stack))
		return ;
	if (stack->nb_in_stack == 2)
	{
		sa(stack->a);
		return ;
	}
	if (stack->nb_in_stack == 3)
		sort_three(stack);
	if (stack->nb_in_stack > 3)
		sort_stack_4_5(stack);
}

void	put_min_in_first(t_stack *stack)
{
	int	min_index;
	int	moves;

	min_index = 0;
	find_min(stack, &min_index);
	if (min_index <= stack->nb_in_stack / 2)
	{
		while (min_index-- > 0)
			ra(&stack->a);
	}
	else
	{
		moves = stack->nb_in_stack - min_index;
		while (moves-- > 0)
			rra(&stack->a);
	}
}

void	sort_stack_4_5(t_stack *stack)
{
	int	to_push;

	if (stack->nb_in_stack == 4)
		to_push = 1;
	else
		to_push = 2;
	while (to_push--)
	{
		put_min_in_first(stack);
		pb(&stack->b, &stack->a);
		stack->nb_in_stack--;
	}
	sort_small_stack(stack);
	while (stack->b)
		pa(&stack->a, &stack->b);
}
