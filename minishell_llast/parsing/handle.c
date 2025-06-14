/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:57:06 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/06/11 16:44:59 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_space_token(char *s, int *i, t_struct **cur)
{
	append_and_advance(cur, create_token(" ", 1, SPACES));
	if (s[*i])
		(*i)++;
}

void	handle_word_token(char *s, int *i, t_struct **cur)
{
	int	start;
	int	len;

	start = *i;
	while (s[*i] && s[*i] != ' ' && s[*i] != '<' && s[*i] != '>' && s[*i] != '|'
		&& s[*i] != '(' && s[*i] != ')')
		(*i)++;
	len = *i - start;
	append_and_advance(cur, create_token(s + start, len, WORD));
}

void	handle_special_tokens(char *s, int *i, t_struct **cur)
{
	if (s[*i] == '|')
	{
		append_and_advance(cur, create_token("|", 1, PIPE));
		(*i)++;
	}
	else if (s[*i] == '(')
	{
		append_and_advance(cur, create_token("(", 1, PARENTHESIS));
		(*i)++;
	}
	else if (s[*i] == ')')
	{
		append_and_advance(cur, create_token(")", 1, PARENTHESIS));
		(*i)++;
	}
	else if (s[*i] == '\'')
	{
		append_and_advance(cur, create_token("'", 1, S_QUOTE));
		(*i)++;
	}
	else if (s[*i] == '\"')
	{
		append_and_advance(cur, create_token("\"", 1, D_QUOTE));
		(*i)++;
	}
}

void	handle_redir_token(char *s, int *i, t_struct **cur)
{
	if (s[*i] == '>' && s[*i + 1] == '>')
	{
		append_and_advance(cur, create_token(">>", 2, APPEND));
		*i += 2;
	}
	else if (s[*i] == '<' && s[*i + 1] == '<')
	{
		append_and_advance(cur, create_token("<<", 2, HEREDOC));
		*i += 2;
	}
	else if (s[*i] == '>')
	{
		append_and_advance(cur, create_token(">", 1, REDIR_OUT));
		(*i)++;
	}
	else if (s[*i] == '<')
	{
		append_and_advance(cur, create_token("<", 1, REDIR_IN));
		(*i)++;
	}
}

void	append_and_advance(t_struct **cur, t_struct *new)
{
	(*cur)->next = new;
	*cur = new;
}
