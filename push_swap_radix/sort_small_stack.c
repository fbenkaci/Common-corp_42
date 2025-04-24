/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small_stack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:11:12 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/24 16:31:45 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	A_is_sorted(t_stack *stack)
{
	t_node	*current;

	current = stack->a;
	// ft_printf("%d\n", stack->a->value);
	while (current->next)
	{
		// ft_printf("current->value == %d current->next->value == %d\n",
		// current->value, current->next->value);
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	// ft_printf("Trié.\n");
	return (1);
}


void	sort_small_stack(t_stack *stack)
{
	int	a;
	int	b;
	int	c;

	if (A_is_sorted(stack))
		return ;
	if (stack->nb_in_stack == 2)
		sa(stack->a);
	else if (stack->nb_in_stack == 3)
	{
		a = stack->a->value;
		b = stack->a->next->value;
		c = stack->a->next->next->value;
		if (a > b && b < c && a < c)
			sa(stack->a);
		else if (a > b && b < c && a > c)
			ra(&stack->a);
		else if (a > b && b > c && a > c)
		{
			ra(&stack->a);
			sa(stack->a);
		}
		else if (a < b && b > c && a > c)
			rra(&stack->a);
		else if (a < b && b > c && a < c)
		{
			rra(&stack->a);
			sa(stack->a);
		}
	}
	else if (stack->nb_in_stack <= 5)
		sort_stack_4_5(stack);
}

void	find_min(t_stack *stack, int *min_index)
{
	t_node	*current;
	t_node	*min_value;
	int		index;

	current = stack->a;
	min_value = current;
	index = 0;
	while (current)
	{
		if (current->value < min_value->value)
		{
			min_value = current;
			*min_index = index;
		}
		current = current->next;
		index++;
	}
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
	int	i;

	i = 2;
	if (stack->nb_in_stack == 4)
	{
		put_min_in_first(stack);
		pb(&stack->b, &stack->a);
		stack->nb_in_stack = 3;
		sort_small_stack(stack);
		pa(&stack->a, &stack->b);
	}
	else
	{
		while (i--)
		{
			put_min_in_first(stack);
			pb(&stack->b, &stack->a);
		}
		stack->nb_in_stack = 3;
		sort_small_stack(stack);
		while (i++ < 2)
			pa(&stack->a, &stack->b);
	}
}
