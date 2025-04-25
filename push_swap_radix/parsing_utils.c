/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:30:12 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/25 20:25:05 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_lstadd_back_cpy(t_stack *stack, t_node *new)
{
	t_node	*tmp;

	if (!new || !stack)
		return ;
	if (!stack->cpy_stack_a)
	{
		stack->cpy_stack_a = new;
		return ;
	}
	tmp = stack->cpy_stack_a;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_node	*lst_new_2(int a)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->value = a;
	new->next = NULL;
	return (new);
}

t_node	*ft_avdernier_bis(t_node *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	while (lst->next->next != NULL)
		lst = lst->next;
	return (lst);
}

t_node	*ft_last_bis(t_node *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// void	free_stack(t_stack **stack)
// {
// 	t_node *tmp;

// 	while ((*stack)->a)
// 	{
// 		tmp = (*stack)->a;
// 		(*stack)->a = (*stack)->a->next;
// 		free(tmp);
// 	}
// 	(*stack)->a = NULL;
// }

void	free_stack(t_node *stack)
{
	t_node	*tmp;

	while (stack)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp);
	}
	stack = NULL;
}
