/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:15:59 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/19 13:34:45 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_node *a)
{
	int	tmp;

	if (a == NULL || (a)->next == NULL)
		return ;
	tmp = a->value;
	a->value = a->next->value;
	a->next->value = tmp;
	write(1, "sa\n", 3);
}

// void	sb(t_list **b)
// {
// 	t_list	*tmp;

// 	if (b == NULL || (*b)->next == NULL)
// 		return ;
// 	tmp = *b;
// 	*b = (*b)->next;
// 	tmp->next = (*b)->next;
// 	(*b)->next = tmp;
// 	write(1, "sb\n", 3);
// }

// void	ss(t_list **a, t_list **b)
// {
// 	sa(a);
// 	sb(b);
// 	write(1, "ss\n", 3);
// }

// void	rrr(t_list **a, t_list **b)
// {
// 	rra(a);
// 	rrb(b);
// 	write(1, "rrr\n", 4);
// }
