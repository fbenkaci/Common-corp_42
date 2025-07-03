/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:15:00 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/06/29 17:15:45 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_pool	*init_token_pool(int initial_capacity)
{
	t_token_pool	*pool;

	pool = malloc(sizeof(t_token_pool));
	if (!pool)
		return (NULL);
	pool->tokens = malloc(sizeof(t_struct) * initial_capacity);
	if (!pool->tokens)
	{
		free(pool);
		return (NULL);
	}
	pool->index = 0;
	pool->capacity = initial_capacity;
	return (pool);
}

t_struct	*get_token_from_pool(t_token_pool *pool)
{
	t_struct	*new_tokens;
	int			new_capacity;
	int			i;

	if (!pool)
		return (NULL);
	if (pool->index >= pool->capacity)
	{
		new_capacity = pool->capacity * 2;
		new_tokens = malloc(sizeof(t_struct) * new_capacity);
		if (!new_tokens)
			return (NULL);
		i = 0;
		while (i < pool->index)
		{
			new_tokens[i] = pool->tokens[i];
			i++;
		}
		free(pool->tokens);
		pool->tokens = new_tokens;
		pool->capacity = new_capacity;
	}
	return (&pool->tokens[pool->index++]);
}

void	reset_token_pool(t_token_pool *pool)
{
	int	i;

	if (!pool)
		return ;
	i = 0;
	while (i < pool->index)
	{
		if (pool->tokens[i].str)
		{
			free(pool->tokens[i].str);
			pool->tokens[i].str = NULL;
		}
		i++;
	}
	pool->index = 0;
}

void	free_token_pool(t_token_pool *pool)
{
	if (!pool)
		return ;
	reset_token_pool(pool);
	if (pool->tokens)
		free(pool->tokens);
	free(pool);
}

void	free_token_strings_only(t_token_pool *pool)
{
	int	i;

	i = 0;
	if (!pool)
		return ;
	while (i < pool->index)
	{
		if (pool->tokens[i].str)
		{
			free(pool->tokens[i].str);
			pool->tokens[i].str = NULL;
		}
		i++;
	}
}
