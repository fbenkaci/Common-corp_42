/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:16:07 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/19 16:17:17 by fbenkaci         ###   ########.fr       */
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

int	handle_out(t_struct **cur, t_cmd *cmd, int fd)
{
	if ((*cur)->next)
	{
		cmd->append = 0;
		*cur = (*cur)->next;
		while (*cur && (*cur)->type == SPACES)
			*cur = (*cur)->next;
		if (!*cur)
			return (-1);
		if (cmd->outfile)
		{
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror(cmd->outfile);
				return (-1);
			}
			close(fd);
			free(cmd->outfile);
		}
		cmd->outfile = ft_strdup((*cur)->str);
		if (!cmd->outfile)
			return (-1);
	}
	return (1);
}

int	handle_out_and_in(t_struct **cur, t_cmd *cmd)
{
	int	fd;

	fd = 0;
	if (*cur && (*cur)->type == REDIR_OUT)
	{
		if (handle_out(cur, cmd, fd) == -1)
			return (-1);
		if ((*cur)->next)
			*cur = (*cur)->next;
		return (1);
	}
	else if (*cur && (*cur)->type == REDIR_IN)
		if (handle_in(cur, cmd) == -1)
			return (-1);
	return (0);
}

int	handle_word_and_expand(t_struct **cur, t_cmd *cmd, int *i, char **envp)
{
	if (*cur && ((*cur)->type == WORD || (*cur)->type == WORD_D_QUOTES
			|| (*cur)->type == WORD_S_QUOTES))
	{
		if (ft_strchr((*cur)->str, '$') && (*cur)->type != WORD_S_QUOTES)
			// jai rajouter cette condion (*cur)->type != WORD_S_QUOTES
		{
			if (expand_variable(cur, (*cur)->str, envp) == -1)
				return (-1);
			if ((*cur)->str[0] == '\0')
			{
				return (1);
			}
			cmd->argv[*i] = ft_strdup((*cur)->str);
			if (!cmd->argv[*i])
				return (ft_free_array(cmd->argv), -1);
		}
		else
		{
			cmd->argv[*i] = ft_strdup((*cur)->str);
			if (!cmd->argv[*i])
				return (-1);
		}
		(*i)++;
	}
	return (1);
}

int	handle_word_and_append(t_struct **cur, t_cmd *cmd, int *i, char **envp)
{
	if (*cur && (*cur)->type == APPEND)
	{
		if ((*cur)->next)
		{
			cmd->append = 1;
			free(cmd->outfile);
			cmd->outfile = NULL;
			while (*cur && (*cur)->next && (*cur)->next->type == SPACES)
				*cur = (*cur)->next;
			if (!(*cur)->next)
				return (-1);
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
		if (handle_word_and_expand(cur, cmd, i, envp) == -1)
			return (-1);
	}
	return (1);
}
