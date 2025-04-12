/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:17:29 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/12 19:19:45 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_list **a, t_list **b)
{
	t_list	*temp;

	if (!b || !*b)
		return ;
	temp = (*b);
	*b = (*b)->next;
	temp->next = *a;
	*a = temp;
}

void	pb(t_list **b, t_list **a)
{
	t_list	*temp;

	if (!a || !*a)
		return ;
	temp = *a;
	(*a) = (*a)->next;
	temp->next = *b;
	*b = temp;
}
