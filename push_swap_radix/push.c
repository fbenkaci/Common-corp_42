/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:17:29 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/22 16:16:17 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
