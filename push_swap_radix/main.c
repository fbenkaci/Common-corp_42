/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:12:32 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/25 20:44:34 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_small_and_free(t_stack *stack, char **args)
{
	sort_small_stack(stack);
	free_stack(stack->a);
	free(stack);
	free_map(args);
}

void	sort_big_and_free(t_stack *stack, char **args)
{
	sort_big_stack(stack);
	free_stack(stack->a);
	free_stack(stack->cpy_stack_a);
	free(stack);
	free_map(args);
}

int	main(int ac, char **av)
{
	t_stack	*stack;
	char	**args;

	if (ac <= 1)
		return (0);
	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (1);
	stack->a = NULL;
	stack->b = NULL;
	args = split_args(av);
	if (!args || check_error(args) == 0 || check_duplicate_nb(args) == 0)
		return (free_all(stack, args));
	fill_stack_a(&stack, args);
	if (a_is_sorted(stack))
	{
		free_stack(stack->a);
		return (free_all(stack, args));
	}
	stack->nb_in_stack = count_element(args);
	if (stack->nb_in_stack <= 5)
		sort_small_and_free(stack, args);
	else
		sort_big_and_free(stack, args);
	return (0);
}
