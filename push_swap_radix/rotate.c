/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:14:41 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/24 19:35:22 by fbenkaci         ###   ########.fr       */
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

// void	rrb(t_node **b)
// {
// 	t_node	*tmp;
// 	t_node	*prev;

// 	tmp = *b;
// 	prev = ft_avdernier(*b);
// 	*b = ft_lstlast(*b);
// 	(*b)->next = tmp;
// 	prev->next = NULL;
// 	write(1, "rrb\n", 4);
// }

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

// void	rb(t_node **b)
// {
// 	t_node	*tmp;

// 	if (!b || !*b || !(*b)->next)
// 		return ;
// 	tmp = *b;
// 	*b = (*b)->next;
// 	ft_lstlast(*b)->next = tmp;
// 	tmp->next = NULL;
// 	write(1, "rb\n", 3);
// }

// void	rr(t_node **a, t_node **b)
// {
// 	ra(a);
// 	rb(b);
// 	write(1, "rr\n", 3);
// }

