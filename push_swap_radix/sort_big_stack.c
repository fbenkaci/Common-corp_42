/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:31:18 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/24 20:40:44 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	index_sort_nb_cpy(t_stack *stack)
{
	t_node	*current;
	int		i;

	current = stack->cpy_stack_a;
	while (current && current->next)
	{
		if (current->value > current->next->value)
		{
			swap(&current->value, &current->next->value);
			current = stack->cpy_stack_a;
		}
		else
			current = current->next;
	}
	current = stack->cpy_stack_a;
	i = 0;
	while (current)
	{
		current->index = i;
		current = current->next;
		i++;
	}
}

void	calculate_max_bit(t_stack *stack, int max_nb)
{
	stack->max_bits = 0;
	while (max_nb >> stack->max_bits != 0)
		stack->max_bits++;
	// ft_printf("max bit == %d\n", stack->max_bits);
}

int	find_max_nb(t_stack *stack)
{
	t_node	*current;
	t_node	*max_value;

	current = stack->a;
	max_value = current->next;
	while (current && current->next)
	{
		if (current->value > max_value->value)
			max_value = current;
		current = current->next;
	}
	// ft_printf("max == %d\n", max_value->value);
	return (max_value->value);
}

void	assign_sorted_index(t_stack *stack)
{
	t_node	*cpy_start;
	t_node	*current;

	cpy_start = stack->cpy_stack_a;
	current = stack->a;
	while (current)
	{
		while (stack->cpy_stack_a)
		{
			if (current->value == stack->cpy_stack_a->value)
			{
				current->value = stack->cpy_stack_a->index;
				stack->cpy_stack_a = cpy_start;
				break ;
			}
			else
				stack->cpy_stack_a = stack->cpy_stack_a->next;
		}
		current = current->next;
	}
	// current = stack->a;
	// while (current)
	// {
	// 	ft_printf("%d\n", current->value);
	// 	current = current->next;
	// }
}

void	index_stack(t_stack *stack)
{
	t_node	*tmp;
	t_node	*new;

	tmp = stack->a;
	stack->cpy_stack_a = NULL;
	// ft_printf("%d\n", tmp->a->next);
	while (tmp)
	{
		new = lst_new_2(tmp->value);
		// ft_printf("%d\n", tmp->value);
		ft_lstadd_back_cpy(stack, new);
		tmp = tmp->next;
	}
}

// void	radix_sort(t_stack *stack)
// {
// 	t_node	*tmp;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	tmp = stack->a;
// 	while (i < stack->max_bits)
// 	{
// 		j = 0;
// 		while (j < stack->nb_in_stack)
// 		{
// 			if (A_is_sorted(stack))
// 			{
// 				while (stack->b)
// 					pa(&stack->a, &stack->b);
// 				return ;
// 			}
// 			tmp = stack->a;
// 			if (((tmp->value >> i) & 1) == 1)
// 			{
// 				ra(&stack->a);
// 			}
// 			else
// 			{
// 				pb(&stack->b, &stack->a);
// 			}
// 			j++;
// 		}
// 		while (stack->b)
// 			pa(&stack->a, &stack->b);
// 		i++;
// 	}
// }

void normalize_stack(t_stack *stack)
{
    t_node *nodes[stack->nb_in_stack];
    int values[stack->nb_in_stack];
    int positions[stack->nb_in_stack];
    int i, j;
    t_node *current;
    
    // Stocker les noeuds et leurs valeurs
    current = stack->a;
    for (i = 0; i < stack->nb_in_stack; i++)
    {
        nodes[i] = current;
        values[i] = current->value;
        current = current->next;
    }
    
    // Trouver les positions (rangs) des valeurs
    for (i = 0; i < stack->nb_in_stack; i++)
    {
        positions[i] = 0;
        for (j = 0; j < stack->nb_in_stack; j++)
        {
            if (values[i] > values[j] || (values[i] == values[j] && i > j))
                positions[i]++;
        }
    }
    
    // Remplacer les valeurs par leurs positions
    for (i = 0; i < stack->nb_in_stack; i++)
        nodes[i]->value = positions[i];
}

void radix_sort(t_stack *stack)
{
    int i;
    int j;
    int size;
    int all_same_bit;
    
    // Normaliser les valeurs
    normalize_stack(stack);
    
    if (A_is_sorted(stack))
        return;
    
    i = 0;
    // Calculer le nombre de bits nécessaires
    int max_bits = 0;
    int temp = stack->nb_in_stack - 1;
    while (temp > 0)
    {
        max_bits++;
        temp >>= 1;
    }
    
    while (i < max_bits)
    {
        // Vérifier si tous les éléments ont le même bit à cette position
        all_same_bit = -1; // -1 = non initialisé, 0 = tous ont 0, 1 = tous ont 1
        t_node *tmp = stack->a;
        for (j = 0; j < stack->nb_in_stack; j++)
        {
            int current_bit = (tmp->value >> i) & 1;
            if (all_same_bit == -1)
                all_same_bit = current_bit;
            else if (all_same_bit != current_bit)
            {
                all_same_bit = -1;
                break;
            }
            tmp = tmp->next;
        }
        
        // Si tous les éléments ont le même bit, passer à l'itération suivante
        if (all_same_bit != -1)
        {
            i++;
            continue;
        }
        
        size = stack->nb_in_stack;
        j = 0;
        
        while (j < size)
        {
            if (((stack->a->value >> i) & 1) == 0)
                pb(&stack->b, &stack->a);
            else
                ra(&stack->a);
            j++;
        }
        
        // Vérifier si le tri est terminé après chaque bit traité
        while (stack->b)
            pa(&stack->a, &stack->b);
            
        if (A_is_sorted(stack))
            return;
            
        i++;
    }
}
void	sort_big_stack(t_stack *stack)
{
	int	max_nb;

	max_nb = 0;
	index_stack(stack);
	index_sort_nb_cpy(stack);
	assign_sorted_index(stack);
	max_nb = find_max_nb(stack);
	calculate_max_bit(stack, max_nb);
	radix_sort(stack);
	// while (stack->a)
	// {
	// 	ft_printf("a == %d\n", stack->a->value);
	// 	stack->a = stack->a->next;
	// }
}
