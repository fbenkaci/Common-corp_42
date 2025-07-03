/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:26:02 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/07/02 15:05:02 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	handle_heredocs(t_struct **cur, t_cmd *cmd)
{
	cmd->heredoc = 1;
	while (*cur && (*cur)->next && (*cur)->next->type == SPACES)
		*cur = (*cur)->next;
	if ((*cur)->next->type == WORD || (*cur)->next->type == WORD_D_QUOTES
		|| (*cur)->next->type == WORD_S_QUOTES)
		*cur = (*cur)->next;
	cmd->heredoc_delim = ft_strdup((*cur)->str);
	if (!cmd->heredoc_delim)
		return (-1);
	return (1);
}

void	add_infile_to_list(t_cmd *cmd, t_redir *new_redir, char *filename)
{
	t_redir	*current;

	if (!cmd->infiles)
		cmd->infiles = new_redir;
	else
	{
		current = cmd->infiles;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = ft_strdup(filename);
}

void	add_outfile_to_list(t_cmd *cmd, t_redir *new_redir, char *filename)
{
	t_redir	*current;

	if (!cmd->outfiles)
		cmd->outfiles = new_redir;
	else
	{
		current = cmd->outfiles;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup(filename);
}

int	handle_variable_assignment(t_struct **cur, t_cmd *cmd, int *i)
{
	char	*combined_arg;
	char	*temp;

	temp = ft_strjoin((*cur)->str, "=");
	if (!temp)
		return (-1);
	if ((*cur)->next->next)
	{
		combined_arg = ft_strjoin(temp, (*cur)->next->next->str);
		*cur = (*cur)->next->next;
	}
	else
	{	
		combined_arg = ft_strdup(temp);
		*cur = (*cur)->next;
	}
	free(temp);
	if (!combined_arg)
		return (-1);
	cmd->argv[*i] = combined_arg;
	(*i)++;
	return (1);
}

int	process_variable_expansion2(t_struct **cur, t_cmd *cmd, int *i, char **envp)
{
	if (expand_variable(cur, (*cur)->str, envp) == -1)
		return (-1);
	if ((*cur)->str[0] == '\0')
		return (1);
	cmd->argv[*i] = ft_strdup((*cur)->str);
	if (!cmd->argv[*i])
		return (ft_free_array(cmd->argv), -1);
	(*i)++;
	return (1);
}
