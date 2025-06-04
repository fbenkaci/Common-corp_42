/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:39:52 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/04 20:27:45 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../libft/libft.h"
#include "../parsing/minishell.h"

#define MAX_ARGS 100

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
	ft_printf("herdoc delim == %s\n", cmd->heredoc_delim);
	return (1);
}

int	fill_cmd_from_token(t_struct **cur, t_cmd *cmd, int *i)
{
	int	res;

	while (*cur && (*cur)->type != PIPE)
	{
		if ((*cur)->type == REDIR_OUT || (*cur)->type == REDIR_IN)
		{
			res = handle_out_and_in(cur, cmd);
			if (res == -1)
				return (-1);
		}
		else if ((*cur)->type == APPEND || (*cur)->type == WORD
			|| (*cur)->type == WORD_D_QUOTES || (*cur)->type == WORD_S_QUOTES)
		{
			if (handle_word_and_append(cur, cmd, i) == -1)
				return (-1);
		}
		else if ((*cur)->type == HEREDOC)
		{
			if (handle_heredocs(cur, cmd) == -1)
				return (-1);
		}
		if ((*cur)->next)
		{
			if (cpy_env((*cur)->next, (*cur)->env) == -1)
				return (-1);
		}
		*cur = (*cur)->next;
	}
	return (1);
}

t_cmd	*init_new_cmd(t_struct **cur, char **envp)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->append = 0;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->heredoc = 0;
	if (cpy_env(*cur, envp) == -1)
		return (NULL);
	cmd->argv = malloc(sizeof(char *) * (MAX_ARGS + 1));
	if (!cmd->argv)
		return (free(cmd), NULL);
	cmd->next = NULL;
	return (cmd);
}

int	create_cmd_list(t_struct **cur, t_cmd *cmd, char **envp)
{
	t_cmd	*current;
	int		i;
	int		j;

	current = cmd;
	while (*cur)
	{
		i = 0;
		if (fill_cmd_from_token(cur, current, &i) == -1)
			return (-1); // free tout
		j = 0;
		while (current->argv[j])
		{
			printf("ARGV[%d] == %s\n", j, current->argv[j]);
			j++;
		}
		printf("INFILE == %s\n", current->infile);
		printf("OUTFILE == %s\n\n", current->outfile);
		current->argv[i] = NULL;
		if (*cur && (*cur)->type == PIPE)
		{
			if ((*cur)->next)
				*cur = (*cur)->next;
			current->next = init_new_cmd(cur, envp);
			if (!current->next)
				return (-1);
			current = current->next;
		}
	}
	return (1);
}

t_cmd	*create_cmd_from_tokens(t_struct **cur, char **envp)
{
	t_cmd	*cmd;

	cmd = init_new_cmd(cur, envp);
	if (!cmd)
		return (NULL);
	if (create_cmd_list(cur, cmd, envp) == -1)
	{
		// if (cmd->outfile)
		// 	free(cmd->outfile);
		// if (cmd->infile)
		// 	free(cmd->infile);
		free(cmd->argv);
		free(cmd);
		return (NULL);
	}
	return (cmd);
}
