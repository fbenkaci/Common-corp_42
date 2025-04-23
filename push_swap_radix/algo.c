/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:11:12 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/23 19:55:16 by fbenkaci         ###   ########.fr       */
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

void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_index(t_stack *stack)
{
	t_node	*tmp;
	t_node	*current;

	current = stack->cpy_stack_a;
	tmp = stack->cpy_stack_a;
	while (current && current->next)
	{
		if (current->value > current->next->value)
		{
			swap(&current->value, &current->next->value);
			current = tmp;
		}
		else
			current = current->next;
	}
}

void	index_stack(t_stack *stack)
{
	t_node	*tmp;
	t_node	*current;

	tmp = stack->a;
	// ft_printf("%d\n", tmp->a->next);
	while (tmp)
	{
		current = lst_new_2(tmp->value);
		ft_lstadd_back_cpy(&stack, current);
		tmp = tmp->next;
	}
	while (stack->cpy_stack_a)
	{
		ft_printf("%d\n", stack->cpy_stack_a->value);
		stack->cpy_stack_a = stack->cpy_stack_a->next;
	}
}

void	sort_big_stack(t_stack *stack)
{
	index_stack(stack);
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
