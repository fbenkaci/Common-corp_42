/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:13:18 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/03/19 12:10:25 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_list **a)
{
	t_list	*tmp;

	if (a == NULL || (*a)->next == NULL)
		return ;
	tmp = *a;
	*a = (*a)->next;
	tmp->next = (*a)->next;
	(*a)->next = tmp;
	write(1, "sa\n", 3);
}

void	sb(t_list **b)
{
	t_list	*tmp;

	if (b == NULL || (*b)->next == NULL)
		return ;
	tmp = *b;
	*b = (*b)->next;
	tmp->next = (*b)->next;
	(*b)->next = tmp;
	write(1, "sb\n", 3);
}

void	ss(t_list **a, t_list **b)
{
	sa(a);
	sb(b);
	write(1, "ss\n", 3);
}

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
