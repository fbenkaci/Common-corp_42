/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:14:41 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/25 20:30:24 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_node **a)
{
	t_node	*tmp;
	t_node	*prev;

	tmp = *a;
	prev = ft_avdernier_bis(*a);
	*a = ft_last_bis(*a);
	(*a)->next = tmp;
	prev->next = NULL;
	ft_printf("rra\n");
}

void	ra(t_node **a)
{
	t_node	*tmp;

	if (!a || !*a || !(*a)->next)
		return ;
	tmp = *a;
	*a = (*a)->next;
	ft_last_bis(*a)->next = tmp;
	tmp->next = NULL;
	ft_printf("ra\n");
}

void	pa(t_node **a, t_node **b)
{
	t_node	*temp;

	if (!b || !*b)
		return ;
	temp = (*b);
	*b = (*b)->next;
	temp->next = *a;
	*a = temp;
	ft_printf("pa\n");
}

void	pb(t_node **b, t_node **a)
{
	t_node	*temp;

	if (!a || !*a)
		return ;
	temp = *a;
	(*a) = (*a)->next;
	temp->next = *b;
	*b = temp;
	ft_printf("pb\n");
}

void	sa(t_node *a)
{
	int	tmp;

	tmp = 0;
	tmp = a->value;
	a->value = a->next->value;
	a->next->value = tmp;
	ft_printf("sa\n");
}
