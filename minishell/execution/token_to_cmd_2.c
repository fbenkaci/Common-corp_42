/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:16:07 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/04 20:22:45 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	handle_in(t_struct **cur, t_cmd *cmd)
{
	if ((*cur)->next)
	{
		while (*cur && (*cur)->next && (*cur)->next->type == SPACES)
			*cur = (*cur)->next;
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup((*cur)->next->str);
		if (!cmd->infile)
			return (-1);
		if ((*cur)->next)
			*cur = (*cur)->next;
		return (1);
	}
	return (0);
}

int	handle_out_and_in(t_struct **cur, t_cmd *cmd)
{
	if (*cur && (*cur)->type == REDIR_OUT)
	{
		if ((*cur)->next)
		{
			cmd->append = 0;
			if (cmd->outfile)
				free(cmd->outfile);
			while (*cur && (*cur)->next && (*cur)->next->type == SPACES)
				*cur = (*cur)->next;
			cmd->outfile = ft_strdup((*cur)->next->str);
			if (!cmd->outfile)
				return (-1);
			if ((*cur)->next)
				*cur = (*cur)->next;
		}
		return (1);
	}
	else if (*cur && (*cur)->type == REDIR_IN)
		return (handle_in(cur, cmd));
	return (0);
}

int	expand_variable(t_struct **cur, char *var)
{
	char	*equal_sign;
	int		len;
	int		i;

	// char	**cpy_env;
	// cpy_env = (*cur)->env;
	if (!(*cur)->env)
		return (-1);
	var++;
	len = ft_strlen(var);
	i = 0;
	while ((*cur)->env[i])
	{
		if (ft_strncmp((*cur)->env[i], var, len) == 0
			&& (*cur)->env[i][len] == '=')
		{
			equal_sign = ft_strchr((*cur)->env[i], '=');
			if (equal_sign)
			{
				if ((*cur)->str)
					free((*cur)->str);
				if (equal_sign[1])
				{
					(*cur)->str = ft_strdup(equal_sign + 1);
				}
				else
				{
					(*cur)->str = ft_strdup("");
				}
				if (!(*cur)->str)
					return (-1);
				return (1);
			}
		}
		i++;
	}
	if ((*cur)->str)
		free((*cur)->str);
	(*cur)->str = ft_strdup("");
	if (!(*cur)->str)
		return (-1);
	return (1);
}

int	handle_word_and_append(t_struct **cur, t_cmd *cmd, int *i)
{
	if (*cur && (*cur)->type == APPEND)
	{
		if ((*cur)->next)
		{
			cmd->append = 1;
			if (cmd->outfile)
				free(cmd->outfile);
			while (*cur && (*cur)->next && (*cur)->next->type == SPACES)
				*cur = (*cur)->next;
			cmd->outfile = ft_strdup((*cur)->next->str);
			if (!cmd->outfile)
				return (-1);
			if ((*cur)->next)
				*cur = (*cur)->next;
		}
	}
	else if (*cur && ((*cur)->type == WORD || (*cur)->type == WORD_D_QUOTES
			|| (*cur)->type == WORD_S_QUOTES))
	{
		if ((*cur)->str[0] == '$' && (*cur)->str[1])
		{
			if (expand_variable(cur, (*cur)->str) == -1)
				return (-1);
			cmd->argv[*i] = ft_strdup((*cur)->str);
			if (!cmd->argv[*i])
				return (ft_free_array(cmd->argv), -1);
		}
		else
		{
			cmd->argv[*i] = ft_strdup((*cur)->str);
			if (!cmd->argv[*i])
				return (ft_free_array(cmd->argv), -1);
		}
		(*i)++;
	}
	return (1);
}
