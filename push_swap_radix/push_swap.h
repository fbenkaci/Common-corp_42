/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:26:12 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/27 15:47:53 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"

typedef struct s_node
{
	int				index;
	int				value;
	struct s_node	*next;

}					t_node;

typedef struct s_stack
{
	int				nb_in_stack;
	int				max_bits;
	t_node			*a;
	t_node			*b;
	t_node			*cpy_stack_a;
}					t_stack;

void				find_min(t_stack *stack, int *min_index);
char				**split_args(char **args);
void				fill_stack_a(t_stack **stack, char **args);
int					check_error(char **args);
int					check_duplicate_nb(char **args);
void				calculate_max_bit(t_stack *stack, int max_nb);
int					find_max_nb(t_stack *stack);
void				swap(int *a, int *b);
int					count_element(char **args);
int					free_all(t_stack *stack, char **args);
void				free_stack(t_node *stack);
void				ft_lstadd_back_cpy(t_stack *stack, t_node *new);
void				sort_big_stack(t_stack *stack);
void				sort_stack_4_5(t_stack *stack);
t_node				*ft_avdernier_bis(t_node *lst);
t_node				*ft_last_bis(t_node *lst);
void				sort_small_stack(t_stack *stack);
int					a_is_sorted(t_stack *stack);
void				ft_lstadd_back_bis(t_stack **lst, t_node *new);
t_node				*lst_new_2(int a);
int					count_words(char **args);
int					is_valid_int(char **args);
int					fill_result(char **args, char **result);
void				rra(t_node **a);
void				rrb(t_node **b);
void				ra(t_node **a);
void				rb(t_node **b);
void				rr(t_node **a, t_node **b);
void				rrr(t_node **a, t_node **b);
void				pa(t_node **a, t_node **b);
void				pb(t_node **b, t_node **a);
void				sa(t_node *a);
void				sb(t_node **b);
void				ss(t_node **a, t_node **b);

#endif