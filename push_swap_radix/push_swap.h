/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:26:12 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/12 19:25:59 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP
# define PUSH_SWAP

# include "libft/libft.h"

typedef struct s_list
{
	int				stack_A;
	int				stack_B;
	int				data;
	struct s_list	*next;
	struct s_list	*pecedent;
}					t_list;

void				rra(t_list **a);
void				rrb(t_list **b);
void				ra(t_list **a);
void				rb(t_list **b);
void				rr(t_list **a, t_list **b);
void				rrr(t_list **a, t_list **b);
void				pa(t_list **a, t_list **b);
void				pb(t_list **b, t_list **a);
void				sa(t_list **a);
void				sb(t_list **b);
void				ss(t_list **a, t_list **b);

#endif