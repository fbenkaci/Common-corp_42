/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fusion_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:42:59 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/05/23 20:53:21 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	can_join_tokens(t_struct *current, t_struct *next)
{
	if (!current || !next)
		return (0);
	if ((current->type == WORD_D_QUOTES || current->type == WORD_S_QUOTES)
		&& (next->type == WORD || next->type == WORD_D_QUOTES
			|| next->type == WORD_S_QUOTES))
		return (1);
	return (0);
}

int	join_quoted_tokens(t_struct *current)
{
	t_struct	*temp;
	char		*joined_str;

	if (!(can_join_tokens(current, current->next)))
		return (0);
	joined_str = ft_strjoin(current->str, current->next->str);
	if (!joined_str)
		return (0);
	free(current->str);
	current->str = joined_str;
	temp = current->next;
	current->next = temp->next;
	free(temp->str);
	free(temp);
	return (1);
}

int	process_quote_chars(char *str, char *clean)
{
	int	i;
	int	j;
	int	in_dquote;
	int	in_squote;

	i = 0;
	j = 0;
	in_dquote = 0;
	in_squote = 0;
	while (str[i])
	{
		if ((str[i] == '"' && !in_squote) || (str[i] == '\'' && !in_dquote))
		{
			if (str[i] == '"')
				in_dquote = !in_dquote;
			else
				in_squote = !in_squote;
			i++;
			continue ;
		}
		clean[j++] = str[i++];
	}
	return (j);
}

void	clean_quotes(t_struct *token)
{
	char	*clean;
	int		clean_len;

	if (!token || !token->str)
		return ;
	clean = NULL;
	if (token->str)
	{
		clean = malloc(ft_strlen(token->str) + 1);
		if (!clean)
			return ;
	}
	else
		return ;
	clean_len = process_quote_chars(token->str, clean);
	clean[clean_len] = '\0';
	free(token->str);
	token->str = clean;
}

void	echo_fusion(t_struct *data)
{
	t_struct	*current;

	if (!data)
		return ;
	current = data;
	while (current && current->next)
	{
		if (join_quoted_tokens(current))
			continue ;
		current = current->next;
	}
	current = data;
	while (current)
	{
		if (current->type == WORD_D_QUOTES || current->type == WORD_S_QUOTES)
			clean_quotes(current);
		current = current->next;
	}
}
