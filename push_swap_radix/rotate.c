/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:14:41 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/12 19:16:34 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_list **a)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *a;
	prev = ft_avdernier(*a);
	*a = ft_lstlast(*a);
	(*a)->next = tmp;
	prev->next = NULL;
	write(1, "rra\n", 4);
}

void	rrb(t_list **b)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *b;
	prev = ft_avdernier(*b);
	*b = ft_lstlast(*b);
	(*b)->next = tmp;
	prev->next = NULL;
	write(1, "rrb\n", 4);
}

void	ra(t_list **a)
{
	t_list	*tmp;

	if (!a || !*a || !(*a)->next)
		return ;
	tmp = *a;
	(*a) = (*a)->next;
	ft_lstlast(*a)->next = tmp;
	tmp->next = NULL;
	write(1, "ra\n", 3);
}

void	rb(t_list **b)
{
	t_list	*tmp;

	if (!b || !*b || !(*b)->next)
		return ;
	tmp = *b;
	*b = (*b)->next;
	ft_lstlast(*b)->next = tmp;
	tmp->next = NULL;
	write(1, "rb\n", 3);
}

void	rr(t_list **a, t_list **b)
{
	ra(a);
	rb(b);
	write(1, "rr\n", 3);
}

