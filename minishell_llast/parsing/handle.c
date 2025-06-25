/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:57:06 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/06/23 17:34:43 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_space_token(char *s, int *i, t_struct **cur)
{
	append_and_advance(cur, create_token(" ", 1, SPACES, *cur));
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
	append_and_advance(cur, create_token(s + start, len, WORD, *cur));
}

void	handle_special_tokens(char *s, int *i, t_struct **cur)
{
	if (s[*i] == '|')
	{
		append_and_advance(cur, create_token("|", 1, PIPE, *cur));
		(*i)++;
	}
	else if (s[*i] == '(')
	{
		append_and_advance(cur, create_token("(", 1, PARENTHESIS, *cur));
		(*i)++;
	}
	else if (s[*i] == ')')
	{
		append_and_advance(cur, create_token(")", 1, PARENTHESIS, *cur));
		(*i)++;
	}
	else if (s[*i] == '\'')
	{
		append_and_advance(cur, create_token("'", 1, S_QUOTE, *cur));
		(*i)++;
	}
	else if (s[*i] == '\"')
	{
		append_and_advance(cur, create_token("\"", 1, D_QUOTE, *cur));
		(*i)++;
	}
}

void	handle_redir_token(char *s, int *i, t_struct **cur)
{
	if (s[*i] == '>' && s[*i + 1] == '>')
	{
		append_and_advance(cur, create_token(">>", 2, APPEND, *cur));
		*i += 2;
	}
	else if (s[*i] == '<' && s[*i + 1] == '<')
	{
		append_and_advance(cur, create_token("<<", 2, HEREDOC, *cur));
		*i += 2;
	}
	else if (s[*i] == '>')
	{
		append_and_advance(cur, create_token(">", 1, REDIR_OUT, *cur));
		(*i)++;
	}
	else if (s[*i] == '<')
	{
		append_and_advance(cur, create_token("<", 1, REDIR_IN, *cur));
		(*i)++;
	}
}

void	append_and_advance(t_struct **cur, t_struct *new)
{
	if(!new)
		return;
	(*cur)->next = new;
	*cur = new;
}