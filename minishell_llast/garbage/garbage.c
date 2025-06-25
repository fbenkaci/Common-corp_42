/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:27:22 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/23 14:55:10 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

// void	init_garbage(t_garbage *gc)
// {
// 	gc->cmd = NULL;
// 	gc->data = NULL;
// 	gc->exec = NULL;
// 	gc->allocations = NULL;
// }

// void	*gc_malloc(size_t size, t_garbage *gc)
// {
// 	t_gc_node	*node;
// 	void		*ptr;

// 	ptr = malloc(size);
// 	if (!ptr)
// 		return (NULL);
// 	node = malloc(sizeof(t_gc_node));
// 	if (!node)
// 	{
// 		free(ptr);
// 		return (NULL);
// 	}
// 	node->ptr = ptr;
// 	node->next = gc->allocations;
// 	gc->allocations = node;
// 	return (ptr);
// }

// char	*gc_strdup(const char *s, t_garbage *gc)
// {
// 	t_gc_node	*node;
// 	char		*ptr;

// 	ptr = ft_strdup(s);
// 	if (!ptr)
// 		return (NULL);
// 	node = malloc(sizeof(t_gc_node));
// 	if (!node)
// 	{
// 		free(ptr);
// 		return (NULL);
// 	}
// 	node->ptr = ptr;
// 	node->next = gc->allocations;
// 	gc->allocations = node;
// 	return (ptr);
// }

// void	free_garbage(t_garbage *gc)
// {
// 	t_gc_node	*current;
// 	t_gc_node	*next;

// 	current = gc->allocations;
// 	while (current)
// 	{
// 		next = current->next;
// 		if (current->ptr)
// 			free(current->ptr);
// 		free(current);
// 		current = next;
// 	}
// 	gc->allocations = NULL;
// 	if (gc->cmd)
// 	{
// 		free_all_cmd(gc->cmd);
// 		gc->cmd = NULL;
// 	}
// 	if (gc->data)
// 	{
// 		free_tokens(gc->data);	
// 		free(gc->data);
// 		gc->data = NULL;
// 	}
// 	if (gc->exec)
// 	{
// 		if (gc->exec->pipes)
// 		{
// 			free(gc->exec->pipes);
// 			gc->exec->pipes = NULL;
// 		}
// 		free(gc->exec);
// 		gc->exec = NULL;
// 	}
// }


// void free_garbage(t_garbage *gc)
// {
// 	if ()
// 	{
// 		/* code */
// 	}
	
// }
