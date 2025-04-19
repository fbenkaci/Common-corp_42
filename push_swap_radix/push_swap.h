/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:26:12 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/19 15:11:00 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP
# define PUSH_SWAP

# include "libft/libft.h"

typedef struct s_node
{
    int             value;
    struct s_node   *next;
}                   t_node;

void	sort_small_stack(t_node *stack, int nb_elmt);
int                 A_is_sorted(t_node *stack);
void                ft_lstadd_back_bis(t_node **lst, t_node *new);
t_node              *lst_new_2(int a);
int                 count_words(char **args);
int                 is_valid_int(char *str);
int                 fill_result(char **args, char **result, char **tmp);
void                rra(t_list **a);
void                rrb(t_list **b);
void                ra(t_list **a);
void                rb(t_list **b);
void                rr(t_list **a, t_list **b);
void                rrr(t_list **a, t_list **b);
void                pa(t_list **a, t_list **b);
void                pb(t_list **b, t_list **a);
void                sa(t_node *a);
void                sb(t_list **b);
void                ss(t_list **a, t_list **b);

#endif